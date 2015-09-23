#! /bin/tcsh

# DATA
./condor_submit.py -r -i --output-dir data/SingleMu_StoreResults_SingleMu_Run2012A_13Jul2012_v1_TLBSM_53x_v2_jsonfix_e3fb55b810dc7a0811f4c66dfa2267c9_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/SingleMu_StoreResults_Run2012A_recover_06Aug2012_v1_TLBSM_53x_v2_e3fb55b810dc7a0811f4c66dfa2267c9_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/SingleMu_StoreResults_Run2012B_13Jul2012_v1_TLBSM_53x_v2_e3fb55b810dc7a0811f4c66dfa2267c9_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/SingleMu_StoreResults_Run2012C_24Aug2012_v1_TLBSM_53x_v2_e3fb55b810dc7a0811f4c66dfa2267c9_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/SingleMu_StoreResults_Run2012C_PromptReco_v2_TLBSM_53x_v2_e3fb55b810dc7a0811f4c66dfa2267c9_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/SingleMu_StoreResults_Run2012C_PromptReco_v2_TLBSM_53x_v2_646f7563e9ae6f48814faa1c250f042a_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/SingleMu_StoreResults_Run2012C_PromptReco_v2_TLBSM_53x_v2_extension_v1_e3fb55b810dc7a0811f4c66dfa2267c9_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/SingleMu_jpilot_Run2012C_EcalRecover_11Dec2012_v1_TLBSM_53x_v2_e3fb55b810dc7a0811f4c66dfa2267c9_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/SingleMu_StoreResults_Run2012D_PromptReco_v1_TLBSM_53x_v2_e3fb55b810dc7a0811f4c66dfa2267c9_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/SingleMu_StoreResults_Run2012D_PromptReco_v1_TLBSM_53x_v2_extension_v1_e3fb55b810dc7a0811f4c66dfa2267c9_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/SingleMu_StoreResults_Run2012D_PromptReco_v1_TLBSM_53x_v2_extension_v2_e3fb55b810dc7a0811f4c66dfa2267c9_USER/27Feb2013v0


# BG MC, 114 jobs
./condor_submit.py -r -i --output-dir data/TTJets_MassiveBinDECAY_TuneZ2star_8TeV_madgraph_tauola_meloam_Summer12_DR53X_PU_S10_START53_V7A_v1_TLBSM_53x_v2_c04f3b4fa74c8266c913b71e0c74901d_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/WJetsToLNu_TuneZ2Star_8TeV_madgraph_tarball_StoreResults_Summer12_DR53X_PU_S10_START53_V7A_v2_TLBSM_53x_v2_c04f3b4fa74c8266c913b71e0c74901d_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/DYJetsToLL_M_50_TuneZ2Star_8TeV_madgraph_tarball_StoreResults_Summer12_DR53X_PU_S10_START53_V7A_v1_TLBSM_53x_v2_c04f3b4fa74c8266c913b71e0c74901d_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/T_tW_channel_DR_TuneZ2star_8TeV_powheg_tauola_StoreResults_Summer12_DR53X_PU_S10_START53_V7A_v1_TLBSM_53x_v2_c04f3b4fa74c8266c913b71e0c74901d_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/Tbar_tW_channel_DR_TuneZ2star_8TeV_powheg_tauola_StoreResults_Summer12_DR53X_PU_S10_START53_V7A_v1_TLBSM_53x_v2_c04f3b4fa74c8266c913b71e0c74901d_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/T_s_channel_TuneZ2star_8TeV_powheg_tauola_StoreResults_Summer12_DR53X_PU_S10_START53_V7A_v1_TLBSM_53x_v2_c04f3b4fa74c8266c913b71e0c74901d_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/Tbar_s_channel_TuneZ2star_8TeV_powheg_tauola_StoreResults_Summer12_DR53X_PU_S10_START53_V7A_v1_TLBSM_53x_v2_c04f3b4fa74c8266c913b71e0c74901d_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/T_t_channel_TuneZ2star_8TeV_powheg_tauola_StoreResults_Summer12_DR53X_PU_S10_START53_V7A_v1_TLBSM_53x_v2_c04f3b4fa74c8266c913b71e0c74901d_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/Tbar_t_channel_TuneZ2star_8TeV_powheg_tauola_StoreResults_Summer12_DR53X_PU_S10_START53_V7A_v1_TLBSM_53x_v2_c04f3b4fa74c8266c913b71e0c74901d_USER/27Feb2013v0
./condor_submit.py -r -i --output-dir data/QCD_Pt_20_MuEnrichedPt_15_TuneZ2star_8TeV_pythia6_StoreResults_Summer12_DR53X_PU_S10_START53_V7A_v1_TLBSM_53x_v2_c04f3b4fa74c8266c913b71e0c74901d_USER/27Feb2013v0


# signal MC, 5 jobs
./condor_submit.py -r -i --output-dir data/t1t1bar_WbG_120GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim_LJMET/27Feb2013v0
./condor_submit.py -r -i --output-dir data/t1t1bar_WbG_150GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim_LJMET/27Feb2013v0
./condor_submit.py -r -i --output-dir data/t1t1bar_WbG_172GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim_LJMET/27Feb2013v0
./condor_submit.py -r -i --output-dir data/t1t1bar_WbG_180GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim_LJMET/27Feb2013v0
./condor_submit.py -r -i --output-dir data/t1t1bar_WbG_200GeV_8TeV_Rutgers_533_PU2012Startup_Fastsim_LJMET/27Feb2013v0
