#include <stdio.h>
#include "../src/VHashTable.h"

int main() {
    vhash_table* table = VHashTable_Init(10);

    VHashTable_Insert(table, "sexo", "xvideos.com");

    char* Valor = (char*) VHashTable_Get(table, "sexo");
    printf("valor: %s\n", Valor);

    
    VHashTable_Free(table);

    return 0;
}
