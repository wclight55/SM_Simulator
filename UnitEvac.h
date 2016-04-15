//---------------------------------------------------------------------------

#ifndef UnitEvacH
#define UnitEvacH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormEvac : public TForm
{
__published:	// IDE-managed Components
        TListBox *ListBox1;
        TLabel *Label1;
        TLabel *Label2;
        TEdit *Edit1;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormEvac(TComponent* Owner);
        TList* FindSensors(TList*pList1,TList*pList2);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormEvac *FormEvac;
//---------------------------------------------------------------------------
#endif
