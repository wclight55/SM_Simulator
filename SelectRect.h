//---------------------------------------------------------------------------
#ifndef SelectClassH
#define SelectClassH
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include <vcl.h>
class TSelectRect
{
private:
   int left;
   int top;
   int right;
   int bottom;

   TColor color;//
   TPenStyle style;//
   int width;//
private:	// User declarations
   int d0_x;//
   int d0_y;//
   int d1_x;//
   int d1_y;//
protected:
   double proportion;
   long XOrientation,YOrientation;
public:		// User declarations
    TSelectRect();
    void Select();

    int Width(){return right-left;}
    int Height(){return bottom-top;}

    void OnDraw(TCanvas*m_canvas,TPenMode mode);

/////
    void SetPosition(int m_left,int m_top);
    void SetMouseDPosition(int m_left,int m_top);
    void SetMouseMPosition(int m_left,int m_top);
    void MoveRelatedMouse(int m_left,int m_top);

    void SetRect(long start_x,long start_y,long end_x,long end_y);
    TRect GetRect(){TRect m =TRect(left,top,right,bottom);return m;};
////
    Boolean Resize(double p);
    Boolean SetOrientation(long x0,long y0);
};
//---------------------------------------------------------------------------
#endif

