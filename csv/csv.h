#pragma once

#include <stdio.h>
#include <stdbool.h>
#include "../hashmap/hashmap.h"

#define STR_CHUNK 100

typedef struct CSVReader
{
  HashMap *headers;
  FILE *fp;
  int cols;
} CSVReader;

CSVReader csv_newreader(char *filename)
{
  FILE *fp = fopen(filename, "r");
  CSVReader reader;
  reader.fp = fp;

  HashMap header = hashmap_new();

  char c = fgetc(fp);
  char *value = malloc(sizeof(char) * STR_CHUNK);
  size_t buf_size = STR_CHUNK;
  size_t str_len = 0;
  int index = 0;
  bool in_quotes = false;
  while (1)
  {
    if ((c == ',' || c == '\n' || c == EOF) && !in_quotes)
    {
      value[str_len] = '\0';
      hashmap_add_int(value, index, &header);
      if (c == '\n' || c == EOF)
      {
        reader.cols = index + 1;
        break;
      }
      value = malloc(sizeof(char) * STR_CHUNK);
      str_len = 0;
      ++index;
    }
    else
    {
      if (c == '"')
      {
        in_quotes = !in_quotes;
        continue;
      }
      value[str_len] = c;
      ++str_len;
      if (str_len >= buf_size)
      {
        buf_size = buf_size + STR_CHUNK;
        value = realloc(value, sizeof(char) * buf_size);
      }
    }
    c = fgetc(fp);
  }

  reader.headers = &header;

  return reader;
}

char **csv_next(CSVReader *reader)
{
  char **rows = malloc(sizeof(char *) * reader->cols);

  char c = fgetc(reader->fp);

  if (c == EOF)
  {
    return NULL;
  }

  char *value = malloc(sizeof(char) * STR_CHUNK);
  size_t buf_size = STR_CHUNK;
  size_t str_len = 0;
  int index = 0;
  bool in_quotes = false;

  while (1)
  {
    if ((c == ',' || c == '\n' || c == EOF) && !in_quotes)
    {
      value[str_len] = '\0';
      rows[index] = value;
      if (c == '\n' || c == EOF)
      {
        break;
      }
      value = malloc(sizeof(char) * STR_CHUNK);
      str_len = 0;
      ++index;
    }
    else
    {
      if (c == '"')
      {
        in_quotes = !in_quotes;
        continue;
      }
      value[str_len] = c;
      ++str_len;
      if (str_len >= buf_size)
      {
        buf_size = buf_size + STR_CHUNK;
        value = realloc(value, sizeof(char) * buf_size);
      }
    }
    c = fgetc(reader->fp);
  }

  return rows;
}

char *csv_row_value(char *col, char **row, CSVReader *csv)
{
  int col_idx = hashmap_get_int(col, csv->headers);
  return row[col_idx];
}
