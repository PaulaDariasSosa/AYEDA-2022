// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 3: Calculadora universal para números enteros grandes
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 06/03/2023
// Se comprime con: tar cfvz ~/Practica3.tgz ../Practica3/

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
#include "number.h"
#include "bigint.h"
#include "number_test.cc"
#include "bigintexcep.h"
int main(int argc, char* argv[]) {
  Usage(argc, argv); // llamamos a la funcion Usage para comprobar los parametros pasados
  const std::string kFileName1 = argv[1];
  const std::string kFileName2 = argv[2];
  Procesar(kFileName1, kFileName2);
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

void Procesar (std::string kFileName1, std::string kFileName2) {
  std::string line;
  std::ifstream input_file(kFileName1, std::ios_base::in);
  std::string titulo;
  int base;
  std::string numero;
  Board tabla;
  while (getline(input_file, line)) {
    std::istringstream iss(line);
    std::string word;
    iss>>word;
    titulo = word;
    iss>>word; // este es el = o ? 
    if (word == "=") {
      iss>>word;
      word.pop_back();
      base = stoi(word);
      iss>>word;
      numero = word;
      try {
        Number* aux2 = create(base, numero);
      } catch (BigIntBaseNotImplemented& exception2) {
        std::cerr << exception2.what() << std::endl;
        std::cerr << "File: " << exception2.getFile() << std::endl;
        std::cerr << "Function: " << exception2.getFuntion() << std::endl;
        std::cerr << "Message: " << exception2.getMsg() << std::endl;
      }
        catch (BigIntBadDigit& exception) {
        std::cerr << exception.what() << std::endl;
        std::cerr << "File: " << exception.getFile() << std::endl;
        std::cerr << "Function: " << exception.getFuntion() << std::endl;
        std::cerr << "Message: " << exception.getMsg() << std::endl;
      }
      
      Number* aux = create(base, numero);
      tabla.tabla_.insert_or_assign(titulo, aux);
    } else {
      if (word == "?") {
        Calculadora aux;
        line.erase(0,5);
        tabla.tabla_.insert_or_assign(titulo, (aux.Calcular(line, tabla)));
      }
    }
  }
  std::string linea_base;
  std::ifstream input_file1(kFileName1, std::ios_base::in);
  getline(input_file1, linea_base);
  std::ofstream output_file;
  output_file.open(kFileName2, std::ofstream::out); //abrimos el fichero de salida
  for (auto auxiliar : tabla.tabla_) {
    output_file << auxiliar.first << " = "; 
    auxiliar.second->write(output_file);
    output_file << "\n";
  }
}

