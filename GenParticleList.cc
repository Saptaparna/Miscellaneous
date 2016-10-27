// -*- C++ -*-
//
// Package:    GenParticleList/GenParticleList
// Class:      GenParticleList
// 
/**\class GenParticleList GenParticleList.cc GenParticleList/GenParticleList/plugins/GenParticleList.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Saptaparna Bhattacharya
//         Created:  Wed, 26 Oct 2016 05:08:56 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include"DataFormats/HepMCCandidate/interface/GenParticle.h"
#include"RecoEgamma/Examples/plugins/GsfElectronMCAnalyzer.h"
#include"FWCore/ParameterSet/interface/ParameterSet.h"
#include"FWCore/Framework/interface/EDAnalyzer.h"
#include"FWCore/Framework/interface/Event.h"
#include"DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include"TLorentzVector.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "DataFormats/JetReco/interface/PFJet.h"
#include "DataFormats/JetReco/interface/PFJetCollection.h"
#include "DataFormats/BTauReco/interface/JetTag.h"
#include "DataFormats/BTauReco/interface/CATopJetTagInfo.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
//


// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class GenParticleList : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit GenParticleList(const edm::ParameterSet&);
      ~GenParticleList();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      edm::EDGetTokenT<std::vector<reco::GenParticle> > srcGenParticles_;
      edm::EDGetTokenT<std::vector<pat::Jet> > srcPatJets_;
      TBranch *branch_;
      TTree *tree_;
      Int_t run_,event_,lumi_;
      std::vector<float> btag_csv;
      std::vector<float> btag_mva;
      // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
GenParticleList::GenParticleList(const edm::ParameterSet& iConfig)
: srcGenParticles_ (consumes<std::vector<reco::GenParticle> >(iConfig.getParameter<edm::InputTag> ("srcGenParticles"))),
  srcPatJets_ (consumes<std::vector<pat::Jet> >(iConfig.getParameter<edm::InputTag> ("srcPatJets")))
{
   usesResource("TFileService");

}


GenParticleList::~GenParticleList()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called for each event  ------------
void
GenParticleList::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   run_   = iEvent.id().run();
   event_ = iEvent.id().event();
   lumi_  = iEvent.luminosityBlock();
   btag_mva.clear();
   btag_csv.clear();

   Handle<std::vector<reco::GenParticle> > genParticles;
   iEvent.getByToken(srcGenParticles_, genParticles);

   for(size_t i = 0; i < genParticles->size(); ++ i)
   {
     const reco::GenParticle & p = dynamic_cast<const reco::GenParticle &>((*genParticles)[i]);
     //if(abs(p.pdgId())==5) std::cout << "p.pdgId() = " << p.pdgId() << std::endl;
   }
   Handle<std::vector<pat::Jet> > patJets;
   iEvent.getByToken(srcPatJets_, patJets);
   assert(patJets.isValid());
   for(unsigned int i=0; i<patJets->size(); i++)
   { 
     double csvb = patJets->at(i).bDiscriminator("pfCombinedInclusiveSecondaryVertexV2BJetTags");
     //if(csvb > 0) std::cout << "csvb = " << csvb << std::endl;
     double mvab = patJets->at(i).bDiscriminator("pfCombinedMVAV2BJetTags");
     //if(mvab > 0) std::cout << "mvab = " << mvab << std::endl;
     btag_mva.push_back(mvab);
     btag_csv.push_back(csvb);
   }
   tree_->Fill(); 
}


// ------------ method called once each job just before starting event loop  ------------
void 
GenParticleList::beginJob()
{
  edm::Service<TFileService> fs;
  tree_=fs->make<TTree>("BTagTest","BTagTest");
  branch_=tree_->Branch("run",   &run_,   "run/I");
  branch_=tree_->Branch("event", &event_, "event/I");
  branch_=tree_->Branch("lumi",  &lumi_,  "lumi/I");
  branch_=tree_->Branch("btag_mva", &btag_mva);
  branch_=tree_->Branch("btag_csv", &btag_csv);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GenParticleList::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
GenParticleList::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(GenParticleList);
