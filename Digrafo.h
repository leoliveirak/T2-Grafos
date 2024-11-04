/*
 * Tarefa 02 - Alteracoes de Transito
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
#include <stack>

class Digrafo{
public:
    Digrafo(int num_vertices);
    int num_arestas();
    void insere_aresta(Aresta e, int d);
    bool existe_aresta(Aresta e);
    void imprime_digrafo();
    void busca_profundidade_original(int v, std::vector<bool> &visitado, std::stack<int> &pilha);
    void busca_profundidade_invertido(int v, std::vector<bool> &visitado, std::vector<int> &componente);
    void componentes_fortemente_conexas();
    Digrafo digrafo_invetido();

private:
    int num_vertices_;
    int num_arestas_;
    std::vector<std::list<int>> lista_adj_;
};

#endif /* DIGRAFO_H */