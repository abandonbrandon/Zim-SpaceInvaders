#include "Tuple.hpp"
#include <cmath>
#include <cstdlib>
#define L left
#define R right

Tuple::Tuple(void) : L (1), R (1) {}


//------------------------------------------------------------------------------

Tuple::Tuple(int le, int ri) {

  L = le;
  R = ri;
}

//------------------------------------------------------------------------------

int Tuple::getL(void) const {
  
  return L;
}

//------------------------------------------------------------------------------

int Tuple::getR(void) const {
  
  return R;
}

//------------------------------------------------------------------------------

void Tuple::setL(int le) {
  
  L = le;
}

//------------------------------------------------------------------------------

void Tuple::setR(int ri) {
  
  R = ri;
}

//------------------------------------------------------------------------------

Tuple Tuple::operator*(const Tuple& other) const {

  return Tuple (L * other.L, R * other.R);
}

//------------------------------------------------------------------------------

void Tuple::operator=(const Tuple& other) {
  
  L = other.L;
  R = other.R;
}

//------------------------------------------------------------------------------

void Tuple::operator+=(const Tuple& other) {
  
  L += other.L;
  R += other.R;
}

//------------------------------------------------------------------------------

void Tuple::operator-=(const Tuple& other) {
  
  L -= other.L;
  R -= other.R;
}

//------------------------------------------------------------------------------

void Tuple::operator*=(const Tuple& other) {

  L *= other.L;
  R *= other.R;
}

//------------------------------------------------------------------------------

Tuple Tuple::operator+(const Tuple &other) const {
  
  return Tuple (L + other.L, R + other.R);
}

//------------------------------------------------------------------------------

bool Tuple::operator==(const Tuple& other) const {
  
  return ( L == other.L && R == other.R );
}

//------------------------------------------------------------------------------

Tuple Tuple::operator-(const Tuple& other) const {
  
  return Tuple (L - other.L, R - other.R);
}

//------------------------------------------------------------------------------

Tuple Tuple::operator^(int other) const {

  return Tuple ( pow ( L,other ), pow ( R,other ) );
}

//------------------------------------------------------------------------------

Tuple Tuple::operator*(int other) const {

  return Tuple (L * other, R * other);
}

void Tuple::operator*=(int other) {
  
  L *= other;
  R *= other;
}
