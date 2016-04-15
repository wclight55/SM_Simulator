//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "ShowResult.h"
#include <math.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TfrmShowResult *frmShowResult;
//---------------------------------------------------------------------------
__fastcall TfrmShowResult::TfrmShowResult(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TfrmShowResult::Button1Click(TObject *Sender)
{

    	if(PageControl1->ActivePageIndex==0)
        {
           RefreshSensorHistory();
        }
        else if(PageControl1->ActivePageIndex==1)
        {
           RefreshUserPath();
        }
        else
        {
           RefreshHistoryDetail();
        }
}
//---------------------------------------------------------------------------
const iHight=8;
const iHight2=15;
const iWidth=1;
const SSS=25;
const dist=5;
const dis2=2;
const len=20;
void TfrmShowResult::RefreshSensorHistory()
{

       int iStart= StrToInt(this->edStart->Text);
       int iEnd= StrToInt(this->edEnd->Text);
       TCanvas* m_canvas=paintSensorHistory->Canvas;



    m_canvas->Brush->Color = clWhite;
    m_canvas->FillRect(paintSensorHistory->ClientRect);

    m_canvas->Pen->Style = psDash;
  m_canvas->Pen->Color = clGray;
         int kkk=0;
        m_canvas->TextOutA(2,(iHight2)*(g_pProject->m_pFCMsNodeList->Count)+iHight,"Time:");
         for(int j= iStart;j<iEnd;j++)
         {
             kkk++;
             if(kkk==len)
             {
                kkk=0;
                int ti=j*g_pProject->m_dSamplingTime;
                AnsiString strTi=AnsiString(ti);
                m_canvas->MoveTo(SSS+(j-iStart)*iWidth,0);
                m_canvas->LineTo(SSS+(j-iStart)*iWidth,(iHight2)*(g_pProject->m_pFCMsNodeList->Count)+iHight);
                m_canvas->TextOutA(SSS+(j-iStart)*iWidth-m_canvas->TextWidth(strTi)/2,(iHight2)*(g_pProject->m_pFCMsNodeList->Count)+iHight,strTi);
             }
          }

  m_canvas->Font->Color=clBlack;
  m_canvas->Font->Size=8;
  m_canvas->Brush->Style = bsSolid;
  m_canvas->Pen->Color = clBlack;
  m_canvas->Pen->Style = psSolid;
       for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
       {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          m_canvas->TextOutA(2,(iHight2)*(i)+iHight/2,myobj->m_strName);
          int past=-1;
          for(int j= iStart;j<iEnd;j++)
          {
             if(j==iStart)
               m_canvas->MoveTo(SSS,(iHight2)*(i+1));
             else
             {
               short tmp=myobj->m_dqHistoryData->at(j);
               if(tmp==0)
               {
                   if(past==-1)
                      m_canvas->LineTo(SSS+(j-iStart+1)*iWidth,(iHight2)*(i+1));
                   else if(past==0)
                      m_canvas->LineTo(SSS+(j-iStart+1)*iWidth,(iHight2)*(i+1));
                   else
                   {
                      m_canvas->LineTo(SSS+(j-iStart)*iWidth,(iHight2)*(i+1));
                      m_canvas->LineTo(SSS+(j-iStart+1)*iWidth,(iHight2)*(i+1));
                   }
                   past=0;
               }
               else
               {
                   if(past==-1)
                   {
                      m_canvas->MoveTo(SSS,(iHight2)*(i+1)-iHight);
                      m_canvas->LineTo(SSS+(j-iStart+1)*iWidth,(iHight2)*(i+1)-iHight);
                   }
                   else if(past==0)
                   {
                      m_canvas->LineTo(SSS+(j-iStart)*iWidth,(iHight2)*(i+1)-iHight);
                      m_canvas->LineTo(SSS+(j-iStart+1)*iWidth,(iHight2)*(i+1)-iHight);
                   }
                   else
                   {
                      m_canvas->LineTo(SSS+(j-iStart+1)*iWidth,(iHight2)*(i+1)-iHight);
                   }
                   past=1;
               }
             }
          }
       }

}
void TfrmShowResult::RefreshUserPath()
{
   double p= g_pProject->proportion;
    long  xo=g_pProject->XOrientation;
    long  yo=g_pProject->YOrientation;
   g_pProject->ZoomTo(1);
   g_pProject->SetOffsetTo(0,0);
   TColor cl[]={65535, 255, 0, 4259584, 16711680, 16711935, 8421504, 32896, 4227327, 8421376};


       int iStart= StrToInt(this->edStart->Text);
       int iEnd= StrToInt(this->edEnd->Text);
       TCanvas* m_canvas=paintUserPath->Canvas;

    m_canvas->Brush->Color = clWhite;
    m_canvas->FillRect(paintUserPath->ClientRect);


   g_pProject->Draw(paintUserPath->Canvas);
    int userinwindow=0;
       for(int i = 0;i<g_pProject->m_pUserHistory->Count;i++)
       {
          WalkingUser*pUser = (WalkingUser*)g_pProject->m_pUserHistory->Items[i];
          bool bBegin=false;

          m_canvas->Pen->Width = 2;
          bool bNew=false;
          for(int j=0;j<pUser->m_pPathList->Count-1;j++)
          {
                HISNODE*n1=(HISNODE*)pUser->m_pPathList->Items[j];
                FCMsNode*myobj = n1->pNode;
                if(n1->iTime<iStart)continue;
                else if(!bNew)
                {
                  bNew=true;m_canvas->Pen->Color = cl[userinwindow];userinwindow++;
                }
                HISNODE*n2=(HISNODE*)pUser->m_pPathList->Items[j+1];
                FCMsNode*myobj2 = n2->pNode;
                if((n2->iTime)<=iEnd)
                {
                        double xt,yt,xg,yg;TPoint arrow[3];

                        long x1 =myobj->X;
                        long y1 =myobj->Y;
                        long x2 =myobj2->X;
                        long y2 =myobj2->Y;

                        if(y2!=y1)
                        {

                                yg=y2-16*(y2-y1)*sqrt(1.0/(double)((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1)));
                                xg=x2-((double)(x2-x1))/((double)(y2-y1))*(y2-yg);
                                xt=xg+8*sqrt((y2-yg)*(y2-yg)/((x2-xg)*(x2-xg)+(y2-yg)*(y2-yg)))/2;
                                yt=yg-(x2-xg)/(y2-yg)*(xt-xg);
                                arrow[0].x=x2;arrow[0].y=y2;
                                arrow[1].x=xt;arrow[1].y=yt;
                                xt=xg-8*sqrt((y2-yg)*(y2-yg)/((x2-xg)*(x2-xg)+(y2-yg)*(y2-yg)))/2;
                                yt=yg-(x2-xg)/(y2-yg)*(xt-xg);
                                arrow[2].x=xt;arrow[2].y=yt;

                        }
                        else
                        {
                                yg=y2;
                                if(x2>x1)
                                        xg=x2-16;
                                else
                                        xg=x2+16;
                                arrow[0].x=x2;arrow[0].y=y2;
                                arrow[1].x=xg;arrow[1].y=yg+8/2 ;
                                arrow[2].x=xg;arrow[2].y=yg-8/2 ;
                        }
                       m_canvas->MoveTo(x1,y1);
                       m_canvas->LineTo(x2,y2);
                       m_canvas->Polygon(arrow,2);

                       POINT d3;
                        d3.x=x1+(x2-x1)/2;
                        d3.y=y1+(y2-y1)/2;
                        m_canvas->TextOutA(d3.x - m_canvas->TextWidth(AnsiString(i))/2,d3.y,AnsiString(i));

                }
                else break;
          }
       }

   g_pProject->ZoomTo(p);
   g_pProject->SetOffsetTo(xo,yo);
    g_pProject->proportion=p;
    g_pProject->XOrientation=xo;
    g_pProject->YOrientation=yo;

}
void __fastcall TfrmShowResult::paintSensorHistoryPaint(TObject *Sender)
{
    RefreshSensorHistory();
}
//---------------------------------------------------------------------------
void __fastcall TfrmShowResult::paintUserPathPaint(TObject *Sender)
{
    RefreshUserPath();

}
//---------------------------------------------------------------------------
void __fastcall TfrmShowResult::paintHistoryDetailPaint(TObject *Sender)
{
   RefreshHistoryDetail();
}
//---------------------------------------------------------------------------
void TfrmShowResult::FindUserBetweenTime(int iStart, int iEnd,TList*userList,FCMsNode*triggered)
{
     for(int i = 0;i<g_pProject->m_pUserHistory->Count;i++)
       {
          WalkingUser*pUser = (WalkingUser*)g_pProject->m_pUserHistory->Items[i];
          for(int j=0;j<pUser->m_pPathList->Count;j++)
          {
                HISNODE*n1=(HISNODE*)pUser->m_pPathList->Items[j];
                FCMsNode*myobj = n1->pNode;
                if(triggered==myobj)
                {
                  if(n1->iTime>=(iStart-2)&&n1->iTime<=(iEnd+2))
                  {
                   userList->Add(pUser);
                   continue;
                  }
                }
          }
       }

}

const iHight3=2;
void TfrmShowResult::RefreshHistoryDetail()
{

       int iStart= StrToInt(this->edStart->Text);
       int iEnd= StrToInt(this->edEnd->Text);
       TCanvas* m_canvas=paintHistoryDetail->Canvas;


    TColor cl[]={65535, 255, 0, 4259584, 16711680, 16711935, 8421504, 32896, 4227327, 8421376};

    m_canvas->Brush->Color = clWhite;
    m_canvas->FillRect(paintHistoryDetail->ClientRect);

    m_canvas->Pen->Style = psDot;
    m_canvas->Pen->Color = clGray;
         int kkk=0;
        m_canvas->TextOutA(2,(iHight2)*(g_pProject->m_pFCMsNodeList->Count)+iHight,"Time:");

         for(int j= iStart;j<iEnd;j++)
         {
             kkk++;
             if(kkk==len)
             {
                int ti=j*g_pProject->m_dSamplingTime;
                AnsiString strTi=AnsiString(ti);
            
                kkk=0;
                m_canvas->MoveTo(SSS+(j-iStart)*iWidth,0);
                m_canvas->LineTo(SSS+(j-iStart)*iWidth,(iHight2)*(g_pProject->m_pFCMsNodeList->Count)+iHight);
                m_canvas->TextOutA(SSS+(j-iStart)*iWidth-m_canvas->TextWidth(strTi)/2,(iHight2)*(g_pProject->m_pFCMsNodeList->Count)+iHight,strTi);
             }
          }

          m_canvas->Font->Color=clBlack;
          m_canvas->Font->Size=8;
          m_canvas->Brush->Style = bsSolid;
          m_canvas->Pen->Color = clBlack;
          m_canvas->Pen->Style = psSolid;

          for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
          {
            FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
            m_canvas->TextOutA(2,(iHight2)*(i),myobj->m_strName);
            m_canvas->MoveTo(SSS,(iHight2)*(i+1)-iHight2/2);
            m_canvas->LineTo(SSS+(iEnd-iStart+1)*iWidth,(iHight2)*(i+1)-iHight2/2);
            int past=-1;
            int iiStart;
            int iiEnd;
            for(int j= iStart;j<iEnd;j++)
            {
               short tmp=myobj->m_dqHistoryData->at(j);
               if(tmp==0)
               {
                   if(past==-1)
                   {
                    ;
                   }
                   else if(past==0)
                   {
                    ;
                   }
                   else
                   {
                     TList*ulist=new TList;
                     FindUserBetweenTime(iiStart,iiEnd,ulist,myobj);
                     AnsiString strName;
                     for(int iii=0;iii<ulist->Count;iii++)
                     {
                        WalkingUser*u1=(WalkingUser*)ulist->Items[iii];
                        if(ulist->Count==1)strName=AnsiString(u1->m_iNum);
                        else if(iii<ulist->Count-1)
                         strName=strName+AnsiString(u1->m_iNum)+";";
                        else
                         strName=strName+AnsiString(u1->m_iNum);
                     }
                     m_canvas->Rectangle(SSS+(iiStart-iStart)*iWidth,(iHight2)*(i+1)-iHight2/2-iHight3,SSS+(iiEnd-iStart)*iWidth,(iHight2)*(i+1)-iHight2/2+iHight3);
                     m_canvas->TextOutA(SSS+(iiStart-iStart)*iWidth+(iiEnd-iiStart)*iWidth/2-m_canvas->TextWidth(strName)/2,(iHight2)*(i+1)-iHight2/2+iHight3,strName);

                     ulist->Clear();
                     delete ulist;
                   }
                   past=0;
               }
               else
               {
                   if(past==-1)
                   {
                     iiStart=j;
                   }
                   else if(past==0)
                   {
                     iiStart=j;
                   }
                   else
                   {
                     iiEnd=j;
                   }
                   past=1;
               }
             }
       }
}

