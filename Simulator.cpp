/***********************************************************************
 * Module:  Simulator.cpp
 * Purpose: Implementation of the class Simulator
 * Comment: 
 ***********************************************************************/



#include <mmsystem.hpp>
#include "MainFrame.h"
#include "Simulator.h"
#pragma package(smart_init)
//*********By WYP at 20140528**************************
#pragma link "Excel_2K_SRVR"
//*****************************************************
Simulator::Simulator(bool CreateSuspended)  //���캯��
    : TThread(CreateSuspended)
{
   pLock=new TCriticalSection; //ʹ����Ҫ���Σ�ÿ��ֻ����һ���߳̽���
   //*********By WYP at 20140511**************
  // CanStart1=new TEvent(NULL,false,true,"ThreadEvent");       //��ǰ���̵Ľ��б�ʶ��������Ϣ�Ƿ�����
   CanStart2=new TEvent(NULL,false,true,"SendMessage");       //��ǰ���̵Ľ��б�ʶ���Ӷ�ȷ�����������Ƿ���Կ�ʼ����
   //*****************************************
  //*********By WYP at 20140516**************
   txt=new TStringList;
   //*****************************************
   //*********By WYP at 20140530**************
   iRows=1;//��ʼʱ�ӵ�һ�п�ʼ����
   //Ex=Variant::CreateObject("Excel.Application");
   //Ex.OlePropertySet("Visible",(Variant)false);//����ExcelΪ���ɼ�
   //*****************************************
   //*********By WYP at 20140609**************************
   for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++) //��ִ���߳�֮ǰ���ȳ�ʼ�����ڵ�Ĵ�������б�ʹ��������б�
   {
        FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        myobj->energy=10000;//��ʼʱÿ���ڵ�������趨Ϊ10000
   }
   //*****************************************************
   simTime=1;
   frmMainFrame->flag = false;
   num = 0;
   m_bWorking=true;                                    
   m_pUserList=new TList;
       g_pProject->m_pUserHistory->Clear();
       srand((unsigned)time(0));   //��ʼ�������������
       if(g_pProject->m_iSwitch)
       {
           m_pMarkSensors=new TList;
           g_pProject->GetAllMarkSensors(m_pMarkSensors);//�����ܲ������˵ĳ�ʼ�ڵ��
       }
       else
       {
           m_pMarkSensors=g_pProject->m_pFCMsNodeList;
           Initial();
       }
}
//******Changed By WYP at 20140505***20140514*****************************************************
void __fastcall Simulator::DoTerminate(void) //��ֹ�߳�
{
   delete pLock;          //������Ҫ�������
   m_pUserList->Clear();  //��������б�
   delete m_pUserList;    //���������б�
   if(g_pProject->m_iSwitch)
   {
        m_pMarkSensors->Clear();
        delete m_pMarkSensors;
   }     
   m_bWorking=false;
   for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++) //�������ڵ��õ����б����
   {
        FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        //myobj->m_pCoveredList->Clear();
        myobj->m_pTriggeredList->Clear();
        myobj->m_psimTimeList->Clear();
        myobj->m_pGetMessageList->Clear();
   }

}
//****************************************************************************************

void __fastcall Simulator::RefreshFrame() //���½���
{
   // if(frmMainFrame->FrameOutput->PageControl->ActivePageIndex!=3)
     //  frmMainFrame->FrameOutput->PageControl->ActivePageIndex=3;
    frmMainFrame->Refresh();
    frmMainFrame->FrameOutput->Invalidate();
}

void __fastcall Simulator::SendData()
{
    frmMainFrame->SendData();
}

