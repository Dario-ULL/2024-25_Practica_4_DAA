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

#include "../Clases/GeneradorGrafo.h"

/**
 * @brief Constructor de la clase GeneradorGrafo.
 * @param nombre_directorio Nombre del directorio donde se encuentran los archivos de texto.
 */
GeneradorGrafo::GeneradorGrafo(std::string nombre_directorio) : nombre_directorio_(nombre_directorio) {}


/**
 * @brief Genera un grafo aleatorio con n nodos y lo guarda en un archivo de texto.
 * @param n Número de nodos del grafo.
 */
void
GeneradorGrafo::generarGrafo(int n) {
  std::string nombre_fichero = nombre_directorio_ + "/Generado_" + std::to_string(n) + "_nodos.txt";
  std::ofstream archivo(nombre_fichero);
  if (archivo) {
    archivo << n << "\n";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        if (i != j) {
          int peso = rand() % 100 + 1;
          archivo << i << " " << j << " " << peso << "\n";
        }
      }
    }
    archivo.close();
    std::cout << "Grafo de " << n << " nodos generado en " << nombre_fichero << "\n";
  } else {
    std::cerr << "No se pudo abrir el archivo: " << nombre_fichero << "\n";
  }
}