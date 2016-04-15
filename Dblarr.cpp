//Header:     DblArr.hpp
//Version:    1.0
//Language:   Borland C++ 3.1
//Envion:     Any
//Date:              10/1995
//Purpose:    Provide a class for double array

#include "dblarr.h"
extern "C"
  {
  #include <stdio.h>
  }

DblArray::DblArray(int min, int max, double value):
	Array(min, max, sizeof(double))
{
  Work = (double*)Elem;
  for(unsigned int i=0; i<Long; i++)
  {
    *Work = value;
    Work++;
  }
}
//operator methods
void DblArray::operator = (DblArray &ia)
{
  Kill();
  Copy(ia);
}
void DblArray::operator = (double *da)
{
  Work = (double*)Elem;
  for(unsigned int i=0; i<Long; i++)
  {
    *Work = *(da+i);
    Work++;
  }
}
DblArray DblArray::operator + (DblArray &ia)
{
  if(Max!=ia.Max || Min!=ia.Min)
  {
    ErrSet(IIG_METHOD);
    return *this;
  }
  DblArray tmp(*this);
  tmp.Work = (double*)tmp.Elem;
  ia.Work = (double*)ia.Elem;
  for(unsigned int i=0; i<tmp.Long; i++)
  {
    *tmp.Work += *ia.Work;
    tmp.Work++;
    ia.Work++;
  }
  return tmp;
}
DblArray& DblArray::operator += (DblArray &ia)
{
  *this = *this + ia;  
  return *this;
}
DblArray DblArray::operator - (DblArray &ia)
{
  if(Max!=ia.Max || Min!=ia.Min)
  {
    ErrSet(IIG_METHOD);
    return *this;
  }
  DblArray tmp(*this);
  tmp.Work = (double*)tmp.Elem;
  ia.Work = (double*)ia.Elem;
  for(unsigned int i=0; i<tmp.Long; i++)
  {
    *tmp.Work -= *ia.Work;
    tmp.Work++;
    ia.Work++;
  }
  return tmp;
}
DblArray& DblArray::operator -= (DblArray &ia)
{
  *this = *this - ia;
  return *this;
}
DblArray DblArray::operator * (DblArray &ia)
{
  if(Max!=ia.Max || Min!=ia.Min)
  {
    ErrSet(IIG_METHOD);
    return *this;
  }
  DblArray tmp(*this);
  tmp.Work = (double*)tmp.Elem;
  ia.Work = (double*)ia.Elem;
  for(unsigned int i=0; i<tmp.Long; i++)
  {
    *tmp.Work *= *ia.Work;
    tmp.Work++;
    ia.Work++;
  }
  return tmp;
}
DblArray& DblArray::operator *= (DblArray &ia)
{
  *this = *this * ia;
  return *this;
}
DblArray DblArray::operator / (DblArray &ia)
{
  if(Max!=ia.Max || Min!=ia.Min)
  {
    ErrSet(IIG_METHOD);
    return *this;
  }
  DblArray tmp(*this);
  tmp.Work = (double*)tmp.Elem;
  ia.Work = (double*)ia.Elem;
  for(unsigned int i=0; i<tmp.Long; i++)
  {
    *tmp.Work /= *ia.Work;
    tmp.Work++;
    ia.Work++;
  }
  return tmp;
}
DblArray& DblArray::operator /= (DblArray &ia)
{
  *this = *this / ia;
  return ia;
}
DblArray DblArray::operator + ()
{
  return *this;
}
DblArray DblArray::operator - ()
{
  DblArray tmp(*this);
  tmp.Work = (double*)tmp.Elem;
  for(double i=0; i<tmp.Long; i++)
  {
    *tmp.Work = -*tmp.Work;
    tmp.Work++;
  }
  return tmp;
}
double& DblArray::operator [](int pos)
{
  Work = (double*)Elem;
  if(pos<Min || pos>Max)
  {
    ErrSet(OUT_RANGE);
    return *Work;
  }
  return *(Work+pos-Min);
}
DblArray operator + (DblArray &a, double &d)
{
  DblArray tmp(a);
  tmp.Work = (double*)tmp.Elem;
  for(unsigned int i=0; i<tmp.Long; i++)
  {
    *tmp.Work += d;
    tmp.Work++;
  }
  return tmp;
}
DblArray operator + (double &d, DblArray &a)
{
  DblArray tmp(a);
  tmp.Work = (double*)tmp.Elem;
  for(unsigned int i=0; i<tmp.Long; i++)
  {
    *tmp.Work += d;
    tmp.Work++;
  }
  return tmp;
}
DblArray operator - (DblArray &a, double &d)
{
  DblArray tmp(a);
  tmp.Work = (double*)tmp.Elem;
  for(unsigned int i=0; i<tmp.Long; i++)
  {
    *tmp.Work -= d;
    tmp.Work++;
  }
  return tmp;
}
DblArray operator * (DblArray &a, double &d)
{
  DblArray tmp(a);
  tmp.Work = (double*)tmp.Elem;
  for(unsigned int i=0; i<tmp.Long; i++)
  {
    *tmp.Work *= d;
    tmp.Work++;
  }
  return tmp;
}
DblArray operator * (double &d, DblArray &a)
{
  DblArray tmp(a);
  tmp.Work = (double*)tmp.Elem;
  for(unsigned int i=0; i<tmp.Long; i++)
  {
    *tmp.Work *= d;
    tmp.Work++;
  }
  return tmp;
}
DblArray operator / (DblArray &a, double &d)
{
  DblArray tmp(a);
  tmp.Work = (double*)tmp.Elem;
  for(unsigned int i=0; i<tmp.Long; i++)
  {
    *tmp.Work /= d;
    tmp.Work++;
  }
  return tmp;
}
DblArray& DblArray::operator += (double &d)
{
  *this = *this + d;
  return *this;
}
DblArray& DblArray::operator -= (double &d)
{
  *this = *this - d;
  return *this;
}
DblArray& DblArray::operator *= (double &d)
{
  *this = *this * d;
  return *this;
}
DblArray& DblArray::operator /= (double &d)
{
  *this = *this / d;
  return *this;
}
ostream& operator << (ostream &os, DblArray &ia)
{
  ia.Work = (double*)ia.Elem;
  for(unsigned int i=0; i<ia.Long; i++)
  {
    os<<*ia.Work<<"  ";
    ia.Work++;
  }
  os<<"\n";
  return os;
}
istream& operator >> (istream &is, DblArray &ia)
{
  ia.Work = (double*)ia.Elem;
  for(unsigned int i=0; i<ia.Long; i++)
  {
    is>>*ia.Work;
    ia.Work++;
  }
  return is;
}
unsigned int DblArray::operator == (DblArray &ia)
{
  if(Min!=ia.Min || Max!=ia.Max)
    return 0;
  Work = (double*)Elem;
  ia.Work = (double*)ia.Elem;
  for(unsigned int i=0; i<Long; i++)
  {
    if(*Work != *ia.Work) return 0;
    Work++;
    ia.Work++;
  }
  return 1;
}
unsigned int DblArray::operator != (DblArray &ia)
{
  if(*this == ia)
    return 0;
  else
    return 1;
}
