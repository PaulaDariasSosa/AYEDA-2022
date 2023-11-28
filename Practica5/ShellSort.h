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
class ShellSort : public SortMethod<Key> {
 public:
    ShellSort(std::vector<Key> data, unsigned tamano, float alfa) : SortMethod<Key>(data, tamano), alfa_(alfa) {}
    void Sort() {
      Shell_Sort(this->seq_, alfa_, this->size_);
    }
  private:
    float alfa_;
};