void __fastcall Simulator::Calculate()   //�߳�1
{
     if(bRunning)//��ʼʱ�̲߳�δ����
        return;
     bRunning=true;
     simTime++;
     //all sensor has triggered data =0;
     for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
     {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          myobj->m_dValue=0;
     }
     //current user keep walking
     for(int i=0;i<m_pUserList->Count;i++)
     {
          WalkingUser*user=(WalkingUser*)m_pUserList->Items[i];//��ȡ�������б��е�ÿ������
          if(g_pProject->NextStep2(user,simTime)<0)
          {
            user->m_iEnd=simTime;
            m_pUserList->Delete(i);
            i--;
          }
     }
     for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
     {
                FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                g_pProject->NodeTrigger(m_pUserList,myobj,simTime);
     }
     //��������
     if(frmMainFrame->dxBarCombo1->Text=="OFF")  //Calculate��ť״̬Ϊ��OFF��ʱ
     {
        //new user or not
        int tmp=(int)g_pProject->P_Rand(g_pProject->m_dLambda);//���ɷֲ�
        if (tmp>0.1)//new user
        {
           TList*newUserList=new TList;
           //SignCome;
           for(int k=0;k<tmp;k++)
           {
             //int comeindex=rand()%(g_pProject->m_pFCMsNodeList->Count);
             int comeindex=rand()%(m_pMarkSensors->Count); //���ȷ��һ�������������˵Ľڵ�
             FCMsNode*myobj = (FCMsNode*)m_pMarkSensors->Items[comeindex]; //��ȡ�����ѡ����Ǹ��ڵ�
             WalkingUser*user=new WalkingUser;
             user->m_iNum=g_pProject->m_pUserHistory->Count;
             user->m_iBegin=simTime;
             user->m_fMeanSpeed =g_pProject->m_dWalkingSpeed; //�������˵�ƽ���ٶ�
             user->m_fVariance=g_pProject->m_fAllVariance;
             user->m_fSpeed=g_pProject->grandn(g_pProject->m_dWalkingSpeed,user->m_fVariance);
             user->X=myobj->X;
             user->Y=myobj->Y;
             user->m_pLastSensor=myobj;
             user->sx=myobj->X;
             user->sy=myobj->Y;
             user->m_iPoint=-1;
             HISNODE*n1=new HISNODE;
             n1->pNode=myobj;
             n1->iTime=simTime;
             user->m_pPathList->Add(n1);//����ǰ�ڵ���ӽ������߹���·���б�
             newUserList->Add(user);
             m_pUserList->Add(user);
             g_pProject->m_pUserHistory->Add(user);
           }
           for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
           {
                FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                g_pProject->NodeTrigger(newUserList,myobj,simTime);  //����Ƿ񴥷��ڵ�
           }
           newUserList->Clear();
           delete newUserList;
        }
        //save all sensor triggered data
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          myobj->StoreOldData(myobj->m_dValue);
        }
        }
        //��������
        else if(frmMainFrame->dxBarCombo1->Text=="ON"&&!frmMainFrame->flag&&m_pUserList->Count<1&&num<10){
        int tmp=1;
        num++;
        //ֻ�ڵ�һ������ʱ����
        if(frmMainFrame->flag)
        {
            return ;
        }
        frmMainFrame->flag = false;
        if (tmp>0.1)//new user
        {
        FCMsNode*myobj;
        FCMsNode*nobj;
        TList*newUserList=new TList;
           //SignCome;
           for(int k=0;k<tmp;k++)
           {
             //int comeindex=rand()%(m_pFCMsNodeList->Count);
             /*for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*my = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          if(my->m_strName==frmMainFrame->ListBoxSim->Items->Strings[0]){
              myobj = my;
              break;
          }
        }
             for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*my = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          if(my->m_strName==frmMainFrame->ListBoxSim->Items->Strings[1]){
              nobj = my;
              break;
          }
        }*/
             //int comeindex=rand()%(m_pMarkSensors->Count);
             //FCMsNode*myobj = (FCMsNode*)m_pMarkSensors->Items[comeindex];//���ѡ��ڵ�
             WalkingUser*user=new WalkingUser;
             user->route = new TList;
             int index = rand()%(frmMainFrame->num); //���ѡ�������Ҫ�ߵ�·��
             //************By WYP at 20150525***************************
             user->route=frmMainFrame->RouteOfTemp.at(index);
             //*********************************************************
             /*if(index==0){
                 user->route = frmMainFrame->route1;
             }
             else if(index==1){
                 user->route = frmMainFrame->route2;
             }
             else if(index==2){
                 user->route = frmMainFrame->route3;
             }
             else if(index==3){
                 user->route = frmMainFrame->route4;
             }
             //*******By WYP at 20150426*********************************
              else if(index==4){
                 user->route = frmMainFrame->route5;
             }
              else if(index==5){
                 user->route = frmMainFrame->route6;
             }
              else if(index==6){
                 user->route = frmMainFrame->route7;
             }
              else if(index==7){
                 user->route = frmMainFrame->route8;
             }
              else if(index==8){
                 user->route = frmMainFrame->route9;
             } */
             //**********************************************************
             myobj = (FCMsNode*)user->route->Items[0];
             nobj = (FCMsNode*)user->route->Items[1];
             user->m_iNum=g_pProject->m_pUserHistory->Count; //�������
             user->m_iBegin=simTime;
             user->m_fMeanSpeed =g_pProject->m_dWalkingSpeed;
             user->m_fVariance=g_pProject->m_fAllVariance;
             user->m_fSpeed=g_pProject->grandn(g_pProject->m_dWalkingSpeed,user->m_fVariance);
             user->X=myobj->X;//�������˵ĳ���λ��
             user->Y=myobj->Y;
             //user->m_pLastSensor=myobj;//�������˵ĳ�����
             //user->m_pNextSensor = nobj;
             user->sx=myobj->X;
             user->sy=myobj->Y;
             user->dx = nobj->X;
             user->dy = nobj->Y;
             user->m_iPoint=-1;
             user->num = 0;
             HISNODE*n1=new HISNODE;
             n1->pNode=myobj;
             n1->iTime=simTime;
             user->m_pPathList->Add(n1);  //user->m_pPathListָ���˾�����·���б�

             m_pUserList->Add(user);
             g_pProject->m_pUserHistory->Add(user);
           }
           for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
           {
                FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                g_pProject->NodeTrigger(m_pUserList,myobj,simTime);//����Ƿ񴥷��ڵ�
           }
            newUserList->Clear();
            delete newUserList;
        }
        //save all sensor triggered data
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          myobj->StoreOldData(myobj->m_dValue);
        }
        }
        mutex=0;
        CanStart2->ResetEvent();
        bRunning=false;


}
void __fastcall Simulator::Calculate2()
{
     if(bRunning)return;
     bRunning=true;
     simTime++;
       //all sensor has triggered data =0;
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          myobj->m_dValue=0;
        }
        //current user keep walking
        for(int i=0;i<m_pUserList->Count;i++)
        {
          WalkingUser*user=(WalkingUser*)m_pUserList->Items[i];
          if(g_pProject->NextStep2(user,simTime)<0)
          {
            user->m_iEnd=simTime;
            m_pUserList->Delete(i);
            i--;
          }
        }
           for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
           {
                FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                g_pProject->NodeTrigger(m_pUserList,myobj,simTime);
           }
           AddSimulatingOutput("----",NULL);
        //save all sensor triggered data
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          myobj->StoreOldData(myobj->m_dValue);
        }
        mutex=0;
        CanStart2->ResetEvent();
        bRunning=false;
}

