for file in ../TestFolder/*/*.blocks; 
do 
  $file > foo.txt
  ./parser < foo.txt; 
done
#./parser < ../TestFolder/n10hard/n10hard.blocks
#./parser < ../TestFolder/n10soft/n10soft.blocks
#./parser < ../TestFolder/n30hard/n30hard.blocks
#./parser < ../TestFolder/n30soft/n30soft.blocks
#./parser < ../TestFolder/n50hard/n50hard.blocks
#./parser < ../TestFolder/n50soft/n50soft.blocks
#./parser < ../TestFolder/n100hard/n100hard.blocks
#./parser < ../TestFolder/n100soft/n100soft.blocks
#./parser < ../TestFolder/n200hard/n200hard.blocks
#./parser < ../TestFolder/n200soft/n200soft.blocks
#./parser < ../TestFolder/n300hard/n300hard.blocks
#./parser < ../TestFolder/n300soft/n300soft.blocks
