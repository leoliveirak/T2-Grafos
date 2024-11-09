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
#include <vector>
#include <stack>

using namespace std;

Digrafo::Digrafo(int num_vertices){
    if (num_vertices <= 0){
        throw invalid_argument("Erro na construcao do Digrafo, o numero de vertices eh invalido");
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
        num_arestas_++;
    }
    else if (!existe_aresta(e) && e.v1 != e.v2 && d == 1){
        lista_adj_ [e.v1].push_back(e.v2);
        num_arestas_++;
    }
}

bool Digrafo::existe_aresta(Aresta e){
    for (int adj : lista_adj_ [e.v1]){
        if (adj == e.v2){
            return true;
        }
    }
    return false;
}

int Digrafo::num_arestas(){ return num_arestas_; }

void Digrafo::imprime_digrafo(){
    for (int i = 0; i < num_vertices_; i++){
        cout << i << ": ";
        for (int j : lista_adj_ [i]){
            cout << j << " ";
        }
        cout << endl;
    }
}

void Digrafo::Busca_Profundidade(int v, stack<int>& pilha, vector<bool>& visitado){
    visitado [v] = true; // recebe o vértice e marca como visitado;

    for (int u : lista_adj_ [v]){ // Executa o processo |d⁺(v)| vezes 
        if (!visitado [u]){ // percorre até achar um vértice não visitado;
            Busca_Profundidade(u, pilha, visitado); // Realiza o mesmo processo recursivamente.
        }
    }

    pilha.push(v); // Adiciona os elementos na pilha 
}

void Digrafo::busca_profundidade_invertido(int v, vector<bool>& visitado, vector<int>& componente){
    visitado [v] = true;
    componente.push_back(v);

    for (int u : lista_adj_ [v]){
        if (!visitado [u]){
            busca_profundidade_invertido(u, visitado, componente);
        }
    }
}

Digrafo Digrafo::digrafo_invertido(){
    Digrafo invertido(num_vertices_);

    for (int v = 0; v < num_vertices_; v++){
        for (int u : lista_adj_ [v]){
            invertido.lista_adj_ [u].push_back(v);
        }
    }

    return invertido;
}
//AINDA EM TESTES
void Digrafo::componentes_fortemente_conexas(){
    stack<int> pilha;
    vector<bool> visitado(num_vertices_, false);

    // Passo 1: Realizar DFS no grafo original e empilhar vértices pela ordem de término
    for (int i = 0; i < num_vertices_; i++){
        if (!visitado [i]){
            Busca_Profundidade(i, pilha, visitado);
        }
    }

    // Passo 2: Criar o grafo invertido
    Digrafo invertido = digrafo_invertido();

    // Passo 3: Realizar DFS no grafo invertido pela ordem dos vértices da pilha
    fill(visitado.begin(), visitado.end(), false);  // Resetar o vetor de visitados

    int componente_index = 0;
    vector<vector<int>> componentes;
    vector<int> map_componentes(num_vertices_);
    while (!pilha.empty()){
        int v = pilha.top();
        pilha.pop();

        if (!visitado [v]){
            vector<int> componente;
            invertido.busca_profundidade_invertido(v, visitado, componente);

            // Imprime a componente fortemente conexa encontrada
            cout << componente_index++ << ": ";
            int comp_index = componentes.size();
            for (int u : componente){
                cout << u << " ";
                map_componentes [u] = comp_index;
            }
            cout << endl;
            componentes.push_back(componente);
        }
    }

    //calcula o grau de saída de cada componente fortemente conexa
    vector<int> grau_saida(componentes.size(), 0);
    vector<bool> comp_visitada(componentes.size(), false);
    for (int i = 0; i < num_vertices_; i++){
        for (int v : lista_adj_ [i]){
            if (map_componentes [i] != map_componentes [v] && !comp_visitada [map_componentes [v]]){
                grau_saida [map_componentes [i]]++;
                comp_visitada [map_componentes [v]] = true;
            }
        }
        for(int v : lista_adj_[i]){
            visitado[map_componentes[v]] = false;
        }
    }

    for (int i = 0; i < componentes.size(); i++){
        cout << "Componente " << i << " (grau de saída: " << grau_saida [i] << "): ";
        for (int v : componentes [i]){
            cout << v << " ";
        }
        cout << endl;
    }
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

