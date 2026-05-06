#ifndef FUNCOES_H
#define FUNCOES_H

#include "estruturas.h"

No* criarNo(int chave);
No* inserir(No* raiz, int chave);
No* inserirNo(No* raiz);

No* removerNo(No* raiz, int chave);
No* encontrarMinimo(No* raiz);

void procurarNo(No* raiz, int chave, int nivel);


void preOrdem(No* raiz);


void somaPorNivel(No* raiz, int* soma, int nivel);

int altura(No* no);
int max(int a, int b);
int fatorBalanceamento(No* no);

No* rotacaoDireita(No* y);
No* rotacaoEsquerda(No* x);

#endif

