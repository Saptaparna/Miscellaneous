//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 16 00:30:22 2016 by ROOT version 5.34/32
// from TTree HGCTiming/HGCTiming
// found on file: HGCTiming_SingleElectron_Pt50GeV.root
//////////////////////////////////////////////////////////

#ifndef HGCTiming_h
#define HGCTiming_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <TLorentzVector.h>

// Fixed size dimensions of array or collections stored in the TTree if any.

class HGCTiming {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           cell_n;
   Int_t           cell_id[34753];   //[cell_n]
   Int_t           cell_subdet[34753];   //[cell_n]
   Int_t           cell_zside[34753];   //[cell_n]
   Int_t           cell_layer[34753];   //[cell_n]
   Int_t           cell_wafer[34753];   //[cell_n]
   Int_t           cell_wafertype[34753];   //[cell_n]
   Int_t           cell_cell[34753];   //[cell_n]
   Int_t           cell_moduleid[34753];   //[cell_n]
   Int_t           cell_triggercellid[34753];   //[cell_n]
   UInt_t          cell_digi[34753];   //[cell_n]
   Int_t           run;
   Int_t           event;
   Int_t           lumi;
   Float_t         vertex_x;
   Float_t         vertex_y;
   Float_t         vertex_z;
   vector<float>   *recHit_energy;
   vector<float>   *recHit_x;
   vector<float>   *recHit_y;
   vector<float>   *recHit_z;
   vector<float>   *recHit_time;
   vector<float>   *uncRecHit_time;
   TLorentzVector  *GenVertex;
   Float_t         dist2center;

   // List of branches
   TBranch        *b_cell_n;   //!
   TBranch        *b_cell_id;   //!
   TBranch        *b_cell_subdet;   //!
   TBranch        *b_cell_zside;   //!
   TBranch        *b_cell_layer;   //!
   TBranch        *b_cell_wafer;   //!
   TBranch        *b_cell_wafertype;   //!
   TBranch        *b_cell_cell;   //!
   TBranch        *b_cell_moduleid;   //!
   TBranch        *b_cell_triggercellid;   //!
   TBranch        *b_cell_digi;   //!
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumi;   //!
   TBranch        *b_vertex_x;   //!
   TBranch        *b_vertex_y;   //!
   TBranch        *b_vertex_z;   //!
   TBranch        *b_recHit_energy;   //!
   TBranch        *b_recHit_x;   //!
   TBranch        *b_recHit_y;   //!
   TBranch        *b_recHit_z;   //!
   TBranch        *b_recHit_time;   //!
   TBranch        *b_uncRecHit_time;   //!
   TBranch        *b_GenVertex;   //!
   TBranch        *b_dist2center;   //!

   HGCTiming(TTree *tree=0);
   virtual ~HGCTiming();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef HGCTiming_cxx
HGCTiming::HGCTiming(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("HGCTiming_SingleElectron_Pt50GeV.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("HGCTiming_SingleElectron_Pt50GeV.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("HGCTiming_SingleElectron_Pt50GeV.root:/hgctiming");
      dir->GetObject("HGCTiming",tree);

   }
   Init(tree);
}

HGCTiming::~HGCTiming()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t HGCTiming::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t HGCTiming::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void HGCTiming::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   recHit_energy = 0;
   recHit_x = 0;
   recHit_y = 0;
   recHit_z = 0;
   recHit_time = 0;
   uncRecHit_time = 0;
   GenVertex = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("cell_n", &cell_n, &b_cell_n);
   fChain->SetBranchAddress("cell_id", cell_id, &b_cell_id);
   fChain->SetBranchAddress("cell_subdet", cell_subdet, &b_cell_subdet);
   fChain->SetBranchAddress("cell_zside", cell_zside, &b_cell_zside);
   fChain->SetBranchAddress("cell_layer", cell_layer, &b_cell_layer);
   fChain->SetBranchAddress("cell_wafer", cell_wafer, &b_cell_wafer);
   fChain->SetBranchAddress("cell_wafertype", cell_wafertype, &b_cell_wafertype);
   fChain->SetBranchAddress("cell_cell", cell_cell, &b_cell_cell);
   fChain->SetBranchAddress("cell_moduleid", cell_moduleid, &b_cell_moduleid);
   fChain->SetBranchAddress("cell_triggercellid", cell_triggercellid, &b_cell_triggercellid);
   fChain->SetBranchAddress("cell_digi", cell_digi, &b_cell_digi);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumi", &lumi, &b_lumi);
   fChain->SetBranchAddress("vertex_x", &vertex_x, &b_vertex_x);
   fChain->SetBranchAddress("vertex_y", &vertex_y, &b_vertex_y);
   fChain->SetBranchAddress("vertex_z", &vertex_z, &b_vertex_z);
   fChain->SetBranchAddress("recHit_energy", &recHit_energy, &b_recHit_energy);
   fChain->SetBranchAddress("recHit_x", &recHit_x, &b_recHit_x);
   fChain->SetBranchAddress("recHit_y", &recHit_y, &b_recHit_y);
   fChain->SetBranchAddress("recHit_z", &recHit_z, &b_recHit_z);
   fChain->SetBranchAddress("recHit_time", &recHit_time, &b_recHit_time);
   fChain->SetBranchAddress("uncRecHit_time", &uncRecHit_time, &b_uncRecHit_time);
   fChain->SetBranchAddress("GenVertex", &GenVertex, &b_GenVertex);
   fChain->SetBranchAddress("dist2center", &dist2center, &b_dist2center);
   Notify();
}

Bool_t HGCTiming::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void HGCTiming::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t HGCTiming::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef HGCTiming_cxx
