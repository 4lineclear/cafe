#include "../src/vec.c"
#include "../utils/testing.c"
#include <stdlib.h>

void empty();
void push();
void pop();

int main() {
  empty();
  push();
  pop();
  return EXIT_SUCCESS;
}

void empty() {
  vec v = new_vec(0);
  free_vec(&v);
}
void push() {
  vec v = new_vec(5);
  int i;
  for (i = 0; i < 10; i++)
    vec_push(&v, i);
  for (i = 0; i < 10; i++)
    assertf(v.arr[i] == i, "item at %d = %d and not the expected %d", i,
            v.arr[i], i);
  free_vec(&v);
}
void pop() {
  vec v = new_vec(0);
  int i;
  for (i = 0; i < 10; i++)
    vec_push(&v, i);
  for (i = 9; i >= 0; i--) {
    int item = vec_pop(&v);
    assertf(item == i, "item at %d = %d and not the expected %d", i, item, i);
  }
  free_vec(&v);
}
