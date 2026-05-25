#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

/*
 * move - copies data from source to destination
 *
 * @dest: destination pointer
 * @src: source pointer
 * @elemsize: size of each element in bytes
 *
 * Returns: void
 */
static void move(void *dest, void *src, int elemsize)
{
    memcpy(dest, src, elemsize);
}

/*
 * swap - swaps two elements using move function
 *
 * @a: pointer to first element
 * @b: pointer to second element
 * @elemsize: size of each element in bytes
 *
 * Returns: void
 */
static void swap(void *a, void *b, int elemsize)
{
    void *temp = malloc(elemsize);

    if (!temp) return;

    move(temp, a, elemsize);
    move(a, b, elemsize);
    move(b, temp, elemsize);

    free(temp);
}

/*
 * compare_wrapper - performs comparison with direction handling
 *
 * @comp: comparison function pointer
 * @a1: pointer to first element
 * @a2: pointer to second element
 * @direction: sorting direction (ASCENDING or DESCENDING)
 *
 * Returns: 1 if a1 should come after a2, 0 if equal, -1 if before
 */
static int compare_wrapper(int (*comp)(void*, void*), void *a1, void *a2, int direction)
{
    int result = comp(a1, a2);

    if (direction == DIR_ASCENDING) {
        return result;
    }
    return -result;
}

/*
 * sort_bubble - Bubble sort algorithm
 *
 * @array: pointer to array to sort
 * @size: number of elements in array
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @direction: sorting direction (DIR_ASCENDING or DIR_DESCENDING)
 *
 * Returns: void
 */
static void sort_bubble(void *array, int size, int elemsize, int (*comp)(void*, void*), int direction)
{
    int i, j;
    unsigned char *base = (unsigned char *)array;

    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < size - i - 1; j++) {
            void *elem1 = base + j * elemsize;
            void *elem2 = base + (j + 1) * elemsize;

            if (compare_wrapper(comp, elem1, elem2, direction) > 0) {
                swap(elem1, elem2, elemsize);
            }
        }
    }
}

/*
 * sort_insertion - Insertion sort algorithm
 *
 * @array: pointer to array to sort
 * @size: number of elements in array
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @direction: sorting direction (DIR_ASCENDING or DIR_DESCENDING)
 *
 * Returns: void
 */
static void sort_insertion(void *array, int size, int elemsize, int (*comp)(void*, void*), int direction)
{
    int i, j;
    unsigned char *base = (unsigned char *)array;
    unsigned char *key = (unsigned char *)malloc(elemsize);

    if (!key) return;

    for (i = 1; i < size; i++) {
        move(key, base + i * elemsize, elemsize);
        j = i - 1;

        while (j >= 0 && compare_wrapper(comp, base + j * elemsize, key, direction) > 0) {
            move(base + (j + 1) * elemsize, base + j * elemsize, elemsize);
            j--;
        }
        move(base + (j + 1) * elemsize, key, elemsize);
    }

    free(key);
}

/*
 * sort_selection - Selection sort algorithm
 *
 * @array: pointer to array to sort
 * @size: number of elements in array
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @direction: sorting direction (DIR_ASCENDING or DIR_DESCENDING)
 *
 * Returns: void
 */
static void sort_selection(void *array, int size, int elemsize, int (*comp)(void*, void*), int direction)
{
    int i, j, min_idx;
    unsigned char *base = (unsigned char *)array;

    for (i = 0; i < size - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < size; j++) {
            void *elem1 = base + j * elemsize;
            void *elem2 = base + min_idx * elemsize;

            if (compare_wrapper(comp, elem1, elem2, direction) < 0) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(base + i * elemsize, base + min_idx * elemsize, elemsize);
        }
    }
}

/*
 * sort_comb - Comb sort algorithm
 *
 * @array: pointer to array to sort
 * @size: number of elements in array
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @direction: sorting direction (DIR_ASCENDING or DIR_DESCENDING)
 *
 * Returns: void
 */
static void sort_comb(void *array, int size, int elemsize, int (*comp)(void*, void*), int direction)
{
    int gap = size;
    int swapped = 1;
    int i;
    unsigned char *base = (unsigned char *)array;

    while (gap > 1 || swapped) {
        if (gap > 1) {
            gap = (gap * 10) / 13;
            if (gap < 1) gap = 1;
        }

        swapped = 0;
        for (i = 0; i + gap < size; i++) {
            void *elem1 = base + i * elemsize;
            void *elem2 = base + (i + gap) * elemsize;

            if (compare_wrapper(comp, elem1, elem2, direction) > 0) {
                swap(elem1, elem2, elemsize);
                swapped = 1;
            }
        }
    }
}

/*
 * sort_shell - Shell sort algorithm
 *
 * @array: pointer to array to sort
 * @size: number of elements in array
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @direction: sorting direction (DIR_ASCENDING or DIR_DESCENDING)
 *
 * Returns: void
 */
