//---------------------------------------------------------------------------

#ifndef CreatPatternH
#define CreatPatternH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>

#include "NodeEvent.h"
//---------------------------------------------------------------------------
class TForm2 : public TForm
{
__published:	// IDE-managed Components
        TListBox *ListBox1;
        TListBox *ListBox2;
        TListBox *ListBox3;
        TLabel *Label5;
        TLabel *Label6;
        TLabel *Label3;
        TButton *Button3;
        TButton *Button1;
        TListBox *ListBox4;
        TLabel *Label1;
        void __fastcall FormCreate(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm2(TComponent* Owner);
        AnsiString r;
        AnsiString t; //记录随机产生的持续触发时间
         int beg;
        int end;
        String s;
        String s1;
        FCMsNode* f;
        FCMsNode* f1;

        vector<vector<int> > path;//记录最短路径
        vector<vector<double> > distmap;//邻接矩阵
        void CreatDismap();
        void CreatLabels();
        void floyd(vector<vector<double> > &distmap,vector<vector<int> > &path);
        void print(const int &beg,const int &end,const vector<vector<int> > &path);

        TStringList *mytxt;
};
//---------------------------------------------------------------------------
extern PACKAGE TForm2 *Form2;
//---------------------------------------------------------------------------
#endif
