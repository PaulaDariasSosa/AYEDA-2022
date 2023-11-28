// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 4: Búsqueda por dispersión
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 20/03/2023

#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <iostream>

#include "bloque.h"
#include "funcion_exploracion.h"
#include "funcion_dispersion.h"
#include "lista.h"
#include "secuencia.h"

template <class Key>
class HashTable {
 public:
  HashTable(size_t table_size, DispersionFunction<Key>* fd, ExplorationFunction<Key>* fe, size_t block_size) : tableSize(table_size), fd_(fd), fe_(fe), block_size_(block_size) {
    table_ = new Sequence<Key>*[table_size]; // creamos una secuencia (de List o Block) de tamaño table_size
    if (fe_ == nullptr) { // si la tabla es abierta
      for (size_t i = 0; i < table_size; ++i) { // en cada espacio de la secuencia insertamos un objeto
        table_[i] = new List<Key>(); // para cada elemento creamos un objeto List
      }
    } else { // si es cerrada
      for (size_t i = 0; i < table_size; ++i) { // en cada espacio de la secuencia insertamos un objeto
        table_[i] = new Block<Key>(block_size_); // para cada elemento creamos un objeto Block
      }
    }
  };
  ~HashTable() {
    for (size_t i = 0; i < tableSize; ++i) {
      delete table_[i];
    }
    delete table_;
  }
  bool Search(const Key& k) const {
    unsigned table_pos = (*fd_)(k); // adivina el movimiento
    if (fe_ != nullptr) { // si es cerrada
      for (size_t i = 0; i < tableSize; ++i) { // exploramos toda la tabla
        unsigned exploration_value = (*fe_)(k, i); // se averigua el valor
        if (table_[(table_pos + exploration_value) % tableSize]->Search(k)) return true; // el valor existe en la tabla, true
        if (!table_[table_pos]->IsFull()) return false; // si no esta llena y no lo encontro, false
      }
    }
    if (table_[table_pos]->Search(k)) return true; // si es cerrada simplemente deberia encontrarlo
    return false; // sino lo encontró, false
  }

  bool Insert(const Key& k) {
    contador = 0;
    unsigned table_pos = (*fd_)(k); // = funcion de distribucion (k) esto nos da su posicion en la tabla
    if (fe_ != nullptr) { // si es cerrada
      for (size_t i = 0; i < tableSize; ++i) { // exploramos toda la tabla
        unsigned exploration_value = (*fe_)(k, i); // = funcion de exploracion (k, i) esto nos da el patron de exploracion
        if (!table_[(table_pos + exploration_value) % tableSize]->Search(k) && !table_[(table_pos + exploration_value) % tableSize]->IsFull()) {// sino la clave no ha sido introducida y no esta llena
          table_[(table_pos + exploration_value) % tableSize]->Insert(k); // entonces, se inserta
          return true;
        }
        if (table_[(table_pos + exploration_value) % tableSize]->Search(k)) return false; // si ya se habia introducido dicho elemento
      }
      return false;
    }
    if (table_[table_pos]->Search(k)) return false; // si ya se habia introducido dicho elemento
    table_[table_pos]->Insert(k); // al ser abierta sencillamente lo coloca y ya
    return true;
  }
  void PrintTable() {
    for (size_t i = 0; i < tableSize; i++) { // en cada espacio de la secuencia insertamos un objeto
      std::cout << "Bloque " << i << std::endl; // para cada Bloque decimos el numero
      table_[i]->Print(); // e imprimimos el elemento que se encuentra en ese bloque
      std::cout << std::endl; // finalizamos la linea
    }
  }
 private:
  size_t tableSize; // Tamaño de la tabla
  DispersionFunction<Key>* fd_; // Función de dispersión
  ExplorationFunction<Key>* fe_ = nullptr;  // Función de exploración
  size_t block_size_ = 0; // Tamaño de bloque
  Sequence<Key>** table_; // Contenedor de la tabla hash
};

#endif  