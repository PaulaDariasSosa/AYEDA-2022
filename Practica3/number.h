// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 3: Calculadora universal para números enteros grandes
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 06/03/2023

//Librerias incluidas:
#include <vector>
#include <iostream>
#include <array>
#include <cmath>
// Controlador para la definicion
#ifndef Number_H_
#define Number_H_

class Number;
template <size_t Base>
class BigInt;
//template<>
class BigInt<2>;

class Number {
 public:
  virtual Number* add (const Number*) const = 0;
  virtual Number* subtract(const Number*) const = 0;
  virtual Number* multiply(const Number*) const = 0;
  virtual Number* divide(const Number*) const = 0;
  virtual Number* module(const Number*) const = 0;
  virtual Number* power(const Number*) const = 0;

  virtual std::ostream& write(std::ostream&) const = 0;
  virtual std::istream& read(std::istream&) = 0;
  friend std::ostream& operator<<(std::ostream&, const Number&);
  friend std::istream& operator>>(std::istream&, Number&);

  virtual operator BigInt<2>() const = 0;
  virtual operator BigInt<8>() const = 0;
  virtual operator BigInt<10>() const = 0;
  virtual operator BigInt<16>() const = 0;
 //private:
  static Number* create(size_t base, const std::string& s);
};

#endif