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

int makeFitsOfHits_50GeV(std::string infile)
{
  TCanvas c1("c1","Highest Energy recHit", 10, 10, 600, 400);
  TFile* file1 = TFile::Open((infile+".root").c_str());
  TH1F *h1 = (TH1F*)file1->Get("h_TimeAverage_1");
  h1->GetXaxis()->SetRangeUser(9, 14);
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(2);
  TF1 *fa1 = new TF1("fa1", "gaus", 10, 12);
  h1->Fit("fa1");
  h1->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow1_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow1_Pt50GeV.png");

  TH1F *h2 = (TH1F*)file1->Get("h_TimeAverage_2");
  h2->GetXaxis()->SetRangeUser(9, 14);
  h2->SetLineColor(kBlack);
  h2->SetLineWidth(2);
  h2->Fit("fa1");
  h2->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow2_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow2_Pt50GeV.png");

  TH1F *h3 = (TH1F*)file1->Get("h_TimeAverage_3");
  h3->GetXaxis()->SetRangeUser(9, 14);
  h3->SetLineColor(kBlack);
  h3->SetLineWidth(2);
  h3->Fit("fa1");
  h3->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow3_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow3_Pt50GeV.png");

  TH1F *h4 = (TH1F*)file1->Get("h_TimeAverage_4");
  h4->GetXaxis()->SetRangeUser(9, 14);
  h4->SetLineColor(kBlack);
  h4->SetLineWidth(2);
  h4->Fit("fa1");
  h4->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow4_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow4_Pt50GeV.png");

  TH1F *h5 = (TH1F*)file1->Get("h_TimeAverage_5");
  h5->GetXaxis()->SetRangeUser(9, 14);
  h5->SetLineColor(kBlack);
  h5->SetLineWidth(2);
  h5->Fit("fa1");
  h5->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow5_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow5_Pt50GeV.png");

  TH1F *h6 = (TH1F*)file1->Get("h_TimeAverage_6");
  h6->GetXaxis()->SetRangeUser(9, 14);
  h6->SetLineColor(kBlack);
  h6->SetLineWidth(2);
  h6->Fit("fa1");
  h6->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow6_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow6_Pt50GeV.png");

  TH1F *h7 = (TH1F*)file1->Get("h_TimeAverage_7");
  h7->GetXaxis()->SetRangeUser(9, 14);
  h7->SetLineColor(kBlack);
  h7->SetLineWidth(2);
  h7->Fit("fa1");
  h7->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow7_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow7_Pt50GeV.png");

  TH1F *h8 = (TH1F*)file1->Get("h_TimeAverage_8");
  h8->GetXaxis()->SetRangeUser(9, 14);
  h8->SetLineColor(kBlack);
  h8->SetLineWidth(2);
  h8->Fit("fa1");
  h8->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow8_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow8_Pt50GeV.png");

  TH1F *h9 = (TH1F*)file1->Get("h_TimeAverage_9");
  h9->GetXaxis()->SetRangeUser(9, 14);
  h9->SetLineColor(kBlack);
  h9->SetLineWidth(2);
  h9->Fit("fa1");
  h9->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow9_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow9_Pt50GeV.png");

  TH1F *h10 = (TH1F*)file1->Get("h_TimeAverage_10");
  h10->GetXaxis()->SetRangeUser(9, 14);
  h10->SetLineColor(kBlack);
  h10->SetLineWidth(2);
  h10->Fit("fa1");
  h10->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow10_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow10_Pt50GeV.png");

  TH1F *h11 = (TH1F*)file1->Get("h_TimeAverage_11");
  h11->GetXaxis()->SetRangeUser(9, 14);
  h11->SetLineColor(kBlack);
  h11->SetLineWidth(2);
  h11->Fit("fa1");
  h11->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow11_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow11_Pt50GeV.png");

  TH1F *h12 = (TH1F*)file1->Get("h_TimeAverage_12");
  h12->GetXaxis()->SetRangeUser(9, 14);
  h12->SetLineColor(kBlack);
  h12->SetLineWidth(2);
  h12->Fit("fa1");
  h12->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow12_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow12_Pt50GeV.png");

  TH1F *h13 = (TH1F*)file1->Get("h_TimeAverage_13");
  h13->GetXaxis()->SetRangeUser(9, 14);
  h13->SetLineColor(kBlack);
  h13->SetLineWidth(2);
  h13->Fit("fa1");
  h13->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow13_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow13_Pt50GeV.png");

  TH1F *h14 = (TH1F*)file1->Get("h_TimeAverage_14");
  h14->Rebin(5);
  h12->SetMaximum(30);
  h14->SetLineColor(kBlack);
  h14->SetLineWidth(2);
  h14->GetXaxis()->SetRangeUser(10, 18);
  TF1 *fa2 = new TF1("fa2", "gaus", 12, 15); 
  fa2->SetParLimits(0, 18, 20);
  h14->Fit("fa2");
  h14->Draw();
  fa2->Draw("same");

  c1.SaveAs("h_Time_AverageWindow14_Pt50GeV.pdf");
  c1.SaveAs("h_Time_AverageWindow14_Pt50GeV.png");

  return 0;

}

