
#ifndef C_SORT_H
#define C_SORT_H

#define SORT_BUBBLE       0
#define SORT_INSERTION    1
#define SORT_SELECTION    2
#define SORT_COMB         3
#define SORT_SHELL        4
#define SORT_QUICK        5
#define SORT_MERGE        6
#define SORT_HEAP         7

#define DIR_ASCENDING     0
#define DIR_DESCENDING    1

#define ERR_SUCCESS       0
#define ERR_NULL_ARRAY    -1
#define ERR_INVALID_SIZE  -2
#define ERR_INVALID_ELEM  -3
#define ERR_NULL_COMP     -4
#define ERR_INVALID_METHOD -5
#define ERR_INVALID_DIR   -6
#define ERR_ALLOC_FAIL    -7

int sort(void *array, int size, int elemsize, int (*comp)(void*, void*), int method, int direction);

int compare_char(void *a, void *b);

int compare_int(void *a, void *b);

int compare_double(void *a, void *b);

#endif
