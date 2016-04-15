//---------------------------------------------------------------------------

#ifndef FindH
#define FindH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
//---------------------------------------------------------------------------
class TfrmFind : public TForm
{
__published:	// IDE-managed Components
	TButton *btnOK;
	TButton *btnCancel;
	TPanel *Panel1;
	TLabel *Label1;
	TEdit *edtSearch;
	void __fastcall btnCancelClick(TObject *Sender);
	void __fastcall btnOKClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TfrmFind(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TfrmFind *frmFind;
//---------------------------------------------------------------------------
#endif
