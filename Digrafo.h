/*
 * Tarefa 01 - Grafo - Listas de Adjacencia
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Leonardo de Oliveira Klitzke
 * Matricula: 2311100019
 * Nome:      Gustavo Botezini
 * Matricula: 2311100062
 */

#ifndef DIGRAFO_H
#define DIGRAFO_H

#include "Aresta.h"
#include <vector>
#include <list>

class Digrafo{
public:
    Digrafo(int num_vertices);
    int num_arestas();
    void insere_aresta(Aresta e, int d);
    bool existe_aresta(Aresta e);
    void imprime_digrafo();
private:
    int num_vertices_;
    int num_arestas_;
    std::vector<std::list<int>> lista_adj_;
};

#endif /* DIGRAFO_H */