//******************By WYP at 20140428***20140430***20140503***20140504***20140513***20140521***20140523*********************
void __fastcall Simulator::UserWalk()  //�̣߳������߶�(�����ߵ�ĳ���ڵ�ʱ���ڵ���¼���������)
{
        if(bRunning)
                return;
        bRunning=true;
        simTime++;
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
                FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                g_pProject->NodeTrigger(m_pUserList,myobj,simTime);
        }

}
void __fastcall Simulator::SendMessage() //�̣߳��ڵ㴫����Ϣ(��ǰ���ݵ��Ǳ�������Ϣ)
{
        //iRows++;//ָ��Excel����һ��
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
                FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i]; //��ȡ��ĳ���ڵ�
                //g_pProject->NodeTrigger(m_pUserList,myobj,simTime);
                if(myobj->m_dValue)
                {
                        //iRows=iRows+2;//ָ��Excel����һ��
                        int current_user_ID=g_pProject->NodeTrigger(m_pUserList,myobj,simTime)-1;//����Ƿ񴥷��ڵ�
                        myobj->GetCoveredNodes();    //�õ����Ƿ�Χ�б�
                        myobj->m_pRouteList->Add(myobj);//���ڵ㱾����ӽ�·����
                        myobj->m_pGetMessageList->Items[i]="true";
                        int index_second=random(myobj->m_pCoveredList->Count);
                        FCMsNode*obj_second=(FCMsNode*)myobj->m_pCoveredList->Items[index_second];
                        myobj->m_pRouteList->Add(obj_second);
                        obj_second->m_pGetMessageList->Items[i]="true";
                        while(myobj->m_pRouteList->Items[myobj->m_pRouteList->Count-1]!=g_pProject->m_pFCMsNodeList->Items[0])//******�ڵ��б��еĵ�һ���ڵ�Ϊsink�ڵ�******
                        {
                                FCMsNode*obj1=(FCMsNode*)myobj->m_pRouteList->Items[myobj->m_pRouteList->Count-1];//����·���б�����һ���ڵ㣬������б������ڵ㲻��ͬ������ӽ�·�ɱ�
                                obj1->GetCoveredNodes();
                                int index=random(obj1->m_pCoveredList->Count); //�ӵ�ǰ�ڵ�ĸ��Ƿ�Χ�б������ѡ��һ���ڵ���Ϊ·�ɱ��е���һ��
                                FCMsNode*obj2=(FCMsNode*)obj1->m_pCoveredList->Items[index];
                                //if(!(obj2->IsInList(myobj->m_pRouteList)))
                                //{
                                myobj->m_pRouteList->Add(obj2);
                                //obj2->m_pGetMessageList->Items[i]="true";
                                //}
                                /*else
                                {
                                        if(index<(obj1->m_pCoveredList->Count)/2)
                                        {
                                            FCMsNode*obj3=(FCMsNode*)obj1->m_pCoveredList->Items[index+1];
                                            if(!(obj3->IsInList(myobj->m_pRouteList)))
                                            {
                                                myobj->m_pRouteList->Add(obj3);
                                                obj3->m_pGetMessageList->Items[i]="true";
                                            }
                                        }
                                        else
                                        {
                                                FCMsNode*obj3=(FCMsNode*)obj1->m_pCoveredList->Items[index-1];
                                                if(!(obj3->IsInList(myobj->m_pRouteList)))
                                                {
                                                        myobj->m_pRouteList->Add(obj3);
                                                        obj3->m_pGetMessageList->Items[i]="true";
                                                }
                                        }
                                }*/
                                obj1->m_pCoveredList->Clear();
                        }
                        myobj->GetBriefRouteList();//��ȡ�ڵ�myobj�����·��
                        //**********By WYP at 20140607***************************
                        /*for(i=0;i<myobj->m_pBrief_RouteList->Count;i++)
                        {
                               FCMsNode*obj5=(FCMsNode*)myobj->m_pBrief_RouteList->Items[i];
                               obj5->energy=obj5->energy-1;
                        }*/ 
                        //*******************************************************
                        FCMsNode*obj3 = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[0]; //��ȡ��sink�ڵ�(�ڵ��б��еĵ�һ���ڵ�)

                        SetCurrentDir("D:\smart-environment-simulator20140308");
                        Boolean file_exist=FileExists("Thread_RouteListFile.txt");
                        int current_long=myobj->m_strName.Length();
                        if(file_exist) //����ļ��Ѿ����ڣ���ֱ�Ӷ��ļ�����д����
                        {
                                //TStringList *txt=new TStringList;
                                txt->LoadFromFile("D:\\smart-environment-simulator20140308\\Thread_RouteListFile.txt");
                                txt->Add("************************");
                                txt->Add("����"+IntToStr(simTime)+":");
                                txt->Add("������ǰ�ڵ��������"+IntToStr(current_user_ID)+":");
                                txt->Add("�ڵ�"+myobj->m_strName+"��sink�ڵ��·���ǣ�");
                                for(int i = 0;i<myobj->m_pBrief_RouteList->Count;i++)//******���ζ�ȡ·���е�ÿ���ڵ�******
                                {
                                        FCMsNode*obj4=(FCMsNode*)myobj->m_pBrief_RouteList->Items[i];
                                        txt->Add(obj4->m_strName);
                                        //txt->SaveToFile("D:\\smart-environment-simulator20140308\\Thread_RouteListFile.txt");
                                }
                                txt->SaveToFile("D:\\smart-environment-simulator20140308\\Thread_RouteListFile.txt");
                                txt->Clear();
                                //FileClose(file_open);
                                //txt->Add("************************");
                        }
                        else   //����ļ������ڣ��򴴽��ļ����ٶ��ļ�����д����
                        {
                                int routefile=FileCreate("Thread_RouteListFile.txt");
                                //TStringList *txt=new TStringList;
                                txt->LoadFromFile("D:\\smart-environment-simulator20140308\\Thread_RouteListFile.txt");
                                txt->Add("************************");
                                txt->Add("����"+IntToStr(simTime)+":");
                                txt->Add("������ǰ�ڵ��������"+IntToStr(current_user_ID)+":");
                                txt->Add("�ڵ�"+myobj->m_strName+"��sink�ڵ��·���ǣ�");
                                for(int i = 0;myobj->m_pBrief_RouteList->Count;i++)
                                {
                                        FCMsNode*obj4=(FCMsNode*)myobj->m_pBrief_RouteList->Items[i];
                                        txt->Add(obj4->m_strName);
                                        //txt->SaveToFile("D:\\smart-environment-simulator20140308\\Thread_RouteListFile.txt");
                                }
                                txt->SaveToFile("D:\\smart-environment-simulator20140308\\Thread_RouteListFile.txt");
                                txt->Clear();
                                //FileClose(file_open);
                                //txt->Add("************************");
                        }

                        //SetCurrentDir("D:\smart-environment-simulator20140308");
                        //Boolean Excel_exist=FileExists("Thread_Record.xls");
                        AnsiString ExcelFileName="D:\\smart-environment-simulator20140308\\Thread_Record.xls";
                        Ex=Variant::CreateObject("Excel.Application");
                        Ex.OlePropertySet("Visible",(Variant)false);//����ExcelΪ���ɼ�
                        Ex.OlePropertyGet("WorkBooks").OleFunction("Open",ExcelFileName.c_str());//�򿪹�����
                        Wb=Ex.OlePropertyGet("ActiveWorkBook");
                        Sheet=Wb.OlePropertyGet("ActiveSheet");
                        if(iRows==1)
                        {
                                Sheet.OlePropertyGet("Cells",iRows,1).OlePropertySet("Value","��������");
                                Sheet.OlePropertyGet("Cells",iRows,2).OlePropertySet("Value","����ID");
                                Sheet.OlePropertyGet("Cells",iRows,3).OlePropertySet("Value","�������ڵ�");
                                Sheet.OlePropertyGet("Cells",iRows,4).OlePropertySet("Value","Sink�ڵ�");
                                Sheet.OlePropertyGet("Cells",iRows,5).OlePropertySet("Value","·��");
                                //Sheet.OlePropertyGet("Cells",iRows+2,5).OlePropertySet("Value","ʣ������");
                                //for(int i = 0;i<myobj->m_pBrief_RouteList->Count;i++)
                                //{
                                //        Sheet.OlePropertyGet("Cells",iRows,i+5).OlePropertySet("Value","·��");
                                //}
                                //iRows++;
                                Sheet.OlePropertyGet("Cells",iRows+1,1).OlePropertySet("Value",IntToStr(simTime).c_str());
                                Sheet.OlePropertyGet("Cells",iRows+1,2).OlePropertySet("Value",IntToStr(current_user_ID).c_str());
                                Sheet.OlePropertyGet("Cells",iRows+1,3).OlePropertySet("Value",myobj->m_strName.c_str());
                                Sheet.OlePropertyGet("Cells",iRows+1,4).OlePropertySet("Value",obj3->m_strName.c_str());
                                //Sheet.OlePropertyGet("Cells",iRows+2,1).OlePropertySet("Value","******");
                                //Sheet.OlePropertyGet("Cells",iRows+2,2).OlePropertySet("Value","******");
                                //Sheet.OlePropertyGet("Cells",iRows+2,3).OlePropertySet("Value","******");
                                //Sheet.OlePropertyGet("Cells",iRows+2,4).OlePropertySet("Value","ʣ������:");
                                for(int i = 0;i<myobj->m_pBrief_RouteList->Count;i++)
                                {
                                        FCMsNode*obj4=(FCMsNode*)myobj->m_pBrief_RouteList->Items[i];
                                        Sheet.OlePropertyGet("Cells",iRows+1,i+5).OlePropertySet("Value",obj4->m_strName.c_str());
                                        obj4->energy=obj4->energy-1;
                                        Sheet.OlePropertyGet("Cells",iRows+2,i+5).OlePropertySet("Value",IntToStr(obj4->energy).c_str());
                                }
                                Wb.OleProcedure("Save");//���湤����
                                Wb.OleProcedure("Close");//�رձ��
                                Ex.OleFunction("Quit");//�˳�Excel
                                Ex.~Variant();
                                iRows=iRows+3;
                        }
                        else
                        {
                                Sheet.OlePropertyGet("Cells",iRows,1).OlePropertySet("Value",IntToStr(simTime).c_str());
                                Sheet.OlePropertyGet("Cells",iRows,2).OlePropertySet("Value",IntToStr(current_user_ID).c_str());
                                Sheet.OlePropertyGet("Cells",iRows,3).OlePropertySet("Value",myobj->m_strName.c_str());
                                Sheet.OlePropertyGet("Cells",iRows,4).OlePropertySet("Value",obj3->m_strName.c_str());
                                //Sheet.OlePropertyGet("Cells",iRows+2,1).OlePropertySet("Value","******");
                                //Sheet.OlePropertyGet("Cells",iRows+2,2).OlePropertySet("Value","******");
                                //Sheet.OlePropertyGet("Cells",iRows+2,3).OlePropertySet("Value","******");
                                //Sheet.OlePropertyGet("Cells",iRows+2,4).OlePropertySet("Value","ʣ������:");
                                for(int i = 0;i<myobj->m_pBrief_RouteList->Count;i++)
                                {
                                        FCMsNode*obj4=(FCMsNode*)myobj->m_pBrief_RouteList->Items[i];
                                        Sheet.OlePropertyGet("Cells",iRows,i+5).OlePropertySet("Value",obj4->m_strName.c_str());
                                        obj4->energy=obj4->energy-1;
                                        Sheet.OlePropertyGet("Cells",iRows+1,i+5).OlePropertySet("Value",IntToStr(obj4->energy).c_str());
                                }
                                Wb.OleProcedure("Save");//���湤����
                                Wb.OleProcedure("Close");//�رձ��
                                Ex.OleFunction("Quit");//�˳�Excel
                                Ex.~Variant();
                                iRows=iRows+2;
                        }
                        //iRows++;//ָ��Excel����һ��
                        myobj->m_pRouteList->Clear();
                        myobj->m_pBrief_RouteList->Clear();

                        //myobj->InitialTriggeredList();//��ʼ���ڵ�myobj�����б���ÿ���ڵ�ĸ��ǽڵ㴥������б�
                        for(int j=0;j<myobj->m_pCoveredList->Count;j++)
                        {
                                FCMsNode*obj=(FCMsNode*)myobj->m_pCoveredList->Items[j]; //������ȡ�����Ƿ�Χ�б��е�ÿ���ڵ㣬���串�Ƿ�Χ
                                //obj->GetCoveredNodes();  //���㱻��ȡ���Ľڵ�ĸ����б�
                                //for(int k=0;k<obj->m_pCoveredList->Count;k++)
                                //{
                                //     FCMsNode*obj1=(FCMsNode*)obj->m_pCoveredList->Items[k];
                                //     obj->m_pTriggeredList->Add("False");    //�������б���ÿ���ڵ�ı����������ʼ������ΪFalse
                                //}

                                for(int r=0;r<obj->m_pCoveredList->Count;r++)  //�ڸ��Ƿ�Χ����в��ҵ��ýڵ������ĸ��ڵ㣬�����ڵ㴥���������ΪTrue
                                {
                                        FCMsNode*obj2=(FCMsNode*)obj->m_pCoveredList->Items[r];
                                        if(obj2==myobj)
                                        {
                                                //int last_simTime=StrToInt(obj->m_psimTimeList->Items[r]);
                                                if(myobj->m_dValue)
                                                {
                                                        obj->m_pTriggeredList->Items[r]="True";   //���´�������б�
                                                        obj->m_psimTimeList->Items[r]=(void*)(simTime); //���´��������б�
                                        
                                                }
                                                else
                                                        obj->m_pTriggeredList->Items[r]="False";
                                        }
                                }
                                obj->m_pCoveredList->Clear();//����ӽڵ㸲�Ƿ�Χ�б�
                        }
                        myobj->m_pCoveredList->Clear();//��ո��ڵ㸲�Ƿ�Χ�б�
                        //break;
                }
                CanStart2->SetEvent();//���õ�ǰ���ݴ�����ϱ�־
                mutex=1;

        }
        //for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)//�õ�ÿ���ڵ�ĸ��Ƿ�Χ�б�
        //{
        //        FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        //        myobj->m_pCoveredList->Clear();    //��ո��Ƿ�Χ�б�
        //}

}
//***********************************************************************************

