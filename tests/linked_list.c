#include "../src/linked_list.c"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_list(lnode *node, int *e, size_t len);

int empty() {
  lnode *node = list_new(0);
  list_free(node);
  return EXIT_SUCCESS;
}

int len_5() {
  lnode *node = list_new(0);
  list_add(node, 1);
  list_add(node, 2);
  list_add(node, 3);
  list_add(node, 4);
  int e[] = {0, 1, 2, 3, 4, 5};

  lnode *n = node;
  int o = check_list(n, e, 5);
  list_free(node);
  return o;
}

int main() {
  int failures = EXIT_SUCCESS;
  failures += empty();
  failures += len_5();
  return failures;
}

int check_list(lnode *node, int *e, size_t len) {
  size_t i = 0;
  int failures = EXIT_SUCCESS;
  while (i < len && node != NULL) {
    if (node->data != e[i]) {
      printf("incorrect input found at index %zu\n", i);
      failures += EXIT_FAILURE;
    }
    node = node->next;
    i++;
  }
  if (node && node->next != NULL) {
    while (node->next != NULL)
      node = node->next;
    printf("node length %zu is more than the expected %zu\n", i, len);
  }
  if (i < len) {
    printf("node length %zu is less than the expected %zu\n", i, len);
  }

  return failures;
}
