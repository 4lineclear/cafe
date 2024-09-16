#include "../src/single_linked_list.c"
#include "../utils/testing.c"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void empty();
void append();
void prepend();
void from_arr();
void search();
void copy_before();
void copy_after();
void extend_before();
void extend_after();
void nth();
void compare_sln(sll *list, int *e, size_t len);

int main() {
  empty();
  append();
  prepend();
  from_arr();
  search();
  copy_before();
  extend_before();
  extend_after();
  copy_after();
  nth();
  return EXIT_SUCCESS;
}

void empty() {
  sln *node = new_sln(0);
  free(node);
  sll list = new_sll(0);
  free_sll(&list);
}

void append() {
  sll list = new_sll(0);
  sll_append(&list, 1);
  sll_append(&list, 2);
  sll_append(&list, 3);
  sll_append(&list, 4);
  sll_append(&list, 5);
  int e[] = {0, 1, 2, 3, 4, 5, 5};
  compare_sln(&list, e, 6);
  free_sll(&list);
}

void prepend() {
  sll list = new_sll(5);
  sll_prepend(&list, 4);
  sll_prepend(&list, 3);
  sll_prepend(&list, 2);
  sll_prepend(&list, 1);
  sll_prepend(&list, 0);
  int e[] = {0, 1, 2, 3, 4, 5};
  compare_sln(&list, e, 6);
  free_sll(&list);
}

void from_arr() {
  int e[] = {0, 1, 2, 3, 4, 5};
  sll list = sll_from_arr(e, 6);
  compare_sln(&list, e, 6);
  free_sll(&list);
}

void search() {
  sll list = sll_from_arr((int[]){0, 1, 2, 3, 4, 5}, 6);
  for (int i = 0; i < 6; i++) {
    sln *o = sll_search(&list, i);
    if (o) {
      assertf(o->data == i, "%d not found, %d found instead\n", i, o->data)
    } else
      assertf(0, "%d not found, NULL found instead\n", i);
  }
  free_sll(&list);
}

void copy_before() {
  sll list = empty_sll();
  sll a = sll_from_arr((int[]){3, 4, 5}, 3);
  sll b = sll_from_arr((int[]){0, 1, 2}, 3);
  int e[] = {0, 1, 2, 3, 4, 5};
  sll_copy_before(&list, a.head);
  sll_copy_before(&list, b.head);
  compare_sln(&list, e, 6);
  free_sll(&list);
  free_sll(&a);
  free_sll(&b);
}

void copy_after() {
  sll list = empty_sll();
  sll a = sll_from_arr((int[]){0, 1, 2}, 3);
  sll b = sll_from_arr((int[]){3, 4, 5}, 3);
  int e[] = {0, 1, 2, 3, 4, 5};
  sll_copy_after(&list, a.head);
  sll_copy_after(&list, b.head);
  compare_sln(&list, e, 6);
  free_sll(&list);
  free_sll(&a);
  free_sll(&b);
}

void extend_before() {
  sll list = empty_sll();
  sll a = sll_from_arr((int[]){3, 4, 5}, 3);
  sll b = sll_from_arr((int[]){0, 1, 2}, 3);
  int e[] = {0, 1, 2, 3, 4, 5};
  sll_extend_before(&list, a.head);
  sll_extend_before(&list, b.head);
  compare_sln(&list, e, 6);
  free_sll(&list);
}

void extend_after() {
  sll list = empty_sll();
  sll a = sll_from_arr((int[]){0, 1, 2}, 3);
  sll b = sll_from_arr((int[]){3, 4, 5}, 3);
  int e[] = {0, 1, 2, 3, 4, 5};
  sll_extend_after(&list, a.head);
  sll_extend_after(&list, b.head);
  compare_sln(&list, e, 6);
  free_sll(&list);
}

void nth() {
  sll list = sll_from_arr((int[]){0, 1, 2, 3, 4, 5}, 6);
  for (int i = 0; i < 6; i++) {
    sln *o = sll_search(&list, i);
    if (o) {
      assertf(o->data == i, "%d not found, %d found instead\n", i, o->data)
    } else
      assertf(0, "%d not found, NULL foudn instead\n", i);
  }
  free_sll(&list);
}

void compare_sln(sll *list, int *e, const size_t len) {
  size_t i = 0;
  sln *node = list->head;
  while (node && i < len) {
    assertf(node->data == e[i],
            "The node at index %zu holds data %d, which differs from the "
            "expected value of %d.",
            i, node->data, e[i]);
    node = node->next;
    i++;
  }
  if (node) {
    while (node->next) {
      i++;
      node = node->next;
    }
    assertf(0, "node length %zu is more than the expected %zu\n", i, len);
  }
  assertf(i >= len, "node length %zu is less than the expected %zu\n", i, len);
}
