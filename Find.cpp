//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "MainFrame.h"
#include "Find.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmFind *frmFind;
//---------------------------------------------------------------------------
__fastcall TfrmFind::TfrmFind(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------


void __fastcall TfrmFind::btnCancelClick(TObject *Sender)
{
	this->Close();	
}
//---------------------------------------------------------------------------
void __fastcall TfrmFind::btnOKClick(TObject *Sender)
{

	TCursor Save_Cursor = Screen->Cursor;
	Screen->Cursor = crHourGlass;    // Show hourglass cursor

	ClearSearchResult();

	String strName=this->edtSearch->Text;
  TTreeView* pTreeView=frmMainFrame->FrameProperty->TreeViewProject;
  pTreeView->Items->BeginUpdate();

  pTreeView->Items->EndUpdate();

  TTreeNodes* pNodes=pTreeView->Items;
	TTreeNode* pNode;
	for(int i=0;i<pNodes->Count;i++)
	{
		pNode=pNodes->Item[i];

    if(pNode->Data!=NULL && pNode->Text.Pos(strName)>0)
			AddSearchResult(pNode->Text,(TObject*)pNode->Data);
	}
  AddSearchResult("Finish Finding!",NULL);
	Close();

	Screen->Cursor = Save_Cursor; // always restore the cursor

}
//---------------------------------------------------------------------------

