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

#ifndef GENERADORGRAFO_H
#define GENERADORGRAFO_H

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

class GeneradorGrafo {
 private:
  std::string nombre_directorio_;
 public:    
  GeneradorGrafo(std::string nombre_directorio);
  void generarGrafo(int n);
};

#endif