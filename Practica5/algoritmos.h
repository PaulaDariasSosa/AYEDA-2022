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

#include <vector>

#pragma once

//-------------------------------------------------------------------Insertsort-------------------------------------------------------------------
template <typename Key>
int Insert_Sort (std::vector<Key>& seq, unsigned size) {
  int contador = 0;
  for (int step = 1; step < size; step++) {
    Key clave = seq[step];
    int j = step - 1;
    while (clave < seq[j] && j >= 0) {
      seq[j + 1] = seq[j];
      ++contador;
      --j;
    }
    seq[j + 1] = clave;
    ++contador;
    for (int i{0}; i < size; ++i) {
      std::cout << seq[i] << " ";
    }
    std::cout << std::endl;
  }
  return contador;
}
//-------------------------------------------------------------------Mergesort-------------------------------------------------------------------
template <typename Key>
void Merge(std::vector<Key>& seq, int left, int middle, int right) {
  int i, j, k;
  int n1 = middle - left + 1;
  int n2 = right - middle;
  std::vector<Key> left_seq(n1);
  std::vector<Key> right_seq(n2);
  // Copy data to temp arrays left_seq[] and right_seq[]
  for (i = 0; i < n1; i++) {
    left_seq[i] = seq[left + i];
  }
  for (j = 0; j < n2; j++) {
    right_seq[j] = seq[middle + 1 + j];
  }
  i = 0;
  j = 0;
  k = left;
      // Merge the temp arrays back into seq[left..right]
  while (i < n1 && j < n2) {
    if (left_seq[i] <= right_seq[j]) {
      seq[k] = left_seq[i];
      i++;
    } else {
      seq[k] = right_seq[j];
      j++;
    }
    k++;
  }
  while (i < n1) {
    seq[k] = left_seq[i];
    i++;
    k++;
  }
  while (j < n2) {
    seq[k] = right_seq[j];
    j++;
    k++;
  }
}

template <typename Key>
void Merge_Sort (std::vector<Key>& seq, int left, int right) {
  if (left < right) {
    int middle = (left + right) / 2;
    // Sort first part of the vector
    Merge_Sort(seq, left, middle);
    // Sort second part of the vector
    Merge_Sort(seq, middle + 1, right);
    // Merge both parts sorted
    Merge(seq, left, middle, right);
    for (unsigned int k = 0; k < seq.size(); k++) {
      std::cout << seq[k] << " ";
    }
    std::cout << "\n";
  }
}


//-------------------------------------------------------------------Shellsort-------------------------------------------------------------------
template <typename Key>
void Shell_Sort(std::vector<Key>& seq, float alfa, unsigned size) {
  int delta = seq.size() * alfa;
  while (delta > 0) {
    // Loop int the sequence with the delta
    for (long unsigned int i = delta; i < seq.size(); i++) {
      int j = i;
      int temp = seq[i];
      // Loop to compare the previous elements with the delta
      while (j >= delta && seq[j - delta] > temp) {
        seq[j] = seq[j - delta];
        j = j - delta;
      }
      seq[j] = temp;
    }
    if (delta == 2) {
      delta = 1;
    } else {
      delta = delta * alfa;
    } 
  for (int i{0}; i < size; ++i) {
    std::cout << seq[i] << " ";
  }
  std::cout << std::endl;
  }
}
//-------------------------------------------------------------------Heapsort-------------------------------------------------------------------
template <typename Key>
void Heapify(std::vector<Key>& seq, unsigned size, int i) {
    // Initialize largest as root
    int largest = i;
    // left = 2*i + 1
    int l = 2 * i + 1;
    // right = 2*i + 2
    int r = 2 * i + 2;
    // If left child is larger than root
    if (l < size && seq[l] > seq[largest])
        largest = l;

    // If right child is larger than largest
    // so far
    if (r < size && seq[r] > seq[largest])
        largest = r;
 
    // If largest is not root
    if (largest != i) {
        Key aux = seq[i];
        seq[i] = seq[largest];
        seq[largest] = aux;
        // Recursively heapify the affected
        // sub-tree
        Heapify(seq, size, largest);
    }
} 

template <typename Key>
void Headsort(std::vector<Key>& seq, unsigned N) {
  // Build heap (rearrange array)
  for (int i = N / 2 - 1; i >= 0; i--)
      // heapify(arr, N, i);
      Heapify(seq, N, i); 
      // One by one extract an element
      // from heap
    for (int i = N - 1; i > 0; i--) {
      // Move current root to end
      Key aux = seq[0];
      seq[0] = seq[i];
      seq[i] = aux;
      // call max heapify on the reduced heap
      //heapify(arr, i, 0);
      
      Heapify(seq, i, 0); 
    for (unsigned int k = 0; k < N; k++) {
        std::cout << seq[k] << " ";
      }
      std::cout << "\n";
    }
}

//-------------------------------------------------------------------Radixsort-------------------------------------------------------------------
template <typename Key>
int countSort(std::vector<Key>& seq, unsigned size, long exp) {
  std::vector<Key> output; // output array
  output.resize(size);
  int i, count [10] = {0};
  int contador = 0;
  // Store count of occurrences in count[]
  for (i = 0; i < size; i++)
      count[(seq[i] / exp) % 10]++;
  
  // Change count[i] so that count[i] now contains actual
  //  position of this digit in output[]
  for (i = 1; i < 10; i++)
      count[i] += count[i - 1];

  // Build the output array
  for (i = size - 1; i >= 0; i--) {
      output[count[(seq[i] / exp) % 10] - 1] = seq[i];
      ++contador;
      count[(seq[i] / exp) % 10]--;
  }

  // Copy the output array to arr[], so that arr[] now
  // contains sorted numbers according to current digit
  for (i = 0; i < size; i++)
      seq[i] = output[i];

  for (unsigned int k = 0; k < seq.size(); k++) {
      std::cout << seq[k] << " ";
    }
    std::cout << "\n";
  return contador;
}

template <typename Key>
int Radix_Sort(std::vector<Key>& seq, unsigned size) {
  int contador = 0;
  // Find the maximum number to know number of digits
  Key m = seq[0];
  for (auto aux : seq ) 
      if (aux > m) m = aux;
  // Do counting sort for every digit. Note that instead
  // of passing digit number, exp is passed. exp is 10^i
  // where i is current digit number
  for (Key exp = 1; m / exp > 0; exp *= 10)
      contador += countSort(seq, size, exp);
  return contador;
}


