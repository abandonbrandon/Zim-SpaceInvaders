/*
Class : List
Description : represents a collection of Tuples
Instances : varies
Hierarchical Level : 1
Functions :
|-> List(int);
| | List(Tuple*,int);
| | ~List(void);
| | sum : returns-> Tuple; parameters-> void; keyword-> const 
| | product : returns-> Tuple; parameters-> void; keyword-> const 
| | add : returns-> void; parameters-> const Tuple&
| | get : returns-> Tuple; parameter-> int
| | fradd : returns-> void; parameters-> const Tuple&
| | append : returns-> void; parameters-> const List&
| | frappend : returns-> void; parameters-> const List&
| | insert : returns-> void; parameters-> const Tuple&,int
| | remove : returns-> void; parameters-> int
| | replace : returns-> void; parameters-> const Tuple&,int
| | reverse : returns-> void; parameters-> void
| | contains : returns-> bool; parameters-> const Tuple&; keyword-> const 
| | occurs : returns-> int; parameters-> const Tuple&; keyword-> const 
| | elements const : returns-> int; parameters-> void
| | operator* : returns-> List; parameters-> const List&; keyword-> const 
| | operator+ : returns-> List; parameters-> const List&; keyword-> const 
| | operator[] const : returns-> Tuple; parameters-> int
| | operator= : returns-> void; parameters-> const List&
| | operator+= : returns-> void; parameters-> const List&
| | operator*= : returns-> void; parameters-> const List&
Variables :
|-> front : the head pointer
| | num : keeps track of how many elements
*/

/* The List class is a class that keeps track of 
 * everything that is more than 3 instances. Some
 * examples would be the Tuples.
 */

#ifndef LIST_HPP_
#define LIST_HPP_

#include "Tuple.hpp"

class List {

public:
  
  List(int);
  List(Tuple*,int);
  ~List(void);
  
  Tuple sum(void) const;
  Tuple product(void) const;
  void add(const Tuple&);
  void getEle (int) const;
  Tuple getTup (int) const;
  
  void fradd(const Tuple&);
  void append(const List&);
  void frappend(const List&);
  void insert(const Tuple&,int);
  void remove(int);
  
  void replace(const Tuple&,int);
  void reverse(void);
  bool contains(const Tuple&) const;
  int occurs(const Tuple&) const;
  int elements(void) const;

  List operator*(const List&) const;
  List operator+(const List&) const;
  Tuple operator[](int) const;
  void operator=(const List&);
  void operator+=(const List&);
  void operator*=(const List&);

private:
  Tuple* front;
  int num;
  
};

#endif
