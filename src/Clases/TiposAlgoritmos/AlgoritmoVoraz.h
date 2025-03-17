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

#ifndef ALGORITMOVORAZ_H
#define ALGORITMOVORAZ_H

#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <limits>
#include <algorithm>

#include "../Grafo.h"
#include "../Algoritmos.h"

class AlgoritmoVoraz : public Algoritmos {
 public:
  AlgoritmoVoraz(Grafo grafo);
  std::vector<std::string> resolver(std::string nodo_inicio);
};

#endif