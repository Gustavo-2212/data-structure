#include <stdio.h>
#include <stdlib.h>

typedef struct NO* ArvBin;

struct NO{
    int info;
    struct NO *esq;
    struct NO *dir;
};

ArvBin* raiz;

ArvBin* criaArvore(/*int info*/);
void destroiArvore(ArvBin *raiz);
int arvoreVazia(ArvBin *raiz); // 0 - não vazia; 1 - vazia ou problema na criação
int alturaArvore(ArvBin *raiz);
int totalNO(ArvBin *raiz);
void pre_ordem(ArvBin *raiz);
void em_ordem(ArvBin *raiz);
void pos_ordem(ArvBin *raiz);
/*
int filhoDireita(ArvBin *raiz, int info);
int filhoEsquerda(ArvBin *raiz, int info);
*/

void main(){
    ArvBin* raiz = criaArvore(4);
    int vazia = arvoreVazia(raiz);
    int altura = alturaArvore(raiz);
    int totalNos = totalNO(raiz);

    /*
    if(filhoEsquerda(raiz, 5))
        printf("Filho Esquerdo criado!\n");
    if(filhoDireita(raiz, 2))
        printf("Filho Direito criado!\n");
    */

    pre_ordem(raiz);
    em_ordem(raiz);
    pos_ordem(raiz);
    if(vazia)
        printf("Vazia!\n");
    printf("Altura: %d\nTotal de nos: %d\n", vazia, altura, totalNos);

    destroiArvore(raiz);
}

ArvBin* criaArvore(/*int info*/){
    ArvBin* raiz = (ArvBin*)malloc(sizeof(ArvBin));
    if(raiz != NULL)
        *raiz = NULL;

    /*
    (*raiz)->info = info;
    (*raiz)->esq = NULL;
    (*raiz)->dir = NULL;
    */
    return raiz;
}

/*
int filhoEsquerda(ArvBin *raiz, int info){
    ArvBin *node = criaArvore(info);
    if((*raiz)->esq == NULL){
        (*raiz)->esq = node;
        // (*raiz)->esq->pai = raiz;
        return 1;
    } else return 0;
}
int filhoDireita(ArvBin *raiz, int info){
    ArvBin *node = criaArvore(info);
    if((*raiz)->dir == NULL){
        (*raiz)->dir = node;
        //(*raiz)->dir->pai = raiz;
        return 1;
    } else return 0;
}
*/

void liberaNO(struct NO* no){
    if(no == NULL)
        return;
    liberaNO(no->esq);
    liberaNO(no->dir);
    free(no);
    no = NULL;
}
void destroiArvore(ArvBin *raiz){
    if(raiz == NULL)
        return;
    liberaNO(*raiz);
    free(raiz);
}

int arvoreVazia(ArvBin *raiz){
    if(raiz == NULL)
        return 1;
    if(*raiz == NULL)
        return 1;
    return 0;
}

int alturaArvore(ArvBin *raiz){
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    int alturaEsquerda = alturaArvore(&((*raiz)->esq));  //  tentar tirar esse '&' depois
    int alturaDireita = alturaArvore(&((*raiz)->dir));
    if(alturaEsquerda > alturaDireita)
        return (alturaEsquerda + 1);
    else
        return (alturaDireita + 1);
}

int totalNO(ArvBin *raiz){
    if(raiz == NULL)
        return 0;
    if(*raiz == NULL)
        return 0;
    int alturaEsquerda = totalNO(&((*raiz)->esq));
    int alturaDireita = totalNO(&((*raiz)->dir));
    return (alturaEsquerda + alturaDireita + 1); // +1: nó pai
}

//Percorrendo a árvore
void pre_ordem(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        printf("%d\n", (*raiz)->info);
        pre_ordem(&((*raiz)->esq));
        pre_ordem(&((*raiz)->dir));
    }
}

void em_ordem(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        em_ordem(&((*raiz)->esq));
        printf("%d\n", (*raiz)->info);
        em_ordem(&((*raiz)->dir));
    }
}

void pos_ordem(ArvBin *raiz){
    if(raiz == NULL)
        return;
    if(*raiz != NULL){
        pos_ordem(&((*raiz)->esq));
        pos_ordem(&((*raiz)->dir));
        printf("%d\n", (*raiz)->info);
    }
}