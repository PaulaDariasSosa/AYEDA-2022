// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 6: Implementación del TDA Árbol
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 30/04/2023

#include <iostream>
#include "ABB.h"
#include "AVL.h"
// Al compilar hacemos un g++ -DTRAZA

#define TRAZA

typedef long Key;

int main() {
    #ifdef TRAZA   
        std::cout << "Modo traza..." << std::endl;
    #endif
    int tipo;
    std::cout << "Seleccione el tipo de árbol: " << std::endl;
    std::cout << "[1] Árbol binario de búsqueda " << std::endl;
    std::cout << "[2] Árbol binario de búsqueda balanceado " << std::endl;
    std::cin >> tipo;
    AB<Key>* arbol;
    if (tipo == 1) arbol = new ABB<Key>();
    else arbol = new ArbolAVL<Key>();
    // Menu opcion
  while (true) {
    std::cout << "Seleccione una opción: " << std::endl;
    std::cout << "[0] Salir " << std::endl;
    std::cout << "[1] Insertar clave " << std::endl;
    std::cout << "[2] Buscar clave " << std::endl;
    std::cout << "[3] Mostrar árbol inorden " << std::endl;
    std::cout << "[4] Mostrar altura " << std::endl;
    int opcion;
    std::cin >> opcion;
    int clave;
    switch (opcion) {
        case 1: 
            std::cout << "Introduce clave a insertar: ";
            std::cin >> clave;
            std::cout << std::endl;
            arbol->insertar(clave);
            std::cout << arbol << std::endl;
            break;
        case 2:
            std::cout << "Intro clave a buscar";
            std::cin >> clave;
            if(arbol->buscar(clave)) std::cout << "Clave encontrada" << std::endl;
            break;
        case 3:
            std::cout << "Recorrido inorden del arbol:" << std::endl;
            arbol->inorden(arbol->get_raiz());
            std::cout << std::endl;
            break;
        case 4:
            std::cout << "Altura del arbol:" << arbol->Alt() << std::endl;
            std::cout << std::endl;
            break;
        case 0: 
            std::cout << arbol << std::endl;
            return 0;
    }
  }
  
}