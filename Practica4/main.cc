// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023
// Se comprime con: tar cfvz ~/Practica4.tgz ../Practica4/

#include <fstream>
#include <iostream>
#include "tabla_hash.h"
#include "fd_modulo.h"
#include "fd_pseudoaleatorio.h"
#include "fd_suma.h"
#include "fe_lineal.h"
#include "fe_cuadratica.h"
#include "fe_doble_dispersion.h"
#include "fe_redispersion.h"
#include "string"

typedef long key; // definimos key como un long

void CambiarANumeroPrimo(size_t& tabla_size) { // esta funcion calcula el siguiente numero primo, para el tamaño de la tabla
  if (tabla_size == 0 || tabla_size == 1) {
    CambiarANumeroPrimo(++tabla_size);
  }
  for (int i = 2; i <= tabla_size/2; ++i) {
    if (tabla_size % i == 0) {
      CambiarANumeroPrimo(++tabla_size);
      break;
    }
  }

}

int main(int argc, char* argv[]) {
  size_t tamano_de_tabla = 0;
  std::cout << "Introduzca el tamaño deseado de la tabla(este numero podra variar para ajustarlo a un numero primo): ";
  std::cin >> tamano_de_tabla; // este numero debe ser primo, ya que numero primo permite una exploracion mas completa.
  // cambiamos el tamaño de la tabla al primo mayor mas cercano
  CambiarANumeroPrimo(tamano_de_tabla);
  char funcion_dispersion;
  DispersionFunction<key>* fd; // se crea un objeto de la clase DispersionFunction, como es una clase abstracta, se crea un puntero
  std::cout << "Introduzca la función de dispersión a utilizar: " << std::endl;
  std::cout << "1.- Módulo" << std::endl;
  std::cout << "2.- Pseudoaleatoria" << std::endl;
  std::cout << "3.- Basada en la suma" << std::endl;
  std::cin >> funcion_dispersion;
  switch (funcion_dispersion) { // dependiendo de la opcion elegida, escogemos la funcion
    case '1':
      fd = new fdModule<key>(tamano_de_tabla); // usamos la promocion de tipos
      break;
    case '2':
      fd = new fdPseudoRandom<key>(tamano_de_tabla);
      break;
    case '3':
      fd = new fdSum<key>(tamano_de_tabla);
      break;
    default:
      std::cerr << "La función de dispersión seleccionada no es valida" << std::endl;
      return 1;
      break;
  }
  char opcion_dispersion, funcion_exploracion;
  size_t tamano_bloque = 0;
  ExplorationFunction<key>* fe = nullptr; // se crea un objeto de la clase ExplorationFunction, como es una clase abstracta, se crea un puntero
  std::cout << "Introduzca la técnica de dispersión a utilizar: " << std::endl; 
  std::cout << "1.- Abierta" << std::endl;
  std::cout << "2.- Cerrada" << std::endl;
  std::cin >> opcion_dispersion;
  if(opcion_dispersion == '2') { // Si se selecciona dispersion cerrada debera elegir la funcion de exploracion y el tamaño del bloque
    std::cout << "Introduzca el tamaño del bloque: ";
    std::cin >> tamano_bloque;
    std::cout << "Introduzca la función de exploración a utilizar: " << std::endl;
    std::cout << "1.- Lineal" << std::endl;
    std::cout << "2.- Cuadrática" << std::endl;
    std::cout << "3.- DobleDispersión" << std::endl;
    std::cout << "4.- Redispersión" << std::endl;
    std::cin >> funcion_exploracion;
    switch (funcion_exploracion) {
    case '1':
      fe = new feLineal<key>;
      break;
    case '2':
      fe = new feQuadratic<key>;
      break;
    case '3':
      fe = new feDoubleDispersion<key>(*fd);
      break;
    case '4':
      fe = new feRedispersion<key>;
      break;
    default:
      std::cerr << "La función de dispersión no es valida" << std::endl;
      return 1;
      break;
    }
  }
  HashTable<key> table(tamano_de_tabla, fd, fe, tamano_bloque);
  while (true) {
    std::cout << "Seleccione la operacion que desea utilizar" << std::endl;
    std::cout << "1. Buscar" << std::endl;
    std::cout << "2. Insertar" << std::endl;
    std::cout << "3. Salir" << std::endl;
    int opcion;
    std::cin >> opcion;
    key clave;
    switch (opcion) {
      case 3:
        std::cout << "El programa ha finalizado" << std::endl;
        table.PrintTable();
        return 0;
        break;
      case 1:
        std::cout << "Introduzca la clave a ser buscada: ";
        std::cin >> clave;
        if (table.Search(clave)) {
          std::cout << "La clave ha podido ser encontrada con éxito" << std::endl;
        } else {
          std::cout << "La clave no ha podido ser encontrada con éxito" << std::endl;
        }
        break;
      case 2:
        std::cout << "Introduzca la clave a ser insertada: ";
        std::cin >> clave;
        if (table.Insert(clave)) {
          std::cout << "La clave ha podido ser insertada con éxito" << std::endl;
        } else {
          std::cout << "La clave no ha podido ser insertada con éxito" << std::endl;
        }
      break;
      default:
        std::cout << "La opción seleccionada no es válida" << std::endl;
      break;
    }
    std::cout << std::endl;
    std::cout << "Numero de comparaciones: " << contador << std::endl;
  }
  return 0;
}
