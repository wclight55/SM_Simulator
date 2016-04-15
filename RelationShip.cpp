//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "RelationShip.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
Ttf_relationship *tf_relationship;
//---------------------------------------------------------------------------
__fastcall Ttf_relationship::Ttf_relationship(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void Ttf_relationship::SetRelation()
{

}

void Ttf_relationship::FillGrid()
{
     for (int i = 0; i < m_pHistory->Count; i++)
     {
         Matrix*obj = (Matrix*)m_pHistory->Items[i];
         ts_relation->Cells[0][i+1]=AnsiString(i+1);
         for(int j=0;j<obj->GetCol();j++)
         {
           ts_relation->Cells[j+1][i+1]=AnsiString((*obj)(1,j+1));
         }
     }
}
void __fastcall Ttf_relationship::FormShow(TObject *Sender)
{
    ts_relation->RowCount=m_pHistory->Count+1;
    Matrix*obj = (Matrix*)m_pHistory->Items[0];
    for(int i=0;i<g_pProject->m_pFCMsNodeList->Count;i++)
    {
        FCMsNode*out=(FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        ts_relation->Cells[i+1][0]=out->m_strName;
    }
    ts_relation->ColCount=obj->GetCol()+1;
    FillGrid();
}
//---------------------------------------------------------------------------

void __fastcall Ttf_relationship::ts_relationDrawCell(TObject *Sender,
      int ACol, int ARow, TRect &Rect, TGridDrawState State)
{
           if(m_HasCircle>=0)
           {
             if(ARow==ts_relation->RowCount-1||(m_HasCircle+1)==ARow)
             {
               ts_relation->Canvas->Font->Color=clWhite;
               ts_relation->Canvas->Brush->Color=clBlue;
               ts_relation->Canvas->FillRect(Rect);
               ts_relation->Canvas->TextOut(Rect.Left+3, Rect.Top+3,ts_relation->Cells[ACol][ARow]);
             }
           }

}
//---------------------------------------------------------------------------


