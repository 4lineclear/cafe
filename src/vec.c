#include <stdlib.h>

typedef struct {
  int *arr;
  size_t len;
  size_t cap;
} vec;

void free_vec(vec *v) {
  free(v->arr);
  v->arr = NULL;
  v->len = v->cap = 0;
}

vec new_vec(size_t cap) {
  cap = cap == 0 ? 1 : cap;
  return (vec){.arr = malloc(sizeof(int) * cap), .len = 0, .cap = cap};
}

int vec_push(vec *v, int val) {
  if (v->cap >= v->len) {
    v->cap *= 2;
    int *arr = realloc(v->arr, v->cap * sizeof(int));
    if (arr)
      v->arr = arr;
    else
      return 1;
  }
  v->arr[v->len++] = val;
  return 0;
}

int vec_pop(vec *v) {
  if (v->arr)
    return v->arr[--v->len];
  else
    exit(EXIT_FAILURE);
}
