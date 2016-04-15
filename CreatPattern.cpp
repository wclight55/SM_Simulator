//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "MainFrame.h"
#include "CreatPattern.h"

#include <vector>
#include <string>
#include <ctime>
#include <iostream>
#include <fstream>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

const int &INF=100000000;
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm2::FormCreate(TObject *Sender)
{
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          if(myobj->m_iInf == 9)
          {
              String tmp = myobj->m_strName;
              ListBox1->Items->Add(tmp);
              ListBox2->Items->Add(tmp);
          }
        }
        CreatLabels();
        CreatDismap();
        floyd(distmap,path);
}
//---------------------------------------------------------------------------
void TForm2::CreatLabels()             //���ɱ�ѡ��ǩ
{
    AnsiString mylabel;
    mylabel = "Have a rest";
    ListBox4->Items->Add(mylabel);
    mylabel = "Wash hands";
    ListBox4->Items->Add(mylabel);
    mylabel = "Take a shower";
    ListBox4->Items->Add(mylabel);
    mylabel = "Watch TV";
    ListBox4->Items->Add(mylabel);
    mylabel = "Wash clothes";
    ListBox4->Items->Add(mylabel);
    mylabel = "Have a meal";
    ListBox4->Items->Add(mylabel);
    mylabel = "Cook";
    ListBox4->Items->Add(mylabel);
    mylabel = "Go to toilet";
    ListBox4->Items->Add(mylabel);
    mylabel = "Go to sleep";
    ListBox4->Items->Add(mylabel);
    mylabel = "Play the piano";
    ListBox4->Items->Add(mylabel);
    mylabel = "Else";
    ListBox4->Items->Add(mylabel);
}

//---------------------------------------------------------------------------
void TForm2::CreatDismap()      //�����ڽӱ�
{
    int n_num = g_pProject->m_pFCMsNodeList->Count;
    distmap.assign(n_num,vector<double>(n_num,INF));
    for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;++i)
    {
        f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        for(int j = 0;j<g_pProject->m_pFCMsNodeList->Count;++j)
        {
            f1 = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[j];
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
//--------------------------------------------------------------------------
void TForm2::floyd(vector<vector<double> > &distmap,vector<vector<int> > &path)//�ɱ����µ��ڽӾ��󣬸��º���ȷ��ԭ�б�,·���ϵ���õ����ת��
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
//-----------------------------------------------------------------------------
void TForm2::print(const int &beg,const int &end,const vector<vector<int> > &path)//�����ã����⿽������ռ���ڴ�ռ�
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
    FCMsNode *myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[end];
    switch(StrToInt(myobj->m_iInf))
    {
        case 1:    t += IntToStr(rand()%20); break;
        case 4:    t += IntToStr(rand()%360);break;
        case 9:    t += IntToStr(rand()%6000);break;
    }
    t += "  ";
    }

    //cout<<"->"<<end;
}
void __fastcall TForm2::Button3Click(TObject *Sender)
{
    srand(time(0));
    mytxt=new TStringList;
    ListBox3->Clear();

    for(int i=0;i<ListBox1->Items->Count;i++){         //��ȡ����ѡ��Ŀ�ʼ�ڵ������
        if(ListBox1->Selected[i]){
            s = ListBox1->Items->Strings[i];
            break;
            }
    }
    for(int i=0;i<ListBox2->Items->Count;i++){          //��ȡ����ѡ��Ľ����ڵ������
        if(ListBox2->Selected[i]){
            s1 = ListBox2->Items->Strings[i];
            break;
            }
    }
    r = "Pattern:  ";
    t = "Duration:  ";
    r += s;  //��ʼ�ڵ�
    t += IntToStr(rand()%6000);        //���ܽڵ����ʱ��ȡ0~6000s�е�����
    t += "  ";
    for(int k = 0;k<g_pProject->m_pFCMsNodeList->Count;++k)
    {
        f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[k];
        if(f->m_strName == s)
            beg = k;
        if(f->m_strName == s1)
            end = k;
    }
    print(beg,end,path);           //��·�ߴ���r

    AnsiString mylabel;
    mylabel = "     ";
    Boolean isLabeled = false;                                 //�Ƿ���ӱ�ǩ
    for(int i=0;i<ListBox4->Items->Count;i++){         //������ӱ�ǩ
        if(ListBox4->Selected[i]){
            mylabel += ListBox4->Items->Strings[i];
            isLabeled = true;
            break;
            }
    }
    if(!isLabeled){
        mylabel += "Unknown Pattern";
        }
    r += mylabel;

    ListBox3->Items->Add(r);
    ListBox3->Items->Add(t);

    FILE *fp;
    fp=fopen("D:\\smart-environment-simulator20140308\\Pattern.txt", "a");
    if(fp == NULL)
        ShowMessage("Open FIle Failed");
    fclose(fp);

//    SetCurrentDir("D:\\smart-environment-simulator20140308");
//    Boolean file_exist=FileExists("Pattern.txt");
//    if(FileExists("Pattern.txt.txt")) //����ļ��Ѿ����ڣ���ֱ�Ӷ��ļ�����д����
//    {
        mytxt->LoadFromFile("D:\\smart-environment-simulator20140308\\Pattern.txt");
        mytxt->Add(r);
        mytxt->Add(t);
        mytxt->SaveToFile("D:\\smart-environment-simulator20140308\\Pattern.txt");
        mytxt->Clear();
//    }
/*    else   //����ļ������ڣ��򴴽��ļ����ٶ��ļ�����д����
    {
        int routefile=FileCreate("Pattern.txt");
        mytxt->LoadFromFile("D:\\smart-environment-simulator20140308\\Pattern.txt");
        mytxt->Add(r);
        mytxt->Add(t);
        mytxt->SaveToFile("D:\\smart-environment-simulator20140308\\Pattern.txt");
        mytxt->Clear();
    }
*/
}
//---------------------------------------------------------------------------

void __fastcall TForm2::Button1Click(TObject *Sender)
{
        this->Close();
}
//---------------------------------------------------------------------------

