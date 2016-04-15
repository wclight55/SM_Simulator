//---------------------------------------------------------------------------


#ifndef OutputH
#define OutputH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TFrameOutput : public TFrame
{
__published:	// IDE-managed Components
	TPageControl *PageControl;
	TTabSheet *TabSheetOutputList;
	TTabSheet *TabSheetErrorList;
	TListBox *ListBoxOutput;
	TListBox *ListBoxError;
  TTabSheet *TabSheetSearch;
  TListBox *ListBoxSearch;
	void __fastcall ListBoxErrorDblClick(TObject *Sender);
  void __fastcall ListBoxSearchDblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TFrameOutput(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFrameOutput *FrameOutput;
//---------------------------------------------------------------------------
#endif
