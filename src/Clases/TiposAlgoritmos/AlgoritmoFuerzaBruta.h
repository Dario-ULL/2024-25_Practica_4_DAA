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

#ifndef ALGORITMOFUERZABRUTA_H
#define ALGORITMOFUERZABRUTA_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>
#include <set>

#include "../Grafo.h"
#include "../Algoritmos.h"

class AlgoritmoFuerzaBruta : public Algoritmos {
 protected:
 int calcularDistancia(const std::vector<std::string>& ruta);
 public:
  AlgoritmoFuerzaBruta(Grafo grafo);
  std::vector<std::string> resolver(std::string nodo_inicio);
};

#endif