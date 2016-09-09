// -*- C++ -*-
//
// Package:    HGCTimingAnalyzer/HGCTimingAnalyzer
// Class:      HGCTimingAnalyzer
// 
/**\class HGCTimingAnalyzer HGCTimingAnalyzer.cc HGCTimingAnalyzer/HGCTimingAnalyzer/plugins/HGCTimingAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Saptaparna Bhattacharya
//         Created:  Sun, 24 Apr 2016 01:18:28 GMT
//
//


// system include files
#ifndef HGCTIMINGANALYZER_H
#define HGCTIMINGANALYZER_H
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/Track/interface/SimTrack.h"
#include "SimDataFormats/Track/interface/SimTrackContainer.h"
#include "SimDataFormats/Vertex/interface/SimVertex.h"
#include "SimDataFormats/Vertex/interface/SimVertexContainer.h"
#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecHitFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFRecHitFraction.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlock.h"
#include "DataFormats/ParticleFlowReco/interface/PFBlockElementCluster.h"
#include "DataFormats/ParticleFlowReco/interface/PFClusterFwd.h"
#include "DataFormats/ParticleFlowReco/interface/PFCluster.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "SimDataFormats/CaloHit/interface/PCaloHit.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"
#include "SimG4CMS/Calo/interface/CaloHitID.h"
#include "DataFormats/ForwardDetId/interface/HGCalDetId.h"
#include "DetectorDescription/OfflineDBLoader/interface/GeometryInfoDump.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"
#include "SimDataFormats/TrackingHit/interface/PSimHit.h"
#include "SimDataFormats/TrackingHit/interface/PSimHitContainer.h"
#include "DataFormats/HGCRecHit/interface/HGCRecHitCollections.h"
#include "DataFormats/HGCDigi/interface/HGCDigiCollections.h"
#include "DataFormats/ForwardDetId/interface/HGCEEDetId.h"
#include "DataFormats/ForwardDetId/interface/HGCHEDetId.h"
#include "DataFormats/ForwardDetId/interface/HGCalDetId.h"
#include "RecoLocalCalo/HGCalRecProducers/interface/HGCalRecHitWorkerBaseClass.h"
#include "RecoLocalCalo/HGCalRecAlgos/interface/HGCalRecHitSimpleAlgo.h"
#include "Geometry/HGCalGeometry/interface/HGCalGeometry.h"
#include "Geometry/HGCalCommonData/interface/HGCalParameters.h"
#include "Geometry/HGCalCommonData/interface/HGCalDDDConstants.h"

#include "FWCore/Framework/interface/ESTransientHandle.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include <iterator>
#include <iostream>

#include "L1Trigger/L1THGCal/interface/HGCalTriggerGeometryBase.h"
#include "L1Trigger/L1THGCal/interface/HGCalTriggerFECodecBase.h"
#include "L1Trigger/L1THGCal/interface/HGCalTriggerBackendProcessor.h"

//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

namespace 
{  
  template<typename T>
  struct array_deleter
  {
    void operator () (T* arr) { delete [] arr; }
  };
}

class HGCTimingAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit HGCTimingAnalyzer(const edm::ParameterSet&);
      ~HGCTimingAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;
      void setTreeCellSize(const size_t);
      // ----------member data ---------------------------
      Int_t run_,event_,lumi_,vertex_nTracks;
      Float_t vertex_x, vertex_y, vertex_z, vertex_pt, vertex_nChi2;
      std::vector<float> recHit_x;
      std::vector<float> recHit_y; 
      std::vector<float> recHit_z;
      std::vector<float> recHit_energy; 
      std::vector<float> recHit_time;
      std::vector<uint32_t> recHit_recoDetId; 
      std::vector<float> uncRecHit_time;
      float dist2center_, tof_;
      TLorentzVector *genVertex_;
      TBranch *branch_;      
      TTree *tree_; 
      edm::EDGetTokenT<std::vector<reco::GenParticle> > srcGenParticles_;      
      edm::EDGetTokenT<std::vector<SimTrack> > srcSimTracks_;
      edm::EDGetTokenT<std::vector<SimVertex> > srcSimVertices_; 
      edm::EDGetTokenT<edm::HepMCProduct> srcHepmcevent_;
      edm::EDGetTokenT<std::vector<reco::PFRecHit> > srcPFRecHit_;
      edm::EDGetTokenT<std::vector<PCaloHit> > srcCaloHit_;
      edm::EDGetTokenT<edm::SortedCollection<HGCUncalibratedRecHit> > srcUncalibratedRecHitEE_; 
      edm::EDGetTokenT<edm::SortedCollection<HGCUncalibratedRecHit> > srcUncalibratedRecHitHEB_;
      edm::EDGetTokenT<edm::SortedCollection<HGCUncalibratedRecHit> > srcUncalibratedRecHitHEF_;
      edm::EDGetToken srcDigiee_, srcDigifh_, srcDigibh_;
      HGCalTriggerGeometryBase::es_info es_info_;
      std::unique_ptr<HGCalTriggerGeometryBase> triggerGeometry_;
      int cellN_;
      std::shared_ptr<int> cellId_;
      std::shared_ptr<int> cellSubdet_;
      std::shared_ptr<int> cellSide_;
      std::shared_ptr<int> cellLayer_;
      std::shared_ptr<int> cellWafer_;
      std::shared_ptr<int> cellWaferType_;
      std::shared_ptr<int> cellCell_;
      std::shared_ptr<int> cellModuleId_;
      std::shared_ptr<int> cellTriggerCellId_;
      std::shared_ptr<uint32_t> cellDigi_;
      std::shared_ptr<float>    cellX_;
      std::shared_ptr<float>    cellY_;
      std::shared_ptr<float>    cellZ_; 
      std::shared_ptr<float>    cellEta_;
      };
      //
      // //
      // // constants, enums and typedefs
      // //
      //
      // //
      // // static data member definitions
      // //
      //
      // //
      // // constructors and destructor
      // //
      //
#endif
