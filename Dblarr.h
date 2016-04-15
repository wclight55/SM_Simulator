//Header:     DblArr.h
//Version:    1.0
//Language:   Borland C++ 3.1
//Envion:     Any
//Date:       10/1995
//Purpose:    Provide a class for double array

#ifndef              __DBLARRAY_H
#define              __DBLARRAY_H

#include "Array.h"
#include <iostream.h>

class DblArray : public Array
{
  protected:
    double *Work;           //work pointer of double
  public:
    //constructor
    DblArray(int min, int max, double value=0);
    DblArray(DblArray &da):Array(da){};
    //destructor
    ~DblArray() { Array::~Array(); };
    //operator methods
    void operator = (DblArray &da);
    void operator = (double*);
    DblArray operator + (DblArray &da);
    DblArray operator - (DblArray &da);
    DblArray operator * (DblArray &da);
    DblArray operator / (DblArray &da);
    DblArray& operator += (DblArray&);
    DblArray& operator -= (DblArray&);
    DblArray& operator *= (DblArray&);
    DblArray& operator /= (DblArray&);
    unsigned int operator == (DblArray&);
    unsigned int operator != (DblArray&);
    operator double* () { return (double*)Elem; };
    DblArray operator + ();
    DblArray operator - ();
    friend DblArray operator + (DblArray&, double&);
    friend DblArray operator + (double&, DblArray&);
    friend DblArray operator - (DblArray&, double&);
    friend DblArray operator * (DblArray&, double&);
    friend DblArray operator * (double&, DblArray&);
    friend DblArray operator / (DblArray&, double&);
    DblArray& operator += (double&);
    DblArray& operator -= (double&);
    DblArray& operator *= (double&);
    DblArray& operator /= (double&);
    double& operator [] (int pos);
    friend ostream& operator << (ostream &os, DblArray &da);
    friend istream& operator >> (istream &is, DblArray &da);
};

#endif
