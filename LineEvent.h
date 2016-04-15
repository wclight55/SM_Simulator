#ifndef LineEventH
#define LineEventH
#include "NodeEvent.h"
//
class BasicGraph;
struct INFLEXTION//¹Õµã
{
  POINT p;//
  Boolean selected;//
};
class LineEvent : public BasicGraph
{
  private:
    Boolean m_bReadyForAddPoint;//
  public:

    TList*points;
    int m_iSection;
	public:
    long m_InID;//
    long m_OutID;//
    NodeEvent*ObjectSource;//
    NodeEvent*ObjectDest;//
    double m_dDistance;//
    int s_x;//
    int s_y;//
    int e_x;//
    int e_y;//
    Boolean m_bType;//
	public:
		LineEvent();
		virtual __fastcall ~LineEvent();
		void Draw (TCanvas* m_canvas);//
		Boolean IsSelect (POINT p);//
		Boolean SelectTest (POINT p);//
		Boolean IsSelect (TRect rect); //

    void SetLinkEventPosition();//
    void SetStartEnd(POINT in,POINT out); //

    Boolean AddNewPoint(POINT p);//
    Boolean CopyNewPoint(POINT p);//
    void UnSelectAllPoints();//
    void SelectPoint(POINT p);//
    void ClearPoints();//
    void MoveSelectedPoint(POINT p);//
    void SetMouseDPosition(int m_x,int m_y,Boolean single);//
    virtual void SetMouseDPosition(int m_x,int m_y){;};//
    void SetMouseMPosition(int m_x,int m_y,Boolean single);//
    virtual void SetMouseMPosition(int m_x,int m_y){;};//
    void MoveRelatedMouse(int m_x,int m_y);//
    void CopyTo(LineEvent*value,Boolean same=true);//
  private:
		Boolean IsSelectSection (POINT p,POINT start,POINT end);
		Boolean IsSelectSection (TRect rect,POINT start,POINT end);

};

#endif
