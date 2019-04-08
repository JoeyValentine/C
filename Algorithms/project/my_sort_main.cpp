#include "my_stdlib.h"

__int64 start, freq, END;

void main() {
	double time,avg;
	int i,j, n = N_MAX_RECORDS;
	RECORD Array[N_MAX_RECORDS];
	RECORD2 Array2[N_MAX_RECORDS];

	printf("Data Size : %d\n\n", n);

	puts("TYPE : RECORD\n");

	for (i = 1, avg=0; i <= TEST_NUM; ++i) {
		init_RECORD_array(Array, n);
		CHECK_TIME_START;
		MY_BEST_SORT(Array, n, sizeof(RECORD), my_record_keys_compare);
		CHECK_TIME_END(time);
		avg += time;
	}
	printf("MY_BEST SORT() : %lf sec\n", avg / i);
	
	printf("* Data after sort: \n");
	for(i=0;i<n;++i) printf(" (0x%s, %d [%u], 0%s, %d) \n",Array[i].hexadecimal,Array[i].dummy1[0],Array[i].key,Array[i].octal,Array[i].dummy2[0]);
	printf("%f sec\n",time);

	puts("\nData Type : RECORD2\n");
	
	for (i = 1, avg=0; i <= TEST_NUM; ++i) {
		init_RECORD2_array(Array2, n);
		CHECK_TIME_START;
		MY_BEST_SORT(Array2, n, sizeof(RECORD2), my_unsigned_int_keys_compare);
		CHECK_TIME_END(time);
		avg += time;
	}
	printf("MY_BEST SORT() : %lf sec\n", avg / i);
	
	printf("* Data after sort: \n");
	for(i=0;i<n;++i) printf(" ([%u]) \n",Array2[i]);
	
}

void init_RECORD_array(RECORD* data, int n) {
	int i, j;
	for (i = 0; i<n; ++i) {
		itoa(i, data[i].hexadecimal, 16);
		data[i].key = i;
		itoa(i, data[i].octal, 8);
		data[i].dummy1[0] = 2 * i;
		data[i].dummy2[0] = -i;
	}

	srand((unsigned int)time(NULL));

	for (i = n - 1; i >= 1; --i) {
		j = rand() % (i + 1);
		{
			char buf[256];
			char *r_i = (char*)(data + i);
			char *r_j = (char*)(data + j);
			size_t m, ms;
			for (ms = sizeof(RECORD); ms>0; ms -= m, r_i += m, r_j += m) {
				m = ms<sizeof(buf) ? ms : sizeof(buf);
				memcpy(buf, r_i, m);
				memcpy(r_i, r_j, m);
				memcpy(r_j, buf, m);
			}
		}
	}
}

void init_RECORD2_array(RECORD2 *data, int n) {
	int i, j;
	RECORD2 tmp;
	for (i = 0; i<n; ++i) data[i] = i;
	srand((unsigned int)time(NULL));
	for (i = n - 1; i >= 1; --i) {
		j = rand() % (i + 1);
		tmp = data[i]; data[i] = data[j]; data[j] = tmp;
	}
}