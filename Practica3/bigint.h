// Universidad de La Laguna
// Escuela Superior de Ingeniería y Tecnología
// Grado en Ingeniería Informática
// Asignatura: Algoritmos y Estructuras de Datos Avanzados
// Curso: 2º
// Práctica 3: Calculadora universal para números enteros grandes
// Autor: Paula María Darias Sosa
// Correo: alu0101398594@ull.es
// Fecha: 06/03/2023

//Librerias incluidas:
#include <vector>
#include <iostream>
#include <array>
#include <cmath>
#include "bigintexcep.h"
#include "number.h"
// Controlador para la definicion
#ifndef BigInt_H_
#define BigInt_H_

template <size_t Base>
class BigInt;
template<>
class BigInt<2>;

template <size_t Base>
class BigInt : public Number{
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
        if (n_cadena[i] < ':') {
          if ((n_cadena[i] - '0') >= Base) throw BigIntBadDigit();
          digitos_.push_back(n_cadena[i] - '0');
        } 
        if (n_cadena[i] > ':') {
          if (Base <= 10) throw BigIntBadDigit();
          digitos_.push_back(n_cadena[i] -'A' + 10);
        } 
        if (n_cadena[i] > 'F') throw BigIntBadDigit();
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
        if (n_cadena[i] < ':') {
          if ((n_cadena[i] - '0') >= Base) throw BigIntBadDigit();
          digitos_.push_back(n_cadena[i] - '0');
        } 
        if (n_cadena[i] > ':') {
          if (Base <= 10) throw BigIntBadDigit();
          digitos_.push_back(n_cadena[i] -'A' + 10);
        } 
        if (n_cadena[i] > 'F') throw BigIntBadDigit();
      }
    }

    // Constructor de copia
    BigInt(const BigInt<Base>& a_copiar) {
      digitos_ = a_copiar.digitos_;
      signo_ = a_copiar.signo_;
    }

    //Getters
    friend std::vector<char> getDigitos(const BigInt<Base>& yu) {
      std::vector<char>fu (yu.digitos_); 
      return fu;
      }
    
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
      BigInt<Base>* aux_ptr = new BigInt<Base>(*this);
      return *aux_ptr;
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
    BigInt<Base> a = *this;
    BigInt<Base> b = operando2;
    if((a.digitos_.size() == 1 && a.digitos_[0] == 0) || (b.digitos_.size() == 1 && b.digitos_[0] == 0)){
        a = BigInt();
        return a;
    }
    int n = a.digitos_.size(), m = b.digitos_.size();
    std::vector<int> v(n + m, 0);
    for (int i = 0; i < n;i++)
        for (int j = 0; j < m;j++){
            v[i + j] += (a.digitos_[i] ) * (b.digitos_[j]);
        }
    n += m;
    a.digitos_.resize(v.size());
    for (int s, i = 0, t = 0; i < n; i++)
    {
        s = t + v[i];
        v[i] = s % Base;
        t = s / Base;
        a.digitos_[i] = v[i] ;
    }
    for (int i = n - 1; i >= 1 && !v[i];i--)
            a.digitos_.pop_back();
    if (this->signo_ != operando2.signo_) a.signo_ = -1;
    return a;
  }


  friend BigInt<Base> operator/(const BigInt<Base>& operando1, const BigInt<Base>& operando2) {
    BigInt<Base> a = operando1;
    BigInt<Base> b = operando2;
    if(b.digitos_.size() == 1 && b.digitos_[0] == 0)
        throw BigIntDivisionByZero();
    if(a < b){
        a = BigInt<Base>("0");
        return a;
    }
    if(a == b){
        a = BigInt<Base>(1);
        return a;
    }
    int i, lgcat = 0, cc;
    int n = a.digitos_.size();
    std::vector<int> cat(n, 0);
    BigInt<Base> t;
    for (i = n - 1; t * Base + a.digitos_[i]  < b;i--){
        t = t * Base;
        t = t + a.digitos_[i] ;
    }
    for (; i >= 0; i--){
        t = t * Base + a.digitos_[i];
        for (cc = (Base - 1); (BigInt<Base>(cc) * b) > t;cc--);
        t = t - (BigInt<Base>(cc) * b);
        cat[lgcat++] = cc;
    }
    a.digitos_.resize(cat.size());
    for (i = 0; i < lgcat;i++) a.digitos_[i] = cat[lgcat - i - 1];
    a.digitos_.resize(lgcat);
    return a;
  }

  BigInt<Base> operator%(const BigInt<Base>& operando2) const {
    BigInt<Base> a = *this;
    BigInt<Base> b = operando2;
    if(b.digitos_.size() == 1 && b.digitos_[0] == 0)
        throw("Arithmetic Error: Division By 0");
    if(a < b){
        return a;
    }
    if(a == b){
        a = BigInt("0");
        return a;
    }
    int i, lgcat = 0, cc;
    int n = a.digitos_.size();
    std::vector<int> cat(n, 0);
    BigInt<Base> t;
    for (i = n - 1; t * 10 + a.digitos_[i]  < b;i--){
        t = t * 10;
        t = t + a.digitos_[i] ;
    }
    for (; i >= 0; i--){
        t = t * 10 + a.digitos_[i];
        for (cc = 9; BigInt<Base>(cc) * b > t;cc--);
        t = t -(BigInt<Base>(cc) * b);
        cat[lgcat++] = cc;
    }
    a = t;
    return a;
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
    return resultado;
  }
  
  operator BigInt<2>() const;

  operator BigInt<8>() const {
  BigInt<8> sumatorio;
  if (*this == BigInt<Base>("0")) return BigInt<8>("0");
  BigInt<Base> operando = *this;
  int signo = this->signo_;
  if (signo == -1) {
    operando = -operando;
  } 
  for (long unsigned int i = 0; i < operando.digitos_.size(); ++i) {
    if (operando.digitos_[i] != 0) {
      sumatorio = sumatorio + operando.digitos_[i]*(pow(Base, i));
    } 
  }
  if (signo == -1) sumatorio = -sumatorio;
  BigInt<8>* aux_ptr = new BigInt<8>(sumatorio);
  return *aux_ptr;
  //return sumatorio;
}

