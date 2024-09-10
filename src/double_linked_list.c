#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct double_linked_list {
  struct double_list_node *head;
  struct double_list_node *tail;
} dll;

typedef struct double_list_node {
  int data;
  struct double_list_node *prev;
  struct double_list_node *next;
} dln;

int dll_empty(dll *list) {
  if (!list->head) {
    assert(!list->tail);
    return 1;
  }
  if (!list->tail) {
    assert(!list->head);
    return 1;
  }
  return 0;
}

void free_dll(dll *list) {
  assert(list);
  dln *curr = list->head;
  dln *next = curr;
  while (curr) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  list->tail = NULL; // for when head = tail
}

void join_dln(dln *prev, dln *next) {
  assert(prev);
  assert(next);
  prev->next = next;
  next->prev = prev;
}

dln *new_dln(int data) {
  dln *node = malloc(sizeof(dln));
  assert(node);
  node->data = data;
  node->prev = NULL;
  node->next = NULL;
  return node;
}

dll empty_dll() { return (dll){.head = NULL, .tail = NULL}; }

dll new_dll(int data) {
  dln *node = new_dln(data);
  return (dll){.head = node, .tail = node};
}

void dll_append(dll *list, int data) {
  assert(list);
  dln *new = new_dln(data);
  assert(new);
  if (dll_empty(list)) {
    list->head = new;
    list->tail = new;
  } else {
    join_dln(list->tail, new);
    list->tail = new;
  }
}

void dll_prepend(dll *list, int data) {
  assert(list);
  dln *new = new_dln(data);
  assert(new);
  if (dll_empty(list)) {
    list->head = new;
    list->tail = new;
  } else {
    join_dln(new, list->head);
    list->head = new;
  }
}

dll copy_dln(dln *node) {
  dll list = empty_dll();
  dln *curr = node;
  while (curr) {
    dll_append(&list, curr->data);
    curr = curr->next;
  }
  return list;
}

dll dll_from_arr(int *items, size_t len) {
  if (len < 1)
    return empty_dll();
  dll list = new_dll(items[0]);
  size_t i;
  for (i = 1; i < len; i++)
    dll_append(&list, items[i]);
  return list;
}

dln *dll_search(dll *list, int data) {
  assert(list);
  dln *curr;
  for (curr = list->head; curr; curr = curr->next)
    if (curr->data == data)
      return curr;
  return NULL;
}

dln *dll_rsearch(dll *list, int data) {
  assert(list);
  dln *curr;
  for (curr = list->tail; curr; curr = curr->prev)
    if (curr->data == data)
      return curr;
  return NULL;
}

void dll_copy_after(dll *list, dln *node) {
  assert(list);
  dll copy = copy_dln(node);
  if (dll_empty(list)) {
    *list = copy;
  } else {
    join_dln(list->tail, copy.head);
    list->tail = copy.tail;
  }
}

void dll_copy_before(dll *list, dln *node) {
  assert(list);
  dll copy = copy_dln(node);
  if (dll_empty(list)) {
    *list = copy;
  } else {
    join_dln(copy.tail, list->head);
    list->head = copy.head;
  }
}

void dll_extend_after(dll *list, dln *nodes) {
  assert(list);
  if (!nodes)
    return;
  dln *curr = nodes;
  while (curr->next)
    curr = curr->next;
  if (dll_empty(list)) {
    list->head = nodes;
    list->tail = curr;
  } else {
    join_dln(list->tail, nodes);
    list->tail = curr;
  }
}

void dll_extend_before(dll *list, dln *nodes) {
  assert(list);
  if (!nodes)
    return;
  dln *curr = nodes;
  while (curr->next)
    curr = curr->next;
  if (dll_empty(list)) {
    list->head = nodes;
    list->tail = curr;
  } else {
    join_dln(curr, list->head);
    list->head = nodes;
  }
}

dln *dln_nth(dln *node, size_t n) {
  size_t i = 0;
  dln *curr = node;
  while (i < n && curr)
    curr = curr->next;
  return curr;
}
