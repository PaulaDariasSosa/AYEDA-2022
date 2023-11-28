// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023

#ifndef _FE_LINEAL_
#define _FE_LINEAL_

#include "funcion_exploracion.h"

template <class Key>
class feLineal : public ExplorationFunction<Key> {
 public:
  feLineal() {};
  unsigned operator()(const Key& k, unsigned i) const { return i; }
};

#endif  