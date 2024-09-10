#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct single_linked_list {
  struct single_list_node *head;
  struct single_list_node *tail;
} sll;

typedef struct single_list_node {
  int data;
  struct single_list_node *next;
} sln;

int sll_empty(sll *list) {
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

void free_sll(sll *list) {
  assert(list);
  sln *curr = list->head;
  sln *next = curr;
  while (curr) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  list->tail = NULL; // for when head = tail
}

sln *new_sln(int data) {
  sln *node = malloc(sizeof(sln));
  assert(node);
  node->data = data;
  node->next = NULL;
  return node;
}

sll empty_sll() { return (sll){.head = NULL, .tail = NULL}; }

sll new_sll(int data) {
  sln *node = new_sln(data);
  return (sll){.head = node, .tail = node};
}

void sll_append(sll *list, int data) {
  assert(list);
  sln *new = new_sln(data);
  assert(new);
  if (sll_empty(list)) {
    list->head = new;
    list->tail = new;
  } else {
    list->tail->next = new;
    list->tail = new;
  }
}

void sll_prepend(sll *list, int data) {
  assert(list);
  sln *new = new_sln(data);
  assert(new);
  if (sll_empty(list)) {
    list->head = new;
    list->tail = new;
  } else {
    new->next = list->head;
    list->head = new;
  }
}

sll copy_sln(sln *node) {
  sll list = empty_sll();
  sln *curr = node;
  while (curr) {
    sll_append(&list, curr->data);
    curr = curr->next;
  }
  return list;
}

sll sll_from_arr(int *items, size_t len) {
  if (len < 1)
    return empty_sll();
  sll list = new_sll(items[0]);
  size_t i;
  for (i = 1; i < len; i++)
    sll_append(&list, items[i]);
  return list;
}

sln *sll_search(sll *list, int data) {
  assert(list);
  sln *curr;
  for (curr = list->head; curr; curr = curr->next)
    if (curr->data == data)
      return curr;
  return NULL;
}

void sll_copy_after(sll *list, sln *node) {
  assert(list);
  sll copy = copy_sln(node);
  if (sll_empty(list)) {
    *list = copy;
  } else {
    list->tail->next = copy.head;
    list->tail = copy.tail;
  }
}

void sll_copy_before(sll *list, sln *node) {
  assert(list);
  sll copy = copy_sln(node);
  if (sll_empty(list)) {
    *list = copy;
  } else {
    copy.tail->next = list->head;
    list->head = copy.head;
  }
}

void sll_extend_after(sll *list, sln *node) {
  assert(list);
  if (!node)
    return;
  sln *curr = node;
  while (curr->next)
    curr = curr->next;
  if (sll_empty(list)) {
    list->head = node;
    list->tail = curr;
  } else {
    list->tail->next = node;
    list->tail = curr;
  }
}

void sll_extend_before(sll *list, sln *nodes) {
  assert(list);
  if (!nodes)
    return;
  sln *curr = nodes;
  while (curr->next)
    curr = curr->next;
  if (sll_empty(list)) {
    list->head = nodes;
    list->tail = curr;
  } else {
    curr->next = list->head;
    list->head = nodes;
  }
}

sln *sln_nth(sln *node, size_t n) {
  size_t i = 0;
  sln *curr = node;
  while (i < n && curr)
    curr = curr->next;
  return curr;
}
