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

#include "../Clases/Algoritmos.h"

Algoritmos::Algoritmos() {}

Algoritmos::Algoritmos(Grafo grafo) {
  grafo_ = grafo;
}

std::multimap<std::string, std::map<std::string, int>>
Algoritmos::getGrafo() {
  return grafo_.getGrafo();
}

int
Algoritmos::getTamanoGrafo() {
  return grafo_.getNumNodos();
}