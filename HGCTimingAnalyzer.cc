#include "HGCTimingAnalyzer/HGCTimingAnalyzer/interface/HGCTimingAnalyzer.h"


bool sameVal(double a, double b)
{
  return fabs(a - b) < 1.000e-02;
}

HGCTimingAnalyzer::HGCTimingAnalyzer(const edm::ParameterSet& iConfig)
:   srcGenParticles_ (consumes<std::vector<reco::GenParticle> >(iConfig.getParameter<edm::InputTag> ("srcGenParticles"))),
    srcSimTracks_ (consumes<std::vector<SimTrack> >(iConfig.getParameter<edm::InputTag> ("srcSimTracks"))), 
    srcSimVertices_ (consumes<std::vector<SimVertex> >(iConfig.getParameter<edm::InputTag> ("srcSimVertices"))),
    srcPFRecHit_ (consumes<std::vector<reco::PFRecHit> >(iConfig.getParameter<edm::InputTag> ("srcPFRecHit"))),
    srcPFCluster_ (consumes<std::vector<reco::PFCluster> >(iConfig.getParameter<edm::InputTag> ("srcPFCluster"))),
    srcCaloParticle_ (consumes<std::vector<CaloParticle> >(iConfig.getParameter<edm::InputTag> ("srcCaloParticle"))),
    srcRecHitEE_ (consumes<edm::SortedCollection<HGCRecHit> >(iConfig.getParameter<edm::InputTag> ("srcRecHitEE"))),
    srcRecHitHEB_ (consumes<edm::SortedCollection<HGCRecHit> >(iConfig.getParameter<edm::InputTag> ("srcRecHitHEB"))),
    srcRecHitHEF_ (consumes<edm::SortedCollection<HGCRecHit> >(iConfig.getParameter<edm::InputTag> ("srcRecHitHEF")))
{
   usesResource("TFileService");
   const edm::ParameterSet& geometryConfig = iConfig.getParameterSet("TriggerGeometry");
   const std::string& trigGeomName = geometryConfig.getParameter<std::string>("TriggerGeometryName");
}


HGCTimingAnalyzer::~HGCTimingAnalyzer()
{
}

