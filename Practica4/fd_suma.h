// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023

#ifndef _FD_SUM_H_
#define _FD_SUM_H_

#include "funcion_dispersion.h"

template <class Key>
class fdSum : public DispersionFunction<Key> {
 public:
  fdSum(const unsigned n) : tableSize(n) {}
  unsigned operator()(const Key& k) const {
    Key d = 0;
    Key x = k;
    while (x > 0) {
      Key y = x % 10;
      d += y;
      x /= 10;
    }
    return (d % tableSize);
  }

 private:
  unsigned tableSize; // Tamaño de la tabla
};

#endif  