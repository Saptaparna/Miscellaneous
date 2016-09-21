#include "HGCTimingAnalyzer/HGCTimingAnalyzer/interface/HGCTimingAnalyzer.h"


bool sameVal(double a, double b)
{
  return fabs(a - b) < 1.000e-06;
}

HGCTimingAnalyzer::HGCTimingAnalyzer(const edm::ParameterSet& iConfig)
: srcGenParticles_ (consumes<std::vector<reco::GenParticle> >(iConfig.getParameter<edm::InputTag> ("srcGenParticles"))),
    srcSimTracks_ (consumes<std::vector<SimTrack> >(iConfig.getParameter<edm::InputTag> ("srcSimTracks"))), 
    srcSimVertices_ (consumes<std::vector<SimVertex> >(iConfig.getParameter<edm::InputTag> ("srcSimVertices"))),
    srcPFRecHit_ (consumes<std::vector<reco::PFRecHit> >(iConfig.getParameter<edm::InputTag> ("srcPFRecHit"))),
    srcSimCluster_ (consumes<std::vector<SimCluster> >(iConfig.getParameter<edm::InputTag> ("srcSimCluster")))
    //srcDigiee_ (consumes<HGCEEDigiCollection>(iConfig.getParameter<edm::InputTag>("srcDigiee"))),
    //srcDigifh_ (consumes<HGCHEDigiCollection>(iConfig.getParameter<edm::InputTag>("srcDigifh"))),
    //srcDigibh_ (consumes<HGCHEDigiCollection>(iConfig.getParameter<edm::InputTag>("srcDigibh")))
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
   recHit_energy.clear();
   recHit_time.clear();
   recHit_layer.clear();

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
     double eta = simTk->at(j).momentum().eta();
     if (simTk->at(j).noVertex()) continue;
     int vertIndex = simTk->at(j).vertIndex();
     vertex_x = simVtx->at(vertIndex).position().x();
     vertex_y = simVtx->at(vertIndex).position().y();
     vertex_z = simVtx->at(vertIndex).position().z();
   }
   /*
   for(size_t i = 0; i < genParticles->size(); ++ i)
   {
     const reco::GenParticle & p = dynamic_cast<const reco::GenParticle &>((*genParticles)[i]);
   }
   */ 
   edm::Handle<std::vector<reco::PFRecHit> > pfRecHit;
   iEvent.getByToken(srcPFRecHit_, pfRecHit);
   
   edm::Handle<std::vector<SimCluster> > simCluster;
   iEvent.getByToken(srcSimCluster_, simCluster); 

   edm::ESHandle<HGCalGeometry> geoHandle;
   iSetup.get<IdealGeometryRecord>().get("HGCalEESensitive",geoHandle);

   for(unsigned int l=0; l<simCluster->size(); l++) // Iterating over sim clusters
   {
     for (int ih=0;ih<simCluster->at(l).numberOfRecHits();++ih)
     {
       uint32_t id = simCluster->at(l).hits_and_fractions().at(ih).first;
       unsigned int i_pfRecHit=0;
       while (i_pfRecHit<pfRecHit->size() && pfRecHit->at(i_pfRecHit).detId()!=id) ++i_pfRecHit;
       if (i_pfRecHit!=pfRecHit->size()) // this means we have matched a PFRecHit to the sim
       {
         const GlobalPoint& center = geoHandle->getPosition(id); 
         if(pfRecHit->at(i_pfRecHit).time() > 0) 
         {
           recHit_time.push_back(pfRecHit->at(i_pfRecHit).time());
           recHit_energy.push_back(pfRecHit->at(i_pfRecHit).energy());
           recHit_layer.push_back(pfRecHit->at(i_pfRecHit).layer());
           recHit_x.push_back(center.x());
           recHit_y.push_back(center.y());
           recHit_z.push_back(center.z());
           double rho = sqrt((fabs(center.x()) - 34.0)*(fabs(center.x()) - 34.0) + center.y()*center.y());
           if(rho > 20 and rho < 30) std::cout << "rho = " << rho << std::endl;
           if(rho > 20 and rho < 30) std::cout << "fabs(center.x()) = " << fabs(center.x()) << std::endl;
           if(rho > 20 and rho < 30) std::cout << "fabs(center.y()) = " << fabs(center.y()) << std::endl; 
         }
       }
     }
   }

   tree_->Fill();
}


// ------------ method called once each job just before starting event loop  ------------
void 
HGCTimingAnalyzer::beginJob()
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
  branch_=tree_->Branch("recHit_time", &recHit_time);
  branch_=tree_->Branch("recHit_layer", &recHit_layer);
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
