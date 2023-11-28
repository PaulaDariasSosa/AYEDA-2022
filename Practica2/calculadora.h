// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 2: Calculadora de números grandes en binario
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 25/02/2023

//Librerias incluidas:
#include <stack>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
//Archivos incluidos:
#include "bigint.h"
// Controlador para la definicion
#ifndef Calculadora_H_
#define Calculadora_H_

template<size_t Base>
class Calculadora {
 public:
  // constructor
  Calculadora() {};
  BigInt<2> Calcular(std::string line, Board<Base> tabla) {
    std::istringstream iss(line);
    std::string word;
    while (iss>>word) {
      if (word == "+") operate_("+", tabla);
      else if (word == "-") operate_("-", tabla);
      else if (word == "*") operate_("*", tabla);
      else if (word == "/") operate_("/", tabla);
      else if (word == "%") operate_("%", tabla);
      else if (word == "^") operate_("^", tabla);
      else if (word == "<") operate_("<", tabla);
      else if (word == "<=") operate_("<=", tabla);
      else if (word == ">") operate_(">", tabla);
      else if (word == ">=") operate_(">=", tabla);
      else if (word == "==") operate_("==", tabla);
      else if (word == "!=") operate_("!=", tabla);
      else {
        BigInt<Base> operando = tabla.find(word);
        stack_.push(operando);
      }
    }
    return (stack_.top());
  }
 private: 
  std::stack<BigInt<2>> stack_;
  void operate_(std::string operador, Board<Base> tabla) {
    if (operador == "-") {
      if (stack_.size() == 1) {
        BigInt<2> operador2 = stack_.top();
        stack_.pop();
        BigInt<2> aux;
        aux = -operador2;
        stack_.push(aux);
      } else {
        BigInt<2> operador2 = stack_.top();
        stack_.pop();
        BigInt<2> operador1 = stack_.top();
        stack_.pop();
        stack_.push(operador1 - operador2);
      }
    }
    if (operador != "-") {
      BigInt<2> operador2 = stack_.top();
      stack_.pop();
      BigInt<2> operador1 = stack_.top();
      stack_.pop();
      if (operador == "+") stack_.push(operador1 + operador2);
    else if (operador == "*") stack_.push(operador1 * operador2);
    else if (operador == "/") stack_.push(operador1 / operador2);
    else if (operador == "%") stack_.push(operador1 % operador2);
    else if (operador == "^") stack_.push(pow(operador1, operador2));
    else if (operador == "<") stack_.push(operador1 < operador2);
    else if (operador == "<=") stack_.push(operador1 <= operador2);
    else if (operador == ">") stack_.push(operador1 > operador2);
    else if (operador == ">=") stack_.push(operador1 >= operador2);
    else if (operador == "==") stack_.push(operador1 == operador2);
    else if (operador == "!=") stack_.push(operador1 != operador2); 
    }
  }
};


#endif