// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023

#ifndef Bloque_H_
#define Bloque_H_

#include <vector>

#include "secuencia.h"

template <class Key>
class Block : public Sequence<Key> {
 public:
  Block() {};
  Block(const int& block_size) : blockSize(block_size) {
    datos_.reserve(block_size);
  }
  bool Search(const Key& k) const {
    for (size_t i = 0; i < datos_.size(); ++i) {
      ++contador;
      if (datos_[i] == k) return true;
    }
    return false;
  }
  bool Insert(const Key& k) {
    if (!Search(k) && !IsFull()) {
      datos_.push_back(k);
      return true;
    }
    return false;
  }
  bool IsFull() const { return datos_.size() >= blockSize; }
  void Print() {
    for(auto const& k : datos_) std::cout << k << ' ';
  }

 private:
  std::vector<Key> datos_; // Vector de claves
  size_t blockSize; // Tamaño del vector
};

#endif  // Bloque_H_