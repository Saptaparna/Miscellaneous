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


int makeFitsOfHits_80GeV(std::string infile)
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

  c1.SaveAs("h_Time_AverageWindow1_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow1_Pt80GeV_PathLengthCorrected.png");

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

  c1.SaveAs("h_Time_AverageWindow2_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow2_Pt80GeV_PathLengthCorrected.png");

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

  c1.SaveAs("h_Time_AverageWindow3_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow3_Pt80GeV_PathLengthCorrected.png");

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

  c1.SaveAs("h_Time_AverageWindow4_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow4_Pt80GeV_PathLengthCorrected.png");

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

  c1.SaveAs("h_Time_AverageWindow5_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow5_Pt80GeV_PathLengthCorrected.png");

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

  c1.SaveAs("h_Time_AverageWindow6_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow6_Pt80GeV_PathLengthCorrected.png");

  TH1F *h7 = (TH1F*)file1->Get("h_TimeAverage_7");
  h7->GetXaxis()->SetRangeUser(9, 14);
  h7->SetLineColor(kBlack);
  h7->SetLineWidth(2);
  //fa1->SetParLimits(0, 330, 350);
  h7->Fit("fa1");
  mean[6] = fa1->GetParameter(1);
  mean_error[6] = fa1->GetParameter(2)/TMath::Sqrt(h7->Integral());
  std::cout << "mean[6] = " << mean[6] << std::endl;
  std::cout << "mean_error[6] = " << mean_error[6] << std::endl;
  h7->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow7_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow7_Pt80GeV_PathLengthCorrected.png");

  TH1F *h8 = (TH1F*)file1->Get("h_TimeAverage_8");
  h8->GetXaxis()->SetRangeUser(9, 14);
  h8->SetLineColor(kBlack);
  h8->SetLineWidth(2);
  //fa1->SetParLimits(0, 205, 210);
  h8->Fit("fa1");
  mean[7] = fa1->GetParameter(1);
  mean_error[7] = fa1->GetParameter(2)/TMath::Sqrt(h8->Integral());
  std::cout << "mean[7] = " << mean[7] << std::endl;
  std::cout << "mean_error[7] = " << mean_error[7] << std::endl;
  h8->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow8_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow8_Pt80GeV_PathLengthCorrected.png");

  TH1F *h9 = (TH1F*)file1->Get("h_TimeAverage_9");
  h9->GetXaxis()->SetRangeUser(9, 14);
  h9->SetLineColor(kBlack);
  h9->SetLineWidth(2);
  //fa1->SetParLimits(0, 130, 135);
  h9->Fit("fa1");
  mean[8] = fa1->GetParameter(1);
  mean_error[8] = fa1->GetParameter(2)/TMath::Sqrt(h9->Integral());
  std::cout << "mean[8] = " << mean[8] << std::endl;
  std::cout << "mean_error[8] = " << mean_error[8] << std::endl;
  h9->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow9_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow9_Pt80GeV_PathLengthCorrected.png");

  TH1F *h10 = (TH1F*)file1->Get("h_TimeAverage_10");
  h10->GetXaxis()->SetRangeUser(9, 14);
  h10->SetLineColor(kBlack);
  h10->SetLineWidth(2);
  //fa1->SetParLimits(0, 95, 100);
  h10->Fit("fa1");
  mean[9] = fa1->GetParameter(1);
  mean_error[9] = fa1->GetParameter(2)/TMath::Sqrt(h10->Integral());
  std::cout << "mean[9] = " << mean[9] << std::endl;
  std::cout << "mean_error[9] = " << mean_error[9] << std::endl;
  h10->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow10_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow10_Pt80GeV_PathLengthCorrected.png");

  TH1F *h11 = (TH1F*)file1->Get("h_TimeAverage_11");
  h11->GetXaxis()->SetRangeUser(9, 14);
  h11->SetLineColor(kBlack);
  h11->SetLineWidth(2);
  //fa1->SetParLimits(0, 45, 50);
  h11->Fit("fa1");
  mean[10] = fa1->GetParameter(1);
  mean_error[10] = fa1->GetParameter(2)/TMath::Sqrt(h11->Integral());
  std::cout << "mean[10] = " << mean[10] << std::endl;
  std::cout << "mean_error[10] = " << mean_error[10] << std::endl;
  h11->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow11_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow11_Pt80GeV_PathLengthCorrected.png");

  TH1F *h12 = (TH1F*)file1->Get("h_TimeAverage_12");
  h12->GetXaxis()->SetRangeUser(9, 14);
  h12->SetLineColor(kBlack);
  h12->SetLineWidth(2);
  //fa1->SetParLimits(0, 20, 22);
  h12->Fit("fa1");
  mean[11] = fa1->GetParameter(1);
  mean_error[11] = fa1->GetParameter(2)/TMath::Sqrt(h12->Integral());
  std::cout << "mean[11] = " << mean[11] << std::endl;
  std::cout << "mean_error[11] = " << mean_error[11] << std::endl;
  h12->Draw();
  fa1->Draw("same");

  c1.SaveAs("h_Time_AverageWindow12_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow12_Pt80GeV_PathLengthCorrected.png");

  TH1F *h13 = (TH1F*)file1->Get("h_TimeAverage_13");
  h13->GetXaxis()->SetRangeUser(9, 14);
  h13->SetLineColor(kBlack);
  h13->SetLineWidth(2);
  TF1 *fa3 = new TF1("fa3", "gaus", 9, 14);
  //fa3->SetParLimits(0, 3, 4);
  h13->Fit("fa3");
  mean[12] = fa3->GetParameter(1);
  mean_error[12] = fa3->GetParameter(2)/TMath::Sqrt(h13->Integral());
  std::cout << "mean[12] = " << mean[12] << std::endl;
  std::cout << "mean_error[12] = " << mean_error[12] << std::endl;
  h13->Draw();
  fa3->Draw("same");

  c1.SaveAs("h_Time_AverageWindow13_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow13_Pt80GeV_PathLengthCorrected.png");

  TH1F *h14 = (TH1F*)file1->Get("h_TimeAverage_14");
  h14->Rebin(5);
  h14->SetLineColor(kBlack);
  h14->SetLineWidth(2);
  h14->GetXaxis()->SetRangeUser(9, 14);
  TF1 *fa2 = new TF1("fa2", "gaus", 12, 15); 
  //fa2->SetParLimits(0, 18, 20);
  h14->Fit("fa2");
  mean[13] = fa2->GetParameter(1);
  mean_error[13] = fa2->GetParameter(2)/TMath::Sqrt(h14->Integral());
  std::cout << "mean[13] = " << mean[13] << std::endl;
  std::cout << "mean_error[13] = " << mean_error[13] << std::endl;
  h14->Draw();
  fa2->Draw("same");

  c1.SaveAs("h_Time_AverageWindow14_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_AverageWindow14_Pt80GeV_PathLengthCorrected.png");
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
  
  c1.SaveAs("h_Time_Average_All_Pt80GeV_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_Average_All_Pt80GeV_PathLengthCorrected.png");
  return 0;

}
