#include <stdio.h>
#include <stdlib.h>
#include "funcoes.h"
#include "estruturas.h"

int main() {

    int opcao, chave;

    No* raiz = NULL;

    do {

        printf("\n=== Menu Arvore Binaria ===\n");

        printf("1. Inserir nos\n");
        printf("2. Procurar no\n");
        printf("3. Remover no\n");
        printf("4. Exibir em pre-ordem\n");
        printf("5. Soma por nivel\n");
        printf("6. Imprimir Arvore\n");
        printf("0. Sair\n");

        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao) {

            case 1:

                raiz = inserirNo(raiz);

            break;

            case 2:

                if (raiz == NULL) {
                     printf("A arvore esta vazia. Nada para procurar.\n");

                } else {
                    printf("Digite a chave: ");
                    scanf("%d", &chave);
                    procurarNo(raiz, chave, 1);
                }

            break;

            case 3:
                if (raiz == NULL) {
                    printf("A arvore esta vazia. Nada para remover.\n");
                } else {
                    printf("Digite a chave: ");
                    scanf("%d", &chave);
                    raiz = removerNo(raiz, chave);
                }
            break;
            case 4:
                if (raiz == NULL) {
                    printf("A arvore esta vazia. Nada para mostrar.\n");
                } else {
                    printf("Arvore em pre-ordem: ");
                    preOrdem(raiz);
                    printf("\n");
                }

            break;
            case 5:
                if (raiz == NULL) {
                    printf("A arvore esta vazia. Nao ha soma possivel.\n");
                } else {
                    int soma[100] = {0};
                    somaPorNivel(raiz, soma, 0);
                    printf("Soma por nivel:\n");
                    for (int i = 0; i < 100 && soma[i] != 0; i++) {
                        printf("Nivel %d: %d\n", i, soma[i]);
                    }
                }

            break;
            case 6:
                if (raiz == NULL) {
                    printf("Arvore vazia. Nada para desenhar.\n");
                } else {
                    printf("Arvore desenhada:\n");
                    imprimirArvore(raiz, 0);
                }
            break;
            case 0:
                printf("Saindo...\n");
            break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    return 0;
}