import FWCore.ParameterSet.Config as cms

process = cms.Process("HGCTiming")

process.load("CondCore.CondDB.CondDB_cfi")
process.load('Configuration.StandardSequences.Services_cff')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.Geometry.GeometryExtended2023D3Reco_cff')
process.load('Configuration.Geometry.GeometryExtended2023D3_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
# get uncalibrechits with weights method
process.load("RecoLocalCalo.HGCalRecProducers.HGCalUncalibRecHit_cfi")
#process.HGCalUncalibRecHit.HGCEEdigiCollection  = 'mix:HGCDigisEE'
#process.HGCalUncalibRecHit.HGCHEFdigiCollection = 'mix:HGCDigisHEfront'
#process.HGCalUncalibRecHit.HGCHEBdigiCollection = 'mix:HGCDigisHEback'

# get rechits e.g. from the weights
process.load("RecoLocalCalo.HGCalRecProducers.HGCalRecHit_cfi")
#process.HGCalRecHit.HGCEEuncalibRecHitCollection  = 'HGCalUncalibRecHit:HGCEEUncalibRecHits'
#process.HGCalRecHit.HGCHEFuncalibRecHitCollection = 'HGCalUncalibRecHit:HGCHEFUncalibRecHits'
#process.HGCalRecHit.HGCHEBuncalibRecHitCollection = 'HGCalUncalibRecHit:HGCHEBUncalibRecHits'

#process.HGCalHit = cms.Sequence(process.HGCalUncalibRecHit)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1))

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
          'file:/uscms_data/d1/sapta/work/HighGranularityCalorimeter/TimingStudies_8X/CMSSW_8_1_0_pre12/src/kLongTime_step3/step3_kLong_Pt100_n1000_part1_directional.root',
          'file:/uscms_data/d1/sapta/work/HighGranularityCalorimeter/TimingStudies_8X/CMSSW_8_1_0_pre12/src/kLongTime_step3/step3_kLong_Pt100_n1000_part2_directional.root',
          'file:/uscms_data/d1/sapta/work/HighGranularityCalorimeter/TimingStudies_8X/CMSSW_8_1_0_pre12/src/kLongTime_step3/step3_kLong_Pt100_n1000_part3_directional.root',
          'file:/uscms_data/d1/sapta/work/HighGranularityCalorimeter/TimingStudies_8X/CMSSW_8_1_0_pre12/src/kLongTime_step3/step3_kLong_Pt100_n1000_part4_directional.root',
          'file:/uscms_data/d1/sapta/work/HighGranularityCalorimeter/TimingStudies_8X/CMSSW_8_1_0_pre12/src/kLongTime_step3/step3_kLong_Pt100_n1000_part5_directional.root',
          'file:/uscms_data/d1/sapta/work/HighGranularityCalorimeter/TimingStudies_8X/CMSSW_8_1_0_pre12/src/kLongTime_step3/step3_kLong_Pt100_n1000_part6_directional.root',
          'file:/uscms_data/d1/sapta/work/HighGranularityCalorimeter/TimingStudies_8X/CMSSW_8_1_0_pre12/src/kLongTime_step3/step3_kLong_Pt100_n1000_part7_directional.root',
          'file:/uscms_data/d1/sapta/work/HighGranularityCalorimeter/TimingStudies_8X/CMSSW_8_1_0_pre12/src/kLongTime_step3/step3_kLong_Pt100_n1000_part8_directional.root',
          'file:/uscms_data/d1/sapta/work/HighGranularityCalorimeter/TimingStudies_8X/CMSSW_8_1_0_pre12/src/kLongTime_step3/step3_kLong_Pt100_n1000_part9_directional.root',
          'file:/uscms_data/d1/sapta/work/HighGranularityCalorimeter/TimingStudies_8X/CMSSW_8_1_0_pre12/src/kLongTime_step3/step3_kLong_Pt100_n1000_part10_directional.root'
    )
)

process.TFileService = cms.Service("TFileService", fileName = cms.string('HGCTiming_SinglekLong_Pt100GeV_NoSmearing_directional.root'))

process.content = cms.EDAnalyzer("EventContentAnalyzer")

process.hgctiming = cms.EDAnalyzer('HGCTimingAnalyzer',
                                   srcGenParticles = cms.InputTag('genParticles'),
                                   srcSimTracks = cms.InputTag('g4SimHits'),
                                   srcSimVertices = cms.InputTag('g4SimHits'),
                                   srcPFRecHit = cms.InputTag('particleFlowRecHitHGC', 'Cleaned'),
                                   srcPFCluster = cms.InputTag('particleFlowClusterHGCal'),
                                   srcRecHitEE = cms.InputTag('HGCalRecHit', 'HGCEERecHits'),
                                   srcRecHitHEB = cms.InputTag('HGCalRecHit', 'HGCHEBRecHits'),
                                   srcRecHitHEF = cms.InputTag('HGCalRecHit', 'HGCHEFRecHits'),
                                   srcCaloParticle = cms.InputTag('mix', 'MergedCaloTruth'),
                                   TriggerGeometry = cms.PSet(
                                       TriggerGeometryName = cms.string('HGCalTriggerGeometryImp1'),
                                       L1TCellsMapping = cms.FileInPath("L1Trigger/L1THGCal/data/cellsToTriggerCellsMap.txt"),
                                       ),
                                  )

process.p = cms.Path(process.hgctiming)
