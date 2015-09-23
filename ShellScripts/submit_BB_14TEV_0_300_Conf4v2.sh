cd /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/
eval `scram runtime -sh`
export SCRAM_ARCH=slc5_amd64_gcc462
cd /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/LJMet/Com/test
max=32
for i in `seq 0 $max`
do
  cp run_BB_14TEV_0_300_Conf4v2.sh run_BB_14TEV_0_300_Conf4v2_$i.sh
  sed -i -e 's/BB_14TEV_0_300_Conf4v2/BB_14TEV_0_300_Conf4v2_'$i'/g' run_BB_14TEV_0_300_Conf4v2_$i.sh 
  #sed -i -e 's/snowmass_cfg_BB_14TEV_0_300_Conf4v2_0/snowmass_cfg_BB_14TEV_0_300_Conf4v2_'$i'/g' run_BB_14TEV_0_300_Conf4v2_$i.sh
  bsub -q 2nd -J myjob1 < run_BB_14TEV_0_300_Conf4v2_$i.sh
  #ljmet /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/LJMet/Com/test/snowmass_cfg_BB_14TEV_0_300_Conf4v2_$i.py
done
