//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------lsl 16.3.1--------------------------------------------------
#include <Dialogs.hpp>
#include "MainFrame.h"
#include "UIProject.h"
#include <vector>
#include <string>
//---------------lsl 16.3.1---------------------------------------------------

#include "Transfer.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
UIProject*g_pProject_new;        //new environment 20160301
const int &INF=100000000;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        graphic_new=NULL;

        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          if(myobj->m_iInf == 9)
          {
              String tmp = myobj->m_strName;
              ListBox1->Items->Add(tmp);
              ListBox5->Items->Add(tmp);
          }
        }

        bmp_new=new Graphics::TBitmap();
        g_pProject_new=new UIProject;
        g_pProject_new->DrawingType = dtSelect;

}
 __fastcall TForm1::~TForm1()
{
      if(!bmp_new == NULL)
          delete bmp_new;
      //if(!g_pProject_new == NULL)
          //delete g_pProject_new;
}
//---------------------------------------------------------------------------

//----------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
    OpenDialog->Filter = "Model File|*.xml";
    OpenDialog->DefaultExt = "*.XML";
    OpenDialog->FileName = "*.XML";
    delete g_pProject_new;
    g_pProject_new=new UIProject;
    g_pProject_new->DrawingType = dtSelect;
    if(OpenDialog->Execute())
    {
        g_pProject_new->m_strFileName=OpenDialog->FileName;
        AnsiString exten = ExtractFileExt(OpenDialog->FileName);
        exten = exten.UpperCase();
        if(exten == ".XML")
        {
          g_pProject_new->XMLDoc = XMLDoc;
          g_pProject_new->LoadFromXML(g_pProject_new->m_strFileName);

          if( graphic_new==NULL)
             graphic_new=new Graphics::TBitmap();
          if(g_pProject_new->m_strLayout.Length()>2)
          {
           try {
              graphic_new->LoadFromFile(g_pProject_new->m_strLayout);
           } catch (Exception &e)
           {  ShowMessage(e.Message);delete graphic_new;graphic_new=NULL;
           }
          }
          this->Caption="Smart Environment----"+g_pProject_new->m_strFileName;
        }
        else
        {
          return;
        }
        ListBox2->Clear();
         for(int i = 0;i<g_pProject_new->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj1 = (FCMsNode*)g_pProject_new->m_pFCMsNodeList->Items[i];
          if(myobj1->m_iInf == 9)
          {
              String tmp = myobj1->m_strName;
              ListBox2->Items->Add(tmp);
          }
        }
       // FrameProperty->RefreshProjectTree();
         Refresh();
         CreatDismap();
         floyd(distmap,path);
    }
}


//---------------------------------------------------------------------------


void TForm1::Refresh()
{

     bmp_new->Canvas->Brush->Color = g_pProject_new->m_cBackGround;
     bmp_new->Canvas->FillRect(PaintBox1->ClientRect);

     if(graphic_new!=NULL)
       bmp_new->Canvas->StretchDraw(TRect(-g_pProject_new->XOrientation*g_pProject_new->proportion,-g_pProject_new->YOrientation*g_pProject_new->proportion
      ,(graphic_new->Width-g_pProject_new->XOrientation) * g_pProject_new->proportion,(graphic_new->Height-g_pProject_new->YOrientation) * g_pProject_new->proportion)
      ,graphic_new);


     bmp_new->Canvas->CopyMode= cmSrcCopy;

     if(g_pProject_new->DrawingType == dtLineEvent)
     {
        double xt,yt,xg,yg;TPoint arrow[3];

        long x1 =((double)(p_start.x-g_pProject_new->XOrientation))*g_pProject_new->proportion;
        long y1 = ((double)(p_start.y-g_pProject_new->YOrientation))*g_pProject_new->proportion;
        long x2 =((double)(p_end.x-g_pProject_new->XOrientation))*g_pProject_new->proportion;
        long y2 =((double)(p_end.y-g_pProject_new->YOrientation))*g_pProject_new->proportion;

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
        bmp_new->Canvas->MoveTo(x1,y1);
        bmp_new->Canvas->LineTo(x2,y2);
        bmp_new->Canvas->Polygon(arrow,2);
     }
     g_pProject_new->Draw(bmp_new->Canvas);
     ////
     PaintBox1->Canvas->CopyRect(PaintBox1->ClientRect,bmp_new->Canvas,PaintBox1->ClientRect);
}
//----------------------------------------------------------------------------
void __fastcall TForm1::TForm1BoxPaint(TObject *Sender)
{
  Refresh();
}
void __fastcall TForm1::PanelPaintResize(TObject *Sender)
{
  g_pProject_new->m_MaxPoint.x=PaintBox1->Width;
  g_pProject_new->m_MaxPoint.y=PaintBox1->Height;
  bmp_new->Width=PaintBox1->Width;
  bmp_new->Height=PaintBox1->Height;
}
//----------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
    ListBox3->Clear();
    ListBox7->Clear();
    flag = false;
    flag1 = false;

    for(int i=0;i<ListBox1->Items->Count;i++){         //��ȡ����ѡ��Ŀ�ʼ�ڵ������
        if(ListBox1->Selected[i]){
            s = ListBox1->Items->Strings[i];
            break;
            }
    }
    for(int i=0;i<ListBox5->Items->Count;i++){          //��ȡ����ѡ��Ľ����ڵ������
        if(ListBox5->Selected[i]){
            s1 = ListBox5->Items->Strings[i];
            break;
            }
    }
    for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];//��������ÿһ���ڵ�
        if(f->m_strName==s){flag = true;break;}
    }                                    //����ѡ��ڵ��ڽڵ��б��ﱻ�ҵ�
    for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        f1 = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];//��������ÿһ���ڵ�
        if(f1->m_strName==s1){flag1 = true;break;}
    }
    for(int i = 0;i<g_pProject_new->m_pFCMsNodeList->Count;i++){
        f2 = (FCMsNode*)g_pProject_new->m_pFCMsNodeList->Items[i];
        if(f2->m_iPosition==f->m_iPosition && flag == true)
        {
                ListBox3->Items->Add(f2->m_strName);
        }
    }
    for(int i = 0;i<g_pProject_new->m_pFCMsNodeList->Count;i++){
        f2 = (FCMsNode*)g_pProject_new->m_pFCMsNodeList->Items[i];
        if(f2->m_iPosition==f1->m_iPosition  && flag1 == true)
        {
                ListBox7->Items->Add(f2->m_strName);
        }
    }

