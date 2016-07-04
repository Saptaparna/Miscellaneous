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
   return fabs(a - b) < 1.000e-06;
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

  TH1F *h_TimeAverage_1 = new TH1F("h_TimeAverage_1", "h_TimeAverage_1; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_2 = new TH1F("h_TimeAverage_2", "h_TimeAverage_2; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_3 = new TH1F("h_TimeAverage_3", "h_TimeAverage_3; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_4 = new TH1F("h_TimeAverage_4", "h_TimeAverage_4; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_5 = new TH1F("h_TimeAverage_5", "h_TimeAverage_5; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_6 = new TH1F("h_TimeAverage_6", "h_TimeAverage_6; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_7 = new TH1F("h_TimeAverage_7", "h_TimeAverage_7; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_8 = new TH1F("h_TimeAverage_8", "h_TimeAverage_8; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_9 = new TH1F("h_TimeAverage_9", "h_TimeAverage_9; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_10 = new TH1F("h_TimeAverage_10", "h_TimeAverage_10; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_11 = new TH1F("h_TimeAverage_11", "h_TimeAverage_11; Average Time [ns]; Events", 200, 0.0, 20.0);              
  TH1F *h_TimeAverage_12 = new TH1F("h_TimeAverage_12", "h_TimeAverage_12; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_13 = new TH1F("h_TimeAverage_13", "h_TimeAverage_13; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_14 = new TH1F("h_TimeAverage_14", "h_TimeAverage_14; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_15 = new TH1F("h_TimeAverage_15", "h_TimeAverage_15; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_16 = new TH1F("h_TimeAverage_16", "h_TimeAverage_16; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_17 = new TH1F("h_TimeAverage_17", "h_TimeAverage_17; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_18 = new TH1F("h_TimeAverage_18", "h_TimeAverage_18; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_19 = new TH1F("h_TimeAverage_19", "h_TimeAverage_19; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_20 = new TH1F("h_TimeAverage_20", "h_TimeAverage_20; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_21 = new TH1F("h_TimeAverage_21", "h_TimeAverage_21; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_22 = new TH1F("h_TimeAverage_22", "h_TimeAverage_22; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_23 = new TH1F("h_TimeAverage_23", "h_TimeAverage_23; Average Time [ns]; Events", 200, 0.0, 20.0);
  TH1F *h_TimeAverage_24 = new TH1F("h_TimeAverage_24", "h_TimeAverage_24; Average Time [ns]; Events", 200, 0.0, 20.0); 

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
    double sumOfHitEnergyTimesWindow[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    double sumOfHitEnergyWindow[24] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; 
    for (unsigned int j=0; j<recHit_energy->size(); j++)
    {
      RecHitInfo recHit;
      recHit.recHitE = recHit_energy->at(j);
      recHit.recHitX = recHit_x->at(j);
      recHit.recHitY = recHit_y->at(j);
      recHit.recHitZ = recHit_z->at(j); 
      double speedOfLight = 29.9792458;
      double pathDifference = (sqrt(recHit_x->at(j)*recHit_x->at(j) + recHit_y->at(j)*recHit_y->at(j) + (recHit_z->at(j))*(recHit_z->at(j))));
      recHit.recHitTime = recHit_time->at(j) + (pathDifference/(speedOfLight)) - 1.0;
      if(pathDifference > 320 and pathDifference < 325) 
      {
        sumOfHitEnergyTimesWindow[0] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[0] += recHit.recHitE;
      }
      else if(pathDifference > 325 and pathDifference < 330)
      {  
        sumOfHitEnergyTimesWindow[1] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[1] += recHit.recHitE;
      }
      else if(pathDifference > 330 and pathDifference < 335)
      {
        sumOfHitEnergyTimesWindow[2] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[2] += recHit.recHitE;
      }
      else if(pathDifference > 335 and pathDifference < 340)
      {
        sumOfHitEnergyTimesWindow[3] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[3] += recHit.recHitE;
      }
      else if(pathDifference > 340 and pathDifference < 345)
      {
        sumOfHitEnergyTimesWindow[4] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[4] += recHit.recHitE;
      }
      else if(pathDifference > 345 and pathDifference < 350)
      {
        sumOfHitEnergyTimesWindow[5] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[5] += recHit.recHitE;
      }
      else if(pathDifference > 350 and pathDifference < 355)
      {  
        sumOfHitEnergyTimesWindow[6] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[6] += recHit.recHitE;
      }
      else if(pathDifference > 355 and pathDifference < 360)
      {
        sumOfHitEnergyTimesWindow[7] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[7] += recHit.recHitE;
      }
      else if(pathDifference > 360 and pathDifference < 365)
      {
        sumOfHitEnergyTimesWindow[8] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[8] += recHit.recHitE;
      }
      else if(pathDifference > 365 and pathDifference < 370)
      {
        sumOfHitEnergyTimesWindow[9] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[9] += recHit.recHitE;
      }
      else if(pathDifference > 370 and pathDifference < 375)
      {
        sumOfHitEnergyTimesWindow[10] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[10] += recHit.recHitE;
      }
      else if(pathDifference > 375 and pathDifference < 380)
      {
        sumOfHitEnergyTimesWindow[11] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[11] += recHit.recHitE;
      }
      else if(pathDifference > 380 and pathDifference < 385)
      {
        sumOfHitEnergyTimesWindow[12] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[12] += recHit.recHitE;
      }
      else if(pathDifference > 385 and pathDifference < 390)
      {
        sumOfHitEnergyTimesWindow[13] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[13] += recHit.recHitE;
      }
      else if(pathDifference > 390 and pathDifference < 395)
      {
        sumOfHitEnergyTimesWindow[14] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[14] += recHit.recHitE;
      }
      else if(pathDifference > 395 and pathDifference < 400)
      {
        sumOfHitEnergyTimesWindow[15] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[15] += recHit.recHitE;
      }
      else if(pathDifference > 400 and pathDifference < 405)
      {
        sumOfHitEnergyTimesWindow[16] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[16] += recHit.recHitE;
      }
      else if(pathDifference > 405 and pathDifference < 410)
      {
        sumOfHitEnergyTimesWindow[17] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[17] += recHit.recHitE;
      }
      else if(pathDifference > 410 and pathDifference < 415)
      {
        sumOfHitEnergyTimesWindow[18] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[18] += recHit.recHitE;
      }
      else if(pathDifference > 415 and pathDifference < 420)
      {
        sumOfHitEnergyTimesWindow[19] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[19] += recHit.recHitE;
      }
      else if(pathDifference > 420 and pathDifference < 425)
      {
        sumOfHitEnergyTimesWindow[20] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[20] += recHit.recHitE;
      }
      else if(pathDifference > 425 and pathDifference < 430)
      {
        sumOfHitEnergyTimesWindow[21] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[21] += recHit.recHitE;
      }
      else if(pathDifference > 430 and pathDifference < 435)
      {
        sumOfHitEnergyTimesWindow[22] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[22] += recHit.recHitE;
      }
      else if(pathDifference > 435 and pathDifference < 440)
      {
        sumOfHitEnergyTimesWindow[23] += recHit.recHitTime*recHit.recHitE;
        sumOfHitEnergyWindow[23] += recHit.recHitE;
      }
      recHits.push_back(recHit);
    }//end loop over hits

/*    std::sort(recHits.begin(), recHits.end(), sortRecHitsInDescendingE);  
 
*/

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
    if(sumOfHitEnergyWindow[14] > 0.0) h_TimeAverage_15->Fill(sumOfHitEnergyTimesWindow[14]/sumOfHitEnergyWindow[14]);
    if(sumOfHitEnergyWindow[15] > 0.0) h_TimeAverage_16->Fill(sumOfHitEnergyTimesWindow[15]/sumOfHitEnergyWindow[15]);
    if(sumOfHitEnergyWindow[16] > 0.0) h_TimeAverage_17->Fill(sumOfHitEnergyTimesWindow[16]/sumOfHitEnergyWindow[16]);
    if(sumOfHitEnergyWindow[17] > 0.0) h_TimeAverage_18->Fill(sumOfHitEnergyTimesWindow[17]/sumOfHitEnergyWindow[17]);
    if(sumOfHitEnergyWindow[18] > 0.0) h_TimeAverage_19->Fill(sumOfHitEnergyTimesWindow[18]/sumOfHitEnergyWindow[18]);
    if(sumOfHitEnergyWindow[19] > 0.0) h_TimeAverage_20->Fill(sumOfHitEnergyTimesWindow[19]/sumOfHitEnergyWindow[19]);
    if(sumOfHitEnergyWindow[20] > 0.0) h_TimeAverage_21->Fill(sumOfHitEnergyTimesWindow[20]/sumOfHitEnergyWindow[20]);
    if(sumOfHitEnergyWindow[21] > 0.0) h_TimeAverage_22->Fill(sumOfHitEnergyTimesWindow[21]/sumOfHitEnergyWindow[21]);
    if(sumOfHitEnergyWindow[22] > 0.0) h_TimeAverage_23->Fill(sumOfHitEnergyTimesWindow[22]/sumOfHitEnergyWindow[22]);
    if(sumOfHitEnergyWindow[23] > 0.0) h_TimeAverage_24->Fill(sumOfHitEnergyTimesWindow[23]/sumOfHitEnergyWindow[23]);

  
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
  h_TimeAverage_15->Write();
  h_TimeAverage_16->Write();
  h_TimeAverage_17->Write();
  h_TimeAverage_18->Write();
  h_TimeAverage_19->Write();
  h_TimeAverage_20->Write();
  h_TimeAverage_21->Write();
  h_TimeAverage_22->Write();
  h_TimeAverage_23->Write();
  h_TimeAverage_24->Write();
  tFile->Close();
  std::cout<<"Wrote output file "<<histfilename<<std::endl;
  return 0; 
}
