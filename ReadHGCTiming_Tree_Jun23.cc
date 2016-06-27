#include <TF1.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TH3F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <TGraphAsymmErrors.h>
#include <TVector3.h>
#include <TRandom.h>

using std::string;

TLorentzVector fillTLorentzVector(double pT, double eta, double phi, double E)
{
  TLorentzVector object_p4;
  object_p4.SetPtEtaPhiE(pT, eta, phi, E);
  return object_p4;
}

typedef struct
{
  float recHitE;
  float recHitX;
  float recHitY;
  float recHitZ;
  float recHitTime;
} RecHitInfo;

bool sortRecHitsInDescendingE(RecHitInfo recHit1, RecHitInfo recHit2)
{
  return (recHit1.recHitE > recHit2.recHitE);
}

bool sortRecHitsInAscendingE(RecHitInfo recHit1, RecHitInfo recHit2)
{
  return (recHit1.recHitE < recHit2.recHitE);
}

std::string itoa(int i) 
{
  char res[15];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

int ReadHGCTiming_Tree_Jun3(std::string infile, std::string outfile)
{
  std::string inputfilename=(infile+".root").c_str();
  TChain *tree=new TChain("hgctiming/HGCTiming");
  tree->Add(inputfilename.c_str());
  std::cout<<"Opened input file "<<inputfilename<<std::endl;

  Int_t           run;
  Int_t           event;
  Int_t           lumi;
  Float_t         vertex_x;
  Float_t         vertex_y;
  Float_t         vertex_z;
  vector<float>   *recHit_energy;
  vector<float>   *recHit_x;
  vector<float>   *recHit_y;
  vector<float>   *recHit_z;
  vector<float>   *recHit_time;
  vector<float>   *uncRecHit_time;
  TLorentzVector  *GenVertex;

  recHit_energy = 0;
  recHit_x = 0;
  recHit_y = 0;
  recHit_z = 0;
  GenVertex = 0;
  uncRecHit_time = 0;
  recHit_time = 0;

  tree->SetBranchAddress("run", &(run));
  tree->SetBranchAddress("lumi", &(lumi));
  tree->SetBranchAddress("event", &(event));
  tree->SetBranchAddress("vertex_x", &(vertex_x));
  tree->SetBranchAddress("vertex_y", &(vertex_y));
  tree->SetBranchAddress("vertex_z", &(vertex_z));
  tree->SetBranchAddress("recHit_energy", &(recHit_energy));
  tree->SetBranchAddress("recHit_x", &(recHit_x));
  tree->SetBranchAddress("recHit_y", &(recHit_y));
  tree->SetBranchAddress("recHit_z", &(recHit_z));
  tree->SetBranchAddress("recHit_time", &(recHit_time));
  tree->SetBranchAddress("GenVertex", &(GenVertex));
  tree->SetBranchAddress("uncRecHit_time", &(uncRecHit_time));

  TH1F *h_vertex_x=new TH1F("h_vertex_x", "h_vertex_x; Vertex [mm]; Events", 100, -50.0, 50.0); h_vertex_x->Sumw2();
  TH1F *h_vertex_y=new TH1F("h_vertex_y", "h_vertex_y; Vertex [mm]; Events", 100, -50.0, 50.0); h_vertex_y->Sumw2();
  TH1F *h_vertex_z=new TH1F("h_vertex_z", "h_vertex_z; Vertex [mm]; Events", 100, -50.0, 50.0); h_vertex_z->Sumw2();
  TH1F *h_recHit_95HighestEnergy = new TH1F("h_recHit_95HighestEnergy", "h_recHit_95HighestEnergy; Energy; Entries", 5000, 0, 5.0); h_recHit_95HighestEnergy->Sumw2();

  TH1F *h_recHit_95X = new TH1F("h_recHit_95X", "h_recHit_95X; recHit x coordinate; Events", 200, -100, 100); h_recHit_95X->Sumw2();
  TH1F *h_recHit_95Y = new TH1F("h_recHit_95Y", "h_recHit_95Y; recHit y coordinate; Events", 200, -100, 100); h_recHit_95Y->Sumw2();
  TH1F *h_recHit_95Z = new TH1F("h_recHit_95Z", "h_recHit_95Z; recHit z coordinate; Events",1000, -500, 500); h_recHit_95Z->Sumw2();
  TH1F *h_recHit_95Phi = new TH1F("h_recHit_95Phi", "h_recHit_95Phi; recHit #phi; Events", 80,  -4,   4); h_recHit_95Phi->Sumw2();
  TH1F *h_recHit_95Eta = new TH1F("h_recHit_95Eta", "h_recHit_95Eta; recHit #eta; Events", 120,  -6,  6); h_recHit_95Eta->Sumw2();
  TH1F *h_recHit_Time = new TH1F("h_recHit_Time", "h_recHit_Time; recHit Time [ns]; Events", 20000, -100.0, 100.0); h_recHit_Time->Sumw2();  
  TH2F *h_recHit_TimeVsEnergy = new TH2F("h_recHit_TimeVsEnergy", "h_recHit_TimeVsEnergy; Energy; recHit Time [ns]", 1000, 0, 0.1, 2000, -100.0, 100.0); h_recHit_TimeVsEnergy->Sumw2();
  TH1F *h_recHit_TimeAverage = new TH1F("h_recHit_TimeAverage", "h_recHit_TimeAverage; recHit Time [ns]; Events", 20000, -100.0, 100.0); h_recHit_TimeAverage->Sumw2();
  TH1F *h_Time_AverageWindow1 = new TH1F("h_Time_AverageWindow1", "h_Time_AverageWindow1; recHit Time [ns]; Events", 20000, -100.0, 100.0); h_Time_AverageWindow1->Sumw2();
  TH1F *h_Time_AverageWindow2 = new TH1F("h_Time_AverageWindow2", "h_Time_AverageWindow2; recHit Time [ns]; Events", 20000, -100.0, 100.0); h_Time_AverageWindow2->Sumw2();
  TH1F *h_recHit_95TimeAverage = new TH1F("h_recHit_95TimeAverage", "h_recHit_95TimeAverage; recHit Time [ns]; Events", 20000, -100.0, 100.0); h_recHit_95TimeAverage->Sumw2();
  TH1F *h_recHit_95HighestEnergyTime = new TH1F("h_recHit_95HighestEnergyTime", "h_recHit_95HighestEnergyTime; recHit Time [ns]; Events", 20000, -100.0, 100.0); h_recHit_95HighestEnergyTime->Sumw2();
  TH1F *h_Time_pathDiffWindow = new TH1F("h_Time_pathDiffWindow", "h_Time_pathDiffWindow; recHit Time [ns]; Events", 20000, -100.0, 100.0); h_Time_pathDiffWindow->Sumw2();
  TH1F *h_Time_pathDiffWindowUnweighted = new TH1F("h_Time_pathDiffWindowUnweighted", "h_Time_pathDiffWindowUnweighted; recHit Time [ns]; Events", 20000, -100.0, 100.0); h_Time_pathDiffWindowUnweighted->Sumw2();
  TH1F *h_Time_pathDiffWindow2 = new TH1F("h_Time_pathDiffWindow2", "h_Time_pathDiffWindow2; recHit Time [ns]; Events", 20000, -100.0, 100.0); h_Time_pathDiffWindow2->Sumw2();
  TH1F *h_Time_pathDiffWindowUnweighted2 = new TH1F("h_Time_pathDiffWindowUnweighted2", "h_Time_pathDiffWindowUnweighted2; recHit Time [ns]; Events", 20000, -100.0, 100.0); h_Time_pathDiffWindowUnweighted2->Sumw2();
  TH1F *h_recHit_TimeThreshold = new TH1F("h_recHit_TimeThreshold", "h_recHit_TimeThreshold; recHit Time [ns]; Events", 20000, -100, 100.0); h_recHit_TimeThreshold->Sumw2();
  TH1F *h_recHit_energyOfHitsTime2 = new TH1F("h_recHit_energyOfHitsTime2", "Energy of hits with time > 2 [ns]; recHit Energy; Events", 1000, 0.0, 0.5); h_recHit_energyOfHitsTime2->Sumw2();
  TH1F *h_recHit_energyOfHitsTime1To2 = new TH1F("h_recHit_energyOfHitsTime1To2", "Energy of hits with time > 0 and time < 2 [ns]; recHit Energy; Events", 1000, 0.0, 0.5); h_recHit_energyOfHitsTime1To2->Sumw2();
  TH1F *h_recHit_Time_UnweightedAverage = new TH1F("h_recHit_Time_UnweightedAverage", "RecHit Time Unweighted Average; Time [ns]; Events", 2000, -100.0, 100.0); h_recHit_Time_UnweightedAverage->Sumw2();
  TH2F *h_recHit_TimeVsrecHitZ = new TH2F("h_recHit_TimeVsrecHitZ", "RecHit Time Versus Z; Time [ns]; recHit Z position", 100, 5, 15.0, 150, 300, 450); h_recHit_TimeVsrecHitZ->Sumw2();
  TH2F *h_recHit_RawTimeVsrecHitZ = new TH2F("h_recHit_RawTimeVsrecHitZ", "Raw RecHit Time Versus Z; Raw recHit Time [ns]; recHit Z position", 200, -10.0, 10.0, 150, 300, 450); h_recHit_RawTimeVsrecHitZ->Sumw2();
  TH1F *h_recHit_PathDiff = new TH1F("h_recHit_PathDiff", "Path Difference; Distance [cm]; Events", 150, 300, 450); h_recHit_PathDiff->Sumw2();
  TH2F *h_recHit_TimeVsrecHitE = new TH2F("h_recHit_TimeVsrecHitE", "RecHit Time Versus Energy; Time [ns]; Energy", 100, 5, 15.0, 1000, 0.0, 0.5); h_recHit_TimeVsrecHitE->Sumw2();
  TH2F *h_recHit_RawTimeVsrecHitE = new TH2F("h_recHit_RawTimeVsrecHitE", "Raw RecHit Time Versus Energy; Raw recHit Time [ns]; Energy", 200, -10.0, 10.0, 1000, 0.0, 0.5); h_recHit_RawTimeVsrecHitE->Sumw2();
  TH2F *h_recHitRatioVsE = new TH2F("h_recHitRatioVsE", "Ratio of Energy/Distance Versus Path Difference; Path Difference; Energy/Path Difference", 300, 300.0, 450.0, 5000, 0.0, 0.5); h_recHitRatioVsE->Sumw2(); 
  TH1F *h_recHit_Energy = new TH1F("h_recHit_Energy", "Reconstructed Hit Energy; Energy; Events", 1000, 0.0, 0.5); h_recHit_Energy->Sumw2();
  TH2F *h_hist_fraction = new TH2F("h_hist_fraction", "Reconstructed Hit Energy; Energy; Fraction of hits", 1000, 0.0, 1.0, 1000, 0, 1); h_hist_fraction->Sumw2();
  int nEvents=tree->GetEntries();
  std::cout << "nEvents= " << nEvents << std::endl;
  TF1 *bs_x = new TF1("bs_x", "exp(-0.5*((x-0.243996)/0.00143119)**2)", -0.30, 0.30);
  TF1 *bs_y = new TF1("bs_y", "exp(-0.5*((x-0.392837)/0.00142161)**2)", -0.40, 0.40);
  TF1 *bs_z = new TF1("bs_z", "exp(-0.5*((x-0.381877)/6.0673)**2)", -0.40, 0.40);
  for (int i=0; i<nEvents; ++i)
  {
    tree->GetEvent(i);
    //filling vertex info
    h_vertex_x->Fill(vertex_x);
    h_vertex_y->Fill(vertex_y);
    h_vertex_z->Fill(vertex_z);
    //filling the recHit info in a vector of structs
    std::vector<RecHitInfo> recHits;
    double sumOfHitEnergy = 0.0;
    double sumOfHitEnergyTimes = 0.0;
    double sumOfHitTimes = 0.0;
    double sumOfHitEnergyTimesWindow1 = 0.0;
    double sumOfHitEnergyTimesWindow2 = 0.0;
    double sumOfHitEnergiesWindow1 = 0.0;
    double sumOfHitEnergiesWindow2 = 0.0;
    double vertex_x_gtoy = bs_x->GetRandom();    
    double vertex_y_gtoy = bs_y->GetRandom();
    double vertex_z_gtoy = bs_z->GetRandom();

    for (unsigned int j=0; j<recHit_energy->size(); j++)
    {
      RecHitInfo recHit;
      recHit.recHitE = recHit_energy->at(j);
      recHit.recHitX = recHit_x->at(j);
      recHit.recHitY = recHit_y->at(j);
      recHit.recHitZ = recHit_z->at(j); 
      double speedOfLight = 29.9792458;
      //double d = GenVertex->Z(); 
      //double pathDifference = (sqrt(recHit_x->at(j)*recHit_x->at(j) + recHit_y->at(j)*recHit_y->at(j) + (recHit_z->at(j)+d)*(recHit_z->at(j)+d))); 
      double pathDifference = (sqrt(recHit_x->at(j)*recHit_x->at(j) + recHit_y->at(j)*recHit_y->at(j) + (recHit_z->at(j))*(recHit_z->at(j))));
      recHit.recHitTime = recHit_time->at(j) + (pathDifference/(speedOfLight)) - 1.0;
      if(recHit.recHitE > 0.01) sumOfHitTimes += recHit.recHitTime;
      if(recHit.recHitE > 0.01) sumOfHitEnergyTimes += recHit.recHitE*recHit.recHitTime;
      if(recHit.recHitE > 0.01) sumOfHitEnergy += recHit.recHitE;
      if(recHit.recHitE > 0.01) h_recHit_Energy->Fill(recHit.recHitE);
      h_recHit_Energy->Fill(recHit.recHitE);
      if(recHit.recHitE > 0.01) h_recHit_Time->Fill(recHit.recHitTime, recHit.recHitE);
      if(recHit.recHitE > 0.01) h_recHit_TimeVsEnergy->Fill(recHit.recHitE, recHit.recHitTime);//TH2F
      if(recHit.recHitE > 0.01) h_recHit_PathDiff->Fill(pathDifference);
      if(recHit.recHitTime > 13.0) h_recHit_energyOfHitsTime2->Fill(recHit.recHitE);
      else if(recHit.recHitTime > 9 and recHit.recHitTime <= 13.0)h_recHit_energyOfHitsTime1To2->Fill(recHit.recHitE);
      if(recHit.recHitE> 0.01) h_recHit_TimeVsrecHitZ->Fill(recHit.recHitTime, pathDifference, recHit.recHitE);
      h_recHit_TimeVsrecHitE->Fill(recHit.recHitTime, recHit.recHitE);
      h_recHit_RawTimeVsrecHitZ->Fill(recHit_time->at(j), pathDifference, recHit.recHitE);
      h_recHit_RawTimeVsrecHitE->Fill(recHit_time->at(j), recHit.recHitE);
      h_recHitRatioVsE->Fill(pathDifference, recHit_energy->at(j));
      //if(recHit.recHitE> 0.01) 
      if(pathDifference > 335 and pathDifference < 345) h_Time_pathDiffWindow->Fill(recHit.recHitTime, recHit.recHitE);
      if(pathDifference > 335 and pathDifference < 345) h_Time_pathDiffWindowUnweighted->Fill(recHit.recHitTime); 
      if(pathDifference > 350 and pathDifference < 360) h_Time_pathDiffWindow2->Fill(recHit.recHitTime, recHit.recHitE);
      if(pathDifference > 350 and pathDifference < 360) h_Time_pathDiffWindowUnweighted2->Fill(recHit.recHitTime);
      if(pathDifference > 335 and pathDifference < 345) sumOfHitEnergyTimesWindow1 += recHit.recHitTime*recHit.recHitE;
      else if(pathDifference > 350 and pathDifference < 360) sumOfHitEnergyTimesWindow2 += recHit.recHitTime*recHit.recHitE;
      if(pathDifference > 335 and pathDifference < 345) sumOfHitEnergiesWindow1 += recHit.recHitE;
      else if(pathDifference > 350 and pathDifference < 360) sumOfHitEnergiesWindow2 += recHit.recHitE;
      recHits.push_back(recHit);
    }//end loop over hits
    
    if(sumOfHitTimes > 0.0 and recHits.size() > 0) h_recHit_Time_UnweightedAverage->Fill(sumOfHitTimes/recHits.size());
    if(sumOfHitEnergy > 0.0) h_recHit_TimeAverage->Fill(sumOfHitEnergyTimes/sumOfHitEnergy);

    if(sumOfHitEnergiesWindow1 > 0.0) h_Time_AverageWindow1->Fill(sumOfHitEnergyTimesWindow1/sumOfHitEnergiesWindow1);
    if(sumOfHitEnergiesWindow2 > 0.0) h_Time_AverageWindow2->Fill(sumOfHitEnergyTimesWindow2/sumOfHitEnergiesWindow2);

    std::sort(recHits.begin(), recHits.end(), sortRecHitsInDescendingE);
    TVector3 recHitV;
    recHitV.SetXYZ(-9999.0, -9999.0, -9999.0);
    //erasing last 10% of entries in the vector of recHits
    //int removeElements = 0.95*recHits.size();
    int removeElements = 0;
    //std::cout << "recHits.size() = " << recHits.size() << std::endl;    

  }//end of event loop

  std::string histfilename=(outfile+".root").c_str();
  TFile *tFile=new TFile(histfilename.c_str(), "RECREATE");
  h_vertex_x->Write();
  h_vertex_y->Write();
  h_vertex_z->Write();
  h_recHit_95HighestEnergy->Write();
  h_recHit_95X->Write();
  h_recHit_95Y->Write();
  h_recHit_95Z->Write();
  h_recHit_95Phi->Write();
  h_recHit_95Eta->Write();
  h_recHit_Time->Write();
  h_recHit_TimeVsEnergy->Write();
  h_recHit_TimeAverage->Write();
  h_recHit_95HighestEnergyTime->Write();
  h_recHit_TimeThreshold->Write();
  h_recHit_energyOfHitsTime2->Write();
  h_recHit_energyOfHitsTime1To2->Write();
  h_recHit_Time_UnweightedAverage->Write();
  h_recHit_TimeVsrecHitZ->Write();
  h_recHit_PathDiff->Write();
  h_recHit_TimeVsrecHitE->Write();
  h_recHit_RawTimeVsrecHitZ->Write();
  h_recHit_RawTimeVsrecHitE->Write();
  h_recHit_Energy->Write(); 
  h_recHitRatioVsE->Write();
  h_recHit_95TimeAverage->Write();
  h_Time_pathDiffWindow->Write();
  h_Time_pathDiffWindowUnweighted->Write();
  h_Time_pathDiffWindow2->Write();
  h_Time_pathDiffWindowUnweighted2->Write();
  h_Time_AverageWindow1->Write();
  h_Time_AverageWindow2->Write();
  h_hist_fraction->Write();
  tFile->Close();
  std::cout<<"Wrote output file "<<histfilename<<std::endl;

  return 0; 
}
