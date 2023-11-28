// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 1: Representación de números grandes en notación posicional
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 12/02/2023

//Librerias incluidas:
#include <iostream>
#include <map>
//Archivos incluidos:
#include "bigint.h"
// Controlador para la definicion
#ifndef Board_H_
#define Board_H_

template <size_t Base>
class Board {
 public:
  Board() {}; // constructor por defecto
  void insert_or_assign(std::string& primero,const BigInt<Base>& segundo) {
    tabla_.insert_or_assign(primero, segundo);
  }
  BigInt<Base> find (std::string indice) {
    auto auxiliar = tabla_.find(indice);
    return (auxiliar->second);
  }
  friend std::ostream& operator<<(std::ostream& out, const Board<Base>& actual){
    for (auto aux : actual.tabla_) {
      out << aux.first << " = " << aux.second << "\n";
    }
    return out;
  }
 private:
  std::map<std::string, BigInt<Base>> tabla_; //atributo principal
};

#endif