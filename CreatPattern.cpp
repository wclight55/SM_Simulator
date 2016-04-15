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
void TForm2::CreatLabels()             //生成备选标签
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
void TForm2::CreatDismap()      //创建邻接表
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
    ofstream out("out.txt");                   //输出邻接矩阵
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
void TForm2::floyd(vector<vector<double> > &distmap,vector<vector<int> > &path)//可被更新的邻接矩阵，更新后不能确定原有边,路径上到达该点的中转点
{
    const int &NODE=distmap.size();//用邻接矩阵的大小传递顶点个数，减少参数传递
    path.assign(NODE,vector<int>(NODE,-1));//初始化路径数组
    for(int k=1; k!=NODE; ++k)//对于每一个中转点
        for(int i=0; i!=NODE; ++i)//枚举源点
            for(int j=0; j!=NODE; ++j)//枚举终点
                if(distmap[i][j]>distmap[i][k]+distmap[k][j])//不满足三角不等式
                {
                    distmap[i][j]=distmap[i][k]+distmap[k][j];//更新
                    path[i][j]=k;//记录路径
                }
}
//-----------------------------------------------------------------------------
void TForm2::print(const int &beg,const int &end,const vector<vector<int> > &path)//传引用，避免拷贝，不占用内存空间
           //也可以用栈结构先进后出的特性来代替函数递归
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

    for(int i=0;i<ListBox1->Items->Count;i++){         //提取出被选择的开始节点的名称
        if(ListBox1->Selected[i]){
            s = ListBox1->Items->Strings[i];
            break;
            }
    }
    for(int i=0;i<ListBox2->Items->Count;i++){          //提取出被选择的结束节点的名称
        if(ListBox2->Selected[i]){
            s1 = ListBox2->Items->Strings[i];
            break;
            }
    }
    r = "Pattern:  ";
    t = "Duration:  ";
    r += s;  //开始节点
    t += IntToStr(rand()%6000);        //功能节点持续时间取0~6000s中的整数
    t += "  ";
    for(int k = 0;k<g_pProject->m_pFCMsNodeList->Count;++k)
    {
        f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[k];
        if(f->m_strName == s)
            beg = k;
        if(f->m_strName == s1)
            end = k;
    }
    print(beg,end,path);           //把路线存入r

    AnsiString mylabel;
    mylabel = "     ";
    Boolean isLabeled = false;                                 //是否添加标签
    for(int i=0;i<ListBox4->Items->Count;i++){         //给活动附加标签
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
//    if(FileExists("Pattern.txt.txt")) //如果文件已经存在，则直接对文件进行写操作
//    {
        mytxt->LoadFromFile("D:\\smart-environment-simulator20140308\\Pattern.txt");
        mytxt->Add(r);
        mytxt->Add(t);
        mytxt->SaveToFile("D:\\smart-environment-simulator20140308\\Pattern.txt");
        mytxt->Clear();
//    }
/*    else   //如果文件不存在，则创建文件，再对文件进行写操作
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

