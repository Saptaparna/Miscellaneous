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
  float recHitTimeRaw;
} RecHitInfo;

bool sortRecHitsInDescendingE(RecHitInfo recHit1, RecHitInfo recHit2)
{
  return (recHit1.recHitE > recHit2.recHitE);
}

bool sortRecHitsInAscendingZ(RecHitInfo recHit1, RecHitInfo recHit2)
{
  return (fabs(recHit1.recHitZ) < fabs(recHit2.recHitZ));
}

bool sortRecHitsInAscendingE(RecHitInfo recHit1, RecHitInfo recHit2)
{
  return (recHit1.recHitE < recHit2.recHitE);
}

std::string itoa(int i) 
{
  char res[50];
  sprintf(res, "%d", i);
  std::string ret(res);
  return ret;
}

bool sameVal(double a, double b)
{
   return fabs(a - b) < 3.000e-03;
}


int ReadHGCTiming_Tree_Jun3(std::string infile, std::string outfile, double energyLow, double energyHigh)
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

  TH1F *h_TimeAverage = new TH1F("h_TimeAverage", "h_TimeAverage; Average Time [ns]; Events", 2000, -10.0, 10.0); h_TimeAverage->Sumw2();
  TH1F *h_TimeAverage_EnergyWeighted = new TH1F("h_TimeAverage_EnergyWeighted", "h_TimeAverage_EnergyWeighted; Average Time Energy Weighted [ns]; Events", 2000, -10.0, 10.0); h_TimeAverage_EnergyWeighted->Sumw2();
  TH1F *h_nHits = new TH1F("h_nHits", "h_nHits; Number of hits; Events", 500, -0.5, -499.5); h_nHits->Sumw2(); 
  TH1F *h_TimeAverage_recHitTime = new TH1F("h_TimeAverage_recHitTime", "Time of flight; Average time of flight [ns]; Events", 2000, 0.0, 20.0); h_TimeAverage_recHitTime->Sumw2();
  TH1F *h_TimeAverage_collTime = new TH1F("h_TimeAverage_collTime", "h_TimeAverage_collTime; Average collision time [ns]; Events", 200000,  -10.0, 10.0); h_TimeAverage_collTime->Sumw2();
  TH1F *h_TimeAverage_collTime_energyWeighted = new TH1F("h_TimeAverage_collTime_energyWeighted", "h_TimeAverage_collTime_energyWeighted; Average collision time [ns]; Events", 200000,  -10.0, 10.0); h_TimeAverage_collTime_energyWeighted->Sumw2();
  TH1F *h_collTime_perHit = new TH1F("h_collTime_perHit", "h_collTime_perHit; Time per hit [ns]; Events", 200000, -10.0, 10.0); h_collTime_perHit->Sumw2();
  TH1F *h_TimeAverage_collTime_perHit_AfterCut = new TH1F("h_TimeAverage_collTime_perHit_AfterCut", "h_TimeAverage_collTime_perHit_AfterCut; Time per hit after cut[ns]; Events", 200000,  -10.0, 10.0); h_TimeAverage_collTime_perHit_AfterCut->Sumw2();
  TH2F *h_distance_time = new TH2F("h_distance_time", "h_distance_time; distance; time", 150, 310.0, 460.0, 400, -2.0, 2.0); h_distance_time->Sumw2();
  TH2F *h_distance_energy = new TH2F("h_distance_energy", "h_distance_energy; distance; energy", 150, 310.0, 460.0, 1000, 0.0, 0.1); h_distance_energy->Sumw2();
  TH2F *h_energy_time = new TH2F("h_energy_time", "h_energy_time; energy; time [ns]", 2000, 0.0, 2.0, 2000, 0.0, 10.0); h_energy_time->Sumw2(); 
  TH2F *h_totalEnergy_nHits = new TH2F("h_totalEnergy_nHits", "h_totalEnergy_nHits; Total Energy; nHits", 1000, 0.0, 10.0, 500, -0.5, 499.5); h_totalEnergy_nHits->Sumw2();
  TH1F *h_recHitZ_AfterCut = new TH1F("h_recHitZ_AfterCut", "h_recHitZ_AfterCut; Z coordinate of the recHit [mm]; Entries", 1000, 0.0, 500.0); h_recHitZ_AfterCut->Sumw2();
  TH1F *h_recHitZ_ReverseCut = new TH1F("h_recHitZ_ReverseCut", "h_recHitZ_ReverseCut; Z coordinate of the recHit [mm]; Entries", 1000, 0.0, 500.0); h_recHitZ_ReverseCut->Sumw2();  
  TH1F *h_energy = new TH1F("h_energy", "h_energy; energy; Entries", 1000, 0, 0.5); h_energy->Sumw2(); 
  TH1F *h_recHitRho_AfterCut = new TH1F("h_recHitRho_AfterCut", "h_recHitRho_AfterCut; #rho (#sqrt{x^{2} + y^{2}}) coordinate of the recHit [cm]; Entries", 1000, 0.0, 100.0); h_recHitRho_AfterCut->Sumw2();
  TH1F *h_recHitRho_ReverseCut = new TH1F("h_recHitRho_ReverseCut", "h_recHitRho_ReverseCut; #rho (#sqrt{x^{2} + y^{2}}) coordinate of the recHit [cm]; Entries", 1000, 0.0, 100.0); h_recHitRho_ReverseCut->Sumw2();
  TH1F *h_time_AfterCuts = new TH1F("h_time_AfterCuts", "h_time_AfterCuts; time [ns]; Entries",  200000, -10.0, 10.0); h_time_AfterCuts->Sumw2();
  TGraph *gr_rho_z_AfterTimingCut = new TGraph();
  TGraph *gr_rho_z_ReverseCut = new TGraph();

  int nEvents=tree->GetEntries();
  std::cout << "nEvents= " << nEvents << std::endl;
  TF1 *bs_x = new TF1("bs_x", "exp(-0.5*((x-0.243996)/0.00143119)**2)", -0.30, 0.30);
  TF1 *bs_y = new TF1("bs_y", "exp(-0.5*((x-0.392837)/0.00142161)**2)", -0.40, 0.40);
  TF1 *bs_z = new TF1("bs_z", "exp(-0.5*((x-0.381877)/6.0673)**2)", -16.0, 16.0);
  TRandom *r1 = new TRandom();
  std::vector<double> rho_coordinate_AfterTimingCut;
  std::vector<double> z_coordinate_AfterTimingCut;
  std::vector<double> rho_coordinate_ReverseCut;
  std::vector<double> z_coordinate_ReverseCut;
  int counter_AfterTimingCut=0;
  int counter_ReverseCut=0;

  for (int i=0; i<nEvents; ++i)
  {
    tree->GetEvent(i);
    //filling the recHit info in a vector of structs
    std::vector<RecHitInfo> recHits;
    double sumOfHitEnergyRawTimes = 0.0;
    double sumOfHitEnergy = 0.0;
    double sumOf80HitEnergyTimes = 0.0;
    double sumOf80HitEnergy = 0.0;
    double sumOfHitEnergy80Percent = 0.0;
    double sumOfEnergy = 0.0;
    int hitNumber = 0.0;

    for (unsigned int k=0; k<recHit_energy->size(); k++)
    {
      RecHitInfo recHit;
      recHit.recHitE = recHit_energy->at(k);
      sumOfEnergy += recHit_energy->at(k);
      recHit.recHitX = recHit_x->at(k);
      recHit.recHitY = recHit_y->at(k);
      recHit.recHitZ = recHit_z->at(k);
      recHit.recHitTime = recHit_time->at(k);
      recHits.push_back(recHit);
    }
    std::sort(recHits.begin(), recHits.end(), sortRecHitsInDescendingE);

    for (unsigned int l=0; l<recHits.size(); l++)
    {  
      sumOf80HitEnergyTimes += recHits.at(l).recHitE*recHits.at(l).recHitTime;
      sumOf80HitEnergy += recHits.at(l).recHitE;
      double criterion = 0.80*sumOfEnergy;
      if(sameVal(criterion, sumOf80HitEnergy))
      {
        sumOfHitEnergy80Percent = sumOf80HitEnergy;
        hitNumber = l;
      }
    }//end loop over hits

    double fraction = ((double)hitNumber/(double)recHits.size());
    if(not (fraction >= 0.50 and fraction <= 0.90)) continue;
    //if(not (fraction >= 0.30 and fraction <= 0.50)) continue;
    if(not (sumOfHitEnergy80Percent > energyLow and sumOfHitEnergy80Percent <= energyHigh)) continue; 
    h_nHits->Fill(recHits.size());
    double sumOfHitEnergyTimesAllWindow = 0.0;
    double sumOfHitEnergyAllWindow = 0.0;
    double speedOfLight = 29.9792458;
    double sumOfHitEnergyTimesAllWindowCollTime = 0.0;
    double sumOfCollTime = 0.0;
    double sumOfCollTimeAfterCut = 0.0;
    double average_energyWeighted = 0.0;

    for (int j=0; j<hitNumber; j++)
    {
      recHits.at(j).recHitTime = recHits.at(j).recHitTime - 1;
      if(recHits.at(j).recHitTime < 0) continue;
      double distance = sqrt(pow(recHits.at(j).recHitX, 2) + pow(recHits.at(j).recHitY, 2) + pow(recHits.at(j).recHitZ, 2));
      h_distance_energy->Fill(distance, recHits.at(j).recHitE);
      h_distance_time->Fill(distance, recHits.at(j).recHitTime);
      sumOfHitEnergyTimesAllWindow += recHits.at(j).recHitTime*recHits.at(j).recHitE;
      if(recHits.at(j).recHitTime < 0.01) sumOfHitEnergyAllWindow += recHits.at(j).recHitE;
      if(recHits.at(j).recHitTime < 0.01) sumOfCollTime += recHits.at(j).recHitTime + gRandom->Gaus(0, 0.05);
      if(recHits.at(j).recHitTime < 0.01) sumOfHitEnergyTimesAllWindowCollTime = sumOfCollTime*recHits.at(j).recHitE;
      h_collTime_perHit->Fill(recHits.at(j).recHitTime); 
      h_energy_time->Fill(recHits.at(j).recHitE, recHits.at(j).recHitTime);
      h_energy->Fill(recHits.at(j).recHitE);
      if(recHits.at(j).recHitTime < 0.01) sumOfCollTimeAfterCut += recHits.at(j).recHitTime + gRandom->Gaus(0, 0.05);
      if(recHits.at(j).recHitTime < 0.01) h_recHitZ_AfterCut->Fill(fabs(recHits.at(j).recHitZ));
      if(recHits.at(j).recHitTime > 0.01) h_recHitZ_ReverseCut->Fill(fabs(recHits.at(j).recHitZ));
      if(recHits.at(j).recHitTime < 0.01) h_recHitRho_AfterCut->Fill(sqrt((recHits.at(j).recHitX-34.0)*(recHits.at(j).recHitX-34.0) + recHits.at(j).recHitY*recHits.at(j).recHitY));
      if(recHits.at(j).recHitTime > 0.01) h_recHitRho_ReverseCut->Fill(sqrt((recHits.at(j).recHitX-34.0)*(recHits.at(j).recHitX-34.0) + recHits.at(j).recHitY*recHits.at(j).recHitY));
      if(recHits.at(j).recHitTime < 0.01) rho_coordinate_AfterTimingCut.push_back(sqrt((recHits.at(j).recHitX-34.0)*(recHits.at(j).recHitX-34.0) + recHits.at(j).recHitY*recHits.at(j).recHitY));
      if(recHits.at(j).recHitTime < 0.01) z_coordinate_AfterTimingCut.push_back(fabs(recHits.at(j).recHitZ));  
   
      if(recHits.at(j).recHitTime > 0.01) rho_coordinate_ReverseCut.push_back(sqrt((recHits.at(j).recHitX-34.0)*(recHits.at(j).recHitX-34.0) + recHits.at(j).recHitY*recHits.at(j).recHitY));
      if(recHits.at(j).recHitTime > 0.01) z_coordinate_ReverseCut.push_back(fabs(recHits.at(j).recHitZ));     
      if(recHits.at(j).recHitTime > 0.01) counter_ReverseCut++;
      if(recHits.at(j).recHitTime < 0.01) counter_AfterTimingCut++; 
      double rho = sqrt((recHits.at(j).recHitX-34.0)*(recHits.at(j).recHitX-34.0) + recHits.at(j).recHitY*recHits.at(j).recHitY);     
      if(recHits.at(j).recHitE > 3e-3 and rho < 5.0 and recHits.at(j).recHitZ < 350.0) h_time_AfterCuts->Fill(recHits.at(j).recHitTime);   

    }//end loop over hits

    if(sumOfHitEnergyAllWindow > 0.0) h_TimeAverage_EnergyWeighted->Fill(sumOfHitEnergyTimesAllWindow/sumOfHitEnergyAllWindow);
    if(hitNumber > 0.0) h_TimeAverage_collTime->Fill(sumOfCollTime/hitNumber);
    h_totalEnergy_nHits->Fill(sumOfHitEnergyAllWindow, hitNumber);
    if(hitNumber > 0.0) h_TimeAverage_collTime_perHit_AfterCut->Fill(sumOfCollTimeAfterCut/hitNumber);
    if(sumOfHitEnergyAllWindow > 0.0) h_TimeAverage_collTime_energyWeighted->Fill((double)sumOfHitEnergyTimesAllWindowCollTime/(double)sumOfHitEnergyAllWindow); 

  }//end of event loop
  gr_rho_z_AfterTimingCut = new TGraph(counter_AfterTimingCut, &(rho_coordinate_AfterTimingCut[0]), &(z_coordinate_AfterTimingCut[0]));
  gr_rho_z_ReverseCut = new TGraph(counter_ReverseCut, &(rho_coordinate_ReverseCut[0]), &(z_coordinate_ReverseCut[0]));
  
  std::string histfilename=(outfile+".root").c_str();
  TFile *tFile=new TFile(histfilename.c_str(), "RECREATE");
  h_time_AfterCuts->Write();
  h_energy->Write();
  h_TimeAverage_EnergyWeighted->Write();
  h_TimeAverage_recHitTime->Write();
  h_nHits->Write();
  h_TimeAverage_collTime->Write();
  h_collTime_perHit->Write();
  h_distance_time->Write();
  h_distance_energy->Write();
  h_TimeAverage_collTime_perHit_AfterCut->Write();
  h_totalEnergy_nHits->Write();
  h_TimeAverage_collTime_energyWeighted->Write();
  h_energy_time->Write();
  h_recHitZ_AfterCut->Write();
  h_recHitZ_ReverseCut->Write();
  h_recHitRho_AfterCut->Write();
  h_recHitRho_ReverseCut->Write();
  gr_rho_z_AfterTimingCut->Write("gr_rho_z_AfterTimingCut");
  gr_rho_z_ReverseCut->Write("gr_rho_z_ReverseCut");
  tFile->Close();
  std::cout<<"Wrote output file "<<histfilename<<std::endl;
  return 0; 
}

