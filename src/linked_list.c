#include <stdlib.h>

struct lnode {
  int data;
  struct lnode *next;
};

typedef struct lnode lnode;

void list_free(lnode *node) {
  if (node == NULL)
    return;
  lnode *curr = node;
  lnode *next = curr;
  while (curr != NULL) {
    next = curr->next;
    free(curr);
    curr = next;
  }
}

lnode *list_new(int data) {
  lnode *node = malloc(sizeof(lnode));
  if (!node)
    return NULL;
  node->data = data;
  node->next = NULL;
  return node;
}

void list_add(lnode *node, int data) {
  if (node == NULL) {
    node = list_new(data);
    return;
  }
  lnode *n = node;
  while (n->next != NULL)
    n = n->next;
  n->next = list_new(data);
}
