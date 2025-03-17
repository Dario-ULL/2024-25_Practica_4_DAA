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


#ifndef LECTORFICHERO_H
#define LECTORFICHERO_H

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <set>

class LectorFichero {
 private:
  std::string fichero_entrada_;
 public:    
  LectorFichero(std::string fichero_entrada);
  ~LectorFichero();
  std::pair<std::multimap<std::string, std::pair<std::string, int>>, int> getDatos();
};

#endif