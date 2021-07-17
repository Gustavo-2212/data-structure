#include<stdio.h>
#include<stdlib.h>

struct lista{
    int info;
    struct lista *ant;
    struct lista *prox;
};

typedef struct lista Lista;

Lista* iniciarLista(void){
    return NULL;
}

Lista* inserirElemento(Lista* l, int v){
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    novo->info = v;
    novo->prox = l;
    novo->ant = NULL;

    if(l != NULL)
        l->ant = novo;
    return novo;
}

Lista* busca(Lista* l, int v){
    Lista* p;
    for(p = l; p != NULL; p = p->prox)
        if(p->info == v)
            return p;
    return NULL; 
}

Lista* removerElemento(Lista* l, int v){
    Lista* p = busca(l, v);

    if(p == NULL)
        return l;
    
    if(l == p)
        l = p->prox;
    else
        p->ant->prox = p->prox;

    if(p->prox != NULL) 
        p->prox->ant = p->ant;

    free(p);

    return l;    
}

void imprimeElementos(Lista* l){
    Lista* p; //Variável auxiliar para percorrer a lista

    for(p = l; p != NULL; p = p->prox)
        printf("info = %d\n", p->info);
}

void liberarLista(Lista* l){ //Remove elemento por elemento
    Lista* p = l;

    while(p != NULL){
        Lista* t = p->prox; //Guarda referência para o próximo elemento a ser removido

        free(p); //Librea p
        p = t; //Faz p apontar para o próximo elemento
    }
}

int main(){
    Lista* l;
    l = iniciarLista();
    l = inserirElemento(l, 23);
    l = inserirElemento(l, 56);
    l = inserirElemento(l, 7);

    imprimeElementos(l);
    printf("\n");
    l = removerElemento(l, 23);
    imprimeElementos(l);
    printf("\n");
    liberarLista(l);

    return 0;
}