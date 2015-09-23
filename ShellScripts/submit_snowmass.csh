#! /bin/tcsh

# tools/Objects/... TLepton - selection
# tprime_plots/... TPrimeAnalysis.C  5.27   channel signs 2012 sample_name input_root_file job_number
#   sample_name: LoadData_2012.C 
# /data/users/speer/yield/YieldSA.C make YieldSA
#   argument channel(OS SS TRI) directory_with_TPrimeAnal_output
# yields  yieldTable(800,doFakes-probably 0,true);


# BG MC, xxx jobs
#./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBAR_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/TTBAR_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset DIPHOTONS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/DIPHOTONS_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset PHOTONJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/PHOTONJETS_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset SSWWJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/SSWWJETS_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBARWW_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/TTBARWW_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBARW_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/TTBARW_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBARZ_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/TTBARZ_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset TTBAR_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/TTBAR_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset WGJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/WGJETS_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset WJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/WJETS_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset WWJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/WWJETS_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset WWW_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/WWW_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset WWZ_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/WWZ_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset WZ3LNUJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/WZ3LNUJETS_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset WZJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/WZJETS_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset WZZ_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/WZZ_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset ZGJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/ZGJETS_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 1000000 --nevents-job 1000000 --dataset ZJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/ZJETS_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset ZZ4LJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/ZZ4LJETS_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 4000000 --nevents-job 1000000 --dataset ZZJETS_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/ZZJETS_13TEV
./condor_submit.py --is-mc -c snowmass_cfg.py --nevents-total 1000000 --nevents-job 1000000 --dataset ZZZ_13TEV-LJMET --input-dir /pnfs/cms/WAX/11/store/user/snowmass/Delphes-3.0.6.1/NoPileUp/ZZZ_13TEV




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
