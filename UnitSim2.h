//---------------------------------------------------------------------------

#ifndef UnitSim2H
#define UnitSim2H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormSim2 : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TButton *Button1;
        void __fastcall Button1Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormSim2(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSim2 *FormSim2;
//---------------------------------------------------------------------------
#endif
