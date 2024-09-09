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
  if (!tree)
    return;
  free_rbtree(tree->left);
  free_rbtree(tree->right);
  free(tree);
}

void rbtree_link(rbtree *parent, rbtree *child, int right) {
  assert(parent);
  if (right)
    parent->right = child;
  else
    parent->left = child;
  if (child)
    child->parent = parent;
}

rbtree *rbtree_root(rbtree *tree) {
  rbtree *curr = tree;
  while (curr->parent)
    curr = curr->parent;
  return curr;
}

rbtree red_rbtree(int data) {
  rbtree tree = {};
  tree.parent = tree.left = tree.right = NULL;
  tree.col = Red;
  tree.data = data;
  return tree;
}

rbtree black_rbtree(int data) {
  rbtree tree = {};
  tree.parent = tree.left = tree.right = NULL;
  tree.col = Black;
  tree.data = data;
  return tree;
}

rbtree *new_rbtree(rbtree tree) {
  rbtree *ntree = malloc(sizeof(rbtree));
  assert(ntree);
  *ntree = tree;
  return ntree;
}
rbtree *new_black_rbtree(int data) { return new_rbtree(black_rbtree(data)); }
rbtree *new_red_rbtree(int data) { return new_rbtree(red_rbtree(data)); }

rbtree *clone_rbtree(rbtree *tree) {
  if (!tree)
    return NULL;
  rbtree *curr = malloc(sizeof(rbtree));
  assert(curr);
  curr->parent = NULL;
  curr->col = tree->col;
  curr->data = tree->data;
  curr->left = clone_rbtree(tree->left);
  curr->right = clone_rbtree(tree->right);
  if (curr->left)
    curr->left->parent = curr;
  if (curr->right)
    curr->right->parent = curr;
  return curr;
}

static inline int rbtree_dir(rbtree *tree) {
  return tree == tree->parent->right;
}

void rbtree_rotate_left(rbtree *g) {
  rbtree *gp = g->parent;
  rbtree *p = g->right;
  rbtree *n = p->left;
  int right = gp ? rbtree_dir(g) : 0;
  rbtree_link(g, n, 1);
  rbtree_link(p, g, 0);
  if (gp)
    rbtree_link(gp, p, right);
  else
    p->parent = NULL;
}

void rbtree_rotate_right(rbtree *g) {
  rbtree *gp = g->parent;
  rbtree *p = g->left;
  rbtree *n = p->right;
  int right = gp ? rbtree_dir(g) : 0;
  rbtree_link(g, n, 0);
  rbtree_link(p, g, 1);
  if (gp)
    rbtree_link(gp, p, right);
  else
    p->parent = NULL;
}

// based off
// https://www.cs.emory.edu/~cheung/Courses/253/Syllabus/Trees/RB-insert2.html

// expects n->parent to be red
void rbtree_insert_fix(rbtree *n) {
  rbtree *p = n->parent;
  rbtree *g = p->parent;
  rbtree *u = rbtree_dir(p) ? g->left : g->right;
  if (u && u->col == Red) { // case 3 ------------------------------------------
    g->col = g->parent ? Red : Black;
    u->col = Black;
    p->col = Black;
    if (g->parent && g->parent->col == Red)
      rbtree_insert_fix(g);
  } else { // case 4 -----------------------------------------------------------
    int p_right = rbtree_dir(p);
    int n_right = rbtree_dir(n);
    if (p_right != n_right) {
      if (p_right)
        rbtree_rotate_right(p);
      else
        rbtree_rotate_left(p);
    }
    if (p_right)
      rbtree_rotate_left(g);
    else
      rbtree_rotate_right(g);
    g->parent->col = Black;
    g->col = Red;
  }
}

void rbtree_insert(rbtree **tree, int data) {
  assert(tree);
  rbtree *n = new_red_rbtree(data);
  assert(n);
  if (!*tree) { // case 1 ------------------------------------------------------
    n->col = Black;
    *tree = n;
    return;
  }
  rbtree *p = *tree;
  rbtree *curr = *tree;
  while (curr) {
    p = curr;
    if (n->data < curr->data)
      curr = curr->left;
    else
      curr = curr->right;
  }
  if (n->data < p->data)
    p->left = n;
  else
    p->right = n;
  n->parent = p;
  if (p->col == Black) // case 2 -----------------------------------------------
    return;
  rbtree_insert_fix(n);
}
