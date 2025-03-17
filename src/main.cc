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

#include "Clases/LectorFichero.h"
#include "Clases/Grafo.h"

#include <iostream>
#include <string>
#include <map>

void mostrarMultiMap(const std::multimap<char, std::pair<char, int>>& mmap) {
  for (const auto& par : mmap) {
      std::cout << "Clave: " << par.first 
                << ", Valor: (" << par.second.first 
                << ", " << par.second.second << ")" 
                << std::endl;
  }
}

int main (int argc, char *argv[]) {
  std::string fichero_entrada = "entrada.txt";
  LectorFichero lector(fichero_entrada);
  std::multimap<char, std::pair<char, int>> datos = lector.getDatos();
  mostrarMultiMap(datos);
  return 0;
}