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

#include "../../Clases/TiposAlgoritmos/AlgoritmoFuerzaBruta.h"

AlgoritmoFuerzaBruta::AlgoritmoFuerzaBruta(Grafo grafo) : Algoritmos(grafo) {}

std::vector<std::string> AlgoritmoFuerzaBruta::resolver(std::string nodo_inicio) {
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
      return mejorRuta; // Si está cancelado, terminamos
    }
  } while (std::next_permutation(ciudades_unicas.begin(), ciudades_unicas.end()));
  mejorRuta.push_back(mejorRuta[0]);
  return mejorRuta;
}




int AlgoritmoFuerzaBruta::calcularDistancia(const std::vector<std::string>& ruta) {
  std::multimap<std::string, std::map<std::string, int>> grafo = getGrafo();
  int distanciaTotal = 0;

  for (size_t i = 0; i < ruta.size() - 1; ++i) {
    std::string ciudadActual = ruta[i];
    std::string ciudadSiguiente = ruta[i + 1];

    // Verificar si la ciudad actual está en el grafo
    auto itActual = grafo.equal_range(ciudadActual);
    if (itActual.first == grafo.end()) {
      std::cerr << "Error: La ciudad " << ciudadActual << " no existe en el grafo." << std::endl;
      return -1; // Valor de error
    }

    bool conexionEncontrada = false;
    // Iterar sobre todas las conexiones de la ciudad actual
    for (auto it = itActual.first; it != itActual.second; ++it) {
      // Verificar si la ciudad siguiente está conectada
      if (it->second.find(ciudadSiguiente) != it->second.end()) {
        distanciaTotal += it->second[ciudadSiguiente];
        conexionEncontrada = true;
        break;
      }
    }

    if (!conexionEncontrada) {
      std::cerr << "Error: No hay una conexión directa de " << ciudadActual << " a " << ciudadSiguiente << std::endl;
      return -1; // Valor de error
    }
  }

  return distanciaTotal;
}
