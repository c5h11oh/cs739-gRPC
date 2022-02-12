#!/bin/bash
pushd ..
./compile.sh
popd

# non-optimized (-O) code
../build/no_opt/exchange_info_server &
../build/no_opt/exchange_info_client >local-exchange_info-no_opt.txt 2>&1
ssh snares-05 "cd $PWD; ../build/no_opt/exchange_info_client royal-09:53706" >remote-exchange_info-no_opt.txt 2>&1
pkill -f -9 ./exchange_inft_server