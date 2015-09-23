max=14
for i in `seq 0 $max`
do
  cp snowmass_cfg_ttB_14TEV_2500_100000_Conf3.py snowmass_cfg_ttB_14TEV_2500_100000_Conf3_$i.py
  sed -i -e 's/ttB_14TEV_2500_100000_Conf3/ttB_14TEV_2500_100000_Conf3_'$i'/g' snowmass_cfg_ttB_14TEV_2500_100000_Conf3_$i.py
done
