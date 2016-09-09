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

void makeLindseyPlot_obs()
{

  TCanvas c1("c1","Pion energy versus hits", 10, 10, 600, 400);
  c1.SetLogx();
  double photonEnergy[6] = {2, 10, 35, 50, 65, 80};
  double medianHits[6] = {7.47360000000000113e+00, 3.16728000000000023e+01, 1.06660000000000011e+02, 1.39072000000000003e+02, 1.71574000000000012e+02, 2.07048000000000002e+02};
  double cellSmear[6] = {0.02, 0.05, 0.08, 0.1, 0.15, 2.0};
  double clusterTime_50ps[6] = {0, 0, 0, 0, 0, 0};

  for(int i=0; i<6; i++)
  {
    clusterTime_50ps[i] = cellSmear[1]/sqrt(medianHits[i]);

  }

  TGraph *gr2 = new TGraph(6, photonEnergy, clusterTime_50ps);
  gr2->SetLineStyle(1);
  gr2->SetLineColor(kRed);
  gr2->SetLineWidth(2);
  gr2->SetMarkerColor(kBlack);
  gr2->SetTitle("");
  gr2->GetXaxis()->SetTitle("Energy of the Single Pion gun [GeV]");
  gr2->GetYaxis()->SetTitle("#sigma_{shower}");
  gr2->SetMaximum(0.05);
  //gr2->Draw("A P*L");

  double clusterTime_obs[6] = {4.13820e-02, 1.14744e-02, 5.78254e-03, 5.47117e-03, 5.15387e-03, 4.78656e-03};
  //double clusterTime_obs[4] = {0.0070, 0.0067, 0.0063, 0.0059};

  TGraph *gr2obs = new TGraph(6, photonEnergy, clusterTime_obs);
  gr2obs->SetLineStyle(5);
  gr2obs->SetLineColor(kRed);
  gr2obs->SetLineWidth(2);
  gr2obs->SetMarkerColor(kBlack);
  gr2obs->SetTitle("");
  gr2obs->GetXaxis()->SetTitle("Energy of the Single Pion gun [GeV]");
  gr2obs->GetYaxis()->SetTitle("#sigma_{shower}");
  gr2obs->SetMaximum(0.05);
  gr2obs->Draw("A P*L");

  TLegend *leg = new TLegend(0.52,0.65,0.90,0.90,NULL,"brNDC");
  //leg->AddEntry(gr2, "Cell #Delta_{t} 50 ps", "lp");
  leg->AddEntry(gr2obs, "Cell #Delta_{t} 50 ps: obs", "lp");
  leg->Draw();

  c1.SaveAs("LindseyPlot_Pions_Obs.pdf");
  c1.SaveAs("LindseyPlot_Pions_Obs.png");


} 
