#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITULO 50
#define MAX_AUTOR 50
#define HASH_SIZE 101

typedef struct livro {
    char titulo[MAX_TITULO];
    char autor[MAX_AUTOR];
    int ano;
    struct livro *prox;
} Livro;

typedef struct hash_table {
    Livro **livros;
    int tamanho;
} HashTable;

int hash(char *chave, int tamanho) {
    int h = 0;
    for (int i = 0; chave[i] != '\0'; i++) {
        h += chave[i];
    }
    return h % tamanho;
}

Livro *novo_livro(char *titulo, char *autor, int ano) {
    Livro *livro = (Livro*) malloc(sizeof(Livro));
    if (livro != NULL) {
        strcpy(livro->titulo, titulo);
        strcpy(livro->autor, autor);
        livro->ano = ano;
        livro->prox = NULL;
    }
    return livro;
}

void inserir_livro(HashTable *hash_table, char *titulo, char *autor, int ano) {
    int indice = hash(titulo, hash_table->tamanho);
    Livro *livro = hash_table->livros[indice];
    Livro *anterior = NULL;

    // Verifica se o livro j� existe na tabela hash
    while (livro != NULL && strcmp(livro->titulo, titulo) != 0) {
        anterior = livro;
        livro = livro->prox;
    }

    if (livro == NULL) { // Caso o livro n�o exista, insere na tabela hash
        livro = novo_livro(titulo, autor, ano);
        if (livro != NULL) {
            if (anterior == NULL) {
                hash_table->livros[indice] = livro;
            } else {
                anterior->prox = livro;
            }
        }
    } else { // Caso o livro j� exista, atualiza o autor e o ano
        strcpy(livro->autor, autor);
        livro->ano = ano;
    }
}

Livro *buscar_livro(HashTable *hash_table, char *titulo) {
    int indice = hash(titulo, hash_table->tamanho);
    Livro *livro = hash_table->livros[indice];

    // Busca pelo livro na lista encadeada do �ndice da tabela hash
    while (livro != NULL && strcmp(livro->titulo, titulo) != 0) {
        livro = livro->prox;
    }

    return livro;
}

void remover_livro(HashTable *hash_table, char *titulo) {
    int indice = hash(titulo, hash_table->tamanho);
    Livro *livro = hash_table->livros[indice];
    Livro *anterior = NULL;

    // Busca pelo livro na lista encadeada do �ndice da tabela hash
    while (livro != NULL && strcmp(livro->titulo, titulo) != 0) {
        anterior = livro;
        livro = livro->prox;
    }

    if (livro != NULL) {
        if (anterior == NULL) {
            hash_table->livros[indice] = livro->prox;
        } else {
            anterior->prox = livro->prox;
        }
        free(livro);
    }
}

void imprimir_livros(Livro *livro) {
if (livro != NULL) {
printf("T�tulo: %s\n", livro->titulo);
printf("Autor: %s\n", livro->autor);
printf("Ano: %d\n", livro->ano);
imprimir_livros(livro->prox);
}
}

void imprimir_tabela_hash(HashTable *hash_table) {
for (int i = 0; i < hash_table->tamanho; i++) {
printf("[%d]: ", i);
imprimir_livros(hash_table->livros[i]);
}
}

void liberar_memoria(HashTable *hash_table) {
for (int i = 0; i < hash_table->tamanho; i++) {
Livro *livro = hash_table->livros[i];
while (livro != NULL) {
Livro *proximo = livro->prox;
free(livro);
livro = proximo;
}
}
free(hash_table->livros);
free(hash_table);
}

int main() {
HashTable hash_table = (HashTable) malloc(sizeof(HashTable));
hash_table->livros = (Livro**) calloc(HASH_SIZE, sizeof(Livro*));
hash_table->tamanho = HASH_SIZE;
}


inserir_livro(hash_table, "O Senhor dos An�is", "J.R.R. Tolkien", 1954);
inserir_livro(hash_table, "Funda��o", "Isaac Asimov", 1951);
inserir_livro(hash_table, "Duna", "Frank Herbert", 1965);

Livro *livro = buscar_livro(hash_table, "O Senhor dos An�is");
if (livro != NULL) {
    printf("Livro encontrado:\n");
    printf("T�tulo: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Ano: %d\n", livro->ano);
} else {
    printf("Livro n�o encontrado\n");
}

remover_livro(hash_table, "Funda��o");

imprimir_tabela_hash(hash_table);

liberar_memoria(hash_table);

return 0;