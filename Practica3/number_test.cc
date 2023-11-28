// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 3: Calculadora universal para números enteros grandes
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 06/03/2023

#include "number.h"
#include "bigint.h"

static Number* create(size_t base, const std::string& s) {
  std::string cadena = s;
    Number* ptr_number;
    switch(base) {
    case (2): {
      BigInt<2>* ptr_bigint = new BigInt<2> (cadena);
      ptr_number = ptr_bigint;
    }
    break;
    case (8) : {
      BigInt<8>* ptr_bigint = new BigInt<8> (cadena);
      ptr_number = ptr_bigint;
    }
    break;
    case (10) : {
      BigInt<10>* ptr_bigint = new BigInt<10> (cadena);
      ptr_number = ptr_bigint;
    }
    break;
    case (16) : {
      BigInt<16>* ptr_bigint = new BigInt<16> (cadena);
      ptr_number = ptr_bigint;
    }
    break;
    default: throw BigIntBaseNotImplemented();
  }
  return ptr_number;
}

std::ostream& operator<<(std::ostream& out, const Number& a) {
  BigInt<10> aux = a;
  out << aux;
  return out;
}

std::istream& operator>>(std::istream& in, Number& a) {
  a.read(in);
  return in;
}
