import FWCore.ParameterSet.Config as cms

process = cms.Process("myprocess")

process.load("CondCore.DBCommon.CondDBCommon_cfi") 
process.load ("RecoBTag.PerformanceDB.PoolBTagPerformanceDB062012")
process.load ("RecoBTag.PerformanceDB.BTagPerformanceDB062012")
#process.load ("RecoBTag.PerformanceDB.PoolBTagPerformanceDB1107")
#process.load ("RecoBTag.PerformanceDB.BTagPerformanceDB1107")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)
process.source = cms.Source("EmptySource")

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string("btag_performance.root")
                                   )


process.myrootwriter = cms.EDAnalyzer("BTagPerformaceRootProducerFromSQLITE",
                                      # modified analyzer:
                                      # if empty, take all available names
                                      names = cms.vstring(),
                                      #names = cms.vstring('TTBARDISCRIMBTAGCSV',
                                      #                    'TTBARWPBTAGCSVM'),
                                      index = cms.uint32(1001) # not used
                                      )


process.p = cms.Path(process.myrootwriter)
