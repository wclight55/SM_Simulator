//---------------------------------------------------------------------------

#ifndef UnitH
#define UnitH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ADODB.hpp>
#include <DB.hpp>
#include <DBGrids.hpp>
#include <Grids.hpp>
#include <Chart.hpp>
#include <DbChart.hpp>
#include <ExtCtrls.hpp>
#include <TeEngine.hpp>
#include <TeeProcs.hpp>
#include <Series.hpp>
#include <TeeFunci.hpp>
//---------------------------------------------------------------------------
class TFormNS : public TForm
{
__published:	// IDE-managed Components
        TPanel *PanelLeft;
        TSplitter *Splitter1;
        TPanel *PanelList;
        TLabel *LabelList;
        TListBox *ListBox1;
        TPanel *PanelOpreation;
        TEdit *Edit1;
        TEdit *Edit2;
        TButton *Button1;
        TButton *Button2;
        //TButton *Button3;
        TButton *Button4;
        TButton *Button5;
        TButton *Button6;
        TPanel *PanelRight;
        TADOConnection *ADOConnection1;
        TADOQuery *ADOQuery1;
        TDataSource *DataSource1;
        TADOQuery *ADOQuery2;
        TPanel *PanelSingleNode;
        TChart *Chart1;
        TSplitter *SplitterSingleNode;
        TPanel *PanelRate;
        TChart *Chart2;
        TBarSeries *Series1;
        TSplitter *SplitterRate;
        TPanel *PanelAllNode;
        TChart *Chart3;
        TBarSeries *Series2;
        TSplitter *SplitterAllNode;
        TPanel *PanelNode4;
        TChart *Chart4;
        TSplitter *SplitterBottom;
        TSplitter *SplitterLeftRight;
        TLineSeries *Series5;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        int DataSelected;
        __fastcall TFormNS(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormNS *FormNS;
//---------------------------------------------------------------------------
#endif
