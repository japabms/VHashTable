#include "VHashTable.h"
#include <stdint.h>
#include <string.h>
#include <sys/types.h>

#define INIT_V_HASH_TABLE_CAPACITY 16

// TODO:
// - Add double hashing

struct vhash_table{
  vhash_item* Items;
  uint64_t Count;
  uint64_t Capacity;
};

vhash_iterator VHashTable_Iterator(vhash_table* Table) {
  vhash_iterator Result = {0};
  Result.Cursor = 0;
  Result.Count = 0;
  Result.Table = Table;

  return Result;
}

vhash_table* VHashTable_Init(uint64_t Capacity) {
  vhash_table* Result = calloc(1, sizeof(vhash_table));
  if(Capacity == 0) {
    Capacity = INIT_V_HASH_TABLE_CAPACITY;
  }

  Result->Items = calloc(Capacity, sizeof(vhash_item));
  Result->Count = 0;
  Result->Capacity = Capacity;
  
  return Result;
}

void VHashTable_Free(vhash_table *Table) {
  free(Table->Items);
  free(Table);
  Table->Items = NULL;
  Table = NULL;
}

// djb2 hash function
static uint64_t VHashTable_Hash(const char* Key) {
    unsigned long Hash = 5381;
    int c;
    while ((c = *Key++))
        Hash = ((Hash << 5) + Hash) + c; // hash * 33 + c
    return Hash;
}

static bool VHashTable_ItemIsEmpty(vhash_table* Table, uint64_t Index) {
  return Table->Items[Index].Key == NULL;
}

static void VHashTable_Rehash(vhash_table* Table) {
  uint64_t OldCapacity = Table->Capacity;
  vhash_item* OldItems = Table->Items;


  Table->Capacity *= 2;
  Table->Count = 0;
  Table->Items = calloc(Table->Capacity, sizeof(vhash_item));

  for(int i = 0; i < OldCapacity; i++) {
    vhash_item Item = OldItems[i];
    
    uint64_t NewIndex = Item.Hash % Table->Capacity;
    while(!VHashTable_ItemIsEmpty(Table, NewIndex)) {
	// Linear Probing
	NewIndex = (NewIndex+1) % Table->Capacity;      
    }

    Table->Items[NewIndex] = Item;
  }
  free(OldItems);
}

bool VHashTable_Insert(vhash_table* Table, char* Key, void* Value) {
  if(Table->Count >= Table->Capacity) {
    // TODO(victor): Rehash
    VHashTable_Rehash(Table);
  }
  
  vhash_item Item;
  Item.Key = strdup(Key);
  Item.Value = Value;

  uint64_t Hash = VHashTable_Hash(Key);
  Item.Hash = Hash;
  uint64_t Index = Hash % Table->Capacity;

  while(!VHashTable_ItemIsEmpty(Table, Index)) {
    if(strcmp(Table->Items[Index].Key, Key) == 0) {
      // Replacing the value if already exist
      Table->Items[Index].Value = Value;
      free(Item.Key);
      return true;
    } else {
      // Linear Probing
      Index = (Index+1) % Table->Capacity;      
    }
  }

  Table->Items[Index] = Item;
  Table->Count += 1;
  return true;
}

void* VHashTable_Get(vhash_table* Table, const char *Key) {
  uint64_t Hash = VHashTable_Hash(Key);
  uint64_t Index = Hash % Table->Capacity;
  while(Table->Items[Index].Key != NULL) {
    if(strcmp(Table->Items[Index].Key, Key) == 0) {
      return Table->Items[Index].Value;
    } else {
      Index = (Index+1) % Table->Capacity;          
    }
  }

  return NULL;
}

void* VHashTable_Remove(vhash_table* Table, const char *Key) {
  uint64_t Hash = VHashTable_Hash(Key);
  uint64_t Index = Hash % Table->Capacity;

  while(Table->Items[Index].Key != NULL) {
    if(strcmp(Table->Items[Index].Key, Key) == 0) {
      vhash_item* Item = &Table->Items[Index];
      free(Item->Key);
      Item->Key = NULL;
      Table->Count -= 1;
      return Item->Value;
    } else {
      Index = (Index+1) % Table->Capacity;          
    }
  }

  return NULL;
}

uint64_t VHashTable_Count(vhash_table* Table) {
  return Table->Count;
}

vhash_item *VHashTable_Next(vhash_iterator* Iterator) {
  vhash_item *Item;
  if(Iterator->Cursor >= Iterator->Table->Capacity ||
     Iterator->Count == Iterator->Table->Count) {
    return NULL;
  } 

  while(VHashTable_ItemIsEmpty(Iterator->Table, Iterator->Cursor)) {
    Iterator->Cursor += 1;
  }

  Item = &Iterator->Table->Items[Iterator->Cursor];
  Iterator->Cursor += 1;
  Iterator->Count += 1;

  return Item;
}
