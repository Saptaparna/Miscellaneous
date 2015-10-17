from CRABClient.UserUtilities import config, getUsernameFromSiteDB
config = config()

config.General.requestName = 'QBH_ADD_MD_4_MQBH_5_n_3_MiniAOD'
config.General.workArea = 'QBH_ADD_MD_4_MQBH_5_n_3_MiniAOD'
config.General.transferOutputs = True
config.General.transferLogs = True

config.Data.inputDataset = '/QBH_ADD_MD_4_MQBH_5_n_3/sapta-QBH_ADD_MD_4_MQBH_5_n_3-43efd47f54c11c6efdc1cb52f92c16e7/USER'
config.Data.inputDBS = 'phys03'
config.JobType.psetName = 'QBH_ADD_MD_4_MQBH_5_n_3_MiniAOD.py'
config.JobType.maxMemoryMB = 2500

config.Data.splitting = 'FileBased'
config.Data.unitsPerJob = 135
NJOBS = 75
config.Data.totalUnits = config.Data.unitsPerJob * NJOBS
config.Data.publication = True
config.Data.outLFNDirBase = '/store/user/sapta/BlackHoleAnalysis_MiniAOD/'

config.Data.ignoreLocality = True
config.Data.publishDBS = 'https://cmsweb.cern.ch/dbs/prod/phys03/DBSWriter/'
config.Data.publishDataName = 'QBH_ADD_MD_4_MQBH_5_n_3_MiniAOD'

config.section_("Site")
config.Site.storageSite = 'T3_US_FNALLPC'
config.Site.whitelist = ['T3_US_FNALLPC']
