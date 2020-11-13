#pragma once

#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define FNV_PRIME_32 16777619
#define FNV_OFFSET_32 2166136261U

typedef struct MapEntry
{
    char *key;
    void *value;
    int int_value;
    struct MapEntry *next;
} MapEntry;

typedef struct MapEntryList
{
    MapEntry *first;
    MapEntry *last;
} MapEntryList;

typedef struct HashMap
{
    MapEntryList data[UINT8_MAX];
} HashMap;

HashMap hashmap_new()
{
    HashMap map;
    for (size_t i = 0; i < UINT8_MAX; ++i)
    {
        MapEntryList entry_list;
        entry_list.first = NULL;
        entry_list.last = NULL;
        map.data[i] = entry_list;
    }
    return map;
}

uint8_t hash_str(char *str)
{
    uint32_t hash = FNV_OFFSET_32;
    for (size_t i = 0; i < strlen(str); ++i)
    {
        hash = hash ^ (str[i]);
        hash = hash * FNV_PRIME_32;
    }
    return hash & 0xFF;
}

void hashmap_add_int(char *key, int value, HashMap *map)
{
    uint8_t hash_key = hash_str(key);
    MapEntry *entry = malloc(sizeof(MapEntry));
    entry->key = key;
    entry->int_value = value;
    entry->next = NULL;
    MapEntryList entry_list = map->data[hash_key];
    if (entry_list.first == NULL)
    {
        entry_list.first = entry;
        entry_list.last = entry;
    }
    else
    {
        entry_list.last->next = entry;
        entry_list.last = entry;
    }
    map->data[hash_key] = entry_list;
}

void hashmap_add(char *key, void *value, HashMap *map)
{
    uint8_t hash_key = hash_str(key);
    MapEntry *entry = malloc(sizeof(MapEntry));
    entry->key = key;
    entry->value = value;
    entry->next = NULL;
    MapEntryList entry_list = map->data[hash_key];
    if (entry_list.first == NULL)
    {
        entry_list.first = entry;
        entry_list.last = entry;
    }
    else
    {
        entry_list.last->next = entry;
        entry_list.last = entry;
    }
    map->data[hash_key] = entry_list;
}

void *hashmap_get(char *key, HashMap *map)
{
    uint8_t hash_key = hash_str(key);
    MapEntryList entry_list = map->data[hash_key];
    MapEntry *entry = entry_list.first;
    if (entry == NULL)
    {
        return NULL;
    }
    while (1)
    {
        MapEntry deref_entry = *entry;
        char *entry_key = deref_entry.key;
        if (strcmp(entry_key, key) == 0)
        {
            return entry->value;
        }
        entry = entry->next;
        if (entry == NULL)
        {
            break;
        }
    }
    return NULL;
}

int hashmap_get_int(char *key, HashMap *map)
{
    uint8_t hash_key = hash_str(key);
    MapEntryList entry_list = map->data[hash_key];
    MapEntry *entry = entry_list.first;
    if (entry == NULL)
    {
        return 0;
    }
    while (1)
    {
        MapEntry deref_entry = *entry;
        char *entry_key = deref_entry.key;
        if (strcmp(entry_key, key) == 0)
        {
            return entry->int_value;
        }
        entry = entry->next;
        if (entry == NULL)
        {
            break;
        }
    }
    return 0;
}

void hashmap_remove(char *key, HashMap *map)
{
    uint8_t hash_key = hash_str(key);
    MapEntryList entry_list = map->data[hash_key];
    MapEntry *entry = entry_list.first;
    if (entry == NULL)
    {
        return;
    }
    MapEntry *previous = NULL;
    while (1)
    {
        MapEntry deref_entry = *entry;
        char *entry_key = deref_entry.key;
        if (strcmp(entry_key, key) == 0)
        {
            if (previous != NULL)
            {
                previous->next = entry->next;
            }
            else
            {
                entry_list.first = entry->next;
            }
            break;
        }
        previous = entry;
        entry = entry->next;
        if (entry == NULL)
        {
            break;
        }
    }
    map->data[hash_key] = entry_list;
}
