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
#include <iostream>
#include <map>
//Archivos incluidos:
#include "bigint.h"
#include "number.h"
// Controlador para la definicion
#ifndef Board_H_
#define Board_H_

struct Board {
  std::map<std::string, Number*> tabla_; //atributo principal
};

#endif