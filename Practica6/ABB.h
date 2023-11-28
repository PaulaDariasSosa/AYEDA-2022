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
#include "AB.h"

// Para implementar la clase ABB<Key> que respresenta el 
template<typename Key>
class ABB : public AB<Key> {
    public: 
        ABB() : AB<Key>() {}
        ~ABB() {}
        bool insertar(const Key& k);
            // Insertar nodo de izquierda a derecha
            // Usar los metodos privados
            // Antes de insertar tenemos que buscar y si no existe inserto
        virtual bool buscar(const Key& k) const; // buscar se desarrolla en AVL
    private:
        bool buscar_rama(NodoB<Key>* nodo, const Key&) const; // esto debe ser bool porque buscar es bool
        bool insertar_rama(NodoB<Key>*& nodo, const Key& k); // esto debe ser bool porque insertar es bool
};

template<class Key>
bool ABB<Key>::insertar(const Key &k) {
  if (this->get_raiz() == nullptr) {
    AB<Key>::raiz = new NodoB<Key>(k);
    return true;
  } else
    return insertar_rama( AB<Key>::raiz, k);
}

template<class Key>
bool ABB<Key>::insertar_rama(NodoB<Key>*& nodo, const Key& k) {
  if(buscar(k))
    return false;
  if (nodo == nullptr)
    nodo = new NodoB<Key>(k);
  else if (k < nodo->get_dato())
    insertar_rama(nodo->get_izq(), k);
  else
    insertar_rama(nodo->get_der(), k);
  return true;
}

template<class Key>
bool ABB<Key>::buscar_rama(NodoB<Key>* nodo, const Key& k) const {
  if (nodo == nullptr)
    return false;
  if (k == nodo->get_dato())
    return true;
  if (k < nodo->get_dato())
    return buscar_rama(nodo->get_izq(), k);
  return buscar_rama(nodo->get_der(), k);
}

template<class Key>
bool ABB<Key>::buscar(const Key &k) const {
  return buscar_rama(this->get_raiz(), k);
}
