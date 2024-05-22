#echo off
#setlocal

# This script is used to generate vs2019 solution files

# determine if camke exists
which cmake
if [ $? -eq 0 ]; then
    echo cmake found
else 
    echo cmake not found
    goto exit_build
fi


# create build directory
dir_name=build
if [ -d ${dir_name}  ];then 
    echo delete dir ${dir_name} 
    rm -rf ${dir_name} 
else
    echo file is not exist
fi

mkdir ${dir_name} 
echo create dir ${dir_name} 
cd ${dir_name} 


#cmake
cmake .. && make -j4