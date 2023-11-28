// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 1: Representación de números grandes en notación posicional
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 12/02/2023

//Librerias incluidas:
#include <vector>
#include <iostream>
#include <array>
// Controlador para la definicion
#ifndef BigInt_H_
#define BigInt_H_

template <size_t Base>
class BigInt {
  public:
    //Constructores
    //Constructor mediante long/int/short
    BigInt(long n = 0) {
      if (n < 0) {
        signo_ = -1;
        n = -n;
      } else {
        signo_ = 1;
      } while (n > 0) {
        digitos_.push_back(n % Base);
        n /= Base;
      }
    }

    //Contructor mediante cadena
    BigInt(std::string& n_cadena) {
      digitos_.clear();
      if (n_cadena[0] == '-') {
        signo_ = -1;
        n_cadena.erase(0, 1);
      } else {
        signo_ = 1;
      }
      for (int i = n_cadena.size() - 1; i >= 0; --i) {
        if (n_cadena[i] < ':') digitos_.push_back(n_cadena[i] - '0');
        if (n_cadena[i] > ':') digitos_.push_back(n_cadena[i] -'A' + 10);
      }
    }

    //constructor mediante char*
    BigInt(const char* n_char) {
      std::string n_cadena = n_char;
      digitos_.clear();
      if (n_cadena[0] == '-') {
        signo_ = -1;
        n_cadena.erase(0, 1);
      } else {
        signo_ = 1;
      }
      for (int i = n_cadena.size() - 1; i >= 0; i--) {
        if (n_cadena[i] < ':') digitos_.push_back(n_cadena[i] - '0');
        if (n_cadena[i] > ':') digitos_.push_back(n_cadena[i] -'A' + 10);
      }
    }

    // Constructor de copia
    BigInt(const BigInt<Base>& a_copiar) {
      digitos_ = a_copiar.digitos_;
      signo_ = a_copiar.signo_;
    }

    //Getters
    void setDigitos(std::vector<int> digitos);
    void setLongitud(long longitud);
    
    //Asignación
    BigInt<Base>& operator=(const BigInt<Base>& a_copiar) {
      digitos_ = a_copiar.digitos_;
      signo_ = a_copiar.signo_;
      return *this;
    }

    //Inserción y extracción en flujo
    friend std::ostream& operator<<(std::ostream& out, const BigInt<Base>& actual) {
      if (actual.signo_ == -1) out << '-';
      for (int i = actual.digitos_.size() - 1; i >= 0; i--) {
        if (actual.digitos_[i] < 10) out << char(actual.digitos_[i] + '0');
        if (actual.digitos_[i] >= 10) out << char('A' + actual.digitos_[i] - 10);
      }
      return out;
    }

    friend std::istream& operator>>(std::istream& in, BigInt<Base>& a) {
      std::string s;
      in >> s;
      BigInt<Base> aux (s);
      a = aux;
      return in;
    }

    //Accesor
    int sign() const { return signo_; } // Signo: 1 o -1
    char operator[](int i) const { return digitos_[i]; } // lo da al reves porque el vector esta al reves

    //Comparación
    friend bool operator==(const BigInt<Base>& primero, const BigInt<Base>& segundo) {
      if (primero.digitos_.size() != segundo.digitos_.size()) return false;
      if (primero.sign() != segundo.sign()) return false;
      for (long unsigned int i = 0; i < primero.digitos_.size(); ++i) {
        if (primero[i] != segundo[i]) return false;
      }
      return true;
    }

    bool operator!=(const BigInt<Base>& actual) const {
      if (actual.digitos_.size() != digitos_.size()) return true;
      if (actual.sign() != sign()) return true;
      for (long unsigned int i = 0; i < actual.digitos_.size(); ++i) {
        if (actual[i] != digitos_[i]) return true;
      }
      return false;
    }
    friend bool operator>(const BigInt<Base>& operando1, const BigInt<Base>& operando2) {
      if (operando1.sign() == 1 && operando2.sign() == -1) return true;
      if (operando1.sign() == -1 && operando2.sign() == 1) return false; 
      if (operando1.digitos_.size() > operando2.digitos_.size()) return true;
      if (operando2.digitos_.size() > operando1.digitos_.size()) return false;
      for (long unsigned int i = operando2.digitos_.size() - 1; i >= 0; --i) {
        if (operando1[i] > operando2[i]) {
          if (operando1.sign() == -1 && operando2.sign() == -1) return false;
          return true;
        } 
        if (operando2[i] > operando1[i]) {
          if (operando1.sign() == -1 && operando2.sign() == -1) return true;
          return false;
        } 
      }
      return false;
    }

