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

using std::cout;
using std::endl;

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

  bool concept = true;

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

  std::cout << " -- Input parameters: " << std::endl
	    << " -- Input file path: " << filePath << std::endl
	    << " -- Output file path: " << outPath << std::endl
	    << " -- Generated energy: " << genEn << std::endl
	    << " -- Requiring " << nSiLayers << " si layers." << std::endl
	    << " -- Processing ";
  if (pNevts == 0) std::cout << "all events." << std::endl;
  else std::cout << pNevts << " events." << std::endl;

  //Reading in the input file
  std::ostringstream input;
  input << filePath << "/" << simFileName;

  TFile *simFile = TFile::Open(input.str().c_str());
  TTree *lSimTree = (TTree*)simFile->Get("HGCSSTree");
  input.str("");
  input << filePath << "/" << recoFileName;
  
  TFile *recFile = TFile::Open(input.str().c_str());
  TTree *lRecTree = (TTree*)recFile->Get("RecoTree");
  //extracting info
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

  //initialize detector
  HGCSSDetector & myDetector = theDetector();

  myDetector.buildDetector(versionNumber,concept,isCaliceHcal);
  TRandom3 lRndm(1);
  std::cout << " -- Random number seed: " << lRndm.GetSeed() << std::endl;
  //initialise calibration class
  HGCSSCalibration mycalib(inFilePath);
  HGCSSDigitisation myDigitiser;
  myDigitiser.setRandomSeed(lRndm.GetSeed());

  const unsigned nLayers = myDetector.nLayers();
  const unsigned nSections = myDetector.nSections();

  std::cout << " -- N layers = " << nLayers << std::endl
	    << " -- N sections = " << nSections << std::endl;

  //assemble in 10*10 to fill maxE
  HGCSSGeometryConversion geomConv10(inFilePath,model,cellSize);
  std::vector<unsigned> granularity10;
  granularity10.resize(nLayers,4);
  geomConv10.setGranularity(granularity10);
  geomConv10.initialiseHistos(false,"_10");

  TFile *outputFile = TFile::Open(outPath.c_str(),"RECREATE");
  
  outputFile->cd();
  TH1F *h_recHitECAL = new TH1F("h_recHitECAL", "Reconstructed hits in the ECAL; Hits in the ECAL; Events", 1000, 0.0, 1000.0);
  h_recHitECAL->Sumw2();
  TH1F *h_recHitHCAL = new TH1F("h_recHitHCAL", "Reconstructed hits in the HCAL; Hits in the HCAL; Events", 1000, 0.0, 1000.0);
  h_recHitHCAL->Sumw2();
  TH1F *h_recHitECALfrac = new TH1F("h_recHitECALfrac", "Fraction of Reconstructed hits in the ECAL; Hit fraction; Events", 1000, 0.0, 1.0);
  h_recHitECALfrac->Sumw2();
  TH1F *h_recHitHCALfrac = new TH1F("h_recHitHCALfrac", "Fraction of Reconstructed hits in the HCAL; Hit fraction; Events", 1000, 0.0, 1.0);
  h_recHitHCALfrac->Sumw2();
  TH2F *h_recHit = new TH2F("h_recHit", "; Layer Number; Hit Occupancy", 52, -0.5, 51.5, 1000, 0.0, 1000.0);
  h_recHit->Sumw2();
  TH2F *h_recHitECALvsHCAL = new TH2F("h_recHitECALvsHCAL", "Reconstructed Hits ECAL versus HCAL; Reconstructed hits in the ECAL; Reconstructed hits in the HCAL", 1000, 0.0, 1000.0, 1000, 0.0, 1000.0);
  h_recHitECALvsHCAL->Sumw2();
  TH2F *h_recHitECALvsHCALfrac = new TH2F("h_recHitECALvsHCALfrac", "Reconstructed Fraction of Hits ECAL versus HCAL; Fraction of reconstructed hits in the ECAL; Fraction of reconstructed hits in the HCAL", 1000, 0.0, 1.0, 1000, 0.0, 1.0);
  TH1F *h_energyECAL = new TH1F("h_energyECAL", "Total energy in the ECAL for hit fraction > 0.9; ECAL energy in MIP; Events", 1000, 0.0, 10000.0);
  h_energyECAL->Sumw2();
  TH1F *h_energyECAL_AM = new TH1F("h_energyECAL_AM", "Total energy in the ECAL AM; ECAL energy in MIP; Events", 1000, 0.0, 10000.0);h_energyECAL_AM->Sumw2(); 
  TH1F *h_energyHCAL = new TH1F("h_energyHCAL", "Total energy in the HCAL for hit fraction > 0.5; HCAL energy in MIP; Events", 1000, 0.0, 10000.0);
  h_energyHCAL->Sumw2();
  TH1F *h_energyHCAL_AM = new TH1F("h_energyHCAL_AM", "Total energy in the HCAL AM; HCAL energy in MIP; Events", 1000, 0.0, 10000.0);h_energyHCAL_AM->Sumw2();
  TH2F *h_energyHCAL_frac = new TH2F("h_energyHCAL_frac", "Total energy in the HCAL Versus hit fraction; HCAL energy in MIP; Reconstructed hits in the HCAL", 100, 0.0, 100.0, 1000, 0.0, 1.0);
  h_energyHCAL_frac->Sumw2();
  TH2F *h_energyECAL_frac = new TH2F("h_energyECAL_frac", "Total energy in the ECAL Versus hit fraction; ECAL energy in MIP; Reconstructed hits in the ECAL", 100, 0.0, 100.0, 1000, 0.0, 1.0);
  h_energyECAL_frac->Sumw2();

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
  
  for (unsigned ievt(0); ievt<nEvts; ++ievt){//loop on entries
    if (debug) std::cout << "... Processing entry: " << ievt << std::endl;
    else if (ievt%1000 == 0) std::cout << "... Processing entry: " << ievt << std::endl;
    
    lSimTree->GetEntry(ievt);
    lRecTree->GetEntry(ievt);

    DetectorEnum type = DetectorEnum::FECAL;// or type == DetectorEnum::MECAL or type == DetectorEnum::BECAL;
    unsigned subdetLayer=0;
    double radius = 0.0;
    unsigned prevLayer = 10000;
    for (unsigned iH(0); iH<(*simhitvec).size(); ++iH){//loop on simhits
      HGCSSSimHit lHit = (*simhitvec)[iH];
      if (lHit.silayer() >= nSiLayers) continue;
      unsigned layer = lHit.layer();
      std::cout << "layer before cuts = " << layer << std::endl;
    
     if (layer >= nLayers) continue;
      unsigned sec =  myDetector.getSection(layer);
      double posx = lHit.get_x(cellSize);
      double posy = lHit.get_y(cellSize);
      double posz = lHit.get_z();
      double lRealTime = mycalib.correctTime(lHit.time(),posx,posy,posz);
      double energy = lHit.energy()*mycalib.MeVToMip(layer);
      double radius = sqrt(pow(posx,2)+pow(posy,2)); 
      bool passTime = myDigitiser.passTimeCut(type,lRealTime);

      if (layer != prevLayer){
        const HGCSSSubDetector & subdet = myDetector.subDetectorByLayer(layer);
        type = subdet.type;
        subdetLayer = layer-subdet.layerIdMin;
        prevLayer = layer;
        if (debug > 1) std::cout << " - layer " << layer << " " << subdet.name << " " << subdetLayer << std::endl;
      }

      if (type == DetectorEnum::FECAL ||
          type == DetectorEnum::MECAL ||
          type == DetectorEnum::BECAL){
        //correct for si thickness 100um
        //        //default for 200um
                       energy *= 2.;  }

     geomConv10.fill(type,subdetLayer,energy,lRealTime,posx,posy,posz);
     std::cout << "type = " << type << std::endl;
     std::cout << "subdetLayer = " << subdetLayer << std::endl;
     std::cout << "energy = " << energy << std::endl;
     std::cout << "lRealTime = " << lRealTime << std::endl;
     std::cout << "posx = " << posx << std::endl;
     std::cout << "posy = " << posy << std::endl;
     std::cout << "posz = " << posz << std::endl;
     if (!passTime) continue;
    }//loop on simulated hits
    //geomConv10.initialiseHistos();
    int recHitECAL = 0;
    int recHitHCAL = 0;
    int recHitTotal = 0;
    double energyECAL = 0.0;
    double energyHCAL = 0.0;
    std::vector<int> recHit(52);
    for (unsigned iH=0; iH<rechitvec->size(); ++iH){//loop on rechits
      
      HGCSSRecoHit lHit = rechitvec->at(iH);
      double energy = lHit.energy();//in MIP already...
      unsigned layer = lHit.layer();
      unsigned sec =  myDetector.getSection(layer);
      double posx = lHit.get_x();
      double posy = lHit.get_y();
      double posz = lHit.get_z();
      double radius = sqrt(pow(posx,2)+pow(posy,2));
      double lRealTime = mycalib.correctTime(lHit.time(),posx,posy,posz);
      //const HGCSSSubDetector & subdet = myDetector.subDetectorByLayer(layer);
      //type = subdet.type;
      //geomConv10.fill(type,subdetLayer,energy,lRealTime,posx,posy,posz);
      if(energy > 1.0) recHitTotal++;
      if(layer>=0 and layer<28 and energy > 1.0) recHitECAL++;
      else if(layer>=28 and layer<52 and energy > 1.0) recHitHCAL++; 
      ++recHit.at(layer);
      if(energy > 1.0) energyECAL += energy;
      if(energy > 1.0) energyHCAL += energy;
    }//loop on rechits
    double fracECAL = (double)recHitECAL/(double)recHitTotal;
    double fracHCAL = (double)recHitHCAL/(double)recHitTotal;
    h_recHitECAL->Fill(recHitECAL);
    h_recHitHCAL->Fill(recHitHCAL);
    h_recHitECALfrac->Fill((double)recHitECAL/(double)recHitTotal);
    h_recHitHCALfrac->Fill((double)recHitHCAL/(double)recHitTotal); 
    h_recHitECALvsHCAL->Fill(recHitECAL, recHitHCAL);
    h_recHitECALvsHCALfrac->Fill((double)recHitECAL/(double)recHitTotal, (double)recHitHCAL/(double)recHitTotal);
    if(fracECAL > 0.9) h_energyECAL->Fill(energyECAL);
    if(fracHCAL > 0.5) h_energyHCAL->Fill(energyHCAL);
    h_energyHCAL_frac->Fill(energyHCAL, (double)recHitHCAL/(double)recHitTotal);
    h_energyECAL_frac->Fill(energyECAL, (double)recHitECAL/(double)recHitTotal);
    for (unsigned int iLayer=0; iLayer<52; ++iLayer){
      h_recHit->Fill(iLayer, recHit.at(iLayer));
    }
    cout << "rechitvec->size() = " << rechitvec->size() << endl;
    cout << "simhitvec->size() = " << simhitvec->size() << endl;
    //Implementing Anne-Marie's method
    double h_Etot10_ecal = 0.0;
    double h_Etot10_hcal = 0.0;
    for (unsigned iLayer=0; iLayer<28; ++iLayer){
      double absweight = (ssvec->at(iLayer)).volX0trans()/(ssvec->at(1)).volX0trans();
      TH2D *hist_ecal = geomConv10.get2DHist(iLayer,"E");
      for (int bin(1);bin<(hist_ecal->GetNbinsX()*hist_ecal->GetNbinsY()+1);++bin){
        double E = hist_ecal->GetBinContent(bin);
        if (E>1.) h_Etot10_ecal += E*absweight;
      }//end of the loop on bins  
    }//end of the loop on layers
    if(fracECAL > 0.9) h_energyECAL_AM->Fill(h_Etot10_ecal);
    double E=0; 
    for (unsigned iLayer=28; iLayer<52; ++iLayer){
      double absweight = (ssvec->at(iLayer)).volX0trans()/(ssvec->at(1)).volX0trans();
      TH2D *hist_hcal = geomConv10.get2DHist(iLayer,"E");
      std::cout << "hist_hcal->GetEntries() = " << hist_hcal->GetEntries() << std::endl;
      for (int bin(1);bin<(hist_hcal->GetNbinsX()*hist_hcal->GetNbinsY()+1);++bin){
        E = hist_hcal->GetBinContent(bin);
        if(E>0) std::cout << "E = " << E << std::endl;
        if (E>1.) h_Etot10_hcal += E*absweight;
      }//end of the loop on bins  
    }//end of the loop on layers
    std::cout << "h_Etot10_hcal = " << h_Etot10_hcal << std::endl;
    h_energyHCAL_AM->Fill(h_Etot10_hcal);      

  }//loop on entries
  
  outputFile->Write();
  outputFile->Close();
  
  return 0;

}//main
