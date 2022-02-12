#!/bin/bash
pushd ..
./compile.sh
popd

opts=("no_opt O3")
sizes=("4K 32K 70K 256K 2M 16M 128M 256M")

# cleanup previous results
rm -f exchange_info-* send_file-* server_output received_file

for opt in $opts; do
    # exchange_info
    ../build/$opt/exchange_info_server &
    ../build/$opt/exchange_info_client >exchange_info-$opt-local.txt 2>&1
    ssh snares-05 "cd $PWD; ../build/$opt/exchange_info_client royal-09:53706" >exchange_info-$opt-remote.txt 2>&1
    pkill -f -9 ./exchange_info_server

    # send_file
    ../build/$opt/send_file_server &
    sleep 2
    for size in $sizes; do
        ../build/$opt/send_file_client ../../../random_files/$size.random >send_file-$opt-$size-local.txt 2>&1
        ssh snares-05 "cd $PWD; ../build/$opt/send_file_client ../../../random_files/$size.random" >send_file-$opt-$size-remote.txt 2>&1
        # echo "../build/$opt/send_file_client ../../../random_files/$size.random"
        # ../build/$opt/send_file_client ../../../random_files/$size.random
    done
    pkill -f -9 ./send_file_server
done

rm -f received_file