    bool operator>=(const BigInt<Base>& operando2) const {
      if ((*this > operando2)||(*this == operando2)) return true;
      return false;
    }

    friend bool operator<(const BigInt<Base>& operando1, const BigInt<Base>& operando2) {
      bool retorno = (operando1 >= operando2);
      return !retorno;
    }

    bool operator<=(const BigInt<Base>& operando2) const {
      bool retorno = (*this > operando2);
      return !retorno;
    }

    //Incremento/decremento
    BigInt<Base>& operator++() { // Pre-incremento
      if (signo_ == -1) {
        BigInt<Base> auxiliar = *this;
        auxiliar.signo_ = 1;
        --auxiliar;
        auxiliar.signo_ = -1;
        *this = auxiliar;
        return *this;
      }
      int i, n = digitos_.size();
      for (i = 0; i < n && digitos_[i] == Base-1;i++)
        digitos_[i] = 0;
      if(i == n)
        digitos_.push_back(1);
      else
        digitos_[i]++;
      return *this;
    } 

    BigInt<Base> operator++(int) { // Post-incremento
      BigInt<Base> aux;
      aux = *this;
      ++(*this);
      return aux;
    }

    BigInt<Base>& operator--() { // Pre-decremento
    if(digitos_[0] == 0 && digitos_.size() == 1) {
      signo_ = -1;
     return  ++*this;
    }
    if (signo_ == -1) {
        BigInt<Base> auxiliar = *this;
        auxiliar.signo_ = 1;
        ++auxiliar;
        auxiliar.signo_ = -1;
        *this = auxiliar;
        return *this;
      }
    int i, n = digitos_.size();
    for (i = 0; digitos_[i] == 0 && i < n;i++)
        digitos_[i] = 9;
    digitos_[i]--;
    if(n > 1 && digitos_[n - 1] == 0)
        digitos_.pop_back();
    return *this;
    }

    BigInt<Base> operator--(int) { // Post-decremento
    BigInt<Base> aux;
    aux = *this;
    --(*this);
    return aux;
    }
    
    //Operadores aritméticos
    friend BigInt<Base> operator+(const BigInt<Base>& sumando1, const BigInt<Base>& sumando2) {
      BigInt<Base> total;
      if (((sumando1.sign() == 1)&&(sumando2.sign() == 1))||((sumando1.sign() == -1)&&(sumando2.sign() == -1))) {
        total.signo_ = sumando1.sign();
      } else {
        if ((sumando1.sign() == 1)&&(sumando2.sign() == -1)) {
          BigInt<Base> sumando2_pos = sumando2;
          sumando2_pos.signo_ = 1;
          return (sumando1 - sumando2_pos);
        } 
        else {
          BigInt<Base> sumando1_pos = sumando1;
          sumando1_pos.signo_ = 1;
          return (sumando2 - sumando1_pos);
        }
      }
      long unsigned int i = 0, j = 0, carry = 0;
      while ((i < sumando1.digitos_.size())&&(j < sumando2.digitos_.size())) {
        long unsigned int resultado = sumando1[i++] + sumando2[j++] + carry;
        carry = 0;
        if (resultado >= Base) {
          total.digitos_.push_back(resultado % Base);
          carry = resultado / Base;
        } else total.digitos_.push_back(resultado);
      }
      if (i == sumando1.digitos_.size()) {
        while (j < sumando2.digitos_.size()) {
          long unsigned int resultado = sumando2[j++] + carry;
        carry = 0;
        if (resultado >= Base) {
          total.digitos_.push_back(resultado % Base);
          carry = resultado / Base;
        } else total.digitos_.push_back(resultado);
        }
      } else {
        while (i < sumando1.digitos_.size()) {
          long unsigned int resultado = sumando1[i++] + carry;
          carry = 0;
        if (resultado >= Base) {
          total.digitos_.push_back(resultado % Base);
          carry = resultado / Base;
        } else total.digitos_.push_back(resultado);
        }
      }
      if (carry == 1) total.digitos_.push_back(carry);
      return total; 
    }

