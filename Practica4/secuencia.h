// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023

#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

static int contador = 0;

template <class Key>
class Sequence {
 public:
  Sequence() {};
  virtual ~Sequence() {}
  virtual bool Search(const Key& k) const = 0;
  virtual bool Insert(const Key& k) = 0;
  virtual bool IsFull() const = 0;
  virtual void Print() = 0;
};

#endif 