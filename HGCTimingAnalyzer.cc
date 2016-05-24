#include "HGCTimingAnalyzer/HGCTimingAnalyzer/interface/HGCTimingAnalyzer.h"


HGCTimingAnalyzer::HGCTimingAnalyzer(const edm::ParameterSet& iConfig)
: srcGenParticles_ (consumes<std::vector<reco::GenParticle> >(iConfig.getParameter<edm::InputTag> ("srcGenParticles"))),
    srcSimTracks_ (consumes<std::vector<SimTrack> >(iConfig.getParameter<edm::InputTag> ("srcSimTracks"))), 
    srcSimVertices_ (consumes<std::vector<SimVertex> >(iConfig.getParameter<edm::InputTag> ("srcSimVertices"))),
    srcHepmcevent_ (consumes<edm::HepMCProduct>(iConfig.getParameter<edm::InputTag> ("srcHepmcevent"))),
    srcPFRecHit_ (consumes<std::vector<reco::PFRecHit> >(iConfig.getParameter<edm::InputTag> ("srcPFRecHit"))),
    srcCaloHit_ (consumes<std::vector<PCaloHit> >(iConfig.getParameter<edm::InputTag> ("srcCaloHit"))),
    srcUncalibratedRecHitEE_ (consumes<edm::SortedCollection<HGCUncalibratedRecHit> >(iConfig.getParameter<edm::InputTag> ("srcUncalibratedRecHitEE"))),
    srcUncalibratedRecHitHEB_ (consumes<edm::SortedCollection<HGCUncalibratedRecHit> >(iConfig.getParameter<edm::InputTag> ("srcUncalibratedRecHitHEB"))),
    srcUncalibratedRecHitHEF_ (consumes<edm::SortedCollection<HGCUncalibratedRecHit> >(iConfig.getParameter<edm::InputTag> ("srcUncalibratedRecHitHEF")))
{
   usesResource("TFileService");
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
   recHit_recoDetId.clear();   
   uncRecHit_time.clear();
   dist2center_ = -99999.0;

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
   // get the gen particles
   edm::Handle<edm::HepMCProduct>  hepmcevent;
   iEvent.getByToken(srcHepmcevent_, hepmcevent);
   const HepMC::GenEvent& genevt = hepmcevent->getHepMCData();
   genVertex_->SetXYZT(0.,0.,0.,0.);

   if( genevt.vertices_size() > 0.0)
   {
     HepMC::FourVector temp = (*genevt.vertices_begin())->position() ;
     genVertex_->SetXYZT(0.1*temp.x(),0.1*temp.y(),0.1*temp.z(),temp.t()/299.792458); // convert positions to cm and time to ns (it's in mm to start with)

     dist2center_ = sqrt((vertex_x - temp.x())*(vertex_x - temp.x()) + (vertex_y - temp.y())*(vertex_y - temp.y()) + (vertex_z - temp.z())*(vertex_z - temp.z()));
   }
   /*
   for(size_t i = 0; i < genParticles->size(); ++ i)
   {
     const reco::GenParticle & p = dynamic_cast<const reco::GenParticle &>((*genParticles)[i]);
   }
   */
   edm::Handle<std::vector<reco::PFRecHit> > pfRecHit;
   iEvent.getByToken(srcPFRecHit_, pfRecHit);

   edm::Handle<edm::SortedCollection<HGCUncalibratedRecHit> > srcUncalibratedRecHitEE;
   iEvent.getByToken(srcUncalibratedRecHitEE_, srcUncalibratedRecHitEE);

   edm::Handle<edm::SortedCollection<HGCUncalibratedRecHit> > srcUncalibratedRecHitHEB;
   iEvent.getByToken(srcUncalibratedRecHitHEB_, srcUncalibratedRecHitHEB);

   edm::Handle<edm::SortedCollection<HGCUncalibratedRecHit> > srcUncalibratedRecHitHEF;
   iEvent.getByToken(srcUncalibratedRecHitHEF_, srcUncalibratedRecHitHEF);

   for (unsigned int k=0; k<pfRecHit->size(); k++)
   { 
     DetId detId_recHit(pfRecHit->at(k).detId());
     edm::SortedCollection<HGCUncalibratedRecHit>::const_iterator hgchitEE = srcUncalibratedRecHitEE->find(detId_recHit);
     if(hgchitEE != srcUncalibratedRecHitEE->end())
     {
       DetId detId_uncHit = hgchitEE->id();
       if(detId_recHit.rawId()==detId_uncHit.rawId())
       {
         if(pfRecHit->at(k).time()>0)//hgchit->jitter() for timing information 
         { 
           recHit_x.push_back(pfRecHit->at(k).position().x());
           recHit_y.push_back(pfRecHit->at(k).position().y());
           recHit_z.push_back(pfRecHit->at(k).position().z());
           recHit_energy.push_back(pfRecHit->at(k).energy());
           recHit_recoDetId.push_back(pfRecHit->at(k).detId());
           recHit_time.push_back(pfRecHit->at(k).time());
           uncRecHit_time.push_back(hgchitEE->jitter());
         }        
       }
     }
     edm::SortedCollection<HGCUncalibratedRecHit>::const_iterator hgchitHEB = srcUncalibratedRecHitHEB->find(detId_recHit);
     if(hgchitHEB != srcUncalibratedRecHitHEB->end())
     { 
       DetId detId_uncHit = hgchitHEB->id();  
       if(detId_recHit.rawId()==detId_uncHit.rawId())
       {
         if(pfRecHit->at(k).time()>0)
         {
           recHit_x.push_back(pfRecHit->at(k).position().x());
           recHit_y.push_back(pfRecHit->at(k).position().y());
           recHit_z.push_back(pfRecHit->at(k).position().z());
           recHit_energy.push_back(pfRecHit->at(k).energy());
           recHit_recoDetId.push_back(pfRecHit->at(k).detId());
           recHit_time.push_back(pfRecHit->at(k).time());
           uncRecHit_time.push_back(hgchitHEB->jitter());
         }
       }
     }
     edm::SortedCollection<HGCUncalibratedRecHit>::const_iterator hgchitHEF = srcUncalibratedRecHitHEF->find(detId_recHit);
     if(hgchitHEF != srcUncalibratedRecHitHEF->end())
     {
       DetId detId_uncHit = hgchitHEF->id();
       if(detId_recHit.rawId()==detId_uncHit.rawId())
       {
         if(pfRecHit->at(k).time()>0)
         {
           recHit_x.push_back(pfRecHit->at(k).position().x());
           recHit_y.push_back(pfRecHit->at(k).position().y());
           recHit_z.push_back(pfRecHit->at(k).position().z());
           recHit_energy.push_back(pfRecHit->at(k).energy());
           recHit_recoDetId.push_back(pfRecHit->at(k).detId());
           recHit_time.push_back(pfRecHit->at(k).time());
           uncRecHit_time.push_back(hgchitHEF->jitter());
         }
       }
     }
   }

    
/*
   edm::ESHandle<HGCalDDDConstants> hgcaldddconstants;
   
   //iSetup.get<IdealGeometryRecord>().get("HGCalHESiliconSensitive", hgcaldddconstants);
   //iSetup.get<IdealGeometryRecord>().get("HGCalHEScintillatorSensitive", hgcaldddconstants);
   bool reco_ = true;
   const HGCalDDDConstants hgdc(*hgcaldddconstants);
   std::cout << " Layers = "    << hgdc.layers(reco_) 
	     << " Sectors = "   << hgdc.sectors()     << " Minimum Slope = "
	     << hgdc.minSlope() << std::endl;


   edm::ESHandle<HGCalGeometry> hefGeom;
   iSetup.get<IdealGeometryRecord>().get("HGCalHEScintillatorSensitive",hefGeom);
   //iSetup.get<IdealGeometryRecord>().get("HGCalHEScintillatorSensitive", hefGeom);
   //iSetup.get<IdealGeometryRecord>().get("HGCalEESensitive", hefGeom);
   const HGCalTopology &topo=hefGeom->topology();
   const HGCalDDDConstants &dddConst=topo.dddConstants(); 
   bool reco_ = true;

   std::cout << "dddConst.layers = " << dddConst.layers(reco_) 
             << " Sectors = "        << dddConst.sectors()     
             << " Minimum Slope = "  << dddConst.minSlope()
             << std::endl;

   for (edm::SortedCollection<HGCUncalibratedRecHit>::const_iterator uncHit = srcUncalibratedRecHitEE->begin(); uncHit != srcUncalibratedRecHitEE->end(); uncHit++)
   {
     DetId detid = uncHit->id(); 
     uint32_t subDetId = detid.subdetId();
     
   }*/

   

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
  branch_=tree_->Branch("uncRecHit_time", &uncRecHit_time);
  branch_=tree_->Branch("GenVertex", "TLorentzVector", &genVertex_);
  branch_=tree_->Branch("dist2center", &dist2center_, "dist2center/F");
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
