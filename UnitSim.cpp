//---------------------------------------------------------------------------

#include <vcl.h>
#include <Dialogs.hpp>
#include "MainFrame.h"
#pragma hdrstop
#include <vector>
#include "UnitSim.h"
#include "UnitSim2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormSim *FormSim;
//---------------------------------------------------------------------------
__fastcall TFormSim::TFormSim(TComponent* Owner)
        : TForm(Owner)
{
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          String tmp = myobj->m_strName;
          ListBox1->Items->Add(tmp);
          if(myobj->m_iType!=1){
              ListBox2->Items->Add(tmp);
              }
        }
}
//---------------------------------------------------------------------------

void __fastcall TFormSim::Button1Click(TObject *Sender)
{
this->num = 0;
for(int i=0;i<ListBox1->Items->Count;i++){
    if(ListBox1->Selected[i]){
            String s = ListBox1->Items->Strings[i];//提取出被选择节点的名称
            for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
                FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];//依次搜索每一个节点
                if(f->m_strName==s){ //若被选择节点在节点列表里被找到
                    if(ListBox3->Items->Count>0){
                        String t = ListBox3->Items->Strings[ListBox3->Items->Count-1]; //取出列表中的最后一个节点的名称
                        TList* tl = new TList;
                        f->GetConnectedNodes(tl);
                        bool b = false;
                        for(int i=0;i<tl->Count;i++){
                            FCMsNode* fc = (FCMsNode*)tl->Items[i];
                            if(t==fc->m_strName){
                                b = true;
                                ListBox3->Items->Add(s);
                            }
                        }
                        if(b==false){
                            ShowMessage("该节点并不与上一选择节点相连");
                        }
                    }
                    else{
                        ListBox3->Items->Add(s);
                    }
                }
            }
            //if(b==true){
            //    ListBox3->Items->Add(ListBox1->Items->Strings[i]);
            //}
            //else{
            //    ShowMessage("该节点并不与上一选择节点相连");
            //}
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TFormSim::Button2Click(TObject *Sender)//关闭对话框
{
this->Close();
}
//---------------------------------------------------------------------------
void __fastcall TFormSim::Button3Click(TObject *Sender) //清空对话框中的列表
{
ListBox3->Clear();
frmMainFrame->route1->Clear();
frmMainFrame->route2->Clear();
frmMainFrame->route3->Clear();
frmMainFrame->route4->Clear();
//*******By WYP at 20150426***********************
frmMainFrame->route5->Clear();
frmMainFrame->route6->Clear();
frmMainFrame->route7->Clear();
frmMainFrame->route8->Clear();
frmMainFrame->route9->Clear();
//************************************************
frmMainFrame->RouteOfTemp.clear();//清空活动模式容器
frmMainFrame->num = 0;
}
//---------------------------------------------------------------------------
void __fastcall TFormSim::Button4Click(TObject *Sender) //选择路线
{
bool sflag = false;
bool eflag = false;
String start = ListBox3->Items->Strings[0];//以列表中第一个节点为起始节点
String end = ListBox3->Items->Strings[ListBox3->Items->Count-1];//以列表中最后一个节点为结束节点
for(int i=0;i<ListBox2->Items->Count;i++){
    String t = ListBox2->Items->Strings[i];
    if(t == start){
        sflag = true;
    }
    else if(t == end){
        eflag = true;
    }
}
if(sflag==false||eflag==false){
    String str = "出入口节点设置错误";
    ShowMessage(str);
}
else{
for(int i=0;i<ListBox3->Items->Count;i++)
{
    String s = ListBox3->Items->Strings[i];
    for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t==s&&frmMainFrame->num==0){
            frmMainFrame->route1->Add(f);
        }
        else if(t==s&&frmMainFrame->num==1){
            frmMainFrame->route2->Add(f);
        }
        else if(t==s&&frmMainFrame->num==2){
            frmMainFrame->route3->Add(f);
        }
        else if(t==s&&frmMainFrame->num==3){
            frmMainFrame->route4->Add(f);
        }
        //************By WYP at 20150426***********************
        else if(t==s&&frmMainFrame->num==4){
            frmMainFrame->route5->Add(f);
        }
        else if(t==s&&frmMainFrame->num==5){
            frmMainFrame->route6->Add(f);
        }
        else if(t==s&&frmMainFrame->num==6){
            frmMainFrame->route7->Add(f);
        }
        else if(t==s&&frmMainFrame->num==7){
            frmMainFrame->route8->Add(f);
        }
        else if(t==s&&frmMainFrame->num==8){
            frmMainFrame->route9->Add(f);
        }
        //*****************************************************
    }
}
frmMainFrame->num++;
ListBox3->Clear();
FormSim2 = new TFormSim2(Application);
FormSim2->Visible = true;
}
//************By WYP at 20150523****************************
frmMainFrame->RouteOfTemp.push_back(frmMainFrame->route1);
frmMainFrame->RouteOfTemp.push_back(frmMainFrame->route2);
frmMainFrame->RouteOfTemp.push_back(frmMainFrame->route3);
frmMainFrame->RouteOfTemp.push_back(frmMainFrame->route4);
frmMainFrame->RouteOfTemp.push_back(frmMainFrame->route5);
frmMainFrame->RouteOfTemp.push_back(frmMainFrame->route6);
frmMainFrame->RouteOfTemp.push_back(frmMainFrame->route7);
frmMainFrame->RouteOfTemp.push_back(frmMainFrame->route8);
frmMainFrame->RouteOfTemp.push_back(frmMainFrame->route9);
//**********************************************************
}
//---------------------------------------------------------------------------

