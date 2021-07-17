 #include <stdio.h>
 #include <stdlib.h>

typedef struct grafo Grafo;

 struct grafo{
     int Ponderado;
     int numVertices;
     int grauMax;
     int** arestas;
     float** pesos;
     int* grau;
 };

 Grafo *gr;

Grafo *criaGrafo(int numVertices, int grauMax, int Ponderado){
    
    Grafo *gr = (Grafo*)malloc(sizeof(struct grafo));
    if(gr != NULL){
        gr->numVertices = numVertices;
        gr->grauMax = grauMax;
        gr->Ponderado = (Ponderado != 0) ? 1: 0;
        gr->grau = (int**)calloc(numVertices, sizeof(int)); //calloc - para o vetor entrar zerado
        gr->arestas = (int**)malloc(numVertices*sizeof(int*));

        for(int i = 0; i < numVertices; i++)
            gr->arestas[i] = (int*)malloc(grauMax*sizeof(int));
            if(gr->Ponderado){
                gr->pesos = (float**)malloc(numVertices*sizeof(float*));
                
                for(int i = 0; i < numVertices; i++)
                    gr->pesos[i] = (float*)malloc(grauMax*sizeof(float));
            }
    }
    return gr;
}

void liberaGrafo(Grafo *gr){
    if(gr != NULL){
        int i;
        for(i = 0; i < gr->numVertices; i++)
            free(gr->arestas[i]);
        free(gr->arestas);

        if(gr->Ponderado){
            for(i = 0; i < gr->numVertices; i++)
                free(gr->pesos[i]);
            free(gr->pesos);
        }

        free(gr->grau);
        free(gr);
    }
}

int inserirAresta(Grafo *gr, int origem, int destino, int digrafo, float peso){
    if(gr == NULL)
        return 0;
    if(origem < 0 || origem >= gr->numVertices)
        return 0;
    if(destino < 0 || destino >= gr->numVertices)
        return 0;
    
    gr->arestas[origem][gr->grau[origem]] = destino;
    if(gr->Ponderado)
        gr->pesos[origem][gr->grau[origem]] = peso;
    gr->grau[origem]++;

    if(digrafo == 0)
        inserirAresta(gr, destino, origem, 1, peso);
    return 1;
}

int removerAresta(Grafo* gr, int origem, int destino, int digrafo){
    if(gr == NULL) return 0;
    if(origem < 0 || origem >= gr->numVertices) return 0;
    if(destino < 0 || destino >= gr->numVertices) return 0;

    int i = 0;
    while(i < gr->grau[origem] && gr->arestas[origem][i] != destino)
        i++;
    if(i == gr->grau[origem]) // Elemento não encontrado
        return 0;
    gr->grau[origem]--;
    gr->arestas[origem][i] = gr->arestas[origem][gr->grau[origem]];
    if(gr->Ponderado)
        gr->pesos[origem][i] = gr->pesos[origem][gr->grau[origem]];
    if(digrafo == 0) // Se for digrafo
        removerAresta(gr, destino, origem, 1);
    return 1;
}

void buscaProfundidade(Grafo *gr, int verticeInicio, int *visitado, int cont){
    int i;
    visitado[verticeInicio] = cont;
    for(i = 0; i < gr->grau[verticeInicio]; i++){
        if(!visitado[gr->arestas[verticeInicio][i]])
            buscaProfundidade(gr, gr->arestas[verticeInicio][i], visitado, cont+1);
    }
}
void buscaProfundidade_Interface(Grafo *gr, int verticeInicio, int *visitado){
    int i, cont = 1;
    for(i = 0; i < gr->numVertices; i++)
        visitado[i] = 0;
    buscaProfundidade(gr, verticeInicio, visitado, cont);
}

void buscaLargura(Grafo *gr, int verticeInicio, int *visitado){
    int i, vert, NV, cont = 1, *fila, IF = 0, FF = 0;  // NV - número de vértices; IF e FF - início e final da fila
    for(i = 0; i < gr->numVertices; i++)
        visitado[i] = 0;
    NV = gr->numVertices;
    fila = (int*)malloc(NV*sizeof(int));
    FF++;
    fila[FF] = verticeInicio;
    visitado[verticeInicio] = cont;
    
    while(IF != FF){
        IF = (IF + 1) % NV;
        vert = fila[IF];
        cont++;
        for(i = 0; i < gr->grau[vert]; i++){
            if(!visitado[gr->arestas[vert][i]]){
                FF = (FF + 1) % NV; //  linhas 125 e 126 - pega o primeiro elemento da fila
                fila[FF] = gr->arestas[vert][i];
                visitado[gr->arestas[vert][i]] = cont;
            }
        }
    }
    free(fila);
}


