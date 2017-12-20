// =============================================================================
// A simple analysis on Bacon ntuples
//
// Input arguments:
//   argv[1] => input bacon file name
//   argv[2] => number of entries
//   argv[3] => ...
//
// Users should inherit from BLTSelector and implement the three functions:
//   Begin()
//   Process()
//   Terminate()
// =============================================================================


#ifndef MULTILEPTONANALYZER_HH
#define MULTILEPTONANALYZER_HH

// Analysis tools
#include "BLT/BLTAnalysis/interface/BLTSelector.hh"
#include "BLT/BLTAnalysis/interface/BLTHelper.hh"
#include "BLT/BLTAnalysis/interface/Parameters.hh"
#include "BLT/BLTAnalysis/interface/Cuts.hh"
#include "BLT/BLTAnalysis/interface/TriggerSelector.hh"
#include "BLT/BLTAnalysis/interface/ParticleSelector.hh"
#include "BLT/BLTAnalysis/interface/WeightUtils.h"

#include "BLT/BLTAnalysis/interface/RoccoR.h"
#include "BLT/BLTAnalysis/interface/rochcor2016.h"

// BaconAna class definitions (might need to add more)
#include "BaconAna/Utils/interface/TTrigger.hh"

// ROOT headers
#include <TLorentzVector.h>
#include <TVector3.h>

// C++ headers
#include <string>
#include <vector>
#include <map>
#include <memory>
#include <iostream>
#include <cmath>
#include <cassert>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <regex>


class FatJetAnalyzer: public BLTSelector {
public:
    FatJetAnalyzer();
    ~FatJetAnalyzer();

    void   Begin(TTree *tree);
    Bool_t Process(Long64_t entry);
    void   Terminate();
    void   ReportPostBegin();
    void   ReportPostTerminate();

    TFile *outFile;
    TTree *outTree;

    // Lumi mask
    RunLumiRangeMap lumiMask;

    // rochester muon corrections
    rochcor2016 *muonCorr;

    // Params and cuts
    std::unique_ptr<Parameters>         params;
    std::unique_ptr<Cuts>               cuts;

    // Utilities
    std::unique_ptr<ParticleSelector>   particleSelector;
    std::unique_ptr<baconhep::TTrigger> trigger;
    std::unique_ptr<WeightUtils>        weights;

    std::vector<string> triggerNames;

    // Branches in the output file
    UInt_t runNumber, lumiSection, nPU, nPartons;
    ULong64_t evtNumber;
    Bool_t triggerStatus;
    Float_t eventWeight;

    TLorentzVector leptonOneP4, leptonTwoP4, jetP4, bjetP4, genJetP4, genBJetP4, fatJetP4, subLeadingJetP4;
    Float_t leptonOneIso, leptonTwoIso;
    Int_t leptonOneQ, leptonTwoQ;
    Int_t leptonOneFlavor, leptonTwoFlavor, jetFlavor, bjetFlavor, subLeadingJetFlavor;
    Bool_t leptonOneTrigger, leptonTwoTrigger;

    Float_t jetD0, bjetD0, subLeadingJetD0;
    Float_t bjetTag, jetTag, genJetTag, genBJetTag, subLeadingJetTag;
    Float_t met, metPhi;
    Float_t fatJetTrimMass, fatJetPrunMass, fatJetSD0, fatJetTau1, fatJetTau2, fatJetTau3;

    UInt_t nJets, nFwdJets, nBJets, nMuons, nElectrons, nfatJets;
    //ClassDef(FatJetAnalyzer,0);
};

//bool sort_by_higher_pt_pair(baconhep::TJet* jet1, baconhep::TJet* jet2)
//{
  //return jet1->pt > jet2->pt;   
//}

bool sort_by_higher_pt_pair(const std::pair<baconhep::TJet*, baconhep::TAddJet*>  &fatJet1, const std::pair<baconhep::TJet*, baconhep::TAddJet*> &fatJet2)
{  
  return fatJet1.first->pt > fatJet2.first->pt;
}
#endif  // MULTILEPTONANALYZER_HH
