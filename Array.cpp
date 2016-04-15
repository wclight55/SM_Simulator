//Header:	Array.h
//Version:	1.0
//Language:	Borland C++ 3.1
//Envion:	Any
//Date:		10/1995
//Purpose:	Privide a base class for array

#include "array.h"
#include <iostream.h>
#include <memory.h>
#include <process.h>

//default error message out function
void DefaultErr(ARRAYErrAttr);
void DefaultErr(ARRAYErrAttr ms)
{
  switch(ms)
  {
    case OUT_RANGE:	cout<<"\nClass Array: array member out of range!\n";
			break;
    case MEM_ALLOC:	cout<<"\nClass Array: memory allocation failure!\n";
			break;
    case IIG_METHOD:	cout<<"\nClass Array: mistake in method use!\n";
			break;
    default:	;
  }
  exit(1);
}
//constructor
Array::Array(long min, long max, size_t es)
{
  Min = min;
  Max = max;
  ErrHandler = DefaultErr;
  Elem = NULL;
  Long = Max-Min+1;
  ElemSize = es;
  AllSize = es*Long;
  BufAlloc();
}
Array::Array(Array &a)
{
  Copy(a);
}
//destructor
Array::~Array()
{
  Kill();
}
//other methods
Array& Array::operator = (Array &a)
{
  Kill();
  Copy(a);
  return *this;
}
void Array::Copy(Array &a)
{
  Min = a.Min;
  Max = a.Max;
  ErrHandler = a.ErrHandler;
  Long = a.Long;
  ElemSize = a.ElemSize;
  AllSize = a.AllSize;
  BufAlloc();
  memcpy(Elem,a.Elem,AllSize);
}
void Array::Kill()
{
  delete Elem;
  Elem = NULL;
}
//error set method
ARRAYErrAttr Array::ErrSet(ARRAYErrAttr er)
{
  ErrAttr = er;
  if(ErrHandler != NULL) ErrHandler(er);
  return ErrAttr;
}
//buffer allocation method
void Array::BufAlloc()
{
  Elem = new char[AllSize];
  if(Elem == NULL)
    ErrSet(MEM_ALLOC);
}