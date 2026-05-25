#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sort.h"

int is_sorted(void *array, int size, int elemsize, int (*comp)(void*, void*), int direction)
{
    unsigned char *base = (unsigned char *)array;
    int i;

    for (i = 0; i < size - 1; i++)
    {
        void *curr = base + i * elemsize;
        void *next = base + (i + 1) * elemsize;
        int result = comp(curr, next);

        if (direction == DIR_ASCENDING)
        {
            if (result > 0) return 0;
        }
        else
        {
            if (result < 0) return 0;
        }
    }
    return 1;
}

void print_test_result(const char *test_name, int passed)
{
    if (passed)
    {
        printf("[PASS] %s\n", test_name);
    }
    else
    {
        printf("[FAIL] %s\n", test_name);
    }
}

void test_bubble_int()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = 7;
    int expected[] = {11, 12, 22, 25, 34, 64, 90};
    int i;
    int passed = 1;

    sort(arr, size, sizeof(int), compare_int, SORT_BUBBLE, DIR_ASCENDING);

    for (i = 0; i < size; i++)
    {
        if (arr[i] != expected[i])
        {
            passed = 0;
            break;
        }
    }

    print_test_result("Bubble sort with integers", passed);
}

void test_insertion_double()
{
    double arr[] = {3.14, 1.59, 2.65, 3.58, 9.79};
    int size = 5;
    int passed;

    sort(arr, size, sizeof(double), compare_double, SORT_INSERTION, DIR_DESCENDING);
    passed = is_sorted(arr, size, sizeof(double), compare_double, DIR_DESCENDING);

    print_test_result("Insertion sort with doubles", passed);
}

void test_selection_char()
{
    char arr[] = {'z', 'y', 'x', 'w', 'v'};
    int size = 5;
    int passed;

    sort(arr, size, sizeof(char), compare_char, SORT_SELECTION, DIR_ASCENDING);
    passed = is_sorted(arr, size, sizeof(char), compare_char, DIR_ASCENDING);

    print_test_result("Selection sort with chars", passed);
}

void test_comb_int()
{
    int arr[] = {5, 1, 4, 2, 8, 0, 3, 7, 6, 9};
    int size = 10;
    int passed;

    sort(arr, size, sizeof(int), compare_int, SORT_COMB, DIR_ASCENDING);
    passed = is_sorted(arr, size, sizeof(int), compare_int, DIR_ASCENDING);

    print_test_result("Comb sort with integers", passed);
}

void test_shell_int()
{
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int size = 10;
    int passed;

    sort(arr, size, sizeof(int), compare_int, SORT_SHELL, DIR_ASCENDING);
    passed = is_sorted(arr, size, sizeof(int), compare_int, DIR_ASCENDING);

    print_test_result("Shell sort", passed);
}

void test_quick_int()
{
    int arr[] = {3, 7, 8, 5, 2, 1, 9, 5, 4};
    int size = 9;
    int passed;

    sort(arr, size, sizeof(int), compare_int, SORT_QUICK, DIR_ASCENDING);
    passed = is_sorted(arr, size, sizeof(int), compare_int, DIR_ASCENDING);

    print_test_result("Quick sort with duplicates", passed);
}

void test_merge_int()
{
    int arr[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
    int size = 10;
    int passed;

    sort(arr, size, sizeof(int), compare_int, SORT_MERGE, DIR_ASCENDING);
    passed = is_sorted(arr, size, sizeof(int), compare_int, DIR_ASCENDING);

    print_test_result("Merge sort", passed);
}

void test_heap_descending()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = 10;
    int passed;

    sort(arr, size, sizeof(int), compare_int, SORT_HEAP, DIR_DESCENDING);
    passed = is_sorted(arr, size, sizeof(int), compare_int, DIR_DESCENDING);

    print_test_result("Heap sort descending", passed);
}

void test_single_element()
{
    int arr[] = {42};
    int size = 1;
    int passed;

    sort(arr, size, sizeof(int), compare_int, SORT_QUICK, DIR_ASCENDING);
    passed = (arr[0] == 42);

    print_test_result("Single element array", passed);
}

void test_two_elements()
{
    int arr[] = {10, 5};
    int size = 2;
    int expected[] = {5, 10};
    int passed = 1;

    sort(arr, size, sizeof(int), compare_int, SORT_BUBBLE, DIR_ASCENDING);

    if (arr[0] != expected[0] || arr[1] != expected[1])
    {
        passed = 0;
    }

    print_test_result("Two element array", passed);
}