static void sort_shell(void *array, int size, int elemsize, int (*comp)(void*, void*), int direction)
{
    int gap, i, j;
    unsigned char *base = (unsigned char *)array;
    unsigned char *temp = (unsigned char *)malloc(elemsize);

    if (!temp) return;

    for (gap = size / 2; gap > 0; gap /= 2) {
        for (i = gap; i < size; i++) {
            move(temp, base + i * elemsize, elemsize);
            j = i;

            while (j >= gap && compare_wrapper(comp, base + (j - gap) * elemsize, temp, direction) > 0) {
                move(base + j * elemsize, base + (j - gap) * elemsize, elemsize);
                j -= gap;
            }
            move(base + j * elemsize, temp, elemsize);
        }
    }

    free(temp);
}

/*
 * partition - Helper function for quick sort
 *
 * @array: pointer to array
 * @low: starting index
 * @high: ending index
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @direction: sorting direction (DIR_ASCENDING or DIR_DESCENDING)
 *
 * Returns: partition index
 */
static int partition(void *array, int low, int high, int elemsize, int (*comp)(void*, void*), int direction)
{
    unsigned char *base = (unsigned char *)array;
    void *pivot = base + high * elemsize;
    int i = low - 1;
    int j;

    for (j = low; j < high; j++) {
        void *curr = base + j * elemsize;

        if (compare_wrapper(comp, curr, pivot, direction) <= 0) {
            i++;
            swap(base + i * elemsize, curr, elemsize);
        }
    }
    swap(base + (i + 1) * elemsize, pivot, elemsize);
    return i + 1;
}

/*
 * quicksort_recursive - Recursive quick sort implementation
 *
 * @array: pointer to array to sort
 * @low: starting index
 * @high: ending index
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @direction: sorting direction (DIR_ASCENDING or DIR_DESCENDING)
 *
 * Returns: void
 */
static void quicksort_recursive(void *array, int low, int high, int elemsize, int (*comp)(void*, void*), int direction)
{
    if (low < high) {
        int pi = partition(array, low, high, elemsize, comp, direction);

        quicksort_recursive(array, low, pi - 1, elemsize, comp, direction);
        quicksort_recursive(array, pi + 1, high, elemsize, comp, direction);
    }
}

/*
 * sort_quick - Quick sort algorithm
 *
 * @array: pointer to array to sort
 * @size: number of elements in array
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @direction: sorting direction (DIR_ASCENDING or DIR_DESCENDING)
 *
 * Returns: void
 */
static void sort_quick(void *array, int size, int elemsize, int (*comp)(void*, void*), int direction)
{
    quicksort_recursive(array, 0, size - 1, elemsize, comp, direction);
}

/*
 * merge - Helper function for merge sort
 *
 * @array: destination array
 * @left: left sorted subarray
 * @right: right sorted subarray
 * @l_size: size of left subarray
 * @r_size: size of right subarray
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @direction: sorting direction (DIR_ASCENDING or DIR_DESCENDING)
 *
 * Returns: void
 */
static void merge(void *array, void *left, void *right, int l_size, int r_size, int elemsize, int (*comp)(void*, void*), int direction)
{
    int i = 0, j = 0, k = 0;
    unsigned char *base = (unsigned char *)array;
    unsigned char *lbase = (unsigned char *)left;
    unsigned char *rbase = (unsigned char *)right;

    while (i < l_size && j < r_size) {
        void *lelem = lbase + i * elemsize;
        void *relem = rbase + j * elemsize;

        if (compare_wrapper(comp, lelem, relem, direction) <= 0) {
            move(base + k * elemsize, lelem, elemsize);
            i++;
        } else {
            move(base + k * elemsize, relem, elemsize);
            j++;
        }
        k++;
    }

    while (i < l_size) {
        move(base + k * elemsize, lbase + i * elemsize, elemsize);
        i++;
        k++;
    }

    while (j < r_size) {
        move(base + k * elemsize, rbase + j * elemsize, elemsize);
        j++;
        k++;
    }
}

/*
 * mergesort_recursive - Recursive merge sort implementation
 *
 * @array: pointer to array to sort
 * @size: number of elements in array
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @direction: sorting direction (DIR_ASCENDING or DIR_DESCENDING)
 *
 * Returns: void
 */
static void mergesort_recursive(void *array, int size, int elemsize, int (*comp)(void*, void*), int direction)
{
    if (size < 2) return;

    int mid = size / 2;
    int left_size = mid;
    int right_size = size - mid;
    void *left = malloc(left_size * elemsize);
    void *right = malloc(right_size * elemsize);

    if (!left || !right) {
        free(left);
        free(right);
        return;
    }

    move(left, array, left_size * elemsize);
    move(right, (unsigned char *)array + mid * elemsize, right_size * elemsize);

    mergesort_recursive(left, left_size, elemsize, comp, direction);
    mergesort_recursive(right, right_size, elemsize, comp, direction);

    merge(array, left, right, left_size, right_size, elemsize, comp, direction);

    free(left);
    free(right);
}

