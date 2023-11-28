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
#include <stack>
#include <map>
#include <fstream>
#include <sstream>
#include <iostream>
//Archivos incluidos:
#include "bigint.h"
#include "board.h"
#include "number.h"
// Controlador para la definicion
#ifndef Calculadora_H_
#define Calculadora_H_

class Calculadora {
 public:
  // constructor
  Calculadora() {};
  Number* Calcular(std::string line, Board tabla) {
    std::istringstream iss(line);
    std::string word;
    while (iss>>word) {
      if (word == "+") operate_("+", tabla);
      else if (word == "-") operate_("-", tabla);
      else if (word == "*") operate_("*", tabla);
      else if (word == "/") operate_("/", tabla);
      else if (word == "%") operate_("%", tabla);
      else if (word == "^") operate_("^", tabla);
      else {
        Number* operando = tabla.tabla_.find(word)->second;
        stack_.push(operando);
      }
    }
    return (stack_.top());
  }
 private: 
  std::stack<Number*> stack_;
  void operate_(std::string operador, Board tabla) {
    Number* operador2 = stack_.top();
    stack_.pop();
    Number* operador1 = stack_.top();
    stack_.pop();
    if (operador == "+") stack_.push(operador1->add(operador2));
    else if (operador == "*") stack_.push(operador1->multiply(operador2));
    else if (operador == "/") stack_.push(operador1->divide(operador2));
    else if (operador == "%") stack_.push(operador1->module(operador2));
    else if (operador == "^") stack_.push(operador1->power(operador2));
    else if (operador == "-") stack_.push(operador1->subtract(operador2)); 
  }
};


#endif