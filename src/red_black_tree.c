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

typedef struct {
  int changed;
  rbnode *root;
} rbnode_deleted;

// based off https://www.youtube.com/watch?v=eoQpRtMpA9I
void rbnode_delete_fix(rbnode *x) {
  if (!x)
    return;
  if (x->col == Red) {
  RBDF_0:
    x->col = Black;
    return;
  }
  int x_right = rbnode_dir(x);
  rbnode *w = x_right ? x->parent->left : x->parent->right;
RBDF_BLACK:;
  if (!w)
    goto RBDF_1;
  if (w->col == Red)
    goto RBDF_2;
  int lb = black(w->left);
  int rb = black(w->right);
  if (lb && rb)
    goto RBDF_1;
  if (x_right ? (lb && !rb) : (rb && !lb))
    goto RBDF_3;
  if (x_right ? !lb : !rb)
    goto RBDF_4;
  exit(1);
RBDF_1:
  puts("1");
  if (w)
    w->col = Black;
  x->parent->col = Red;
  if (x_right) {
    rbnode_rotate_right(x->parent);
    w = x->parent->left;
  } else {
    rbnode_rotate_left(x->parent);
    w = x->parent->right;
  }
  goto RBDF_BLACK;
RBDF_2:
  puts("2");
  w->col = Red;
  x = x->parent;
  if (red(x))
    goto RBDF_0;
  else if (!x->parent) // root
    goto RBDF_DONE;
  else
    goto RBDF_BLACK;
RBDF_3:
  puts("3");
  w->col = Black;
  if (x_right) {
    if (w->right)
      w->right->col = Black;
    rbnode_rotate_left(w);
    w = x->parent->right;
  } else {
    if (w->left)
      w->left->col = Black;
    rbnode_rotate_right(w);
    w = x->parent->left;
  }
  goto RBDF_4;
RBDF_4:
  puts("4");
  w->col = x->parent->col;
  x->parent->col = Black;
  if (x_right) {
    if (w->left)
      w->left->col = Black;
    rbnode_rotate_right(x);
  } else {
    if (w->right)
      w->left->col = Black;
    rbnode_rotate_left(x);
  }
  goto RBDF_DONE;
RBDF_DONE:; // finished state
}

void rbnode_delete(rbnode **root, rbnode *del) {
  assert(root);
  if (!del || !*root)
    return;
  rbnode *repl = rbnode_min(del->right);
  rbnode *x = NULL; // case i
  if (del->right)
    x = del->left ? repl->right : del->right; // case iii : ii
  else if (del->left)                         // case ii
    x = repl = del->left;
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
    if (!repl || repl->col == Red) { // a
      puts("a");                     // do nothing
    } else {                         // b
      puts("b");
      repl->col = Red;
      rbnode_delete_fix(x);
    }
  } else {
    if (repl && repl->col == Red) { // c
      puts("c");
      repl->col = Black;
    } else if (*root == x) { // d
      puts("d");             // do nothing
    } else {                 // e
      puts("e");
      rbnode_delete_fix(x);
    }
  }
  free(del);
}

// deletes the given node, returns the root
//
// precondition: del must be within root's branches
void rbnode_delete2(rbnode **root, rbnode *del) {
  assert(root);
  if (!del || !*root)
    return;
  if (*root == del && !del->left && !del->right) { // case 1 empty root
    free(*root);
    *root = NULL;
    return;
  }
  if (!del->left && !del->right) {
    if (del->col == Red) { // case 2 empty red leaf
      rbnode_unlink(del);
      free(del);
    } else { // case 3 empty black leaf
      if (del->parent->col == Red)
        del->parent->col = Black;
      puts("black leaves not handled");
      exit(EXIT_FAILURE);
    }
    return;
  }
  if (!del->left || !del->right) { // case 4 single child
    rbnode *child = del->left ? del->left : del->right;
    if (del->col == Black)
      child->col = Black;
    child->parent = del->parent;
    if (*root == del)
      *root = child;
    else
      rbnode_link(del->parent, child, rbnode_dir(del));
    free(del);
    return;
  }
  rbnode *x; // del's replacement
  rbnode *w; // x's sibling
  rbnode *y; // x's replacement
  x = rbnode_min(del->right);
  y = x->right;
  if (x == del->right) {
    w = del->left;
    rbnode_link(del, y, 1);
  } else {
    w = x->parent->right;
    rbnode_link(x->parent, y, 0);
  }
  if (x->col == Red) { // case 5 red replacement
    // do nothing
  } else if (y && y->col == Red) { // case 6 black replacement
    y->col = Black;
  } else if (*root == del) {
  } else if (!w ||
             (w->col == Black &&                    //
              black(w->left) && black(w->right))) { // case 6 black replacement
  } else {
    if (red(del)) {
    }
    puts("case not handled");
    exit(EXIT_FAILURE);
  }
  del->data = x->data;
  *root = del->parent ? *root : del;
  free(x);
}

int rbnode_search_delete(rbnode **root, int data) {
  rbnode *del = search_rbnode(*root, data);
  rbnode_delete(root, del);
  return del ? 1 : 0;
}
