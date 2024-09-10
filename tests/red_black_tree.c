#include "../src/red_black_tree.c"
#include "../utils/testing.c"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void cmp_node(rbnode *, rbnode *);
void clone();
void rotate();
void search();
void search_null();
void search_fail();
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
void print(rbnode *);

#define check_node(N, D, C)                                                    \
  assertf(N != NULL, "given node is null");                                    \
  assertf(N->data == D, "data: actual %d != expected %d", N->data, D);         \
  assertf(N->col == C, "col: actual %d != expected %d", N->col, C)

int main() {
  clone();
  rotate();
  search();
  search_fail();
  search_null();
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

void print_node(rbnode *node, int depth) {
  if (!node)
    return;
  printf("%d: %d ", depth, node->data);
  print_node(node->left, depth + 1);
  print_node(node->right, depth + 1);
}

rbnode *test_node_one() {
  rbnode *p = new_black_rbnode(4);
  rbnode *x = new_black_rbnode(10);
  rbnode *y = new_black_rbnode(12);
  rbnode *a = new_black_rbnode(9);
  rbnode *b = new_black_rbnode(11);
  rbnode *c = new_black_rbnode(13);
  rbnode_link(p, x, 1);
  rbnode_link(x, a, 0);
  rbnode_link(x, y, 1);
  rbnode_link(y, b, 0);
  rbnode_link(y, c, 1);
  return p;
}

void clone() {
  rbnode *actual = test_node_one();
  rbnode *expected = clone_rbnode(actual);
  cmp_node(expected, actual);
  free_rbnode(actual);
  free_rbnode(expected);
}

void rotate() {
  rbnode *actual = test_node_one();
  rbnode *expected = test_node_one();
  rbnode_rotate_left(actual->right);
  rbnode_rotate_right(actual->right);
  cmp_node(expected, actual);
  free_rbnode(actual);
  free_rbnode(expected);
}

void search() {
  rbnode *node = test_node_one();
  rbnode *expected = node->right->right->right;
  rbnode *actual = search_rbnode(node, 13);
  assertf(actual == expected, "actual %p != expected %p", actual, expected);
  free_rbnode(node);
}

void search_null() {
  rbnode *node = NULL;
  rbnode *expected = NULL;
  rbnode *actual = search_rbnode(node, 13);
  assertf(actual == expected, "actual %p != expected %p", actual, expected);
}

void search_fail() {
  rbnode *node = test_node_one();
  rbnode *expected = NULL;
  rbnode *actual = search_rbnode(node, 14);
  assertf(actual == expected, "actual %p != expected %p", actual, expected);
  free_rbnode(node);
}

void insert_case1() {
  rbnode *node = NULL;
  rbnode_insert(&node, 11);
  check_node(node, 11, Black);
  free_rbnode(node);
}

void insert_case2a() {
  rbnode *node = NULL;
  rbnode_insert(&node, 11);
  rbnode_insert(&node, 12);
  rbnode_insert(&node, 9);
  check_node(node, 11, Black);
  check_node(node->left, 9, Red);
  check_node(node->right, 12, Red);
  free_rbnode(node);
}

void insert_case2b() {
  rbnode *node = NULL;
  rbnode_insert(&node, 11);
  rbnode_insert(&node, 12);
  rbnode_insert(&node, 10);
  rbnode_insert(&node, 9);
  rbnode_insert(&node, 7);
  rbnode_insert(&node, 8);
  rbnode_insert(&node, 6);
  rbnode_insert(&node, 5);
  node = rbnode_root(node);
  check_node(node, 9, Black);
  check_node(node->left, 7, Red);
  check_node(node->left->left, 6, Black);
  check_node(node->left->left->left, 5, Red);
  check_node(node->left->right, 8, Black);
  check_node(node->right, 11, Red);
  check_node(node->right->left, 10, Black);
  check_node(node->right->right, 12, Black);
  free_rbnode(node);
}

void insert_case3a1() {
  rbnode *node = NULL;
  rbnode_insert(&node, 11);
  rbnode_insert(&node, 12);
  rbnode_insert(&node, 9);
  rbnode_insert(&node, 8);
  check_node(node, 11, Black);
  check_node(node->left, 9, Black);
  check_node(node->left->left, 8, Red);
  check_node(node->right, 12, Black);
  free_rbnode(node);
}

void insert_case3a2() {
  rbnode *node = NULL;
  rbnode_insert(&node, 11);
  rbnode_insert(&node, 10);
  rbnode_insert(&node, 12);
  rbnode_insert(&node, 13);
  check_node(node, 11, Black);
  check_node(node->left, 10, Black);
  check_node(node->right, 12, Black);
  check_node(node->right->right, 13, Red);
  free_rbnode(node);
}

void insert_case3b1() {
  rbnode *node = NULL;
  rbnode_insert(&node, 11);
  rbnode_insert(&node, 12);
  rbnode_insert(&node, 9);
  rbnode_insert(&node, 10);
  rbnode_insert(&node, 8);
  rbnode_insert(&node, 6);
  check_node(node, 11, Black);
  check_node(node->left, 9, Red);
  check_node(node->left->left, 8, Black);
  check_node(node->left->right, 10, Black);
  check_node(node->left->left->left, 6, Red);
  check_node(node->right, 12, Black);
  free_rbnode(node);
}

void insert_case3b2() {
  rbnode *node = NULL;
  rbnode_insert(&node, 11);
  rbnode_insert(&node, 10);
  rbnode_insert(&node, 13);
  rbnode_insert(&node, 12);
  rbnode_insert(&node, 14);
  rbnode_insert(&node, 15);
  check_node(node, 11, Black);
  check_node(node->left, 10, Black);
  check_node(node->right, 13, Red);
  check_node(node->right->left, 12, Black);
  check_node(node->right->right, 14, Black);
  check_node(node->right->right->right, 15, Red);
  free_rbnode(node);
}

void insert_case4a1() {
  rbnode *node = NULL;
  rbnode_insert(&node, 11);
  rbnode_insert(&node, 12);
  rbnode_insert(&node, 10);
  rbnode_insert(&node, 9);
  rbnode_insert(&node, 8);
  check_node(node, 11, Black);
  check_node(node->left, 9, Black);
  check_node(node->left->left, 8, Red);
  check_node(node->left->right, 10, Red);
  check_node(node->right, 12, Black);
  free_rbnode(node);
}

void insert_case4a2() {
  rbnode *node = NULL;
  rbnode_insert(&node, 11);
  rbnode_insert(&node, 10);
  rbnode_insert(&node, 14);
  rbnode_insert(&node, 15);
  rbnode_insert(&node, 16);
  check_node(node, 11, Black);
  check_node(node->left, 10, Black);
  check_node(node->right, 15, Black);
  check_node(node->right->left, 14, Red);
  check_node(node->right->right, 16, Red);
  free_rbnode(node);
}

void insert_case4b1() {
  rbnode *node = NULL;
  rbnode_insert(&node, 11);
  rbnode_insert(&node, 12);
  rbnode_insert(&node, 10);
  rbnode_insert(&node, 8);
  rbnode_insert(&node, 9);
  check_node(node, 11, Black);
  check_node(node->left, 9, Black);
  check_node(node->left->left, 8, Red);
  check_node(node->left->right, 10, Red);
  check_node(node->right, 12, Black);
  free_rbnode(node);
}

void insert_case4b2() {
  rbnode *node = NULL;
  rbnode_insert(&node, 11);
  rbnode_insert(&node, 10);
  rbnode_insert(&node, 14);
  rbnode_insert(&node, 16);
  rbnode_insert(&node, 15);
  check_node(node, 11, Black);
  check_node(node->left, 10, Black);
  check_node(node->right, 15, Black);
  check_node(node->right->left, 14, Red);
  check_node(node->right->right, 16, Red);
  free_rbnode(node);
}

void insert_casem1() {
  rbnode *node = NULL;
  rbnode_insert(&node, 11);
  rbnode_insert(&node, 10);
  rbnode_insert(&node, 9);
  node = rbnode_root(node);
  check_node(node, 10, Black);
  check_node(node->left, 9, Red);
  check_node(node->right, 11, Red);
  free_rbnode(node);
}

void insert_casem2() {
  rbnode *node = NULL;
  for (int data = 0; data < 11; data++)
    rbnode_insert(&node, data);
  check_node(node, 3, Black);
  check_node(node->left, 1, Black);
  check_node(node->left->left, 0, Black);
  check_node(node->left->right, 2, Black);
  check_node(node->right, 5, Black);
  check_node(node->right->left, 4, Black);
  check_node(node->right->right, 7, Red);
  check_node(node->right->right->left, 6, Black);
  check_node(node->right->right->right, 9, Black);
  check_node(node->right->right->right->left, 8, Red);
  check_node(node->right->right->right->right, 10, Red);

  node = rbnode_root(node);
  free_rbnode(node);
}

void cmp_node(rbnode *actual, rbnode *expected) {
  if (!actual) {
    assertf(!expected, "%d", expected->data);
    return;
  }
  if (!expected) {
    assertf(!actual, "%d", actual->data);
    return;
  }
  assertf(actual->data == expected->data, "data: actual %d != expected %d",
          actual->data, expected->data);
  assertf(actual->col == expected->col, "color: actual %d != expected %d",
          actual->col, expected->col);
  cmp_node(actual->left, expected->left);
  cmp_node(actual->right, expected->right);
}

void print(rbnode *node) {
  if (!node)
    return;
  int dir = -1;
  if (node->parent)
    dir = node == node->parent->right;
  if (-1 == dir)
    printf("%d root\n", node->data);
  else if (dir)
    printf("%d right\n", node->data);
  else
    printf("%d left\n", node->data);
  print(node->left);
  print(node->right);
}
