#include "hashmap/hashmap.h"
#include "csv/csv.h"
#include <stdio.h>

int main() {
  HashMap map = hashmap_new();
  hashmap_add("key", "value", &map);
  printf("%s\n", (char*)hashmap_get("key", &map));
  return 0;
}
