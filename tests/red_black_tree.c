#include "../src/red_black_tree.c"
#include "../utils/testing.c"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cmp_tree(rbtree *, rbtree *);
void clone();
void rotate();
void insert_case1();
void insert_case2a();
void insert_case2b();
void insert_case3a1();
void insert_case3a2();
void insert_case3b1();
void insert_case3b2();
void insert_case4a1();
void insert_case4a2();
void insert_case4b1();
void insert_case4b2();
void insert_casem1();
void insert_casem2();
void print(rbtree *);

#define check_node(N, D, C)                                                    \
  assertf(N != NULL, "given node is null");                                    \
  assertf(N->data == D, "data: actual %d != expected %d", N->data, D);         \
  assertf(N->col == C, "col: actual %d != expected %d", N->col, C)

int main() {
  clone();
  rotate();
  insert_case1();
  insert_case2a();
  insert_case2b();
  insert_case3a1();
  insert_case3a2();
  insert_case3b1();
  insert_case3b2();
  insert_case4a1();
  insert_case4a2();
  insert_case4b1();
  insert_case4b2();
  insert_casem1();
  return EXIT_SUCCESS;
}

void print_tree(rbtree *tree, int depth) {
  if (NULL == tree)
    return;
  printf("%d: %d ", depth, tree->data);
  print_tree(tree->left, depth + 1);
  print_tree(tree->right, depth + 1);
}

rbtree *test_tree_one() {
  rbtree *p = new_black_rbtree(4);
  rbtree *x = new_black_rbtree(10);
  rbtree *y = new_black_rbtree(12);
  rbtree *a = new_black_rbtree(9);
  rbtree *b = new_black_rbtree(11);
  rbtree *c = new_black_rbtree(13);
  rbtree_link(p, x, 1);
  rbtree_link(x, a, 0);
  rbtree_link(x, y, 1);
  rbtree_link(y, b, 0);
  rbtree_link(y, c, 1);
  return p;
}

void clone() {
  rbtree *actual = test_tree_one();
  rbtree *expected = clone_rbtree(actual);
  cmp_tree(expected, actual);
  free_rbtree(actual);
  free_rbtree(expected);
}

void rotate() {
  rbtree *actual = test_tree_one();
  rbtree *expected = test_tree_one();
  rbtree_rotate_left(actual->right);
  rbtree_rotate_right(actual->right);
  cmp_tree(expected, actual);
  free_rbtree(actual);
  free_rbtree(expected);
}

void insert_case1() {
  rbtree *tree = NULL;
  rbtree_insert(&tree, 11);
  check_node(tree, 11, Black);
  free_rbtree(tree);
}

void insert_case2a() {
  rbtree *tree = NULL;
  rbtree_insert(&tree, 11);
  rbtree_insert(&tree, 12);
  rbtree_insert(&tree, 9);
  check_node(tree, 11, Black);
  check_node(tree->left, 9, Red);
  check_node(tree->right, 12, Red);
  free_rbtree(tree);
}

void insert_case2b() {
  rbtree *tree = NULL;
  rbtree_insert(&tree, 11);
  rbtree_insert(&tree, 12);
  rbtree_insert(&tree, 10);
  rbtree_insert(&tree, 9);
  rbtree_insert(&tree, 7);
  rbtree_insert(&tree, 8);
  rbtree_insert(&tree, 6);
  rbtree_insert(&tree, 5);
  tree = rbtree_root(tree);
  check_node(tree, 9, Black);
  check_node(tree->left, 7, Red);
  check_node(tree->left->left, 6, Black);
  check_node(tree->left->left->left, 5, Red);
  check_node(tree->left->right, 8, Black);
  check_node(tree->right, 11, Red);
  check_node(tree->right->left, 10, Black);
  check_node(tree->right->right, 12, Black);
  free_rbtree(tree);
}

void insert_case3a1() {
  rbtree *tree = NULL;
  rbtree_insert(&tree, 11);
  rbtree_insert(&tree, 12);
  rbtree_insert(&tree, 9);
  rbtree_insert(&tree, 8);
  check_node(tree, 11, Black);
  check_node(tree->left, 9, Black);
  check_node(tree->left->left, 8, Red);
  check_node(tree->right, 12, Black);
  free_rbtree(tree);
}

void insert_case3a2() {
  rbtree *tree = NULL;
  rbtree_insert(&tree, 11);
  rbtree_insert(&tree, 10);
  rbtree_insert(&tree, 12);
  rbtree_insert(&tree, 13);
  check_node(tree, 11, Black);
  check_node(tree->left, 10, Black);
  check_node(tree->right, 12, Black);
  check_node(tree->right->right, 13, Red);
  free_rbtree(tree);
}

void insert_case3b1() {
  rbtree *tree = NULL;
  rbtree_insert(&tree, 11);
  rbtree_insert(&tree, 12);
  rbtree_insert(&tree, 9);
  rbtree_insert(&tree, 10);
  rbtree_insert(&tree, 8);
  rbtree_insert(&tree, 6);
  check_node(tree, 11, Black);
  check_node(tree->left, 9, Red);
  check_node(tree->left->left, 8, Black);
  check_node(tree->left->right, 10, Black);
  check_node(tree->left->left->left, 6, Red);
  check_node(tree->right, 12, Black);
  free_rbtree(tree);
}