//******************By WYP at 20140505***********************************************
void __fastcall Simulator::RefreshMessage()  //�̣߳����±���������б�����ʱ��û�������Ľڵ�Ĵ����������Ϊ"False"
{
        if(bRunning)
                return;
        bRunning=true;
        simTime++;
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
                FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                g_pProject->NodeTrigger(m_pUserList,myobj,simTime);//����Ƿ񴥷��ڵ�
        }
}
//***********************************************************************************
void Simulator::Initial()
{
      //new user or not
        int tmp=g_pProject->m_dLambda;
        if (tmp>0.1)//new user
        {
           //SignCome;
           for(int k=0;k<tmp;k++)
           {
             //int comeindex=rand()%(m_pFCMsNodeList->Count);
             int comeindex=rand()%(m_pMarkSensors->Count);
             FCMsNode*myobj = (FCMsNode*)m_pMarkSensors->Items[comeindex];//���ѡ��ڵ�
             frmMainFrame->ListBox1->Items->Add(myobj->m_strName);
             WalkingUser*user=new WalkingUser;
             user->m_iNum=g_pProject->m_pUserHistory->Count;
             user->m_iBegin=simTime;
             user->m_fMeanSpeed =g_pProject->m_dWalkingSpeed;
             user->m_fVariance=g_pProject->m_fAllVariance;
             user->m_fSpeed=g_pProject->grandn(g_pProject->m_dWalkingSpeed,user->m_fVariance);
             user->X=myobj->X;//�������˵ĳ���λ��
             user->Y=myobj->Y;
             user->m_pLastSensor=myobj;//�������˵ĳ�����
             user->sx=myobj->X;
             user->sy=myobj->Y;
             user->m_iPoint=-1;
             HISNODE*n1=new HISNODE;
             n1->pNode=myobj;
             n1->iTime=simTime;
             user->m_pPathList->Add(n1);

             m_pUserList->Add(user);
             g_pProject->m_pUserHistory->Add(user);
           }
           for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
           {
                FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                g_pProject->NodeTrigger(m_pUserList,myobj,simTime);//����Ƿ񴥷��ڵ�
           }
           AddSimulatingOutput("----",NULL);
        }
        //save all sensor triggered data
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          myobj->StoreOldData(myobj->m_dValue);
        }
}