void __fastcall TFormSim::Button5Click(TObject *Sender)
{
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m35"){
            frmMainFrame->route1->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m9"){
            frmMainFrame->route1->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m10"){
            frmMainFrame->route1->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m12"){
            frmMainFrame->route1->Add(f);
        }
}

for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m35"){
            frmMainFrame->route2->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m33"){
            frmMainFrame->route2->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m34"){
            frmMainFrame->route2->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m11"){
            frmMainFrame->route2->Add(f);
        }
}
frmMainFrame->num = 2;
}
//---------------------------------------------------------------------------

void __fastcall TFormSim::Button6Click(TObject *Sender)
{
int file;
file = FileOpen("D:\\smart-environment-simulator20140308\\Bin\\new.txt", fmOpenWrite);
if(frmMainFrame->num>0){
    for(int i=0;i<frmMainFrame->route1->Count;i++){
        FCMsNode*my = (FCMsNode*)frmMainFrame->route1->Items[i];
        if(i==frmMainFrame->route1->Count-1)
        {
            FileSeek(file,0,2);
            String s = my->m_strName;
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
            FileWrite(file, "\r\n",sizeof("\r\n"));
        }
        else
        {
            FileSeek(file,0,2);
            String s = my->m_strName;
            s = s+"->";
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
        }
}
}
if(frmMainFrame->num>1){
    for(int i=0;i<frmMainFrame->route2->Count;i++){
        FCMsNode*my = (FCMsNode*)frmMainFrame->route2->Items[i];
        if(i==frmMainFrame->route2->Count-1){
            FileSeek(file,0,2);
            String s = my->m_strName;
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
            FileWrite(file, "\r\n",sizeof("\r\n"));
        }
        else{
            FileSeek(file,0,2);
            String s = my->m_strName;
            s = s+"->";
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
        }
}
}
if(frmMainFrame->num>2){
    for(int i=0;i<frmMainFrame->route3->Count;i++){
        FCMsNode*my = (FCMsNode*)frmMainFrame->route3->Items[i];
        if(i==frmMainFrame->route3->Count-1){
            FileSeek(file,0,2);
            String s = my->m_strName;
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
            FileWrite(file, "\r\n",sizeof("\r\n"));
        }
        else{
            FileSeek(file,0,2);
            String s = my->m_strName;
            s = s+"->";
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
        }
}
}
if(frmMainFrame->num>3){
    for(int i=0;i<frmMainFrame->route4->Count;i++){
        FCMsNode*my = (FCMsNode*)frmMainFrame->route4->Items[i];
        if(i==frmMainFrame->route4->Count-1){
            FileSeek(file,0,2);
            String s = my->m_strName;
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
            FileWrite(file, "\r\n",sizeof("\r\n"));
        }
        else{
            FileSeek(file,0,2);
            String s = my->m_strName;
            s = s+"->";
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
        }
}
}
//**************By WYP at 20150426**********************************
if(frmMainFrame->num>4){
    for(int i=0;i<frmMainFrame->route5->Count;i++){
        FCMsNode*my = (FCMsNode*)frmMainFrame->route5->Items[i];
        if(i==frmMainFrame->route5->Count-1){
            FileSeek(file,0,2);
            String s = my->m_strName;
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
            FileWrite(file, "\r\n",sizeof("\r\n"));
        }
        else{
            FileSeek(file,0,2);
            String s = my->m_strName;
            s = s+"->";
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
        }
}
}
if(frmMainFrame->num>5){
    for(int i=0;i<frmMainFrame->route6->Count;i++){
        FCMsNode*my = (FCMsNode*)frmMainFrame->route6->Items[i];
        if(i==frmMainFrame->route6->Count-1){
            FileSeek(file,0,2);
            String s = my->m_strName;
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
            FileWrite(file, "\r\n",sizeof("\r\n"));
        }
        else{
            FileSeek(file,0,2);
            String s = my->m_strName;
            s = s+"->";
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
        }
}
}
if(frmMainFrame->num>6){
    for(int i=0;i<frmMainFrame->route7->Count;i++){
        FCMsNode*my = (FCMsNode*)frmMainFrame->route7->Items[i];
        if(i==frmMainFrame->route7->Count-1){
            FileSeek(file,0,2);
            String s = my->m_strName;
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
            FileWrite(file, "\r\n",sizeof("\r\n"));
        }
        else{
            FileSeek(file,0,2);
            String s = my->m_strName;
            s = s+"->";
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
        }
}
}
if(frmMainFrame->num>7){
    for(int i=0;i<frmMainFrame->route8->Count;i++){
        FCMsNode*my = (FCMsNode*)frmMainFrame->route8->Items[i];
        if(i==frmMainFrame->route8->Count-1){
            FileSeek(file,0,2);
            String s = my->m_strName;
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
            FileWrite(file, "\r\n",sizeof("\r\n"));
        }
        else{
            FileSeek(file,0,2);
            String s = my->m_strName;
            s = s+"->";
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
        }
}
}
if(frmMainFrame->num>8){
    for(int i=0;i<frmMainFrame->route9->Count;i++){
        FCMsNode*my = (FCMsNode*)frmMainFrame->route9->Items[i];
        if(i==frmMainFrame->route9->Count-1){
            FileSeek(file,0,2);
            String s = my->m_strName;
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
            FileWrite(file, "\r\n",sizeof("\r\n"));
        }
        else{
            FileSeek(file,0,2);
            String s = my->m_strName;
            s = s+"->";
            FileWrite(file, s.c_str(), sizeof(s.c_str()));
        }
}
}
//******************************************************************
FileClose(file);
}
//---------------------------------------------------------------------------