int makeFitsOfHits_500GeV(std::string infile)
{
    TCanvas c1("c1","Highest Energy recHit", 10, 10, 600, 400);
    TFile* file1 = TFile::Open((infile+".root").c_str());
    TH1F *h1 = (TH1F*)file1->Get("h_TimeAverage_1");
    h1->GetXaxis()->SetRangeUser(9, 14);
    h1->SetLineColor(kBlack);
    h1->SetLineWidth(2);
    TF1 *fa1 = new TF1("fa1", "gaus", 10, 12);
    h1->Fit("fa1");
    h1->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow1_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow1_Pt500GeV.png");
    
    TH1F *h2 = (TH1F*)file1->Get("h_TimeAverage_2");
    h2->GetXaxis()->SetRangeUser(9, 14);
    h2->SetLineColor(kBlack);
    h2->SetLineWidth(2);
    h2->Fit("fa1");
    h2->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow2_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow2_Pt500GeV.png");
    
    TH1F *h3 = (TH1F*)file1->Get("h_TimeAverage_3");
    h3->GetXaxis()->SetRangeUser(9, 14);
    h3->SetLineColor(kBlack);
    h3->SetLineWidth(2);
    h3->Fit("fa1");
    h3->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow3_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow3_Pt500GeV.png");
    
    TH1F *h4 = (TH1F*)file1->Get("h_TimeAverage_4");
    h4->GetXaxis()->SetRangeUser(9, 14);
    h4->SetLineColor(kBlack);
    h4->SetLineWidth(2);
    h4->Fit("fa1");
    h4->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow4_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow4_Pt500GeV.png");
    
    TH1F *h5 = (TH1F*)file1->Get("h_TimeAverage_5");
    h5->GetXaxis()->SetRangeUser(9, 14);
    h5->SetLineColor(kBlack);
    h5->SetLineWidth(2);
    h5->Fit("fa1");
    h5->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow5_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow5_Pt500GeV.png");
    
    TH1F *h6 = (TH1F*)file1->Get("h_TimeAverage_6");
    h6->GetXaxis()->SetRangeUser(9, 14);
    h6->SetLineColor(kBlack);
    h6->SetLineWidth(2);
    h6->Fit("fa1");
    h6->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow6_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow6_Pt500GeV.png");
    
    TH1F *h7 = (TH1F*)file1->Get("h_TimeAverage_7");
    h7->GetXaxis()->SetRangeUser(9, 14);
    h7->SetLineColor(kBlack);
    h7->SetLineWidth(2);
    h7->Fit("fa1");
    h7->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow7_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow7_Pt500GeV.png");
    
    TH1F *h8 = (TH1F*)file1->Get("h_TimeAverage_8");
    h8->GetXaxis()->SetRangeUser(9, 14);
    h8->SetLineColor(kBlack);
    h8->SetLineWidth(2);
    h8->Fit("fa1");
    h8->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow8_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow8_Pt500GeV.png");
    
    TH1F *h9 = (TH1F*)file1->Get("h_TimeAverage_9");
    h9->GetXaxis()->SetRangeUser(9, 14);
    h9->SetLineColor(kBlack);
    h9->SetLineWidth(2);
    h9->Fit("fa1");
    h9->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow9_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow9_Pt500GeV.png");
    
    TH1F *h10 = (TH1F*)file1->Get("h_TimeAverage_10");
    h10->GetXaxis()->SetRangeUser(9, 14);
    h10->SetLineColor(kBlack);
    h10->SetLineWidth(2);
    h10->Fit("fa1");
    h10->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow10_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow10_Pt500GeV.png");
    
    TH1F *h11 = (TH1F*)file1->Get("h_TimeAverage_11");
    h11->GetXaxis()->SetRangeUser(9, 14);
    h11->SetLineColor(kBlack);
    h11->SetLineWidth(2);
    h11->Fit("fa1");
    h11->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow11_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow11_Pt500GeV.png");
    
    TH1F *h12 = (TH1F*)file1->Get("h_TimeAverage_12");
    h12->GetXaxis()->SetRangeUser(9, 14);
    h12->SetLineColor(kBlack);
    h12->SetLineWidth(2);
    h12->Fit("fa1");
    h12->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow12_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow12_Pt500GeV.png");
    
    TH1F *h13 = (TH1F*)file1->Get("h_TimeAverage_13");
    h13->GetXaxis()->SetRangeUser(9, 14);
    h13->SetLineColor(kBlack);
    h13->SetLineWidth(2);
    h13->Fit("fa1");
    h13->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow13_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow13_Pt500GeV.png");
    
    TH1F *h14 = (TH1F*)file1->Get("h_TimeAverage_14");
    h14->Rebin(5);
    h12->SetMaximum(30);
    h14->SetLineColor(kBlack);
    h14->SetLineWidth(2);
    h14->GetXaxis()->SetRangeUser(10, 18);
    TF1 *fa2 = new TF1("fa2", "gaus", 12, 15); 
    fa2->SetParLimits(0, 35, 40);
    h14->Fit("fa2");
    h14->Draw();
    fa2->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow14_Pt500GeV.pdf");
    c1.SaveAs("h_Time_AverageWindow14_Pt500GeV.png");
    
    return 0;
    
}