void insert_case3b2() {
  rbtree *tree = NULL;
  rbtree_insert(&tree, 11);
  rbtree_insert(&tree, 10);
  rbtree_insert(&tree, 13);
  rbtree_insert(&tree, 12);
  rbtree_insert(&tree, 14);
  rbtree_insert(&tree, 15);
  check_node(tree, 11, Black);
  check_node(tree->left, 10, Black);
  check_node(tree->right, 13, Red);
  check_node(tree->right->left, 12, Black);
  check_node(tree->right->right, 14, Black);
  check_node(tree->right->right->right, 15, Red);
  free_rbtree(tree);
}

void insert_case4a1() {
  rbtree *tree = NULL;
  rbtree_insert(&tree, 11);
  rbtree_insert(&tree, 12);
  rbtree_insert(&tree, 10);
  rbtree_insert(&tree, 9);
  rbtree_insert(&tree, 8);
  check_node(tree, 11, Black);
  check_node(tree->left, 9, Black);
  check_node(tree->left->left, 8, Red);
  check_node(tree->left->right, 10, Red);
  check_node(tree->right, 12, Black);
  free_rbtree(tree);
}

void insert_case4a2() {
  rbtree *tree = NULL;
  rbtree_insert(&tree, 11);
  rbtree_insert(&tree, 10);
  rbtree_insert(&tree, 14);
  rbtree_insert(&tree, 15);
  rbtree_insert(&tree, 16);
  check_node(tree, 11, Black);
  check_node(tree->left, 10, Black);
  check_node(tree->right, 15, Black);
  check_node(tree->right->left, 14, Red);
  check_node(tree->right->right, 16, Red);
  free_rbtree(tree);
}

void insert_case4b1() {
  rbtree *tree = NULL;
  rbtree_insert(&tree, 11);
  rbtree_insert(&tree, 12);
  rbtree_insert(&tree, 10);
  rbtree_insert(&tree, 8);
  rbtree_insert(&tree, 9);
  check_node(tree, 11, Black);
  check_node(tree->left, 9, Black);
  check_node(tree->left->left, 8, Red);
  check_node(tree->left->right, 10, Red);
  check_node(tree->right, 12, Black);
  free_rbtree(tree);
}

void insert_case4b2() {
  rbtree *tree = NULL;
  rbtree_insert(&tree, 11);
  rbtree_insert(&tree, 10);
  rbtree_insert(&tree, 14);
  rbtree_insert(&tree, 16);
  rbtree_insert(&tree, 15);
  check_node(tree, 11, Black);
  check_node(tree->left, 10, Black);
  check_node(tree->right, 15, Black);
  check_node(tree->right->left, 14, Red);
  check_node(tree->right->right, 16, Red);
  free_rbtree(tree);
}

void insert_casem1() {
  rbtree *tree = NULL;
  rbtree_insert(&tree, 11);
  rbtree_insert(&tree, 10);
  rbtree_insert(&tree, 9);
  tree = rbtree_root(tree);
  check_node(tree, 10, Black);
  check_node(tree->left, 9, Red);
  check_node(tree->right, 11, Red);
  free_rbtree(tree);
}

void insert_casem2() {
  rbtree *tree = NULL;
  for (int data = 0; data < 11; data++)
    rbtree_insert(&tree, data);
  check_node(tree, 3, Black);
  check_node(tree->left, 1, Black);
  check_node(tree->left->left, 0, Black);
  check_node(tree->left->right, 2, Black);
  check_node(tree->right, 5, Black);
  check_node(tree->right->left, 4, Black);
  check_node(tree->right->right, 7, Red);
  check_node(tree->right->right->left, 6, Black);
  check_node(tree->right->right->right, 9, Black);
  check_node(tree->right->right->right->left, 8, Red);
  check_node(tree->right->right->right->right, 10, Red);

  tree = rbtree_root(tree);
  free_rbtree(tree);
}

void cmp_tree(rbtree *actual, rbtree *expected) {
  if (NULL == actual) {
    assertf(NULL == expected, "%d", expected->data);
    return;
  }
  if (NULL == expected) {
    assertf(NULL == actual, "%d", actual->data);
    return;
  }
  assertf(actual->data == expected->data, "data: actual %d != expected %d",
          actual->data, expected->data);
  assertf(actual->col == expected->col, "color: actual %d != expected %d",
          actual->col, expected->col);
  cmp_tree(actual->left, expected->left);
  cmp_tree(actual->right, expected->right);
}

void print(rbtree *tree) {
  if (NULL == tree)
    return;
  int dir = -1;
  if (NULL != tree->parent)
    dir = tree == tree->parent->right;
  if (-1 == dir)
    printf("%d root\n", tree->data);
  else if (dir)
    printf("%d right\n", tree->data);
  else
    printf("%d left\n", tree->data);
  print(tree->left);
  print(tree->right);
}
