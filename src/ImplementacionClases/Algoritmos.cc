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

/**
 * @brief Constructor por defecto de la clase Algoritmos.
 */
Algoritmos::Algoritmos() {}

/**
 * @brief Constructor que inicializa un objeto Algoritmos con un grafo dado.
 * @param grafo Objeto de la clase Grafo que se usará en los algoritmos.
 */
Algoritmos::Algoritmos(Grafo grafo) {
  grafo_ = grafo;
}

/**
 * @brief Obtiene el grafo almacenado en el objeto Algoritmos.
 * @return Multimap que representa el grafo con sus conexiones y pesos.
 */
std::multimap<std::string, std::map<std::string, int>>
Algoritmos::getGrafo() {
  return grafo_.getGrafo();
}

/**
 * @brief Obtiene el número de nodos en el grafo.
 * @return Entero que indica la cantidad de nodos en el grafo.
 */
int
Algoritmos::getTamanoGrafo() {
  return grafo_.getNumNodos();
}