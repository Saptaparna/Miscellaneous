import FWCore.ParameterSet.Config as cms

process = cms.Process("BTagTest")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")

process.printDecay = cms.EDAnalyzer("ParticleDecayDrawer",
                                   src = cms.InputTag("prunedGenParticles"),
                                   printP4 = cms.untracked.bool(False),
                                   printPtEtaPhi = cms.untracked.bool(False),
                                   printVertex = cms.untracked.bool(False)
                                   )


process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
        #'file:/uscms_data/d2/sapta/work/TestForSteve/CMSSW_8_0_20/src/out_miniaod.root'
        'file:/uscms_data/d2/sapta/work/TestForSteve/CMSSW_8_0_20/src/001AFDCE-C33B-E611-B032-0025905D1C54.root',
        'file:/uscms_data/d2/sapta/work/TestForSteve/CMSSW_8_0_20/src/02432E02-C13B-E611-92DE-0025904C66EA.root',
        'file:/uscms_data/d2/sapta/work/TestForSteve/CMSSW_8_0_20/src/04105911-C73B-E611-BDF0-0025904C6788.root'
    )
)

process.TFileService = cms.Service("TFileService", fileName = cms.string('BTagTest.root'))

process.btagtest = cms.EDAnalyzer('GenParticleList',
                              srcGenParticles = cms.InputTag('prunedGenParticles'),
                              srcPatJets = cms.InputTag('slimmedJets')
)

#process.p = cms.Path(process.printDecay*process.btagtest)

process.p = cms.Path(process.btagtest)
