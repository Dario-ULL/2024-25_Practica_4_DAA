/**
 * @file AlgoritmoVorazMedio.cpp
 * @brief Implementación del algoritmo voraz para la resolución de problemas en grafos.
 * 
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Asignatura: Diseño y Análisis de Complejidad
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    18/03/2024
 * 
 * @details Esta implementación utiliza un enfoque voraz para recorrer un grafo,
 *          seleccionando en cada paso el nodo con la menor distancia aún no visitado.
 *          Si el recorrido no logra cubrir todos los nodos, se indica que no hay solución.
 */

#include "../../Clases/TiposAlgoritmos/AlgoritmoVorazMedio.h"

/**
* @brief Constructor de la clase AlgoritmoVorazMedio.
* @param grafo Grafo sobre el que se aplicará el algoritmo voraz.
*/
AlgoritmoVorazMedio::AlgoritmoVorazMedio(Grafo grafo) : Algoritmos(grafo) {}

/**
* @brief Resuelve el problema utilizando un algoritmo voraz.
* @param nodo_inicio Nodo desde el cual iniciar el recorrido.
* @return Devuelve un vector con la ruta encontrada, o vacío si no se encuentra solución.
*/
std::vector<std::string>
AlgoritmoVorazMedio::resolver(std::string nodo_inicio) {
  std::set<std::string> visitados;
  std::vector<std::string> ruta;
  std::multimap<std::string, std::map<std::string, int>> grafo = getGrafo();
  size_t tamano_grafo = getTamanoGrafo();
  std::string nodo_actual = nodo_inicio;

  visitados.insert(nodo_actual);
  ruta.push_back(nodo_actual);
  while (visitados.size() < tamano_grafo) {
    std::string siguiente_nodo = "\0";
    auto rango = grafo.equal_range(nodo_actual);
    std::map<int, std::string> buscarMedio;
    for (auto it = rango.first; it != rango.second; ++it) {
      std::string vecino_actual = it->second.begin()->first;
      int distancia = it->second.begin()->second;
      if (visitados.find(vecino_actual) == visitados.end()) {
        buscarMedio.insert({distancia, vecino_actual});
      }
    }
    size_t mitad = 0;
    for (std::map<int,std::string>::iterator it=buscarMedio.begin(); it!=buscarMedio.end(); ++it) {
      if (mitad >= buscarMedio.size()/2) {
        siguiente_nodo = it->second;
        break;
      }
      mitad++;
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
