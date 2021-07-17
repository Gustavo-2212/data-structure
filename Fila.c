#include<stdio.h>
float fila[49], num;
int quant = -1;

void remover_elemento(){
    if(quant==-1)
        printf("\nFila vazia!");
    else{
        num = fila[0];
        for(int i=0; i<quant;i++)
            fila[i] = fila[i+1];
        quant--;
        printf("\nElemento %f foi removido com sucesso", num);
    }
}

void exibir_ultimo(){
    if(quant == -1)
        printf("\nFila Vazia!");
    else printf("\nUltimo elemento da fila: %f", fila[quant]);
}

void exibir_primeiro(){
    if(quant == -1)
        printf("\nFila vazia!");
    else printf("Primeiro elemento: %f", fila[0]);
}

void exibir_fila(){
    if(quant==-1)
        printf("\nFila vazia!");
    else
        for(int i=0; i<=quant; i++)
            printf("%f\t", fila[i]);  
}
void inserir_elemento(){
    if(quant==48)
        printf("\nFila cheia!");
    else{
        printf("\nInforme o elemento: ");
        scanf("%f", &num);
        quant++;
        fila[quant] = num;
        printf("\nElemento %f foi inserirdo!", num);
    }
}

void main(){
int op, resp;

    do{
        printf("\n1 - Inserir Elemento");
        printf("\n2 - Remover Elemento");
        printf("\n3 - Exibir Ultimo");
        printf("\n4 - Exibir Primeiro");
        printf("\n5 - Exibir Elementos");

        printf("\nEscolha a operacao desejada: ");
        scanf("%d", &op);

        switch(op){

            case 1: exibir_ultimo();
                break;
            case 2: remover_elemento();
                break;
            case 3: exibir_ultimo();
                break;
            case 4: exibir_primeiro();
                break;
            case 5: exibir_fila();
                break;

            default: printf("\nOperacao invalida!\n");
        }

        printf("\nDeseja continuar? 1 - sim | 0  - nao: ");
        scanf("%d", &resp);
    }while(resp==1);
}