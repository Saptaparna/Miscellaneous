#include "TStyle.h"
#include "TMath.h"
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
  double mean[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double mean_error[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  gStyle->SetOptFit(1);
  TCanvas c1("c1","Highest Energy recHit", 10, 10, 600, 400);
  TFile* file1 = TFile::Open((infile+".root").c_str());
  TH1F *h1 = (TH1F*)file1->Get("h_TimeAverage_1");
  h1->GetXaxis()->SetRangeUser(9, 14);
  h1->SetLineColor(kBlack);
  h1->SetLineWidth(2);
  TF1 *fa1 = new TF1("fa1", "gaus", 10, 12);
  h1->Fit("fa1");
  mean[0] = fa1->GetParameter(1);
  mean_error[0] = fa1->GetParameter(2)/TMath::Sqrt(h1->Integral());
  std::cout << "mean[0] = " << mean[0] << std::endl;
  std::cout << "mean_error[0] = " << mean_error[0] << std::endl;
  h1->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow1_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow1_Pt50GeV_PathLengthCorrected.png");

  TH1F *h2 = (TH1F*)file1->Get("h_TimeAverage_2");
  h2->GetXaxis()->SetRangeUser(9, 14);
  h2->SetLineColor(kBlack);
  h2->SetLineWidth(2);
  h2->Fit("fa1");
  mean[1] = fa1->GetParameter(1);
  mean_error[1] = fa1->GetParameter(2)/TMath::Sqrt(h2->Integral());
  std::cout << "mean[1] = " << mean[1] << std::endl;
  std::cout << "mean_error[1] = " << mean_error[1] << std::endl;
  h2->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow2_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow2_Pt50GeV_PathLengthCorrected.png");

  TH1F *h3 = (TH1F*)file1->Get("h_TimeAverage_3");
  h3->GetXaxis()->SetRangeUser(9, 14);
  h3->SetLineColor(kBlack);
  h3->SetLineWidth(2);
  h3->Fit("fa1");
  mean[2] = fa1->GetParameter(1);
  mean_error[2] = fa1->GetParameter(2)/TMath::Sqrt(h3->Integral());
  std::cout << "mean[2] = " << mean[2] << std::endl;
  std::cout << "mean_error[2] = " << mean_error[2] << std::endl;
  h3->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow3_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow3_Pt50GeV_PathLengthCorrected.png");

  TH1F *h4 = (TH1F*)file1->Get("h_TimeAverage_4");
  h4->GetXaxis()->SetRangeUser(9, 14);
  h4->SetLineColor(kBlack);
  h4->SetLineWidth(2);
  h4->Fit("fa1");
  mean[3] = fa1->GetParameter(1);
  mean_error[3] = fa1->GetParameter(2)/TMath::Sqrt(h4->Integral());
  std::cout << "mean[3] = " << mean[3] << std::endl;
  std::cout << "mean_error[3] = " << mean_error[3] << std::endl;
  h4->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow4_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow4_Pt50GeV_PathLengthCorrected.png");

  TH1F *h5 = (TH1F*)file1->Get("h_TimeAverage_5");
  h5->GetXaxis()->SetRangeUser(9, 14);
  h5->SetLineColor(kBlack);
  h5->SetLineWidth(2);
  h5->Fit("fa1");
  mean[4] = fa1->GetParameter(1);
  mean_error[4] = fa1->GetParameter(2)/TMath::Sqrt(h5->Integral());
  std::cout << "mean[4] = " << mean[4] << std::endl;
  std::cout << "mean_error[4] = " << mean_error[4] << std::endl;
  h5->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow5_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow5_Pt50GeV_PathLengthCorrected.png");

  TH1F *h6 = (TH1F*)file1->Get("h_TimeAverage_6");
  h6->GetXaxis()->SetRangeUser(9, 14);
  h6->SetLineColor(kBlack);
  h6->SetLineWidth(2);
  h6->Fit("fa1");
  mean[5] = fa1->GetParameter(1);
  mean_error[5] = fa1->GetParameter(2)/TMath::Sqrt(h6->Integral());
  std::cout << "mean[5] = " << mean[5] << std::endl;
  std::cout << "mean_error[5] = " << mean_error[5] << std::endl;
  h6->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow6_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow6_Pt50GeV_PathLengthCorrected.png");

  TH1F *h7 = (TH1F*)file1->Get("h_TimeAverage_7");
  h7->GetXaxis()->SetRangeUser(9, 14);
  h7->SetLineColor(kBlack);
  h7->SetLineWidth(2);
  fa1->SetParLimits(0, 330, 350);
  h7->Fit("fa1");
  mean[6] = fa1->GetParameter(1);
  mean_error[6] = fa1->GetParameter(2)/TMath::Sqrt(h7->Integral());
  std::cout << "mean[6] = " << mean[6] << std::endl;
  std::cout << "mean_error[6] = " << mean_error[6] << std::endl;
  h7->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow7_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow7_Pt50GeV_PathLengthCorrected.png");

  TH1F *h8 = (TH1F*)file1->Get("h_TimeAverage_8");
  h8->GetXaxis()->SetRangeUser(9, 14);
  h8->SetLineColor(kBlack);
  h8->SetLineWidth(2);
  fa1->SetParLimits(0, 205, 210);
  h8->Fit("fa1");
  mean[7] = fa1->GetParameter(1);
  mean_error[7] = fa1->GetParameter(2)/TMath::Sqrt(h8->Integral());
  std::cout << "mean[7] = " << mean[7] << std::endl;
  std::cout << "mean_error[7] = " << mean_error[7] << std::endl;
  h8->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow8_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow8_Pt50GeV_PathLengthCorrected.png");

  TH1F *h9 = (TH1F*)file1->Get("h_TimeAverage_9");
  h9->GetXaxis()->SetRangeUser(9, 14);
  h9->SetLineColor(kBlack);
  h9->SetLineWidth(2);
  fa1->SetParLimits(0, 130, 135);
  h9->Fit("fa1");
  mean[8] = fa1->GetParameter(1);
  mean_error[8] = fa1->GetParameter(2)/TMath::Sqrt(h9->Integral());
  std::cout << "mean[8] = " << mean[8] << std::endl;
  std::cout << "mean_error[8] = " << mean_error[8] << std::endl;
  h9->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow9_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow9_Pt50GeV_PathLengthCorrected.png");

  TH1F *h10 = (TH1F*)file1->Get("h_TimeAverage_10");
  h10->GetXaxis()->SetRangeUser(9, 14);
  h10->SetLineColor(kBlack);
  h10->SetLineWidth(2);
  fa1->SetParLimits(0, 95, 100);
  h10->Fit("fa1");
  mean[9] = fa1->GetParameter(1);
  mean_error[9] = fa1->GetParameter(2)/TMath::Sqrt(h10->Integral());
  std::cout << "mean[9] = " << mean[9] << std::endl;
  std::cout << "mean_error[9] = " << mean_error[9] << std::endl;
  h10->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow10_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow10_Pt50GeV_PathLengthCorrected.png");

  TH1F *h11 = (TH1F*)file1->Get("h_TimeAverage_11");
  h11->GetXaxis()->SetRangeUser(9, 14);
  h11->SetLineColor(kBlack);
  h11->SetLineWidth(2);
  fa1->SetParLimits(0, 45, 50);
  h11->Fit("fa1");
  mean[10] = fa1->GetParameter(1);
  mean_error[10] = fa1->GetParameter(2)/TMath::Sqrt(h11->Integral());
  std::cout << "mean[10] = " << mean[10] << std::endl;
  std::cout << "mean_error[10] = " << mean_error[10] << std::endl;
  h11->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow11_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow11_Pt50GeV_PathLengthCorrected.png");

  TH1F *h12 = (TH1F*)file1->Get("h_TimeAverage_12");
  h12->GetXaxis()->SetRangeUser(9, 14);
  h12->SetLineColor(kBlack);
  h12->SetLineWidth(2);
  fa1->SetParLimits(0, 20, 22);
  h12->Fit("fa1");
  mean[11] = fa1->GetParameter(1);
  mean_error[11] = fa1->GetParameter(2)/TMath::Sqrt(h12->Integral());
  std::cout << "mean[11] = " << mean[11] << std::endl;
  std::cout << "mean_error[11] = " << mean_error[11] << std::endl;
  h12->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow12_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow12_Pt50GeV_PathLengthCorrected.png");

  TH1F *h13 = (TH1F*)file1->Get("h_TimeAverage_13");
  h13->GetXaxis()->SetRangeUser(9, 14);
  h13->SetLineColor(kBlack);
  h13->SetLineWidth(2);
  TF1 *fa3 = new TF1("fa3", "gaus", 9, 14);
  fa3->SetParLimits(0, 3, 4);
  h13->Fit("fa3");
  mean[12] = fa3->GetParameter(1);
  mean_error[12] = fa3->GetParameter(2)/TMath::Sqrt(h13->Integral());
  std::cout << "mean[12] = " << mean[12] << std::endl;
  std::cout << "mean_error[12] = " << mean_error[12] << std::endl;
  h13->Draw();
  fa3->Draw("same");

  c1.SaveAs("h_Time_AverageWindow13_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow13_Pt50GeV_PathLengthCorrected.png");

  TH1F *h14 = (TH1F*)file1->Get("h_TimeAverage_14");
  h14->Rebin(5);
  h14->SetLineColor(kBlack);
  h14->SetLineWidth(2);
  h14->GetXaxis()->SetRangeUser(9, 14);
  TF1 *fa2 = new TF1("fa2", "gaus", 12, 15); 
  fa2->SetParLimits(0, 18, 20);
  h14->Fit("fa2");
  mean[13] = fa2->GetParameter(1);
  mean_error[13] = fa2->GetParameter(2)/TMath::Sqrt(h14->Integral());
  std::cout << "mean[13] = " << mean[13] << std::endl;
  std::cout << "mean_error[13] = " << mean_error[13] << std::endl;
  h14->Draw();
  fa2->Draw("same");

  c1.SaveAs("h_Time_AverageWindow14_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow14_Pt50GeV_PathLengthCorrected.png");
  double x[14] = {320, 325, 330, 335, 340, 345, 350, 355, 360, 365, 370, 375, 380, 385};
  double x_error[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  for(int i=0; i<14; i++)  
  {
    std::cout << "mean[i] = " << mean[i] << std::endl;
    std::cout << "mean_error[i] = " << mean_error[i] << std::endl;
  }
  TGraphErrors *gr = new TGraphErrors(14, x, mean, x_error, mean_error);
  gr->SetLineColor(kBlue);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(kBlack);
  gr->SetTitle("Time of flight as the particle moves through the detector");
  gr->GetXaxis()->SetTitle("Distance [cm]");
  gr->GetYaxis()->SetTitle("Time [ns]");
  gr->Draw("AP*");
  
  c1.SaveAs("h_Time_Average_All_Pt50GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_Average_All_Pt50GeV_PathLengthCorrected.png");
  return 0;

}

int makeFitsOfHits_500GeV(std::string infile)
{

    double mean[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    double mean_error[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    gStyle->SetOptFit(1);
    TCanvas c1("c1","Highest Energy recHit", 10, 10, 600, 400);
    TFile* file1 = TFile::Open((infile+".root").c_str());
    TH1F *h1 = (TH1F*)file1->Get("h_TimeAverage_1");
    h1->GetXaxis()->SetRangeUser(9, 14);
    h1->SetLineColor(kBlack);
    h1->SetLineWidth(2);
    TF1 *fa1 = new TF1("fa1", "gaus", 10, 12);
    h1->Fit("fa1");
    mean[0] = fa1->GetParameter(1);
    mean_error[0] = fa1->GetParameter(2)/TMath::Sqrt(h1->Integral());
    std::cout << "mean[0] = " << mean[0] << std::endl;
    std::cout << "mean_error[0] = " << mean_error[0] << std::endl;
    h1->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow1_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow1_Pt500GeV_PathLengthCorrected.png");
    
    TH1F *h2 = (TH1F*)file1->Get("h_TimeAverage_2");
    h2->GetXaxis()->SetRangeUser(9, 14);
    h2->SetLineColor(kBlack);
    h2->SetLineWidth(2);
    h2->Fit("fa1");
    mean[1] = fa1->GetParameter(1);
    mean_error[1] = fa1->GetParameter(2)/TMath::Sqrt(h2->Integral());
    std::cout << "mean[1] = " << mean[1] << std::endl;
    std::cout << "mean_error[1] = " << mean_error[1] << std::endl;
    h2->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow2_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow2_Pt500GeV_PathLengthCorrected.png");
    
    TH1F *h3 = (TH1F*)file1->Get("h_TimeAverage_3");
    h3->GetXaxis()->SetRangeUser(9, 14);
    h3->SetLineColor(kBlack);
    h3->SetLineWidth(2);
    h3->Fit("fa1");
    mean[2] = fa1->GetParameter(1);
    mean_error[2] = fa1->GetParameter(2)/TMath::Sqrt(h3->Integral());
    std::cout << "mean[2] = " << mean[2] << std::endl;
    std::cout << "mean_error[2] = " << mean_error[2] << std::endl;
    h3->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow3_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow3_Pt500GeV_PathLengthCorrected.png");
    
    TH1F *h4 = (TH1F*)file1->Get("h_TimeAverage_4");
    h4->GetXaxis()->SetRangeUser(9, 14);
    h4->SetLineColor(kBlack);
    h4->SetLineWidth(2);
    h4->Fit("fa1");
    mean[3] = fa1->GetParameter(1);
    mean_error[3] = fa1->GetParameter(2)/TMath::Sqrt(h4->Integral());
    std::cout << "mean[3] = " << mean[3] << std::endl;
    std::cout << "mean_error[3] = " << mean_error[3] << std::endl;
    h4->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow4_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow4_Pt500GeV_PathLengthCorrected.png");
    
    TH1F *h5 = (TH1F*)file1->Get("h_TimeAverage_5");
    h5->GetXaxis()->SetRangeUser(9, 14);
    h5->SetLineColor(kBlack);
    h5->SetLineWidth(2);
    h5->Fit("fa1");
    mean[4] = fa1->GetParameter(1);
    mean_error[4] = fa1->GetParameter(2)/TMath::Sqrt(h5->Integral());
    std::cout << "mean[4] = " << mean[4] << std::endl;
    std::cout << "mean_error[4] = " << mean_error[4] << std::endl;
    h5->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow5_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow5_Pt500GeV_PathLengthCorrected.png");
    
    TH1F *h6 = (TH1F*)file1->Get("h_TimeAverage_6");
    h6->GetXaxis()->SetRangeUser(9, 14);
    h6->SetLineColor(kBlack);
    h6->SetLineWidth(2);
    h6->Fit("fa1");
    mean[5] = fa1->GetParameter(1);
    mean_error[5] = fa1->GetParameter(2)/TMath::Sqrt(h6->Integral());
    std::cout << "mean[5] = " << mean[5] << std::endl;
    std::cout << "mean_error[5] = " << mean_error[5] << std::endl;
    h6->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow6_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow6_Pt500GeV_PathLengthCorrected.png");
    
    TH1F *h7 = (TH1F*)file1->Get("h_TimeAverage_7");
    h7->GetXaxis()->SetRangeUser(9, 14);
    h7->SetLineColor(kBlack);
    h7->SetLineWidth(2);
    h7->Fit("fa1");
    mean[6] = fa1->GetParameter(1);
    mean_error[6] = fa1->GetParameter(2)/TMath::Sqrt(h7->Integral());
    std::cout << "mean[6] = " << mean[6] << std::endl;
    std::cout << "mean_error[6] = " << mean_error[6] << std::endl;
    h7->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow7_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow7_Pt500GeV_PathLengthCorrected.png");
    
    TH1F *h8 = (TH1F*)file1->Get("h_TimeAverage_8");
    h8->GetXaxis()->SetRangeUser(9, 14);
    h8->SetLineColor(kBlack);
    h8->SetLineWidth(2);
    h8->Fit("fa1");
    mean[7] = fa1->GetParameter(1);
    mean_error[7] = fa1->GetParameter(2)/TMath::Sqrt(h8->Integral());
    std::cout << "mean[7] = " << mean[7] << std::endl;
    std::cout << "mean_error[7] = " << mean_error[7] << std::endl;
    h8->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow8_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow8_Pt500GeV_PathLengthCorrected.png");
    
    TH1F *h9 = (TH1F*)file1->Get("h_TimeAverage_9");
    h9->GetXaxis()->SetRangeUser(9, 14);
    h9->SetLineColor(kBlack);
    h9->SetLineWidth(2);
    h9->Fit("fa1");
    mean[8] = fa1->GetParameter(1);
    mean_error[8] = fa1->GetParameter(2)/TMath::Sqrt(h9->Integral());
    std::cout << "mean[8] = " << mean[8] << std::endl;
    std::cout << "mean_error[8] = " << mean_error[8] << std::endl;
    h9->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow9_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow9_Pt500GeV_PathLengthCorrected.png");
    
    TH1F *h10 = (TH1F*)file1->Get("h_TimeAverage_10");
    h10->GetXaxis()->SetRangeUser(9, 14);
    h10->SetLineColor(kBlack);
    h10->SetLineWidth(2);
    h10->Fit("fa1");
    mean[9] = fa1->GetParameter(1);
    mean_error[9] = fa1->GetParameter(2)/TMath::Sqrt(h10->Integral());
    std::cout << "mean[9] = " << mean[9] << std::endl;
    std::cout << "mean_error[9] = " << mean_error[9] << std::endl;
    h10->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow10_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow10_Pt500GeV_PathLengthCorrected.png");
    
    TH1F *h11 = (TH1F*)file1->Get("h_TimeAverage_11");
    h11->GetXaxis()->SetRangeUser(9, 14);
    h11->SetLineColor(kBlack);
    h11->SetLineWidth(2);
    h11->Fit("fa1");
    mean[10] = fa1->GetParameter(1);
    mean_error[10] = fa1->GetParameter(2)/TMath::Sqrt(h11->Integral());
    std::cout << "mean[10] = " << mean[10] << std::endl;
    std::cout << "mean_error[10] = " << mean_error[10] << std::endl;
    h11->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow11_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow11_Pt500GeV_PathLengthCorrected.png");
    
    TH1F *h12 = (TH1F*)file1->Get("h_TimeAverage_12");
    h12->GetXaxis()->SetRangeUser(9, 14);
    h12->SetLineColor(kBlack);
    h12->SetLineWidth(2);
    h12->Fit("fa1");
    mean[11] = fa1->GetParameter(1);
    mean_error[11] = fa1->GetParameter(2)/TMath::Sqrt(h12->Integral());
    std::cout << "mean[11] = " << mean[11] << std::endl;
    std::cout << "mean_error[11] = " << mean_error[11] << std::endl;
    h12->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow12_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow12_Pt500GeV_PathLengthCorrected.png");
    
    TH1F *h13 = (TH1F*)file1->Get("h_TimeAverage_13");
    h13->GetXaxis()->SetRangeUser(9, 14);
    h13->SetLineColor(kBlack);
    h13->SetLineWidth(2);
    h13->Fit("fa1");
    mean[12] = fa1->GetParameter(1);
    mean_error[12] = fa1->GetParameter(2)/TMath::Sqrt(h13->Integral());
    std::cout << "mean[12] = " << mean[12] << std::endl;
    std::cout << "mean_error[12] = " << mean_error[12] << std::endl;
    h13->Draw();
    fa1->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow13_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow13_Pt500GeV_PathLengthCorrected.png");
    
    TH1F *h14 = (TH1F*)file1->Get("h_TimeAverage_14");
    h14->Rebin(5);
    h12->SetMaximum(30);
    h14->SetLineColor(kBlack);
    h14->SetLineWidth(2);
    h14->GetXaxis()->SetRangeUser(9, 14);
    TF1 *fa2 = new TF1("fa2", "gaus", 9, 14); 
    fa2->SetParLimits(0, 35, 40);
    h14->Fit("fa2");
    mean[13] = fa2->GetParameter(1);
    mean_error[13] = fa2->GetParameter(2)/TMath::Sqrt(h14->Integral());
    std::cout << "mean[13] = " << mean[13] << std::endl;
    std::cout << "mean_error[13] = " << mean_error[13] << std::endl;
    h14->Draw();
    fa2->Draw("same");
    
    c1.SaveAs("h_Time_AverageWindow14_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_AverageWindow14_Pt500GeV_PathLengthCorrected.png");

    double x[14] = {320, 325, 330, 335, 340, 345, 350, 355, 360, 365, 370, 375, 380, 385};
    double x_error[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    for(int i=0; i<14; i++)
    {
      std::cout << "mean[i] = " << mean[i] << std::endl;
      std::cout << "mean_error[i] = " << mean_error[i] << std::endl;
    }
    TGraphErrors *gr = new TGraphErrors(14, x, mean, x_error, mean_error);
    gr->SetLineColor(kBlue);
    gr->SetLineWidth(2);
    gr->SetMarkerColor(kBlack);
    gr->SetTitle("Time of flight as the particle moves through the detector");
    gr->GetXaxis()->SetTitle("Distance [cm]");
    gr->GetYaxis()->SetTitle("Time [ns]");
    gr->Draw("AP*");
    c1.SaveAs("h_Time_Average_All_Pt500GeV_PathLengthCorrected.pdf");
    c1.SaveAs("h_Time_Average_All_Pt500GeV_PathLengthCorrected.png");
    
    return 0;
    
}

int computeSpeed_50GeV()
{
  double mean[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double mean_error[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  mean[0] = 10.8251;
  mean_error[0] = 0.0099474;
  mean[1] = 10.9798;
  mean_error[1] = 0.00625701;
  mean[2] = 11.136;
  mean_error[2] = 0.00519519;
  mean[3] = 11.2856;
  mean_error[3] = 0.00509323;
  mean[4] = 11.4432;
  mean_error[4] = 0.00489423;
  mean[5] = 11.6065;
  mean_error[5] = 0.00478683;
  mean[6] = 11.7761;
  mean_error[6] = 0.0056265;
  mean[7] = 11.9335;
  mean_error[7] = 0.00669901;
  mean[8] = 12.098;
  mean_error[8] = 0.00868749;
  mean[9] = 12.2761;
  mean_error[9] = 0.0107791;
  mean[10] = 12.392;
  mean_error[10] = 0.0145253;
  mean[11] = 12.5858;
  mean_error[11] = 0.0294899;
  mean[12] = 13.5699;
  mean_error[12] = 0.170504;
  mean[13] = 13.591;
  mean_error[13] = 0.078911;

  double units = 0.01/(1e-9);
  double array0 = (5.0/(mean[1] - mean[0]))*units;
  double array1 = (5.0/(mean[2] - mean[1]))*units; 
  double array2 = (5.0/(mean[3] - mean[2]))*units; 
  double array3 = (5.0/(mean[4] - mean[3]))*units; 
  double array4 = (5.0/(mean[5] - mean[4]))*units; 
  double array5 = (5.0/(mean[6] - mean[5]))*units;
  double array6 = (5.0/(mean[7] - mean[6]))*units;
  double array7 = (5.0/(mean[8] - mean[7]))*units;
  double array8 = (5.0/(mean[9] - mean[8]))*units;
  double array9 = (5.0/(mean[10] - mean[9]))*units;
  double array10 = (5.0/(mean[11] - mean[10]))*units;
  double array11 = (5.0/(mean[12] - mean[11]))*units;

  double speed[12] = {array0, array1, array2, array3, array4, array5, array6, array7, array8, array9, array10, array11};
  double x[12] = {320, 325, 330, 335, 340, 345, 350, 355, 360, 365, 370, 375};
  for(int i=0; i<12; i++)
  {
    std::cout << "speed["<<i<<"] = "<< speed[i] << std::endl;
  }
  TGraph *gr = new TGraph(12, x, speed);
  gr->SetLineColor(kBlue);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(kBlack);
  gr->SetTitle("Speed of propagation of particles through the detector");
  gr->GetXaxis()->SetTitle("Distance [cm]");
  gr->GetYaxis()->SetTitle("Time [ns]");
  gr->Draw("AP*");


  return 0;

} 


int computeSpeed_500GeV()
{
  double mean[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double mean_error[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

  mean[0] = 10.8335;
  mean_error[0] = 0.00915249;
  mean[1] = 10.9784;
  mean_error[1] = 0.0060528;
  mean[2] = 11.1278;
  mean_error[2] = 0.00532063;
  mean[3] = 11.3025;
  mean_error[3] = 0.00503702;
  mean[4] = 11.4645;
  mean_error[4] = 0.00483413;
  mean[5] = 11.6201;
  mean_error[5] = 0.00464213;
  mean[6] = 11.7711;
  mean_error[6] = 0.00458883;
  mean[7] = 11.9373;
  mean_error[7] = 0.00516174;
  mean[8] = 12.1072;
  mean_error[8] = 0.00594922;
  mean[9] = 12.2807;
  mean_error[9] = 0.00758584;
  mean[10] = 12.4312;
  mean_error[10] = 0.00897584;
  mean[11] = 12.6056;
  mean_error[11] = 0.0116994;
  mean[12] = 12.8135;
  mean_error[12] = 0.0180405;
  mean[13] = 13.0518;
  mean_error[13] = 0.0358609;

  double units = 0.01/(1e-9);
  double array0 = (5.0/(mean[1] - mean[0]))*units;
  double array1 = (5.0/(mean[2] - mean[1]))*units;
  double array2 = (5.0/(mean[3] - mean[2]))*units;
  double array3 = (5.0/(mean[4] - mean[3]))*units;
  double array4 = (5.0/(mean[5] - mean[4]))*units;
  double array5 = (5.0/(mean[6] - mean[5]))*units;
  double array6 = (5.0/(mean[7] - mean[6]))*units;
  double array7 = (5.0/(mean[8] - mean[7]))*units;
  double array8 = (5.0/(mean[9] - mean[8]))*units;
  double array9 = (5.0/(mean[10] - mean[9]))*units;
  double array10 = (5.0/(mean[11] - mean[10]))*units;
  double array11 = (5.0/(mean[12] - mean[11]))*units;

  double speed[12] = {array0, array1, array2, array3, array4, array5, array6, array7, array8, array9, array10, array11};
  double x[12] = {320, 325, 330, 335, 340, 345, 350, 355, 360, 365, 370, 375};
  for(int i=0; i<12; i++)
  {
    std::cout << "speed["<<i<<"] = "<< speed[i] << std::endl;
  }
  TGraph *gr = new TGraph(12, x, speed);
  gr->SetMinimum(150000000);
  gr->SetMaximum(500000000);
  gr->SetLineColor(kBlue);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(kBlack);
  gr->SetTitle("Speed of propagation of particles through the detector");
  gr->GetXaxis()->SetTitle("Distance [cm]");
  gr->GetYaxis()->SetTitle("Time [ns]");
  gr->Draw("AP*");

  return 0;
} 

