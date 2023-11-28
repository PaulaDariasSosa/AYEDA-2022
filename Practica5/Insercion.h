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
class Insercion : public SortMethod<Key> {
 public:
    Insercion(std::vector<Key> data, unsigned tamano) : SortMethod<Key>(data, tamano) {}
    void Sort() {
     contador = Insert_Sort(this->seq_, this->size_); 
     std::cout << "Numero de movimientos: " << contador << std::endl;
    }
 private:
    int contador;
};

