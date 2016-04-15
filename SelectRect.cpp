#include "SelectRect.h"

TSelectRect::TSelectRect()
{
   style = psDot;
   color = clBlack;
   width = 1;

   proportion = 1;
   XOrientation = 0;
   YOrientation = 0;

   left   = 0;
   top    = 0;
   right  = 0;
   bottom = 0;
}

void TSelectRect::OnDraw(TCanvas*m_canvas,TPenMode mode)
{
//
  TPenStyle bs= m_canvas->Pen->Style;
  TColor cl= m_canvas->Pen->Color;
  TPenMode pm = m_canvas->Pen->Mode;
  int b = m_canvas->Pen->Width;
//
  m_canvas->Pen->Mode = mode;
  m_canvas->Pen->Style = style;
  m_canvas->Pen->Color = color;
  m_canvas->Pen->Width = width;

  long x1,y1;
  x1 = (left - XOrientation)*proportion;
  y1 = (top - YOrientation)*proportion;

  m_canvas->MoveTo(x1,y1);
  m_canvas->LineTo(x1,y1+Height()*proportion);
  m_canvas->LineTo(x1+Width()*proportion,y1+Height()*proportion);
  m_canvas->LineTo(x1+Width()*proportion,y1);
  m_canvas->LineTo(x1,y1);

  m_canvas->Pen->Style = bs;
  m_canvas->Pen->Color = cl;
  m_canvas->Pen->Width = b;
  m_canvas->Pen->Mode = pm;

}

void TSelectRect::SetPosition(int m_left,int m_top)
{
   left=m_left;
   top=m_top;
}
void TSelectRect::SetMouseDPosition(int m_left,int m_top)
{
  d0_x = m_left;
  d0_y = m_top;
}
void TSelectRect::SetMouseMPosition(int m_left,int m_top)
{
  d1_x = m_left;
  d1_y = m_top;
}
void TSelectRect::MoveRelatedMouse(int m_left,int m_top)
{
  SetMouseMPosition(m_left,m_top);
  left = left+d1_x-d0_x;
  top = top+d1_y-d0_y;
}
void TSelectRect::SetRect(long start_x,long start_y,long end_x,long end_y)
{
    left   = start_x<=end_x ? start_x:end_x;
    top    = start_y<=end_y ? start_y:end_y;
    right  = start_x>=end_x ? start_x:end_x;
    bottom = start_y>=end_y ? start_y:end_y;
}
//////////
Boolean TSelectRect::Resize(double p)
{  if (p>0)
   {  proportion = p;
      return true;
   }
   else return false;
}
Boolean TSelectRect::SetOrientation(long x0,long y0)
{  XOrientation = x0;YOrientation = y0;
   return true;
}

