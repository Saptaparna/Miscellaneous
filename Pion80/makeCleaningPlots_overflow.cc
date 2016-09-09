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
#include "TGraph.h"
#include "TFile.h"
#include "TCanvas.h"

using std::string;
using std::cout;
using std::endl;
using std::istringstream;

void makeCleaningPlots()
{

  gROOT->SetStyle("Plain");
  TCanvas c1("c1","Cleaning Plot", 10, 10, 600, 400);
  c1.SetLogy();

  TFile* file1 = TFile::Open("output_HGCTiming_SinglePion_Pt80GeV_NoSmearing_directional_All.root");  
  //TFile* file1 = TFile::Open("output_HGCTiming_SinglePion_Pt80GeV_NoSmearing_AfterCleaning.root");
  TH1F *h1 = (TH1F*)file1->Get("h_recHitRho_AfterCut");
  //h1->Rebin(5);
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(2);
  h1->SetStats(kFALSE);
  h1->SetMaximum(50000.0);
  h1->SetMinimum(0.01);
  h1->SetTitle("");
  h1->GetXaxis()->SetRangeUser(0, 10);
  h1->Draw("hist");

  TH1F *h2 = (TH1F*)file1->Get("h_recHitRho_ReverseCut");
  h2->Rebin(10);
  h2->SetLineColor(kRed);
  h2->SetLineWidth(2);
  h2->SetStats(kFALSE);
  h2->GetXaxis()->SetRangeUser(0, 200);
  h2->Draw("hist same");

  TLegend *leg1 = new TLegend(0.5907383,0.6609651,0.8959732,0.8579088,NULL,"brNDC");
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.03);
  leg1->SetLineColor(1);
  leg1->SetLineStyle(0);
  leg1->SetLineWidth(1);
  leg1->SetFillColor(10);
  leg1->SetFillStyle(0);
  leg1->AddEntry(h1,"Time < 0.01","l");
  leg1->AddEntry(h2,"Time > 0.01","l");
  leg1->Draw();

  c1.SaveAs("h_recHitRho_directional.pdf");
  c1.SaveAs("h_recHitRho_directional.png");

}

void makeCleaningPlots_Z()
{

  gROOT->SetStyle("Plain");
  TCanvas c1("c1","Cleaning Plot", 10, 10, 600, 400);
  c1.SetLogy();

  TFile* file1 = TFile::Open("output_HGCTiming_SinglePion_Pt80GeV_NoSmearing_directional_All.root"); 
  //TFile* file1 = TFile::Open("output_HGCTiming_SinglePion_Pt80GeV_NoSmearing_AfterCleaning.root");
  TH1F *h1 = (TH1F*)file1->Get("h_recHitZ_AfterCut");
  h1->Rebin(5);
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(2);
  h1->SetStats(kFALSE);
  h1->SetMaximum(100000.0);
  h1->SetTitle("");
  h1->GetXaxis()->SetRangeUser(300, 400);
  h1->Draw("hist");

  TH1F *h2 = (TH1F*)file1->Get("h_recHitZ_ReverseCut");
  h2->Rebin(5);
  h2->SetLineColor(kRed);
  h2->SetLineWidth(2);
  h2->SetStats(kFALSE);
  h2->GetXaxis()->SetRangeUser(250, 400);
  h2->Draw("hist same");

  TLegend *leg1 = new TLegend(0.5907383,0.6609651,0.8959732,0.8579088,NULL,"brNDC");
  leg1->SetBorderSize(0);
  leg1->SetTextSize(0.03);
  leg1->SetLineColor(1);
  leg1->SetLineStyle(0);
  leg1->SetLineWidth(1);
  leg1->SetFillColor(10);
  leg1->SetFillStyle(0);
  leg1->AddEntry(h1,"Time < 0.01","l");
  leg1->AddEntry(h2,"Time > 0.01","l");
  leg1->Draw();

  c1.SaveAs("h_recHitZ_directional.pdf");
  c1.SaveAs("h_recHitZ_directional.png");

}
