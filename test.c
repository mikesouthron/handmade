#include "csv/csv.h"
#include <stdio.h>

int main()
{
  CSVReader csv = csv_newreader("test.csv");
  char **row = csv_next(&csv);
  while (row != NULL)
  {
    for (size_t i = 0; i < csv.cols; ++i)
    {
      if (i != 0)
      {
        printf(",");
      }
      printf("%s", row[i]);
    }
    row = csv_next(&csv);
  }
  return 0;
}
