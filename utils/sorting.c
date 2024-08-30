#include <stdio.h>
#include <stdlib.h>

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
