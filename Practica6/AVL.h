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
#include "NodoAVL.h"

template<class Key>
class ArbolAVL: public ABB<Key> {
 public:
  ArbolAVL() : ABB<Key>() {};
  bool insertar(const Key& k);
 private:
  //bool buscar(const Key& k) const;

  void rotacion_II(NodoAVL<Key> *&nodo);
  void rotacion_DD(NodoAVL<Key> *&nodo);
  void rotacion_ID(NodoAVL<Key> *&nodo);
  void rotacion_DI(NodoAVL<Key> *&nodo);

  void inserta_bal(NodoAVL<Key> *&nodo, NodoAVL<Key> *nuevo, bool &crece);
  void insert_re_balancea_izqda(NodoAVL<Key> *&nodo, bool &crece);
  void insert_re_balancea_dcha(NodoAVL<Key> *&nodo, bool &crece);

  void inorden(NodoAVL<Key> *nodo);
  void Write();
};

template<class Key>
bool ArbolAVL<Key>::insertar(const Key& k) {
  if (ABB<Key>::buscar(k) == true) return false;
  auto *nuevo = new NodoAVL<Key>(k, 0);
  bool crece = false;
  inserta_bal(reinterpret_cast<NodoAVL<Key>*&>(AB<Key>::raiz), nuevo, crece);
  return true;
}


template<class Key>
void ArbolAVL<Key>::rotacion_II(NodoAVL<Key> *&nodo) {
  #ifdef TRAZA  
  std::cout << "Desbalanceo: " << std::endl;
  this->Write();
  std::cout << std::endl;
  std::cout << "Rotación II en [" << nodo->get_dato() << "]" << std::endl;
  #endif
  NodoAVL<Key>* nodo1 = reinterpret_cast<NodoAVL<Key>*&>(nodo->get_izq());
  nodo->get_izq() = reinterpret_cast<NodoAVL<Key>*&>(nodo1->get_der());
  nodo1->get_der() = nodo;
  if (nodo1->getbal() == 1) {
    nodo->getbal() = 0;
    nodo1->getbal() = 0;
  } else { // nodo1->bal == 0
    nodo->getbal() = 1;
    nodo1->getbal() = -1;
  }
  nodo = nodo1;
}

template<class Key>
void ArbolAVL<Key>::rotacion_DD(NodoAVL<Key> *&nodo) {
  #ifdef TRAZA  
  std::cout << "Desbalanceo: " << std::endl;
  this->Write();
  std::cout << std::endl;
  std::cout << "Rotación DD en [" << nodo->get_dato() << "]" << std::endl;
  #endif
  NodoAVL<Key>* nodo1 = reinterpret_cast<NodoAVL<Key>*&>(nodo->get_der());
  nodo->get_der() = nodo1->get_izq();
  nodo1->get_izq() = nodo;
  if (nodo1->getbal() == -1) {
    nodo->getbal() = 0;
    nodo1->getbal() = 0;
  } else { // nodo1->bal == 0
    nodo->getbal() = -1;
    nodo1->getbal() = 1;
  }
  nodo = nodo1;
}

template<class Key>
void ArbolAVL<Key>::rotacion_ID(NodoAVL<Key> *&nodo) {
  #ifdef TRAZA  
  std::cout << "Desbalanceo: " << std::endl;
  this->Write();
  std::cout << std::endl;
  std::cout << "Rotación ID en [" << nodo->get_dato() << "]" << std::endl;
  #endif
  NodoAVL<Key> *nodo1 = reinterpret_cast<NodoAVL<Key>*&>(nodo->get_izq());
  NodoAVL<Key> *nodo2 = reinterpret_cast<NodoAVL<Key>*&>(nodo1->get_der());
  nodo->get_izq() = nodo2->get_der();
  nodo2->get_der() = nodo;
  nodo1->get_der() = nodo2->get_izq();
  nodo2->get_izq() = nodo1;
  if (nodo2->getbal() == -1)
    nodo1->getbal() = 1;
  else nodo1->getbal() = 0;
  if (nodo2->getbal() == 1)
    nodo->getbal() = -1;
  else nodo->getbal() = 0;
  nodo2->getbal() = 0;
  nodo = nodo2;
}

