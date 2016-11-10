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

TLorentzVector fillTLorentzVector(double pT, double eta, double phi, double E)
{
  TLorentzVector object_p4;
  object_p4.SetPtEtaPhiE(pT, eta, phi, E);
  return object_p4;
}

int ReadRussianTree(std::string infile, std::string outfile)
{
  std::string inputfilename=(infile+".root").c_str();
  TChain *tree=new TChain("amumu_presel");
  tree->Add(inputfilename.c_str());
  std::cout<<"Opened input file "<<inputfilename<<std::endl;

  Double_t        dilepton_mass;
  Double_t        dilepton_b_mass;
  Int_t           run_number;
  Int_t           event_number;
  Int_t           n_jets;
  Int_t           n_bjets;
  Int_t           n_fwdjets;
  Double_t        dilepton_pt;
  Double_t        dilepton_eta;
  Double_t        lepton1_eta;
  Double_t        lepton1_pt;
  Double_t        lepton1_phi;
  Double_t        lepton2_eta;
  Double_t        lepton2_pt;
  Double_t        lepton2_phi;
  Double_t        jet_eta;
  Double_t        jet_pt;
  Double_t        jet_phi;
  Double_t        bjet_eta;
  Double_t        bjet_pt;
  Double_t        bjet_phi;
  Double_t        met_mag;
  Double_t        dphi_mumu_bj;  
 
  tree->SetBranchAddress("run_number", &(run_number));
  tree->SetBranchAddress("event_number", &(event_number));
  tree->SetBranchAddress("dilepton_mass", &(dilepton_mass));
  tree->SetBranchAddress("dilepton_b_mass", &(dilepton_b_mass));
  tree->SetBranchAddress("n_jets", &(n_jets));
  tree->SetBranchAddress("n_bjets", &(n_bjets));
  tree->SetBranchAddress("n_fwdjets", &(n_fwdjets));
  tree->SetBranchAddress("dilepton_pt", &(dilepton_pt));
  tree->SetBranchAddress("dilepton_eta", &(dilepton_eta));
  tree->SetBranchAddress("lepton1_eta", &(lepton1_eta));
  tree->SetBranchAddress("lepton1_phi", &(lepton1_phi));
  tree->SetBranchAddress("lepton1_pt", &(lepton1_pt));
  tree->SetBranchAddress("lepton2_eta", &(lepton2_eta));
  tree->SetBranchAddress("lepton2_phi", &(lepton2_phi));
  tree->SetBranchAddress("lepton2_pt", &(lepton2_pt));
  tree->SetBranchAddress("jet_eta", &(jet_eta));
  tree->SetBranchAddress("jet_phi", &(jet_phi));
  tree->SetBranchAddress("jet_pt", &(jet_pt));
  tree->SetBranchAddress("bjet_eta", &(bjet_eta));
  tree->SetBranchAddress("bjet_phi", &(bjet_phi));
  tree->SetBranchAddress("bjet_pt", &(bjet_pt));
  tree->SetBranchAddress("met_mag", &(met_mag));
  tree->SetBranchAddress("dphi_mumu_bj", &(dphi_mumu_bj));

  TH1F *dilepton_mass_1b1f = new TH1F("dilepton_mass_1b1f", "dilepton_mass_1b1f", 100, 0.0, 100.0);
  TH1F *dilepton_mass_1b1f_withQTCut = new TH1F("dilepton_mass_1b1f_withQTCut", "dilepton_mass_1b1f_withQTCut", 100, 0.0, 100.0);
  TH1F *dilepton_mass_1b1f_withQT_Plus_MetCut = new TH1F("dilepton_mass_1b1f_withQT_Plus_MetCut", "dilepton_mass_1b1f_withQT_Plus_MetCut", 100, 0.0, 100.0);
  TH1F *dilepton_mass_1b1f_withQT_Plus_MetCut_Plus_dphi = new TH1F("dilepton_mass_1b1f_withQT_Plus_MetCut_Plus_dphi", "dilepton_mass_1b1f_withQT_Plus_MetCut_Plus_dphi", 100, 0.0, 100.0);
  TH1F *dilepton_mass_1b1c = new TH1F("dilepton_mass_1b1c", "dilepton_mass_1b1c", 100, 0.0, 100.0);
  TH1F *dilepton_mass_1b1c_withQTCut = new TH1F("dilepton_mass_1b1c_withQTCut", "dilepton_mass_1b1c_withQTCut", 100, 0.0, 100.0);
  TH1F *dilepton_mass_1b1c_withQT_Plus_MetCut = new TH1F("dilepton_mass_1b1c_withQT_Plus_MetCut", "dilepton_mass_1b1c_withQT_Plus_MetCut", 100, 0.0, 100.0);
  TH1F *dilepton_mass_1b1c_withQT_Plus_MetCut_Plus_dphi = new TH1F("dilepton_mass_1b1c_withQT_Plus_MetCut_Plus_dphi", "dilepton_mass_1b1c_withQT_Plus_MetCut_Plus_dphi", 100, 0.0, 100.0); 

  int nEvents=tree->GetEntries();
  int n_1b1f = 0;
  int n_1b1c = 0;
  vector <long long> checkDuplicates;
  int nDup = 0;
  long long RUNPREF = 1000 * 1000;
  RUNPREF *= 1000 * 1000;
  std::cout << "nEvents= " << nEvents << std::endl;
  for (int i=0; i<nEvents; ++i)
  {
    tree->GetEvent(i);

    TLorentzVector lep1;
    lep1.SetPtEtaPhiM(lepton1_pt, lepton1_eta, lepton1_phi, 0.105);
    TLorentzVector lep2;
    lep2.SetPtEtaPhiM(lepton2_pt, lepton2_eta, lepton2_phi, 0.105);

    if(lepton1_pt>25.0 and lepton2_pt>25.0 and n_fwdjets>=1 and n_bjets==1 and n_jets==0 and dilepton_mass>12 and dilepton_mass<70) 
    {
      long long dupCheck = run_number*RUNPREF + event_number;
      bool bDuplicate = false;
      for (unsigned int uid = 0; uid < checkDuplicates.size(); uid++)
      {
        if (checkDuplicates[uid] == dupCheck)
        {
          cout<<dupCheck<<endl;
          bDuplicate = true;
          nDup++;
          break;
        }
      }
      if (bDuplicate) continue;
      else checkDuplicates.push_back(dupCheck); 
      n_1b1f++;
      if(not (dilepton_mass>24 and dilepton_mass<33)) dilepton_mass_1b1f->Fill(dilepton_mass);
      if(not (dilepton_mass>24 and dilepton_mass<33) and ((lep1+lep2).Pt()/dilepton_mass) > 2.0) dilepton_mass_1b1f_withQTCut->Fill(dilepton_mass);
      if((not (dilepton_mass>24 and dilepton_mass<33)) and ((lep1+lep2).Pt()/dilepton_mass) > 2.0 and met_mag<40.0) dilepton_mass_1b1f_withQT_Plus_MetCut->Fill(dilepton_mass);
      if((not (dilepton_mass>24 and dilepton_mass<33)) and ((lep1+lep2).Pt()/dilepton_mass) > 2.0 and met_mag<40.0 and dphi_mumu_bj > 2.5) dilepton_mass_1b1f_withQT_Plus_MetCut_Plus_dphi->Fill(dilepton_mass);
    }//if statement for 1b1f  
    
    if(lepton1_pt>25.0 and lepton2_pt>25.0 and n_bjets>=1 and (n_bjets + n_jets==2) and dilepton_mass>12 and dilepton_mass<70 and n_fwdjets==0)
    {
      long long dupCheck = run_number*RUNPREF + event_number;
      bool bDuplicate = false;
      for (unsigned int uid = 0; uid < checkDuplicates.size(); uid++)
      {  
        if (checkDuplicates[uid] == dupCheck)
        {
          cout<<dupCheck<<endl;
          bDuplicate = true;
          nDup++;
          break;
        }
      }
      if (bDuplicate) continue;
      else checkDuplicates.push_back(dupCheck);   
      if(not (dilepton_mass>24 and dilepton_mass<33)) dilepton_mass_1b1c->Fill(dilepton_mass);
      if(not (dilepton_mass>24 and dilepton_mass<33) and ((lep1+lep2).Pt()/dilepton_mass) > 2.0) dilepton_mass_1b1c_withQTCut->Fill(dilepton_mass); 
      if((not (dilepton_mass>24 and dilepton_mass<33)) and ((lep1+lep2).Pt()/dilepton_mass) > 2.0 and met_mag<40.0) dilepton_mass_1b1c_withQT_Plus_MetCut->Fill(dilepton_mass);
      if((not (dilepton_mass>24 and dilepton_mass<33)) and ((lep1+lep2).Pt()/dilepton_mass) > 2.0 and met_mag<40.0 and dphi_mumu_bj > 2.5) dilepton_mass_1b1c_withQT_Plus_MetCut_Plus_dphi->Fill(dilepton_mass);
      if(met_mag<40.0 and dphi_mumu_bj > 2.5) n_1b1c++;
    }//if statement for 1b1c 
     
  }//end of event loop

  std::cout << "n_1b1f = " << n_1b1f << std::endl;
  std::cout << "n_1b1c = " << n_1b1c << std::endl;
  TH1F *dilepton_mass_All = (TH1F*)dilepton_mass_1b1f->Clone("dilepton_mass_All");
  dilepton_mass_All->Add(dilepton_mass_1b1c);
  dilepton_mass_All->SetName("dilepton_mass_All");
  
  TH1F *dilepton_mass_All_withQTCut = (TH1F*)dilepton_mass_1b1f_withQTCut->Clone("dilepton_mass_All_withQTCut");
  dilepton_mass_All_withQTCut->Add(dilepton_mass_1b1c_withQTCut);
  dilepton_mass_All_withQTCut->SetName("dilepton_mass_All_withQTCut");

  TH1F *dilepton_mass_All_withQT_Plus_MetCut = (TH1F*)dilepton_mass_1b1f_withQT_Plus_MetCut->Clone("dilepton_mass_All_withQT_Plus_MetCut");
  dilepton_mass_All_withQT_Plus_MetCut->Add(dilepton_mass_1b1c_withQT_Plus_MetCut);
  dilepton_mass_All_withQT_Plus_MetCut->SetName("dilepton_mass_All_withQT_Plus_MetCut");

  TH1F *dilepton_mass_All_withQT_Plus_MetCut_Plus_dphi = (TH1F*)dilepton_mass_1b1f_withQT_Plus_MetCut_Plus_dphi->Clone("dilepton_mass_All_withQT_Plus_MetCut_Plus_dphi");
  dilepton_mass_All_withQT_Plus_MetCut_Plus_dphi->Add(dilepton_mass_1b1c_withQT_Plus_MetCut_Plus_dphi);
  dilepton_mass_All_withQT_Plus_MetCut_Plus_dphi->SetName("dilepton_mass_All_withQT_Plus_MetCut_Plus_dphi");

  std::string histfilename=(outfile+".root").c_str();
  TFile *tFile=new TFile(histfilename.c_str(), "RECREATE");
  dilepton_mass_1b1f->Write();
  dilepton_mass_1b1f_withQTCut->Write();
  dilepton_mass_1b1f_withQT_Plus_MetCut->Write();
  dilepton_mass_1b1f_withQT_Plus_MetCut_Plus_dphi->Write();
  dilepton_mass_1b1c->Write();
  dilepton_mass_1b1c_withQTCut->Write();
  dilepton_mass_1b1c_withQT_Plus_MetCut->Write();
  dilepton_mass_1b1c_withQT_Plus_MetCut_Plus_dphi->Write();
  dilepton_mass_All->Write();
  dilepton_mass_All_withQTCut->Write();
  dilepton_mass_All_withQT_Plus_MetCut->Write();
  dilepton_mass_All_withQT_Plus_MetCut_Plus_dphi->Write();
  tFile->Close();
  std::cout<<"Wrote output file "<<histfilename<<std::endl;

  return 0;
}