operator BigInt<10>() const {
  BigInt<10> sumatorio;
  if (*this == BigInt<Base>("0")) return BigInt<10>("0");
  BigInt<Base> operando = *this;
  int signo = this->signo_;
  if (signo == -1) {
    operando = -operando;
  } 
  for (long unsigned int i = 0; i < operando.digitos_.size(); ++i) {
    if (operando.digitos_[i] != 0) {
      sumatorio = sumatorio + operando.digitos_[i]*(pow(Base, i));
    } 
  }
  if (signo == -1) sumatorio = -sumatorio;
  return sumatorio;
}

operator BigInt<16>() const {
  BigInt<16> sumatorio;
  if (*this == BigInt<Base>("0")) return BigInt<16>("0");
  BigInt<Base> operando = *this;
  int signo = this->signo_;
  if (signo == -1) {
    operando = -operando;
  } 
  for (long unsigned int i = 0; i < operando.digitos_.size(); ++i) {
    if (operando.digitos_[i] != 0) {
      sumatorio = sumatorio + operando.digitos_[i]*(pow(Base, i));
    } 
  }
  if (signo == -1) sumatorio = -sumatorio;
  return sumatorio;
}

  Number* add (const Number* b2) const {
    Number* number_ptr = nullptr;
    BigInt<Base>* derivada_ptr = new BigInt<Base> ((*this) +(BigInt<Base>(*b2)));
    number_ptr = derivada_ptr;
    return number_ptr;
  }

  Number* subtract(const Number* b2) const {
    Number* number_ptr = nullptr;
    BigInt<Base>* derivada_ptr = new BigInt<Base> ((*this) - (BigInt<Base>(*b2)));
    number_ptr = derivada_ptr;
    return number_ptr;
  }

  Number* multiply(const Number* b2) const {
    Number* number_ptr = nullptr;
    BigInt<Base>* derivada_ptr = new BigInt<Base> ((*this) * (BigInt<Base>(*b2)));
    number_ptr = derivada_ptr;
    return number_ptr;
  }

  Number* divide(const Number* b2) const {
    Number* number_ptr = nullptr;
    try {
      BigInt<Base> ((*this) / (BigInt<Base>(*b2)));
    } catch (BigIntDivisionByZero& exception) {
      std::cerr << exception.what() << std::endl;
      std::cerr << "File: " << exception.getFile() << std::endl;
      std::cerr << "Function: " << exception.getFuntion() << std::endl;
      std::cerr << "Message: " << exception.getMsg() << std::endl;
    }
    BigInt<Base>* derivada_ptr = new BigInt<Base> ((*this) / (BigInt<Base>(*b2)));
    number_ptr = derivada_ptr;
    return number_ptr;
  }

  Number* module(const Number* b2) const {
    Number* number_ptr = nullptr;
    BigInt<Base>* derivada_ptr = new BigInt<Base> ((*this) % (BigInt<Base>(*b2)));
    number_ptr = derivada_ptr;
    return number_ptr;
  }
  
  Number* power(const Number* b2) const {
    Number* number_ptr = nullptr;
    BigInt<Base>* derivada_ptr = new BigInt<Base> (pow((*this), (BigInt<Base>(*b2))));
    number_ptr = derivada_ptr;
    return number_ptr;
  }

  std::ostream& write(std::ostream& out) const {
    out << Base << ", " << BigInt<Base>(*this);
    return out;
  }

  std::istream& read(std::istream& in) {
    Number* number_ptr = nullptr;
    std::string s;
    in >> s;
    BigInt<Base>* derivada_ptr = new BigInt<Base> (s);
    number_ptr = derivada_ptr;
    *this = *derivada_ptr;
    return in;
  }

 private:
    std::vector<char> digitos_;
    int signo_;
};

