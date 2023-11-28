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

#pragma once
template<typename Key>
class NodoB {
    protected: 
        Key dato;
        NodoB<Key>* izdo;
        NodoB<Key>* dcho;
    public: 
        NodoB(const Key& k, NodoB<Key>* i = NULL, NodoB<Key>* d = NULL ) : dato(k), izdo(i), dcho(d) {}
        ~NodoB() {}
        Key get_dato() const { return dato;}
        NodoB<Key>* get_izq() const {return izdo;}
        NodoB<Key>*& get_izq() { return izdo;} // Este metodo es un getter/setter
        NodoB<Key>* get_der() const {return dcho;}
        NodoB<Key>*& get_der() { return dcho;} // Este metodo es un getter/setter
};
template<typename Key>
std::ostream& operator<<(std::ostream& os, const NodoB<Key>& nodo) {
    return os << nodo.get_dato();
}