#include "../src/single_linked_list.c"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int empty();
int append();
int prepend();
int compare_sln(sll *list, int *e, size_t len);

int main(int argc, char *argv[]) {
  int failures = EXIT_SUCCESS;
  failures += empty();
  failures += append();
  failures += prepend();
  return failures;
}

int empty() {
  sln *node = new_sln(0);
  free(node);
  sll list = new_sll(0);
  free_sll(&list);
  return EXIT_SUCCESS;
}

int append() {
  int failures = EXIT_SUCCESS;
  sll list = new_sll(0);
  sll_append(&list, 1);
  sll_append(&list, 2);
  sll_append(&list, 3);
  sll_append(&list, 4);
  int e[] = {0, 1, 2, 3, 4, 5};
  failures += compare_sln(&list, e, 5);
  free_sll(&list);
  return failures;
}

int prepend() {
  int failures = EXIT_SUCCESS;
  sll list = new_sll(4);
  sll_prepend(&list, 3);
  sll_prepend(&list, 2);
  sll_prepend(&list, 1);
  sll_prepend(&list, 0);
  int e[] = {0, 1, 2, 3, 4};
  failures += compare_sln(&list, e, 5);
  free_sll(&list);
  return failures;
}

int compare_sln(sll *list, int *e, const size_t len) {
  int failures = EXIT_SUCCESS;
  size_t i = 0;
  sln *node = list->head;
  while (node != NULL && i < len) {
    if (node->data != e[i]) {
      printf("incorrect input found at index %zu\n", i);
      failures += EXIT_FAILURE;
    }
    node = node->next;
    i++;
  }
  if (node != NULL) {
    while (node->next != NULL) {
      i++;
      node = node->next;
    }
    printf("node length %zu is more than the expected %zu\n", i, len);
    failures += EXIT_FAILURE;
  }
  if (i < len) {
    printf("node length %zu is less than the expected %zu\n", i, len);
    failures += EXIT_FAILURE;
  }
  return failures;
}
