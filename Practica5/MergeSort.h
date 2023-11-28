/** 
* Universidad de La Laguna
* Escuela Superior de Ingeniería y Tecnología
* Grado en Ingeniería Informática
* Asignatura: Algoritmos y Estructuras de Datos Avanzados
* Curso: 2º
* Práctica 5: Implementación de métodos de ordenación
* Autor: Paula María Darias Sosa
* Correo: alu0101398594@ull.es
* Fecha: 17/04/2023
*/

#include "SortMethod.h"
#include "algoritmos.h" 

template<class Key>
class MergeSort : public SortMethod<Key> {
 public:
    MergeSort(std::vector<Key> data, unsigned tamano) : SortMethod<Key>(data, tamano) {}
    void Sort() {
      Merge_Sort(this->seq_, 0, this->size_ - 1); 
    }
};

