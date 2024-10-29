#include <stdio.h>
#include <stdlib.h>

struct lista {
    int info;
    struct lista *prox;
};

typedef struct lista Lista;

Lista* criaLista() {
    return NULL;
}

// Função para inserir um elemento no início da lista (sem ordem)
Lista* inserirLista(Lista *lista, int i) {
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->info = i;
    novo->prox = lista;
    return novo;
}

// Função para inserir um elemento de forma ordenada
Lista* inserirEmOrdem(Lista *l, int v) {
    Lista* novo = (Lista*) malloc(sizeof(Lista));
    novo->info = v;

    Lista* ant = NULL;  // Ponteiro anterior
    Lista* p = l;       // Ponteiro para percorrer

    // Procura a posição correta para inserir
    while (p != NULL && p->info < v) {
        ant = p;
        p = p->prox;
    }

    // Se for inserido no início
    if (ant == NULL) {
        novo->prox = l;
        l = novo;
    } else {
        // Insere o elemento no meio ou no final
        novo->prox = ant->prox;
        ant->prox = novo;
    }

    return l;
}

void imprimeLista(Lista *l) {
    Lista *p;
    if (l == NULL) {
        printf("A lista está vazia.\n");
        return;
    }
    for (p = l; p != NULL; p = p->prox) {
        printf("%d -> ", p->info);
    }
    printf("NULL\n");
}

int listaVazia(Lista *l) {
    return (l == NULL);
}

Lista* buscaLista(Lista *l, int v) {
    Lista *p;
    for (p = l; p != NULL; p = p->prox) {
        if (p->info == v) {
            return p;
        }
    }
    return NULL;
}

Lista* retiraLista(Lista *l, int v) {
    Lista *ant = NULL;  // Ponteiro para o anterior
    Lista *p = l;       // Pontei para percorrer a lista

    // Procura o elemento da lista
    while (p != NULL && p->info != v) {
        ant = p;
        p = p->prox;
    }

    // Não encontrou o elemento, retorna a lista original
    if (p == NULL) {
        return l;
    }

    // Retira o elemento
    if (ant == NULL) {
        // Retir ao primeiro elemento
        l = p->prox;
    } else {
        // Retira do meio ou final
        ant->prox = p->prox;
    }
    free(p);
    return l;
}

void liberaLista(Lista *l) {
    Lista *p = l;
    while (p != NULL) {
        Lista *t = p->prox;
        free(p);
        p = t;
    }
}

void menu() {
    printf("******************\n****** MENU ******\n");
    printf("******************\n\n1 - Inserir elemento (sem ordem)\n");
    printf("2 - Inserir elemento em ordem crescente\n");
    printf("3 - Imprimir lista\n");
    printf("4 - Buscar elemento\n");
    printf("5 - Remover elemento\n");
    printf("6 - Sair\n");
    printf("=======================================\n");
    printf("Escolha uma opção: ");
}

int main() {
    Lista* l = criaLista();
    int opcao, valor;
    Lista* encontrado;

    do {
        menu();
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o valor a ser inserido (sem ordem): ");
                scanf("%d", &valor);
                l = inserirLista(l, valor);
                printf("Valor %d inserido na lista (sem ordem).\n", valor);
                break;

            case 2:
                printf("Digite o valor a ser inserido em ordem crescente: ");
                scanf("%d", &valor);
                l = inserirEmOrdem(l, valor);
                printf("Valor %d inserido na lista em ordem.\n", valor);
                break;

            case 3:
                imprimeLista(l);
                break;

            case 4:
                printf("Digite o valor a ser buscado: ");
                scanf("%d", &valor);
                encontrado = buscaLista(l, valor);
                if (encontrado != NULL) {
                    printf("Valor %d encontrado na lista.\n", valor);
                } else {
                    printf("Valor %d não encontrado.\n", valor);
                }
                break;

            case 5:
                printf("Digite o valor a ser removido: ");
                scanf("%d", &valor);
                l = retiraLista(l, valor);
                printf("Valor %d removido da lista.\n", valor);
                break;

            case 6:
                liberaLista(l);
                printf("Saindo do programa e liberando a memória...\n");
                break;

            default:
                printf("Opção inválida! Tente novamente.\n");
        }
    } while (opcao != 6);

    return 0;
}