void __fastcall TFormSim::Button7Click(TObject *Sender)
{
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m12"){
            frmMainFrame->route1->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m14"){
            frmMainFrame->route1->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m13"){
            frmMainFrame->route1->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m2"){
            frmMainFrame->route1->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m19"){
            frmMainFrame->route2->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m18"){
            frmMainFrame->route2->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m10"){
            frmMainFrame->route2->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m11"){
            frmMainFrame->route2->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m31"){
            frmMainFrame->route3->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m29"){
            frmMainFrame->route3->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m21"){
            frmMainFrame->route3->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m24"){
            frmMainFrame->route3->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m23"){
            frmMainFrame->route3->Add(f);
        }
}
frmMainFrame->num = 3;
}
//---------------------------------------------------------------------------

void __fastcall TFormSim::Button8Click(TObject *Sender)
{
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m35"){
            frmMainFrame->route1->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m9"){
            frmMainFrame->route1->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m10"){
            frmMainFrame->route1->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m12"){
            frmMainFrame->route1->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m35"){
            frmMainFrame->route2->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m33"){
            frmMainFrame->route2->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m34"){
            frmMainFrame->route2->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m11"){
            frmMainFrame->route2->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m35"){
            frmMainFrame->route3->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m9"){
            frmMainFrame->route3->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m33"){
            frmMainFrame->route3->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m34"){
            frmMainFrame->route3->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m11"){
            frmMainFrame->route3->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m35"){
            frmMainFrame->route4->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m33"){
            frmMainFrame->route4->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m9"){
            frmMainFrame->route4->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m10"){
            frmMainFrame->route4->Add(f);
        }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode* f = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        String t = f->m_strName;
        if(t=="m12"){
            frmMainFrame->route4->Add(f);
        }
}
frmMainFrame->num = 4;
}
//---------------------------------------------------------------------------

