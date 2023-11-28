// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023

#ifndef _FE_QUADRATIC_
#define _FE_QUADRATIC_

#include "funcion_exploracion.h"

template <class Key>
class feQuadratic : public ExplorationFunction<Key> {
 public:
  feQuadratic() {};
  unsigned operator()(const Key& k, unsigned i) const { return i * i; }
};

#endif  