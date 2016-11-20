//
//  graph.c
//
//  Created by Lukas Ferreira Machado on 9/3/16.
//  Copyright © 2016 Lukas Ferreira Machado. All rights reserved.
//

#include "graph.h"

Graph cria_grafo (char * nome)
{
    Graph grafo;
    grafo = malloc(sizeof(struct graph));
    if (grafo == NULL)
        return NULL;

    char * temp = realloc(grafo->nome, strlen(nome) * sizeof(char));
    grafo->nome = temp;
    strcpy(grafo->nome , nome);
    grafo->vertices = malloc(sizeof(struct vertex));
    grafo->total_vertices = 0;

    return grafo;
}

char * retorna_nome_grafo(Graph g)
{
    if (g != NULL)
    {
        return g->nome;
    }
    return "null";
}

void matriz_free(float** matriz, int tamanho)
{
    if (sizeof(matriz) != 0)
    {
        int i;
        
        for(i = 0; i < tamanho; i++)
        {
            /*
             * Libera memória de cada vetor (coluna da matriz)
             */
            free(matriz[i]);
        }
        
        /*
         * Libera memória da matriz (vetor das linhas)
         */
        free(matriz);
        matriz = NULL;
        assert (matriz == NULL);
    }
}

void destroi_grafo(Graph g)
{
    if (g== NULL)
    {
        return;
    }
    if(sizeof(g) != 0  || g != NULL)
    {
        /*
         * Libera todos os componentes do vetor:
         * matriz de arestas
         * lista de vértices
         * nome do grafo
         * memória alocada para o grafo
         */
        matriz_free(g->arestas, g->total_vertices);
        g->arestas = NULL;
        free(g->vertices);
        g->vertices = NULL;
        free(g->nome);
        g->nome = NULL;
        g->total_vertices = 0;
        free(g);
        g = NULL;
        assert (g == NULL);
    }
}

int posicao_vertex(Graph g, int nome)
{
    if (sizeof(g) == 0 || g == NULL)
    {
        return -1;
    }
    
    int i;
    
    for (i = 0; i < g->total_vertices ; i++)
    {
        if(g->vertices[i].id == nome)
        {
            /*
             * Se encontrou o vértice procuradao, retorna a posição no vetor de vértices
             */
            return i;
        }
    }
    return -1;
}

bool adjacente(Graph g, int x, int y)
{
    int pos_x = posicao_vertex(g, x);
    int pos_y = posicao_vertex(g, y);
    
    if(pos_x == -1 || pos_y == -1)
    {
        return false;
    }
    
    /*
     * Se x e y foram encontrados, e o peso da aresta (x, y) > 0
     * retorna verdadeiro: a aresta existe
     * Senão retorna falso (aresta não encontrada)
     */
    if(g->arestas[pos_y][pos_x] > 0)
        return true;
    
    return false;
}

struct vertex * vizinhos(Graph g, int x)
{
    if (g == NULL)
    {
        puts("Grafo nulo");
        return NULL;
    }
    
    int pos_x = posicao_vertex(g, x);
    
    if (pos_x == -1)
    {
        return NULL;
    }

    struct vertex * vizinhos = NULL;
    int total = 0;
    
    int i;
    
    for (i = 0; i < g->total_vertices; i++)
    {
        if(g->arestas[i][pos_x] > 0)
        {
            /*
             * Se x foi encontrado (x está presente na lista de vértices):
             * busca os vizinhos: itera entre todos os vértices e verifica peso da aresta (i, x)
             * se peso da aresta > 0,  imprime me tela tal vértice e o adiciona na lista de retorno
             */
            vizinhos = realloc(vizinhos, (total + 1) * sizeof(struct vertex));
            vizinhos[total] = g->vertices[i];
            printf("Vertice %d -  valor: %f \n", g->vertices[i].id, g->vertices[i].valor);
            total++;
        }
        
    }
    assert (vizinhos != NULL);
    return vizinhos;
}

void adiciona_vertice(Graph g, int x)
{
    
    if (sizeof(g) == 0 || g == NULL)
    {
        return;
    }

    if (posicao_vertex(g, x) != -1)
    {
        return;
    }
    
    if(g->total_vertices > 0)
    {
        struct vertex * temp = realloc(g->vertices, (g->total_vertices + 1) * sizeof(struct vertex));
        g->vertices = temp;
    }
    
    g->vertices[g->total_vertices].id = x;
    g->vertices[g->total_vertices].valor = 0;

    g->total_vertices++;
  
    /*
     * Instancia as arestas com valor inicial zero
     * Realoca matriz de vértices - aumenta o nro de linhas e colunas em 1.
     */
    g->arestas = realoca_matriz(g->arestas, g->total_vertices);
}

float ** aloca_matriz(float ** matriz, int elements)
{
    int i;
    matriz = malloc(sizeof(float) * elements * elements);
    
    if(matriz != NULL)
    {
        /*
         * Aloca espaço para cada linha da matriz
         */
        
        for(i = 0; i < elements; i++)
        {
            /*
             * Aloca um vetor de vértices para cada linha
             */
            matriz[i] = malloc(sizeof(float) * elements);
            if(matriz[i] == NULL)
            {
                return NULL;
            }
        }
    }
    assert (matriz != NULL);
    return matriz;
}

