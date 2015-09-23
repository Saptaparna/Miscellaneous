max=23
for i in `seq 0 $max`
do
  cp snowmass_cfg_ttB_14TEV_900_1600_Conf4v2.py snowmass_cfg_ttB_14TEV_900_1600_Conf4v2_$i.py
  sed -i -e 's/ttB_14TEV_900_1600_Conf4v2/ttB_14TEV_900_1600_Conf4v2_'$i'/g' snowmass_cfg_ttB_14TEV_900_1600_Conf4v2_$i.py
done
