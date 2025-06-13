#include <check.h>
#include <stdlib.h>
#include <stdio.h>
#include "quick_sort.h"

// Вспомогательная функция для сравнения массивов
int arrays_equal(int a[], int b[], int n) {
    if (n == 0) return 1;
    for (int i = 0; i < n; i++) {
        if (a[i] != b[i]) return 0;
    }
    return 1;
}

// Вспомогательная функция для создания строки с элементами массива
void array_to_string(int arr[], int n, char *buffer, size_t buf_size) {
    size_t offset = 0;
    offset += snprintf(buffer + offset, buf_size - offset, "[");
    for (int i = 0; i < n; i++) {
        if (i > 0)
            offset += snprintf(buffer + offset, buf_size - offset, ", ");
        offset += snprintf(buffer + offset, buf_size - offset, "%d", arr[i]);
        if (offset >= buf_size) break;
    }
    snprintf(buffer + offset, buf_size - offset, "]");
}

#define BUF_SIZE 256

#define ASSERT_ARRAYS_EQUAL(arr, expected, n) do { \
    if (!arrays_equal(arr, expected, n)) { \
        char got_str[BUF_SIZE]; \
        char exp_str[BUF_SIZE]; \
        array_to_string(arr, n, got_str, BUF_SIZE); \
        array_to_string(expected, n, exp_str, BUF_SIZE); \
        ck_abort_msg("Массивы не совпадают!\nПолучено: %s\nОжидалось: %s", got_str, exp_str); \
    } \
} while(0)

START_TEST(test_sorted_array) {
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 5, 5};
    quick_sort(arr, 5);
    ASSERT_ARRAYS_EQUAL(arr, expected, 5);
}
END_TEST

START_TEST(test_reverse_array) {
    int arr[] = {5, 4, 3, 2, 1};
    int expected[] = {1, 2, 3, 4, 5};
    quick_sort(arr, 5);
    ASSERT_ARRAYS_EQUAL(arr, expected, 5);
}
END_TEST

START_TEST(test_unsorted_array) {
    int arr[] = {3, 1, 4, 5, 2};
    int expected[] = {1, 2, 3, 4, 5};
    quick_sort(arr, 5);
    ASSERT_ARRAYS_EQUAL(arr, expected, 5);
}
END_TEST

START_TEST(test_empty_array) {
    int *arr = NULL;
    int *expected = NULL;
    quick_sort(arr, 0);
    ASSERT_ARRAYS_EQUAL(arr, expected, 0);
}
END_TEST

START_TEST(test_single_element_array) {
    int arr[] = {42};
    int expected[] = {42};
    quick_sort(arr, 1);
    ASSERT_ARRAYS_EQUAL(arr, expected, 1);
}
END_TEST

START_TEST(test_repeating_elements) {
    int arr[] = {5, 2, 5, 1, 2};
    int expected[] = {1, 2, 2, 5, 5};
    quick_sort(arr, 5);
    ASSERT_ARRAYS_EQUAL(arr, expected, 5);
}
END_TEST

START_TEST(test_negative_numbers) {
    int arr[] = {-5, -2, -1, -4, -3};
    int expected[] = {-5, -4, -3, -2, -1};
    quick_sort(arr, 5);
    ASSERT_ARRAYS_EQUAL(arr, expected, 5);
}
END_TEST

START_TEST(test_zeros_and_pos_neg) {
    int arr[] = {-1, 0, 5, -3, 0, 2};
    int expected[] = {-3, -1, 0, 0, 2, 5};
    quick_sort(arr, 6);
    ASSERT_ARRAYS_EQUAL(arr, expected, 6);
}
END_TEST

START_TEST(test_all_elements_equal) {
    int arr[] = {7, 7, 7, 7, 7};
    int expected[] = {7, 7, 7, 7, 7};
    quick_sort(arr, 5);
    ASSERT_ARRAYS_EQUAL(arr, expected, 5);
}
END_TEST

Suite* quick_sort_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("QuickSort");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_sorted_array);
    tcase_add_test(tc_core, test_reverse_array);
    tcase_add_test(tc_core, test_unsorted_array);
    tcase_add_test(tc_core, test_empty_array);
    tcase_add_test(tc_core, test_single_element_array);
    tcase_add_test(tc_core, test_repeating_elements);
    tcase_add_test(tc_core, test_negative_numbers);
    tcase_add_test(tc_core, test_zeros_and_pos_neg);
    tcase_add_test(tc_core, test_all_elements_equal);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = quick_sort_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_NORMAL);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (number_failed == 0) ? 0 : 1;
}
