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

#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

class Grafo {
 private:
  std::multimap<std::string, std::map<std::string, int>> grafo_;
  int numNodos_;
 public:    
  Grafo() = default;
  Grafo(std::pair<std::multimap<std::string, std::pair<std::string, int>>, int> datos);
  Grafo(const Grafo& otro);
  ~Grafo();
  void mostrarGrafo();
  void mostrarVecinos(std::string nodo);
  void mostrarVecinosPeso(std::string nodo);
  void mostrarVecinosPesoOrdenado(std::string nodo);
  std::multimap<std::string, std::map<std::string, int>> getGrafo();
  int getNumNodos();
  int valorCamino(std::vector<std::string> camino);
  Grafo& operator=(const Grafo& otro);
};

#endif