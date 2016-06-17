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

void beamSpot(){

  TCanvas* c1 = new TCanvas("c1", "c1", 600, 400);

  TF1 *fa1 = new TF1("fa1","gaus", 2600, 20000);
  double x1 = fa1->GetRandom();
  TH1F *h1 = new TH1F("h1", "h1", 174, 2600.0, 20000.0);
  h1->FillRandom("fa1", 100000);
  c1->SetLogy();
  h1->Draw();

  


}
