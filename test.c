#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct TestStruct {
    char* name;
    uint8_t age;
    int* things;
} TestStruct;

TestStruct parse_test_struct_json(char* json_string) {
    TestStruct t = {0};
    size_t len = strlen(json_string);
    bool in_obj = false;
    bool in_key = false;
    bool in_value = false;
    bool in_escape = false;
    
    char *key = malloc(sizeof(char) * 100);
    size_t key_len = 0;
    size_t key_buf_size = 100;
    
    char *value = malloc(sizeof(char) * 100);
    size_t value_len = 0;
    size_t value_buf_size = 100;
    
    for (size_t i = 0; i < len; ++i) {
        char c = json_string[i];
        
        if (c == '{') {
            if (in_value) {
                //TODO: Handle inner object if needed...
            }
        } else if (c == ',' || c == '}') {
            value[value_len++] = '\0';
            
            printf("Key: %s, Value %s\n", key, value);
            
            if (strcmp(key, "name") == 0) {
                t.name = value;
            } else if (strcmp(key, "age") == 0) {
                t.age = atoi(value);
            }
            
            key = malloc(sizeof(char) * 100);
            key_len = 0;
            key_buf_size = 100;
            
            value = malloc(sizeof(char) * 100);
            value_len = 0;
            value_buf_size = 100;
            in_value = false;
            in_key = true;
            
            if (c == '}') {
                in_obj = false;
            }
        } else if (c == ':') {
            in_key = false;
            key[key_len++] = '\0';
            in_value = true;
        } else if (c == '\\') {
            in_escape = true;
        } else if (c == '"') {
            if (in_escape) {
                in_escape = false;
                if (in_key) {
                    key[key_len++] = c;
                } else if (in_value) {
                    value[key_len++] = c;
                }
            }
        } else if (c == ' ') {
            if (in_key && key_len > 0) {
                key[key_len++] = c;
            }
            if (in_value && value_len > 0) {
                value[value_len++] = c;
            }
        } else {
            if (in_key) {
                printf("Adding %c to key\n", c);
                key[key_len++] = c;
            } else if (in_value) {
                printf("Adding %c to value\n", c);
                value[value_len++] = c;
            }
        }
        
        if (key_len >= key_buf_size)
        {
            key_buf_size = key_buf_size + 100;
            key = realloc(key, sizeof(char) * key_buf_size);
        }
        if (value_len >= value_buf_size) {
            value_buf_size = value_buf_size * 100;
            value = realloc(value, sizeof(char) * value_buf_size);
        }
    }
    return t;
}

int main() {
    char* json_string = "{\"name\": \"Mike\", \"age\": 35, \"things\":[1,2,3,4,5]}";
    TestStruct test = parse_test_struct_json(json_string);
    printf("Name: %s, Age: %d", test.name, test.age);
    return 0;
}