template<>
class BigInt<2> : public Number {
 public:
  BigInt(long n = 0) {
    bool negativo = false;
    if (n < 0) {
      negativo = true;
      n *= -1;
    }
    while (n > 0) {
      digitos_.push_back(n % 2);
      n /= 2;
    }
    digitos_.push_back(0);
    if (negativo == true) {
      bool primer_uno = false;
      for (long unsigned int i = 0;i < digitos_.size(); ++i) {
        if (primer_uno == true) {
          if (digitos_[i] == 1) digitos_[i] = 0;
          else digitos_[i] = 1;
        }
        if ((primer_uno == false)&&(digitos_[i] == 1)) {
          primer_uno = true;
        }
      }
    }
  }

  BigInt(std::string& n_cadena) {
    digitos_.clear();
    for (int i = n_cadena.size() - 1; i >= 0; --i) {
      if (n_cadena[i] > '1') throw BigIntBadDigit();
      digitos_.push_back(n_cadena[i] - '0');
    }
  }

  BigInt(const char* n_cadena_char) {
    std::string n_cadena = n_cadena_char;
    for (int i = n_cadena.size() - 1; i >= 0; --i) {
      if (n_cadena[i] > '1') throw BigIntBadDigit();
      digitos_.push_back(n_cadena[i] - '0');
    }
  }

  BigInt(const BigInt<2>& a_copiar){ // Constructor de copia
    digitos_ = a_copiar.digitos_;
  }    
    //Asignación
  BigInt<2>& operator=(const BigInt<2>& a_copiar) {
    digitos_ = a_copiar.digitos_;
    return *this;
  }

  friend std::ostream& operator<<(std::ostream& out, const BigInt<2>& actual)   {
    for (int i = actual.digitos_.size() - 1; i >= 0; i--) {
      out << char(actual.digitos_[i] + '0');
    }
    return out;
  }

  friend std::istream& operator>>(std::istream& in, BigInt<2>& a) {
    std::string s;
    in >> s;
    BigInt<2> aux (s);
    a = aux;
    return in;
  }
  
  operator BigInt<2>() const {
    return *this;
  }

