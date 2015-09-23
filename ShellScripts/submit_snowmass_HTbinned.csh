#! /bin/tcsh

# tools/Objects/... TLepton - selection
# tprime_plots/... TPrimeAnalysis.C  5.27   channel signs 2012 sample_name input_root_file job_number
#   sample_name: LoadData_2012.C 
# /data/users/speer/yield/YieldSA.C make YieldSA
#   argument channel(OS SS TRI) directory_with_TPrimeAnal_output
# yields  yieldTable(800,doFakes-probably 0,true);


# BG MC, xxx jobs
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBAR_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Inclusive/Delphes-3.0.9.1/140PileUp/TTBAR_13TEV
#/uscms_data/d1/jstupak/delphes/output/AZh_14TEV_tata_500A_NoPileUp.root

#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 4000000 --dataset tB_14TEV_LJMET_0_500  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tB-4p-0-500-v1510_14TEV 
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 4000000 --dataset tB_14TEV_LJMET_500_900  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tB-4p-500-900-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 4000000 --dataset tB_14TEV_LJMET_900_1500  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tB-4p-900-1500-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 4000000 --dataset tB_14TEV_LJMET_1500_2200  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tB-4p-1500-2200-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 4000000 --dataset tB_14TEV_LJMET_2200_100000  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tB-4p-2200-100000-v1510_14TEV

#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 4000000 --dataset ttB_14TEV_LJMET_0_900  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/ttB-4p-0-900-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 4000000 --dataset ttB_14TEV_LJMET_900_1600  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/ttB-4p-900-1600-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 4000000 --dataset ttB_14TEV_LJMET_1600_2500  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/ttB-4p-1600-2500-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 4000000 --dataset ttB_14TEV_LJMET_2500_100000  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/ttB-4p-2500-100000-v1510_14TEV

#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBAR_13TEV_LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tt-4p-0-600-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBAR_13TEV_LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tt-4p-600-1100-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBAR_13TEV_LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tt-4p-1100-1700-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBAR_13TEV_LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tt-4p-1700-2500-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBAR_13TEV_LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tt-4p-2500-100000-v1510_14TEV


#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 10000 --dataset TRIBOSON  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/BBB-4p-0-600-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 10000 --dataset TRIBOSON  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/BBB-4p-600-1300-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 10000 --dataset TRIBOSON  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/BBB-4p-1300-100000-v1510_14TEV

#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 10000 --dataset DIBOSON  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/BB-4p-0-300-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 10000 --dataset DIBOSON  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/BB-4p-300-700-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 10000 --dataset DIBOSON  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/BB-4p-700-1300-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 10000 --dataset DIBOSON  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/BB-4p-1300-2100-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 10000 --dataset DIBOSON  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/BB-4p-2100-100000-v1510_14TEV 

#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset SINGLET_13TEV-LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tj-4p-0-500-v1510_14TEV/
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset SINGLET_13TEV-LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tj-4p-500-1000-v1510_14TEV 
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset SINGLET_13TEV-LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tj-4p-1000-1600-v1510_14TEV 
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset SINGLET_13TEV-LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tj-4p-1600-2400-v1510_14TEV 
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset SINGLET_13TEV-LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tj-4p-2400-100000-v1510_14TEV  

#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBAR_13TEV--LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tt-4p-0-600-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBAR_13TEV--LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tt-4p-600-1100-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBAR_13TEV--LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tt-4p-1100-1700-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBAR_13TEV--LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tt-4p-1700-2500-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBAR_13TEV--LJMET  --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/tt-4p-2500-100000-v1510_14TEV

#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset ZJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/Bj-4p-0-300-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset ZJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/Bj-4p-300-600-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset ZJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/Bj-4p-600-1100-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset ZJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/Bj-4p-1100-1800-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset ZJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/Bj-4p-1800-2700-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset ZJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/Bj-4p-2700-3700-v1510_14TEV
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset ZJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/HTBinned/Delphes-3.0.9.1/NoPileUp/Bj-4p-3700-100000-v1510_14TEV



# signal MC, xxx jobs
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_bb_1000-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_bb_1000
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_bb_200-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_bb_200
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_bb_250-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_bb_250
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_bb_300-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_bb_300
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_bb_350-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_bb_350
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_bb_400-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_bb_400
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_bb_450-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_bb_450
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_bb_500-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_bb_500
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_bb_600-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_bb_600
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_bb_700-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_bb_700
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_bb_800-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_bb_800
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_bb_900-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_bb_900
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_tata_1000-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_tata_1000
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_tata_200-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_tata_200
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_tata_250-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_tata_250
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_tata_300-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_tata_300
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_tata_350-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_tata_350
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_tata_400-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_tata_400
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_tata_450-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_tata_450
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_tata_500-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_tata_500
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_tata_600-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_tata_600
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_tata_700-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_tata_700
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_tata_800-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_tata_800
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_tata_900-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_tata_900
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_ww_1000-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_ww_1000
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_ww_200-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_ww_200
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_ww_250-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_ww_250
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_ww_300-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_ww_300
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_ww_350-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_ww_350
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_ww_400-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_ww_400
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_ww_450-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_ww_450
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_ww_500-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_ww_500
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_ww_600-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_ww_600
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_ww_700-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_ww_700
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_ww_800-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_ww_800
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_ww_900-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_ww_900
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_zz_1000-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_zz_1000
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_zz_200-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_zz_200
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_zz_250-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_zz_250
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_zz_300-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_zz_300
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_zz_350-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_zz_350
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_zz_400-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_zz_400
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_zz_450-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_zz_450
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_zz_500-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_zz_500
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_zz_600-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_zz_600
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_zz_700-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_zz_700
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_zz_800-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_zz_800
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset AZh_14TEV_zz_900-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/AZh_14TEV_zz_900
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset HWW_14TEV_1000-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/HWW_14TEV_1000
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset HWW_14TEV_200-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/HWW_14TEV_200
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset HWW_14TEV_250-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/HWW_14TEV_250
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset HWW_14TEV_300-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/HWW_14TEV_300
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset HWW_14TEV_350-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/HWW_14TEV_350
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset HWW_14TEV_400-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/HWW_14TEV_400
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset HWW_14TEV_500-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/HWW_14TEV_500
#./condor_submit.py --is-mc --is-signal -c snowmass_cfg.py --nevents-total 50000 --nevents-job 50000 --dataset HWW_14TEV_600-LJMET --input-dir /eos/uscms/store/user/kukarzev/snowmass/14TeV/HWW_14TEV_600
