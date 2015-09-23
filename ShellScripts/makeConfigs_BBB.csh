max=20
for i in `seq 0 $max`
do
  cp snowmass_cfg_BBB_14TEV_600_1300_Conf4v2.py snowmass_cfg_BBB_14TEV_600_1300_Conf4v2_$i.py
  sed -i -e 's/BBB_14TEV_600_1300_Conf4v2/BBB_14TEV_600_1300_Conf4v2_'$i'/g' snowmass_cfg_BBB_14TEV_600_1300_Conf4v2_$i.py
done
