void selection_sort(int *items, unsigned int len) {
  int temp;
  for (unsigned int i = 0; i < len; i++) {
    for (unsigned int j = i + 1; j < len; j++) {
      if (items[j] < items[i]) {
        temp = items[i];
        items[i] = items[j];
        items[j] = temp;
      }
    };
  }
}
