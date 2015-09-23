max=25
for i in `seq 0 $max`
do
  cp snowmass_cfg_Bj_14TEV_3700_100000_Conf4v2.py snowmass_cfg_Bj_14TEV_3700_100000_Conf4v2_$i.py
  sed -i -e 's/Bj_14TEV_3700_100000_Conf4v2/Bj_14TEV_3700_100000_Conf4v2_'$i'/g' snowmass_cfg_Bj_14TEV_3700_100000_Conf4v2_$i.py
done
