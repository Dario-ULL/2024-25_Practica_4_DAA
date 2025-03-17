/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Diseño y Analisis de Complejidad
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    18/03/2024
 * @brief   Implementacion de algoritmos Dinamica.
 *          
*/

#ifndef ALGORITMOPROGRAMACIONDINAMICA_H
#define ALGORITMOPROGRAMACIONDINAMICA_H

#include <iostream>
#include <vector>
#include <climits>
#include <cstring>
#include <map>
#include <set>

#include "../Grafo.h"
#include "../Algoritmos.h"

class AlgoritmoProgramacionDinamica : public Algoritmos {
 protected:
  int tsp(int mask, int pos, const std::vector<std::string>& cities, const std::vector<std::vector<int>>& dist, std::vector<std::vector<int>>& dp, 
         std::vector<std::vector<int>>& next_city, int n);
  std::vector<int> reconstruirCamino(int n, const std::vector<std::vector<int>>& next_city);
  int getDistancia(std::string origen, std::string destino);
 public:
  AlgoritmoProgramacionDinamica(Grafo grafo);
  std::vector<std::string> resolver(std::string nodo_inicio);
};

#endif