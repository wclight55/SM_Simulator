//Header:	Array.hpp
//Version:	1.0
//Language:	Borland C++ 3.1
//Envion:	Any
//Date:		10/1995
//Purpose:	Privide a base class for array

#ifndef		__ARRAY_HPP
#define		__ARRAY_HPP

#include <alloc.h>

enum ARRAYErrAttr { NO_ERR, OUT_RANGE, MEM_ALLOC, IIG_METHOD };

class Array
{
  protected:
    long Min;		//minium number of array member
    long Max;		//maxmum number of array member
    unsigned int Long;	//array long allowed
    void *Elem;		//pointer to element of array
    size_t ElemSize;	//size of each element
    unsigned long AllSize;	//size of all array
    void (*ErrHandler)(ARRAYErrAttr ms);	//error handler for user
    //error set method
    ARRAYErrAttr ErrSet(ARRAYErrAttr er);
    //buffer allocation method
    void BufAlloc();
    //other methods
    void Copy(Array &a);
    void Kill();
  public:
    ARRAYErrAttr ErrAttr;	//error attribut
    //constructor
    Array(long min, long max, size_t es);
    Array(Array &a);
    //deconstructor
    ~Array();
    //other method
    Array& operator = (Array&);
    int GetMin() { return Min; };
    int GetMax() { return Max; };
    unsigned int GetLong() { return Long; };
    //error handler set method
    void SetErrHandler(void (*userHandler)(ARRAYErrAttr ms)) { ErrHandler=userHandler; };
};

#endif