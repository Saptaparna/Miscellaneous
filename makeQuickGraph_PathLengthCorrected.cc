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
  double mean[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double mean_error[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  double x[12] = {320, 325, 330, 335, 340, 345, 350, 355, 360, 365, 370, 375};
  double x_error[12] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
  mean[0] = 10.8251;
  mean_error[0] = 0.0099474;
  mean[1] = 10.8485;
  mean_error[1] = 0.00623785;
  mean[2] = 10.8525;
  mean_error[2] = 0.00544669;
  mean[3] = 10.8512;
  mean_error[3] = 0.0051411;
  mean[4] = 10.8564;
  mean_error[4] = 0.00488162;
  mean[5] = 10.8594;
  mean_error[5] = 0.00484716;
  mean[6] = 10.8648;
  mean_error[6] = 0.00545544;
  mean[7] = 10.8658;
  mean_error[7] = 0.00679767;
  mean[8] = 10.8569;
  mean_error[8] = 0.00852693;
  mean[9] = 10.8721;
  mean_error[9] = 0.0100835;
  mean[10] = 10.8474;
  mean_error[10] = 0.0146608;
  mean[11] = 10.8267;
  mean_error[11] = 0.0207798;

  TGraphErrors *gr = new TGraphErrors(12, x, mean, x_error, mean_error);
  gr->SetLineColor(kBlue);
  gr->SetLineWidth(2);
  gr->SetMarkerColor(kBlack);
  gr->SetTitle("Time of flight as the particle moves through the detector");
  gr->GetXaxis()->SetTitle("Distance [cm]");
  gr->GetYaxis()->SetTitle("Time [ns]");
  gr->SetMaximum(20);
  gr->SetMinimum(0);
  gr->Draw("AP*");
  TF1 *f = new TF1("f","[0]*x+[1]",320, 375);
  gr->Fit("f");
  f->Draw("same");
  c1.SaveAs("h_Time_Average_All_Pt50GeV_Fitted_PathLengthCorrected.pdf");
  c1.SaveAs("h_Time_Average_All_Pt50GeV_Fitted_PathLengthCorrected.png");
  c1.SaveAs("h_Time_Average_All_Pt50GeV_Fitted_PathLengthCorrected.C");
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
