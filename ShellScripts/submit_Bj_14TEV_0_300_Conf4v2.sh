cd /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/
eval `scram runtime -sh`
export SCRAM_ARCH=slc5_amd64_gcc462
cd /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/LJMet/Com/test
max=20
for i in `seq 0 $max`
do
  cp run_Bj_14TEV_0_300_Conf4v2.sh run_Bj_14TEV_0_300_Conf4v2_$i.sh
  sed -i -e 's/Bj_14TEV_0_300_Conf4v2/Bj_14TEV_0_300_Conf4v2_'$i'/g' run_Bj_14TEV_0_300_Conf4v2_$i.sh 
  #sed -i -e 's/snowmass_cfg_Bj_14TEV_0_300_Conf4v2_0/snowmass_cfg_Bj_14TEV_0_300_Conf4v2_'$i'/g' run_Bj_14TEV_0_300_Conf4v2_$i.sh
  bsub -q 2nd -J myjob1 < run_Bj_14TEV_0_300_Conf4v2_$i.sh
  #ljmet /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/LJMet/Com/test/snowmass_cfg_Bj_14TEV_0_300_Conf4v2_$i.py
done
