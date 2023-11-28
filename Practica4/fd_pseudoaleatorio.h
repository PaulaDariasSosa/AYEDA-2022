// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023

#ifndef _FD_PSEUDORANDOM_H_
#define _FD_PSEUDORANDOM_H_

#include <cstdlib>

#include "funcion_dispersion.h"

template <class Key>
class fdPseudoRandom : public DispersionFunction<Key> {
 public:
  fdPseudoRandom(const unsigned n) : tableSize(n) {}
  unsigned operator()(const Key& k) const {
    srand(k);
    return rand() % tableSize;
  }
 private:
  unsigned tableSize; // Tamaño de la tabla
};

#endif  