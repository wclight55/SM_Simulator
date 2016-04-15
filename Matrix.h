//Header:	Matrix.h
//Version:	1.0
//Language:	Borland C++ 3.1
//Environ:	Any
//Date:		10/1995~3/1996
//Purpose:	Provide a base class for matrix

#ifndef		__MATRIX__H
#define		__MATRIX__H

#include "dblarr.h"
#include <iostream.h>

enum MtErrType { MT_MEM_ALLOC, MT_ILL_METHOD };

static char *MtErrMsg[] = { "\nClass Matrix: memory allocation failure!\n",
			    "\nClass Matrix: invalid methods being used!\n"
			  };

class Matrix
{
  protected:
    int ColMax;		//maximum number of columns
    int RowMax;		//maximum number of rows
    DblArray **Row;	//array for each row of double array
    int DataWitch;	//data witch of output to stream
	int DataPrec;	//data precision of output to stream
    void Copy(Matrix&);
    void Kill();
    //error process method
    MtErrType ErrSet(MtErrType);
    void (*ErrHandler)(MtErrType);
  public:
    //constructor
    Matrix(){ ColMax=0;RowMax=0;Row=NULL; DataWitch=0; };
    Matrix(int row, int col, double fill=0);
    Matrix(Matrix&);
    //destructor
    ~Matrix();
    //operator methods
    Matrix& operator = (Matrix&);
    bool operator == (Matrix&);
    Matrix operator + (Matrix&);
    Matrix operator - (Matrix&);
    Matrix operator * (Matrix&);
    Matrix operator + ();
    Matrix operator - ();
    Matrix operator / (double d) { return (*this)*(1/d); };
    double& operator () (int, int);
    friend Matrix operator * (Matrix&, double);
    friend ostream& operator << (ostream&, Matrix&);
    friend istream& operator >> (istream&, Matrix&);
    //other methods
    int GetRow() { return RowMax; };
    int GetCol() { return ColMax; };
    void SetW(int w) { DataWitch=w; };
    void Duplicate(Matrix&);
	void SetP(int p) { DataPrec=p; };
    double DefA(void);		//get the row-colum equation of matrix
    double SubA(int, int);	//get the sub-row-colum equation of matrix
    Matrix T(void);		//get chang matrix
    Matrix Reverse(void);	//get the reverse matrix
    void SetErrHandler(void (*userHandler)(MtErrType et))
      { ErrHandler=userHandler; };
};

#endif