//************Changed By WYP at 20140505***20140507***20140511***20140513***20140516***20140530*****************************************************
void __fastcall Simulator::Execute()
{
        mutex=1;
        //iRows=1;
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++) //��ִ���߳�֮ǰ���ȳ�ʼ�����ڵ�Ĵ�������б�ʹ��������б�
        {
             FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
             //myobj->GetCoveredNodes();    //�õ����Ƿ�Χ�б�
             myobj->InitialTriggeredList(); //��ʼ������������б�
             myobj->InitialsimTimeList();   //��ʼ�����������б�
             myobj->InitialGetMessageList();//��ʼ����Ϣ�����б�
             //*********By WYP at 20140607**************************
             //myobj->energy=10000;//��ʼʱÿ���ڵ�������趨Ϊ10000
             //*****************************************************
             
        }

        /*SetCurrentDir("D:\smart-environment-simulator20140308");
        Boolean Excel_exist=FileExists("Thread_Record.xls");
        AnsiString ExcelFileName="D:\\smart-environment-simulator20140308\\Thread_Record.xls";
        if(!Excel_exist)//���Excel��񲻴���
        {
                ShowMessage("Ҫ���в�����Excel��񲻴��ڣ�");
                return;
        }
        Ex.OlePropertyGet("WorkBooks").OleFunction("Open",ExcelFileName.c_str());//�򿪹�����
        Wb=Ex.OlePropertyGet("ActiveWorkBook");
        Sheet=Wb.OlePropertyGet("ActiveSheet");
        Sheet.OlePropertyGet("Cells",iRows,1).OlePropertySet("Value","��������");
        Sheet.OlePropertyGet("Cells",iRows,2).OlePropertySet("Value","����ID");
        Sheet.OlePropertyGet("Cells",iRows,3).OlePropertySet("Value","�������ڵ�");
        Sheet.OlePropertyGet("Cells",iRows,4).OlePropertySet("Value","Sink�ڵ�");
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
                Sheet.OlePropertyGet("Cells",iRows,i+5).OlePropertySet("Value","·��");
        } */
        while(!Terminated)
        {
                if(m_bWorking)
                {
                        if(simTime<=g_pProject->m_nIteratTime)
                        {
                                if(g_pProject->m_iSwitch)
                                {
                                        //pLock->Acquire();
                                        if(CanStart2->WaitFor(INFINITE)||mutex==1) //�ȴ���Ϣ�����߳�ִ�����
                                        {
                                                Synchronize((TThreadMethod)&Calculate); //ִ��������Ϣ�����߳�
                                                //CanStart1->SetEvent();   //����������Ϣ�����߳�����ź�
                                                //CanStart2->ResetEvent();
                                        }
                                        //pLock->Release();
                                        
                                       // pLock->Acquire();
                                       //if(CanStart1->WaitFor(INFINITE))  //�ȴ�������Ϣ�����߳�ִ�����
                                       //{
                                                Synchronize((TThreadMethod)&SendMessage); //ִ����Ϣ�����߳�
                                                //CanStart2->SetEvent();   //������Ϣ�����߳�����ź�
                                                //CanStart1->ResetEvent();
                                       //}
                                       //pLock->Release();
                                }
                                else
                                {
                                       // pLock->Acquire();
                                        if(CanStart2->WaitFor(INFINITE)||mutex==1) //�ȴ���Ϣ�����߳�ִ�����
                                        {
                                                Synchronize((TThreadMethod)&Calculate2); //ִ��������Ϣ�����߳�
                                                //CanStart1->SetEvent();  //����������Ϣ�����߳�����ź�
                                               // CanStart2->ResetEvent();
                                        }
                                      // pLock->Release();

                                      // pLock->Acquire();
                                       //if(CanStart1->WaitFor(INFINITE)) //�ȴ�������Ϣ�����߳�ִ�����
                                       //{
                                                Synchronize((TThreadMethod)&SendMessage); //ִ����Ϣ�����߳�
                                                //CanStart2->SetEvent();   //������Ϣ�����߳�����ź�
                                                //CanStart1->ResetEvent();
                                       //}
                                       //pLock->Release();
                                }
                                if(g_pProject->m_nWorkType==1)
                                {
                                        Synchronize((TThreadMethod)&RefreshFrame);
                                        if(!g_pProject->m_iSwitch)
                                                Synchronize((TThreadMethod)&SendData);
                                 }
                        }
                        else
                        {
                                m_bWorking=false;
                        }
                }
                if(g_pProject->m_nWorkType==1)
                {
                        if(g_pProject->m_iSwitch)
                                Sleep(200);
                        else
                        {
                                Sleep(2000);
                        }
                }
                //txt->SaveToFile("D:\\smart-environment-simulator20140308\\Thread_RouteListFile.txt");
                //txt->Clear();
                //Wb.OleProcedure("Save");//���湤����
                //Wb.OleProcedure("Close");//�رձ��
               // Ex.OleFunction("Quit");//�˳�Excel
        }
}
//**********************************************************************************************************

 