// ------------ method called for each event  ------------
void
HGCTimingAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   run_   = iEvent.id().run();
   event_ = iEvent.id().event();
   lumi_  = iEvent.luminosityBlock();

   vertex_x = -999.0;
   vertex_y = -999.0;
   vertex_z = -999.0;
   vertex_nTracks = 0;
   vertex_pt = 0.0;
   vertex_nChi2 = 0.0;
   recHit_x.clear();
   recHit_y.clear();
   recHit_z.clear();
   cluster_x.clear();
   cluster_y.clear();
   cluster_z.clear();
   cluster_energy.clear();
   cluster_time.clear();
   recHit_energy.clear();
   recHit_time.clear();
   cluster_layer.clear();
   genParticle_eta.clear();
   genParticle_phi.clear();
   simCluster_eta.clear();
   simCluster_phi.clear();
   simCluster_energy.clear();
   simCluster_pt.clear();
   simCluster_simEnergy.clear();

   edm::Handle<std::vector<SimTrack> > simTk;
   iEvent.getByToken(srcSimTracks_, simTk);
   edm::Handle<std::vector<SimVertex> > simVtx;
   iEvent.getByToken(srcSimVertices_, simVtx);
   edm::Handle<std::vector<reco::GenParticle> > genParticles;
   iEvent.getByToken(srcGenParticles_, genParticles);
 
   for (unsigned int j=0; j<simTk->size(); j++) 
   {
     double pt = simTk->at(j).momentum().pt();
     if(pt < 2.0) continue;
     //double eta = simTk->at(j).momentum().eta();
     if (simTk->at(j).noVertex()) continue;
     int vertIndex = simTk->at(j).vertIndex();
     vertex_x = simVtx->at(vertIndex).position().x();
     vertex_y = simVtx->at(vertIndex).position().y();
     vertex_z = simVtx->at(vertIndex).position().z();
   }
   
   /*const reco::GenParticle &p = (*genParticles)[0];
   genParticle_eta = p.eta();
   genParticle_phi = p.phi();
   */
   for(size_t i = 0; i < genParticles->size(); ++ i)
   {
     const reco::GenParticle & p = dynamic_cast<const reco::GenParticle &>((*genParticles)[i]);
     genParticle_eta.push_back(p.eta());
     genParticle_phi.push_back(p.phi());
   }
 
   //edm::SortedCollection<HGCRecHit,edm::StrictWeakOrdering<HGCRecHit> > hgcRecHit;
   //iEvent.getByToken(srchgcRecHit_, hgcRecHit);

   edm::Handle<edm::SortedCollection<HGCRecHit> > srcRecHitEE;
   iEvent.getByToken(srcRecHitEE_, srcRecHitEE);
   edm::Handle<edm::SortedCollection<HGCRecHit> > srcRecHitHEF;
   iEvent.getByToken(srcRecHitHEF_, srcRecHitHEF);
   edm::Handle<std::vector<reco::PFCluster> > pfCluster;
   iEvent.getByToken(srcPFCluster_, pfCluster); 
   edm::Handle<std::vector<CaloParticle> > caloParticle;
   iEvent.getByToken(srcCaloParticle_, caloParticle);
   edm::ESHandle<HGCalGeometry> geoHandle_ee;
   iSetup.get<IdealGeometryRecord>().get("HGCalEESensitive",geoHandle_ee);
   edm::ESHandle<HGCalGeometry> geoHandle_hef;
   iSetup.get<IdealGeometryRecord>().get("HGCalHESiliconSensitive",geoHandle_hef);

   //EE 
   for(unsigned int l=0; l<pfCluster->size(); l++) // Iterating over sim clusters
   {
     if(pfCluster->at(l).time() > std::numeric_limits<double>::min())
     { 
       cluster_x.push_back(pfCluster->at(l).position().X());
       cluster_y.push_back(pfCluster->at(l).position().Y());
       cluster_z.push_back(pfCluster->at(l).position().Z());
       cluster_energy.push_back(pfCluster->at(l).energy());
       cluster_time.push_back(pfCluster->at(l).time());
       cluster_layer.push_back(pfCluster->at(l).layer());
       for(unsigned ifrac = 0; ifrac < pfCluster->at(l).hitsAndFractions().size(); ifrac++)
       {
         uint32_t id = pfCluster->at(l).hitsAndFractions().at(ifrac).first;
         edm::SortedCollection<HGCRecHit>::const_iterator hgcHitEE = srcRecHitEE->find(id);
         if(hgcHitEE != srcRecHitEE->end())
         {
           DetId detId_recHit_ee = hgcHitEE->detid();
           if(id==detId_recHit_ee.rawId() and hgcHitEE->time() > 0)
           {
             const GlobalPoint& recHitPos_ee = geoHandle_ee->getPosition(id); 
             recHit_x.push_back(recHitPos_ee.x());
             recHit_y.push_back(recHitPos_ee.y());
             recHit_z.push_back(recHitPos_ee.z());
             recHit_energy.push_back(hgcHitEE->energy());
             recHit_time.push_back(hgcHitEE->time());
           }
         }
       }
       //HEF
       for(unsigned ifrac = 0; ifrac < pfCluster->at(l).hitsAndFractions().size(); ifrac++)
       {
         uint32_t id = pfCluster->at(l).hitsAndFractions().at(ifrac).first;
         edm::SortedCollection<HGCRecHit>::const_iterator hgcHitHEF = srcRecHitHEF->find(id);
         if(hgcHitHEF != srcRecHitHEF->end())
         {
           DetId detId_recHit_hef = hgcHitHEF->detid();
           if(id==detId_recHit_hef.rawId() and hgcHitHEF->time() > 0)
           {
             const GlobalPoint& recHitPos_hef = geoHandle_hef->getPosition(id);
             recHit_x.push_back(recHitPos_hef.x());
             recHit_y.push_back(recHitPos_hef.y());
             recHit_z.push_back(recHitPos_hef.z());
             recHit_energy.push_back(hgcHitHEF->energy());
             recHit_time.push_back(hgcHitHEF->time());
           }
         }
       }
     }
   }
   // loop over caloParticles based on https://github.com/CMS-HGCAL/reco-ntuples/blob/master/HGCalAnalysis/plugins/HGCalAnalysis.cc
   for (std::vector<CaloParticle>::const_iterator it_caloPart = caloParticle->begin(); it_caloPart != caloParticle->end(); ++it_caloPart) 
   {
     const SimClusterRefVector simClusterRefVector = it_caloPart->simClusters();
     std::vector<uint32_t> simClusterIndex;
     simCluster_eta.push_back(it_caloPart->eta());
     simCluster_phi.push_back(it_caloPart->phi());
     simCluster_energy.push_back(it_caloPart->energy());
     simCluster_pt.push_back(it_caloPart->pt());
     simCluster_simEnergy.push_back(it_caloPart->simEnergy());
   }
