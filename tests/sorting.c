#include "../src/sorting.c"
#include <stdio.h>
#include <stdlib.h>

int compare_arrs(int *a, int *b, const size_t len);

int test_selection();

int main() {
  int failures = EXIT_SUCCESS;
  failures += test_selection();
  return EXIT_FAILURE;
}

int test_selection() {
  printf("Testing selection sort");
  const int len = 6;
  int expected[] = {0, 1, 2, 3, 4, 5};
  int to_test[] = {5, 3, 1, 2, 0, 4};
  selection_sort(to_test, len);
  return compare_arrs(expected, to_test, len);
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

void print_arrays(int *a, int *b, const size_t diff, const size_t len) {
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
      printf("incorrect input found at index %zu %d %d\n", i, a[i], b[i]);
      failures += EXIT_FAILURE;
    }
  }
  if (failures != EXIT_SUCCESS) {
    print_arrays(a, b, i, len);
  }
  return failures;
}
