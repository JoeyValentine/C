#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define CHECK_TIME_START QueryPerformanceFrequency ((LARGE_INTEGER*)&freq); QueryPerformanceCounter((LARGE_INTEGER*)&start)
#define CHECK_TIME_END(a) QueryPerformanceCounter((LARGE_INTEGER*)&END); a=(float)((float) (END - start)/freq)
#define MAX_BUF 256
#define N_MAX_RECORDS 100
#define SMALL_SIZE 32
#define TEST_NUM 1

typedef int _Cmpfun(const void*, const void*);

typedef struct _record {
	char hexadecimal[32];
	int dummy1[16];
	unsigned int key;
	char octal[32];
	int dummy2[39];
} RECORD;

typedef unsigned int RECORD2;

void init_RECORD_array(RECORD* data, int n);
void init_RECORD2_array(RECORD2 *data, int n);
void Fisher_Yates_shuffle(int*, int);
int my_record_keys_compare(const void *a, const void *b);
int my_unsigned_int_keys_compare(const void* a, const void *b);

void QS_ITER(void*, size_t, size_t, _Cmpfun*);
void INSERT(void*, size_t, size_t, _Cmpfun*);
int cmpInt(const void*, const void*);
int partition(void*, size_t, size_t, _Cmpfun*);
void QS_REC(void*, size_t, size_t, _Cmpfun*);
int opt_partition(void* ary, size_t n, size_t size, _Cmpfun *cmp);
void QS_REC_PIVOT_INSERT(void*, size_t, size_t, _Cmpfun*);
void QS_ITER_PIVOT_INSERT(void*, size_t, size_t, _Cmpfun*);
void MY_BEST_SORT(void*, size_t, size_t, _Cmpfun*);