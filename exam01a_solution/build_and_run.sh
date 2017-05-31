CFLAGS="-std=gnu99 -lrt -Wall -g -lpthread"

gcc bank.c -c -o bank.o $CFLAGS
gcc bank_server.c bank.o -o bank_server $CFLAGS
gcc bank_client.c bank.o -o bank_client $CFLAGS

for i in `seq 0 19`; do ./bank_client $i & done
./bank_server

rm BANK_FIFO
rm bank.o
rm bank_client
rm bank_server
