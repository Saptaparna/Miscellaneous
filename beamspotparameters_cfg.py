import FWCore.ParameterSet.Config as cms

process = cms.Process("BeamSpotParam")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
        'file:/uscms_data/d1/lpcljm/sapta/SUSYSearch/CMSSW_5_3_16_patch1/src/BeamSpotParameters/BeamSpotParameters/test/005221EF-0F18-E211-AD27-485B39800C23.root'
    )
)

process.beamspotparam = cms.EDAnalyzer('BeamSpotParameters')

process.p = cms.Path(process.beamspotparam)
