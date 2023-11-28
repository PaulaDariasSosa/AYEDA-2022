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
  BigInt<Base> Calcular(std::string line, Board<Base> tabla) {
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
      else if (word == "AND") operate_("AND", tabla);
      else {
        BigInt<Base> operando = tabla.find(word);
        stack_.push(operando);
      }
    }
    return (stack_.top());
  }
 private: 
  std::stack<BigInt<Base>> stack_;
  void operate_(std::string operador, Board<Base> tabla) {
    if (operador == "-") {
      if (stack_.size() == 1) {
        BigInt<Base> operador2 = stack_.top();
        stack_.pop();
        BigInt<Base> aux;
        aux = -operador2;
        stack_.push(aux);
      } else {
        BigInt<Base> operador2 = stack_.top();
        stack_.pop();
        BigInt<Base> operador1 = stack_.top();
        stack_.pop();
        stack_.push(operador1 - operador2);
      }
    }
    if (operador != "-") {
      BigInt<Base> operador2 = stack_.top();
      stack_.pop();
      BigInt<Base> operador1 = stack_.top();
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
    else if (operador == "AND") {
      BigInt<Base> uno ("1");
      if ((operador1==uno) &&(operador2 == uno)) stack_.push("1");
      else stack_.push("0");
    } 
    }
  }  

};

#endif