int procuraMenorDistancia(float *dist, int *visitado, int NV){
    int i, menor = -1, primeiro = 1;
    for(i = 0; i < NV; i++){
        if(dist[i] >= 0 && visitado[i] == 0){
            if(primeiro){
                menor = i;
                primeiro = 0;
            } else{
                if(dist[menor] > dist[i]) menor = i;
            }
        }
    }
    return menor;
}
void buscaMenorCaminho(Grafo *gr, int verticeInicio, int *anterior, float *dist){ // Algoritimo de Dijkstra
    int i, cont, NV, ind, *visitado, u;

    cont = NV = gr->numVertices;
    visitado = (int*)malloc(NV*sizeof(int));
    for(i = 0; i < NV; i++){
        anterior[i] = -1;
        dist[i] = -1;
        visitado[i] = 0;
    }

    dist[verticeInicio] = 0;
    while(cont > 0){
        u = procuraMenorDistancia(dist, visitado, NV);
        if(u == -1)
            break;

        visitado[u] = 1;
        cont--;

        for(i = 0; i < gr->grau[u]; i++){
            ind = gr->arestas[u][i];
            if(dist[ind] < 0){
                dist[ind] = dist[u] + 1;
                //  ou peso da aresta
                //  dist[ind] = dist[u] + gr->pesos[u][i];
                anterior[ind] = u;
            } else{
                if(dist[ind] > dist[u] + 1){  //  ou peso da aresta
                    dist[ind] = dist[u] + 1;  //  if(dist[ind] > dist[u]+1)
                    //  ou peso da aresta
                    //  dist[ind] = dist[u] + gr->pesos[u][i];
                    anterior[ind] = u;
                }
            }
        }
    }
    free(visitado);
}

// Árvore Geradora Mínima (dispositivos integrados, redes de computadores, etc) - subgrafo com todos os vértices (V) originais
// com (V - 1) originais arestas
// -Encontra a menor estrutura em um grafo que conecta todos os vértices
// -Necessidades:
//      .Grafo conexo
//      .Grafo ponderado
//      .Grafo não direcionado
// -Formas de resolver:
//      .Estratégia Gulosa: constrói a árvore incrementalmente
//          *Algoritimo de Prim - Pior caso V: vértices, E: arestas - O(VE) -> Melhor caso (fila de prioridade) O(N^3)
//          *Algoritimo de Kruskal 
void algoritimoPrim(Grafo *gr, int orig, int *pai){
    int i, j, dest, primeiro, NV = gr->numVertices;
    double menorPeso;

    for(i = 0; i < NV; i++)
        pai[i] = -1;
    pai[orig] = orig;

    while (1){
        primeiro = 1;

        //  percorre todos os vértices
        for(i = 0; i < NV; i++){
            //  achou vértices já visitados
            if(pai[i] != -1){
                //  percorre os vizinhos do vértice visitado
                for(j = 0; j < gr->grau[i]; j++){
                    //  procura menor peso
                    //  achou vértice vizinho não visitado
                    if(pai[gr->arestas[i][j]] == 1){
                        if(primeiro){ //  procura aresta de menor custo
                            menorPeso = gr->pesos[i][j];
                            orig = i;
                            dest = gr->arestas[i][j];
                            primeiro = 0;
                        } else{
                            if(menorPeso > gr->pesos[i][j]){
                                menorPeso = gr->pesos[i][j];
                                orig = i;
                                dest = gr->arestas[i][j];
                            }
                        }
                    }
                }
            }
        }
        if(primeiro == 1)
            break;

            pai[dest] = orig;
    }
    
}

 void main(){

    Grafo *gr;
    gr = criaGrafo(10, 7, 0);
    inserirAresta(gr, 0, 1, 0, 0);
    inserirAresta(gr, 1, 3, 0, 0);
    removerAresta(gr, 0, 1, 0);

    int vis[10]; // Vetor para busca em profundidade - mesmo número de vértices
    buscaProfundidade_Interface(gr, 0, vis);
    buscaLargura(gr, 0, vis);

    //Vetor para buscar por menor caminho
    int ant[5];
    float dist[5];
    buscaMenorCaminho(gr, 0, ant, dist);

    //Algoritimo de Prim - Grafo Estrela - Rede estrela com um hexágono regular circulando-a
    // int i, pai[6];
    // algoritimoPrim(gr, 0, pai);
    // for(i = 0; i < 6; i++)
    //    printf("%d: %d\n", pai[i], i);
    
    liberaGrafo(gr);
 }