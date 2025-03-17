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

#include "../../Clases/TiposAlgoritmos/AlgoritmoVoraz.h"

AlgoritmoVoraz::AlgoritmoVoraz(Grafo grafo) : Algoritmos(grafo) {}

std::vector<std::string>
AlgoritmoVoraz::resolver(std::string nodo_inicio) {
  std::set<std::string> visitados; 
  std::vector<std::string> ruta;    
  std::multimap<std::string, std::map<std::string, int>> grafo = getGrafo();
  size_t tamano_grafo = getTamanoGrafo();
  std::string nodo_actual = nodo_inicio;
  visitados.insert(nodo_actual); 
  ruta.push_back(nodo_actual);
  while (visitados.size() < tamano_grafo) {
    std::string siguiente_nodo = "\0";
    int min_distancia = std::numeric_limits<int>::max();
    auto rango = grafo.equal_range(nodo_actual);
    for (auto it = rango.first; it != rango.second; ++it) {
      std::string vecino_actual = it->second.begin()->first;
      int distancia = it->second.begin()->second;
      if (visitados.find(vecino_actual) == visitados.end() && distancia < min_distancia) {
        siguiente_nodo = vecino_actual;
        min_distancia = distancia;
      }
    }
    if (siguiente_nodo != "\0") {
      ruta.push_back(siguiente_nodo);
      visitados.insert(siguiente_nodo);
      nodo_actual = siguiente_nodo;
    } else {
      break;
    }
  }
  if (ruta.size() != tamano_grafo) {
    std::cerr << "No se ha podido encontrar una solución." << std::endl;
    ruta.clear();
    return ruta;
  }

  ruta.push_back(nodo_inicio);
  return ruta;
}

