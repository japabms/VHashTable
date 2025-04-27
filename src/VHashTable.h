#ifndef _V_HASH_TABLE_
#define _V_HASH_TABLE_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct vhash_table vhash_table;

typedef struct {
  char* Key;
  void* Value;
  uint64_t Hash;
} vhash_item;

typedef struct {
  uint64_t Cursor;
  uint64_t Count;
  vhash_table* Table;
} vhash_iterator;

vhash_table* VHashTable_Init(uint64_t Capacity);
void VHashTable_Free(vhash_table *Table);

bool VHashTable_Insert(vhash_table* Table, uint8_t* Key, void* Value);
void* VHashTable_Get(vhash_table* Table, const uint8_t* Key);
void* VHashTable_Remove(vhash_table* Table, const uint8_t* Key);

uint64_t VHashTable_Count(vhash_table* Table);

vhash_iterator VHashTable_Iterator(vhash_table* Table);
vhash_item *VHashTable_Next(vhash_iterator* Iterator);


#endif