int startOfShower(std::string infile, std::string outfile, double energyLow, double energyHigh)
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
   int nEvents=tree->GetEntries();
 
   TH1F *h_recHitZ = new TH1F("h_recHitZ", "h_recHitZ; recHit Z [cm]; Events", 10000, 300.0, 400.0);
   TH1F *h_recHitX = new TH1F("h_recHitX", "h_recHitX; recHit X [cm]; Events", 20000, 0.0, 500.0);
   TH1F *h_recHitY = new TH1F("h_recHitY", "h_recHitY; recHit Y [cm]; Events", 20000, 0.0, 500.0); 

   for (int i=9; i<10; ++i)
   {
     tree->GetEvent(i);
     //filling the recHit info in a vector of structs
     std::vector<RecHitInfo> recHits;
     double sumOfEnergy = 0.0;
     double sumOfHitEnergyRawTimes = 0.0;
     double sumOfHitEnergy = 0.0;
     double sumOf80HitEnergyTimes = 0.0;
     double sumOf80HitEnergy = 0.0;
     double sumOfHitEnergy80Percent = 0.0;
     int hitNumber = 0.0;

     for (unsigned int k=0; k<recHit_energy->size(); k++)
     {
       RecHitInfo recHit;
       recHit.recHitE = recHit_energy->at(k);
       sumOfEnergy += recHit_energy->at(k);
       recHit.recHitX = recHit_x->at(k);
       recHit.recHitY = recHit_y->at(k);
       recHit.recHitZ = recHit_z->at(k);
       recHit.recHitTime = recHit_time->at(k);
       recHits.push_back(recHit);
     }//end loop over hits
       
     std::sort(recHits.begin(), recHits.end(), sortRecHitsInDescendingE);
       
     for (unsigned int l=0; l<recHits.size(); l++)
     {
       sumOf80HitEnergyTimes += recHits.at(l).recHitE*recHits.at(l).recHitTime;
       sumOf80HitEnergy += recHits.at(l).recHitE;
       double criterion = 0.80*sumOfEnergy;
       if(sameVal(criterion, sumOf80HitEnergy))
       {
         sumOfHitEnergy80Percent = sumOf80HitEnergy;
         hitNumber = l;
       }
     }//end loop over hits
       
     double fraction = ((double)hitNumber/(double)recHits.size());
     if(not (fraction >= 0.30 and fraction <= 0.50)) continue;
     if(not (sumOfHitEnergy80Percent > energyLow and sumOfHitEnergy80Percent <= energyHigh)) continue;
      
     std::vector<RecHitInfo> recHitsReduced;
       
     for (int j=0; j<=hitNumber; j++)
     {
       recHits.at(j).recHitTime = recHits.at(j).recHitTime - 1;
       if(recHits.at(j).recHitTime < 0) continue;
       RecHitInfo recHitReduced;
       recHitReduced.recHitZ = recHits.at(j).recHitZ;
       recHitReduced.recHitX = recHits.at(j).recHitX;
       recHitReduced.recHitY = recHits.at(j).recHitY;
       recHitReduced.recHitTime = recHits.at(j).recHitTime;
       recHitReduced.recHitE = recHits.at(j).recHitE;
       recHitsReduced.push_back(recHitReduced);
     }//reduced recHit collection
       
     std::sort(recHitsReduced.begin(), recHitsReduced.end(), sortRecHitsInAscendingZ);
     if(recHitsReduced.size() > 0.0) h_recHitZ->Fill(fabs(recHitsReduced.at(0).recHitZ));
     if(recHitsReduced.size() > 0.0) h_recHitX->Fill(fabs(recHitsReduced.at(0).recHitX));
     if(recHitsReduced.size() > 0.0) h_recHitY->Fill(fabs(recHitsReduced.at(0).recHitY));
   }//end loop over events
    
  std::string histfilename=(outfile+".root").c_str();
  TFile *tFile=new TFile(histfilename.c_str(), "RECREATE");
  h_recHitZ->Write();
  h_recHitX->Write();
  h_recHitY->Write();  
  tFile->Close();
  return 0;   
}
