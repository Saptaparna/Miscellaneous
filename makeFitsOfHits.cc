#include "TH1.h"
#include "TTree.h"
#include "TKey.h"
#include "Riostream.h"
#include <TCanvas.h>
#include <TLatex.h>
#include "TGraphErrors.h"
#include "TLegend.h"
#include <TPad.h>
#include <sstream>
#include "TVectorD.h"
#include "TChain.h"
#include "TGraph.h"
#include "TFile.h"
#include "TF1.h"

int makeFitsOfHits_Window1_50GeV()
{
  TCanvas c1("c1","Highest Energy recHit", 10, 10, 600, 400);

  TFile* file1 = TFile::Open("ShowerPropagation_HGCTiming_SinglePion_Pt50GeV.root");
  TH1F *h1 = (TH1F*)file1->Get("h_Time_AverageWindow1");
  h1->Rebin(10);
  h1->GetXaxis()->SetRangeUser(9, 14);
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(2);
  TF1 *fa1 = new TF1("fa1", "gaus", 10, 12);
  h1->Fit("fa1");
  h1->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow1_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow1_Pt50GeV.png");

  return 0;
}

int makeFitsOfHits_Window2_50GeV()
{
  TCanvas c1("c1","Highest Energy recHit", 10, 10, 600, 400);
  TFile* file1 = TFile::Open("ShowerPropagation_HGCTiming_SinglePion_Pt50GeV.root");
  TH1F *h1 = (TH1F*)file1->Get("h_Time_AverageWindow2");
  h1->Rebin(10);
  h1->GetXaxis()->SetRangeUser(9, 14);
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(2);
  TF1 *fa1 = new TF1("fa1", "gaus", 10, 12);
  h1->Fit("fa1");
  h1->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow2_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow2_Pt50GeV.png");

  return 0;
}

int makeFitsOfHits_Window1_500GeV()
{
  TCanvas c1("c1","Highest Energy recHit", 10, 10, 600, 400);

  TFile* file1 = TFile::Open("ShowerPropagation_HGCTiming_SinglePion_Pt500GeV.root");
  TH1F *h1 = (TH1F*)file1->Get("h_Time_AverageWindow1");
  h1->Rebin(10);
  h1->GetXaxis()->SetRangeUser(9, 14);
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(2);
  TF1 *fa1 = new TF1("fa1", "gaus", 10, 12);
  h1->Fit("fa1");
  h1->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow1_Pt500GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow1_Pt500GeV.png");

  return 0;
}

int makeFitsOfHits_Window2_500GeV()
{
  TCanvas c1("c1","Highest Energy recHit", 10, 10, 600, 400);
  TFile* file1 = TFile::Open("ShowerPropagation_HGCTiming_SinglePion_Pt500GeV.root");
  TH1F *h1 = (TH1F*)file1->Get("h_Time_AverageWindow2");
  h1->Rebin(10);
  h1->GetXaxis()->SetRangeUser(9, 14);
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(2);
  TF1 *fa1 = new TF1("fa1", "gaus", 10, 12);
  h1->Fit("fa1");
  h1->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow2_Pt500GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow2_Pt500GeV.png");

  return 0;
}

