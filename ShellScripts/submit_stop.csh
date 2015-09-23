#! /bin/tcsh

# DATA, 260 jobs
./condor_submit.py --is-data -c stop_cfg.py -d /SingleMu/StoreResults-SingleMu_Run2012A-13Jul2012-v1_TLBSM_53x_v2_jsonfix-e3fb55b810dc7a0811f4c66dfa2267c9/USER
./condor_submit.py --is-data -c stop_cfg.py -d /SingleMu/StoreResults-Run2012A-recover-06Aug2012-v1_TLBSM_53x_v2-e3fb55b810dc7a0811f4c66dfa2267c9/USER
./condor_submit.py --is-data -c stop_cfg.py -d /SingleMu/StoreResults-Run2012B-13Jul2012-v1_TLBSM_53x_v2-e3fb55b810dc7a0811f4c66dfa2267c9/USER
./condor_submit.py --is-data -c stop_cfg.py -d /SingleMu/StoreResults-Run2012C-24Aug2012-v1_TLBSM_53x_v2-e3fb55b810dc7a0811f4c66dfa2267c9/USER
./condor_submit.py --is-data -c stop_cfg.py -d /SingleMu/StoreResults-Run2012C-PromptReco-v2_TLBSM_53x_v2-e3fb55b810dc7a0811f4c66dfa2267c9/USER
./condor_submit.py --is-data -c stop_cfg.py -d /SingleMu/StoreResults-Run2012C-PromptReco-v2_TLBSM_53x_v2-646f7563e9ae6f48814faa1c250f042a/USER
./condor_submit.py --is-data -c stop_cfg.py -d /SingleMu/StoreResults-Run2012C-PromptReco-v2_TLBSM_53x_v2_extension_v1-e3fb55b810dc7a0811f4c66dfa2267c9/USER
./condor_submit.py --is-data -c stop_cfg.py --dbs-instance 'http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_02/servlet/DBSServlet' -d /SingleMu/jpilot-Run2012C-EcalRecover_11Dec2012-v1_TLBSM_53x_v2-e3fb55b810dc7a0811f4c66dfa2267c9/USER
./condor_submit.py --is-data -c stop_cfg.py -d /SingleMu/StoreResults-Run2012D-PromptReco-v1_TLBSM_53x_v2-e3fb55b810dc7a0811f4c66dfa2267c9/USER
./condor_submit.py --is-data -c stop_cfg.py -d /SingleMu/StoreResults-Run2012D-PromptReco-v1_TLBSM_53x_v2_extension_v1-e3fb55b810dc7a0811f4c66dfa2267c9/USER
./condor_submit.py --is-data -c stop_cfg.py -d /SingleMu/StoreResults-Run2012D-PromptReco-v1_TLBSM_53x_v2_extension_v2-e3fb55b810dc7a0811f4c66dfa2267c9/USER

# BG MC, 114 jobs
./condor_submit.py --is-mc -c stop_cfg.py -d /TTJets_MassiveBinDECAY_TuneZ2star_8TeV-madgraph-tauola/meloam-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/USER
./condor_submit.py --is-mc -c stop_cfg.py -d /WJetsToLNu_TuneZ2Star_8TeV-madgraph-tarball/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v2_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/USER
./condor_submit.py --is-mc -c stop_cfg.py -d /DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/USER
./condor_submit.py --is-mc -c stop_cfg.py -d /T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/USER
./condor_submit.py --is-mc -c stop_cfg.py -d /Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/USER
./condor_submit.py --is-mc -c stop_cfg.py -d /T_s-channel_TuneZ2star_8TeV-powheg-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/USER
./condor_submit.py --is-mc -c stop_cfg.py -d /Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/USER
./condor_submit.py --is-mc -c stop_cfg.py -d /T_t-channel_TuneZ2star_8TeV-powheg-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/USER
./condor_submit.py --is-mc -c stop_cfg.py -d /Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/USER
./condor_submit.py --is-mc -c stop_cfg.py -d /QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6/StoreResults-Summer12_DR53X-PU_S10_START53_V7A-v1_TLBSM_53x_v2-c04f3b4fa74c8266c913b71e0c74901d/USER

# signal MC, 5 jobs
./condor_submit.py --is-mc --is-signal -c stop_cfg.py --nevents-total 300000 --nevents-job 300000 --dataset t1t1bar_WbG_120GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim-LJMET --input-dir /pnfs/cms/WAX/11/store/user/kukarzev/t1t1bar_WbG_120GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim-AODSIM/TLBSM_53X_v2/18dec2012v1
./condor_submit.py --is-mc --is-signal -c stop_cfg.py --nevents-total 300000 --nevents-job 300000 --dataset t1t1bar_WbG_150GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim-LJMET --input-dir /pnfs/cms/WAX/11/store/user/kukarzev/t1t1bar_WbG_150GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim-AODSIM/TLBSM_53X_v2/18dec2012v1
./condor_submit.py --is-mc --is-signal -c stop_cfg.py --nevents-total 300000 --nevents-job 300000 --dataset t1t1bar_WbG_172GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim-LJMET --input-dir /pnfs/cms/WAX/11/store/user/kukarzev/t1t1bar_WbG_172GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim-AODSIM/TLBSM_53X_v2/18dec2012v1
./condor_submit.py --is-mc --is-signal -c stop_cfg.py --nevents-total 300000 --nevents-job 300000 --dataset t1t1bar_WbG_180GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim-LJMET --input-dir /pnfs/cms/WAX/11/store/user/kukarzev/t1t1bar_WbG_180GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim-AODSIM/TLBSM_53X_v2/18dec2012v1
./condor_submit.py --is-mc --is-signal -c stop_cfg.py --nevents-total 300000 --nevents-job 300000 --dataset t1t1bar_WbG_200GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim-LJMET --input-dir /pnfs/cms/WAX/11/store/user/kukarzev/t1t1bar_WbG_200GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim-AODSIM/TLBSM_53X_v2/18dec2012v1
