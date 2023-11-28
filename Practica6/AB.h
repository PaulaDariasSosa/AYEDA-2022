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
#include <stack>
#include "NodoB.h"

template<typename Key>
class AB {
    protected:
        NodoB<Key>* raiz;
    public: 
        AB(): raiz(NULL) {};
        virtual ~AB() { Podar(raiz); } // Porque los arboles ABB y AVL se destruyan de la misma forma
        NodoB<Key>* get_raiz() const {return raiz;}
        NodoB<Key>*& get_raiz() { return raiz;} // Este metodo es un getter/setter
        virtual bool insertar(const Key&) = 0;
        virtual bool buscar(const Key& ) const = 0;
        void inorden(NodoB<Key>* nodo) const;
        void postorden(NodoB<Key>* nodo) const;
        void preorden(NodoB<Key>* nodo) const;
        const int Alt() { return AltN(raiz); }
        const int AltN(NodoB<Key>* nodo);

    private: 
        void Podar(NodoB<Key>* nodo) {
          if (nodo == NULL) return ;
          Podar(nodo->get_izq()); // Podar subarbol izquierdo
          Podar(nodo->get_der()); // Podar subarbol derecho
          delete nodo;       // Eliminar nodo
          nodo = NULL;
        }
};

template<typename Key>
std::ostream& operator<<(std::ostream& os, const AB<Key>* arbol) {
  std::queue<std::pair<NodoB<Key>*, int>> aux_queue;
  std::pair<NodoB<Key>*, int> aux_pair{arbol->get_raiz(), 0};
  int current_level{0};
  std::cout << "Nivel 0: ";
  aux_queue.push(aux_pair);
  while (!aux_queue.empty()) {
    aux_pair = aux_queue.front();
    aux_queue.pop();
    if (aux_pair.second > current_level) {
      current_level = aux_pair.second;
      os << "\n";
      std::cout << "Nivel " << current_level << ": ";
    }
    if (aux_pair.first == nullptr) os << "[.]";
    else {
      os << "[" << aux_pair.first->get_dato() << "]";
      aux_queue.push(std::make_pair(aux_pair.first->get_izq(), aux_pair.second + 1));
      aux_queue.push(std::make_pair(aux_pair.first->get_der(), aux_pair.second + 1));
    }
  }
  return os;
}

template<typename Key>
void AB<Key>::inorden(NodoB<Key>* nodo) const {
  if (nodo == NULL) return;
  inorden(nodo->get_izq());
  std::cout << nodo->get_dato() << " ";
  inorden(nodo->get_der());
}

template<typename Key>
void AB<Key>::postorden(NodoB<Key>* nodo) const {
  if (nodo == NULL) return;
  preorden(nodo->get_izq());
  preorden(nodo->get_der());
  std::cout << nodo->get_dato() << " ";
  
}

template<typename Key>
void AB<Key>::preorden(NodoB<Key>* nodo) const {
  if (nodo == NULL) return;
  std::cout << nodo->get_dato() << " ";
  preorden(nodo->get_izq());
  preorden(nodo->get_der());
}
template<typename Key>
const int AB<Key>::AltN(NodoB<Key>* nodo) {
  if (nodo == NULL)
    return 0 ;
  int alt_i = AltN(nodo->get_izq());
  int alt_d = AltN(nodo->get_der());
  if (alt_d > alt_i) 
    return ++alt_d;
  else 
    return ++alt_i; 
}
