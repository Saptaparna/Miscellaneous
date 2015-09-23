max=4
for i in `seq 0 $max`
do
  cp snowmass_cfg_tj_14TEV_2400_100000_Conf3.py snowmass_cfg_tj_14TEV_2400_100000_Conf3_$i.py
  sed -i -e 's/tj_14TEV_2400_100000_Conf3/tj_14TEV_2400_100000_Conf3_'$i'/g' snowmass_cfg_tj_14TEV_2400_100000_Conf3_$i.py
done
