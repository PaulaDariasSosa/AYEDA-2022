// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023

#ifndef _FD_MODULE_H_
#define _FD_MODULE_H_

#include "funcion_dispersion.h"

template <class Key>
class fdModule : public DispersionFunction<Key> {
 public:
  fdModule(const unsigned n) : tableSize(n) {}
  unsigned operator()(const Key& k) const { 
    return k % tableSize; 
  }
 private:
  unsigned tableSize; // Tamaño de la tabla
};

#endif  