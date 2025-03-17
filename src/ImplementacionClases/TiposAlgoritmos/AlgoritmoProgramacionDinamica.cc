/**
 * @file AlgoritmoProgramacionDinamica.cpp
 * @brief Implementación de un algoritmo basado en Programación Dinámica para resolver el problema del Viajante de Comercio.
 * 
 * Universidad de La Laguna
 * Escuela Superior de Ingeniería y Tecnología
 * Asignatura: Diseño y Análisis de Complejidad
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    18/03/2024
 * 
 * @details Esta implementación utiliza un enfoque de Programación Dinámica para encontrar la ruta óptima
 *          en un grafo, minimizando la distancia total recorrida en un problema del Viajante de Comercio (TSP).
 */

#include "../../Clases/TiposAlgoritmos/AlgoritmoProgramacionDinamica.h"

/**
* @brief Constructor de la clase AlgoritmoProgramacionDinamica.
* @param grafo Grafo sobre el que se aplicará el algoritmo.
*/
AlgoritmoProgramacionDinamica::AlgoritmoProgramacionDinamica(Grafo grafo) : Algoritmos(grafo) {}

/**
* @brief Resuelve el problema del Viajante de Comercio utilizando Programación Dinámica.
* @param nodo_inicio Nodo desde el cual iniciar el recorrido.
* @return Devuelve un vector con la ruta óptima encontrada, o vacío si no se encuentra solución.
*/
std::vector<std::string> 
AlgoritmoProgramacionDinamica::resolver(std::string nodo_inicio) {
  std::multimap<std::string, std::map<std::string, int>> grafo = getGrafo();
  size_t tamano_grafo = getTamanoGrafo();
  std::set<std::string> conjunto_ciudades;
  for (const auto& par : grafo) {
    conjunto_ciudades.insert(par.first);
    for (const auto& adyacente : par.second) {
      conjunto_ciudades.insert(adyacente.first);
    }
  }
  std::vector<std::string> ciudades(conjunto_ciudades.begin(), conjunto_ciudades.end());
  int cantidad_ciudades = ciudades.size();
  std::vector<std::vector<int>> matriz_distancias(cantidad_ciudades, std::vector<int>(cantidad_ciudades, INT_MAX));
  for (int i = 0; i < cantidad_ciudades; i++) {
    for (int j = 0; j < cantidad_ciudades; j++) {
      if (i == j) {
        matriz_distancias[i][j] = 0;
      } else {
        int distancia = getDistancia(ciudades[i], ciudades[j]);
        if (distancia != INT_MAX) {
          matriz_distancias[i][j] = distancia;
        }
      }
    }
  }
  std::vector<std::vector<int>> dp(1 << cantidad_ciudades, std::vector<int>(cantidad_ciudades, -1));
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
    return ruta;
  }
  if (ruta.size() != tamano_grafo + 1) {
    std::cerr << "No se ha podido encontrar una solución." << std::endl;
    ruta.clear();
    return ruta;
  }
  return ruta;
}

/**
* @brief Obtiene la distancia entre dos nodos del grafo.
* @param origen Nodo de origen.
* @param destino Nodo de destino.
* @return Distancia entre los nodos o INT_MAX si no existe conexión.
*/
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

/**
* @brief Implementación recursiva de la solución del TSP con Programación Dinámica.
* @param mascara Máscara de bits que indica las ciudades visitadas.
* @param posicion Ciudad actual en el recorrido.
* @param ciudades Vector con las ciudades.
* @param matriz_distancias Matriz con las distancias entre ciudades.
* @param dp Tabla de Programación Dinámica para memorización.
* @param siguiente_ciudad Tabla para reconstrucción del camino óptimo.
* @param cantidad_ciudades Número total de ciudades.
* @return Distancia mínima del recorrido óptimo.
*/
int 
AlgoritmoProgramacionDinamica::tsp(int mascara, int posicion, const std::vector<std::string>& ciudades, const std::vector<std::vector<int>>& matriz_distancias,
  std::vector<std::vector<int>>& dp, std::vector<std::vector<int>>& siguiente_ciudad, int cantidad_ciudades) {
  if (mascara == (1 << cantidad_ciudades) - 1) {
    return matriz_distancias[posicion][0]; 
  }
  if (dp[mascara][posicion] != -1) {
    return dp[mascara][posicion];
  }
  int mejor_distancia = INT_MAX;
  int mejor_ciudad = -1;
  
  for (int ciudad = 0; ciudad < cantidad_ciudades; ciudad++) {
    if ((mascara & (1 << ciudad)) == 0) {
      int nueva_distancia = matriz_distancias[posicion][ciudad] + tsp(mascara | (1 << ciudad), ciudad, ciudades, matriz_distancias, dp, siguiente_ciudad, cantidad_ciudades);
      if (nueva_distancia < mejor_distancia) {
        mejor_distancia = nueva_distancia;
        mejor_ciudad = ciudad;
      }
    }
    if (cancelado.load()) {
      return mejor_distancia;
    }
  }
  dp[mascara][posicion] = mejor_distancia;
  siguiente_ciudad[mascara][posicion] = mejor_ciudad;
  return mejor_distancia;
}

/**
 * @brief Reconstruye el camino óptimo obtenido tras la ejecución del algoritmo de Programación Dinámica.
 * @param cantidad_ciudades Número total de ciudades en el problema.
 * @param siguiente_ciudad Matriz que almacena las transiciones óptimas entre ciudades.
 * @return Devuelve un vector con la secuencia de ciudades en el orden óptimo.
 */
std::vector<int> 
AlgoritmoProgramacionDinamica::reconstruirCamino(int cantidad_ciudades, const std::vector<std::vector<int>>& siguiente_ciudad) {
  std::vector<int> camino;
  int ciudad_actual = 0;
  camino.push_back(ciudad_actual);
  int mascara = 1;
  while (mascara != (1 << cantidad_ciudades) - 1) {
    ciudad_actual = siguiente_ciudad[mascara][ciudad_actual];
    camino.push_back(ciudad_actual);
    mascara |= (1 << ciudad_actual);
    if (cancelado.load()) {
      return camino;
    }
  }  
  return camino;
}