  operator BigInt<8>() const {
    BigInt<8> sumatorio;
    BigInt<2> operando = *this;
    int signo = this->digitos_[digitos_.size() - 1];
    if (signo == 1) {
      operando = -operando;
      signo = -1;
    } else {
      signo = 1;
    }
    for (long unsigned int i = 0; i < operando.digitos_.size() - 1; ++i) {
      if (operando.digitos_[i] != 0) {
        sumatorio = sumatorio + operando.digitos_[i]*(pow(2, i));
      } 
    }
    sumatorio = sumatorio + BigInt<8>("0");
    if (signo == -1) sumatorio = -sumatorio;
    return sumatorio;
  }

  operator BigInt<10>() const {
    BigInt<10> sumatorio;
    BigInt<2> operando = *this;
    int signo = this->digitos_[digitos_.size() - 1];
    if (signo == 1) {
      operando = -operando;
      signo = -1;
    } else {
      signo = 1;
    }
    for (long unsigned int i = 0; i < operando.digitos_.size() - 1; ++i) {
      if (operando.digitos_[i] != 0) {
        sumatorio = sumatorio + operando.digitos_[i]*(pow(2, i));
      } 
    }
    sumatorio = sumatorio + BigInt<10>("0");
    if (signo == -1) sumatorio = -sumatorio;
    return sumatorio;
  }

  operator BigInt<16>() const {
    BigInt<16> sumatorio;
    BigInt<2> operando = *this;
    int signo = this->digitos_[digitos_.size() - 1];
    if (signo == 1) {
      operando = -operando;
      signo = -1;
    } else {
      signo = 1;
    }
    for (long unsigned int i = 0; i < operando.digitos_.size() - 1; ++i) {
      if (operando.digitos_[i] != 0) {
        sumatorio = sumatorio + operando.digitos_[i]*(pow(2, i));
      } 
    }
    sumatorio = sumatorio + BigInt<16>("0");
    if (signo == -1) sumatorio = -sumatorio;
    return sumatorio;
  }

  char operator[](int i) const {return digitos_[i];}

  friend bool operator==(const BigInt<2>& operando1, const BigInt<2> & operando2)  {
    BigInt<2> primero = operando1;
    BigInt<2> segundo = operando2;
    if (operando1.digitos_.size() != operando2.digitos_.size()) Igualar_tamano(primero, segundo);
    if (primero.digitos_.size() != segundo.digitos_.size()) return false;
    for (long unsigned int i = 0; i < primero.digitos_.size(); ++i) {
      if (primero[i] != segundo[i]) return false;
    }
    return true;
  }

bool operator!=(const BigInt<2>& segundo) const {
  bool retorno = (*this == segundo);
  return !retorno;
}

  friend bool operator>(const BigInt<2>& operando_1, const BigInt<2> &operando_2) {
    BigInt<2> operando1 = operando_1;
    BigInt<2> operando2 = operando_2;
    if (operando1.digitos_.size() != operando2.digitos_.size()) Igualar_tamano(operando1, operando2);
    if (operando1[operando1.digitos_.size() - 1] == 0 && operando2[operando2.digitos_.size() - 1] == 1) return true;
    if (operando1[operando1.digitos_.size() - 1] == 1 && operando2[operando2.digitos_.size() - 1] == 0) return false; 
        for (long unsigned int i = operando2.digitos_.size() - 2; i >= 0; --i) {
          if (operando1[i] > operando2[i]) {
            //if (operando1[operando1.digitos_.size() - 1] == 1 && operando2[operando2.digitos_.size() - 1] == 1) return false;
            return true;
          } 
          if (operando2[i] > operando1[i]) {
            //if (operando1[operando1.digitos_.size() - 1] == 1 && operando2[operando2.digitos_.size() - 1] == 1) return true;
            return false;
          } 
        }
    return false;
  }
    

  bool operator>=(const BigInt<2>& operando2) const {
    bool retorno = (*this > operando2) || (*this == operando2);
    return retorno;
  }

  friend bool operator<(const BigInt<2>& operando1, const BigInt<2>&operando2) {
    bool retorno = (operando1 > operando2);
    return !retorno;
  }

  bool operator<=(const BigInt<2>& operando2) const {
    bool retorno = (*this < operando2) || (*this == operando2);
    return retorno;
  }

