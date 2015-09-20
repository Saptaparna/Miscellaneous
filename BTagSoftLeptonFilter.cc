// -*- C++ -*-
//
// Package:    BTagSoftLeptonFilter
// Class:      BTagSoftLeptonFilter
// 
/**\class BTagSoftLeptonFilter BTagSoftLeptonFilter.cc BTagSoftLepton/BTagSoftLeptonFilter/src/BTagSoftLeptonFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  "Saptaparna Bhattacharya"
//         Created:  Wed Dec  3 18:36:18 CST 2008
// $Id: BTagSoftLeptonFilter.cc,v 1.3 2009/02/27 19:47:08 sapta Exp $
//
//


// system include files
#include <memory>

// user include files
#include "BTagTest/BTagSoftLeptonAnalyzer/interface/BTagSoftLeptonFilter.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"
#include "BTagTest/BTagSoftLeptonAnalyzer/interface/GluonSplittingToBBFinder.h"
#include "BTagTest/BTagSoftLeptonAnalyzer/interface/RooGKCounter.h"

using namespace std; 

using namespace reco;

using namespace pat;

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
BTagSoftLeptonFilter::BTagSoftLeptonFilter(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed

  jet_et_min = iConfig.getParameter<double>("jet_et_min");
  jet_eta_max = iConfig.getParameter<double>("jet_eta_max");
  
}


BTagSoftLeptonFilter::~BTagSoftLeptonFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
BTagSoftLeptonFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   bool result = false;

   event_count.count();
 
 Handle<vector<pat::Jet> > jets;
 iEvent.getByLabel("selectedLayer1Jets",jets);
 Handle<GenParticleCollection> GPC;
 iEvent.getByLabel("genParticles",GPC);
 const GenParticleCollection gpc = *(GPC.product());
 
   //_n_jets=jets->size();
   //cout << "Number of jets = " <<_n_jets<< endl;


 for(vector<pat::Jet>::const_iterator jet = jets -> begin(); jet != jets -> end(); jet ++){
   
   jet_count.count();
   
   double _energy_jets = jet->energy();
   //cout << "Energy of jet ="<< _energy_jets << endl;

   double _transverse_energy_jets = jet->et();
   
   if( _transverse_energy_jets > jet_et_min ){
     
     if (abs(jet->partonFlavour())==5){

       bjet_partonflavor_count1.count();

        result = true;

       cout <<  "b jets (Parton Flavor)= " << jet->partonFlavour() << endl;
     
     }

     GluonSplittingToBBFinder gbb;
     const reco::Jet rjet = jet->recJet();
     int _b_quark_status = gbb.has_b_quark(gpc, rjet, 0.4, 0.2 );
     int _nb_status = gbb.n_b_from_gluons(gpc, rjet, 0.4, 0.2, true);
     int _nb_tommaso = gbb.procDisc(gpc, rjet, 0.4, 0.6, false);
    
 
     if (_b_quark_status == 2){
       
       bjet_count.count();

       // result = true;
       
       cout << "Found b-quark with status: " << _b_quark_status << endl;
     }
     
     /*
     

     if (_nb_status == 3){
       cout << "Found 333333333333" << _nb_status << endl;
     }
     
     */
     
     if (_nb_tommaso == 3){

       result =  true;

       if (abs(jet->partonFlavour())==5){
	   bjet_partonflavor_count2.count();
	 }

       tommaso_count.count();

       //cout << "Parton Flavor" << jet->partonFlavour() << endl;

       cout << "Found 3!3!3!3!3!3!3!3!3!3!3!3!" << _nb_tommaso << endl;
     }
       
   
     //cout << "Transverse Energy of jet ="<< _transverse_energy_jets << endl;
     }

     
     
     
     
   }

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif

#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
   return result;
}

// ------------ method called once each job just before starting event loop  ------------
void 
BTagSoftLeptonFilter::beginJob(const edm::EventSetup&)
{

  // _file = new TFile("test.root", "RECREATE");

  //_tree = new TTree("Softlepton_test", "Softlepton_test", 64000000);

   //b_n_jets = _tree -> Branch("n_jets", &_n_jets, "n_jets/I" );


  jet_count.setPrintCount(true);
  jet_count.setDivider(100);
  bjet_partonflavor_count1.setPrintCount(true);
  bjet_partonflavor_count1.setDivider(100);
  bjet_count.setPrintCount(true);
  bjet_count.setDivider(100);
  tommaso_count.setPrintCount(true);
  tommaso_count.setDivider(100);
  bjet_partonflavor_count2.setPrintCount(true);
  bjet_partonflavor_count2.setDivider(100);


}

// ------------ method called once each job just after ending the event loop  ------------
void 
BTagSoftLeptonFilter::endJob() {

  cout << "===> Events processed: " << event_count.getCount() << endl;
  cout << "===> jets processed: " << jet_count.getCount() << endl;
  cout << "===> b-jets processed (parton flavor): " << bjet_partonflavor_count1.getCount() << endl;
  cout << "===> b-jets processed: " << bjet_count.getCount() << endl;
  cout << "===> tommaso: b-jets processed: " << tommaso_count.getCount() << endl; 
  cout << "===> tommaso b-jets processed (parton flavor): " << bjet_partonflavor_count2.getCount() << endl;

}

//define this as a plug-in
DEFINE_FWK_MODULE(BTagSoftLeptonFilter);
