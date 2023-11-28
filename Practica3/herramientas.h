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

//Declaracion de la funcion Usage
void Usage (int argc, char* argv[]);
//
void Procesar (std::string kFileName1, std::string kFileName2);
//Declaracion del texto de ayuda
const std::string kHelpText = "El programa realina calculos a partir de un fichero en notacion polaca inversa y lo almacena en un fichero de salida. Necesita el nombre de los dos ficheros para la ejecucion";