  friend BigInt<2> operator+(const BigInt<2>& operando1, const BigInt<2>& operando2) {
    // Overflow: Cuando en una suma con signo, dos números positivos arrojan un 
    // resultado negativo, o dos números negativos arrojan un resultado positivo.
    BigInt<2> total;
    total.digitos_.clear();
    BigInt<2> sumando1 = operando1;
    BigInt<2> sumando2 = operando2;
    if (sumando1.digitos_.size() != sumando2.digitos_.size()) Igualar_tamano(sumando1, sumando2);
    long unsigned int i = 0, j = 0, carry = 0;
        while ((i < sumando1.digitos_.size())&&(j < sumando2.digitos_.size())) {
          long unsigned int resultado = sumando1[i++] + sumando2[j++] + carry;
          carry = 0;
          if (resultado >= 2) {
            total.digitos_.push_back(resultado % 2);
            carry = resultado / 2;
          } else total.digitos_.push_back(resultado);
        }
        if (i == sumando1.digitos_.size()) {
          while (j < sumando2.digitos_.size()) {
            long unsigned int resultado = sumando2[j++] + carry;
          carry = 0;
          if (resultado >= 2) {
            total.digitos_.push_back(resultado % 2);
            carry = resultado / 2;
          } else total.digitos_.push_back(resultado);
          }
        } else {
          while (i < sumando1.digitos_.size()) {
            long unsigned int resultado = sumando1[i++] + carry;
            carry = 0;
          if (resultado >= 2) {
            total.digitos_.push_back(resultado % 2);
            carry = resultado / 2;
          } else total.digitos_.push_back(resultado);
        }
      }
    if ((sumando1[sumando1.digitos_.size() - 1] == sumando2[sumando2.digitos_.size() - 1])&&(sumando1[sumando1.digitos_.size() - 1] != total[total.digitos_.size() - 1])) total.digitos_.push_back(carry);
    return total;
  }

  BigInt<2> operator-() const {
    bool primer_uno = false;
    BigInt<2> aux = *this;
    for (long unsigned int i = 0;i < aux.digitos_.size(); ++i) {
      if (primer_uno == true) {
        if (digitos_[i] == 1) aux.digitos_[i] = 0;
        else aux.digitos_[i] = 1;
      }
      if ((primer_uno == false)&&(aux.digitos_[i] == 1)) {
        primer_uno = true;
      }
    }
    return aux;
  }

  BigInt<2> operator-(const BigInt<2> & operando2) const {
    BigInt<2> operando2_c2 = -operando2;
    BigInt<2> total = *this + operando2_c2;
    if (operando2 == *this) return BigInt<2>();
    return total;
  }

  BigInt<2> operator*(const BigInt<2>& operando2) const {
    BigInt<2> a = *this;
    BigInt<2> b = operando2;
    if (a.digitos_.size() != b.digitos_.size()) Igualar_tamano(a, b);
    int cambiar_signo = 1;
      if (this->digitos_[digitos_.size() - 1] == 1) {
        a = -a;
        cambiar_signo *= -1;
      } 
      if (operando2.digitos_[operando2.digitos_.size() - 1] == 1) {
        b = -b;
        cambiar_signo *= -1;
      }
      if((a.digitos_.size() == 1 && a.digitos_[0] == 0) || (b.digitos_.size() == 1 && b.digitos_[0] == 0)){
          a = BigInt();
          return a;
      }
      int n = a.digitos_.size() - 1, m = b.digitos_.size() - 1;
      std::vector<int> v(n + m, 0);
      for (int i = 0; i < n;i++)
          for (int j = 0; j < m;j++){
              v[i + j] += (a.digitos_[i] ) * (b.digitos_[j]);
          }
      n += m;
      a.digitos_.resize(v.size());
      for (int s, i = 0, t = 0; i < n; i++) {
          s = t + v[i];
          v[i] = s % 2;
          t = s / 2;
          a.digitos_[i] = v[i] ;
      }
      for (int i = n - 1; i >= 1 && !v[i];i--)
              a.digitos_.pop_back();
      a.digitos_.push_back(0);
      if (cambiar_signo == -1) a = -a;
      return a;
  }

