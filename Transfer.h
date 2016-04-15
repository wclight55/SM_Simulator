//---------------------------------------------------------------------------

#ifndef TransferH
#define TransferH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <ImgList.hpp>
#include "dxBar.hpp"
#include "dxBarExtItems.hpp"
#include "NodeEvent.h"
#include "UIProject.h"
#include "SelectRect.h"
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include "ReasonMachine.h"
#include <vector>
#include <iostream>
#include <fstream>

//extern UIProject*g_pProject_new;
//extern PACKAGE int __fastcall FileOpen(const AnsiString Filename, int Mode);
//extern PACKAGE int __fastcall FileClose(int Handle);
//extern PACKAGE int __fastcall FileCreate(const AnsiString Filename);
//extern PACKAGE int __fastcall FileWrite(int Handle,const void *Buffer,unsigned Count);
//extern PACKAGE int __fastcall FileRead(int Handle,const void *Buffer,unsigned Count);

//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label2;
        TLabel *Label4;
        TListBox *ListBox1;
        TListBox *ListBox2;
        TListBox *ListBox3;
        TButton *Button3;
        TButton *Button4;
        TButton *Button2;
        TOpenDialog *OpenDialog;
        TXMLDocument *XMLDoc;
        TPanel *Panel1;
        TPaintBox *PaintBox1;
        TListBox *ListBox4;
        TLabel *Label3;
        TLabel *Label5;
        TLabel *Label6;
        TListBox *ListBox7;
        TLabel *Label7;
        TListBox *ListBox5;
        void __fastcall Button4Click(TObject *Sender);
        //void __fastcall FormCreate(TObject *Sender);
        //void __fastcall FormDestroy(TObject *Sender);
        void __fastcall TForm1BoxPaint(TObject *Sender);
        void __fastcall PanelPaintResize(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);

private:	// User declarations
        Graphics::TBitmap *bmp_new;
        //Boolean m_bMouseMove;
        POINT   p_start,p_end;
        int m_nFramePropertyWidth,m_nFrameOutputHeight;
        ReasonMachine*m_pReasonMachine;
public:		// User declarations
        void __fastcall PrintPage(int page);
        void InitialProject();
        void ClearProject();
        void Refresh();
        void CreatDismap(); //创建邻接表
        void floyd(vector<vector<double> > &distmap, vector<vector<int> > &path);
        void print(const int &beg,const int &end,const vector<vector<int> > &path);
        __fastcall TForm1(TComponent* Owner);
        virtual __fastcall ~TForm1();
        long LoadFromXML(AnsiString fileName);
        TSelectRect* m_selectRect;
        Boolean m_bEditCanvas;
        //Simulator*m_pSimulator;
        Graphics::TBitmap* graphic_new;
        int beg;
        int end;
        String s;
        String s1;
        FCMsNode* f;
        FCMsNode* f1;
        FCMsNode* f2;
        bool flag;
        bool flag1;
        AnsiString r;
        vector<vector<int> > path;//记录最短路径
        vector<vector<double> > distmap;//邻接矩阵
        //bool m_bSendingData;
        //bool flag;
        //bool fofrtt;
        //int DatabaseSelected;
        //int num;
       // void __fastcall AppException(TObject * Sender, Exception * E);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
