cd /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/
eval `scram runtime -sh`
export SCRAM_ARCH=slc5_amd64_gcc462
cd /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/LJMet/Com/test
ljmet /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/LJMet/Com/test/snowmass_cfg_BB_14TEV_700_1300_Conf3_7.py 
