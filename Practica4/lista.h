#ifndef _LIST_H_
#define _LIST_H_

// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023

#include <vector>

#include "secuencia.h"


template <class Key>
class List : public Sequence<Key> {
 public:
  List() {};
  bool Search(const Key& k) const{
    for (size_t i = 0; i < data_.size(); ++i) {
      ++contador;
      if (data_[i] == k) return true;
    }
    return false;
  }
  bool Insert(const Key& k) {
    if (!Search(k)) {
      data_.push_back(k);
      return true;
    }
    return false;
  }
  bool IsFull() const { return false; }
  void Print() {
    for(auto const& k : data_) std::cout << k << ' ';
  }
 private:
  std::vector<Key> data_; // Vector de claves
};

#endif 