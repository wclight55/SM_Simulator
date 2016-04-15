//---------------------------------------------------------------------------

#ifndef ShowResultH
#define ShowResultH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <ComCtrls.hpp>
#include "UIProject.h"
//---------------------------------------------------------------------------
class TfrmShowResult : public TForm
{
__published:	// IDE-managed Components
        TPanel *Panel1;
        TEdit *edStart;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *edEnd;
        TButton *Button1;
        TPanel *Panel2;
        TPageControl *PageControl1;
        TTabSheet *tabSensorHistory;
        TTabSheet *tabUserPath;
        TScrollBar *scHSensorHistory;
        TScrollBar *scVSensorHistory;
        TScrollBar *scHUserPath;
        TScrollBar *scVUserPath;
        TLabel *labTotal;
        TLabel *Label3;
        TPaintBox *paintSensorHistory;
        TPaintBox *paintUserPath;
        TTabSheet *tabHistoryDetail;
        TPaintBox *paintHistoryDetail;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall paintSensorHistoryPaint(TObject *Sender);
        void __fastcall paintUserPathPaint(TObject *Sender);
        void __fastcall paintHistoryDetailPaint(TObject *Sender);
private:	// User declarations
public:
UIProject*g_pProject;
public:		// User declarations
        __fastcall TfrmShowResult(TComponent* Owner);
        void RefreshSensorHistory();
        void RefreshUserPath();
        void RefreshHistoryDetail();
        void FindUserBetweenTime(int iStart, int iEnd,TList*userList,FCMsNode*triggered);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmShowResult *frmShowResult;
//---------------------------------------------------------------------------
#endif
