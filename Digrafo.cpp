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

void Digrafo::componentes_fortemente_conexas() {
    stack<int> pilha;
    vector<bool> visitado(num_vertices_, false);

    // Realizar busca em profundidade no grafo original e empilhar vértices pela ordem de término
    for (int i = 0; i < num_vertices_; i++) {
        if (!visitado[i]) {
            Busca_Profundidade(i, pilha, visitado);
        }
    }

    // Criar o grafo invertido
    Digrafo invertido = digrafo_invertido();

    fill(visitado.begin(), visitado.end(), false);  // Resetar o vetor de visitados
    vector<vector<int>> componentes;
    vector<int> map_componentes(num_vertices_);
    
    // Executar busca em profundidade no grafo invertido para identificar as componentes
    while (!pilha.empty()) {
        int v = pilha.top();
        pilha.pop();
        if (!visitado[v]) {
            vector<int> componente;
            invertido.busca_profundidade_invertido(v, visitado, componente);
            int comp_index = componentes.size();
            for (int u : componente) {
                map_componentes[u] = comp_index;
            }
            componentes.push_back(componente);
        }
    }

    // Construir o grafo das componentes e calcular o grau de saída
    Digrafo grafo_componentes(componentes.size());
    vector<int> grau_saida(componentes.size(), 0);

    for (int i = 0; i < num_vertices_; i++) {
        for (int v : lista_adj_[i]) {
            int comp_origem = map_componentes[i];
            int comp_destino = map_componentes[v];
            // Incrementar o grau de saída se a aresta conecta componentes diferentes
            if (comp_origem != comp_destino) {
                Aresta nova_aresta(comp_origem, comp_destino);
                if (!grafo_componentes.existe_aresta(nova_aresta)) {
                    grafo_componentes.insere_aresta(nova_aresta, 1);
                    grau_saida[comp_origem]++;
                }
            }
        }
    }
    for (int i = 0; i < grau_saida.size(); i++) {
        cout << i << ": " << grau_saida[i] << " " << endl;
    }
}