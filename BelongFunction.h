//---------------------------------------------------------------------------

#ifndef BelongFunctionH
#define BelongFunctionH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Buttons.hpp>
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include <ImgList.hpp>
#include <Grids.hpp>
#include "nodeevent.h"

//---------------------------------------------------------------------------

class Tfrm_BelongFunction : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel4;
        TPanel *Panel5;
        TPanel *Panel6;
        TSpeedButton *sp_refresh;
        TPaintBox *pb_function;
        TStringGrid *st_function;
        TSpeedButton *sb_close;
        TStaticText *StaticText1;
        void __fastcall st_functionDblClick(TObject *Sender);
        void __fastcall FormShow(TObject *Sender);
        void __fastcall sp_refreshClick(TObject *Sender);
        void __fastcall FormResize(TObject *Sender);
        void __fastcall pb_functionPaint(TObject *Sender);
        void __fastcall sb_closeClick(TObject *Sender);
private:	// User declarations
        void RefreshChart();
        void Initial();
        void FillStringGrid(int row);
        void DrawGrid(TCanvas*m_canvas,TRect&m_rect);
        Graphics::TBitmap *bmp;

        void DrawFunction(TCanvas*m_canvas,TRect&m_rect);
        void DrawFunction(TCanvas*m_canvas,TRect&m_rect,AnsiString exp);        
        POINT ToScreen(double x,double y);

        double begin;
        double end;
        TRect charrect;
        int M;//      
public:		// User declarations
        __fastcall Tfrm_BelongFunction(TComponent* Owner);
        AnsiString m_strExpress;
        AnsiString m_strFunc;
};
//---------------------------------------------------------------------------
extern PACKAGE Tfrm_BelongFunction *frm_BelongFunction;
//---------------------------------------------------------------------------
#endif
