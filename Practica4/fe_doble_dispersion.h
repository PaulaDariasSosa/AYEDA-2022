// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023

#ifndef fe_double_dispersion_H_
#define fe_double_dispersion_H_

#include "funcion_exploracion.h"
#include "funcion_dispersion.h"

template <class Key>
class feDoubleDispersion : public ExplorationFunction<Key> {
 public:
  feDoubleDispersion(DispersionFunction<Key>& fd) : fd_(fd) {}
  unsigned operator()(const Key& k, unsigned i) const { return i * fd_(k); }
 private:
  DispersionFunction<Key>& fd_; // Función de dispersión
};

#endif  