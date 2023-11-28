/** 
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Algoritmos y Estructuras de Datos Avanzados
* Curso: 2º
* Práctica 5: Implementación de métodos de ordenación
* Autor: Paula María Darias Sosa
* Correo: alu0101398594@ull.es
* Fecha: 17/04/2023
*/

#include <stdlib.h>
#include <string>
#include <iostream>
#include <vector>
#include "HeapSort.h"
#include "SortMethod.h"
#include "MergeSort.h"
#include "Insercion.h"
#include "algoritmos.h"
#include "ShellSort.h"
#include "RadixSort.h"
#include "algoritmos.h"

typedef long Key;

int main() {
  std::vector<Key> data;
  int size;
  int algoritmo;
  int opcion;
  std::cout << "Algoritmos a elegir:\n";
  std::cout << "1. Insercion\n";
  std::cout << "2. MergeSort\n";
  std::cout << "3. ShellSort\n";
  std::cout << "4. HeapSort\n";
  std::cout << "5. RadixSort\n";
  std::cout << "Introduzca una opción (entre el 1 y el 5): ";
  std::cin >> algoritmo;
  SortMethod<Key>* ordenacion;
  std::cout << "Introduzca el numero de elementos: ";
  std::cin >> size;
  // Random generator
  std::cout << "Quiere introducir los elementos : (0), o se seleccionan "
               "aleatoriamente: (1) ";
  std::cin >> opcion;
  switch (opcion) {
    case 0:
      std::cout << "Introduce " << size
                << " valores, intercalados por espacios\n";
      for (int i{0}; i < size; i++) {
        int valor;
        std::cin >> valor;
        data.push_back(valor);
      }
      break;
    case 1:
      std::cout << "Elementos seleccionados aleatoriamente\n\n";
      for (int i{0}; i < size; ++i) {
        int num;
        num = 1000 + rand() % (10000 - 1000);	
        data.push_back(num);
      }
      break;
  }
  switch (algoritmo) {
    case 1:
      ordenacion = new Insercion<Key>(data, size);
      break;
    case 2:
      ordenacion = new MergeSort<Key>(data, size);
      break;
    case 3:
      float alfa;
      std::cout << "Introduzca el valor de alfa (valor entre 0 y 1): ";
      std::cin >> alfa;
      ordenacion = new ShellSort<Key>(data, size, alfa);
      break;
    case 4:
      ordenacion = new HeapSort<Key>(data, size);
      break;
    case 5:
      ordenacion = new RadixSort<Key>(data, size);
      break;
    default:
      break;
  }
  // Ejecuto el algoritmo de odenar
  ordenacion->Sort();
  return 0;
}