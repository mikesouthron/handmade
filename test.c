#include "hashmap/hashmap.h"
#include <stdio.h>

int main() {
  HashMap map = new_hashmap();
  hashmap_add("key", "value", &map);
  printf("%s\n", (char*)hashmap_get("key", &map));
  return 0;
}
