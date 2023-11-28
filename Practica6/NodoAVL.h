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
#include <queue>
#include <tuple>
#include "NodoB.h"

template<typename Key>
class NodoAVL: public NodoB<Key> {
    private:
        int bal;
    public:
        NodoAVL(const Key& k, NodoB<Key>* i = NULL, NodoB<Key>* d = NULL, int balanceo = 0 ) : NodoB<Key>(k, i, d), bal(balanceo) {}
        ~NodoAVL() {}
        int& getbal(){ return bal;}
};