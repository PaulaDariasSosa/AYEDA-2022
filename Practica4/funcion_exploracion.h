// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023

#ifndef _EXPLORATION_FUNCTION_
#define _EXPLORATION_FUNCTION_

template <class Key>
class ExplorationFunction {
 public:
  ExplorationFunction() {};
  virtual unsigned operator()(const Key& k, unsigned i) const = 0;
};

#endif