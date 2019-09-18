for file in ../TestFolder/*/*.blocks; 
do 
   echo $file
   echo $file | ./parser; 
done
