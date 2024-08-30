#include "../src/sorting/selection.c"
#include "../utils/sorting.c"

int main() {
  const int len = 6;
  int expected[] = {0, 1, 2, 3, 4, 5};
  int to_test[] = {5, 3, 1, 2, 0, 4};
  selection_sort(to_test, len);
  return compare_arrs(expected, to_test, len);
}
