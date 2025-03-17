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

#include "../Clases/Grafo.h"

Grafo::Grafo(std::pair<std::multimap<std::string, std::pair<std::string, int>>, int> datos) {
  std::multimap<std::string, std::pair<std::string, int>> grafo = datos.first;
  numNodos_ = datos.second;
  for (const auto& par : grafo) {
    grafo_.insert({par.first, {{par.second.first, par.second.second}}});
  }
}

Grafo::Grafo(const Grafo& otro) {
  grafo_ = otro.grafo_;
  numNodos_ = otro.numNodos_;
}

Grafo::~Grafo() {
  grafo_.clear();
}

void 
Grafo::mostrarGrafo() {
  if (grafo_.empty()) {
    std::cout << "El grafo está vacío." << std::endl;
    return;
  }

  for (const auto& par : grafo_) {
    std::cout << "Nodo: " << par.first << " -> ";
    
    if (par.second.empty()) {
      std::cout << "Sin vecinos";
    } else {
      for (const auto& vecino : par.second) {
        std::cout << "(" << vecino.first << ", Peso: " << vecino.second << ") ";
      }
    }

    std::cout << std::endl;
  }
}

void 
Grafo::mostrarVecinos(std::string nodo) {
  auto rango = grafo_.equal_range(nodo);
  if (rango.first == rango.second) {
    std::cerr << "Error: El nodo '" << nodo << "' no existe en el grafo." << std::endl;
    return;
  }

  std::cout << "Vecinos del nodo '" << nodo << "': ";
  for (auto it = rango.first; it != rango.second; ++it) {
    for (const auto& vecino : it->second) {
      std::cout << vecino.first << " ";  // Mostrar solo el vecino
    }
  }
  std::cout << std::endl;
}

void 
Grafo::mostrarVecinosPeso(std::string nodo) {
  auto rango = grafo_.equal_range(nodo);
  if (rango.first == rango.second) {
    std::cerr << "Error: El nodo '" << nodo << "' no existe en el grafo." << std::endl;
    return;
  }

  std::cout << "Vecinos del nodo '" << nodo << "' con pesos:" << std::endl;
  for (auto it = rango.first; it != rango.second; ++it) {
    for (const auto& vecino : it->second) {
      std::cout << "- " << vecino.first << " (Peso: " << vecino.second << ")" << std::endl;
    }
  }
}

void 
Grafo::mostrarVecinosPesoOrdenado(std::string nodo) {
  auto rango = grafo_.equal_range(nodo);
  if (rango.first == rango.second) {
    std::cerr << "Error: El nodo '" << nodo << "' no existe en el grafo." << std::endl;
    return;
  }

  std::multimap<int, std::string> vecinos_ordenados;
  for (auto it = rango.first; it != rango.second; ++it) {
    for (const auto& vecino : it->second) {
      vecinos_ordenados.insert({vecino.second, vecino.first});
    }
  }

  std::cout << "Vecinos del nodo '" << nodo << "' ordenados por peso:" << std::endl;
  for (const auto& vecino : vecinos_ordenados) {
    std::cout << "- " << vecino.second << " (Peso: " << vecino.first << ")" << std::endl;
  }
}

std::multimap<std::string, std::map<std::string, int>>
Grafo::getGrafo() {
  return grafo_;
}

int
Grafo::getNumNodos() {
  return numNodos_;
}

int 
Grafo::valorCamino(std::vector<std::string> camino) {
  int distanciaTotal = 0;

  for (size_t i = 0; i < camino.size() - 1; ++i) {
    std::string ciudadActual = camino[i];
    std::string ciudadSiguiente = camino[i + 1];

    // Verificar si la ciudad actual está en el grafo
    auto itActual = grafo_.equal_range(ciudadActual);
    if (itActual.first == grafo_.end()) {
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


Grafo& Grafo::operator=(const Grafo& otro) {
  if (this == &otro) {
    return *this;
  }
  grafo_ = otro.grafo_;
  numNodos_ = otro.numNodos_;
  return *this;
}