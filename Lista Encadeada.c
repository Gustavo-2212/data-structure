#include<stdio.h>
#include<stdlib.h>

struct lista{
    int info;
    struct lista* p;
};
typedef struct lista Lista;

Lista* iniciarLista(void){
    return NULL;
}

Lista* inserirElemento(Lista* l, int v){        //Insere o elemento sempre no início da Lista, empurrando os demais
    Lista* novo = (Lista*)malloc(sizeof(Lista));
    novo->info = v;
    novo->p = l;
    return novo;
}

Lista* inserirElementoNaOrdem(Lista* l, int v){
    Lista* novo = (Lista*)malloc(sizeof(Lista)); //Lista* novo = cria(v) -> Lista* criaNovoNó(int v){Lista* p = (Lista*)malloc(sizeof(Lista))p->info = v}
    Lista* anterior = NULL;                      //Ponteiro para o elemento anterior
    Lista* p = l;                                //Ponteiro para percorrer a lista

    novo->info = v;
    novo->p = l;

    while(p != NULL && p->info < v){             //Procura posição de inserção
        anterior = p;
        p = p->p;
    }

    if(anterior == NULL){   //Inserir elemento no início da Lista
        novo->p = l;
        l = novo;
    }else{
        novo->p = anterior->p;
        anterior->p = novo;
    }

    return l;
}

void imprimeElementos(Lista* l){
    Lista* p; //Variável auxiliar para percorrer a lista

    for(p = l; p != NULL; p = p->p)
        printf("info = %d\n", p->info);
}

int vazia(Lista* l){
    //1 - vazia; 0 - não vazia
    if(l == NULL)
        return 1;
    else
        return 0;
    //OU...
    /*
    retrun (l == NULL);
    */
}

Lista* busca(Lista* l, int v){
    Lista* p;
    for(p = l; p != NULL; p = p->p)
        if(p->info == v)
            return p;
    return NULL; //Caso não ache o elemento
}

Lista* removerElemento(Lista* l, int v){
    Lista* anterior = NULL; //Ponteiro para o elemento anterior
    Lista* p = l; //Ponterito para percorrer a lista

    while(p != NULL && p->info != v){
        anterior = p;
        p = p->p;
    }

    if(p == NULL)
        return l; //Não achou: retorna a lista original
    
    if(anterior == NULL){ //Caso o elemento à ser removido esteja no início da lista
        l = p->p;
    }else{ //Elemento à ser removido no meio da lista
        anterior->p = p->p;
    }
    free(p);
    return l;
}

void liberarLista(Lista* l){ //Remove elemento por elemento
    Lista* p = l;

    while(p != NULL){
        Lista* t = p->p; //Guarda referência para o próximo elemento a ser removido

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
    l = inserirElementoNaOrdem(l, 25);
    imprimeElementos(l);
    printf("\n");
    l = removerElemento(l, 23);
    imprimeElementos(l);
    printf("\n");
    liberarLista(l);

    return 0;
}