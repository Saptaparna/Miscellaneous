#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include <boost/algorithm/string.hpp>

#include "TFile.h"
#include "TTree.h"
#include "TH3F.h"
#include "TH2F.h"
#include "TH1F.h"
#include "TF1.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TRandom3.h"

#include "HGCSSEvent.hh"
#include "HGCSSInfo.hh"
#include "HGCSSSamplingSection.hh"
#include "HGCSSSimHit.hh"
#include "HGCSSRecoHit.hh"
#include "HGCSSGenParticle.hh"
#include "HGCSSParameters.hh"
#include "HGCSSCalibration.hh"
#include "HGCSSDigitisation.hh"
#include "HGCSSDetector.hh"
#include "HGCSSGeometryConversion.hh"

int main(int argc, char** argv){//main  

  if (argc < 7) {
    std::cout << " Usage: " 
	      << argv[0] << " <nEvts to process (0=all)>"
	      << " <path to input files>"
	      << " <name of input sim file>"
	      << " <name of input reco file>"
	      << " <full path to output file>"
	      << " <number of si layers to consider: 1,2 or 3>" 
	      << " <optional: debug (default=0)>"
	      << std::endl;
    return 1;
  }

  //////////////////////////////////////////////////////////
  //// Hardcoded config ////////////////////////////////////
  //////////////////////////////////////////////////////////
  //for HGCAL, true means only 12 FHCAL layers considered (24 are simulated)
  bool concept = true;

  bool selectEarlyDecays = true;

  double minX=-1700,maxX=1700;
  double minY=-1700,maxY=1700;
  double minZ=3170,maxZ=5070;
  //double minX=-510,maxX=510;
  //double minY=-510,maxY=510;
  //double minZ=-1000,maxZ=1000;

  unsigned nX=(maxX-minX)/10,nY=(maxY-minY)/10;
  unsigned nZ=maxZ-minZ;

  double FHcalEMCalib = 118;//40.4;//39.81;//38;
  double FHcalEMOffset = -209;//-3.9;//1.9;//-15;
  double BHcalEMCalib = 9.92;//40.4;//39.81;//38;
  double BHcalEMOffset = -5.1;//1.9;//-15;
  double HcalPionCalib = 0.92;//1/1.19;//0.901;//1./0.9;//1/0.846;
  double HcalPionOffset = 0;//-0.81;
  double BHcalSlope = 2.7;
  double G4BHcalSlope = 0.24;
  // choose a jet definition
  //double R = 0.5;
  //JetDefinition jet_def(antikt_algorithm, R);

  //////////////////////////////////////////////////////////
  //// End Hardcoded config ////////////////////////////////////
  //////////////////////////////////////////////////////////

  const unsigned pNevts = atoi(argv[1]);
  std::string filePath = argv[2];
  std::string simFileName = argv[3];
  std::string recoFileName = argv[4];

  std::string inFilePath = filePath+simFileName;

  std::string outPath = argv[5];
  unsigned nSiLayers = 2;
  nSiLayers = atoi(argv[6]);

  unsigned debug = 0;
  if (argc >7) debug = atoi(argv[7]);


  unsigned genEn;
  size_t end=outPath.find_last_of(".root");
  size_t start=outPath.find_last_of("e");
  std::istringstream(outPath.substr(start+1,end))>>genEn;

  bool isEM = false;

  if (inFilePath.find("e-")!=inFilePath.npos || 
      inFilePath.find("e+")!=inFilePath.npos) isEM = true;

  if (selectEarlyDecays && isEM) {
    selectEarlyDecays = false;
    HcalPionCalib = 1;
    HcalPionOffset = 0;
  }

  std::cout << " -- Input parameters: " << std::endl
	    << " -- Input file path: " << filePath << std::endl
	    << " -- Output file path: " << outPath << std::endl
	    << " -- Generated energy: " << genEn << std::endl
	    << " -- Requiring " << nSiLayers << " si layers." << std::endl
	    << " -- Processing ";
  if (pNevts == 0) std::cout << "all events." << std::endl;
  else std::cout << pNevts << " events." << std::endl;

  TRandom3 lRndm(1);
  std::cout << " -- Random number seed: " << lRndm.GetSeed() << std::endl;

  /////////////////////////////////////////////////////////////
  //input
  /////////////////////////////////////////////////////////////


  std::ostringstream input;
  input << filePath << "/" << simFileName;

  TFile *simFile = TFile::Open(input.str().c_str());

  if (!simFile) {
    std::cout << " -- Error, input file " << input.str() << " cannot be opened. Exiting..." << std::endl;
    return 1;
  }
  else std::cout << " -- input file " << simFile->GetName() << " successfully opened." << std::endl;
  
  TTree *lSimTree = (TTree*)simFile->Get("HGCSSTree");
  if (!lSimTree){
    std::cout << " -- Error, tree HGCSSTree cannot be opened. Exiting..." << std::endl;
    return 1;
  }

  input.str("");
  input << filePath << "/" << recoFileName;
  
  TFile *recFile = TFile::Open(input.str().c_str());

  if (!recFile) {
    std::cout << " -- Error, input file " << input.str() << " cannot be opened. Exiting..." << std::endl;
    return 1;
  }
  else std::cout << " -- input file " << recFile->GetName() << " successfully opened." << std::endl;

  TTree *lRecTree = (TTree*)recFile->Get("RecoTree");
  if (!lRecTree){
    std::cout << " -- Error, tree RecoTree cannot be opened. Exiting..." << std::endl;
    return 1;
  }


  /////////////////////////////////////////////////////////////
  //Info
  /////////////////////////////////////////////////////////////

  HGCSSInfo * info=(HGCSSInfo*)simFile->Get("Info");
  const double cellSize = info->cellSize();
  const unsigned versionNumber = info->version();
  const unsigned model = info->model();
  
  //models 0,1 or 3.
  bool isTBsetup = (model != 2);
  bool isCaliceHcal = versionNumber==23;//inFilePath.find("version23")!=inFilePath.npos || inFilePath.find("version_23")!=inFilePath.npos;

  //extract input energy

  std::cout << " -- Version number is : " << versionNumber 
	    << ", model = " << model
	    << ", cellSize = " << cellSize
	    << std::endl;


  //initialise detector
  HGCSSDetector & myDetector = theDetector();

  myDetector.buildDetector(versionNumber,concept,isCaliceHcal);

  //initialise calibration class
  HGCSSCalibration mycalib(inFilePath);
  HGCSSDigitisation myDigitiser;
  myDigitiser.setRandomSeed(lRndm.GetSeed());

  const unsigned nLayers = myDetector.nLayers();
  const unsigned nSections = myDetector.nSections();

  std::cout << " -- N layers = " << nLayers << std::endl
	    << " -- N sections = " << nSections << std::endl;

  HGCSSGeometryConversion geomConv5(inFilePath,model,cellSize);
     //assemble in 5*5 and 10*10 to fill maxE
  std::vector<unsigned> granularity5;
  granularity5.resize(nLayers,2);
  geomConv5.setGranularity(granularity5);
  geomConv5.initialiseHistos(false,"_5");
  HGCSSGeometryConversion geomConv10(inFilePath,model,cellSize);
  std::vector<unsigned> granularity10;
  granularity10.resize(nLayers,4);
  geomConv10.setGranularity(granularity10);
  geomConv10.initialiseHistos(false,"_10");
  HGCSSGeometryConversion geomConv15(inFilePath,model,cellSize);
  std::vector<unsigned> granularity15;
  granularity15.resize(nLayers,6);
  geomConv15.setGranularity(granularity15);
  geomConv15.initialiseHistos(false,"_15");
  HGCSSGeometryConversion geomConv2d5(inFilePath,model,cellSize);
  std::vector<unsigned> granularity2d5;
  granularity2d5.resize(nLayers,1);
  geomConv2d5.setGranularity(granularity2d5);
  geomConv2d5.initialiseHistos(false,"_2d5");

  TFile *outputFile = TFile::Open(outPath.c_str(),"RECREATE");
  
  if (!outputFile) {
    std::cout << " -- Error, output file " << outPath << " cannot be opened. Please create output directory. Exiting..." << std::endl;
    return 1;
  }
  else {
    std::cout << " -- output file " << outputFile->GetName() << " successfully opened." << std::endl;
  }
  
  
  std::cout << " -- 2-D histograms: " << std::endl
	    << " -- X: " << nX << " " << minX << " " << maxX << std::endl
	    << " -- Y: " << nY << " " << minY << " " << maxY << std::endl
	    << " -- Z: " << nZ << " " << minZ << " " << maxZ << std::endl
    ;
  outputFile->cd();

  TH2F *p_EsimvsLayer = new TH2F("p_EsimvsLayer",";layer ; Esim (MIPs)",
				 nLayers,0,nLayers,
				 1000,0,5000);
  TH2F *p_ErecovsLayer = new TH2F("p_ErecovsLayer",";layer ; Ereco (MIPs)",
				  nLayers,0,nLayers,
				  1000,0,5000);
  TH1F *p_timeSim = new TH1F("p_timeSim",";G4 time (ns)",1000,0,1000);
  TH2F *p_HCALvsECAL = new TH2F("p_HCALvsECAL",";ECAL (GeV);HCAL (GeV)",
				500,0,500,
				500,0,500);

  TH2F *p_BHCALvsFHCAL = new TH2F("p_BHCALvsFHCAL",";FHCAL (GeV);BHCAL (GeV)",
				  1000,0,2000,
				  1000,0,2000);

  TH2F *p_G4_BHCALvsFHCAL = new TH2F("p_G4_BHCALvsFHCAL",";FHCAL (GeV);BHCAL (GeV)",
				     5000,0,100000,
				     5000,0,100000);

  TH2F *p_ECALvsHCAL = new TH2F("p_ECALvsHCAL",";ECAL energy (MIP);HCAL energy (MIP)",
  				     10000,0,100000,
  				     10000,0,100000);

  TH1F *p_nGenPart = new TH1F("p_nGenPart",";n(genParticles)",200,0,200);
  TH1F *p_genPartId = new TH1F("p_genPartId",";pdgid",12000,-6000,6000);

  TH1F *p_firstInteraction = new TH1F("p_firstInteraction",";layer with 1st nucl. int.",nLayers,0,nLayers);

  TH1F *p_maxEhit_2d5 = new TH1F("p_maxEhit_2d5",";maxE (MIPS) in 2.5 #times 2.5 mm^{2} cell; n_{events}",5000,0,5000);
  TH1F *p_maxEhit_5 = new TH1F("p_maxEhit_5",";maxE (MIPS) in 5 #times 5 mm^{2} cell; n_{events}",5000,0,15000);
  TH1F *p_maxEhit_10 = new TH1F("p_maxEhit_10",";maxE (MIPS) in 10 #times 10 mm^{2} cell; n_{events}",5000,0,15000);
  TH1F *p_maxEhit_15 = new TH1F("p_maxEhit_15",";maxE (MIPS) in 15 #times 15 mm^{2} cell; n_{events}",5000,0,15000);

  p_maxEhit_2d5->StatOverflows();
  p_maxEhit_5->StatOverflows();
  p_maxEhit_10->StatOverflows();
  p_maxEhit_15->StatOverflows();

  //  TH1F *p_nAboveMax_2d5 = new TH1F("p_nAboveMax_2d5",";n(E>maxE) 2.5 #times 2.5 mm^{2} cell; n_{events}",500,0,500);
  TH1F *p_nAboveMax_5 = new TH1F("p_nAboveMax_5",";n(E>maxE) 5 #times 5 mm^{2} cell; n_{events}",50,0,50);
  TH1F *p_nAboveMax_10 = new TH1F("p_nAboveMax_10",";n(E>maxE) 10 #times 10 mm^{2} cell; n_{events}",50,0,50);
  TH1F *p_nAboveMax_15 = new TH1F("p_nAboveMax_15",";n(E>maxE) 15 #times 15 mm^{2} cell; n_{events}",50,0,50);

  TH1F *p_nAbove1_5 = new TH1F("p_nAbove1_5",";n(E>1 MIP) 5 #times 5 mm^{2} cell; n_{events}",1000,0,1000);
  TH1F *p_nAbove1_10 = new TH1F("p_nAbove1_10",";n(E>1 MIP) 10 #times 10 mm^{2} cell; n_{events}",1000,0,1000);
  TH1F *p_nAbove1_15 = new TH1F("p_nAbove1_15",";n(E>1 MIP) 15 #times 15 mm^{2} cell; n_{events}",1000,0,1000);
  p_nAbove1_5->StatOverflows();
  p_nAbove1_10->StatOverflows();
  p_nAbove1_15->StatOverflows();

  TH1F *p_fracEmissed_5 = new TH1F("p_fracEmissed_5",";#frac{E_{missed}}{E_{tot}} 5 #times 5 mm^{2} cell;n_{events}",500,0,1);
  TH1F *p_fracEmissed_10 = new TH1F("p_fracEmissed_10",";#frac{E_{missed}}{E_{tot}} 10 #times 10 mm^{2} cell;n_{events}",500,0,1);
  TH1F *p_fracEmissed_15 = new TH1F("p_fracEmissed_15",";#frac{E_{missed}}{E_{tot}} 15 #times 15 mm^{2} cell;n_{events}",500,0,1);

  //mean+3*rms -> leads at most 2 more cells in <1% of events
  //TF1 *fit5 = new TF1("fit5","72+5.32*x",0,2000);
  //TF1 *fit10 = new TF1("fit10","92+7.60*x",0,2000);
  //TF1 *fit15 = new TF1("fit15","106+8.86*x",0,2000);
  //mean max
  TF1 *fit5 = new TF1("fit5","21+4.15*x-0.000331*x*x",0,2000);
  TF1 *fit10 = new TF1("fit10","28+6.04*x-0.000536*x*x",0,2000);
  TF1 *fit15 = new TF1("fit15","34+7.13*x-0.000676*x*x",0,2000);

  double maxEavg5 = 5000;//fit5->Eval(genEn);
  double maxEavg10 = 5000;//fit10->Eval(genEn);
  double maxEavg15 = 5000;//fit15->Eval(genEn);

  std::cout << " -- Values taken for <MaxEhit>: 5x5="
	    << maxEavg5 << ", 10x10=" << maxEavg10 << ", 15x15=" << maxEavg15
	    << std::endl;

  TH1F *p_nSimHits = new TH1F("p_nSimHits","n(SimHits)",
			      1000,0,500000);
  p_nSimHits->StatOverflows();
  
  TH1F *p_nRecHits = new TH1F("p_nRecHits","n(RecHits)",
			      1000,0,5000);
  p_nRecHits->StatOverflows();

  TH1F *p_EsimTotal = new TH1F("p_EsimTotal",";Esim (MIPs)",30000,0,300000);
  TH1F *p_ErecoTotal = new TH1F("p_ErecoTotal",";Ereco (GeV)",2000,0,1000);
  p_EsimTotal->StatOverflows();
  p_ErecoTotal->StatOverflows();

  TH1F *p_Esim[nSections];
  TH1F *p_Ereco[nSections];
  TH1F *p_ETOT10 = new TH1F("p_ETOT10", "; Etot > 1 MIP 10 #times 10 mm^{2} cell", 30000,0,300000);

  std::ostringstream lName;

  for (unsigned iD(0); iD<nSections; ++iD){
    lName.str("");
    lName << "p_Esim_" << myDetector.detName(iD);
    if (myDetector.detType(iD)==DetectorEnum::BHCAL1 || myDetector.detType(iD)==DetectorEnum::BHCAL2) p_Esim[iD] = new TH1F(lName.str().c_str(),";Esim (MIPs)",2000,0,20000);
    else p_Esim[iD] = new TH1F(lName.str().c_str(),";Esim (MIPs)",20000,0,200000);
    p_Esim[iD]->StatOverflows();
    lName.str("");
    lName << "p_Ereco_" << myDetector.detName(iD);
    if (myDetector.detType(iD)==DetectorEnum::BHCAL1 || myDetector.detType(iD)==DetectorEnum::BHCAL2)  p_Ereco[iD] = new TH1F(lName.str().c_str(),";Ereco (MIPs)",200,0,2000);
    else p_Ereco[iD] = new TH1F(lName.str().c_str(),";Ereco (MIPs)",1000,0,10000);
    p_Ereco[iD]->StatOverflows();
  }

  HGCSSEvent * event = 0;
  std::vector<HGCSSSamplingSection> * ssvec = 0;
  std::vector<HGCSSSimHit> * simhitvec = 0;
  std::vector<HGCSSRecoHit> * rechitvec = 0;
  std::vector<HGCSSGenParticle> * genvec = 0;
  
  lSimTree->SetBranchAddress("HGCSSEvent",&event);
  lSimTree->SetBranchAddress("HGCSSSamplingSectionVec",&ssvec);
  lSimTree->SetBranchAddress("HGCSSSimHitVec",&simhitvec);
  lSimTree->SetBranchAddress("HGCSSGenParticleVec",&genvec);
  
  lRecTree->SetBranchAddress("HGCSSRecoHitVec",&rechitvec);

  const unsigned nEvts = ((pNevts > lSimTree->GetEntries() || pNevts==0) ? static_cast<unsigned>(lSimTree->GetEntries()) : pNevts) ;
  
  std::cout << "- Processing = " << nEvts  << " events out of " << lSimTree->GetEntries() << std::endl;
  
  //Initialise histos
  //necessary to have overflows ?
  gStyle->SetOptStat(1111111);
  double EtotSim[nLayers];
  double EtotRec[nLayers];
  
  for (unsigned iL(0);iL<nLayers;++iL){
    EtotSim[iL] = 0;
    EtotRec[iL] = 0;
  }
  double Esim[nSections];
  double Ereco[nSections];
  for (unsigned iD(0); iD<nSections; ++iD){
    Esim[iD] = 0;
    Ereco[iD] = 0;
  }

  bool firstEvent = true;
  std::map<unsigned,bool> channelAlive;

  for (unsigned ievt(0); ievt<nEvts; ++ievt){//loop on entries
    if (debug) std::cout << "... Processing entry: " << ievt << std::endl;
    else if (ievt%50 == 0) std::cout << "... Processing entry: " << ievt << std::endl;
    
    lSimTree->GetEntry(ievt);
    lRecTree->GetEntry(ievt);

    unsigned firstInteraction = 0;

    //to get simhit energy in final granularity
    unsigned prevLayer = 10000;
    DetectorEnum type = DetectorEnum::FECAL;
    unsigned subdetLayer=0;

    for (unsigned iH(0); iH<(*simhitvec).size(); ++iH){//loop on hits
      HGCSSSimHit lHit = (*simhitvec)[iH];

      //discard some si layers...
      if (lHit.silayer() >= nSiLayers) continue; 

      unsigned layer = lHit.layer();
      std::cout << "layer before cuts = " << layer << std::endl;
      if (layer >= nLayers) {
	//std::cout << " WARNING! SimHits with layer " << layer << " outside of detector's definition range ! Please fix the digitiser or the detector definition used here. Ignoring..." << std::endl;
	continue;
      }
      if (layer != prevLayer){
	const HGCSSSubDetector & subdet = myDetector.subDetectorByLayer(layer);
	type = subdet.type;
	subdetLayer = layer-subdet.layerIdMin;
	prevLayer = layer;
	if (debug > 1) std::cout << " - layer " << layer << " " << subdet.name << " " << subdetLayer << std::endl;
      }     

      unsigned sec =  myDetector.getSection(layer);

      if ( firstInteraction == 0 &&
	   (lHit.nNeutrons()>0 || 
	    lHit.nProtons()>0 ||
	    lHit.nHadrons()>0 ) && 
	   lHit.mainParentTrackID() > 0
	   ) firstInteraction = layer;

      double posx = lHit.get_x(cellSize);
      double posy = lHit.get_y(cellSize);
      double posz = lHit.get_z();
      //double radius = sqrt(posx*posx+posy*posy);
      double lRealTime = mycalib.correctTime(lHit.time(),posx,posy,posz);
      double energy = lHit.energy()*mycalib.MeVToMip(layer);

      //if (energy>1) std::cout << "Hit " << layer << " " << posx << " " << posy << " " << posz << " " << energy << std::endl;

      if (type == DetectorEnum::FECAL ||
	  type == DetectorEnum::MECAL ||
	  type == DetectorEnum::BECAL){
	//correct for si thickness 100um
	//default for 200um
	energy *= 2.;
      }

      geomConv2d5.fill(type,subdetLayer,energy,lRealTime,posx,posy,posz);
      if (layer==11 || layer==18) geomConv5.fill(type,subdetLayer,energy,lRealTime,posx,posy,posz);
      geomConv10.fill(type,subdetLayer,energy,lRealTime,posx,posy,posz);
      std::cout << "type = " << type << std::endl;
      std::cout << "subdetLayer = " << subdetLayer << std::endl;
      std::cout << "energy = " << energy << std::endl;
      std::cout << "lRealTime = " << lRealTime << std::endl;
      std::cout << "posx = " << posx << std::endl;
      std::cout << "posy = " << posy << std::endl;
      std::cout << "posz = " << posz << std::endl;
      geomConv15.fill(type,subdetLayer,energy,lRealTime,posx,posy,posz);

      bool passTime = myDigitiser.passTimeCut(type,lRealTime);
      if (!passTime) continue;

      if (debug>1) {
	std::cout << " --  SimHit " << iH << "/" << (*simhitvec).size() << " --" << std::endl
		  << " --  position x,y " << posx << "," << posy << std::endl;
	lHit.Print(std::cout);
      }

      //correct for time of flight
      p_timeSim->Fill(lRealTime);
      
      EtotSim[layer] += energy;
      if (debug>1) std::cout << "-hit" << iH << "-" << layer << " " << energy << " " << EtotSim[layer];

      //double absweight = myDetector.subDetectorByLayer(layer).absWeight;
      double absweight = (*ssvec)[layer].volX0trans()/(*ssvec)[1].volX0trans();

      Esim[sec] += energy*absweight;
      
    }//loop on hits

    double h_Etot10_ecal = 0.0;
    double h_Etot10_hcal = 0.0;
    bool HCALevent = false;

    for (unsigned iL=0; iL<28; ++iL){//ECAL layers only
      double absweight = (*ssvec)[iL].volX0trans()/(*ssvec)[1].volX0trans(); 
      TH2D *hist_ecal = geomConv10.get2DHist(iL,"E");
      double Emax_ecal = hist_ecal->GetBinContent(hist_ecal->GetMaximumBin());
      for (int bin(1);bin<(hist_ecal->GetNbinsX()*hist_ecal->GetNbinsY()+1);++bin){
        double E = hist_ecal->GetBinContent(bin);
        if (E>1.) h_Etot10_ecal += E*absweight;
      }//end of the loop on bins
    }//end of the loop on layers
    
    for (unsigned iL=28; iL<52; ++iL){//HCAL layers only
      HCALevent=true;
      double absweight = (*ssvec)[iL].volX0trans()/(*ssvec)[1].volX0trans();
      TH2D *hist_hcal = geomConv10.get2DHist(iL,"E");
      std::cout << "hist_hcal->GetEntries() = " << hist_hcal->GetEntries() << std::endl;
      double Emax_hcal = hist_hcal->GetBinContent(hist_hcal->GetMaximumBin());
      for (int bin(1);bin<(hist_hcal->GetNbinsX()*hist_hcal->GetNbinsY()+1);++bin){
        double E = hist_hcal->GetBinContent(bin);   
        if (E>1.) h_Etot10_hcal += E*absweight;
        if(E>0) std::cout << "E = " << E << std::endl;
      }//end of the loop on bins
    }//end of the loop on layers
    std::cout << "h_Etot10_hcal = " << h_Etot10_hcal << std::endl;
    p_ECALvsHCAL->Fill(h_Etot10_ecal, h_Etot10_hcal);
    std::cout << "rechitvec->size() = " << rechitvec->size() << std::endl;
    std::cout << "simhitvec->size() = " << simhitvec->size() << std::endl;
    
    geomConv2d5.initialiseHistos();
    geomConv5.initialiseHistos();
    geomConv10.initialiseHistos();
    geomConv15.initialiseHistos();

    p_nSimHits->Fill((*simhitvec).size());
    p_firstInteraction->Fill(firstInteraction);

    if (debug)  std::cout << std::endl;

    for (unsigned iH(0); iH<(*rechitvec).size(); ++iH){//loop on rechits
      HGCSSRecoHit lHit = (*rechitvec)[iH];
      if (debug>1) {
	lHit.Print(std::cout);
      }
      
      double energy = lHit.energy();//in MIP already...
      unsigned layer = lHit.layer();

      if (layer >= nLayers) {
	continue;
      }
      unsigned sec =  myDetector.getSection(layer);
      
      EtotRec[layer] += energy;
      if (debug>1) std::cout << "-hit" << iH << "-" << layer << " " << energy << " " << EtotRec[layer];

      double absweight = (*ssvec)[layer].voldEdx()/(*ssvec)[1].voldEdx();

      Ereco[sec] += energy*absweight;
      double energy_sum = 0.0;
      energy_sum += energy;
   }//loop on rechits
    
    p_nRecHits->Fill((*rechitvec).size());

    double Eecal = 0;
    if (myDetector.section(DetectorEnum::FECAL)<nSections) Eecal += myDigitiser.MIPtoGeV(myDetector.subDetectorByEnum(DetectorEnum::FECAL),Ereco[myDetector.section(DetectorEnum::FECAL)]);
    if (myDetector.section(DetectorEnum::FECAL)<nSections) //std::cout << "Eecal = " << Eecal << std::endl;
    if (myDetector.section(DetectorEnum::MECAL)<nSections) Eecal += myDigitiser.MIPtoGeV(myDetector.subDetectorByEnum(DetectorEnum::MECAL),Ereco[myDetector.section(DetectorEnum::MECAL)]);
    if (myDetector.section(DetectorEnum::BECAL)<nSections) Eecal += myDigitiser.MIPtoGeV(myDetector.subDetectorByEnum(DetectorEnum::BECAL),Ereco[myDetector.section(DetectorEnum::BECAL)]);
    double Efhcal = 0;
    if (myDetector.section(DetectorEnum::FHCAL)<nSections) Efhcal += (Ereco[myDetector.section(DetectorEnum::FHCAL)]-FHcalEMOffset)/FHcalEMCalib;
    double Ebhcal = 0;
    if (myDetector.section(DetectorEnum::BHCAL1)<nSections) Ebhcal += (Ereco[myDetector.section(DetectorEnum::BHCAL1)]-BHcalEMOffset)/BHcalEMCalib;
    if (myDetector.section(DetectorEnum::BHCAL2)<nSections) Ebhcal += (Ereco[myDetector.section(DetectorEnum::BHCAL2)]-BHcalEMOffset)/BHcalEMCalib;

    double Etotcal = Eecal+(Efhcal+(1./BHcalSlope*Ebhcal)-HcalPionOffset)/HcalPionCalib;

    bool doFill = true;
    if (selectEarlyDecays && firstInteraction>5) doFill = false;

    double etotmips = 0;
    if (versionNumber==21) etotmips = Esim[0]+Esim[1]/G4BHcalSlope;
    else{ 
      for (unsigned iD(0); iD<nSections; ++iD){
	etotmips += Esim[iD];//*(versionNumber==12?1:myDetector.subDetectorBySection(iD).absWeight);
      }
    }
    
    for (unsigned iL(0);iL<nLayers;++iL){//loop on layers
      if (doFill) p_EsimvsLayer->Fill(iL,EtotSim[iL]);
      if (doFill) p_ErecovsLayer->Fill(iL,EtotRec[iL]);
      EtotSim[iL] = 0;
      EtotRec[iL] = 0;

    }//loop on layers
    if (doFill) {
      p_HCALvsECAL->Fill(Eecal,Efhcal+Ebhcal);
      p_BHCALvsFHCAL->Fill(Efhcal,Ebhcal);
      p_G4_BHCALvsFHCAL->Fill(Esim[0],Esim[1]);
    }

    for (unsigned iD(0); iD<nSections; ++iD){
      if (doFill)p_Esim[iD]->Fill(Esim[iD]);
      if (doFill)p_Ereco[iD]->Fill(Ereco[iD]);
      Esim[iD]=0;
      Ereco[iD]=0;
    }
    
    if (doFill){
      p_EsimTotal->Fill(etotmips);
      p_ErecoTotal->Fill(Etotcal);
    }
    
    firstEvent = false;
  }//loop on entries
  
  outputFile->Write();
  //outputFile->Close();
  
  return 0;


}//main
