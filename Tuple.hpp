/*
Class : Tuple
Description : allows more succinct manipulation of data that comes in twos
Instances : varies
Hierarchical Level : 1
Functions :
|-> Tuple(int);
| | Tuple(int,int);
| | getL const : returns-> int; parameters-> void
| | getR const : returns-> int; parameters-> void
| | setL : returns-> void; parameters-> int
| | setR : returns-> void; parameters-> int
| | operator+ : returns-> Tuple; parameters-> const Tuple &; keyword-> const 
| | operator- : returns-> Tuple; parameters-> const Tuple &; keyword-> const 
| | operator== : returns-> bool; parameters-> const Tuple &; keyword-> const
| | operator* : returns-> Tuple; parameters-. const Tuple&; keyword-> const
| | operator= : returns-> void; parameters-> const Tuple &
| | operator+=: returns-> void; parameters-> const Tuple &
| | operator-=  : returns-> void; parameters-> const Tuple &
| | operator*= : returns-> void; parameters-> const Tuple &
| | operator* : returns-> Tuple; parameters-> int; keyword-> const 
| | operator/ : returns-> Tuple; parameters-> int; keyword-> const 
| | operator^ : returns-> Tuple; parameters-> int; keyword-> const 
| | operator*=  : returns-> void; parameters-> int;
Variables :
|-> left : stores the one of the values
| | right : stores the other value
*/

#ifndef TUPLE_HPP_
#define TUPLE_HPP_

/* A Tuple is anything that can represented
 * as two things. Position is one that uses 
 * Tuple alot. 
 */

class Tuple {
  
public:

  Tuple(void);
  Tuple(int,int);
  int getL(void) const;
  int getR(void) const;
  void setL(int) ;
  void setR(int) ;
  
  //Operations with another Tuple
  Tuple operator+(const Tuple &) const;
  Tuple operator-(const Tuple &) const;
  bool operator==(const Tuple &) const;
  Tuple operator*(const Tuple &) const;
  void operator=(const Tuple &);
  void operator+=(const Tuple &);  
  void operator-=(const Tuple &);
  void operator*=(const Tuple &);
  
//Operations with an int
  Tuple operator*(int) const;
  Tuple operator/(int) const;
  Tuple operator^(int) const;
  void operator*=(int) ;
private:
  
  int left;
  int right;
};

#endif
