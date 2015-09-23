max=25
for i in `seq 0 $max`
do
  cp snowmass_cfg_TTBAR_14TEV_2500_100000_Conf4v2.py snowmass_cfg_TTBAR_14TEV_2500_100000_Conf4v2_$i.py
  sed -i -e 's/TTBAR_14TEV_2500_100000_Conf4v2/TTBAR_14TEV_2500_100000_Conf4v2_'$i'/g' snowmass_cfg_TTBAR_14TEV_2500_100000_Conf4v2_$i.py
done
