#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum color {
  Red,
  Black,
} color;

typedef struct red_black_node {
  struct red_black_node *parent;
  struct red_black_node *left;
  struct red_black_node *right;
  enum color col;
  int data;
} rbnode;

void free_rbnode(rbnode *node) {
  if (!node)
    return;
  free_rbnode(node->left);
  free_rbnode(node->right);
  free(node);
}

void rbnode_link(rbnode *parent, rbnode *child, int right) {
  assert(parent);
  if (right)
    parent->right = child;
  else
    parent->left = child;
  if (child)
    child->parent = parent;
}

rbnode *rbnode_root(rbnode *node) {
  rbnode *curr = node;
  while (curr->parent)
    curr = curr->parent;
  return curr;
}

rbnode red_rbnode(int data) {
  rbnode node = {};
  node.parent = node.left = node.right = NULL;
  node.col = Red;
  node.data = data;
  return node;
}

rbnode black_rbnode(int data) {
  rbnode node = {};
  node.parent = node.left = node.right = NULL;
  node.col = Black;
  node.data = data;
  return node;
}

rbnode *new_rbnode(rbnode node) {
  rbnode *nnode = malloc(sizeof(rbnode));
  assert(nnode);
  *nnode = node;
  return nnode;
}
rbnode *new_black_rbnode(int data) { return new_rbnode(black_rbnode(data)); }
rbnode *new_red_rbnode(int data) { return new_rbnode(red_rbnode(data)); }

rbnode *clone_rbnode(rbnode *node) {
  if (!node)
    return NULL;
  rbnode *curr = malloc(sizeof(rbnode));
  assert(curr);
  curr->parent = NULL;
  curr->col = node->col;
  curr->data = node->data;
  curr->left = clone_rbnode(node->left);
  curr->right = clone_rbnode(node->right);
  if (curr->left)
    curr->left->parent = curr;
  if (curr->right)
    curr->right->parent = curr;
  return curr;
}

rbnode *search_rbnode(rbnode *node, int data) {
  if (!node)
    return NULL;
  else if (node->data < data)
    return search_rbnode(node->right, data);
  else if (node->data > data)
    return search_rbnode(node->left, data);
  else
    return node;
}

static inline int rbnode_dir(rbnode *node) {
  return node == node->parent->right;
}

void rbnode_rotate_left(rbnode *g) {
  rbnode *gp = g->parent;
  rbnode *p = g->right;
  rbnode *n = p->left;
  int right = gp ? rbnode_dir(g) : 0;
  rbnode_link(g, n, 1);
  rbnode_link(p, g, 0);
  if (gp)
    rbnode_link(gp, p, right);
  else
    p->parent = NULL;
}

void rbnode_rotate_right(rbnode *g) {
  rbnode *gp = g->parent;
  rbnode *p = g->left;
  rbnode *n = p->right;
  int right = gp ? rbnode_dir(g) : 0;
  rbnode_link(g, n, 0);
  rbnode_link(p, g, 1);
  if (gp)
    rbnode_link(gp, p, right);
  else
    p->parent = NULL;
}

// based off
// https://www.cs.emory.edu/~cheung/Courses/253/Syllabus/nodes/RB-insert2.html

// expects n->parent to be red
void rbnode_insert_fix(rbnode *n) {
start:;
  rbnode *p = n->parent;
  rbnode *gp = p->parent;
  rbnode *u = rbnode_dir(p) ? gp->left : gp->right;
  if (u && u->col == Red) { // case 3 ------------------------------------------
    rbnode *ggp = gp->parent;
    gp->col = ggp ? Red : Black;
    u->col = Black;
    p->col = Black;
    if (ggp && ggp->col == Red) {
      n = gp;
      goto start;
    }
    return;
  } // case 4 ------------------------------------------------------------------
  int p_right = rbnode_dir(p);
  int n_right = rbnode_dir(n);
  if (p_right != n_right) {
    if (p_right)
      rbnode_rotate_right(p);
    else
      rbnode_rotate_left(p);
  }
  if (p_right)
    rbnode_rotate_left(gp);
  else
    rbnode_rotate_right(gp);
  gp->parent->col = Black;
  gp->col = Red;
}

void rbnode_insert(rbnode **node, int data) {
  assert(node);
  rbnode *n = new_red_rbnode(data);
  assert(n);
  if (!*node) { // case 1 ------------------------------------------------------
    n->col = Black;
    *node = n;
    return;
  }
  rbnode *p = *node;
  rbnode *curr = *node;
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
  rbnode_insert_fix(n);
}
