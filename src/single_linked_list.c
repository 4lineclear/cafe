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

void assert_sll(sll *list) {
  assert(NULL != list);
  assert(NULL != list->head);
  assert(NULL != list->tail);
}

void free_sll(sll *list) {
  assert_sll(list);
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

sll new_sll(int data) {
  sln *node = new_sln(data);
  return (sll){.head = node, .tail = node};
}

void sll_append(sll *list, int data) {
  assert_sll(list);
  sln *new = new_sln(data);
  assert(NULL != new);
  if (list->head == list->tail) {
    list->head->next = new;
    list->tail = new;
  } else {
    list->tail->next = new;
    list->tail = new;
  }
}

void sll_prepend(sll *list, int data) {
  assert_sll(list);
  sln *new = new_sln(data);
  assert(new);
  if (new == NULL)
    return;
  new->next = list->head;
  list->head = new;
}
