//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "UnitSim2.h"
#include "UnitSim.h"
#include "MainFrame.h"
#include <Dialogs.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSim2 *FormSim2;
//---------------------------------------------------------------------------
__fastcall TFormSim2::TFormSim2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFormSim2::Button1Click(TObject *Sender)
{
int m = frmMainFrame->num;
if(m<9){
    int n = 9-m;
    String s = IntToStr(n);
    ShowMessage("There are "+s+" more routes to add");
    this->Close();
}
else{
    ShowMessage("No more routes to add");
    this->Close();
}
}
//---------------------------------------------------------------------------