void test_all_methods()
{
    int original[] = {5, 2, 8, 1, 9, 3, 7, 4, 6};
    int size = 9;
    int test_arr[9];
    int methods[] = {SORT_BUBBLE, SORT_INSERTION, SORT_SELECTION, SORT_COMB, SORT_SHELL, SORT_QUICK, SORT_MERGE, SORT_HEAP};
    const char *method_names[] = {"BUBBLE", "INSERTION", "SELECTION", "COMB", "SHELL", "QUICK", "MERGE", "HEAP"};
    int i;
    int all_passed = 1;

    for (i = 0; i < 8; i++)
    {
        memcpy(test_arr, original, size * sizeof(int));
        sort(test_arr, size, sizeof(int), compare_int, methods[i], DIR_ASCENDING);

        if (!is_sorted(test_arr, size, sizeof(int), compare_int, DIR_ASCENDING))
        {
            printf("[FAIL] All methods test - %s failed\n", method_names[i]);
            all_passed = 0;
        }
    }

    if (all_passed)
    {
        print_test_result("All methods with identical data", 1);
    }
}

void test_null_array()
{
    int result = sort(NULL, 5, sizeof(int), compare_int, SORT_QUICK, DIR_ASCENDING);
    print_test_result("NULL array handling", (result == ERR_NULL_ARRAY));
}

void test_invalid_size()
{
    int arr[] = {1, 2, 3};
    int result = sort(arr, 0, sizeof(int), compare_int, SORT_QUICK, DIR_ASCENDING);
    print_test_result("Invalid size handling", (result == ERR_INVALID_SIZE));
}

void test_invalid_method()
{
    int arr[] = {1, 2, 3};
    int result = sort(arr, 3, sizeof(int), compare_int, 99, DIR_ASCENDING);
    print_test_result("Invalid method handling", (result == ERR_INVALID_METHOD));
}

void test_invalid_direction()
{
    int arr[] = {1, 2, 3};
    int result = sort(arr, 3, sizeof(int), compare_int, SORT_QUICK, 99);
    print_test_result("Invalid direction handling", (result == ERR_INVALID_DIR));
}

void test_null_comp()
{
    int arr[] = {1, 2, 3};
    int result = sort(arr, 3, sizeof(int), NULL, SORT_QUICK, DIR_ASCENDING);
    print_test_result("NULL comparison function handling", (result == ERR_NULL_COMP));
}

void test_large_array()
{
    int size = 1000;
    int *arr = (int*)malloc(size * sizeof(int));
    int i;
    int passed;

    for (i = 0; i < size; i++)
    {
        arr[i] = size - i;
    }

    sort(arr, size, sizeof(int), compare_int, SORT_QUICK, DIR_ASCENDING);
    passed = is_sorted(arr, size, sizeof(int), compare_int, DIR_ASCENDING);

    print_test_result("Large array (1000 elements)", passed);

    free(arr);
}

void test_already_sorted()
{
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = 10;
    int passed;

    sort(arr, size, sizeof(int), compare_int, SORT_BUBBLE, DIR_ASCENDING);
    passed = is_sorted(arr, size, sizeof(int), compare_int, DIR_ASCENDING);

    print_test_result("Already sorted array", passed);
}

void test_reverse_sorted()
{
    int arr[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    int size = 10;
    int passed;

    sort(arr, size, sizeof(int), compare_int, SORT_QUICK, DIR_ASCENDING);
    passed = is_sorted(arr, size, sizeof(int), compare_int, DIR_ASCENDING);

    print_test_result("Reverse sorted array", passed);
}

void test_all_zeros()
{
    int arr[] = {0, 0, 0, 0, 0};
    int size = 5;
    int passed;

    sort(arr, size, sizeof(int), compare_int, SORT_MERGE, DIR_ASCENDING);
    passed = is_sorted(arr, size, sizeof(int), compare_int, DIR_ASCENDING);

    print_test_result("All elements equal", passed);
}

int main()
{

    printf("\nRUNNING ALL SORTING MODULE TESTS\n");

    test_bubble_int();
    test_insertion_double();
    test_selection_char();
    test_comb_int();
    test_shell_int();
    test_quick_int();
    test_merge_int();
    test_heap_descending();
    test_single_element();
    test_two_elements();
    test_all_methods();

    printf("\nERROR HANDLING TESTS\n");
    test_null_array();
    test_invalid_size();
    test_invalid_method();
    test_invalid_direction();
    test_null_comp();
    test_large_array();
    test_already_sorted();
    test_reverse_sorted();
    test_all_zeros();

    printf("\nALL TESTS COMPLETED\n");

    return 0;
}