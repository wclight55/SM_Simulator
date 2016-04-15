//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Output.h"
#include "MainFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFrameOutput *FrameOutput;
//---------------------------------------------------------------------------
__fastcall TFrameOutput::TFrameOutput(TComponent* Owner)
	: TFrame(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TFrameOutput::ListBoxErrorDblClick(TObject *Sender)
{

	TObject* pObj=ListBoxError->Items->Objects[ListBoxError->ItemIndex];
	if(pObj==NULL) return;
	try
	{
		String strClassName=pObj->ClassName();
		if(strClassName=="RulesetNode"||strClassName=="CaculateNode"||strClassName=="LogicalNode")
		{
			frmMainFrame->NodeInCenter((NodeEvent*)pObj);
			frmMainFrame->FrameProperty->ChangeTreeSelectStatus();
		}
	}
	catch(...)
	{
		MessageBox(NULL,"The Object dosen't exist","Hint",MB_OK+MB_ICONEXCLAMATION);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFrameOutput::ListBoxSearchDblClick(TObject *Sender)
{

	TObject* pObj=ListBoxSearch->Items->Objects[ListBoxSearch->ItemIndex];
	if(pObj==NULL) return;
	try
	{
		String strClassName=pObj->ClassName();
		if(strClassName=="FCMsNode")
		{
			frmMainFrame->NodeInCenter((NodeEvent*)pObj);
			frmMainFrame->FrameProperty->ChangeTreeSelectStatus();
		}
	}
	catch(...)
	{
		MessageBox(NULL,"The Object dosen't exist","Hint",MB_OK+MB_ICONEXCLAMATION);
	}  
}
//---------------------------------------------------------------------------

