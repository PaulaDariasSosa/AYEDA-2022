// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023

#ifndef _FE_REDISPERSION_
#define _FE_REDISPERSION_

#include <cstdlib> // rand()

#include "funcion_exploracion.h"

template <class Key>
class feRedispersion : public ExplorationFunction<Key> {
 public:
  feRedispersion() {};
  unsigned operator()(const Key& k, unsigned i) const {
    srand(k);
    int aleatorio{0};
    for (unsigned j = 0; j < i ; ++j) {
      aleatorio = rand();
    }
    return aleatorio;
  }
};
#endif  