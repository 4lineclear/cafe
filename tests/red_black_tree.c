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
void insert_casem3();
void from_arr();
void delete_null();
void delete_root();
void delete_red_leaf();
void delete_single_child();
void delete_single_child_root();
void delete_red_red();
void delete_black_red();
void delete_red_black_red();
void print(rbnode *);

#define col(C) C == Red ? "red" : "black"
#define check_node(N, D, C)                                                    \
  assertf(N != NULL, "given node is null");                                    \
  assertf(N->data == D, "data: actual %d != expected %d", N->data, D);         \
  assertf(N->col == C, "col: actual %s != expected %s", col(N->col), col(C))

#define node_null(N)                                                           \
  assertf(N == NULL, "given node is not null, data: %d, color: %s", N->data,   \
          col(N->col));

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
  insert_casem2();
  insert_casem3();
  from_arr();
  delete_null();
  delete_root();
  delete_red_leaf();
  delete_single_child();
  delete_single_child_root();
  delete_red_red();
  delete_black_red();
  delete_red_black_red();
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
  rbnode *root = test_node_one();
  rbnode *expected = root->right->right->right;
  rbnode *actual = search_rbnode(root, 13);
  assertf(actual == expected, "actual %p != expected %p", actual, expected);
  free_rbnode(root);
}

void search_null() {
  rbnode *root = NULL;
  rbnode *expected = NULL;
  rbnode *actual = search_rbnode(root, 13);
  assertf(actual == expected, "actual %p != expected %p", actual, expected);
}

void search_fail() {
  rbnode *root = test_node_one();
  rbnode *expected = NULL;
  rbnode *actual = search_rbnode(root, 14);
  assertf(actual == expected, "actual %p != expected %p", actual, expected);
  free_rbnode(root);
}

void insert_case1() {
  rbnode *root = NULL;
  rbnode_insert(&root, 11);
  check_node(root, 11, Black);
  free_rbnode(root);
}

void insert_case2a() {
  rbnode *root = NULL;
  rbnode_insert(&root, 11);
  rbnode_insert(&root, 12);
  rbnode_insert(&root, 9);
  check_node(root, 11, Black);
  check_node(root->left, 9, Red);
  check_node(root->right, 12, Red);
  free_rbnode(root);
}

void insert_case2b() {
  rbnode *root = NULL;
  rbnode_insert(&root, 11);
  rbnode_insert(&root, 12);
  rbnode_insert(&root, 10);
  rbnode_insert(&root, 9);
  rbnode_insert(&root, 7);
  rbnode_insert(&root, 8);
  rbnode_insert(&root, 6);
  rbnode_insert(&root, 5);
  check_node(root, 9, Black);
  check_node(root->left, 7, Red);
  check_node(root->left->left, 6, Black);
  check_node(root->left->left->left, 5, Red);
  check_node(root->left->right, 8, Black);
  check_node(root->right, 11, Red);
  check_node(root->right->left, 10, Black);
  check_node(root->right->right, 12, Black);
  free_rbnode(root);
}

void insert_case3a1() {
  rbnode *root = NULL;
  rbnode_insert(&root, 11);
  rbnode_insert(&root, 12);
  rbnode_insert(&root, 9);
  rbnode_insert(&root, 8);
  check_node(root, 11, Black);
  check_node(root->left, 9, Black);
  check_node(root->left->left, 8, Red);
  check_node(root->right, 12, Black);
  free_rbnode(root);
}

void insert_case3a2() {
  rbnode *root = NULL;
  rbnode_insert(&root, 11);
  rbnode_insert(&root, 10);
  rbnode_insert(&root, 12);
  rbnode_insert(&root, 13);
  check_node(root, 11, Black);
  check_node(root->left, 10, Black);
  check_node(root->right, 12, Black);
  check_node(root->right->right, 13, Red);
  free_rbnode(root);
}

void insert_case3b1() {
  rbnode *root = NULL;
  rbnode_insert(&root, 11);
  rbnode_insert(&root, 12);
  rbnode_insert(&root, 9);
  rbnode_insert(&root, 10);
  rbnode_insert(&root, 8);
  rbnode_insert(&root, 6);
  check_node(root, 11, Black);
  check_node(root->left, 9, Red);
  check_node(root->left->left, 8, Black);
  check_node(root->left->right, 10, Black);
  check_node(root->left->left->left, 6, Red);
  check_node(root->right, 12, Black);
  free_rbnode(root);
}

