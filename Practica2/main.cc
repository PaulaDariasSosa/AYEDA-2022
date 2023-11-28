// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 2: Calculadora de números grandes en binario
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 25/02/2023
// Se comprime con: tar cfvz ~/Practica2.tgz ../Practica2/

//Librerias incluidas:
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
//Archivos incluidos:
#include "herramientas.h"
#include "board.h"
#include "calculadora.h"

int main(int argc, char* argv[]) {
  Usage(argc, argv); // llamamos a la funcion Usage para comprobar los parametros pasados
  const std::string kFileName1 = argv[1];
  const std::string kFileName2 = argv[2];
  std::string line;
  std::ifstream input_file(kFileName1, std::ios_base::in);
  getline(input_file, line); // extraemos primera linea del fichero
  std::istringstream iss(line);   // separamos por espacios
  std::string word;
  iss>>word; // Base
  iss>>word; // =
  iss>>word; // N(2, 8, 10, 16)
  int Base = stoi(word); // pasamos de string a entero
  switch(Base){ // segun la base operamos
    case(2): 
      Procesar<2> (kFileName1, kFileName2);
    break;
    case(8): 
      Procesar<8> (kFileName1, kFileName2);
    break;
    case(10): 
      Procesar<10> (kFileName1, kFileName2);
    break;
    case(16): 
      Procesar<16> (kFileName1, kFileName2);
    break;
  }
  return 0;
}

/**
 * @brief: Funcion para controlar el funcionamiento del programa
*/
void Usage (int argc, char* argv[]){
  if (argc == 2) {
    std::string parameter{argv[1]};
    if (parameter == "--help") {
      std::cout << kHelpText << std::endl;
      exit(EXIT_SUCCESS);
    } 
  } 
  if (argc != 3) {
    std::cout << argv[0] << ": Faltan parámetros para realizar la operación." << std::endl;
    std::cout << "Pruebe " << argv[0] << " --help para más información" << std::endl;
    exit(EXIT_SUCCESS);
  }
}

template <size_t Base>
void Procesar (std::string kFileName1, std::string kFileName2) {
  std::string line;
  std::ifstream input_file(kFileName1, std::ios_base::in);
  getline(input_file, line); // extraemos primera linea del fichero
  std::string titulo;
  std::string numero;
  Board<Base> tabla;
  while (getline(input_file, line)) {
    std::istringstream iss(line);
    std::string word;
    iss>>word;
    titulo = word;
    iss>>word; // este es el = o ? 
    if (word == "=") {
      iss>>word;
      numero = word;
      tabla.insert_or_assign(titulo, BigInt<Base> (numero));
    } else {
      if (word == "?") {
        line.erase(0,5);
        Calculadora<Base> aux;
        tabla.insert_or_assign(titulo, (aux.Calcular(line, tabla)));
      }
    }
  }
  std::string linea_base;
  std::ifstream input_file1(kFileName1, std::ios_base::in);
  getline(input_file1, linea_base);
  std::ofstream output_file;
  output_file.open(kFileName2, std::ofstream::out); //abrimos el fichero de salida
  output_file << linea_base << "\n";
  output_file << tabla;
}
