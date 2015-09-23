max=32
for i in `seq 0 $max`
do
  cp snowmass_cfg_BB_14TEV_2100_100000_Conf4v2.py snowmass_cfg_BB_14TEV_2100_100000_Conf4v2_$i.py
  sed -i -e 's/BB_14TEV_2100_100000_Conf4v2/BB_14TEV_2100_100000_Conf4v2_'$i'/g' snowmass_cfg_BB_14TEV_2100_100000_Conf4v2_$i.py
done
