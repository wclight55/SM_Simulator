//Header:       Matrix.hpp
//Version:      1.0
//Language:     Borland C++ 3.1
//Environ:      Any
//Date:         10/1995~3/1996
//Purpose:      Provide a base class for matrix

#include "matrix.h"
#include <iomanip.h>
//extern "C"
  //{
  #include <process.h>
  #include <math.h>
  //}

//default error handler
void DefaultErr(MtErrType);
void DefaultErr(MtErrType et)
{
  cout<<MtErrMsg[et];
  exit(1);
}
MtErrType Matrix::ErrSet(MtErrType et)
{
  if(ErrHandler != NULL)
    ErrHandler(et);
  return et;
}
//constructor
Matrix::Matrix(int row, int col, double fill)
{
  DataWitch = 0;
  DataPrec = 0;
  RowMax = row;
  ColMax = col;
  ErrHandler = DefaultErr;
  if((Row=new DblArray* [RowMax]) == NULL)
    ErrSet(MT_MEM_ALLOC);
  for(int i=0; i<RowMax; i++)
    if((Row[i]=new DblArray(1, ColMax, fill)) == NULL)
      ErrSet(MT_MEM_ALLOC);
}
Matrix::Matrix(Matrix &s)
{
  Copy(s);
}
//destructor
Matrix::~Matrix()
{
  Kill();
}
//private copy and kill method
void Matrix::Copy(Matrix &s)
{
  RowMax = s.RowMax;
  ColMax = s.ColMax;
  ErrHandler = s.ErrHandler;
  if((Row=new DblArray* [RowMax]) == NULL)
    ErrSet(MT_MEM_ALLOC);
  for(int i=0; i<RowMax; i++)
    if((Row[i]=new DblArray(*s.Row[i])) == NULL)
      ErrSet(MT_MEM_ALLOC);
}
void Matrix::Duplicate(Matrix&s)
{
  if(RowMax!=s.RowMax || ColMax!=s.ColMax)
  {
    ErrSet(MT_ILL_METHOD);
    return ;
  }
   for(int i=0; i<RowMax; i++)
    for(int j=0;j<ColMax;j++)
    {
      (*this)(i+1,j+1)=s(i+1,j+1);
    }
}
void Matrix::Kill()
{
  if(Row==NULL) return;
  for(int i=0; i<RowMax; i++)
    if(Row[i]!=NULL)
      delete Row[i];
  delete Row;
  Row = NULL;
}
//operator methods
Matrix& Matrix::operator = (Matrix &s)
{
  Kill();
  Copy(s);
  return *this;
}
Matrix Matrix::operator + (Matrix &s)
{
  if(RowMax!=s.RowMax || ColMax!=s.ColMax)
  {
    ErrSet(MT_ILL_METHOD);
    return *this;
  }
  Matrix tmp(*this);
  for(int i=0; i<tmp.RowMax; i++)
    *tmp.Row[i] += *s.Row[i];
  return tmp;
}
bool Matrix::operator == (Matrix&s)
{
  if(RowMax!=s.RowMax || ColMax!=s.ColMax)
  {
    return false;
  }
  for(int i=0; i<RowMax; i++)
    for(int j=0; j<ColMax; j++)
    {
      if((*this)(i+1,j+1)!=s(i+1,j+1))
          return false;
    }
  return true;
}
Matrix Matrix::operator - (Matrix &s)
{
  if(RowMax!=s.RowMax || ColMax!=s.ColMax)
  {
    ErrSet(MT_ILL_METHOD);
    return *this;
  }
  Matrix tmp(*this);
  for(int i=0; i<RowMax; i++)
    *tmp.Row[i] -= *s.Row[i];
  return tmp;
}
Matrix Matrix::operator * (Matrix &s)
{
  if(ColMax!=s.RowMax)
  {
    ErrSet(MT_ILL_METHOD);
    return *this;
  }
  Matrix tmp(RowMax, s.ColMax);
  for(int row=1; row<=RowMax; row++)
    for(int col=1; col<=s.ColMax; col++)
      for(int count=1; count<=ColMax; count++)
	tmp(row,col)=tmp(row,col)+(*this)(row,count)*s(count,col);
  return tmp;
}
Matrix Matrix::operator + ()
{
  return *this;
}
Matrix Matrix::operator - ()
{
  Matrix tmp(*this);
  Matrix *dd=new Matrix(RowMax,ColMax,-1);
  tmp =(*dd);
  delete dd;
  return tmp;
}
Matrix operator * (Matrix &m, double d)
{
  Matrix tmp(m);
  for(int i=0; i<m.RowMax; i++)
    *tmp.Row[i] *= d;
  return tmp;
}
ostream& operator << (ostream &os, Matrix &s)
{
  os<<"\n";
  unsigned int l = s.Row[0]->GetLong();
  for(int i=0; i<s.RowMax; i++)
  {
    double *value = (double*)*s.Row[i];
    for(unsigned int j=0; j<l; j++)
    {
      os<<" ";
      if(s.DataWitch != 0) os<<setw(s.DataWitch);
	  if(s.DataPrec != 0) os<<setprecision(s.DataPrec);
      os<<*(value+j);
    }
    os<<"\n";
  }
  return os;
}
istream& operator >> (istream &is, Matrix &s)
{
  for(int i=0; i<s.RowMax; i++)
    is>>*s.Row[i];
  return is;
}
double& Matrix::operator ()(int row, int col)
{
  if(col<1 || col>ColMax || row<1 || row>RowMax)
  {
    ErrSet(MT_ILL_METHOD);
    return (*(Row[1]))[1];
  }
  return (*(Row[row-1]))[col];
}
//other methods
double Matrix::DefA(void)
{
  double Result=0;
  if(ColMax!=RowMax || ColMax<1)
  {
    ErrSet(MT_ILL_METHOD);
    return 0;
  }
  if(ColMax == 1)
    return (*this)(1,1);
  for(int i=1; i<=RowMax; i++)
    Result += this->SubA(1,i)*(*this)(1,i);
  return Result;
}
double Matrix::SubA(int i, int j)
{
  Matrix tmp(RowMax-1,ColMax-1);
  int trow=1;
  for(int row=1; row<=RowMax-1; row++)
  {
    int tcol=1;
    if(trow == i) trow++;
    for(int col=1; col<=ColMax-1; col++)
    {
      if(tcol == j) tcol++;
      tmp(row,col) = (*this)(trow,tcol);
      tcol++;
    }
    trow++;
  }
  return tmp.DefA()*pow(-1,i+j);
}
Matrix Matrix::T(void)
{
  Matrix tmp(ColMax,RowMax);
  for(int row=1; row<=RowMax; row++)
    for(int col=1; col<=ColMax; col++)
      tmp(col,row)=(*this)(row,col);
  return tmp;
}
Matrix Matrix::Reverse(void)
{
  if(ColMax != RowMax)
  {
    ErrSet(MT_ILL_METHOD);
    return *this;
  }
  if(this->DefA() == 0)
  {
    ErrSet(MT_ILL_METHOD);
    return *this;
  }
  Matrix Result(RowMax,ColMax);
  for(int row=1; row<=RowMax; row++)
    for(int col=1; col<=ColMax; col++)
      Result(row,col) = this->SubA(col,row);
  return Result/this->DefA();
}
