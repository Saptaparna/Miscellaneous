// -*- C++ -*-
//
// Package:    BTagSoftLeptonAnalyzer
// Class:      BTagSoftLeptonAnalyzer
// 
/**\class BTagSoftLeptonAnalyzer BTagSoftLeptonAnalyzer.cc BTagTest/BTagSoftLeptonAnalyzer/src/BTagSoftLeptonAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  "Saptaparna Bhattacharya"
//         Created:  Fri Oct 17 14:34:49 CDT 2008
// $Id: BTagSoftLeptonAnalyzer.cc,v 1.2 2008/12/22 22:20:34 sapta Exp $
//
//



#include "BTagTest/BTagSoftLeptonAnalyzer/interface/BTagSoftLeptonAnalyzer.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/BTauReco/interface/SecondaryVertexTagInfo.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/TrackReco/interface/Track.h" 
#include "BTagTest/BTagSoftLeptonAnalyzer/interface/GluonSplittingToBBFinder.h"
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
BTagSoftLeptonAnalyzer::BTagSoftLeptonAnalyzer(const edm::ParameterSet& iConfig)

{
   //now do what ever initialization is needed

}


BTagSoftLeptonAnalyzer::~BTagSoftLeptonAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------


void
BTagSoftLeptonAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   cout << "BTagSoftLeptonAnalyzer::analyze(): beginning to analyze event #" << event_counter << endl;
   event_counter++;


// Handle<reco::CaloJetCollection> jets;
// iEvent.getByLabel("iterativeCone5CaloJets",jets);
   Handle<vector<pat::Jet> > jets;
   iEvent.getByLabel("selectedLayer1Jets",jets);
   Handle<GenParticleCollection> GPC;
   iEvent.getByLabel("genParticles",GPC);
   const GenParticleCollection gpc = *(GPC.product());

   _n_jets=jets->size();
   cout << "Number of jets = " <<_n_jets<< endl;
   
   for(vector<pat::Jet>::const_iterator jet = jets -> begin(); jet != jets -> end(); jet ++){
     
     _energy_jets = jet->energy();
     //  cout << "Energy of jet ="<< _energy_jets << endl;

     _transverse_energy_jets = jet->et();
     // cout << "Transverse Energy of jet ="<< _transverse_energy_jets << endl;
     
     _pt_jets = jet->pt();
     //cout << "Pt of jets ="<< _pt_jets << endl;	
     
     _eta_jets = jet->eta();
     // cout << "eta of jets="<< _eta_jets << endl;
     
     _phi_jets = jet->phi();
     // cout << "phi of jets="<< _phi_jets << endl;
     
     _parton_flavour = jet->partonFlavour();
     //cout << "Parton Flavor = " << _parton_flavour << endl;  

     _jet_category = 0;
     
     string tagger1 = "trackCountingHighEffBJetTags";
     string tagger2 = "softMuonBJetTags";

     float bDiscriminator1 = jet->bDiscriminator(tagger1);
     cout << "B-Discriminator for Track Counting Algorithm =" << bDiscriminator1 << endl;

     float bDiscriminator2 = jet->bDiscriminator(tagger2);
     cout << "B-Discriminator for Soft Lepton Algorithm =" << bDiscriminator2 << endl;

     string tag_info_label1 = "softMuon";
     const reco::SoftLeptonTagInfo * tag_info = jet-> tagInfoSoftLepton(tag_info_label1);
     if (tag_info){
       if (tag_info->leptons()>0){
	 cout << tag_info->properties(0).sip2d << endl ;
       }
     }
     else{
       //   cout << "Tag Info " << tag_info_label1 << "is not found!!!" << endl;
     }

     string tag_info_label2 = "secondaryVertex";
     
     const reco::SecondaryVertexTagInfo * tag_info2 = jet-> tagInfoSecondaryVertex(tag_info_label2);
     if (tag_info2){
       
       _n_vertices = jet->tagInfoSecondaryVertex(tag_info_label2)->nVertices();
     } 
     
     else{
       // cout << "no tag info object with the label " << tag_info_label2 << " found!" << endl;
     }
     
     if (tag_info2){
       
       _n_vertextracks = jet->tagInfoSecondaryVertex(tag_info_label2)->nVertexTracks();
     }
     
     else{
       // cout << "no tag info object with the label " << tag_info_label2 << " found!" << endl;
       
     }
     //cout << "N Vertices Secondary Vertex = " << _n_vertices << endl; 
     
     
     if ( _n_vertices != 0 ){
       const Vertex a_vertex = jet-> tagInfoSecondaryVertex(tag_info_label2)-> secondaryVertex ( 0 );
       
       
       _n_vertex_tracks_size = a_vertex.tracksSize();
       
       //cout << "Number of Vertex Tracks = " << a_vertex.tracksSize() << endl;
       
       _a_chi2 = a_vertex.chi2();
       
       //cout << "Chi-squared = " << a_vertex.chi2() << endl;
       
       _a_ndof = a_vertex.ndof();
       
       // cout << "Degrees of Freedom = " << a_vertex.ndof() << endl;
       
       _a_normalized_chi2 = a_vertex.normalizedChi2();
       
       //cout << "Normalized Chi-squared  = " << a_vertex.normalizedChi2() << endl;
       
     }
     
     const reco::TrackRefVector & a_vector_of_tracks = jet -> associatedTracks();
     
      _n_jet_tracks = a_vector_of_tracks.size();
     
      //cout << "Total number of tracks for a jet = " <<  a_vector_of_tracks.size() << endl;

     _max_dR = -10;

     for (reco::TrackRefVector::const_iterator track1 = a_vector_of_tracks.begin(); track1 != a_vector_of_tracks.end(); track1++){
       
       for (reco::TrackRefVector::const_iterator track2 = track1 + 1; track2 != a_vector_of_tracks.end(); track2++){
	 
	 
	 //cout << "track pair " << endl;
	 
	 TrackRef _track1 = *track1;
	 TrackRef _track2 = *track2;
	 double track1eta = _track1->eta();
	 double track2eta = _track2->eta();
	 
	 double track1phi = _track1->phi();
	 double track2phi = _track2->phi();

	 double delta_eta = track1eta - track2eta;
	 double delta_phi = track1phi - track1phi;
	 
	 if (delta_phi > 3.1419265){
	   delta_phi = delta_phi - 2*3.1419265;
	 }
	 
	 double dR = sqrt((delta_eta)*(delta_eta) + (delta_phi)*(delta_phi));
	
	 if (_max_dR < dR){
	   _max_dR = dR;
	   cout << "_max_dR" << _max_dR << endl; 
	 }
	 
        
	 
       }
       
     }
     
     
     GluonSplittingToBBFinder gbb;
     const reco::Jet rjet = jet->recJet();
     _nb_status = gbb.n_b_from_gluons(gpc, rjet, 0.4, 0.5, true);
     _nb_tommaso = gbb.procDisc(gpc, rjet, 0.4, 0.0, false);
 

     if (_nb_status == 3){

       cout << "Found 333333333333" << _nb_status << endl;}

     if (_nb_tommaso == 3){

       cout << "Found 3!3!3!3!3!3!3!3!3!3!3!3!" << _nb_tommaso << endl;}
     
     
     _tree->Fill();    
     
   }
   
   
   
}


void BTagSoftLeptonAnalyzer::beginJob(const edm::EventSetup&)
{  
  _file = new TFile("test.root", "RECREATE");

  _tree = new TTree("Softlepton_test", "Softlepton_test", 64000000);

  event_counter = 0; 
 
 b_n_jets = _tree -> Branch("n_jets", &_n_jets, "n_jets/I" );

 b_energy_jets = _tree -> Branch("energy_jets", &_energy_jets, "energy_jets/D" );

 b_transverse_energy_jets = _tree -> Branch("transverse_energy_jets", &_transverse_energy_jets, "transverse_energy_jets/D" );

 b_pt_jets = _tree->Branch("pt_jets", &_pt_jets, "pt_jets/D");

 b_eta_jets = _tree -> Branch("eta_jets", &_eta_jets, "eta_jets/D");

 b_phi_jets = _tree -> Branch("phi_jets", &_phi_jets, "phi_jets/D");

 b_n_vertices = _tree -> Branch("n_vertices", &_n_vertices, "n_vertices/I" );
 
 // b_n_vertextracks = _tree -> Branch("n_vertextracks", &_n_vertextracks, "n_vertextracks/I" );

 b_n_vertex_tracks_size = _tree -> Branch("n_vertex_tracks_size", &_n_vertex_tracks_size, "n_vertex_tracks_size/I" );

 b_a_chi2 =  _tree -> Branch("a_chi2", &_a_chi2, "a_chi2/D" ); 

 b_a_ndof =  _tree -> Branch("a_ndof", &_a_ndof, "a_dof/D" );

 b_a_normalized_chi2 = _tree -> Branch("a_normalized_chi2", &_a_normalized_chi2, "a_normalized_chi2/D" );  

 b_n_jet_tracks = _tree-> Branch("n_jet_tracks", &_n_jet_tracks, "n_jet_tracks/I" );  

 b_max_dR = _tree-> Branch("max_dR", &_max_dR, "max_dR/D");

 b_event_counter = _tree-> Branch("event_counter", &event_counter, "event_counter/I");

 b_parton_flavour = _tree->Branch("parton_flavour", &_parton_flavour, "parton_flavour/I");

 b_jet_category = _tree->Branch("jet_category", &_jet_category, "jet_category/I");

 b_nb_status = _tree->Branch("nb_status", &_nb_status, "nb_status/I");

 b_nb_tommaso = _tree->Branch("nb_tommaso", &_nb_tommaso, "nb_tommaso/I");



}














// ------------ method called once each job just after ending the event loop  ------------
void 
BTagSoftLeptonAnalyzer::endJob() {

_file -> Write();
_file -> Close();

}

//define this as a plug-in
DEFINE_FWK_MODULE(BTagSoftLeptonAnalyzer);
