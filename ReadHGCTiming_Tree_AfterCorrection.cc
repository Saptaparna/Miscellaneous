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

  TH1F *h_TimeAverage_1 = new TH1F("h_TimeAverage_1", "h_TimeAverage_1; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_1->Sumw2();
  TH1F *h_TimeAverage_2 = new TH1F("h_TimeAverage_2", "h_TimeAverage_2; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_2->Sumw2();
  TH1F *h_TimeAverage_3 = new TH1F("h_TimeAverage_3", "h_TimeAverage_3; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_3->Sumw2();
  TH1F *h_TimeAverage_4 = new TH1F("h_TimeAverage_4", "h_TimeAverage_4; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_4->Sumw2();
  TH1F *h_TimeAverage_5 = new TH1F("h_TimeAverage_5", "h_TimeAverage_5; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_5->Sumw2();
  TH1F *h_TimeAverage_6 = new TH1F("h_TimeAverage_6", "h_TimeAverage_6; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_6->Sumw2();
  TH1F *h_TimeAverage_7 = new TH1F("h_TimeAverage_7", "h_TimeAverage_7; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_7->Sumw2();
  TH1F *h_TimeAverage_8 = new TH1F("h_TimeAverage_8", "h_TimeAverage_8; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_8->Sumw2();
  TH1F *h_TimeAverage_9 = new TH1F("h_TimeAverage_9", "h_TimeAverage_9; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_9->Sumw2();
  TH1F *h_TimeAverage_10 = new TH1F("h_TimeAverage_10", "h_TimeAverage_10; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_10->Sumw2();
  TH1F *h_TimeAverage_11 = new TH1F("h_TimeAverage_11", "h_TimeAverage_11; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_11->Sumw2();             
  TH1F *h_TimeAverage_12 = new TH1F("h_TimeAverage_12", "h_TimeAverage_12; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_12->Sumw2();
  TH1F *h_TimeAverage_13 = new TH1F("h_TimeAverage_13", "h_TimeAverage_13; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_13->Sumw2();
  TH1F *h_TimeAverage_14 = new TH1F("h_TimeAverage_14", "h_TimeAverage_14; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_14->Sumw2();
  TH1F *h_TimeAverage_All = new TH1F("h_TimeAverage_All", "h_TimeAverage_All; Average Time [ns]; Events", 200, 0.0, 20.0); h_TimeAverage_All->Sumw2();
  TH1F *h_nHits = new TH1F("h_nHits", "h_nHits; Number of hits; Events", 500, -0.5, -499.5); h_nHits->Sumw2();  

  int nEvents=tree->GetEntries();
  std::cout << "nEvents= " << nEvents << std::endl;
  TF1 *bs_x = new TF1("bs_x", "exp(-0.5*((x-0.243996)/0.00143119)**2)", -0.30, 0.30);
  TF1 *bs_y = new TF1("bs_y", "exp(-0.5*((x-0.392837)/0.00142161)**2)", -0.40, 0.40);
  TF1 *bs_z = new TF1("bs_z", "exp(-0.5*((x-0.381877)/6.0673)**2)", -0.40, 0.40);
  double window[25] = {320, 325, 330, 335, 340, 345, 350, 355, 360, 365, 370, 375, 380, 385, 390, 395, 400, 405, 410, 415, 420, 425, 430, 435, 440};
  Int_t  nWindows = sizeof(window)/sizeof(double) - 1;
  for (int i=0; i<nEvents; ++i)
  {
    tree->GetEvent(i);
    //filling the recHit info in a vector of structs
    std::vector<RecHitInfo> recHits;
    double vertex_x_gtoy = bs_x->GetRandom();    
    double vertex_y_gtoy = bs_y->GetRandom();
    double vertex_z_gtoy = bs_z->GetRandom();
    double sumOfHitEnergyRawTimes = 0.0;
    double sumOfHitEnergy = 0.0;
    double sumOfHitEnergyTimesWindow[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double sumOfHitEnergyWindow[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
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
    if(not (fraction >= 0.30 and fraction <= 0.70)) continue;
    if(not (sumOfHitEnergy80Percent > energyLow and sumOfHitEnergy80Percent <= energyHigh)) continue; 

    h_nHits->Fill(recHits.size());

    for (int j=0; j<hitNumber; j++)
    {
      double speedOfLight = 29.9792458;
      double pathDifference = (sqrt(recHits.at(j).recHitX*recHits.at(j).recHitX + recHits.at(j).recHitY*recHits.at(j).recHitY + recHits.at(j).recHitZ*recHits.at(j).recHitZ));
      if(pathDifference > 320 and pathDifference < 325) 
      {
        double recHitTimeWindow0 = recHits.at(j).recHitTime + (pathDifference/(speedOfLight)) - 1.0; //difference of time between window 1 and window 2
        sumOfHitEnergyTimesWindow[0] += recHitTimeWindow0*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[0] += recHits.at(j).recHitE;
      }
      else if(pathDifference > 325 and pathDifference < 330)
      {  
        double recHitTimeWindow1 = recHits.at(j).recHitTime + ((10.9798-10.8251)/(speedOfLight)) - 1.0 + 10.8251; //difference of time between window 1 and window 2
        sumOfHitEnergyTimesWindow[1] += recHitTimeWindow1*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[1] += recHits.at(j).recHitE;
      }
      else if(pathDifference > 330 and pathDifference < 335)
      {
        double recHitTimeWindow2 = recHits.at(j).recHitTime + ((11.136-10.9798)/(speedOfLight)) - 1.0 + 10.8251; //difference of time between window 2 and window 3
        sumOfHitEnergyTimesWindow[2] += recHitTimeWindow2*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[2] += recHits.at(j).recHitE;
      }
      else if(pathDifference > 335 and pathDifference < 340)
      {
        double recHitTimeWindow3 = recHits.at(j).recHitTime + ((11.2856-11.136)/(speedOfLight)) - 1.0 + 10.8251; //difference of time between window 3 and window 4
        sumOfHitEnergyTimesWindow[3] += recHitTimeWindow3*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[3] += recHits.at(j).recHitE;
      }
      else if(pathDifference > 340 and pathDifference < 345)
      {
        double recHitTimeWindow4 = recHits.at(j).recHitTime + ((11.4432-11.2856)/(speedOfLight)) - 1.0 + 10.8251; //difference of time between window 4 and window 5
        sumOfHitEnergyTimesWindow[4] += recHitTimeWindow4*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[4] += recHits.at(j).recHitE;
      }
      else if(pathDifference > 345 and pathDifference < 350)
      {
        double recHitTimeWindow5 = recHits.at(j).recHitTime + ((11.6065-11.4432)/(speedOfLight)) - 1.0 + 10.8251; //difference of time between window 5 and window 6
        sumOfHitEnergyTimesWindow[5] += recHitTimeWindow5*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[5] += recHits.at(j).recHitE;
      }
      else if(pathDifference > 350 and pathDifference < 355)
      {  
        double recHitTimeWindow6 = recHits.at(j).recHitTime + ((11.7761-11.6065)/(speedOfLight)) - 1.0 + 10.8251; //difference of time between window 6 and window 7
        sumOfHitEnergyTimesWindow[6] += recHitTimeWindow6*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[6] += recHits.at(j).recHitE;
      }
      else if(pathDifference > 355 and pathDifference < 360)
      {
        double recHitTimeWindow7 = recHits.at(j).recHitTime + ((11.9335-11.7761)/(speedOfLight)) - 1.0 + 10.8251; //difference of time between window 7 and window 8
        sumOfHitEnergyTimesWindow[7] += recHitTimeWindow7*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[7] += recHits.at(j).recHitE;
      }
      else if(pathDifference > 360 and pathDifference < 365)
      {
        double recHitTimeWindow8 = recHits.at(j).recHitTime + ((12.098-11.9335)/(speedOfLight)) - 1.0 + 10.8251; //difference of time between window 8 and window 9
        sumOfHitEnergyTimesWindow[8] += recHitTimeWindow8*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[8] += recHits.at(j).recHitE;
      }
      else if(pathDifference > 365 and pathDifference < 370)
      {
        double recHitTimeWindow9 = recHits.at(j).recHitTime + ((12.2761-12.098)/(speedOfLight)) - 1.0 + 10.8251; //difference of time between window 9 and window 10
        sumOfHitEnergyTimesWindow[9] += recHitTimeWindow9*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[9] += recHits.at(j).recHitE;
      }
      else if(pathDifference > 370 and pathDifference < 375)
      {
        double recHitTimeWindow10 = recHits.at(j).recHitTime + ((12.392-12.2761)/(speedOfLight)) - 1.0 + 10.8251; //difference of time between window 10 and window 11
        sumOfHitEnergyTimesWindow[10] += recHitTimeWindow10*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[10] += recHits.at(j).recHitE;
      }
      else if(pathDifference > 375 and pathDifference < 380)
      {
        double recHitTimeWindow11 = recHits.at(j).recHitTime + ((12.5858-12.392)/(speedOfLight)) - 1.0 + 10.8251; //difference of time between window 11 and window 12
        sumOfHitEnergyTimesWindow[11] += recHitTimeWindow11*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[11] += recHits.at(j).recHitE;
      }
      else if(pathDifference > 380 and pathDifference < 385)
      {
        double recHitTimeWindow12 = recHits.at(j).recHitTime + ((13.5699-12.5858)/(speedOfLight)) - 1.0 + 10.8251; //difference of time between window 12 and window 13
        sumOfHitEnergyTimesWindow[12] += recHitTimeWindow12*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[12] += recHits.at(j).recHitE;
      }
      else if(pathDifference > 385 and pathDifference < 440)
      {
        double recHitTimeWindow13 = recHits.at(j).recHitTime + ((13.591-13.5699)/(speedOfLight)) - 1.0 + 10.8251; //difference of time between window 13 and window 14
        sumOfHitEnergyTimesWindow[13] += recHitTimeWindow13*recHits.at(j).recHitE;
        sumOfHitEnergyWindow[13] += recHits.at(j).recHitE;
      }
    }//end loop over hits

    if(sumOfHitEnergyWindow[0] > 0.0) h_TimeAverage_1->Fill(sumOfHitEnergyTimesWindow[0]/sumOfHitEnergyWindow[0]);
    if(sumOfHitEnergyWindow[1] > 0.0) h_TimeAverage_2->Fill(sumOfHitEnergyTimesWindow[1]/sumOfHitEnergyWindow[1]);
    if(sumOfHitEnergyWindow[2] > 0.0) h_TimeAverage_3->Fill(sumOfHitEnergyTimesWindow[2]/sumOfHitEnergyWindow[2]);  
    if(sumOfHitEnergyWindow[3] > 0.0) h_TimeAverage_4->Fill(sumOfHitEnergyTimesWindow[3]/sumOfHitEnergyWindow[3]);
    if(sumOfHitEnergyWindow[4] > 0.0) h_TimeAverage_5->Fill(sumOfHitEnergyTimesWindow[4]/sumOfHitEnergyWindow[4]);
    if(sumOfHitEnergyWindow[5] > 0.0) h_TimeAverage_6->Fill(sumOfHitEnergyTimesWindow[5]/sumOfHitEnergyWindow[5]);
    if(sumOfHitEnergyWindow[6] > 0.0) h_TimeAverage_7->Fill(sumOfHitEnergyTimesWindow[6]/sumOfHitEnergyWindow[6]);
    if(sumOfHitEnergyWindow[7] > 0.0) h_TimeAverage_8->Fill(sumOfHitEnergyTimesWindow[7]/sumOfHitEnergyWindow[7]);
    if(sumOfHitEnergyWindow[8] > 0.0) h_TimeAverage_9->Fill(sumOfHitEnergyTimesWindow[8]/sumOfHitEnergyWindow[8]);
    if(sumOfHitEnergyWindow[9] > 0.0) h_TimeAverage_10->Fill(sumOfHitEnergyTimesWindow[9]/sumOfHitEnergyWindow[9]);
    if(sumOfHitEnergyWindow[10] > 0.0) h_TimeAverage_11->Fill(sumOfHitEnergyTimesWindow[10]/sumOfHitEnergyWindow[10]);
    if(sumOfHitEnergyWindow[11] > 0.0) h_TimeAverage_12->Fill(sumOfHitEnergyTimesWindow[11]/sumOfHitEnergyWindow[11]);
    if(sumOfHitEnergyWindow[12] > 0.0) h_TimeAverage_13->Fill(sumOfHitEnergyTimesWindow[12]/sumOfHitEnergyWindow[12]);
    if(sumOfHitEnergyWindow[13] > 0.0) h_TimeAverage_14->Fill(sumOfHitEnergyTimesWindow[13]/sumOfHitEnergyWindow[13]);
    double sumOfHitEnergyTimesAllWindow = 0.0;
    double sumOfHitEnergyAllWindow = 0.0;

    for(int i=0; i<14; i++)
    {
      sumOfHitEnergyTimesAllWindow += sumOfHitEnergyTimesWindow[i]; 
      sumOfHitEnergyAllWindow += sumOfHitEnergyWindow[i];
    }

    if(sumOfHitEnergyAllWindow > 0.0) h_TimeAverage_All->Fill(sumOfHitEnergyTimesAllWindow/sumOfHitEnergyAllWindow);
 
 
  }//end of event loop
  std::string histfilename=(outfile+".root").c_str();
  TFile *tFile=new TFile(histfilename.c_str(), "RECREATE");
  h_TimeAverage_1->Write();
  h_TimeAverage_2->Write();
  h_TimeAverage_3->Write();
  h_TimeAverage_4->Write();
  h_TimeAverage_5->Write();
  h_TimeAverage_6->Write();
  h_TimeAverage_7->Write();
  h_TimeAverage_8->Write();
  h_TimeAverage_9->Write();
  h_TimeAverage_10->Write();
  h_TimeAverage_11->Write();
  h_TimeAverage_12->Write();
  h_TimeAverage_13->Write();
  h_TimeAverage_14->Write();
  h_TimeAverage_All->Write();
  h_nHits->Write();
  tFile->Close();
  std::cout<<"Wrote output file "<<histfilename<<std::endl;
  return 0; 
}
