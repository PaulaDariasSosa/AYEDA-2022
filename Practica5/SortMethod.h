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

#include<vector>
#pragma once
template<class Key>
class SortMethod {
 protected:
  unsigned size_;
  std::vector<Key> seq_;
 public:
  SortMethod(std::vector<Key> data, unsigned tamano) : seq_(data), size_(tamano) {}
  virtual void Sort() = 0;
};