  friend BigInt<2> operator/(const BigInt<2>& operando1, const BigInt<2>& operando2) {
    BigInt<2> incremento("01");
    BigInt<2> dividendo(operando1);
    BigInt<2> divisor(operando2);
    int cambiar_signo = 1;
    if (operando2 == (BigInt<2>("00"))) {
      throw BigIntDivisionByZero();
    }

    if (operando1 < operando2) return BigInt<2>("00");
    if (operando1.digitos_[operando1.digitos_.size() - 1] == 1) {
      dividendo = -dividendo;
      cambiar_signo *= -1;
    } 
    if (operando2.digitos_[operando2.digitos_.size() - 1] == 1) {
      divisor = -divisor;
      cambiar_signo *= -1;
    }
    BigInt<2> a(dividendo);
    BigInt<2> b(divisor);
    int i, lgcat = 0, cc;
    int n = a.digitos_.size(), m = b.digitos_.size();
    std::vector<bool> cat(n, 0);
    BigInt<2> t;
    for (i = n - 1; t * 2 + BigInt<2>(a.digitos_[i])  < b;i--){
        t = t * 2;
        t = t + BigInt<2>(a.digitos_[i]) ;
    }
    for (; i >= 0; i--){
        t = t * 2 + BigInt<2>(a.digitos_[i]);
        for (cc = 1; BigInt<2>(cc) * b > t;cc--);
        t = t - BigInt<2>(cc)* b;
        cat[lgcat++] = cc;
    }
    a.digitos_.resize(cat.size());
    for (i = 0; i < lgcat;i++)
        a.digitos_[i] = cat[lgcat - i - 1];
    a.digitos_.resize(lgcat);
    if (cambiar_signo == -1) a = -a;
    return a;
  }

  friend BigInt<2> pow(const BigInt<2>& operando1, const BigInt<2>& operando2) {
    BigInt<2> exponente = operando2;
    BigInt<2> base = operando1;
    BigInt<2> cero("0");
    BigInt<2> resultado("01");
    while(exponente != cero){
        if(exponente[0] & 1) { 
          resultado = resultado * base;
        }
        base = base * base;
        divide_by_2(exponente);
    }
    return resultado;
  }

  friend void divide_by_2(BigInt<2>& a){
    int add = 0;
    for (int i = a.digitos_.size() - 1; i >= 0;i--){
        int digit = (a.digitos_[i] >> 1) + add;
        add = (a.digitos_[i] & 1);
        a.digitos_[i] = digit;
    }
    while(a.digitos_.size() > 1 && !a.digitos_.back())
        a.digitos_.pop_back();
  }

  BigInt<2> operator%(const BigInt<2>& operando2) const {
  BigInt<2> incremento("01");
    BigInt<2> dividendo(*this);
    BigInt<2> divisor(operando2);
    int cambiar_signo = 1;
    if (this->digitos_[digitos_.size() - 1] == 1) {
      dividendo = -dividendo;
    } 
    if (operando2.digitos_[operando2.digitos_.size() - 1] == 1) {
      divisor = -divisor;
      cambiar_signo *= -1;
    }
    BigInt<2> cero("0");
    while (dividendo >= divisor) {
      dividendo = dividendo - divisor;
    }
    dividendo.digitos_.push_back(0); // el signo
    if (cambiar_signo == -1) dividendo = -dividendo;
    return dividendo;
  }

  //Incremento/decremento
  BigInt<2>& operator++() { // Pre-incremento
    BigInt<2> auxiliar = *this;
    if (this->digitos_[digitos_.size() - 1] == 1) {
      auxiliar = -auxiliar;
      --auxiliar;
      auxiliar = -auxiliar;
      *this = auxiliar;
      return *this;
    }
    *this = auxiliar + BigInt<2>("01");
    return *this;
  } 

  BigInt<2> operator++(int) { // Post-incremento
    BigInt<2> aux;
    aux = *this;
    ++(*this);
    return aux;
  }

