// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 1: Representación de números grandes en notación posicional
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 12/02/2023
// Se comprime con: tar cfvz ~/Practica1.tgz ../Practica1/

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
    case(2):  {
      std::string titulo;
      std::string numero;
      Board<2> tabla;
      while (getline(input_file, line)) {
        std::istringstream iss(line);   //or use stringstream
        std::string word;
        iss>>word;
        titulo = word;
        iss>>word; // este es el =
        iss>>word;
        bool es_operacion = false;
        std::istringstream iss_aux(line);   //or use stringstream
        std::string word_aux;
        while (iss_aux>>word_aux) {
          if ((word_aux == "+")||(word_aux == "-")||(word_aux == "*")||(word_aux == "/")||(word_aux == "%")||(word_aux == "^")||(word_aux == "<")||(word_aux == "<=")||(word_aux == ">")||(word_aux == ">=")||(word_aux == "==")||(word_aux == "!=")||(word_aux == "AND")) {
            es_operacion = true;
            break;
          }
        }
        if (es_operacion == false) {
          numero = word;
          tabla.insert_or_assign(titulo, BigInt<2> (numero));
        } else {
          Calculadora<2> aux;
          tabla.insert_or_assign(titulo, BigInt<2> (aux.Calcular(line, tabla)));
        }
      }
      std::ofstream output_file;
      output_file.open(kFileName2, std::ofstream::out); //abrimos el fichero de salida
      output_file << tabla;
    }
    break;
    case(8):  {
      std::string titulo;
      std::string numero;
      Board<8> tabla;
      while (getline(input_file, line)) {
        std::istringstream iss(line);   //or use stringstream
        std::string word;
        iss>>word;
        titulo = word;
        iss>>word; // este es el =
        iss>>word;
        bool es_operacion = false;
        std::istringstream iss_aux(line);   //or use stringstream
        std::string word_aux;
        while (iss_aux>>word_aux) {
          if ((word_aux == "+")||(word_aux == "-")||(word_aux == "*")||(word_aux == "/")||(word_aux == "%")||(word_aux == "^")||(word_aux == "<")||(word_aux == "<=")||(word_aux == ">")||(word_aux == ">=")||(word_aux == "==")||(word_aux == "!=")) {
            es_operacion = true;
            break;
          }
        }
        if (es_operacion == false) {
          numero = word;
          tabla.insert_or_assign(titulo, BigInt<8> (numero));
        } else {
          Calculadora<8> aux;
          tabla.insert_or_assign(titulo, BigInt<8> (aux.Calcular(line, tabla)));
        }
      }
      std::ofstream output_file;
      output_file.open(kFileName2, std::ofstream::out); //abrimos el fichero de salida
      output_file << tabla;
    }
    break;
    case(10): {
      std::string titulo;
      std::string numero;
      Board<10> tabla;
      while (getline(input_file, line)) {
        std::istringstream iss(line);   //or use stringstream
        std::string word;
        iss>>word;
        titulo = word;
        iss>>word; // este es el =
        iss>>word;
        bool es_operacion = false;
        std::istringstream iss_aux(line);   //or use stringstream
        std::string word_aux;
        while (iss_aux>>word_aux) {
          if ((word_aux == "+")||(word_aux == "-")||(word_aux == "*")||(word_aux == "/")||(word_aux == "%")||(word_aux == "^")||(word_aux == "<")||(word_aux == "<=")||(word_aux == ">")||(word_aux == ">=")||(word_aux == "==")||(word_aux == "!=")) {
            es_operacion = true;
            break;
          }
        }
        if (es_operacion == false) {
          numero = word;
          tabla.insert_or_assign(titulo, BigInt<10> (numero));
        } else {
          Calculadora<10> aux;
          tabla.insert_or_assign(titulo, BigInt<10> (aux.Calcular(line, tabla)));
        }
      }
      std::ofstream output_file;
      output_file.open(kFileName2, std::ofstream::out); //abrimos el fichero de salida
      output_file << tabla;
    }
    break;
    case(16): {std::string titulo;
      std::string numero;
      Board<16> tabla;
      while (getline(input_file, line)) {
        std::istringstream iss(line);   //or use stringstream
        std::string word;
        iss>>word;
        titulo = word;
        iss>>word; // este es el =
        iss>>word;
        bool es_operacion = false;
        std::istringstream iss_aux(line);   //or use stringstream
        std::string word_aux;
        while (iss_aux>>word_aux) {
          if ((word_aux == "+")||(word_aux == "-")||(word_aux == "*")||(word_aux == "/")||(word_aux == "%")||(word_aux == "^")||(word_aux == "<")||(word_aux == "<=")||(word_aux == ">")||(word_aux == ">=")||(word_aux == "==")||(word_aux == "!=")) {
            es_operacion = true;
            break;
          }
        }
        if (es_operacion == false) {
          numero = word;
          tabla.insert_or_assign(titulo, BigInt<16> (numero));
        } else {
          Calculadora<16> aux;
          tabla.insert_or_assign(titulo, BigInt<16> (aux.Calcular(line, tabla)));
        }
      }
      std::ofstream output_file;
      output_file.open(kFileName2, std::ofstream::out); //abrimos el fichero de salida
      output_file << tabla;
    }
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

//¿Como leer el archivo?
// si tiene NN = nnnnnnnn; es una declaracion
// si tiene NN = operaciones; son operaciones
