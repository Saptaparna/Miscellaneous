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

int makeQuickGraph_50GeV() 
{
  TCanvas c1("c1","Highest Energy recHit", 10, 10, 600, 400);
  gStyle->SetOptFit(1);
  double mean[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double mean_error[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double x[14] = {320, 325, 330, 335, 340, 345, 350, 355, 360, 365, 370, 375, 380, 385};
  double x_error[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
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

  TGraphErrors *gr = new TGraphErrors(14, x, mean, x_error, mean_error);
  gr->SetLineColor(kBlue);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(kBlack);
  gr->SetTitle("Time of flight as the particle moves through the detector");
  gr->GetXaxis()->SetTitle("Distance [cm]");
  gr->GetYaxis()->SetTitle("Time [ns]");
  gr->Draw("AP*");
  TF1 *f = new TF1("f","[0]*x+[1]",320, 390);
  gr->Fit("f");
  f->Draw("same");
  c1.SaveAs("h_Time_Average_All_Pt50GeV_Fitted.pdf");
  c1.SaveAs("h_Time_Average_All_Pt50GeV_Fitted.png");
  c1.SaveAs("h_Time_Average_All_Pt50GeV_Fitted.C");
  return 0;
}

int makeQuickGraph_500GeV()
{ 
  gStyle->SetOptFit(1);
  TCanvas c1("c1","Highest Energy recHit", 10, 10, 600, 400); 
  double mean[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double mean_error[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double x_error[14] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double x[14] = {320, 325, 330, 335, 340, 345, 350, 355, 360, 365, 370, 375, 380, 385};
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

  TGraphErrors *gr = new TGraphErrors(14, x, mean, x_error, mean_error);
  gr->SetLineColor(kBlue);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(kBlack);
  gr->SetTitle("Time of flight as the particle moves through the detector");
  gr->GetXaxis()->SetTitle("Distance [cm]");
  gr->GetYaxis()->SetTitle("Time [ns]");
  gr->Draw("AP*");
  TF1 *f = new TF1("f","[0]*x+[1]",320, 390);
  gr->Fit("f");
  f->Draw("same");
  c1.SaveAs("h_Time_Average_All_Pt500GeV_Fitted.pdf");
  c1.SaveAs("h_Time_Average_All_Pt500GeV_Fitted.png");
  return 0;

}
