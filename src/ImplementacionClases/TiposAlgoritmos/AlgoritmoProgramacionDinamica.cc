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

#include "../../Clases/TiposAlgoritmos/AlgoritmoProgramacionDinamica.h"

AlgoritmoProgramacionDinamica::AlgoritmoProgramacionDinamica(Grafo grafo) : Algoritmos(grafo) {}

std::vector<std::string> AlgoritmoProgramacionDinamica::resolver(std::string nodo_inicio) {
  std::multimap<std::string, std::map<std::string, int>> grafo = getGrafo();
  size_t tamano_grafo = getTamanoGrafo();
  std::set<std::string> conjunto_ciudades;
    for (const auto& par : grafo) {
        conjunto_ciudades.insert(par.first); // Añadir ciudad de origen
        for (const auto& adyacente : par.second) {
          conjunto_ciudades.insert(adyacente.first); // Añadir ciudad destino
        }
    }

    std::vector<std::string> ciudades(conjunto_ciudades.begin(), conjunto_ciudades.end());
    int cantidad_ciudades = ciudades.size();
    
    // Crear la matriz de distancias entre ciudades


    std::vector<std::vector<int>> matriz_distancias(cantidad_ciudades, std::vector<int>(cantidad_ciudades, INT_MAX));
    for (int i = 0; i < cantidad_ciudades; i++) {
      for (int j = 0; j < cantidad_ciudades; j++) {
        if (i == j) {
          matriz_distancias[i][j] = 0; // Distancia de una ciudad a sí misma es 0
        } else {
          int distancia = getDistancia(ciudades[i], ciudades[j]);
          if (distancia != INT_MAX) { // Si hay un camino, se asigna la distancia real
            matriz_distancias[i][j] = distancia;
          }
        }
      }
    }

    // Inicializar la tabla DP con -1
    std::vector<std::vector<int>> dp(1 << cantidad_ciudades, std::vector<int>(cantidad_ciudades, -1));
    // Inicializar la tabla de decisiones
    std::vector<std::vector<int>> proxima_ciudad(1 << cantidad_ciudades, std::vector<int>(cantidad_ciudades, -1));
    tsp(1, 0, ciudades, matriz_distancias, dp, proxima_ciudad, cantidad_ciudades);
    std::vector<int> camino = reconstruirCamino(cantidad_ciudades, proxima_ciudad);
    std::vector<std::string> ruta;
    for (size_t i = 0; i < camino.size(); i++) {
      ruta.push_back(ciudades[camino[i]]);
    }
    ruta.push_back(nodo_inicio);
    if (cancelado.load()) {
      std::cout << "Algoritmo cancelado." << std::endl;
      return ruta; // Si está cancelado, terminamos
    }
    if (ruta.size() != tamano_grafo + 1) {
      std::cerr << "No se ha podido encontrar una solución." << std::endl;
      ruta.clear();
      return ruta;
    }

    return ruta;
}

int 
AlgoritmoProgramacionDinamica::getDistancia(std::string origen, std::string destino) {
  std::multimap<std::string, std::map<std::string, int>> grafo = getGrafo();
  int distancia = INT_MAX;
  for (const auto& par : grafo) {
    if (!par.second.empty()) {
      for (const auto& vecino : par.second) {
        if (vecino.first == origen && par.first == destino) {
          distancia = vecino.second;
        }
      }
    }
  }
  return distancia;
}

int 
AlgoritmoProgramacionDinamica::tsp(int mascara, int posicion, const std::vector<std::string>& ciudades, const std::vector<std::vector<int>>& matriz_distancias,
  std::vector<std::vector<int>>& dp, std::vector<std::vector<int>>& siguiente_ciudad, int cantidad_ciudades) {
  if (mascara == (1 << cantidad_ciudades) - 1) {
    return matriz_distancias[posicion][0]; // Regresar a la ciudad inicial
  }
  if (dp[mascara][posicion] != -1) {
    return dp[mascara][posicion];
  }

  int mejor_distancia = INT_MAX;
  int mejor_ciudad = -1;

  // Probar todas las ciudades no visitadas
  for (int ciudad = 0; ciudad < cantidad_ciudades; ciudad++) {
    if ((mascara & (1 << ciudad)) == 0) { // Si la ciudad no ha sido visitada
        int nueva_distancia = matriz_distancias[posicion][ciudad] + tsp(mascara | (1 << ciudad), ciudad, ciudades, matriz_distancias, dp, siguiente_ciudad, cantidad_ciudades);
        if (nueva_distancia < mejor_distancia) {
            mejor_distancia = nueva_distancia;
            mejor_ciudad = ciudad;
        }
    }
    if (cancelado.load()) {
      return mejor_distancia; // Si está cancelado, terminamos
    }
  }

  dp[mascara][posicion] = mejor_distancia;
  siguiente_ciudad[mascara][posicion] = mejor_ciudad; // Guardamos la mejor ciudad para el próximo paso
  return mejor_distancia;
}

std::vector<int> 
AlgoritmoProgramacionDinamica::reconstruirCamino(int cantidad_ciudades, const std::vector<std::vector<int>>& siguiente_ciudad) {
  std::vector<int> camino;
  int ciudad_actual = 0; // Comenzamos en la ciudad 0

  camino.push_back(ciudad_actual);
  int mascara = 1;

  while (mascara != (1 << cantidad_ciudades) - 1) {
      ciudad_actual = siguiente_ciudad[mascara][ciudad_actual];
      camino.push_back(ciudad_actual);
      mascara |= (1 << ciudad_actual);
      if (cancelado.load()) {
        return camino; // Si está cancelado, terminamos
      }
  }  
  
  return camino;
}
