//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "NewEnvironment.h"
#include "MainFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TNewEnbironment *NewEnbironment;
//---------------------------------------------------------------------------
__fastcall TNewEnbironment::TNewEnbironment(TComponent* Owner)
        : TForm(Owner)
{
        //NewEnbironment->Parent = frmMainFrame->Panel1;
        //NewEnbironment->Visible = true;
}
//---------------------------------------------------------------------------
void __fastcall TNewEn::btnOpenClick(TObject *Sender)
{
    OpenDialog->Filter = "Model File|*.xml";
    OpenDialog->DefaultExt = "*.XML";
    OpenDialog->FileName = "*.XML";
    if(g_pProject->m_bModified)
    {
      switch (Application->MessageBox("Model File has been modified, save£¿","Hint",MB_YESNOCANCEL))
      {  case ID_YES :
            SaveCommand();
            break;
         case ID_CANCEL :
            return;
      }
    }
    ClearProject();
    InitialProject();
    if(OpenDialog->Execute())
    {
        g_pProject->m_strFileName=OpenDialog->FileName;
        AnsiString exten = ExtractFileExt(OpenDialog->FileName);
        exten = exten.UpperCase();
        if(exten == ".XML")
        {
          g_pProject->XMLDoc = XMLDocument1;
          g_pProject->LoadFromXML(g_pProject->m_strFileName);

          if( graphic==NULL)
             graphic=new Graphics::TBitmap();
          if(g_pProject->m_strLayout.Length()>2)
          {
           try {
              graphic->LoadFromFile(g_pProject->m_strLayout);
           } catch (Exception &e)
           {  ShowMessage(e.Message);delete graphic;graphic=NULL;
           }
          }
          this->Caption="Smart Environment----"+g_pProject->m_strFileName;
        }
        else
        {
          return;
        }
        FrameProperty->RefreshProjectTree();
        Refresh();
    }

}
