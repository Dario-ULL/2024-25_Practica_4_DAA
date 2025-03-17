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
#include "Clases/Algoritmos.h"
#include "Clases/TiposAlgoritmos/AlgoritmoVoraz.h"
#include "Clases/TiposAlgoritmos/AlgoritmoFuerzaBruta.h"
#include "Clases/TiposAlgoritmos/AlgoritmoProgramacionDinamica.h"

#include <iostream>
#include <string>
#include <map>
#include <filesystem>
#include <fstream>
#include <chrono>
#include <thread>
#include <atomic>
#include <stdexcept>
#include <future>

std::vector<std::string>
leerArchivosTxt(const std::string& directorio) {
  std::vector<std::string> ficheros;
  for (const auto& entry : std::filesystem::directory_iterator(directorio)) {
    if (entry.path().extension() == ".txt") {
      std::ifstream archivo(entry.path());
      if (archivo) {
        ficheros.push_back(entry.path());
      } else {
        std::cerr << "No se pudo abrir el archivo: " << entry.path() << "\n";
      }
    }
  }
  return ficheros;
}

std::vector<std::string> resolverConTiempo(Algoritmos* algoritmo, const std::string& inicio, int limiteTiempoSegundos) {
    std::vector<std::string> solucionParcial;
    algoritmo->cancelado = false;
    auto futuro = std::async(std::launch::async, [algoritmo, inicio, &solucionParcial]() {
      try {
        solucionParcial = algoritmo->resolver(inicio);
      } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
      }
    });
    if (futuro.wait_for(std::chrono::seconds(limiteTiempoSegundos)) == std::future_status::timeout) {
        algoritmo->cancelado = true;
    }
    futuro.get(); 
    return solucionParcial;
}

void imprimirTabla(const std::string& fichero, const std::vector<std::tuple<std::string, double, double>>& resultados) {
  const int ancho = 25;
  std::cout << "\nFichero: " << fichero << "\n";
  std::cout << std::setw(ancho) << "Algoritmo" << std::setw(ancho) << "Tiempo (s)" << std::setw(ancho) << "Valor del Camino" << "\n";
  std::cout << std::string(3 * ancho, '-') << "\n";
  
  for (const auto& [nombre, tiempo, valor] : resultados) {
    if (tiempo >= 300) {
      std::cout << std::setw(ancho) << nombre << std::setw(ancho) << "EXCESIVO" << std::setw(ancho) << valor << "\n";
    } else {
      std::cout << std::setw(ancho) << nombre << std::setw(ancho) << tiempo << std::setw(ancho) << valor << "\n";
    }
  }
  std::cout << std::endl;
}

int main (int argc, char *argv[]) {
  std::string directorio;
  if (argc > 1) {
    directorio = argv[1];
  } else {
    directorio = std::filesystem::current_path().string();
  }
  if (!std::filesystem::exists(directorio) || !std::filesystem::is_directory(directorio)) {
    std::cerr << "El directorio especificado no existe o no es valido.\n";
    return 1;
  }
  std::vector<std::string> ficheros = leerArchivosTxt(directorio);
  for (const std::string& fichero : ficheros) {
    std::vector<std::tuple<std::string, double, double>> resultados;
    LectorFichero lector(fichero);
    Grafo grafo(lector.getDatos());
    std::vector<std::string> algoritmos = {"Algoritmo Voraz", "Fuerza Bruta", "Prog. Dinámica"};
    std::vector<Algoritmos*> instancias = {new AlgoritmoVoraz(grafo), new AlgoritmoFuerzaBruta(grafo), new AlgoritmoProgramacionDinamica(grafo)};
    for (size_t i = 0; i < algoritmos.size(); i++) {
      auto inicioTiempo = std::chrono::high_resolution_clock::now();
      std::vector<std::string> solucion = resolverConTiempo(instancias[i], "A", 5 * 60);
      auto finTiempo = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> tiempoTranscurrido = finTiempo - inicioTiempo;
      double valorCamino = grafo.valorCamino(solucion);
      resultados.emplace_back(algoritmos[i], tiempoTranscurrido.count(), valorCamino);
    }
    imprimirTabla(fichero, resultados);
  }
  return 0;
}