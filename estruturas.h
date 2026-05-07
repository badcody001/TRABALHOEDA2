#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

typedef struct no {
    int chave;
    int altura;
    struct no *esq;
    struct no *dir;
} No;

#endif
