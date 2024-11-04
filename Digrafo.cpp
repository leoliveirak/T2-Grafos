/*
 * Tarefa 02 - Alteracoes de Transito
 *
 * GEN254 - Digrafos - 2024/2
 *
 * Nome:      Leonardo de Oliveira Klitzke
 * Matricula: 2311100019
 * Nome:      Gustavo Botezini
 * Matricula: 2311100062
 */

#include "Digrafo.h"
#include "Aresta.h"
#include <iostream>

using namespace std;

Digrafo::Digrafo(int num_vertices){
    if (num_vertices <= 0){
        throw(invalid_argument("Erro na construcao do Digrafo, o numero de vertices eh invalido"));
    }
    num_vertices_ = num_vertices;
    num_arestas_ = 0;

    lista_adj_.resize(num_vertices_);
}

void Digrafo::insere_aresta(Aresta e, int d){
    if (!existe_aresta(e) && e.v1 != e.v2 && d == 2){
        lista_adj_ [e.v1].push_back(e.v2);
        lista_adj_ [e.v2].push_back(e.v1);
        num_arestas_++;
    }
    else if (!existe_aresta(e) && e.v1 != e.v2 && d == 1){
        lista_adj_ [e.v1].push_back(e.v2);
    }
}

bool Digrafo::existe_aresta(Aresta e){
    for (int adj : lista_adj_ [e.v1]){
        if (adj == e.v2){
            return true;
        }
    }
    for (int adj : lista_adj_ [e.v2]){
        if (adj == e.v1){
            return true;
        }
    }
    return false;
}

int Digrafo::num_arestas(){ return num_arestas_; }

void Digrafo::imprime_digrafo(){
    for (int i = 0; i < num_vertices_; i++){
        cout << i << ": ";
        for (int j = 0; j < num_vertices_; j++){
            if (existe_aresta(Aresta(i, j))){
                cout << j << " ";
            }
        }
        cout << endl;
    }
}

void Digrafo::componentes_fortemente_conexas(){
    std::stack<int> pilha;
    std::vector<bool> visitado(num_vertices_, false);

    for (int i = 0; i < num_vertices_; i++){
        if (!visitado [i]){
            busca_profundidade_original(i, pilha, visitado);
        }
    }
    Digrafo invertido = digrafo_invetido();
    std::stack<int> pilhai;
    std::vector<bool> visitadoi(num_vertices_, false);
    while (!pilhai.empty())
    //continuar
    
}


/*
1. Faça i = 0
2. Enquanto houver vértices não visitados no digrafo G:
3. Realize uma busca em profundidade no digrafo G começando por um vértice não
visitado; quando um vértice v e seus vizinhos de saída tiverem sido visitados, faça fin(v)
= i e i = i + 1
4. Construa o digrafo G’ dado pelo digrafo G com as direções das arestas de G invertidas
5. Enquanto houver vértices não visitados no digrafo G’:
6. Realize uma busca em profundidade no digrafo G’ começando por um vértice não
visitado v para o qual fin(v) seja máximo
*/

