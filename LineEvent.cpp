//---------------------------------------------------------------------------


#pragma hdrstop
#include <Math.h>
#include <algorithm.h>
#include "LineEvent.h"
const int LinePointLimit=2;
const long g_ItemSize = 20;
const int Sensitivity=3;//
//---------------------------------------------------------------------------

#pragma package(smart_init)
LineEvent::LineEvent()
{
  points=NULL;
}
__fastcall LineEvent::~LineEvent()
{
  if(points!=NULL)
  {
     for(int i=0;i<points->Count;i++)
     {
        INFLEXTION*d=(INFLEXTION*)points->Items[i];
        delete d;
     }
     points->Clear();
     delete points;
  }
}
Boolean LineEvent::CopyNewPoint(POINT p)
{
   if(points==NULL)
   {
      points=new TList;
   }
   if(points->Count<LinePointLimit)
   {
      UnSelectAllPoints();
      INFLEXTION*d=new INFLEXTION;
      d->p=p;
      d->selected=true;
      points->Add(d);
   }
   else
      return false;
   return true;
}
Boolean LineEvent::AddNewPoint(POINT p)
{
   if(points==NULL)
   {
      points=new TList;
   }
   if(points->Count<LinePointLimit)
   {
      UnSelectAllPoints();
      INFLEXTION*d=new INFLEXTION;
      d->p=p;
      d->selected=true;
      points->Insert(m_iSection,d);
   }
   else
      return false;
   return true;
}
void LineEvent::MoveSelectedPoint(POINT p)
{
  if(points!=NULL)
  {
     for(int i=0;i<points->Count;i++)
     {
        INFLEXTION*d=(INFLEXTION*)points->Items[i];
        if(d->selected)
        {
           d->p=p;
           return;
        }
     }
  }

}
void LineEvent::CopyTo(LineEvent*value,Boolean same)
{
  if(points!=NULL)
  {
     for(int i=0;i<points->Count;i++)
     {
        INFLEXTION*d=(INFLEXTION*)points->Items[i];
        if(same)
        {
          POINT p;
          p.x=d->p.x+g_ItemSize;
          p.y=d->p.y+g_ItemSize;
          value->CopyNewPoint(p);
        }
        else
          value->CopyNewPoint(d->p);
     }
  }
}
void LineEvent::SetMouseDPosition(int m_x,int m_y,Boolean single)
{
        d0_x = m_x;
        d0_y = m_y;
        if(single)
          m_bReadyForAddPoint=true;
}
void LineEvent::SetMouseMPosition(int m_x,int m_y,Boolean single)
{
        d1_x = m_x;
        d1_y = m_y;
        if(single)
        {
          if(m_bReadyForAddPoint)
          {
            POINT p;
            p.x=d0_x;
            p.y=d0_y;
            AddNewPoint(p);
            m_bReadyForAddPoint=false;
          }
          POINT p;
          p.x=d1_x;
          p.y=d1_y;
          MoveSelectedPoint(p);
        }
}
void LineEvent::MoveRelatedMouse(int m_x,int m_y)
{
        if(points!=NULL)
        {
           SetMouseMPosition(m_x,m_y,false);
           for(int i=0;i<points->Count;i++)
           {
              INFLEXTION*d=(INFLEXTION*)points->Items[i];
              d->p.x = d->p.x+d1_x-d0_x;
              d->p.y = d->p.y+d1_y-d0_y;
           }
        }
}

void LineEvent::ClearPoints()
{
  if(points!=NULL)
  {
     for(int i=0;i<points->Count;i++)
     {
        INFLEXTION*d=(INFLEXTION*)points->Items[i];
        delete d;
     }
     m_iSection=0;
     points->Clear();
     delete points;
     points=NULL;
  }
}

void LineEvent::SelectPoint(POINT p)
{
   if(points==NULL)return;
   for(int i=0;i<points->Count;i++)
   {
      INFLEXTION*d=(INFLEXTION*)points->Items[i];
      double dis=sqrt((d->p.x-p.x)*(d->p.x-p.x)+(d->p.y-p.y)*(d->p.y-p.y));
      if(dis<Sensitivity)
         d->selected=true;
      else
         d->selected=false;
   }
}

void LineEvent::UnSelectAllPoints()
{
   if(points==NULL)
      return;
   for(int i=0;i<points->Count;i++)
   {
      INFLEXTION*d=(INFLEXTION*)points->Items[i];
      d->selected=false;
   }
}

