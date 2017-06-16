gcc -std=gnu11 freelist_test.c -o freelist_test_local -DLOCAL -lpthread -O3
gcc -std=gnu11 freelist_test.c -o freelist_test_global -DGLOBAL -lpthread -O3 -Wall
echo ""
echo "Local allocators:"
time ./freelist_test_local
echo ""
echo "Global Allocators:"
time ./freelist_test_global