if(ListBox3->Items->Count != NULL && ListBox7->Items->Count != NULL)   //���û�п�ʼ�������ֹ���򲻽���ƥ��
{
    ListBox4->Clear();
    for(int i=0;i<ListBox3->Items->Count;++i)
        for(int j=0;j<ListBox7->Items->Count;++j)
        {
            r = ListBox3->Items->Strings[i];
            for(int k = 0;k<g_pProject_new->m_pFCMsNodeList->Count;++k)
            {
                f2 = (FCMsNode*)g_pProject_new->m_pFCMsNodeList->Items[k];
                if(f2->m_strName == ListBox3->Items->Strings[i])
                    beg = k;
                if(f2->m_strName == ListBox7->Items->Strings[j])
                    end = k;
            }
            print(beg,end,path);           //��·�ߴ���r
            ListBox4->Items->Add(r);
        }

}
}

void TForm1::print(const int &beg,const int &end,const vector<vector<int> > &path)//�����ã����⿽������ռ���ڴ�ռ�
           //Ҳ������ջ�ṹ�Ƚ���������������溯���ݹ�
{
    if(path[beg][end]>=0)
    {
        print(beg,path[beg][end],path);
        print(path[beg][end],end,path);
    }
    else
    {
    r += " -> m";
    r += IntToStr(end+1);
    }

    //cout<<"->"<<end;
}

//---------------------------------------------------------------------------
void TForm1::CreatDismap()      //�����ڽӱ�
{
    int n_num = g_pProject_new->m_pFCMsNodeList->Count;
    distmap.assign(n_num,vector<double>(n_num,INF));
    for(int i = 0;i<g_pProject_new->m_pFCMsNodeList->Count;++i)
    {
        f = (FCMsNode*)g_pProject_new->m_pFCMsNodeList->Items[i];
        for(int j = 0;j<g_pProject_new->m_pFCMsNodeList->Count;++j)
        {
            f1 = (FCMsNode*)g_pProject_new->m_pFCMsNodeList->Items[j];
            if(IsConnected(f,f1))
            {
                distmap[i][j] = sqrt((f->X-f1->X)*(f->X-f1->X)+(f->Y-f1->Y)*(f->Y-f1->Y));
            }
        }
    }
 /*
    ofstream out("out.txt");                   //����ڽӾ���
     for(int i = 0;i<g_pProject_new->m_pFCMsNodeList->Count;++i)
    {
        for(int j = 0;j<g_pProject_new->m_pFCMsNodeList->Count;++j)
        {
            out <<distmap[i][j]<<',';
        }
        out <<endl;
    }
    out.close();
 */
}



void TForm1::floyd(vector<vector<double> > &distmap,vector<vector<int> > &path)//�ɱ����µ��ڽӾ��󣬸��º���ȷ��ԭ�б�,·���ϵ���õ����ת��
{
    const int &NODE=distmap.size();//���ڽӾ���Ĵ�С���ݶ�����������ٲ�������
    path.assign(NODE,vector<int>(NODE,-1));//��ʼ��·������
    for(int k=1; k!=NODE; ++k)//����ÿһ����ת��
        for(int i=0; i!=NODE; ++i)//ö��Դ��
            for(int j=0; j!=NODE; ++j)//ö���յ�
                if(distmap[i][j]>distmap[i][k]+distmap[k][j])//���������ǲ���ʽ
                {
                    distmap[i][j]=distmap[i][k]+distmap[k][j];//����
                    path[i][j]=k;//��¼·��
                }
}



void __fastcall TForm1::Button2Click(TObject *Sender)
{
    this->Close();
}
//---------------------------------------------------------------------------

