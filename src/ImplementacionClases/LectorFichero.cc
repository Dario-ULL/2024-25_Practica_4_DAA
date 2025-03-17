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

 #include "../Clases/LectorFichero.h"

 /**
  * @brief Constructor de la clase LectorFichero.
  * @param fichero_entrada Nombre del fichero de entrada.
  */
 LectorFichero::LectorFichero(std::string fichero_entrada) {
   fichero_entrada_ = fichero_entrada;
 }
 
 /**
  * @brief Destructor de la clase LectorFichero.
  */
 LectorFichero::~LectorFichero() {
   fichero_entrada_.clear();
 }
 
 /**
  * @brief Lee los datos desde un fichero y los almacena en una estructura multimap.
  * @return Un par que contiene un multimap con los datos leídos y el número de nodos.
  * @throws Termina la ejecución si hay errores en la lectura del fichero.
  */
 std::pair<std::multimap<std::string, std::pair<std::string, int>>, int> LectorFichero::getDatos() {
   std::multimap<std::string, std::pair<std::string, int>> datos;
   std::ifstream fichero(fichero_entrada_);
   if (!fichero.is_open()) {
     std::cerr << "Error al abrir el fichero de entrada." << std::endl;
     exit(1);
   }
   std::string origen, destino;
   int peso;
   int num_nodos;
   std::set<std::string> nodos_unicos; // Para almacenar los nodos únicos
   if (!(fichero >> num_nodos)) {
     std::cerr << "Error: No se pudo leer el número de nodos." << std::endl;
     exit(1);
   }
   while (fichero >> origen >> destino >> peso) {
     datos.insert({origen, {destino, peso}});
     datos.insert({destino, {origen, peso}});
     nodos_unicos.insert(origen);
     nodos_unicos.insert(destino);
   }
   fichero.close();
   if (static_cast<int>(nodos_unicos.size()) != num_nodos) {
     std::cerr << "Error: Se esperaban " << num_nodos << " nodos, pero se encontraron " 
               << nodos_unicos.size() << "." << std::endl;
     exit(1);
   }
 
   return {datos, num_nodos};
 }
 