float ** realoca_matriz(float ** matriz, int elements)
{
    
    if (sizeof(matriz) == 0)
    {
        return NULL;
    }

    /*
     * Copia a matriz de adjacências
     */
    float ** copia;
    copia = aloca_matriz(copia, (elements));
    int i, j;

    /*
     * Diminui 1 linha e 1 coluna na matriz, realocando as arestas se necessário
     */
    for (i = 0; i < elements; i++)
    {
        for (j = 0; j < elements; j++){
            if (i == elements - 1 || j == elements - 1)
            {
                copia[i][j] = 0;
            }else
            {
                copia[i][j] = matriz [i][j];
            }
        }
    }
    assert (copia != NULL);
    return copia;
}

void remove_vertice(Graph g, int x)
{
    int pos_x = posicao_vertex(g, x);
    
    if (pos_x == -1)
    {
        return;
    }
    
    /*
     * Copia a matriz de adjacências
     */
    float ** copia;
    copia = aloca_matriz(copia, (g->total_vertices - 1));
    int i, j, a, b;

    a = 0;
    
    /*
     * Copia a matriz de adjacências, removendo o vértice x
     */
    for (i = 0; i < g->total_vertices; i++)
    {
        if (i != pos_x)
        {
            b=0;
            for (j = 0; j < g->total_vertices; j++)
            {
                if (j != pos_x)
                {
                    copia[a][b] = g->arestas[i][j];
                    b++;
                }
            }
            a++;
        }
    }
    
    /*
     * Copia a lista de vértices
     */
    
    struct vertex *cp = malloc(sizeof(struct vertex)*(g->total_vertices-1));
    int pos = 0;
    
    for (i = 0; i < g->total_vertices; i++)
    {
        if (i != pos_x)
        {
            cp[pos] = g->vertices[i];
            pos++;
        }
    }
    
    /*
     * Seta a nova lista de vértices e a nova matriz para o grafo
     * Diminuiu o nro total de vértices
     */
    g->arestas = copia;
    g->vertices = cp;
    g->total_vertices--;
    
}

void adiciona_aresta(Graph g, int x, int y)
{
    int pos_x = posicao_vertex(g, x);
    int pos_y = posicao_vertex(g, y);
    
    if (pos_x == -1 || pos_y == -1)
    {
        return;
    }
    /*
     * Adicionar aresta: setar valor da aresa (y,x) = 1
     */
    g->arestas[pos_y][pos_x] = 1;
}

void remove_aresta(Graph g , int x, int y)
{
    int pos_x = posicao_vertex(g, x);
    int pos_y = posicao_vertex(g, y);
    
    if (pos_x == -1 || pos_y == -1 || g->arestas[pos_y][pos_x] == 0)
    {
        return;
    }
    
    /*
     * Faz peso da aresta (y,x) =0
     */
    g->arestas[pos_y][pos_x] = 0;
}

float retorna_valor_vertice(Graph g, int x)
{
    int pos_x = posicao_vertex(g, x);
    
    if (pos_x == -1)
    {
        return -1;
    }
    
    return g->vertices[pos_x].valor;
}

void muda_valor_vertice(Graph g, int x, int valor)
{
    int pos_x = posicao_vertex(g, x);
    if (pos_x == -1)
    {
        return;
    }
    g->vertices[pos_x].valor = valor;
}

float retorna_valor_aresta(Graph g, int x, int y)
{
    int pos_x = posicao_vertex(g, x);
    int pos_y = posicao_vertex(g, y);
    
    if (pos_x == -1 || pos_y == -1)
    {
        return -1;
    }
    /*
     * Vértice de x para y na representacao utilizada significa aresta (y, x)
     */
    return g->arestas[pos_y][pos_x];
}

void muda_valor_aresta(Graph g, int x, int y, int valor)
{
    int pos_x = posicao_vertex(g, x);
    int pos_y = posicao_vertex(g, y);
    
    if (pos_x == -1 || pos_y == -1 || g->arestas[pos_y][pos_x] == 0)
    {
        return;
    }
    
    g->arestas[pos_y][pos_x] = valor;
}

void print_graph(Graph g)
{
    if (sizeof(g) == 0 || g == NULL)
    {
        puts("Grafo nulo");
        return;
    }
    
    printf("Grafo %s :\n", g->nome);
    puts("Vertices: ");
    
    int i, j;
    
    for (i = 0; i < g->total_vertices; i++)
    {
        printf("Vertice %d -  valor: %f \n", g->vertices[i].id, g->vertices[i].valor);
    }
    
    puts("Matriz de Arestas: ");
    
    for (i = 0; i < g->total_vertices; i++)
    {
        for (j = 0; j < g->total_vertices; j++)
        {
            printf("%.2f  ", g->arestas[i][j]);
        }
        printf("\n");
    }
}
