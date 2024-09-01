#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

struct single_linked_list {
  struct single_list_node *head;
  struct single_list_node *tail;
};

struct single_list_node {
  int data;
  struct single_list_node *next;
};

typedef struct single_linked_list sll;
typedef struct single_list_node sln;

int sll_empty(sll *list) {
  if (list->head == NULL) {
    assert(list->tail == NULL);
    return 1;
  }
  if (list->tail == NULL) {
    assert(list->head == NULL);
    return 1;
  }
  return 0;
}

void free_sll(sll *list) {
  assert(NULL != list);
  sln *curr = list->head;
  sln *next = curr;
  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
  list->tail = NULL; // for when head = tail
}

sln *new_sln(int data) {
  sln *node = malloc(sizeof(sln));
  assert(NULL != node);
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
  assert(NULL != list);
  sln *new = new_sln(data);
  assert(NULL != new);
  if (sll_empty(list)) {
    list->head = new;
    list->tail = new;
  } else if (list->head == list->tail) {
    list->head->next = new;
    list->tail = new;
  } else {
    list->tail->next = new;
    list->tail = new;
  }
}

void sll_prepend(sll *list, int data) {
  assert(NULL != list);
  sln *new = new_sln(data);
  assert(NULL != new);
  if (sll_empty(list)) {
    list->head = new;
    list->tail = new;
  } else {
    new->next = list->head;
    list->head = new;
  }
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
  assert(NULL != list);
  sln *curr = list->head;
  for (sln *curr = list->head; curr != NULL; curr = curr->next)
    if (curr->data == data)
      return curr;
  return NULL;
}

void sll_copy_after(sll *list, sln *nodes) {
  assert(NULL != list);
  sln *curr = nodes;
  while (curr != NULL) {
    sll_append(list, curr->data);
    curr = curr->next;
  }
}

void sll_copy_before(sll *list, sln *nodes) {
  assert(NULL != list);
  if (NULL == nodes)
    return;
  sln *new_head = new_sln(nodes->data);
  sln *new_curr = new_head;
  sln *curr = nodes->next;
  while (curr != NULL) {
    new_curr->next = new_sln(curr->data);
    new_curr = new_curr->next;
    curr = curr->next;
  }
  new_curr->next = list->head;
  list->head = new_head;
}

void sll_extend_after(sll *list, sln *nodes) {
  assert(NULL != list);
  if (NULL == nodes)
    return;
  sln *curr = nodes;
  while (curr->next != NULL)
    curr = curr->next;
  if (sll_empty(list)) {
    list->head = nodes;
    list->tail = curr;
  } else {
    list->tail->next = nodes;
    list->tail = curr;
  }
}

void sll_extend_before(sll *list, sln *nodes) {
  assert(NULL != list);
  if (NULL == nodes)
    return;
  sln *curr = nodes;
  while (curr->next != NULL)
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
  while (i < n && NULL != curr)
    curr = curr->next;
  return curr;
}
