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

#ifndef ALGORITMOS_H
#define ALGORITMOS_H

#include <iostream>
#include <map>
#include <vector>
#include <atomic>

#include "Grafo.h"

class grafo;

class Algoritmos {
 private:
  Grafo grafo_;
 public:
  Algoritmos();
  Algoritmos(Grafo grafo);
  std::multimap<std::string, std::map<std::string, int>> getGrafo();
  int getTamanoGrafo();
  virtual std::vector<std::string> resolver(std::string nodo_inicio) = 0;
  std::atomic<bool> cancelado{false};
};

#endif