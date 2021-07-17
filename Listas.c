#include<stdio.h>

int Lista[5], num, i, quant = -1, pos, achou;

void inserir_inicio(){
    if(quant == 4) printf("Lista Cheia!");
    else{
        printf("Informe o elemento: ");
        scanf("%d", &num);

        for(i=quant+1; i>0; i--) Lista[i] = Lista[i - 1];
        quant++;
        Lista[0] = num;
        printf("O elemento %d foi inserido!\n", num);
    }
}

void inserir_fim(){
    if(quant == 4) printf("Lista Cheia!");
    else{
        printf("Informe o elemento a ser inserido: ");
        scanf("%d", &num);
        Lista[quant + 1] = num;
        quant++;
        printf("O elemento %d foi inserido!\n", num);
    }
}

void inserir_elemento(){
    if(quant == 4) printf("Lista Cheia!");
    else{
        printf("Informe o elemento: ");
        scanf("%d", &num);

        printf("Informe tambem a posicao que deseja inserir o elemento (0 - 4): ");
        scanf("%d", &pos);

        if(pos < 0 || pos > 4) printf("Posicao Invalida!!\n");
        else{
            for(i = quant + 1; i > pos; i--) Lista[i] = Lista[i - 1];
            quant++;
            Lista[pos] = num;
            printf("O elemento %d foi inserido na posicao %d.\n", num, pos);
        }
    }
}

void remover_elemento(){
    if(quant == -1) printf("Lista Vazia!");
    else{
        printf("Informe o elemento: ");
        scanf("%d", &num);
        pos = -1; //variavel da Posicao do elemento inicializada

        for(i = 0; i <= quant; i++)
            if(Lista[i] == num) pos = i;
            if(pos != -1){

                for(i = pos; i < quant; i++) Lista[i] = Lista[i + 1];
                quant--;
                printf("O elemento %d foi removido da posicao %d!\n", num, pos);
            } else printf("O elemento %d nao foi encontrado!\n", num);
    }
}

void exibir_lista(){
    if(quant == -1) printf("Lista Vazia!!");
    else{
        for(i = 0; i <= quant; i++) printf("%d\t", Lista[i]);
    }
}

void busca_sequencial(){
    if(quant == -1) printf("Lista Vazia!");
    else{
        printf("Informe o elemento: ");
        scanf("%d", &num);
        i = 0;
        achou = 0;
        while(i <= quant && achou == 0)
            if(Lista[i] == num){
                achou = 1;
                pos = i;
            } else i++;
            if(achou == 0) printf("O elemento %d nao foi encontrado!\n", num);
            else printf("O elemento %d foi encontrado na posicao %d.\n", num, pos);
    }
}

void ordenar_bubleSort(){
    int j, aux;
    if(quant == -1) printf("Lista Vazia!");
    else{
        for(i = 0; i < quant; i++)
            for(j = 0; j < quant; j++)
                if(Lista[j] > Lista[j+1]){
                    aux = Lista[j];
                    Lista[j] = Lista[j + 1];
                    Lista[j + 1] = aux;
                }
        printf("Ordenacao realizada com sucesso!\n");
    }
}

void busca_binaria(){
    int inicio, fim;
    if(quant == -1) printf("Lista Vazia!");
    else{
        ordenar_bubleSort();
        printf("Informe o elemento: ");
        scanf("%d", &num);
        achou = 0;
        inicio = 0;
        fim = quant;
        pos = (inicio + fim)/2;
        while(achou == 0 && inicio <= fim){
            if(num == Lista[pos]) achou = 1;
            else{
                if(num > Lista[pos]) 
                    inicio = pos + 1;
                else fim = pos - 1;
                pos = (inicio + fim)/2;
            }
        }
        if(achou == 0) printf("O elemento %d nao foi encontrado.\n", num);
        else printf("O elemento %d foi encontrado na posicao %d.\n", num , pos);
    }
}

void main(){
    int op, resp;


    do{
        printf("\n1 - Inserir Elementos Inicio");
        printf("\n2 - Inserir Elementos Fim");
        printf("\n3 - Inserir Elementos");
        printf("\n4 - Remover Elementos");
        printf("\n5 - Exibir Lista");
        printf("\n6 - Busca Sequencial");
        printf("\n7 - Ordenar BubleSort");
        printf("\n8 - Busca Binaria");

        printf("\nEscolha a operacao desejada: ");
        scanf("%d", &op);

        switch(op){

            case 1: inserir_inicio();
                break;
            case 2: inserir_fim();
                break;
            case 3: inserir_elemento();
                break;
            case 4: remover_elemento();
                break;
            case 5: exibir_lista();
                break;
            case 6: busca_sequencial();
                break;
            case 7: ordenar_bubleSort();
                break;
            case 8: busca_binaria();
                break;
            
            default: printf("\nOperacao invalida!\n");
        }

        printf("\nDeseja continuar? 1 - sim | 0  - nao: ");
        scanf("%d", &resp);
    }while(resp==1);

    return 0;
}