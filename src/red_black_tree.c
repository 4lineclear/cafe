/*
 * visualization used from
 * https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
 * */
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

static inline int rbnode_dir(rbnode *node) {
  return node == node->parent->right;
}

static inline int black(rbnode *node) { return !node || node->col == Black; }
static inline int red(rbnode *node) { return !black(node); }

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

void rbnode_unlink(rbnode *child) {
  if (!child || !child->parent)
    return;
  if (child == child->parent->right)
    child->parent->right = NULL;
  else if (child == child->parent->left)
    child->parent->left = NULL;
  else
    exit(EXIT_FAILURE);
  child->parent = NULL;
}

rbnode *rbnode_root(rbnode *node) {
  if (!node)
    return NULL;
  rbnode *curr = node;
  while (curr->parent)
    curr = curr->parent;
  return curr;
}

rbnode *rbnode_min(rbnode *node) {
  if (!node)
    return NULL;
  rbnode *curr = node;
  while (curr->left)
    curr = curr->left;
  return curr;
}

rbnode *rbnode_max(rbnode *node) {
  if (!node)
    return NULL;
  rbnode *curr = node;
  while (curr->right)
    curr = curr->right;
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

void rbnode_rotate_left(rbnode *gp) {
  rbnode *ggp = gp->parent;
  rbnode *p = gp->right;
  rbnode *n = p->left;
  int right = ggp ? rbnode_dir(gp) : 0;
  rbnode_link(gp, n, 1);
  rbnode_link(p, gp, 0);
  if (ggp)
    rbnode_link(ggp, p, right);
  else
    p->parent = NULL;
}

void rbnode_rotate_right(rbnode *gp) {
  rbnode *ggp = gp->parent;
  rbnode *p = gp->left;
  rbnode *n = p->right;
  int right = ggp ? rbnode_dir(gp) : 0;
  rbnode_link(gp, n, 0);
  rbnode_link(p, gp, 1);
  if (ggp)
    rbnode_link(ggp, p, right);
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

void rbnode_insert(rbnode **root, int data) {
  assert(root);
  rbnode *n = new_red_rbnode(data);
  assert(n);
  if (!*root) { // case 1 ------------------------------------------------------
    n->col = Black;
    *root = n;
    return;
  }
  rbnode *p = *root;
  rbnode *curr = *root;
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
  *root = rbnode_root(*root); // if root is changed
}

rbnode *rbnode_from_arr(int *data, size_t len) {
  size_t i;
  rbnode *root;
  for (i = 0, root = NULL; i < len; i++)
    rbnode_insert(&root, data[i]);
  return root;
}

// based off https://www.youtube.com/watch?v=eoQpRtMpA9I
void rbnode_delete_fix(rbnode *x, rbnode *p, int x_right) {
  if (red(x)) {
  RBDF_0: // -------------------------------------------------------------------
    x->col = Black;
    return;
  }
  rbnode *w = x_right ? p->left : p->right;
RBDF_BLACK:
  if (!w)
    goto RBDF_2;
  if (w->col == Red)
    goto RBDF_1;
  int lb = black(w->left);
  int rb = black(w->right);
  if (lb && rb)
    goto RBDF_2;
  if (x_right ? (lb && !rb) : (rb && !lb))
    goto RBDF_3;
  if (x_right ? !lb : !rb)
    goto RBDF_4;
  exit(1);
RBDF_1: // --------------------------------------------------------------------
  if (w)
    w->col = Black;
  p->col = Red;
  if (x_right) {
    rbnode_rotate_right(p);
    w = p->left;
  } else {
    rbnode_rotate_left(p);
    w = p->right;
  }
  goto RBDF_BLACK;
RBDF_2: // --------------------------------------------------------------------
  w->col = Red;
  x = p;
  p = p->parent;
  x_right = rbnode_dir(x);
  if (red(x))
    goto RBDF_0;
  else if (!p) // root
    goto RBDF_DONE;
  else
    goto RBDF_BLACK;
RBDF_3: // --------------------------------------------------------------------
  w->col = Red;
  if (x_right) {
    if (w->right)
      w->right->col = Black;
    rbnode_rotate_left(w);
    w = p->left;
  } else {
    if (w->left)
      w->left->col = Black;
    rbnode_rotate_right(w);
    w = p->right;
  }
  goto RBDF_4;
RBDF_4: // --------------------------------------------------------------------
  w->col = p->col;
  p->col = Black;
  if (x_right) {
    if (w->left)
      w->left->col = Black;
    rbnode_rotate_right(p);
  } else {
    if (w->right)
      w->right->col = Black;
    rbnode_rotate_left(p);
  }
  goto RBDF_DONE;
RBDF_DONE:;
}

void rbnode_delete(rbnode **root, rbnode *del) {
  assert(root);
  if (!del || !*root)
    return;

  rbnode *repl = rbnode_min(del->right);
  rbnode *x = NULL; // case i
  rbnode *p = NULL;
  int x_dir = 0;

  if (del->right) {
    x = del->left ? repl->right : del->right; // case iii : ii
    x_dir = 1;
  } else if (del->left) { // case ii
    x = repl = del->left;
    x_dir = 0;
  }

  if (x)
    p = x->parent;
  else if (repl)
    p = repl;
  else
    p = del->parent;

  if (repl) {
    rbnode_link(repl->parent, repl->right, rbnode_dir(repl));
    rbnode_link(repl, del->left, 0);
    rbnode_link(repl, del->right, 1);
  }

  if (*root == del)
    *root = repl;
  else
    rbnode_link(del->parent, repl, rbnode_dir(del));
  if (del->col == Red) {
    if (!repl || repl->col == Red) { // a: do nothing
    } else {                         // b:
      repl->col = Red;
      rbnode_delete_fix(x, p, x_dir);
      *root = rbnode_root(*root);
    }
  } else {
    if (repl && repl->col == Red) { // c:
      repl->col = Black;
    } else if (*root == x) { // d: do nothing
    } else {                 // e:
      rbnode_delete_fix(x, p, x_dir);
      *root = rbnode_root(*root);
    }
  }
  free(del);
}

int rbnode_search_delete(rbnode **root, int data) {
  rbnode *del = search_rbnode(*root, data);
  rbnode_delete(root, del);
  return del ? 1 : 0;
}
