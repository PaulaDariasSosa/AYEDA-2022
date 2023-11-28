// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023

#ifndef _DISPERSION_FUNCTION_H_
#define _DISPERSION_FUNCTION_H_

template <class Key>
class DispersionFunction {
 public:
  DispersionFunction() {};
  virtual unsigned operator()(const Key& k) const = 0;
};

#endif 