/*
 * Tarefa 02 - Alteracoes de Transito
 *
 * GEN254 - Grafos - 2024/2
 *
 * Nome:      Leonardo de Oliveira Klitzke 🤓
 * Matricula: 2311100019
 * Nome:      Gustavo Botezini 🤠
 * Matricula: 2311100062
 */

#include "Digrafo.h"
#include "Aresta.h"
#include <iostream>
#include <vector>

using namespace std;

int main(){
  int P; // Número de pontos;
  int D; // Número de descritores;
  int X; // Vértice X;
  int Y; // Vértice Y;
  int S; // Direção.

//##############################//

  cin >> P >> D; // Valores de controle.
  Digrafo Novo_Digrafo = Digrafo(P); // Cria o digrafo com o tamanho certo.
  for (int i = 0; i < D; i++){
    cin >> X >> Y >> S; // Vértices e direção.
    Aresta Nova_Aresta = Aresta(X, Y); // Cria a aresta.
    Novo_Digrafo.insere_aresta(Nova_Aresta, S);// Adiciona a nova aresta ao digrafo.
  }
  Novo_Digrafo.componentes_fortemente_conexas(); // Exibe as componentes fortemente conexas.
}
