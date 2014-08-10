#include "Tuple.hpp"
#include <cmath>
#include <cstdlib>
#include "List.hpp"
#include <iostream>
using namespace std;

List::List(int n) : num(n) {
  
  front = new Tuple[n];

  for (int i(0);i<n;i++)
    front[i] = Tuple();
}

//------------------------------------------------------------------------------

List::List(Tuple* arr,int n) : num(n) {
  
  front = new Tuple[n];
  
  for (int i(0);i<n;i++)
    front[i] = arr[i];
}

//------------------------------------------------------------------------------

List::~List(void) {

  if (front != NULL)
    delete[] front;
}

//------------------------------------------------------------------------------

Tuple List::operator[](int idx) const {

  if (idx >= 0)
    return front[idx];
  else
    return front[num + idx];
}

//------------------------------------------------------------------------------

Tuple List::getTup (int idx) const {

  if (idx >= 0)
    return front[idx];
  else
    return front[num + idx];
  
}

//------------------------------------------------------------------------------

Tuple List::sum(void) const {
  
  Tuple tsum(0,0);

  for (int i(0);i<num;i++)
    tsum += front[i];

  return tsum;
}

//------------------------------------------------------------------------------

Tuple List::product(void) const {
  
  Tuple pro(1,1);

  for (int i(0);i<num;i++)
    pro *= front[i];

  return pro;
}

//------------------------------------------------------------------------------

void List::add(const Tuple& tup) {
  
  int newNum(num+1);
  Tuple* h = new Tuple[newNum];

  for (int i(0);i<num;i++)
    h[i] = front[i];

  delete[] front;
  h[newNum-1] = tup;
  front = h;
  num = newNum;
}

//------------------------------------------------------------------------------

void List::fradd(const Tuple& tup) {
  
  int newNum(num+1);
  Tuple* h = new Tuple[newNum];
  h[0] = tup;

  for (int i(1);i<newNum;i++)
    h[i] = front[i];

  delete[] front;
  front = h;
  num = newNum;
}

//------------------------------------------------------------------------------

void List::append(const List& lis) {

  if (!lis.num)
    return;
  
  int newNum(num + lis.num);
  Tuple* h = new Tuple[newNum];

  for (int i(0);i<num;i++)
    h[i] = front[i];

  delete[] front;

  for (int j(num);j<newNum;j++)
    h[j] = lis[j-num];

  front = h;
  num = newNum;
}

//------------------------------------------------------------------------------

void List::frappend(const List& lis) {
  
  int newNum(num + lis.num);
  Tuple* h = new Tuple[newNum];

  for (int i(0);i<lis.num;i++)
    h[i] = lis[i];

  for (int j(lis.num);j<newNum;j++)
    h[j] = front[j-lis.num];

  delete[] front;
  front = h;
  num = newNum;
}

//------------------------------------------------------------------------------

void List::insert(const Tuple& tup,int index) {

  if (index < 0)
    index += num;
  
  int newNum(num + 1);
  Tuple* h = new Tuple[newNum];
  h[index] = tup;

  for (int i(0);i<index;i++)
    h[i] = this->operator[](i);

  for (int j(index+1);j<newNum;j++)
    h[j] = this->operator[](j - 1);

  delete[] front;
  front = h;
  num = newNum;
}

//------------------------------------------------------------------------------

void List::remove(int idx) {
  
  int newNum(num - 1);
  Tuple* h = new Tuple[newNum];
  int i(0),j(0);

  do {
    if (i == idx)
      ++j;
    
    h[i] = this->operator[](j);
    ++j;
    ++i;
        
  } while (i < newNum);

  delete[] front;
  front = h;
  num = newNum;
}

//------------------------------------------------------------------------------

void List::replace(const Tuple& tup,int idx) {
  
  front[(idx < 0)?num+idx:idx] = tup;
}

//------------------------------------------------------------------------------

void List::reverse(void) {
  
  if (num == 1)
    return;
  
  Tuple* h = new Tuple[num];

  for (int i(0);i<num;i++)
    h[i] = this->operator[](-(i + 1));

  delete[] front;
  front = h;
}

//------------------------------------------------------------------------------

bool List::contains(const Tuple& tup) const {
  
  for (int i(0);i<num;i++)
    if (front[i] == tup)
      return true;

  return false;
}

//------------------------------------------------------------------------------

int List::occurs(const Tuple& tup) const {
  
  if (!this->contains(tup))
    return 0;
  
  int counter(0);

  for (int i(0);i<num;i++)
    if (front[i] == tup)
      ++counter;;

  return counter;
}

//------------------------------------------------------------------------------

int List::elements(void) const {
  return num;
}

//------------------------------------------------------------------------------

List List::operator+(const List& lis) const {

  Tuple* h = new Tuple[num];

  for (int i(0);i<num;i++)
    h[i] = front[i] + lis[i];

  return List(h,num);
}

//------------------------------------------------------------------------------

List List::operator*(const List& lis) const {

  Tuple* h = new Tuple[num];

  for (int i(0);i<num;i++)
    h[i] = front[i] * lis[i];

  return List(h,num);
}

//------------------------------------------------------------------------------

void List::operator=(const List& lis) {
  
  num = lis.num;

  delete[] front;

  front = new Tuple[num];
  for (int a (0);a<num;a++)
    front[a] = lis[a];
  
}

//------------------------------------------------------------------------------

void List::operator+=(const List& lis) {
  
  List tmp = this->operator+(lis);

  delete[] front;

  front = tmp.front;
}


//------------------------------------------------------------------------------

void List::operator*=(const List& lis) {
  
  List tmp = this->operator*(lis);

  delete[] front;

  front = tmp.front;
}
