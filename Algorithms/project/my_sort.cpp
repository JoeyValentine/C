#include "my_stdlib.h"

int my_record_keys_compare(const void *a, const void *b) {
	RECORD *rec_a = (RECORD*)a, *rec_b = (RECORD*)b;
	if (rec_a->key == rec_b->key) return 0;
	else if (rec_a->key < rec_b->key) return -1;
	else return 1;
}

int my_unsigned_int_keys_compare(const void* a, const void *b) {
	RECORD2 *ui_a = (RECORD2*)a, *ui_b = (RECORD2*)b;
	if (*ui_a == *ui_b) return 0;
	else if (*ui_a<*ui_b) return -1;
	else return 1;
}

void Fisher_Yates_shuffle(int *A, int n) {
	int i, j;
	int tmp;

	srand((unsigned int)time(NULL));

	for (i = n - 1; i >= 1; --i) {
		j = rand() % (i + 1);
		tmp = A[i]; A[i] = A[j]; A[j] = tmp;
	}
}

void QS_ITER(void* base, size_t n, size_t size, _Cmpfun *cmp) {
	while (1<n) {
		size_t i = 0;
		size_t j = n - 1;
		char *qi = (char *)base;
		char *qj = qi + size * j;
		char *qp = qj;

		while (i<j) {
			while (i<j && (*cmp)(qi, qp) <= 0)
				++i, qi += size;
			while (i<j && (*cmp)(qp, qj) <= 0)
				--j, qj -= size;
			if (i<j) {
				char buf[MAX_BUF];
				char *q1 = qi;
				char *q2 = qj;
				size_t m, ms;

				for (ms = size; 0<ms; ms -= m, q1 += m, q2 += m) {
					m = ms < sizeof(buf) ? ms : sizeof(buf);
					memcpy(buf, q1, m);
					memcpy(q1, q2, m);
					memcpy(q2, buf, m);
				}
				++i, qi += size;
			}
		}
		if (qi != qp) {
			char buf[MAX_BUF];
			char *q1 = qi;
			char *q2 = qp;
			size_t m, ms;
			for (ms = size; 0<ms; ms -= m, q1 += m, q2 += m) {
				m = ms < sizeof(buf) ? ms : sizeof(buf);
				memcpy(buf, q1, m);
				memcpy(q1, q2, m);
				memcpy(q2, buf, m);
			}
		}
		j = n - i - 1, qi += size;
		if (j<i) {
			if (1<j)
				QS_ITER(qi, j, size, cmp);
			n = i;
		}
		else {
			if (1<i)
				QS_ITER(base, i, size, cmp);
			base = qi;
			n = j;
		}
	}
}

void INSERT(void* ary, size_t n, size_t size, _Cmpfun *cmp) {
	char *p = (char*)ary;
	void* temp = (char*)malloc(size);
	for (register size_t i = 1; i<n; ++i) {
		memcpy(temp, &p[i*size], size);
		register size_t j = i;
		for (; j>0 && (*cmp)(&p[(j - 1)*size], temp)>0; --j)
			memcpy(&p[j*size], &p[(j - 1)*size], size);
		memcpy(&p[j*size], temp, size);
	}
	free(temp);
}

int cmpInt(const void* x, const void* y) {
	return *(int*)x - *(int*)y;
}

int partition(void* ary, size_t n, size_t size, _Cmpfun *cmp) {
	char *p = (char*)ary;
	void *pval = malloc(size), *temp = malloc(size);

	int r[3];
	r[0] = rand() % n;
	r[1] = rand() % n;
	r[2] = rand() % n;
	INSERT(r, 3, sizeof(int), cmpInt);

	memcpy(temp, &p[r[1] * size], size);
	memcpy(&p[r[1] * size], &p[(n - 1)*size], size);
	memcpy(&p[(n - 1)*size], temp, size);
	memcpy(pval, &p[(n - 1)*size], size);

	register int i = -1;
	for (register size_t j = 0; j<n; ++j) {
		if ((*cmp)(&p[j*size], pval)<0) {
			++i;
			memcpy(temp, &p[i*size], size);
			memcpy(&p[i*size], &p[j*size], size);
			memcpy(&p[j*size], temp, size);
		}
	}
	memcpy(temp, &p[(i + 1)*size], size);
	memcpy(&p[(i + 1)*size], &p[(n - 1)*size], size);
	memcpy(&p[(n - 1)*size], temp, size);
	free(pval);
	free(temp);
	return i + 1;
}

