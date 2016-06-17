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

Int_t cell_n;
Int_t           cell_layer[1000000];   //[cell_n]
Int_t cell_id[1000000]; // [cell_n]
Int_t cell_subdet[1000000]; // [cell_n]
Int_t cell_zside[1000000]; // [cell_n]
Int_t cell_wafer[1000000]; // [cell_n]
Int_t cell_wafertype[1000000]; // [cell_n]
Int_t cell_cell[1000000]; // [cell_n]
Int_t cell_moduleid[1000000]; // [cell_n]
Int_t cell_triggercellid[1000000]; // [cell_n]
UInt_t cell_digi[1000000];  // [cell_n]
/*Float_t cell_x[6000]; // [cell_n]
Float_t cell_y[6000]; // [cell_n]
Float_t cell_z[6000]; // [cell_n]
Float_t cell_eta[6000]; // [cell_n]
*/
int DigiReader(std::string infile, std::string outfile)
{
  std::string inputfilename=(infile+".root").c_str();
  TChain *tree=new TChain("hgctiming/HGCTiming");
  tree->Add(inputfilename.c_str());
  std::cout<<"Opened input file "<<inputfilename<<std::endl;

  tree->SetBranchAddress("cell_n" , &cell_n);
  tree->SetBranchAddress("cell_layer", cell_layer);
  tree->SetBranchAddress("cell_id", cell_id);
  tree->SetBranchAddress("cell_subdet", cell_subdet);
  tree->SetBranchAddress("cell_zside", cell_zside);
  tree->SetBranchAddress("cell_wafer", cell_wafer);
  tree->SetBranchAddress("cell_wafertype", cell_wafertype);
  tree->SetBranchAddress("cell_cell", cell_cell);
  tree->SetBranchAddress("cell_moduleid", cell_moduleid);
  tree->SetBranchAddress("cell_triggercellid", cell_triggercellid);
  tree->SetBranchAddress("cell_digi", cell_digi);
  /*tree->SetBranchAddress("cell_x", cell_x);
  tree->SetBranchAddress("cell_y", cell_y);
  tree->SetBranchAddress("cell_z", cell_z);
  tree->SetBranchAddress("cell_eta", cell_eta);
  */
  int nEvents=tree->GetEntries();

  for (int i=0; i<10; ++i)
  {
    tree->GetEvent(i);
    Int_t ncell = cell_n;
    //int array_size = sizeof(cell_layer)/sizeof(Int_t);

    //for(int i=0; i<cell_n; i++ )
    //{
      UInt_t  value_ = cell_digi[i];
      /*bool mode_      = ((value_ >> 30) & 0x1 ); // True -> TDC readout activated, False -> ADC.
      uint32_t toa_   = ((value_ >> 13) & 0x3ff); // Time of arrival.
      uint32_t data_  = ((value_ >> 0)  & 0xfff);
      if(mode_)
      {
        double toaLSBToNS               = 0.005;
        float jitter_ = double(toa_) * toaLSBToNS;
        std::cout << "jitter_ = " << jitter_ << std::endl;
      }  */
    //}
    
  }
  return 0;
}
