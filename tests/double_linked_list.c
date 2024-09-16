#include "../src/double_linked_list.c"
#include "../utils/testing.c"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

void empty();
void append();
void prepend();
void from_arr();
void search();
void rsearch();
void copy_before();
void copy_after();
void extend_before();
void extend_after();
void nth();
void compare_dln(dll *list, int *e, size_t len);

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
  dln *node = new_dln(0);
  free(node);
  dll list = new_dll(0);
  free_dll(&list);
}

void append() {
  dll list = new_dll(0);
  dll_append(&list, 1);
  dll_append(&list, 2);
  dll_append(&list, 3);
  dll_append(&list, 4);
  dll_append(&list, 5);
  int e[] = {0, 1, 2, 3, 4, 5, 5};
  compare_dln(&list, e, 6);
  free_dll(&list);
}

void prepend() {
  dll list = new_dll(5);
  dll_prepend(&list, 4);
  dll_prepend(&list, 3);
  dll_prepend(&list, 2);
  dll_prepend(&list, 1);
  dll_prepend(&list, 0);
  int e[] = {0, 1, 2, 3, 4, 5};
  compare_dln(&list, e, 6);
  free_dll(&list);
}

void from_arr() {
  int e[] = {0, 1, 2, 3, 4, 5};
  dll list = dll_from_arr(e, 6);
  compare_dln(&list, e, 6);
  free_dll(&list);
}

void search() {
  dll list = dll_from_arr((int[]){0, 1, 2, 3, 4, 5}, 6);
  for (int i = 0; i < 6; i++) {
    dln *o = dll_search(&list, i);
    if (o) {
      assertf(o->data == i, "%d not found, %d found instead\n", i, o->data)
    } else
      assertf(0, "%d not found, NULL found instead\n", i);
  }
  free_dll(&list);
}

void rsearch() {
  dll list = dll_from_arr((int[]){0, 1, 2, 3, 4, 5}, 6);
  for (int i = 0; i < 6; i++) {
    dln *o = dll_rsearch(&list, i);
    if (o) {
      assertf(o->data == i, "%d not found, %d found instead\n", i, o->data)
    } else
      assertf(0, "%d not found, NULL found instead\n", i);
  }
  free_dll(&list);
}

void copy_before() {
  dll list = empty_dll();
  dll a = dll_from_arr((int[]){3, 4, 5}, 3);
  dll b = dll_from_arr((int[]){0, 1, 2}, 3);
  int e[] = {0, 1, 2, 3, 4, 5};
  dll_copy_before(&list, a.head);
  dll_copy_before(&list, b.head);
  compare_dln(&list, e, 6);
  free_dll(&list);
  free_dll(&a);
  free_dll(&b);
}

void copy_after() {
  dll list = empty_dll();
  dll a = dll_from_arr((int[]){0, 1, 2}, 3);
  dll b = dll_from_arr((int[]){3, 4, 5}, 3);
  int e[] = {0, 1, 2, 3, 4, 5};
  dll_copy_after(&list, a.head);
  dll_copy_after(&list, b.head);
  compare_dln(&list, e, 6);
  free_dll(&list);
  free_dll(&a);
  free_dll(&b);
}

void extend_before() {
  dll list = empty_dll();
  dll a = dll_from_arr((int[]){3, 4, 5}, 3);
  dll b = dll_from_arr((int[]){0, 1, 2}, 3);
  int e[] = {0, 1, 2, 3, 4, 5};
  dll_extend_before(&list, a.head);
  dll_extend_before(&list, b.head);
  compare_dln(&list, e, 6);
  free_dll(&list);
}

void extend_after() {
  dll list = empty_dll();
  dll a = dll_from_arr((int[]){0, 1, 2}, 3);
  dll b = dll_from_arr((int[]){3, 4, 5}, 3);
  int e[] = {0, 1, 2, 3, 4, 5};
  dll_extend_after(&list, a.head);
  dll_extend_after(&list, b.head);
  compare_dln(&list, e, 6);
  free_dll(&list);
}

void nth() {
  dll list = dll_from_arr((int[]){0, 1, 2, 3, 4, 5}, 6);
  for (int i = 0; i < 6; i++) {
    dln *o = dll_search(&list, i);
    if (o) {
      assertf(o->data == i, "%d not found, %d found instead\n", i, o->data)
    } else
      assertf(0, "%d not found, NULL foudn instead\n", i);
  }
  free_dll(&list);
}

void compare_forward(dll *list, int *e, const size_t len) {
  size_t i = 0;
  dln *node = list->head;
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

void compare_reverse(dll *list, int *e, const size_t len) {
  size_t i = len;
  dln *node = list->tail;
  while (node && i > 0) {
    i--;
    assertf(node->data == e[i],
            "The node at index %zu holds data %d, which differs from the "
            "expected value of %d.",
            i, node->data, e[i]);
    node = node->prev;
  }
  if (node) {
    while (node->prev) {
      node = node->prev;
      i -= i > 0;
    }
    assertf(0, "node length %zu is less than the expected %zu\n", i, len);
  }
  assertf(i <= len, "node length %zu is more than the expected %zu\n", i, len);
}

void compare_dln(dll *list, int *e, const size_t len) {
  compare_forward(list, e, len);
  compare_reverse(list, e, len);
}