void QS_REC(void* ary, size_t n, size_t size, _Cmpfun *cmp) {
	if (n>1) {
		int idx = partition(ary, n, size, cmp);
		QS_REC(ary, idx + 1, size, cmp);
		QS_REC((char*)ary + (idx + 1)*size, n - idx - 1, size, cmp);
	}
}

int opt_partition(void* ary, size_t n, size_t size, _Cmpfun *cmp) {
	char *p = (char*)ary;
	void *pval = malloc(size), *temp = malloc(size);
	int idx, from = 0, mid = (n - 1)*size / 2, last = (n - 1)*size;

	if ((*cmp)(&p[from], &p[mid])>0) {
		if ((*cmp)(&p[mid], &p[last])>0) idx = (n - 1) / 2;
		else if ((*cmp)(&p[from], &p[last])>0) idx = n - 1;
		else idx = 0;
	}
	else {
		if ((*cmp)(&p[mid], &p[last])>0) idx = (n - 1) / 2;
		else if ((*cmp)(&p[from], &p[last])>0) idx = n - 1;
		else idx = 0;
	}

	memcpy(temp, &p[idx*size], size);
	memcpy(&p[idx*size], &p[(n - 1)*size], size);
	memcpy(&p[(n - 1)*size], temp, size);
	memcpy(pval, &p[(n - 1)*size], size);

	register int i = -1;
	for (register size_t j = 0; j<n; ++j) {
		if ((*cmp)(&p[j*size], pval)<0) {
			++i;
			memcpy(temp, &p[i*size], size);
			memcpy(&p[i*size], &p[j*size], size);
			memcpy(&p[j*size], temp, size);
		}
	}
	memcpy(temp, &p[(i + 1)*size], size);
	memcpy(&p[(i + 1)*size], &p[(n - 1)*size], size);
	memcpy(&p[(n - 1)*size], temp, size);
	free(pval);
	free(temp);
	return i + 1;
}

void QS_REC_PIVOT_INSERT(void* ary, size_t n, size_t size, _Cmpfun *cmp) {
	if (n <= SMALL_SIZE)
		INSERT(ary, n, size, cmp);
	else {
		int f = 0, b = n - 1;
		while (f<b) {
			int splitPoint = opt_partition((char*)ary + f*size, b - f + 1, size, cmp) + f;
			if (splitPoint - f < b - splitPoint) {
				QS_REC_PIVOT_INSERT((char*)ary + f*size, splitPoint - f, size, cmp);
				f = splitPoint + 1;
			}
			else {
				QS_REC_PIVOT_INSERT((char*)ary + (splitPoint + 1)*size, b - splitPoint, size, cmp);
				b = splitPoint - 1;
			}
		}
	}
}

void QS_ITER_PIVOT_INSERT(void* ary, size_t n, size_t size, _Cmpfun *cmp) {
	int l = 0, h = n - 1, *stack = (int*)malloc((h - l + 1)*sizeof(int)), top = -1;
	stack[++top] = l;
	stack[++top] = h;
	while (top >= 0) {
		h = stack[top--];
		l = stack[top--];
		int p = opt_partition((char*)ary + l*size, h - l + 1, size, cmp) + l;
		if (p - 1 > l) {
			stack[++top] = l;
			stack[++top] = p - 1;
		}
		if (p + 1 < h) {
			stack[++top] = p + 1;
			stack[++top] = h;
		}
	}
	free(stack);
}

void MY_BEST_SORT(void* ary, size_t n, size_t size, _Cmpfun *cmp) {
	if (n <= SMALL_SIZE)
		INSERT(ary, n, size, cmp);
	else {
		int f = 0, b = n - 1;
		while (f<b) {
			int splitPoint = opt_partition((char*)ary + f*size, b - f + 1, size, cmp) + f;
			if (splitPoint - f < b - splitPoint) {
				MY_BEST_SORT((char*)ary + f*size, splitPoint - f, size, cmp);
				f = splitPoint + 1;
			}
			else {
				MY_BEST_SORT((char*)ary + (splitPoint + 1)*size, b - splitPoint, size, cmp);
				b = splitPoint - 1;
			}
		}
	}
}