/*
   for(unsigned int k=0; k<pfRecHit->size(); k++)
   {
   std::cout << "pfRecHit->at(k).layer() = " << pfRecHit->at(k).layer() << std::endl;
   }*/
tree_->Fill();
}

// ------------ method called once each job just before starting event loop  ------------
void HGCTimingAnalyzer::beginJob()
{
  edm::Service<TFileService> fs;
  tree_=fs->make<TTree>("HGCTiming","HGCTiming");
  branch_=tree_->Branch("run",   &run_,   "run/I");
  branch_=tree_->Branch("event", &event_, "event/I");
  branch_=tree_->Branch("lumi",  &lumi_,  "lumi/I");
  branch_=tree_->Branch("vertex_x", &vertex_x, "vertex_x/F");
  branch_=tree_->Branch("vertex_y", &vertex_y, "vertex_y/F");
  branch_=tree_->Branch("vertex_z", &vertex_z, "vertex_z/F");
  branch_=tree_->Branch("recHit_energy", &recHit_energy);
  branch_=tree_->Branch("recHit_x", &recHit_x);
  branch_=tree_->Branch("recHit_y", &recHit_y);
  branch_=tree_->Branch("recHit_z", &recHit_z);
  branch_=tree_->Branch("cluster_x", &cluster_x);
  branch_=tree_->Branch("cluster_y", &cluster_y);
  branch_=tree_->Branch("cluster_z", &cluster_z);
  branch_=tree_->Branch("cluster_energy", &cluster_energy);
  branch_=tree_->Branch("cluster_time", &cluster_time);
  branch_=tree_->Branch("recHit_time", &recHit_time);
  branch_=tree_->Branch("cluster_layer", &cluster_layer);
  branch_=tree_->Branch("genParticle_eta", &genParticle_eta);
  branch_=tree_->Branch("genParticle_phi", &genParticle_phi);
  branch_=tree_->Branch("simCluster_eta", &simCluster_eta);
  branch_=tree_->Branch("simCluster_phi", &simCluster_phi);
  branch_=tree_->Branch("simCluster_energy", &simCluster_energy);
  branch_=tree_->Branch("simCluster_pt", &simCluster_pt);
  branch_=tree_->Branch("simCluster_simEnergy", &simCluster_simEnergy);
}

// ------------ method called once each job just after ending the event loop  ------------
	void 
HGCTimingAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HGCTimingAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
	//The following says we do not know what parameters are allowed so do no validation
	// Please change this to state exactly what you do use, even if it is no parameters
	edm::ParameterSetDescription desc;
	desc.setUnknown();
	descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HGCTimingAnalyzer);