Boolean LineEvent::IsSelectSection (TRect rect,POINT start,POINT end)
{
   long left   = start.x<=end.x ? start.x:end.x;
   long top    = start.y<=end.y ? start.y:end.y;
   long right  = start.x>=end.x ? start.x:end.x;
   long bottom = start.y>=end.y ? start.y:end.y;
  TPoint points[4];
  points[0].x = left-1;
  points[0].y = top-1;
  points[1].x = left+1;
  points[1].y = top+1;
  points[2].x = right-1;
  points[2].y = bottom+1;
  points[3].x = right+1;
  points[3].y = bottom-1;

 HRGN rgn=CreatePolygonRgn(points,4,ALTERNATE);
 if(RectInRegion(rgn,&rect))
 {
  DeleteObject(rgn);
   m_bSelected=true;
   return true;
 }
  DeleteObject(rgn);
  return false;
}
Boolean LineEvent::IsSelect (TRect rect)
{
   m_bSelected=false;
   POINT start;
   POINT end;
   start.x=s_x;
   start.y=s_y;
   if(points!=NULL)
   {
       for(int i=0;i<points->Count;i++)
       {
          INFLEXTION*d=(INFLEXTION*)points->Items[i];
          end=d->p;
          if(IsSelectSection(rect,start,end))
          {
             m_bSelected=true;
             return true;
          }
          start=end;
       }
   }
   end.x=e_x;
   end.y=e_y;
    if(IsSelectSection(rect,start,end))
    {
       m_bSelected=true;
       return true;
    }
   return false;
}
Boolean LineEvent::IsSelectSection (POINT p,POINT start,POINT end)
{
   m_bSelected=false;
   double d,k,c;
   if (end.x-start.x!=0)
   {  k=((double)(end.y-start.y))/((double)(end.x-start.x));
      c=((double)(end.x*start.y-start.x*end.y))/((double)(end.x-start.x));
      d=fabs((double)p.y-k*(double)p.x-c)/sqrt(1+k*k);
   }
   else
   {  d=fabs(p.x-start.x);
   }
   long max=end.x;
   long may=end.y;
   long mix=start.x;
   long miy=start.y;
   if (d<=Sensitivity)
   {  if (miy>may) swap(miy,may);
      if (mix>max) swap(mix,max);
      if ((p.y-(miy-2))*(p.y-(may+2))>0) return false;
      if ((p.x-(mix-2))*(p.x-(max+2))>0) return false;
      return true;
   }
   return false;

}

