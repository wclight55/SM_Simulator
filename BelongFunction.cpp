//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <math.h>
#include "BelongFunction.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Tfrm_BelongFunction *frm_BelongFunction;
//---------------------------------------------------------------------------
__fastcall Tfrm_BelongFunction::Tfrm_BelongFunction(TComponent* Owner)
        : TForm(Owner)
{
        bmp = new Graphics::TBitmap();
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
void Tfrm_BelongFunction::Initial()
{
        st_function->RowCount =2;

}




void __fastcall Tfrm_BelongFunction::st_functionDblClick(TObject *Sender)
{
    int row,col;double tem,temp1;AnsiString tem1;
    row = st_function->Row;
    col = st_function->Col;
    if(row==1)
    {
        switch(col)
        {
        case 0:
        {
          tem1=InputBox("Set up function","Input funtion expression please",st_function->Cells[0][row]);
          //if(IsValidExpress(tem1))
          {
            st_function->Cells[0][row]=tem1;
          }
          break;
        }
  }
        AnsiString str = "["+st_function->Cells[1][row]+","+st_function->Cells[2][row]+"]";
        m_strExpress=st_function->Cells[0][row];
        m_strFunc=m_strExpress+str;
    }
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_BelongFunction::FormShow(TObject *Sender)
{
    st_function->Cells[0][0]="Function expression";
    st_function->Cells[1][0]="Floor level";
    st_function->Cells[2][0]="Roof Level";
    Initial();

    RefreshChart();

}
//---------------------------------------------------------------------------
void Tfrm_BelongFunction::FillStringGrid(int row)
{
    st_function->RowCount=2;
    st_function->Cells[0][1]=  m_strExpress;
    st_function->Cells[1][1]=-10;
    st_function->Cells[2][1]=10;
}


void __fastcall Tfrm_BelongFunction::sp_refreshClick(TObject *Sender)
{
    RefreshChart();
}

void Tfrm_BelongFunction::DrawGrid(TCanvas*m_canvas,TRect&m_rect)
{
   TPenStyle style = m_canvas->Pen->Style;
   TColor color =  m_canvas->Pen->Color;
   m_canvas->Pen->Style = psDot;
   m_canvas->Pen->Color =clDkGray;
   int sizegrid = 30;
   M=0;
   for(double i=m_rect.Left;i<=(int)(m_rect.Right);i=i+sizegrid)
   {
       m_canvas->MoveTo(i,m_rect.Top);
       m_canvas->LineTo(i,m_rect.Bottom);
       M++;
   }
   M--;
   int k=0;
   for(double i=m_rect.Bottom;i>=(int)(m_rect.Top);i=i-sizegrid)
   {
       m_canvas->MoveTo(m_rect.Left,i);
       m_canvas->LineTo(m_rect.Right,i);
       double zz = k*0.25;
       AnsiString str;
       str = FloatToStr(zz);
       m_canvas->TextOutA(m_rect.Left-20,i-5,str);
       k++;
   }
   m_canvas->Pen->Style = style;
   m_canvas->Pen->Color = color;
//plot
   m_canvas->MoveTo(m_rect.Left,m_rect.Bottom);
   m_canvas->LineTo(m_rect.Right,m_rect.Bottom);

   TPoint p[3];double alfa,sina,cosa;double arrowsize1,arrowsize2;
   alfa=atan(0);
   sina=sin(alfa);
   cosa=cos(alfa);
   arrowsize1=((double)10);
   arrowsize2=((double)4);
   {  p[0]=Point((double)m_rect.Right-arrowsize1*cosa+arrowsize2*sina,
                 (double)m_rect.Bottom-arrowsize1*sina-arrowsize2*cosa);
      p[1]=Point(m_rect.Right,m_rect.Bottom);
      p[2]=Point((double)m_rect.Right-arrowsize1*cosa-arrowsize2*sina,
                 (double)m_rect.Bottom-arrowsize1*sina+arrowsize2*cosa);
   }
   m_canvas->Polygon(p,2);

   m_canvas->MoveTo(m_rect.Left,m_rect.Bottom);
   m_canvas->LineTo(m_rect.Left,m_rect.Top);
   alfa=-3.14159265/2;
   sina=sin(alfa);
   cosa=cos(alfa);
   arrowsize1=((double)10);
   arrowsize2=((double)4);
   {  p[0]=Point((double)m_rect.Left-arrowsize1*cosa+arrowsize2*sina,
                 (double)m_rect.Top-arrowsize1*sina-arrowsize2*cosa);
      p[1]=Point(m_rect.Left,m_rect.Top);
      p[2]=Point((double)m_rect.Left-arrowsize1*cosa-arrowsize2*sina,
                 (double)m_rect.Top-arrowsize1*sina+arrowsize2*cosa);
   }
   m_canvas->Polygon(p,2);
}
void Tfrm_BelongFunction::DrawFunction(TCanvas*m_canvas,TRect&m_rect)
{
   TPenStyle style = m_canvas->Pen->Style;
   TColor color =  m_canvas->Pen->Color;
   m_canvas->Pen->Style = psSolid;
   m_canvas->Pen->Color =clBlue;


   if(begin==end)
     return;
   AnsiString str = m_strExpress+"[-10,10]";
   DrawFunction(m_canvas,m_rect,str);
//////////////////////////////

//
   int sizegrid = 30;
   double dis = (end-begin)/M;
   for(double i=0;i<=M;i++)
   {
       AnsiString str;
       str = FloatToStr(begin+dis*i);
       str = str.FormatFloat("0.00",begin+dis*i);
       m_canvas->TextOutA(m_rect.Left+i*sizegrid-5,m_rect.Bottom+5,str);
   }

   m_canvas->Pen->Style = style;
   m_canvas->Pen->Color = color;

}
POINT Tfrm_BelongFunction::ToScreen(double x,double y)
{
      int sizegrid = 30;
      int Y = charrect.Bottom - 4*sizegrid*y;

      double b = charrect.Left - (begin*M*sizegrid)/(end-begin);
      double k= M*sizegrid/(end-begin);
      int X = x*k+b;
      POINT p;
      p.x = X;
      p.y = Y;
      return p;
}
void Tfrm_BelongFunction::DrawFunction(TCanvas*m_canvas,TRect&m_rect,AnsiString exp)
{
   double U = 10;
   double D = -10;
   AnsiString str =  m_strExpress;
   double dis = (U-D)/100;
    AnsiString tmp_str = FloatToStr(D);
    int s=0;
   // GetExpressValue("X="+tmp_str,s);

   double py = 1;//GetExpressValue(str,s);
   double px = D;
   POINT pt = ToScreen(px,py);
   m_canvas->MoveTo(pt.x,pt.y);
   for(int i=0;i<=100;i++)
   {
      tmp_str = FloatToStr(D+dis*i);
      s=0;
      //GetExpressValue("X="+tmp_str,s);
      py = 1;//GetExpressValue(str,s);
      px = D+dis*i;
      pt = ToScreen(px,py);
      m_canvas->LineTo(pt.x,pt.y);
   }
}

//---------------------------------------------------------------------------
void Tfrm_BelongFunction::RefreshChart()
{
     bmp->Canvas->Brush->Color = clWhite;
     bmp->Canvas->FillRect(pb_function->ClientRect);

     bmp->Canvas->CopyMode= cmSrcCopy;
     TRect rect;
     rect.Left  = pb_function->ClientRect.Left+25;
     rect.Right  = pb_function->ClientRect.Right-10;
     rect.Top  = pb_function->ClientRect.Top+10;
     rect.Bottom  = pb_function->ClientRect.Bottom-20;

     charrect = rect;
 
     DrawGrid(bmp->Canvas,rect);
     DrawFunction(bmp->Canvas,rect);
     pb_function->Canvas->CopyRect(pb_function->ClientRect,bmp->Canvas,pb_function->ClientRect);
}
//---------------------------------------------------------------------------

void __fastcall Tfrm_BelongFunction::FormResize(TObject *Sender)
{
     bmp->Width=pb_function->Width;
     bmp->Height=pb_function->Height;
}
//---------------------------------------------------------------------------


void __fastcall Tfrm_BelongFunction::pb_functionPaint(TObject *Sender)
{
         RefreshChart();
}
//---------------------------------------------------------------------------



void __fastcall Tfrm_BelongFunction::sb_closeClick(TObject *Sender)
{
     Close();
}
//---------------------------------------------------------------------------



