#include<stdio.h>

//Estrutura do nó da Árvore Binária
typedef struct node{
    int dado;
    struct node *esq;
    struct node *dir;
    struct node *pai;
} Node;

//Retorna o ponteiro que aponta para o filho à esquerda
Node* esquerda(Node *raiz){
    Node *aux = raiz;
    if(aux->esq != NULL) aux = aux->esq;
    else return NULL;
    return aux;
}

//Retorna o ponteiro que aponta para o filho à direita
Node* direita(Node *raiz){
    Node *aux = raiz;
    if(aux->dir != NULL) aux = aux->dir;
    else return NULL;
    return aux;
}

//Retorna o ponteiro que aponta para o pai do nó inserido
Node* pai_no(Node *raiz){
    Node *aux = raiz;
    if(aux->pai != NULL) aux = aux->pai;
    else return NULL;
    return aux;
}

//Retorna o ponteiro que aponta para o irmão do nó inserido
Node* irmao(Node *raiz){
    Node *aux = raiz;

    if(aux == aux->pai->esq){
        if(aux->pai->dir != NULL){
            aux = aux->pai->dir;
            return aux;
        } else return NULL;
    }
    if(aux == aux->pai->dir){
        if(aux->pai->esq != NULL){
            aux = aux->pai->esq;
            return aux;
        } else return NULL;
    }
}

//Cria uma árvore binária com a raiz com o dado inserido, e a retorna
Node* criaArvoreBinaria(int dado){
    //Aloca memória para o novo nó
    Node *node = (Node*)malloc(sizeof(Node));

    //Define o dado do nó
    node->dado = dado;

    //Inicializa os filhos da esquerda e direita e o pai como NULL.
    node->esq = NULL;
    node->dir = NULL;
    node->pai = NULL;
    return node;
}

//Cria um filho à esquerda do nó inserido, retorna 1 se conseguir e 0 se falhar
int filhoEsquerda(Node *raiz, int dado){
    Node *node = criaArvoreBinaria(dado);
    if(raiz->esq == NULL){
        raiz->esq = node;
        raiz->esq->pai = raiz;
        return 1;
    } else return 0;
}

//Cria um filho à direita do nó inserido, retorna 1 se conseguir e 0 se falhar
int filhoDireita(Node *raiz, int dado){
    Node *node = criaArvoreBinaria(dado);
    if(raiz->dir == NULL){
        raiz->dir = node;
        raiz->dir->pai = raiz;
        return 1;
    } else return 0;
}

//Percorrendo árvores binárias
//Percorrendo em PRE ORDEM
void pre_ordem(Node *raiz){
    if(raiz == NULL) return;
    printf("%d\n", raiz->dado);
    pre_ordem(raiz->esq);
    pre_ordem(raiz->dir);
}

//Percorrendo em ORDEM
void ordem(Node *raiz){
    if(raiz == NULL) return;
    ordem(raiz->esq);
    printf("%d\n", raiz->dado);
    ordem(raiz->dir);
}

//Percorrendo em POS ORDEM
void pos_ordem(Node *raiz){
    if(raiz == NULL) return;
    pos_ordem(raiz->esq);
    pos_ordem(raiz->dir);
    printf("%s/n", raiz->dado);
}

//Operações de Buscas em Árvores Binárias
//Busca um valor específico na árvore binária. Valor encontrado - return 1, se não 0
int buscaArvoreBinaria(Node *raiz, int dado){
    if(raiz->dado == dado) return 1;
    else{
        if(dado > raiz->dado) raiz = direita(raiz);
        else raiz = esquerda(raiz);
        if(raiz == NULL) return 0;
        buscaArvoreBinaria(raiz, dado);
    }
}

//Insere um novo nó com o valor dado na árvore binária de busca raiz, retorna 1 - sucesso e 0 - se um nó
//com o mesmo valor já estiver alocado
int insereArvoreBinaria(Node *raiz, int dado){
    if(raiz->dado == dado) return 0;
    else{
        if(dado > raiz->dado){
            if(direita(raiz) != NULL){
                raiz = direita(raiz);
                insereArvoreBinaria(raiz, dado);
            }
            else{
                filhoDireita(raiz, dado);
                return 1;
            }
        } else {
            if(esquerda(raiz) != NULL){
                raiz = esquerda(raiz);
                insereArvoreBinaria(raiz, dado);
            } else {
                filhoEsquerda(raiz, dado);
                return 1;
            }
        }
    }
}

//Remove o nó com o valor dado da árvore binária de busca raiz
int removeArvoreBinaria(Node *raiz, int dado){
    Node *pai = raiz;

    while(raiz != NULL && raiz->dado != dado){
        pai = raiz;
        if(dado > raiz->dado) raiz = direita(raiz);
        else raiz = esquerda(raiz);
    }

    if(raiz != NULL){
        //Se houver duas subárvores
        if(esquerda(raiz) != NULL && direita(raiz) != NULL){
            Node *aux = raiz;
            pai = raiz;
            raiz = direita(raiz);
            while(esquerda(raiz) != NULL){
                pai = raiz;
                raiz = esquerda(raiz);
            }
            aux->dado = raiz->dado;
        }

        //Precisa ser um 'if', e não um 'else if'
        //Se houver uma árvore à esquerda
        if(esquerda(raiz) == NULL && direita(raiz) != NULL){
            if(pai->esq == raiz) pai->esq = direita(raiz);
            else pai->dir = direita(raiz);
        }
        //Se houver uma subárvore à direita
        else if(esquerda(raiz) != NULL && direita(raiz) == NULL){
            if(pai->esq == raiz) pai->esq = esquerda(raiz);
            else pai->dir = esquerda(raiz);
        }
        //Se for uma folha
        else if(esquerda(raiz) == NULL && direita(raiz) == NULL){
            if(pai->esq == raiz) pai->esq = NULL;
            else pai->dir = NULL;
        }
        free(raiz);
    }
}

int main(){
    Node *arvore;

    arvore = criaArvoreBinaria(5);
    filhoDireita(arvore, 3);
    filhoEsquerda(arvore, 2);
    Node *filho_esquerdo = esquerda(arvore);
    Node *filho_direito = direita(arvore);
    Node *pai_do_no = pai_no(arvore->dir);
    Node *irmao_do_no = irmao(arvore->esq);
    int no = arvore->dado;

    printf("No:\t%d\n", no);
    printf("Filho esquerdo:\t%d\n", filho_esquerdo->dado);
    printf("Filho direito:\t%d\n", filho_direito->dado);
    printf("Pai do no %d:\t%d\n", arvore->dir->dado, pai_do_no->dado);
    printf("Irmao do no %d:\t%d\n", arvore->esq->dado, irmao_do_no->dado);

    return 0;
}