Boolean LineEvent::IsSelect (POINT p)
{
   m_bSelected=false;
   POINT start;
   POINT end;
   start.x=s_x;
   start.y=s_y;
   m_iSection=0;
   if(points!=NULL)
   {
       for(int i=0;i<points->Count;i++)
       {
          INFLEXTION*d=(INFLEXTION*)points->Items[i];
          end=d->p;
          if(IsSelectSection(p,start,end))
          {
             SelectPoint(p);
             m_bSelected=true;
             return true;
          }
          m_iSection++;
          start=end;
       }
   }
   end.x=e_x;
   end.y=e_y;
    if(IsSelectSection(p,start,end))
    {
       SelectPoint(p);
       m_bSelected=true;
       return true;
    }
   return false;
}
Boolean LineEvent::SelectTest (POINT p)
{
   double d,k,c;
   if (e_x-s_x!=0)
   {  k=((double)(e_y-s_y))/((double)(e_x-s_x));
      c=((double)(e_x*s_y-s_x*e_y))/((double)(e_x-s_x));
      d=fabs((double)p.y-k*(double)p.x-c)/sqrt(1+k*k);
   }
   else
   {  d=fabs(p.x-s_x);
   }
   long max=e_x;
   long may=e_y;
   long mix=s_x;
   long miy=s_y;
   if (d<=Sensitivity)
   {  if (miy>may) swap(miy,may);
      if (mix>max) swap(mix,max);
      if ((p.y-(miy-2))*(p.y-(may+2))>0) return false;
      if ((p.x-(mix-2))*(p.x-(max+2))>0) return false;
      return true;
   }
	 return false;
}
void LineEvent::Draw (TCanvas* m_canvas)
{
	 TColor cColor;
	 int penWidth;
	 SetLinkEventPosition();
	 cColor = m_LineUI.m_tcLinePenColor;
	 penWidth=m_LineUI.m_iLinePenWidth;

   long s_x1,s_y1,e_x1,e_y1;
   s_x1=((double)(s_x- XOrientation))*proportion;
   s_y1=((double)(s_y- YOrientation))*proportion;
   e_x1=((double)(e_x- XOrientation))*proportion;
   e_y1=((double)(e_y- YOrientation))*proportion;
   TColor pcl = m_canvas->Pen->Color;
   TPenStyle pst = m_canvas->Pen->Style;
 //
    TBrushStyle bs= m_canvas->Brush->Style;
    TColor cl = m_canvas->Brush->Color;
    int ws=  m_canvas->Pen->Width;

   if (m_canvas->Pen->Mode != pmNotXor)
   {
      if (m_bSelected)
      {
           m_canvas->Pen->Color = cColor;
           m_canvas->Pen->Style = psDash ;
           m_canvas->Pen->Width = penWidth;
           m_canvas->MoveTo(s_x1,s_y1);
           long x_1=s_x1;
           long y_1=s_y1;
           if(points!=NULL)
           {
               for(int i=0;i<points->Count;i++)
               {
                   INFLEXTION*d=(INFLEXTION*)points->Items[i];
                   x_1=((double)(d->p.x- XOrientation))*proportion;
                   y_1=((double)(d->p.y- YOrientation))*proportion;
                   m_canvas->LineTo(x_1,y_1);
               }
           }
           m_canvas->LineTo(e_x1,e_y1);
           m_canvas->Brush->Color=cColor;
           m_canvas->Brush->Style = bsSolid;

           if(points!=NULL)
           {
               m_canvas->Brush->Color = clBlack;
               m_canvas->Brush->Style = bsSolid;
               for(int i=0;i<points->Count;i++)
               {
                   INFLEXTION*d=(INFLEXTION*)points->Items[i];
                   x_1=((double)(d->p.x- XOrientation))*proportion;
                   y_1=((double)(d->p.y- YOrientation))*proportion;
                   m_canvas->FillRect(TRect(x_1-2,y_1-2,x_1+2,y_1+2));
               }
               m_canvas->Brush->Color = cl;
           }
      }
      else
      {
           m_canvas->Pen->Color = cColor;
           m_canvas->Pen->Width = penWidth;
         
           m_canvas->MoveTo(s_x1,s_y1);
           long x_1=s_x1;
           long y_1=s_y1;
           if(points!=NULL)
           {
               for(int i=0;i<points->Count;i++)
               {
                  INFLEXTION*d=(INFLEXTION*)points->Items[i];
                  x_1=((double)(d->p.x- XOrientation))*proportion;
                  y_1=((double)(d->p.y- YOrientation))*proportion;
                  m_canvas->LineTo(x_1,y_1);
               }
           }
           m_canvas->LineTo(e_x1,e_y1);


           m_canvas->Brush->Color = cl;
           m_canvas->Brush->Style = bs;
       }
   }

   m_canvas->Brush->Color = cl;
   m_canvas->Brush->Style = bs;
   m_canvas->Pen->Color=pcl;
   m_canvas->Pen->Style=pst;
   m_canvas->Pen->Width=ws;
}
void LineEvent::SetLinkEventPosition()
{

    int d_x;
    int d_y;

    int s_x;
    int s_y;

    TPoint&s = TPoint(0,0);
    TPoint&d = TPoint(0,0);
    
    if(ObjectSource==NULL)return;
    if(ObjectDest==NULL)return;

    s.x = ObjectSource->X;
    s.y = ObjectSource->Y;
    d.x = ObjectDest->X;
    d.y = ObjectDest->Y;
    POINT s1;
    POINT d1;
     if(points!=NULL)
     {
         if(points->Count>0)
         {
            INFLEXTION*d=(INFLEXTION*)points->Items[0];
            s1=ObjectSource->GetPoint(d->p.x,d->p.y);
            d=(INFLEXTION*)points->Items[points->Count-1];
            d1=ObjectDest->GetPoint(d->p.x,d->p.y);
            SetStartEnd(s1,d1);
            return;
         }
     }
    s1=ObjectSource->GetPoint(d.x,d.y);
    d1=ObjectDest->GetPoint(s.x,s.y);
    SetStartEnd(s1,d1);
}
void LineEvent::SetStartEnd(POINT in,POINT out)
{
   s_x = in.x;
   s_y = in.y;
   e_x = out.x;
   e_y = out.y;
}

