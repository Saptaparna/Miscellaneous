cd /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/
eval `scram runtime -sh`
export SCRAM_ARCH=slc5_amd64_gcc462
cd /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/LJMet/Com/test
max=18
for i in `seq 0 $max`
do
  ljmet /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/LJMet/Com/test/snowmass_cfg_TTBAR_14TEV_0_600_Conf3_$i.py
done
