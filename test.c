#include "csv/csv.h"
#include "hashmap/hashmap.h"
#include <stdio.h>

int main()
{
    CSVReader csv = csv_newreader("test.csv");
    
    printf("Cols: %d\n", csv.cols);
    
    char **row = csv_next(&csv);
    int count = 0;
    while (row != NULL)
    {
        ++count;
        row = csv_next(&csv);
    }
    
    printf("Rows: %d\n", count);
    
    return 0;
}
