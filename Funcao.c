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

    // Verifica se o livro já existe na tabela hash
    while (livro != NULL && strcmp(livro->titulo, titulo) != 0) {
        anterior = livro;
        livro = livro->prox;
    }

    if (livro == NULL) { // Caso o livro não exista, insere na tabela hash
        livro = novo_livro(titulo, autor, ano);
        if (livro != NULL) {
            if (anterior == NULL) {
                hash_table->livros[indice] = livro;
            } else {
                anterior->prox = livro;
            }
        }
    } else { // Caso o livro já exista, atualiza o autor e o ano
        strcpy(livro->autor, autor);
        livro->ano = ano;
    }
}

Livro *buscar_livro(HashTable *hash_table, char *titulo) {
    int indice = hash(titulo, hash_table->tamanho);
    Livro *livro = hash_table->livros[indice];

    // Busca pelo livro na lista encadeada do índice da tabela hash
    while (livro != NULL && strcmp(livro->titulo, titulo) != 0) {
        livro = livro->prox;
    }

    return livro;
}

void remover_livro(HashTable *hash_table, char *titulo) {
    int indice = hash(titulo, hash_table->tamanho);
    Livro *livro = hash_table->livros[indice];
    Livro *anterior = NULL;

    // Busca pelo livro na lista encadeada do índice da tabela hash
    while (livro != NULL && strcmp(livro->titulo, titulo) != 0) {
        anterior = livro;
        livro = livro->prox;
    }

    if (livro == NULL) { // Caso o livro não seja encontrado, não há nada a ser feito
        return;
    }

    if (anterior == NULL) { // Se o livro a ser removido é o primeiro da lista, atualiza o ponteiro do índice da tabela hash
        hash_table->livros[indice] = livro->prox;
    } else { // Caso contrário, atualiza o ponteiro do livro anterior para o próximo livro da lista
        anterior->prox = livro->prox;
    }

    free(livro); // Libera a memória alocada pelo livro a ser removido
}

void liberar_tabela(HashTable *hash_table) {
    for (int i = 0; i < hash_table->tamanho; i++) {
        Livro *livro = hash_table->livros[i];
        while (livro != NULL) {
            Livro *temp = livro;
            livro = livro->prox;
            free(temp);
        }
    }
    free(hash_table->livros);
    free(hash_table);
}

void imprimir_tabela(HashTable *hash_table) {
    for (int i = 0; i < hash_table->tamanho; i++) {
        Livro *livro = hash_table->livros[i];
        while (livro != NULL) {
            printf("%s, %s, %d\n", livro->titulo, livro->autor, livro->ano);
            livro = livro->prox;
        }
    }
}

HashTable *criar_hash_table(int tamanho) {
    HashTable *hash_table = (HashTable*) malloc(sizeof(HashTable));
    if (hash_table != NULL) {
        hash_table->livros = (Livro**) malloc(tamanho * sizeof(Livro*));
        if (hash_table->livros != NULL) {
            hash_table->tamanho = tamanho;
            for (int i = 0; i < tamanho; i++) {
                hash_table->livros[i] = NULL;
            }
            return hash_table;
        } else {
            free(hash_table);
        }
    }
    return NULL;
}

int main() {
    HashTable *hash_table = criar_hash_table(HASH_SIZE);

    // Inserindo alguns livros na tabela hash
    inserir_livro(hash_table, "O Senhor dos Aneis", "J.R.R. Tolkien", 1954);
    inserir_livro(hash_table, "Fundacao", "Isaac Asimov", 1951);
    inserir_livro(hash_table, "Duna", "Frank Herbert", 1965);
    inserir_livro(hash_table, "O Guia do Mochileiro das Galáxias", "Douglas Adams", 1979);
    inserir_livro(hash_table, "O Restaurante no Fim do Universo", "Douglas Adams", 1980);
    inserir_livro(hash_table, "A Vida, o Universo e Tudo Mais", "Douglas Adams", 1982);
    inserir_livro(hash_table, "Até Mais, e Obrigado pelos Peixes!", "Douglas Adams", 1984);
    inserir_livro(hash_table, "Praticamente Inofensiva", "Douglas Adams", 1992);

    // Buscando livros na tabela hash
    //Inserir aqui o livro a ser buscado
    Livro *livro = buscar_livro(hash_table, "O Senhor dos Aneis");
    if (livro != NULL) {
        printf("Livro encontrado: %s, %s, %d\n", livro->titulo, livro->autor, livro->ano);
    } else {
        printf("Livro não encontrado.\n");
    }
  
    livro = buscar_livro(hash_table, "Dirk Gently, Agência de Investigações Holísticas");
    if (livro != NULL) {
        printf("Livro encontrado: %s, %s, %d\n", livro->titulo, livro->autor, livro->ano);
    } else {
        printf("Livro não encontrado.\n");
    }

    // Removendo livros da tabela hash
    remover_livro(hash_table, "Até Mais, e Obrigado pelos Peixes!");
    remover_livro(hash_table, "O Guia do Mochileiro das Galáxias");

    // Buscando livros novamente
    livro = buscar_livro(hash_table, "O Guia do Mochileiro das Galáxias");
    if (livro != NULL) {
        printf("Livro encontrado: %s, %s, %d\n", livro->titulo, livro->autor, livro->ano);
    } else {
        printf("Livro não encontrado.\n");
    }

    livro = buscar_livro(hash_table, "Até Mais, e Obrigado pelos Peixes!");
    if (livro != NULL) {
        printf("Livro encontrado: %s, %s, %d\n", livro->titulo, livro->autor, livro->ano);
    } else {
        printf("Livro não encontrado.\n");
    }

    // Liberando a memória alocada pela tabela hash e seus livros
    //destruir_hash_table(hash_table);

    return 0;
}
