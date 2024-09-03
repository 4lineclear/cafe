#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum color {
  Red,
  Black,
} color;

typedef struct red_black_tree {
  struct red_black_tree *parent;
  struct red_black_tree *left;
  struct red_black_tree *right;
  enum color col;
  int data;
} rbtree;

void free_rbtree(rbtree *tree) {
  if (NULL == tree)
    return;
  free_rbtree(tree->left);
  free_rbtree(tree->right);
  free(tree);
}

void rbtree_link(rbtree *parent, rbtree *child, int right) {
  assert(NULL != parent);
  assert(NULL != child);
  if (right)
    parent->right = child;
  else
    parent->left = child;
  child->parent = parent;
}

rbtree *red_rbtree(int data) {
  rbtree *tree = malloc(sizeof(rbtree));
  assert(NULL != tree);
  tree->parent = NULL;
  tree->left = NULL;
  tree->right = NULL;
  tree->col = Red;
  tree->data = data;
  return tree;
}

rbtree *black_rbtree(int data) {
  rbtree *tree = malloc(sizeof(rbtree));
  assert(NULL != tree);
  tree->parent = NULL;
  tree->left = NULL;
  tree->right = NULL;
  tree->col = Black;
  tree->data = data;
  return tree;
}

rbtree *clone_rbtree(rbtree *tree) {
  if (NULL == tree)
    return NULL;
  rbtree *curr = malloc(sizeof(rbtree));
  assert(NULL != curr);
  curr->parent = NULL;
  curr->col = tree->col;
  curr->data = tree->data;
  curr->left = clone_rbtree(tree->left);
  curr->right = clone_rbtree(tree->right);
  if (NULL != curr->left)
    curr->left->parent = curr;
  if (NULL != curr->right)
    curr->right->parent = curr;
  return curr;
}

static inline int rbtree_dir(rbtree *tree) {
  return tree == tree->parent->right;
}

void rbtree_rotate_left(rbtree *x) {
  rbtree *p = x->parent;
  rbtree *y = x->right;
  rbtree *b = y->left;
  int x_right = rbtree_dir(x);
  rbtree_link(x, b, 1);
  rbtree_link(y, x, 0);
  rbtree_link(p, y, x_right);
}

void rbtree_rotate_right(rbtree *x) {
  rbtree *p = x->parent;
  rbtree *y = x->left;
  rbtree *b = y->right;
  int x_right = rbtree_dir(x);
  rbtree_link(x, b, 0);
  rbtree_link(y, x, 1);
  rbtree_link(p, y, x_right);
}

void rbtree_insert(rbtree *node, int data) {}
