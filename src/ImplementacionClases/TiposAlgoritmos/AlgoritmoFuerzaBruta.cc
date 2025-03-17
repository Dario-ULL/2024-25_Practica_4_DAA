/**
 * @file AlgoritmoFuerzaBruta.cpp
 * @brief Implementación de un algoritmo de Fuerza Bruta para resolver el problema del Viajante de Comercio.
 * 
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Asignatura: Diseño y Análisis de Complejidad
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    18/03/2024
 * 
 * @details Este algoritmo prueba todas las posibles permutaciones de las ciudades para encontrar la ruta 
 *          de menor distancia en el problema del Viajante de Comercio (TSP).
 */

#include "../../Clases/TiposAlgoritmos/AlgoritmoFuerzaBruta.h"

/**
* @brief Constructor de la clase AlgoritmoFuerzaBruta.
* @param grafo Grafo sobre el que se aplicará el algoritmo.
*/
AlgoritmoFuerzaBruta::AlgoritmoFuerzaBruta(Grafo grafo) : Algoritmos(grafo) {}

/**
* @brief Resuelve el problema del Viajante de Comercio utilizando un enfoque de Fuerza Bruta.
* @param nodo_inicio Nodo desde el cual iniciar el recorrido.
* @return Devuelve un vector con la ruta de menor distancia encontrada.
*/
std::vector<std::string>
AlgoritmoFuerzaBruta::resolver(std::string nodo_inicio) {
  std::multimap<std::string, std::map<std::string, int>> grafo = getGrafo();
  std::set<std::string> ciudades;
  for (const auto& ciudad : grafo) {
    ciudades.insert(ciudad.first);
  }
  std::vector<std::string> ciudades_unicas(ciudades.begin(), ciudades.end());
  std::sort(ciudades_unicas.begin(), ciudades_unicas.end());
  int distanciaMinima = INT_MAX;
  std::vector<std::string> mejorRuta;
  do {
    int distancia = calcularDistancia(ciudades_unicas);
    if (distancia < distanciaMinima) {
      distanciaMinima = distancia;
      mejorRuta = ciudades_unicas;
    }
    if (cancelado.load()) {
      std::cout << "Algoritmo cancelado." << std::endl;
      return mejorRuta;
    }
  } while (std::next_permutation(ciudades_unicas.begin(), ciudades_unicas.end()));
  mejorRuta.push_back(mejorRuta[0]);
  return mejorRuta;
}

/**
* @brief Calcula la distancia total de una ruta dada.
* @param ruta Vector de ciudades en un orden específico.
* @return La distancia total del recorrido o -1 si hay ciudades sin conexión.
*/
int 
AlgoritmoFuerzaBruta::calcularDistancia(const std::vector<std::string>& ruta) {
  std::multimap<std::string, std::map<std::string, int>> grafo = getGrafo();
  int distanciaTotal = 0;
  for (size_t i = 0; i < ruta.size() - 1; ++i) {
    std::string ciudadActual = ruta[i];
    std::string ciudadSiguiente = ruta[i + 1];
    auto itActual = grafo.equal_range(ciudadActual);
    if (itActual.first == grafo.end()) {
      std::cerr << "Error: La ciudad " << ciudadActual << " no existe en el grafo." << std::endl;
      return -1;
    }
    bool conexionEncontrada = false;
    for (auto it = itActual.first; it != itActual.second; ++it) {
      if (it->second.find(ciudadSiguiente) != it->second.end()) {
        distanciaTotal += it->second[ciudadSiguiente];
        conexionEncontrada = true;
        break;
      }
    }
    if (!conexionEncontrada) {
      std::cerr << "Error: No hay una conexión directa de " << ciudadActual << " a " << ciudadSiguiente << std::endl;
      return -1;
    }
  }
  return distanciaTotal;
}
 