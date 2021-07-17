#include<stdio.h>
int pilha[73], topo=-1, num;

void exibir_pilha(){
    int i;
    if(topo == -1)
        printf("\nPilha Vazia!");
    else
        for(i=topo; i>=0; i--)
            printf("%d\n", pilha[i]);
}
void inserir_elemento(){
    if(topo == 37)
        printf("\nPilha Cheia!");
    else{
        printf("\nInforme o elemento: ");
        scanf("%d", &num);
        topo++;
        pilha[topo] = num;
        printf("\nElemento %d foi inserirdo com sucesso!", num);
    }
}

void remover_elemento(){
    if(topo == -1)
        printf("\nPilha Vazia!");
    else{
        num = pilha[topo];
        topo--;
        printf("\nElemento %d foi removido com sucesso!", num);
    }
}

void exibir_topo(){
    if(topo==-1)
        printf("\nPilha vazia!");
    else printf("\nElemento do topo: %d", pilha[topo]);
}
void main(){
    int op, resp;

    do{
        printf("\n1 - Inserir Elementos");
        printf("\n2 - Remover Elementos");
        printf("\n3 - Exibir Elementos");
        printf("\n4 - Exibir topo");

        printf("\nEscolha a operacao desejada: ");
        scanf("%d", &op);

        switch(op){

            case 1: inserir_elemento();
                break;
            case 2: remover_elemento();
                break;
            case 3: exibir_pilha();
                break;
            case 4: exibir_topo();
                break;
            
            default: printf("\nOperacao invalida!\n");
        }

        printf("\nDeseja continuar? 1 - sim | 0  - nao: ");
        scanf("%d", &resp);
    }while(resp==1);
}