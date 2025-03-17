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
    // Variable para almacenar la solución parcial
    std::vector<std::string> solucionParcial;
    algoritmo->cancelado = false;
    // Ejecutar el algoritmo de manera asincrónica
    auto futuro = std::async(std::launch::async, [algoritmo, inicio, &solucionParcial]() {
        // Llamar al algoritmo en el hilo secundario

        try {
            solucionParcial = algoritmo->resolver(inicio);
        } catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    });
    // Esperar con límite de tiempo
    if (futuro.wait_for(std::chrono::seconds(limiteTiempoSegundos)) == std::future_status::timeout) {
        std::cout << "Ejecución cancelada debido a tiempo excedido." << std::endl;
        algoritmo->cancelado = true;  // Cancelar la ejecución
        // Aquí puedes manejar la cancelación, dependiendo de cómo lo tengas implementado en el algoritmo
    } else {
        std::cout << "Algoritmo completado en menos de " << limiteTiempoSegundos << " segundos." << std::endl;
    }

    // Recoger el resultado del futuro (esto asegura que el futuro se haya completado)
    futuro.get(); 

    return solucionParcial; // Devolvemos la solución parcial calculada hasta el momento
}


int main (int argc, char *argv[]) {
  std::string directorio;  // Si se proporciona un argumento, se usa como directorio
  if (argc > 1) {
    directorio = argv[1];
  } else {
    // Si no, se usa el directorio actual
    directorio = std::filesystem::current_path().string();
  }
  if (!std::filesystem::exists(directorio) || !std::filesystem::is_directory(directorio)) {
    std::cerr << "El directorio especificado no existe o no es valido.\n";
    return 1;
  }
  std::vector<std::string> ficheros = leerArchivosTxt(directorio);



  for (const std::string& fichero : ficheros) {
    std::cout << "Fichero: " << fichero << std::endl;
    LectorFichero lector(fichero);
    Grafo grafo(lector.getDatos());
    Algoritmos* algoritmo;
    algoritmo = new AlgoritmoVoraz(grafo);
    std::cout << "Solucion Algoritmo Voraz:" << std::endl;
    auto inicioTiempo = std::chrono::high_resolution_clock::now();
    std::vector<std::string> solucion = resolverConTiempo(algoritmo, "A", 5*60);
    auto finTiempo = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> tiempoTranscurrido = finTiempo - inicioTiempo;
    std::cout << "Tiempo transcurrido: " << tiempoTranscurrido.count() << " segundos" << std::endl;
    for (std::string nodo : solucion) {
      std::cout << nodo << " ";
    }

    std::cout << std::endl;
    std::cout << "Valor del camino: " << grafo.valorCamino(solucion) << std::endl  << std::endl;
    algoritmo = new AlgoritmoFuerzaBruta(grafo);
    std::cout << "Solucion Algoritmo Fuerza Bruta:" << std::endl;
    inicioTiempo = std::chrono::high_resolution_clock::now();
    solucion = resolverConTiempo(algoritmo, "A", 5*60);
    finTiempo = std::chrono::high_resolution_clock::now();
    tiempoTranscurrido = finTiempo - inicioTiempo;
    std::cout << "Tiempo transcurrido: " << tiempoTranscurrido.count() << " segundos" << std::endl;
    for (std::string nodo : solucion) {
      std::cout << nodo << " ";
    }  
    std::cout << std::endl;
    std::cout << "Valor del camino: " << grafo.valorCamino(solucion) << std::endl << std::endl;
    std::cout << "Solucion Algoritmo Programacion Dinamica:" << std::endl;
    algoritmo = new AlgoritmoProgramacionDinamica(grafo);
    inicioTiempo = std::chrono::high_resolution_clock::now();
    solucion = resolverConTiempo(algoritmo, "A", 5*60);
    finTiempo = std::chrono::high_resolution_clock::now();
    tiempoTranscurrido = finTiempo - inicioTiempo;
    std::cout << "Tiempo transcurrido: " << tiempoTranscurrido.count() << " segundos" << std::endl;
    for (std::string nodo : solucion) {
      std::cout << nodo << " ";
    }
    std::cout << std::endl;
    std::cout << "Valor del camino: " << grafo.valorCamino(solucion) << std::endl << std::endl;
  }


  return 0;
}