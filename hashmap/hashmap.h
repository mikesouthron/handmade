#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define FNV_PRIME_32 16777619
#define FNV_OFFSET_32 2166136261U

typedef struct MapEntry {
    char* key;
    void* value;
    struct MapEntry *next;
} MapEntry;

typedef struct MapEntryList {
    MapEntry *first;
    MapEntry *last;
} MapEntryList;

typedef struct HashMap {
    MapEntryList data[UINT8_MAX];
} HashMap;

HashMap new_hashmap() {
    HashMap map;
    for (size_t i = 0; i < UINT8_MAX; ++i) {
        MapEntryList entry_list;
        entry_list.first = NULL;
        entry_list.last = NULL;
        map.data[i] = entry_list;
    }
    return map;
}

uint8_t hash_str(char* str) {
    uint32_t hash = FNV_OFFSET_32;
    for (size_t i = 0; i < strlen(str); ++i) {
        hash = hash ^ (str[i]);
        hash = hash * FNV_PRIME_32;
    }
    return hash & 0xFF;
}

void hashmap_add(char *key, void *value, HashMap *map) {
    uint8_t hash_key = hash_str(key);
    MapEntry *entry = malloc(sizeof(MapEntry));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    MapEntryList entry_list = map->data[hash_key];
    if (entry_list.first == NULL) {
        entry_list.first = entry;
        entry_list.last = entry;
    } else {
        entry_list.last->next = entry;
        entry_list.last = entry;
    }
    map->data[hash_key] = entry_list;
}

void* hashmap_get(char *key, HashMap *map) {
    uint8_t hash_key = hash_str(key);
    MapEntryList entry_list = map->data[hash_key];
    MapEntry *entry = entry_list.first;
    if (entry == NULL) {
        return NULL;
    }
    while (1) {
        MapEntry deref_entry = *entry;
        char* entry_key = deref_entry.key;
        if (strcmp(entry_key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
        if (entry == NULL) {
            break;
        }
    }
    return NULL;
}