template<class Key>
void ArbolAVL<Key>::rotacion_DI(NodoAVL<Key> *&nodo) {
  #ifdef TRAZA  
  std::cout << "Desbalanceo: " << std::endl;
  this->Write();
  std::cout << std::endl;
  std::cout << "Rotación DI en [" << nodo->get_dato() << "]" << std::endl;
  #endif
  NodoAVL<Key> *nodo1 = reinterpret_cast<NodoAVL<Key>*&>(nodo->get_der());
  NodoAVL<Key> *nodo2 = reinterpret_cast<NodoAVL<Key>*&>(nodo1->get_izq());
  nodo->get_der() = nodo2->get_izq();
  nodo2->get_izq() = nodo;
  nodo1->get_izq() = nodo2->get_der();
  nodo2->get_der() = nodo1;
  if (nodo2->getbal() == 1)
    nodo1->getbal() = -1;
  else nodo1->getbal() = 0;
  if (nodo2->getbal() == -1)
    nodo->getbal() = 1;
  else nodo->getbal() = 0;
  nodo2->getbal() = 0;
  nodo = nodo2;
}


template<class Key>
void ArbolAVL<Key>::inserta_bal(NodoAVL<Key> *&nodo, NodoAVL<Key> *nuevo, bool &crece) {
  if (nodo == nullptr) {
    nodo = nuevo;
    crece = true;
  } else if (nuevo->get_dato() < nodo->get_dato()) {
    inserta_bal(reinterpret_cast<NodoAVL<Key>*&>(nodo->get_izq()), nuevo, crece);
    if (crece) insert_re_balancea_izqda(nodo, crece);
  } else {
    inserta_bal(reinterpret_cast<NodoAVL<Key>*&>(nodo->get_der()), nuevo, crece);
    if (crece) insert_re_balancea_dcha(nodo, crece);
  }
}

template<class Key>
void ArbolAVL<Key>::insert_re_balancea_izqda(NodoAVL<Key> *&nodo, bool &crece) {
  switch (nodo->getbal()) {
    case -1: nodo->getbal() = 0;
      crece = false;
      break;
    case 0: nodo->getbal() = 1;
      break;
    case 1: NodoAVL<Key> *nodo1 = reinterpret_cast<NodoAVL<Key>*&>(nodo->get_izq());
      if (nodo1->getbal() == 1)
        rotacion_II(nodo);
      else rotacion_ID(nodo);
      crece = false;
  }
}

template<class Key>
void ArbolAVL<Key>::insert_re_balancea_dcha(NodoAVL<Key> *&nodo, bool &crece) {
  switch (nodo->getbal()) {
    case 1: nodo->getbal() = 0;
      crece = false;
      break;
    case 0: nodo->getbal() = -1;
      break;
    case -1: NodoAVL<Key> *nodo1 = reinterpret_cast<NodoAVL<Key>*&>(nodo->get_der());
      if (nodo1->getbal() == -1)
        rotacion_DD(nodo);
      else rotacion_DI(nodo);
      crece = false;
  }
}

template <class Key>
void ArbolAVL<Key>::Write() {
  NodoAVL<Key> *nodo = reinterpret_cast<NodoAVL<Key>*&>(AB<Key>::raiz);
  std::deque<std::pair<NodoAVL<Key> *, int>> Q;
  NodoAVL<Key> *aux;
  int nivel = 0, nivel_actual = 0;

  Q.push_back(std::pair<NodoAVL<Key> *, int>(nodo, 0));

  std::cout << "\nNivel 0: ";

  while (!Q.empty())
  {
    aux = (Q.front()).first;
    nivel = (Q.front()).second;
    Q.pop_front();

    if (nivel > nivel_actual)
    {
      nivel_actual = nivel;
      std::cout << "\nNivel " << nivel_actual << ": ";
    }
    if (aux == nullptr) std::cout << "[.]";
    else {
      std::cout << "[";
      std::cout << *aux;
      std::cout << "]";
    } 
    if (aux != nullptr)
    {
      Q.push_back(std::pair<NodoAVL<Key> *, int>(reinterpret_cast<NodoAVL<Key>*&>(aux->get_izq()), nivel + 1));
      Q.push_back(std::pair<NodoAVL<Key> *, int>(reinterpret_cast<NodoAVL<Key>*&>(aux->get_der()), nivel + 1));
    }
  }
}