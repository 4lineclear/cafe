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
void print(rbtree *tree);

int main() {
  clone();
  rotate();
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
  rbtree *p = black_rbtree(4);
  rbtree *x = black_rbtree(10);
  rbtree *y = black_rbtree(12);
  rbtree *a = black_rbtree(9);
  rbtree *b = black_rbtree(11);
  rbtree *c = black_rbtree(13);
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
