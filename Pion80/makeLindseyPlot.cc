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
#include <TVector2.h>
#include <TF1.h>
#include <TMatrixD.h>
#include <TCanvas.h>

void makeLindseyPlot()
{

  TCanvas c1("c1","Pion energy versus hits", 10, 10, 600, 400);
  double photonEnergy[4] = {35, 50, 65, 80};
  double medianHits[4] = {1.06660000000000011e+02, 1.39072000000000003e+02, 1.71574000000000012e+02, 2.07048000000000002e+02};
  double cellSmear[6] = {0.02, 0.05, 0.08, 0.1, 0.15, 2.0};
  double clusterTime_20ps[4] = {0, 0, 0, 0};  
  for(int i=0; i<4; i++)
  {
    clusterTime_20ps[i] = cellSmear[0]/sqrt(medianHits[i]);

  }
  TGraph *gr1 = new TGraph(4, photonEnergy, clusterTime_20ps);
  gr1->SetLineColor(kBlue);
  gr1->SetLineWidth(2);
  gr1->SetMarkerColor(kBlack);
  gr1->SetTitle("");
  gr1->GetXaxis()->SetTitle("Energy of the Single Pion gun [GeV]");
  gr1->GetYaxis()->SetTitle("#sigma_{shower}");
  gr1->SetMaximum(0.02);
  gr1->Draw("AP*L");

  double clusterTime_50ps[4] = {0, 0, 0, 0};

  for(int i=0; i<4; i++)
  {
    clusterTime_50ps[i] = cellSmear[1]/sqrt(medianHits[i]);

  }


  TGraph *gr2 = new TGraph(4, photonEnergy, clusterTime_50ps);
  gr2->SetLineColor(kRed);
  gr2->SetLineWidth(2);
  gr2->SetMarkerColor(kBlack);
  gr2->Draw("P*L same");

  double clusterTime_80ps[4] = {0, 0, 0, 0};

  for(int i=0; i<4; i++)
  {
    clusterTime_80ps[i] = cellSmear[2]/sqrt(medianHits[i]);

  }


  TGraph *gr3 = new TGraph(4, photonEnergy, clusterTime_80ps);
  gr3->SetLineColor(kCyan);
  gr3->SetLineWidth(2);
  gr3->SetMarkerColor(kBlack);
  gr3->Draw("P*L same");

  double clusterTime_100ps[4] = {0, 0, 0, 0};

  for(int i=0; i<4; i++)
  {
    clusterTime_100ps[i] = cellSmear[3]/sqrt(medianHits[i]);

  }

  TGraph *gr4 = new TGraph(4, photonEnergy, clusterTime_100ps);
  gr4->SetLineColor(kGreen);
  gr4->SetLineWidth(2);
  gr4->SetMarkerColor(kBlack);
  gr4->Draw("P*L same");

  double clusterTime_150ps[4] = {0, 0, 0, 0};

  for(int i=0; i<4; i++)
  {
    clusterTime_150ps[i] = cellSmear[4]/sqrt(medianHits[i]);

  }

  TGraph *gr5 = new TGraph(4, photonEnergy, clusterTime_150ps);
  gr5->SetLineColor(kOrange+7);
  gr5->SetLineWidth(2);
  gr5->SetMarkerColor(kBlack);
  gr5->Draw("P*L same");

  double clusterTime_200ps[4] = {0, 0, 0, 0};

  for(int i=0; i<4; i++)
  {
    clusterTime_200ps[i] = cellSmear[5]/sqrt(medianHits[i]);

  }

  TGraph *gr6 = new TGraph(4, photonEnergy, clusterTime_200ps);
  gr6->SetLineColor(kMagenta);
  gr6->SetLineWidth(2);
  gr6->SetMarkerColor(kBlack);
  gr6->Draw("P*L same");

  TLegend *leg = new TLegend(0.62,0.55,0.90,0.90,NULL,"brNDC");
  leg-> SetNColumns(2);
  leg->AddEntry(gr1, "Cell #Delta_{t} 20 ps", "lp");
  leg->AddEntry(gr2, "Cell #Delta_{t} 50 ps", "lp");
  leg->AddEntry(gr3, "Cell #Delta_{t} 80 ps", "lp");
  leg->AddEntry(gr4, "Cell #Delta_{t} 100 ps", "lp");
  leg->AddEntry(gr5, "Cell #Delta_{t} 150 ps", "lp");
  leg->AddEntry(gr6, "Cell #Delta_{t} 200 ps", "lp");
  leg->Draw();

  c1.SaveAs("LindseyPlot_Pions.pdf");
  c1.SaveAs("LindseyPlot_Pions.png");


} 
