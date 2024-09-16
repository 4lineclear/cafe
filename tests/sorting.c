#include "../src/sorting.c"
#include <stdio.h>
#include <stdlib.h>

int compare_arrs(int *a, int *b, const size_t len);
void print_one(int *n, const size_t len);

int standard_test(const char *name, void (*sort)(int *, size_t));

int main() {
  int failures = EXIT_SUCCESS;
  failures += standard_test("selection sort", selection_sort);
  failures += standard_test("bubble sort", bubble_sort);
  failures += standard_test("insertion sort", insertion_sort);
  failures += standard_test("merge sort", merge_sort);
  return failures;
}

int empty_test(void (*sort)(int *, size_t)) {
  const size_t len = 0;
  int expected[] = {};
  int to_test[] = {};
  sort(to_test, len);
  return compare_arrs(expected, to_test, len);
}

int standard_test(const char *name, void (*sort)(int *, size_t)) {
  printf("Testing %s: ", name);
  const size_t len = 6;
  int expected[] = {0, 1, 2, 3, 4, 5};
  int to_test[] = {5, 3, 1, 2, 0, 4};
  print_one(to_test, len);
  puts("");
  sort(to_test, len);
  int o = empty_test(sort) + compare_arrs(expected, to_test, len);
  if (o == EXIT_SUCCESS)
    puts("success");
  return o;
}

void print_one(int *n, const size_t len) {
  size_t i;
  printf("[ ");
  if (len != 0) {
    printf("%d", n[0]);
    for (i = 1; i < len; i++) {
      printf(", %d", n[i]);
    }
  }
  printf(" ]");
}

void print_arrays(int *a, int *b, const size_t len) {
  puts("array a:");
  print_one(a, len);
  puts("");
  puts("array b:");
  print_one(b, len);
  puts("");
}

int compare_arrs(int *a, int *b, const size_t len) {
  size_t i;
  int failures = EXIT_SUCCESS;
  for (i = 0; i < len; i++) {
    if (a[i] != b[i]) {
      printf("incorrect input found at index %zu\n", i);
      failures += EXIT_FAILURE;
    }
  }
  if (failures != EXIT_SUCCESS)
    print_arrays(a, b, len);
  return failures;
}
