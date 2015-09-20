
#include "BTagTest/BTagSoftLeptonAnalyzer/interface/BTagTestAnalyzer.h"


BTagTestAnalyzer::BTagTestAnalyzer(const ParameterSet& pSet)
{
  jetTag = pSet.getParameter<InputTag>( "jetTag" );
}

void 
BTagTestAnalyzer::analyze(const Event& iEvent, const EventSetup& iSetup)
{
  Handle< View<reco::Jet> > jets;
  iEvent.getByLabel("iterativeCone5CaloJets", jets); // get your jets
  Handle<reco::JetTagCollection> bJetTags;
  iEvent.getByLabel(jetTag, bJetTags); // b-tag algorithm

  for(unsigned int index = 0; index < jets->size(); ++index) {
    float disc = (*bJetTags)[jets->refAt(index)]; // get discriminator
    cout << "A jet with pt() = " << (*jets)[index].pt()
    << " has the b-tag discriminator = " << disc
    << endl;
  }

  Handle<reco::TrackIPTagInfoCollection> ipTagInfos;
  iEvent.getByLabel("impactParameterTagInfos", ipTagInfos);
  for(unsigned int index = 0; index < ipTagInfos->size(); ++index) {
     // get the jet which is used to compute the TagInfo
    RefToBase<reco::Jet> jet = (*ipTagInfos)[index].jet();
    reco::TrackRefVector tracks = (*ipTagInfos)[index].selectedTracks();
    vector<reco::TrackIPTagInfo::TrackIPData> data =
	(*ipTagInfos)[index].impactParameterData();
    for(unsigned int track = 0; track < tracks.size(); ++track) {
      cout << "A jet with pt(), phi(), eta(), energy() = " << jet->pt() << endl << jet->phi() << endl << jet->eta()  << endl << jet->energy() 
           <<  " has a track of pt() = " << tracks[track]->pt()
	   << " with a 2d IP of " << data[track].ip2d.value()
	   << endl;
    }
  }

  Handle<reco::SecondaryVertexTagInfoCollection> svTagInfos;
  iEvent.getByLabel("secondaryVertexTagInfos", svTagInfos);
  for(unsigned int index = 0; index < svTagInfos->size(); ++index) {
    RefToBase<reco::Jet> jet = (*svTagInfos)[index].jet();
    unsigned int nVertices = (*svTagInfos)[index].nVertices();
    cout << "A jet with pt() = " << jet->pt() << " contains "
	 << nVertices << " secondary vertices:" << endl;
    for(unsigned int i = 0; i < nVertices; ++i) {
      const reco::Vertex &vertex = (*svTagInfos)[index].secondaryVertex(i);
      cout << " at "<< vertex.position() << endl;
    }
  }
}


//define this as a plug-in
DEFINE_FWK_MODULE(BTagTestAnalyzer);
