#ifndef _V_HASH_TABLE_
#define _V_HASH_TABLE_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct vhash_iterator vhash_iterator;
typedef struct vhash_item vhash_item;
typedef struct vhash_table vhash_table;


vhash_table* VHashTable_Init(uint64_t Capacity);

bool VHashTable_Insert(vhash_table* Table, char* Key, void* Value);
void* VHashTable_Get(vhash_table* Table, const char* Key);
void* VHashTable_Remove(vhash_table* Table, const char *Key);

uint64_t VHashTable_Count(vhash_table* Table);

vhash_iterator VHashTable_Iterator(vhash_table* Table);
vhash_item *VHashTable_Next(vhash_iterator* Iterator);


#endif

