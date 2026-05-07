#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "funcoes.h"        



int altura(No* no) {
    if (no == NULL)
        return 0;

    return no->altura;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int fatorBalanceamento(No* no) {
    if (no == NULL)
        return 0;

    return altura(no->esq) - altura(no->dir);
}

No* rotacaoDireita(No* y) {

    No* x = y->esq;
    No* T2 = x->dir;

    x->dir = y;
    y->esq = T2;

    y->altura = 1 + max(altura(y->esq), altura(y->dir));
    x->altura = 1 + max(altura(x->esq), altura(x->dir));

    return x;
}

No* rotacaoEsquerda(No* x) {

    No* y = x->dir;
    No* T2 = y->esq;

    y->esq = x;
    x->dir = T2;

    x->altura = 1 + max(altura(x->esq), altura(x->dir));
    y->altura = 1 + max(altura(y->esq), altura(y->dir));

    return y;
}

No* criarNo(int chave) {

    No* novoNo = (No*) malloc(sizeof(No));

    if (novoNo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return NULL;
    }

    novoNo->chave = chave;
    novoNo->altura = 1;
    novoNo->esq = NULL;
    novoNo->dir = NULL;

    return novoNo;
}

No* inserir(No* raiz, int chave) {

    if (raiz == NULL)
        return criarNo(chave);

    if (chave < raiz->chave)
        raiz->esq = inserir(raiz->esq, chave);

    else if (chave > raiz->chave)
        raiz->dir = inserir(raiz->dir, chave);

    else
        return raiz;

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    int fb = fatorBalanceamento(raiz);

    // Esquerda Esquerda
    if (fb > 1 && chave < raiz->esq->chave)
        return rotacaoDireita(raiz);

    // Direita Direita
    if (fb < -1 && chave > raiz->dir->chave)
        return rotacaoEsquerda(raiz);

    // Esquerda Direita
    if (fb > 1 && chave > raiz->esq->chave) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    // Direita Esquerda
    if (fb < -1 && chave < raiz->dir->chave) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

No* inserirNo(No* raiz) {

    int chave;

    printf("Digite a chave (-1 para sair): ");
    scanf("%d", &chave);

    while (chave != -1) {

        raiz = inserir(raiz, chave);

        printf("Digite a chave (-1 para sair): ");
        scanf("%d", &chave);
    }

    return raiz;
}

No* encontrarMinimo(No* raiz) {

    while (raiz != NULL && raiz->esq != NULL) {
        raiz = raiz->esq;
    }

    return raiz;
}

No* removerNo(No* raiz, int chave) {

    if (raiz == NULL)
        return raiz;
    

    if (chave < raiz->chave) {

        raiz->esq = removerNo(raiz->esq, chave);

    } else if (chave > raiz->chave) {

        raiz->dir = removerNo(raiz->dir, chave);

    } else {

        if (raiz->esq == NULL || raiz->dir == NULL) {

            No* temp;

            if (raiz->esq != NULL)
                temp = raiz->esq;
            else
                temp = raiz->dir;

            if (temp == NULL) {

                temp = raiz;
                raiz = NULL;

            } else {

                *raiz = *temp;
            }

            free(temp);

        } else {

            No* temp = encontrarMinimo(raiz->dir);

            raiz->chave = temp->chave;

            raiz->dir = removerNo(raiz->dir, temp->chave);
        }
    }

    if (raiz == NULL)
        return raiz;

    raiz->altura = 1 + max(altura(raiz->esq), altura(raiz->dir));

    int fb = fatorBalanceamento(raiz);

    // Esquerda Esquerda
    if (fb > 1 && fatorBalanceamento(raiz->esq) >= 0)
        return rotacaoDireita(raiz);

    // Esquerda Direita
    if (fb > 1 && fatorBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }

    // Direita Direita
    if (fb < -1 && fatorBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);

    // Direita Esquerda
    if (fb < -1 && fatorBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void procurarNo(No* raiz, int chave, int nivel) {

    if (raiz == NULL) {
         printf("A arvore esta vazia. Nada para procurar.\n");
        return;
    }

    if (chave < raiz->chave) {

        procurarNo(raiz->esq, chave, nivel + 1);

    } else if (chave > raiz->chave) {

        procurarNo(raiz->dir, chave, nivel + 1);

    } 
}

void preOrdem(No* raiz) {

    if (raiz != NULL) {

        printf("%d ", raiz->chave);

        preOrdem(raiz->esq);

        preOrdem(raiz->dir);
    }
}

void somaPorNivel(No* raiz, int* soma, int nivel) {

    if (raiz != NULL) {

        soma[nivel] += raiz->chave;

        somaPorNivel(raiz->esq, soma, nivel + 1);

        somaPorNivel(raiz->dir, soma, nivel + 1);
    }
}

void imprimirArvore(No* raiz, int espaco) {

    if (raiz == NULL)
        return;

    int incremento = 5;

    espaco += incremento;

   
    imprimirArvore(raiz->dir, espaco);

    printf("\n");

    for (int i = incremento; i < espaco; i++)
        printf(" ");

    printf("%d\n", raiz->chave);

    imprimirArvore(raiz->esq, espaco);
}