  BigInt<2>& operator--() { // Pre-decremento
    BigInt<2> auxiliar = *this;
    if (this->digitos_[digitos_.size() - 1] == 1) {
      auxiliar = -auxiliar;
      ++auxiliar;
      auxiliar = -auxiliar;
      *this = auxiliar;
      return *this;
    }
    *this = auxiliar + BigInt<2>("111");
    return *this;
  }

  BigInt<2> operator--(int) { // Post-decremento
    BigInt<2> aux;
    aux = *this;
    --(*this);
    return aux;
  }

  friend void Igualar_tamano(BigInt<2>& numero1, BigInt<2>& numero2) { // Extender signo
    if (numero1.digitos_.size() > numero2.digitos_.size()) {
      while (numero1.digitos_.size() > numero2.digitos_.size()) {
        numero2.digitos_.push_back(numero2.digitos_[numero2.digitos_.size() - 1]);
      }
    } else {
      while (numero2.digitos_.size() > numero1.digitos_.size()) {
        numero1.digitos_.push_back(numero1.digitos_[numero1.digitos_.size() - 1]);
      }
    }
  }

  Number* add (const Number* b2) const {
    Number* number_ptr = nullptr;
    BigInt<2>* derivada_ptr = new BigInt<2> ((*this) + (BigInt<2>(*b2)));
    number_ptr = derivada_ptr;
    return number_ptr;
  }
  
  Number* subtract(const Number* b2) const {
    Number* number_ptr = nullptr;
    BigInt<2>* derivada_ptr = new BigInt<2> ((*this) - (BigInt<2>(*b2)));
    number_ptr = derivada_ptr;
    return number_ptr;
  }

  Number* multiply(const Number* b2) const {
    Number* number_ptr = nullptr;
    BigInt<2>* derivada_ptr = new BigInt<2> ((*this) * (BigInt<2>(*b2)));
    number_ptr = derivada_ptr;
    return number_ptr;
  }

  Number* divide(const Number* b2) const {
    try {
      BigInt<2> ((*this) / (BigInt<2>(*b2)));
    } catch (BigIntDivisionByZero& exception) {
      std::cerr << exception.what() << std::endl;
      std::cerr << "File: " << exception.getFile() << std::endl;
      std::cerr << "Function: " << exception.getFuntion() << std::endl;
      std::cerr << "Message: " << exception.getMsg() << std::endl;
    }
    Number* number_ptr = nullptr;
    BigInt<2>* derivada_ptr = new BigInt<2> ((*this) / (BigInt<2>(*b2)));
    number_ptr = derivada_ptr;
    return number_ptr;
  }

  Number* module(const Number* b2) const {
    Number* number_ptr = nullptr;
    BigInt<2>* derivada_ptr = new BigInt<2> ((*this) % (BigInt<2>(*b2)));
    number_ptr = derivada_ptr;
    return number_ptr;
  }
  
  Number* power(const Number* b2) const {
    Number* number_ptr = nullptr;
    BigInt<2>* derivada_ptr = new BigInt<2> (pow((*this),(BigInt<2>(*b2))));
    number_ptr = derivada_ptr;
    return number_ptr;
  }
  
  std::ostream& write(std::ostream& out) const {
    out << 2 << ", " << BigInt<2>(*this);
    return out;
  }

  std::istream& read(std::istream& in) {
    Number* number_ptr = nullptr;
    std::string s;
    in >> s;
    BigInt<2>* derivada_ptr = new BigInt<2> (s);
    number_ptr = derivada_ptr;
    *this = *derivada_ptr;
    return in;
  }

 private:
  std::vector<bool> digitos_;
};


template <size_t Base>
BigInt<Base>::operator BigInt<2UL>() const {
  BigInt<2> sumatorio;
  if (*this == BigInt<Base>("0")) return BigInt<2>("0");
  BigInt<Base> operando = *this;
  int signo = this->signo_;
  if (signo == -1) {
    operando = -operando;
  } 
  for (long unsigned int i = 0; i < operando.digitos_.size(); ++i) {
    if (operando.digitos_[i] != 0) {
      sumatorio = sumatorio + operando.digitos_[i]*(pow(Base, i));
    } 
  }
  if (signo == -1) sumatorio = -sumatorio;
  return sumatorio;
}

#endif

