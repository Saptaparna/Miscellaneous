#include "HGCTimingAnalyzer/HGCTimingAnalyzer/interface/HGCTimingAnalyzer.h"


bool sameVal(double a, double b)
{
  return fabs(a - b) < 1.000e-06;
}

HGCTimingAnalyzer::HGCTimingAnalyzer(const edm::ParameterSet& iConfig)
: srcGenParticles_ (consumes<std::vector<reco::GenParticle> >(iConfig.getParameter<edm::InputTag> ("srcGenParticles"))),
    srcSimTracks_ (consumes<std::vector<SimTrack> >(iConfig.getParameter<edm::InputTag> ("srcSimTracks"))), 
    srcSimVertices_ (consumes<std::vector<SimVertex> >(iConfig.getParameter<edm::InputTag> ("srcSimVertices"))),
    srcHepmcevent_ (consumes<edm::HepMCProduct>(iConfig.getParameter<edm::InputTag> ("srcHepmcevent"))),
    srcPFRecHit_ (consumes<std::vector<reco::PFRecHit> >(iConfig.getParameter<edm::InputTag> ("srcPFRecHit"))),
    srcCaloHit_ (consumes<std::vector<PCaloHit> >(iConfig.getParameter<edm::InputTag> ("srcCaloHit"))),
    srcUncalibratedRecHitEE_ (consumes<edm::SortedCollection<HGCUncalibratedRecHit> >(iConfig.getParameter<edm::InputTag> ("srcUncalibratedRecHitEE"))),
    srcUncalibratedRecHitHEB_ (consumes<edm::SortedCollection<HGCUncalibratedRecHit> >(iConfig.getParameter<edm::InputTag> ("srcUncalibratedRecHitHEB"))),
    srcUncalibratedRecHitHEF_ (consumes<edm::SortedCollection<HGCUncalibratedRecHit> >(iConfig.getParameter<edm::InputTag> ("srcUncalibratedRecHitHEF"))),
    srcDigiee_ (consumes<HGCEEDigiCollection>(iConfig.getParameter<edm::InputTag>("srcDigiee"))),
    srcDigifh_ (consumes<HGCHEDigiCollection>(iConfig.getParameter<edm::InputTag>("srcDigifh"))),
    srcDigibh_ (consumes<HGCHEDigiCollection>(iConfig.getParameter<edm::InputTag>("srcDigibh")))
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
           //if(sameVal(pfRecHit->at(k).energy(), 0.00138456)) std::cout << "pfRecHit->at(k).energy() = " << pfRecHit->at(k).energy() << std::endl;
           //if(pfRecHit->at(k).energy() > 0.25) std::cout << "pfRecHit->at(k).energy() = " << pfRecHit->at(k).energy() << std::endl;
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
           //if(sameVal(pfRecHit->at(k).energy(), 0.00138456)) std::cout << "pfRecHit->at(k).energy() = " << pfRecHit->at(k).energy() << std::endl;
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
  //code from Jean-Baptiste
  
  iSetup.get<IdealGeometryRecord>().get("HGCalEESensitive",es_info_.geom_ee);
  iSetup.get<IdealGeometryRecord>().get("HGCalHESiliconSensitive",es_info_.geom_fh);
  iSetup.get<IdealGeometryRecord>().get("HGCalHEScintillatorSensitive",es_info_.geom_bh);
  iSetup.get<IdealGeometryRecord>().get("HGCalEESensitive",es_info_.topo_ee);
  iSetup.get<IdealGeometryRecord>().get("HGCalHESiliconSensitive",es_info_.topo_fh);
  iSetup.get<IdealGeometryRecord>().get("HGCalHEScintillatorSensitive",es_info_.topo_bh);

  edm::Handle<HGCEEDigiCollection> ee_digis_h;
  edm::Handle<HGCHEDigiCollection> fh_digis_h;

  iEvent.getByToken(srcDigiee_,ee_digis_h);
  iEvent.getByToken(srcDigifh_,fh_digis_h);

  const HGCEEDigiCollection& ee_digis = *ee_digis_h;
  const HGCHEDigiCollection& fh_digis = *fh_digis_h;

  cellN_ = ee_digis.size() + fh_digis.size(); 
  setTreeCellSize(cellN_);
  size_t ic = 0;
  for(const auto& eedata : ee_digis)
  {
    const HGCalDetId id = eedata.id();
    const GlobalPoint& center = es_info_.geom_ee->getPosition(id); 
    cellId_            .get()[ic] = id.rawId();
    cellSubdet_        .get()[ic] = ForwardSubdetector::HGCEE;
    cellSide_          .get()[ic] = id.zside();
    cellLayer_         .get()[ic] = id.layer();
    cellWafer_         .get()[ic] = id.wafer();
    cellWaferType_     .get()[ic] = id.waferType();
    cellCell_          .get()[ic] = id.cell();
    cellModuleId_      .get()[ic] = 0;//modulePtr->moduleId();
    cellTriggerCellId_ .get()[ic] = 0;//triggerCellPtr->triggerCellId();
    cellDigi_          .get()[ic] = eedata[2].raw(); 
    cellX_             .get()[ic] = center.x();
    cellY_             .get()[ic] = center.y();
    cellZ_             .get()[ic] = center.z();
    cellEta_           .get()[ic] = center.eta();
    ic++; 
  } 

  for(const auto& fhdata : fh_digis)
  {
    const HGCalDetId id = fhdata.id();
    const GlobalPoint& center = es_info_.geom_fh->getPosition(id); 
    cellId_            .get()[ic] = id.rawId();
    cellSubdet_        .get()[ic] = ForwardSubdetector::HGCHEF;
    cellSide_          .get()[ic] = id.zside();
    cellLayer_         .get()[ic] = id.layer();
    cellWafer_         .get()[ic] = id.wafer();
    cellWaferType_     .get()[ic] = id.waferType();
    cellCell_          .get()[ic] = id.cell();
    cellModuleId_      .get()[ic] = 0;//modulePtr->moduleId();
    cellTriggerCellId_ .get()[ic] = 0;//triggerCellPtr->triggerCellId();
    cellDigi_          .get()[ic] = fhdata[2].raw(); 
    cellX_             .get()[ic] = center.x();
    cellY_             .get()[ic] = center.y();
    cellZ_             .get()[ic] = center.z();
    cellEta_           .get()[ic] = center.eta();
    ic++;
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
  cellId_             .reset(new int[1],   array_deleter<int>());
  cellSubdet_         .reset(new int[1],   array_deleter<int>());
  cellSide_           .reset(new int[1],   array_deleter<int>());
  cellLayer_          .reset(new int[1],   array_deleter<int>());
  cellWafer_          .reset(new int[1],   array_deleter<int>());
  cellWaferType_      .reset(new int[1],   array_deleter<int>());
  cellCell_           .reset(new int[1],   array_deleter<int>());
  cellModuleId_       .reset(new int[1],   array_deleter<int>());
  cellTriggerCellId_  .reset(new int[1],   array_deleter<int>());
  cellDigi_           .reset(new uint32_t[1],   array_deleter<uint32_t>());
  cellX_              .reset(new float[1], array_deleter<float>());
  cellY_              .reset(new float[1], array_deleter<float>());
  cellZ_              .reset(new float[1], array_deleter<float>());
  cellEta_            .reset(new float[1], array_deleter<float>());
  
  tree_->Branch("cell_n" , &cellN_ , "cell_n/I");
  tree_->Branch("cell_id"                   , cellId_                   .get() , "cell_id[cell_n]/I");
  tree_->Branch("cell_subdet"               , cellSubdet_               .get() , "cell_subdet[cell_n]/I");
  tree_->Branch("cell_zside"                , cellSide_                 .get() , "cell_zside[cell_n]/I");
  tree_->Branch("cell_layer"                , cellLayer_                .get() , "cell_layer[cell_n]/I");
  tree_->Branch("cell_wafer"                , cellWafer_                .get() , "cell_wafer[cell_n]/I");
  tree_->Branch("cell_wafertype"            , cellWaferType_            .get() , "cell_wafertype[cell_n]/I");
  tree_->Branch("cell_cell"                 , cellCell_                 .get() , "cell_cell[cell_n]/I");
  tree_->Branch("cell_moduleid"             , cellModuleId_             .get() , "cell_moduleid[cell_n]/I");
  tree_->Branch("cell_triggercellid"        , cellTriggerCellId_        .get() , "cell_triggercellid[cell_n]/I");
  tree_->Branch("cell_digi"                 , cellDigi_                 .get() , "cell_digi[cell_n]/i");
  tree_->Branch("cell_x"                    , cellX_                    .get() , "cell_x[cell_n]/F");
  tree_->Branch("cell_y"                    , cellY_                    .get() , "cell_y[cell_n]/F");
  tree_->Branch("cell_z"                    , cellZ_                    .get() , "cell_z[cell_n]/F");
  tree_->Branch("cell_eta"                  , cellEta_                  .get() , "cell_eta[cell_n]/F");
  
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

/*****************************************************************/
void HGCTimingAnalyzer::setTreeCellSize(const size_t n) 
/*****************************************************************/
{
  cellId_             .reset(new int[n],   array_deleter<int>());
  cellSubdet_         .reset(new int[n],   array_deleter<int>());
  cellSide_           .reset(new int[n],   array_deleter<int>());
  cellLayer_          .reset(new int[n],   array_deleter<int>());
  cellWafer_          .reset(new int[n],   array_deleter<int>());
  cellWaferType_      .reset(new int[n],   array_deleter<int>());
  cellCell_           .reset(new int[n],   array_deleter<int>());
  cellModuleId_       .reset(new int[n],   array_deleter<int>());
  cellTriggerCellId_  .reset(new int[n],   array_deleter<int>());
  cellDigi_           .reset(new uint32_t[n],   array_deleter<uint32_t>());
  cellX_              .reset(new float[n], array_deleter<float>());
  cellY_              .reset(new float[n], array_deleter<float>());
  cellZ_              .reset(new float[n], array_deleter<float>());
  cellEta_            .reset(new float[n], array_deleter<float>());
  
  tree_->GetBranch("cell_id")           ->SetAddress(cellId_             .get());
  tree_->GetBranch("cell_subdet")       ->SetAddress(cellSubdet_         .get());
  tree_->GetBranch("cell_zside")        ->SetAddress(cellSide_           .get());
  tree_->GetBranch("cell_layer")        ->SetAddress(cellLayer_          .get());
  tree_->GetBranch("cell_wafer")        ->SetAddress(cellWafer_          .get());
  tree_->GetBranch("cell_wafertype")    ->SetAddress(cellWaferType_      .get());
  tree_->GetBranch("cell_cell")         ->SetAddress(cellCell_           .get());
  tree_->GetBranch("cell_moduleid")     ->SetAddress(cellModuleId_       .get());
  tree_->GetBranch("cell_triggercellid")->SetAddress(cellTriggerCellId_  .get());
  tree_->GetBranch("cell_digi")         ->SetAddress(cellDigi_           .get());
  tree_->GetBranch("cell_x")            ->SetAddress(cellX_              .get());
  tree_->GetBranch("cell_y")            ->SetAddress(cellY_              .get());
  tree_->GetBranch("cell_z")            ->SetAddress(cellZ_              .get());
  tree_->GetBranch("cell_eta")          ->SetAddress(cellEta_            .get());
  
}

//define this as a plug-in
DEFINE_FWK_MODULE(HGCTimingAnalyzer);
