#include <stdio.h>
void swap(int *a, int *b);

void selection_sort(int *items, size_t len) {
  for (size_t i = 0; i < len; i++) {
    for (size_t j = i + 1; j < len; j++) {
      if (items[j] < items[i]) {
        swap(&items[i], &items[j]);
      }
    }
  }
}

void bubble_sort(int *items, size_t len) {
  if (len < 2) {
    return;
  }
  for (size_t i = 0; i < len; i++) {
    for (size_t j = 0; j < (len - i - 1); j++) {
      if (items[j] > items[j + 1]) {
        swap(&items[j], &items[j + 1]);
      }
    }
  }
}

void insertion_sort(int *items, size_t len) {
  for (size_t i = 1; i < len; i++) {
    int temp = items[i];
    int j;
    for (j = i - 1; j >= 0 && items[j] > temp; j--) {
      items[j + 1] = items[j];
    }
    items[j + 1] = temp;
  }
}

void merge(int arr[], size_t l, size_t m, size_t r) {
  int i, j, k;
  int il = m - l + 1;
  int jl = r - m;
  int L[il], R[jl];

  for (i = 0; i < il; i++)
    L[i] = arr[l + i];
  for (j = 0; j < jl; j++)
    R[j] = arr[m + 1 + j];
  i = 0;
  j = 0;
  k = l;

  while (i < il && j < jl)
    if (L[i] <= R[j])
      arr[k++] = L[i++];
    else
      arr[k++] = R[j++];

  while (i < il)
    arr[k++] = L[i++];
  while (j < jl)
    arr[k++] = R[j++];
}

void merge_sort_inner(int *items, size_t l, size_t r) {
  if (l < r) {
    int m = l + (r - l) / 2;

    merge_sort_inner(items, l, m);
    merge_sort_inner(items, m + 1, r);

    merge(items, l, m, r);
  }
}

void merge_sort(int *items, size_t len) {
  if (len > 1)
    merge_sort_inner(items, 0, len - 1);
}

void swap(int *a, int *b) {
  int temp = *a;
  *a = *b;
  *b = temp;
}
