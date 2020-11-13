#include "hashmap/hashmap.h"
#include "csv/csv.h"
#include <stdio.h>

int main()
{
  CSVReader csv = csv_newreader("test.csv");
  char **row = csv_next(&csv);
  char *value = csv_row_value("col1", row, &csv);
  printf("%s\n", value);
  row = csv_next(&csv);
  if (row == NULL)
  {
    printf("End Of File\n");
  }
  return 0;
}