    BigInt<Base> operator-(const BigInt<Base>& operando2) const {
      BigInt<Base> total;
      if ((sign() == 1)&&(operando2.sign() == -1)) {
        total = operando2;
        total.signo_ = 1;
        return (*this + total);
      }
      if ((sign() == -1)&&(operando2.sign() == -1)) {
        total = operando2;
        total.signo_ = 1;
        BigInt<Base> operando1 = *this;
        operando1.signo_ = 1;
        return (total - operando1);
      }
      if ((sign() == -1)&&(operando2.sign() == 1)) {
        total = operando2;
        total.signo_ = -1;
        return (*this + total);
      }
      if (operando2 > *this) {
        BigInt<Base> resultado = operando2 - *this;
        resultado.signo_ = -1;
        return resultado;
      }
      long unsigned int i = 0, j = 0, carry = 0, minuendo = 0, sustrayendo = 0;
      while ((i < digitos_.size())&&(j < operando2.digitos_.size())) {
        minuendo = digitos_[i++];
        sustrayendo =  operando2[j++];
        if (carry == 1) {
          sustrayendo += 1;
          carry = 0;
        } 
        if (minuendo < sustrayendo) {
          minuendo += Base;
          carry = 1;
        }
        total.digitos_.push_back(minuendo - sustrayendo);
      }
      if (i != digitos_.size()) {
        while (i < digitos_.size()) {
        minuendo = digitos_[i++];
        sustrayendo =  0;
        if (carry == 1) {
          sustrayendo += 1;
          carry = 0;
        } 
        if (minuendo < sustrayendo) {
          minuendo += Base;
          carry = 1;
        }
        total.digitos_.push_back(minuendo - sustrayendo);
        }
      }
      while ((total[total.digitos_.size()-1] == 0)&&(total != BigInt<Base> ("0"))) total.digitos_.resize(total.digitos_.size()-1);
    return total;
  }

  BigInt<Base> operator-() const {
    BigInt<Base> retorno = *this;
    int signo = this->sign();
    signo *= -1;
    retorno.signo_ = signo;
    return retorno;
  }

  BigInt<Base> operator*(const BigInt<Base>& operando2) const {
    BigInt<Base> resultado;
    BigInt<Base> incremento(1);
    BigInt<Base> multiplicando(*this);
    BigInt<Base> multiplicador(operando2);
    multiplicando.signo_ = 1;
    multiplicador.signo_ = 1;
    BigInt<Base> cero("0");
    while (cero != multiplicador) {
      resultado = resultado + multiplicando;
      cero = cero + incremento;
    }
    if (operando2.sign() == this->sign()) resultado.signo_ = 1;
    else resultado.signo_ = -1;
    return resultado;
  }

  friend BigInt<Base> operator/(const BigInt<Base>& operando1, const BigInt<Base>& operando2) {
    BigInt<Base> incremento(1);
    BigInt<Base> dividendo(operando1);
    BigInt<Base> divisor(operando2);
    dividendo.signo_ = 1;
    divisor.signo_ = 1;
    BigInt<Base> cero("0");
    while (dividendo >= divisor) {
      dividendo = dividendo - divisor;
      cero = cero + incremento;
    }
    if (operando1.sign() == operando2.sign()) cero.signo_ = 1;
    if (operando1.sign() != operando2.sign()) cero.signo_ = -1;
    return cero;
  }

  BigInt<Base> operator%(const BigInt<Base>& operando2) const {
    BigInt<Base> incremento(1);
    BigInt<Base> dividendo(*this);
    BigInt<Base> divisor(operando2);
    dividendo.signo_ = 1;
    divisor.signo_ = 1;
    BigInt<Base> cero("0");
    while (dividendo >= divisor) {
      dividendo = dividendo - divisor;
    }
    cero.signo_ = operando2.sign();
    return dividendo;
  }
  friend BigInt<Base> pow(const BigInt<Base>& operando1, const BigInt<Base>& operando2) {
    
    BigInt<Base> resultado;
    BigInt<Base> incremento(1);
    BigInt<Base> base(operando1);
    BigInt<Base> exponente(operando2);
    if (exponente == BigInt<Base> ("0")) return BigInt<Base> ("1");
    base.signo_ = 1;
    exponente.signo_ = 1;
    BigInt<Base> cero("1");
    resultado = base;
    while (cero != exponente) {
      resultado = resultado * base;
      cero = cero + incremento;
    }
    //if (operando2.sign() == this->sign()) resultado.signo_ = 1;
    //else resultado.signo_ = -1;
    return resultado;
  }
 private:
    std::vector<char> digitos_;
    int signo_;
};


#endif