void insert_case3b2() {
  rbnode *root = NULL;
  rbnode_insert(&root, 11);
  rbnode_insert(&root, 10);
  rbnode_insert(&root, 13);
  rbnode_insert(&root, 12);
  rbnode_insert(&root, 14);
  rbnode_insert(&root, 15);
  check_node(root, 11, Black);
  check_node(root->left, 10, Black);
  check_node(root->right, 13, Red);
  check_node(root->right->left, 12, Black);
  check_node(root->right->right, 14, Black);
  check_node(root->right->right->right, 15, Red);
  free_rbnode(root);
}

void insert_case4a1() {
  rbnode *root = NULL;
  rbnode_insert(&root, 11);
  rbnode_insert(&root, 12);
  rbnode_insert(&root, 10);
  rbnode_insert(&root, 9);
  rbnode_insert(&root, 8);
  check_node(root, 11, Black);
  check_node(root->left, 9, Black);
  check_node(root->left->left, 8, Red);
  check_node(root->left->right, 10, Red);
  check_node(root->right, 12, Black);
  free_rbnode(root);
}

void insert_case4a2() {
  rbnode *root = NULL;
  rbnode_insert(&root, 11);
  rbnode_insert(&root, 10);
  rbnode_insert(&root, 14);
  rbnode_insert(&root, 15);
  rbnode_insert(&root, 16);
  check_node(root, 11, Black);
  check_node(root->left, 10, Black);
  check_node(root->right, 15, Black);
  check_node(root->right->left, 14, Red);
  check_node(root->right->right, 16, Red);
  free_rbnode(root);
}

void insert_case4b1() {
  rbnode *root = NULL;
  rbnode_insert(&root, 11);
  rbnode_insert(&root, 12);
  rbnode_insert(&root, 10);
  rbnode_insert(&root, 8);
  rbnode_insert(&root, 9);
  check_node(root, 11, Black);
  check_node(root->left, 9, Black);
  check_node(root->left->left, 8, Red);
  check_node(root->left->right, 10, Red);
  check_node(root->right, 12, Black);
  free_rbnode(root);
}

void insert_case4b2() {
  rbnode *root = NULL;
  rbnode_insert(&root, 11);
  rbnode_insert(&root, 10);
  rbnode_insert(&root, 14);
  rbnode_insert(&root, 16);
  rbnode_insert(&root, 15);
  check_node(root, 11, Black);
  check_node(root->left, 10, Black);
  check_node(root->right, 15, Black);
  check_node(root->right->left, 14, Red);
  check_node(root->right->right, 16, Red);
  free_rbnode(root);
}

void insert_casem1() {
  rbnode *root = NULL;
  rbnode_insert(&root, 11);
  rbnode_insert(&root, 10);
  rbnode_insert(&root, 9);
  check_node(root, 10, Black);
  check_node(root->left, 9, Red);
  check_node(root->right, 11, Red);
  free_rbnode(root);
}

void insert_casem2() {
  rbnode *root = NULL;
  rbnode_insert(&root, 9);
  rbnode_insert(&root, 10);
  rbnode_insert(&root, 11);
  check_node(root, 10, Black);
  check_node(root->left, 9, Red);
  check_node(root->right, 11, Red);
  free_rbnode(root);
}

void insert_casem3() {
  rbnode *root = NULL;
  for (int data = 0; data < 11; data++)
    rbnode_insert(&root, data);
  check_node(root, 3, Black);
  check_node(root->left, 1, Black);
  check_node(root->left->left, 0, Black);
  check_node(root->left->right, 2, Black);
  check_node(root->right, 5, Black);
  check_node(root->right->left, 4, Black);
  check_node(root->right->right, 7, Red);
  check_node(root->right->right->left, 6, Black);
  check_node(root->right->right->right, 9, Black);
  check_node(root->right->right->right->left, 8, Red);
  check_node(root->right->right->right->right, 10, Red);
  free_rbnode(root);
}

