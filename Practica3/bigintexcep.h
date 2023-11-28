// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 3: Calculadora universal para números enteros grandes
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 06/03/2023

#include <iostream>
#include <exception>

#ifndef BIExcep_H_
#define BIExcep_H_

class BigIntException : public std::exception {
 public:
  BigIntException(const char* msg, const char* file, const char* function) : std::exception(), msg_(msg), file_(file), function_(function) {}
  const char* getMsg() const { return msg_; }
  const char* getFile() const { return file_; }
  const char* getFuntion() const { return function_; }
 private :
  const char* msg_;
  const char* file_;
  const char* function_;
};

class BigIntBadDigit : public BigIntException {
 public:
  BigIntBadDigit () : BigIntException {"Exception thrown by BigIntBadDigit", "BigInt.h", "En un constructor o en la operación de extracción de un flujo."} {}
};

class  BigIntDivisionByZero : public BigIntException {
 public:
  BigIntDivisionByZero () : BigIntException {"Exception thrown by  BigIntDivisionByZero. No es posible dividir entre 0", "BigInt.h", "Division"} {}
};

class  BigIntBaseNotImplemented : public BigIntException {
 public:
  BigIntBaseNotImplemented () : BigIntException {"Exception thrown by  BigIntBaseNotImplemented. Intento de crear un objeto BigInt<Base> con un valor de Base no implementado", "Number.h", "Constructor Number*"} {}
};

#endif