/*
 * sort_merge - Merge sort algorithm
 *
 * @array: pointer to array to sort
 * @size: number of elements in array
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @direction: sorting direction (DIR_ASCENDING or DIR_DESCENDING)
 *
 * Returns: void
 */
static void sort_merge(void *array, int size, int elemsize, int (*comp)(void*, void*), int direction)
{
    mergesort_recursive(array, size, elemsize, comp, direction);
}

/*
 * heapify - Helper function for heap sort
 *
 * @array: pointer to array
 * @size: heap size
 * @i: root index
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @direction: sorting direction (DIR_ASCENDING or DIR_DESCENDING)
 *
 * Returns: void
 */
static void heapify(void *array, int size, int i, int elemsize, int (*comp)(void*, void*), int direction)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    unsigned char *base = (unsigned char *)array;

    if (left < size && compare_wrapper(comp, base + left * elemsize, base + largest * elemsize, direction) > 0) {
        largest = left;
    }

    if (right < size && compare_wrapper(comp, base + right * elemsize, base + largest * elemsize, direction) > 0) {
        largest = right;
    }

    if (largest != i) {
        swap(base + i * elemsize, base + largest * elemsize, elemsize);
        heapify(array, size, largest, elemsize, comp, direction);
    }
}

/*
 * sort_heap - Heap sort algorithm
 *
 * @array: pointer to array to sort
 * @size: number of elements in array
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @direction: sorting direction (DIR_ASCENDING or DIR_DESCENDING)
 *
 * Returns: void
 */
static void sort_heap(void *array, int size, int elemsize, int (*comp)(void*, void*), int direction)
{
    int i;
    unsigned char *base = (unsigned char *)array;

    for (i = size / 2 - 1; i >= 0; i--) {
        heapify(array, size, i, elemsize, comp, direction);
    }

    for (i = size - 1; i > 0; i--) {
        swap(base, base + i * elemsize, elemsize);
        heapify(array, i, 0, elemsize, comp, direction);
    }
}

/*
 * sort - Main interface function for sorting
 *
 * @array: pointer to array to sort
 * @size: number of elements in array
 * @elemsize: size of each element in bytes
 * @comp: comparison function pointer
 * @method: sorting method
 * @direction: sorting direction
 *
 * Returns: error code (ERR_SUCCESS on success, negative on error)
 */
int sort(void *array, int size, int elemsize, int (*comp)(void*, void*), int method, int direction)
{
    if (array == NULL) {
        return ERR_NULL_ARRAY;
    }

    if (size <= 0) {
        return ERR_INVALID_SIZE;
    }

    if (elemsize <= 0) {
        return ERR_INVALID_ELEM;
    }

    if (comp == NULL) {
        return ERR_NULL_COMP;
    }

    if (method < SORT_BUBBLE || method > SORT_HEAP) {
        return ERR_INVALID_METHOD;
    }

    if (direction != DIR_ASCENDING && direction != DIR_DESCENDING) {
        return ERR_INVALID_DIR;
    }

    switch (method) {
        case SORT_BUBBLE:
            sort_bubble(array, size, elemsize, comp, direction);
            break;
        case SORT_INSERTION:
            sort_insertion(array, size, elemsize, comp, direction);
            break;
        case SORT_SELECTION:
            sort_selection(array, size, elemsize, comp, direction);
            break;
        case SORT_COMB:
            sort_comb(array, size, elemsize, comp, direction);
            break;
        case SORT_SHELL:
            sort_shell(array, size, elemsize, comp, direction);
            break;
        case SORT_QUICK:
            sort_quick(array, size, elemsize, comp, direction);
            break;
        case SORT_MERGE:
            sort_merge(array, size, elemsize, comp, direction);
            break;
        case SORT_HEAP:
            sort_heap(array, size, elemsize, comp, direction);
            break;
        default:
            return ERR_INVALID_METHOD;
    }

    return ERR_SUCCESS;
}

/*
 * compare_char - Comparison function for char type
 *
 * @a: pointer to first char
 * @b: pointer to second char
 *
 * Returns: -1 if a < b, 0 if a == b, 1 if a > b
 */
int compare_char(void *a, void *b)
{
    char ca = *(char*)a;
    char cb = *(char*)b;

    if (ca < cb) return -1;
    if (ca > cb) return 1;
    return 0;
}

/*
 * compare_int - Comparison function for int type
 *
 * @a: pointer to first int
 * @b: pointer to second int
 *
 * Returns: -1 if a < b, 0 if a == b, 1 if a > b
 */
int compare_int(void *a, void *b)
{
    int ia = *(int*)a;
    int ib = *(int*)b;

    if (ia < ib) return -1;
    if (ia > ib) return 1;
    return 0;
}

/*
 * compare_double - Comparison function for double type
 *
 * @a: pointer to first double
 * @b: pointer to second double
 *
 * Returns: -1 if a < b, 0 if a == b, 1 if a > b
 */
int compare_double(void *a, void *b)
{
    double da = *(double*)a;
    double db = *(double*)b;

    if (da < db) return -1;
    if (da > db) return 1;
    return 0;
}