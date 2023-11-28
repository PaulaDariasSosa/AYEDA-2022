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

int main() {
  BigInt<2> myUser ("011");
  std::cout << myUser << std::endl;
  size_t sizeOfMyUser = sizeof(myUser);
  std::cout << sizeOfMyUser << std::endl;
}