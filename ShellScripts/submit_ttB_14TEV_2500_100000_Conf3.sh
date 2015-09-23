cd /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/
eval `scram runtime -sh`
export SCRAM_ARCH=slc5_amd64_gcc462
cd /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/LJMet/Com/test
max=14
for i in `seq 0 $max`
do
  cp run_ttB_14TEV_2500_100000_Conf3.sh run_ttB_14TEV_2500_100000_Conf3_$i.sh
  sed -i -e 's/ttB_14TEV_2500_100000_Conf3/ttB_14TEV_2500_100000_Conf3_'$i'/g' run_ttB_14TEV_2500_100000_Conf3_$i.sh 
  #sed -i -e 's/snowmass_cfg_ttB_14TEV_2500_100000_Conf3_0/snowmass_cfg_ttB_14TEV_2500_100000_Conf3_'$i'/g' run_ttB_14TEV_2500_100000_Conf3_$i.sh
  bsub -q 2nd -J myjob1 < run_ttB_14TEV_2500_100000_Conf3_$i.sh
  #ljmet /afs/cern.ch/work/s/sapta/private/CMSSW_5_3_6/src/LJMet/Com/test/snowmass_cfg_ttB_14TEV_2500_100000_Conf3_$i.py
done
