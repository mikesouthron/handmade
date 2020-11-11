#pragma once

#include <stdio.h>
#include "../hashmap/hashmap.h"

typedef struct CSVReader {
  HashMap headers;
  FILE *fp;
} CSVReader;

CSVReader csv_newreader(char* filename) {
  FILE *fp = fopen(filename, "r");
  CSVReader reader;
  reader.fp = fp;
  return reader;
}
