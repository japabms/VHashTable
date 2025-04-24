#include <stdio.h>
#include "../src/VHashTable.h"

int main() {
    // Inicializa uma hash table com capacidade de 10 elementos
    vhash_table* table = VHashTable_Init(10);
    if (!table) {
        printf("Erro ao inicializar a tabela hash.\n");
        return 1;
    }

    // Insere alguns pares chave-valor
    VHashTable_Insert(table, "chave1", "valor1");
    VHashTable_Insert(table, "chave2", "valor2");
    VHashTable_Insert(table, "chave3", "valor3");

    // Recupera e imprime valores
    char* val = (char*)VHashTable_Get(table, "chave2");
    if (val) {
        printf("Valor encontrado para 'chave2': %s\n", val);
    } else {
        printf("Valor não encontrado para 'chave2'\n");
    }

    // Remove um valor
    char* removed = (char*)VHashTable_Remove(table, "chave1");
    if (removed) {
        printf("Removido: chave1 -> %s\n", removed);
    }

    // Tenta obter a chave removida
    if (!VHashTable_Get(table, "chave1")) {
        printf("chave1 removida com sucesso.\n");
    }

    // Conta os elementos atuais
    printf("Total de elementos: %llu\n", VHashTable_Count(table));

    // Itera sobre os elementos restantes
    printf("Iterando sobre a tabela:\n");
    vhash_iterator it = VHashTable_Iterator(table);
    vhash_item* item;
    while ((item = VHashTable_Next(&it)) != NULL) {
        printf("Chave: %s | Valor: %s\n", (char*)item->Key, (char*)item->Value);
    }

    // Aqui seria interessante uma função para liberar a tabela
    // VHashTable_Free(table); // caso implementado

    return 0;
}
