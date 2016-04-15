//---------------------------------------------------------------------------

#include <vcl.h>
#include <Dialogs.hpp>
#pragma hdrstop

#include "UnitEvac.h"
#include "MainFrame.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormEvac *FormEvac;
//---------------------------------------------------------------------------
__fastcall TFormEvac::TFormEvac(TComponent* Owner)
        : TForm(Owner)
{
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          String tmp = myobj->m_strName;
          if(myobj->m_iType==2){
              ListBox1->Items->Add(tmp);;
              }
        }
}
//---------------------------------------------------------------------------
void __fastcall TFormEvac::Button1Click(TObject *Sender)
{
String target;
FCMsNode*tobj;
FCMsNode*t1;
FCMsNode*t2;
for(int i=0;i<ListBox1->Items->Count;i++){
    if(ListBox1->Selected[i]){
            target = ListBox1->Items->Strings[i];
        }
    }
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          tobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          if(tobj->m_strName==target){
              break;
              }
        }
String s = Edit1->Text;
if(s==NULL){
    String str = "请设置房间人数";
    ShowMessage(str);
}
else{
    bool b = false;
    bool b1 = false;
    bool b2 = false;
    int c=0;
    TList*tl = new TList;
    TList*e1 = new TList;
    TList*e2 = new TList;
    TList*n1 = new TList;
    TList*n2 = new TList;
    while(!b||c<2){
        if(b==false){
            e1->Add(tobj);
            e2->Add(tobj);
            tobj->GetConnectedNodes(tl);
            if(tl->Count>=2){
                b = true;
                t1 = (FCMsNode*) tl->Items[0];
                t2 = (FCMsNode*) tl->Items[1];
                if(t1->m_iType==3){
                    c++;
                    e1->Add(t1);
                    b1 = true;
                }
                if(t2->m_iType==3){
                    c++;
                    e2->Add(t2);
                    b2 = true;
                }
                //if(!b1){e1->Add(t1);}
                //if(!b2){e2->Add(t2);}
            }
            else{
                e1->Add(tobj);
                e2->Add(tobj);
                tobj = (FCMsNode*) tl->Items[0];
                if(tobj->m_iType==3){
                    c+=2;
                    e1->Add(tobj);
                    e2->Add(tobj);
                    b1 = true;
                    b2 = true;
                }
                //if(!b1){e1->Add(tobj);}
                //if(!b2){e2->Add(tobj);}
            }
        }
        //
        else{
            if(!b1){
                e1->Add(t1);
                t1->GetConnectedNodes(n1);
                n1=FindSensors(n1,e1);
                for(int i=0;i<n1->Count;i++){
                    FCMsNode* f = (FCMsNode*) n1->Items[i];
                    if(f->m_iType==3){
                        c++;
                        e1->Add(f);
                        //frmMainFrame->ListBox1->Items->Add("2");
                        //frmMainFrame->ListBox1->Items->Add(f->m_strName);
                        b1 = true;
                        break;
                    }
                    t1 = f;
                }
            //if(!b1){e1->Add(t1);}
            }
            if(!b2){
                e2->Add(t2);
                t2->GetConnectedNodes(n2);
                n2=FindSensors(n2,e2);
                for(int i=0;i<n2->Count;i++){
                    FCMsNode* f = (FCMsNode*) n2->Items[i];
                    if(f->m_iType==3){
                        c++;
                        b2 = true;
                        e2->Add(f);
                        break;
                    }
                    t2 = f;
            }
            //if(!b2){e2->Add(t2);}
            }


        }
    }
    int num = StrToInt(Edit1->Text);
    tobj->capa = num;
    for(int i=0;i<e1->Count;i++){
        FCMsNode* f = (FCMsNode*) e1->Items[i];
        frmMainFrame->ListBox1->Items->Add(f->m_strName);
    }
    for(int i=0;i<e2->Count;i++){
        FCMsNode* f = (FCMsNode*) e2->Items[i];
        frmMainFrame->ListBox1->Items->Add(f->m_strName);
    }
    this->Close();
}
}
TList* TFormEvac::FindSensors(TList*pList1,TList*pList2)
{
        TList*tmplist=new TList;
	for(int i=0;i<pList1->Count;i++)
	{
		FCMsNode* pNode=(FCMsNode*)pList1->Items[i];
                bool bFount=false;
                for(int i=0;i<pList2->Count;i++)
        	{
		        HISNODE* n1=(HISNODE*)pList2->Items[i];
                        if(pNode==n1->pNode)bFount=true;
	        }
                if(!bFount)
                {tmplist->Add(pNode);}
	}
        return tmplist;
}
//---------------------------------------------------------------------------
