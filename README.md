NAME
     SortingModule -- generic array sorting library

SYNOPSIS
     #include "sort.h"

     int sort(void *array, int size, int elemsize, int (*comp)(void *, void *),
         int method, int direction);

DESCRIPTION
     The sort() function sorts an array of arbitrary elements.  The caller
     provides a comparison function that knows how to compare two elements.

     The arguments are as follows:

     array    Pointer to the first element of the array.

     size     Number of elements in the array.

     elemsize Size of each element in bytes.

     comp     Comparison function.  It takes two void pointers to elements
              and returns -1 if first is less than second, 0 if equal, 1 if
              greater.

     method   Sorting algorithm to use.  Valid values are:

              SORT_BUBBLE      Bubble sort
              SORT_INSERTION   Insertion sort
              SORT_SELECTION   Selection sort
              SORT_COMB        Comb sort
              SORT_SHELL       Shell sort
              SORT_QUICK       Quick sort
              SORT_MERGE       Merge sort
              SORT_HEAP        Heap sort

     direction Sorting order.  Valid values are:

              DIR_ASCENDING    Sort from smallest to largest
              DIR_DESCENDING   Sort from largest to smallest

RETURN VALUES
     The sort() function returns 0 on success.  On error, it returns one of
     the following negative values:

     ERR_NULL_ARRAY     array is NULL
     ERR_INVALID_SIZE   size is zero or negative
     ERR_INVALID_ELEM   elemsize is zero or negative
     ERR_NULL_COMP      comp is NULL
     ERR_INVALID_METHOD method is not a valid 
     ERR_INVALID_DIR    direction is not DIR_ASCENDING or DIR_DESCENDING
     ERR_ALLOC_FAIL     memory allocation failed

EXAMPLES
     Sort integers using quick sort:

           int compare_int(void *a, void *b)
           {
               int ia = *(int *)a;
               int ib = *(int *)b;
               if (ia < ib) return -1;
               if (ia > ib) return 1;
               return 0;
           }

           int arr[] = {5, 2, 8, 1, 9};
           sort(arr, 5, sizeof(int), compare_int, SORT_QUICK, DIR_ASCENDING);

     Sort characters in reverse order:

           char arr[] = {'a', 'c', 'b', 'd'};
           sort(arr, 4, sizeof(char), compare_char, SORT_HEAP, DIR_DESCENDING);
