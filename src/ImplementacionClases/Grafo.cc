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

 /**
  * @brief Constructor de la clase Grafo.
  * @param datos Par que contiene el multimap de conexiones y el número de nodos.
  */
 Grafo::Grafo(std::pair<std::multimap<std::string, std::pair<std::string, int>>, int> datos) {
   std::multimap<std::string, std::pair<std::string, int>> grafo = datos.first;
   numNodos_ = datos.second;
   for (const auto& par : grafo) {
     grafo_.insert({par.first, {{par.second.first, par.second.second}}});
   }
 }
 
 /**
  * @brief Constructor de copia de la clase Grafo.
  * @param otro Objeto Grafo a copiar.
  */
 Grafo::Grafo(const Grafo& otro) {
   grafo_ = otro.grafo_;
   numNodos_ = otro.numNodos_;
 }
 
 /**
  * @brief Destructor de la clase Grafo.
  */
 Grafo::~Grafo() {
   grafo_.clear();
 }
 
 /**
  * @brief Muestra el contenido del grafo en consola.
  */
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
 
 /**
  * @brief Muestra los vecinos de un nodo específico.
  * @param nodo Nodo del cual se quieren ver los vecinos.
  */
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
       std::cout << vecino.first << " ";
     }
   }
   std::cout << std::endl;
 }
 
 /**
  * @brief Muestra los vecinos de un nodo con sus respectivos pesos.
  * @param nodo Nodo del cual se quieren ver los vecinos y sus pesos.
  */
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
 
 /**
  * @brief Muestra los vecinos de un nodo ordenados por peso ascendente.
  * @param nodo Nodo del cual se quieren ver los vecinos ordenados por peso.
  */
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
 
 /**
  * @brief Obtiene la representación del grafo.
  * @return Un multimap con los nodos y sus conexiones.
  */
 std::multimap<std::string, std::map<std::string, int>>
 Grafo::getGrafo() {
   return grafo_;
 }
 
 /**
  * @brief Obtiene el número de nodos del grafo.
  * @return Número de nodos.
  */
 int
 Grafo::getNumNodos() {
   return numNodos_;
 }
 
 /**
  * @brief Calcula la distancia total de un camino en el grafo.
  * @param camino Vector de strings representando el camino.
  * @return Distancia total del camino o -1 si el camino no es válido.
  */
 int 
 Grafo::valorCamino(std::vector<std::string> camino) {
   int distanciaTotal = 0;
   for (size_t i = 0; i < camino.size() - 1; ++i) {
     std::string ciudadActual = camino[i];
     std::string ciudadSiguiente = camino[i + 1];
     auto itActual = grafo_.equal_range(ciudadActual);
     if (itActual.first == grafo_.end()) {
       std::cerr << "Error: La ciudad " << ciudadActual << " no existe en el grafo." << std::endl;
       return -1; 
     }
     bool conexionEncontrada = false;
     for (auto it = itActual.first; it != itActual.second; ++it) {
       if (it->second.find(ciudadSiguiente) != it->second.end()) {
         distanciaTotal += it->second[ciudadSiguiente];
         conexionEncontrada = true;
         break;
       }
     }
     if (!conexionEncontrada) {
       std::cerr << "Error: No hay una conexión directa de " << ciudadActual << " a " << ciudadSiguiente << std::endl;
       return -1;
     }
   }
   return distanciaTotal;
 }
 
 /**
  * @brief Sobrecarga del operador de asignación para la clase Grafo.
  * @param otro Objeto Grafo a asignar.
  * @return Referencia al objeto Grafo modificado.
  */
 Grafo& Grafo::operator=(const Grafo& otro) {
   if (this == &otro) {
     return *this;
   }
   grafo_ = otro.grafo_;
   numNodos_ = otro.numNodos_;
   return *this;
 }
 