void from_arr() {
  int data[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  rbnode *root = rbnode_from_arr(data, 11);
  check_node(root, 3, Black);
  check_node(root->left, 1, Black);
  check_node(root->left->left, 0, Black);
  check_node(root->left->right, 2, Black);
  check_node(root->right, 5, Black);
  check_node(root->right->left, 4, Black);
  check_node(root->right->right, 7, Red);
  check_node(root->right->right->left, 6, Black);
  check_node(root->right->right->right, 9, Black);
  check_node(root->right->right->right->left, 8, Red);
  check_node(root->right->right->right->right, 10, Red);
  free_rbnode(root);
}

void delete_null() {
  rbnode *root = NULL;
  rbnode_delete(&root, root);
  node_null(root);
}

void delete_root() {
  rbnode *root = NULL;
  rbnode_insert(&root, 0);
  rbnode_delete(&root, root);
  node_null(root);
}

void delete_red_leaf() {
  int data[] = {0, 1};
  rbnode *root = rbnode_from_arr(data, 2);
  rbnode_delete(&root, root->right);
  node_null(root->right);
  free_rbnode(root);
}

void delete_single_child() {
  int data[] = {0, 1, 2, 3};
  rbnode *root = rbnode_from_arr(data, 4);
  check_node(root, 1, Black);
  check_node(root->left, 0, Black);
  check_node(root->right, 2, Black);
  check_node(root->right->right, 3, Red);
  rbnode_delete(&root, root->right);
  check_node(root, 1, Black);
  check_node(root->left, 0, Black);
  check_node(root->right, 3, Black);
  node_null(root->right->right);
  free_rbnode(root);
}

void delete_single_child_root() {
  int data[] = {0, 1};
  rbnode *root = rbnode_from_arr(data, 2);
  check_node(root, 0, Black);
  check_node(root->right, 1, Red);
  rbnode_delete(&root, root);
  check_node(root, 1, Black);
  rbnode_insert(&root, 2);
  check_node(root->right, 2, Red);
  rbnode_delete(&root, root);
  check_node(root, 2, Black);
  free_rbnode(root);
}

// red replaced with red
void delete_red_red() {
  int data[] = {11, 10, 13, 12, 15, 14};
  rbnode *root = rbnode_from_arr(data, 6);
  check_node(root, 11, Black);
  check_node(root->left, 10, Black);
  check_node(root->right, 13, Red);
  check_node(root->right->left, 12, Black);
  check_node(root->right->right, 15, Black);
  check_node(root->right->right->left, 14, Red);
  rbnode_delete(&root, root->right);
  check_node(root, 11, Black);
  check_node(root->left, 10, Black);
  check_node(root->right, 14, Red);
  check_node(root->right->left, 12, Black);
  check_node(root->right->right, 15, Black);
  node_null(root->right->right->left);
  free_rbnode(root);
}

// black replaced with red
void delete_black_red() {
  int data[] = {11, 10, 13, 12};
  rbnode *root = rbnode_from_arr(data, 4);
  check_node(root, 11, Black);
  check_node(root->left, 10, Black);
  check_node(root->right, 13, Black);
  check_node(root->right->left, 12, Red);
  rbnode_delete(&root, root);
  check_node(root, 12, Black);
  check_node(root->left, 10, Black);
  check_node(root->right, 13, Black);
  node_null(root->right->left);
  free_rbnode(root);
}

// red replaced with black
//
// black is replaced by red
void delete_red_black_red() {
  int data[] = {7, 3, 18, 10, 22, 8, 11, 26};
  rbnode *root = rbnode_from_arr(data, 8);
  check_node(root, 7, Black);
  check_node(root->left, 3, Black);
  check_node(root->right, 18, Red);
  check_node(root->right->left, 10, Black);
  check_node(root->right->left->left, 8, Red);
  check_node(root->right->left->right, 11, Red);
  check_node(root->right->right, 22, Black);
  check_node(root->right->right->right, 26, Red);
  rbnode_delete(&root, root->right);
  check_node(root, 7, Black);
  check_node(root->left, 3, Black);
  check_node(root->right, 22, Red);
  check_node(root->right->left, 10, Black);
  check_node(root->right->left->left, 8, Red);
  check_node(root->right->left->right, 11, Red);
  check_node(root->right->right, 26, Black);
  free_rbnode(root);
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
