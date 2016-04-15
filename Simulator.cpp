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
Simulator::Simulator(bool CreateSuspended)  //构造函数
    : TThread(CreateSuspended)
{
   pLock=new TCriticalSection; //使用重要区段，每次只允许一个线程进入
   //*********By WYP at 20140511**************
  // CanStart1=new TEvent(NULL,false,true,"ThreadEvent");       //当前进程的进行标识，行人信息是否生成
   CanStart2=new TEvent(NULL,false,true,"SendMessage");       //当前进程的进行标识，从而确定其他进程是否可以开始进行
   //*****************************************
  //*********By WYP at 20140516**************
   txt=new TStringList;
   //*****************************************
   //*********By WYP at 20140530**************
   iRows=1;//初始时从第一行开始操作
   //Ex=Variant::CreateObject("Excel.Application");
   //Ex.OlePropertySet("Visible",(Variant)false);//设置Excel为不可见
   //*****************************************
   //*********By WYP at 20140609**************************
   for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++) //在执行线程之前，先初始化各节点的触发情况列表和触发节拍列表
   {
        FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        myobj->energy=10000;//初始时每个节点的能量设定为10000
   }
   //*****************************************************
   simTime=1;
   frmMainFrame->flag = false;
   num = 0;
   m_bWorking=true;                                    
   m_pUserList=new TList;
       g_pProject->m_pUserHistory->Clear();
       srand((unsigned)time(0));   //初始化随机数发生器
       if(g_pProject->m_iSwitch)
       {
           m_pMarkSensors=new TList;
           g_pProject->GetAllMarkSensors(m_pMarkSensors);//生成能产生行人的初始节点表
       }
       else
       {
           m_pMarkSensors=g_pProject->m_pFCMsNodeList;
           Initial();
       }
}
//******Changed By WYP at 20140505***20140514*****************************************************
void __fastcall Simulator::DoTerminate(void) //终止线程
{
   delete pLock;          //销毁重要区域对象
   m_pUserList->Clear();  //清空行人列表
   delete m_pUserList;    //销毁行人列表
   if(g_pProject->m_iSwitch)
   {
        m_pMarkSensors->Clear();
        delete m_pMarkSensors;
   }     
   m_bWorking=false;
   for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++) //将各个节点用到的列表清空
   {
        FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        //myobj->m_pCoveredList->Clear();
        myobj->m_pTriggeredList->Clear();
        myobj->m_psimTimeList->Clear();
        myobj->m_pGetMessageList->Clear();
   }

}
//****************************************************************************************

void __fastcall Simulator::RefreshFrame() //更新界面
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

void __fastcall Simulator::Calculate()   //线程1
{
     if(bRunning)//初始时线程并未启动
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
          WalkingUser*user=(WalkingUser*)m_pUserList->Items[i];//提取出行人列表中的每个个体
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
     //生成行人
     if(frmMainFrame->dxBarCombo1->Text=="OFF")  //Calculate按钮状态为“OFF”时
     {
        //new user or not
        int tmp=(int)g_pProject->P_Rand(g_pProject->m_dLambda);//泊松分布
        if (tmp>0.1)//new user
        {
           TList*newUserList=new TList;
           //SignCome;
           for(int k=0;k<tmp;k++)
           {
             //int comeindex=rand()%(g_pProject->m_pFCMsNodeList->Count);
             int comeindex=rand()%(m_pMarkSensors->Count); //随机确定一个即将产生行人的节点
             FCMsNode*myobj = (FCMsNode*)m_pMarkSensors->Items[comeindex]; //提取出随机选择的那个节点
             WalkingUser*user=new WalkingUser;
             user->m_iNum=g_pProject->m_pUserHistory->Count;
             user->m_iBegin=simTime;
             user->m_fMeanSpeed =g_pProject->m_dWalkingSpeed; //设置行人的平均速度
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
             user->m_pPathList->Add(n1);//将当前节点添加进行人走过的路径列表
             newUserList->Add(user);
             m_pUserList->Add(user);
             g_pProject->m_pUserHistory->Add(user);
           }
           for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
           {
                FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                g_pProject->NodeTrigger(newUserList,myobj,simTime);  //检测是否触发节点
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
        //测试生成
        else if(frmMainFrame->dxBarCombo1->Text=="ON"&&!frmMainFrame->flag&&m_pUserList->Count<1&&num<10){
        int tmp=1;
        num++;
        //只在第一次生成时运行
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
             //FCMsNode*myobj = (FCMsNode*)m_pMarkSensors->Items[comeindex];//随机选择节点
             WalkingUser*user=new WalkingUser;
             user->route = new TList;
             int index = rand()%(frmMainFrame->num); //随机选择该行人要走的路线
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
             user->m_iNum=g_pProject->m_pUserHistory->Count; //行人序号
             user->m_iBegin=simTime;
             user->m_fMeanSpeed =g_pProject->m_dWalkingSpeed;
             user->m_fVariance=g_pProject->m_fAllVariance;
             user->m_fSpeed=g_pProject->grandn(g_pProject->m_dWalkingSpeed,user->m_fVariance);
             user->X=myobj->X;//设置行人的出生位置
             user->Y=myobj->Y;
             //user->m_pLastSensor=myobj;//设置行人的出发点
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
             user->m_pPathList->Add(n1);  //user->m_pPathList指行人经过的路径列表

             m_pUserList->Add(user);
             g_pProject->m_pUserHistory->Add(user);
           }
           for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
           {
                FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                g_pProject->NodeTrigger(m_pUserList,myobj,simTime);//检测是否触发节点
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
void __fastcall Simulator::UserWalk()  //线程：行人走动(行人走到某个节点时，节点会记录被触发情况)
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
void __fastcall Simulator::SendMessage() //线程：节点传送信息(当前传递的是被触发信息)
{
        //iRows++;//指向Excel的下一行
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
                FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i]; //提取出某个节点
                //g_pProject->NodeTrigger(m_pUserList,myobj,simTime);
                if(myobj->m_dValue)
                {
                        //iRows=iRows+2;//指向Excel的下一行
                        int current_user_ID=g_pProject->NodeTrigger(m_pUserList,myobj,simTime)-1;//检测是否触发节点
                        myobj->GetCoveredNodes();    //得到覆盖范围列表
                        myobj->m_pRouteList->Add(myobj);//将节点本身添加进路由中
                        myobj->m_pGetMessageList->Items[i]="true";
                        int index_second=random(myobj->m_pCoveredList->Count);
                        FCMsNode*obj_second=(FCMsNode*)myobj->m_pCoveredList->Items[index_second];
                        myobj->m_pRouteList->Add(obj_second);
                        obj_second->m_pGetMessageList->Items[i]="true";
                        while(myobj->m_pRouteList->Items[myobj->m_pRouteList->Count-1]!=g_pProject->m_pFCMsNodeList->Items[0])//******节点列表中的第一个节点为sink节点******
                        {
                                FCMsNode*obj1=(FCMsNode*)myobj->m_pRouteList->Items[myobj->m_pRouteList->Count-1];//查找路由列表的最后一个节点，如果与列表所属节点不相同，则添加进路由表
                                obj1->GetCoveredNodes();
                                int index=random(obj1->m_pCoveredList->Count); //从当前节点的覆盖范围列表中随机选择一个节点作为路由表中的下一跳
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
                        myobj->GetBriefRouteList();//获取节点myobj的最简路由
                        //**********By WYP at 20140607***************************
                        /*for(i=0;i<myobj->m_pBrief_RouteList->Count;i++)
                        {
                               FCMsNode*obj5=(FCMsNode*)myobj->m_pBrief_RouteList->Items[i];
                               obj5->energy=obj5->energy-1;
                        }*/ 
                        //*******************************************************
                        FCMsNode*obj3 = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[0]; //提取出sink节点(节点列表中的第一个节点)

                        SetCurrentDir("D:\smart-environment-simulator20140308");
                        Boolean file_exist=FileExists("Thread_RouteListFile.txt");
                        int current_long=myobj->m_strName.Length();
                        if(file_exist) //如果文件已经存在，则直接对文件进行写操作
                        {
                                //TStringList *txt=new TStringList;
                                txt->LoadFromFile("D:\\smart-environment-simulator20140308\\Thread_RouteListFile.txt");
                                txt->Add("************************");
                                txt->Add("节拍"+IntToStr(simTime)+":");
                                txt->Add("触发当前节点的是行人"+IntToStr(current_user_ID)+":");
                                txt->Add("节点"+myobj->m_strName+"到sink节点的路由是：");
                                for(int i = 0;i<myobj->m_pBrief_RouteList->Count;i++)//******依次读取路由中的每个节点******
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
                        else   //如果文件不存在，则创建文件，再对文件进行写操作
                        {
                                int routefile=FileCreate("Thread_RouteListFile.txt");
                                //TStringList *txt=new TStringList;
                                txt->LoadFromFile("D:\\smart-environment-simulator20140308\\Thread_RouteListFile.txt");
                                txt->Add("************************");
                                txt->Add("节拍"+IntToStr(simTime)+":");
                                txt->Add("触发当前节点的是行人"+IntToStr(current_user_ID)+":");
                                txt->Add("节点"+myobj->m_strName+"到sink节点的路由是：");
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
                        Ex.OlePropertySet("Visible",(Variant)false);//设置Excel为不可见
                        Ex.OlePropertyGet("WorkBooks").OleFunction("Open",ExcelFileName.c_str());//打开工作簿
                        Wb=Ex.OlePropertyGet("ActiveWorkBook");
                        Sheet=Wb.OlePropertyGet("ActiveSheet");
                        if(iRows==1)
                        {
                                Sheet.OlePropertyGet("Cells",iRows,1).OlePropertySet("Value","触发节拍");
                                Sheet.OlePropertyGet("Cells",iRows,2).OlePropertySet("Value","行人ID");
                                Sheet.OlePropertyGet("Cells",iRows,3).OlePropertySet("Value","被触发节点");
                                Sheet.OlePropertyGet("Cells",iRows,4).OlePropertySet("Value","Sink节点");
                                Sheet.OlePropertyGet("Cells",iRows,5).OlePropertySet("Value","路由");
                                //Sheet.OlePropertyGet("Cells",iRows+2,5).OlePropertySet("Value","剩余能量");
                                //for(int i = 0;i<myobj->m_pBrief_RouteList->Count;i++)
                                //{
                                //        Sheet.OlePropertyGet("Cells",iRows,i+5).OlePropertySet("Value","路由");
                                //}
                                //iRows++;
                                Sheet.OlePropertyGet("Cells",iRows+1,1).OlePropertySet("Value",IntToStr(simTime).c_str());
                                Sheet.OlePropertyGet("Cells",iRows+1,2).OlePropertySet("Value",IntToStr(current_user_ID).c_str());
                                Sheet.OlePropertyGet("Cells",iRows+1,3).OlePropertySet("Value",myobj->m_strName.c_str());
                                Sheet.OlePropertyGet("Cells",iRows+1,4).OlePropertySet("Value",obj3->m_strName.c_str());
                                //Sheet.OlePropertyGet("Cells",iRows+2,1).OlePropertySet("Value","******");
                                //Sheet.OlePropertyGet("Cells",iRows+2,2).OlePropertySet("Value","******");
                                //Sheet.OlePropertyGet("Cells",iRows+2,3).OlePropertySet("Value","******");
                                //Sheet.OlePropertyGet("Cells",iRows+2,4).OlePropertySet("Value","剩余能量:");
                                for(int i = 0;i<myobj->m_pBrief_RouteList->Count;i++)
                                {
                                        FCMsNode*obj4=(FCMsNode*)myobj->m_pBrief_RouteList->Items[i];
                                        Sheet.OlePropertyGet("Cells",iRows+1,i+5).OlePropertySet("Value",obj4->m_strName.c_str());
                                        obj4->energy=obj4->energy-1;
                                        Sheet.OlePropertyGet("Cells",iRows+2,i+5).OlePropertySet("Value",IntToStr(obj4->energy).c_str());
                                }
                                Wb.OleProcedure("Save");//保存工作簿
                                Wb.OleProcedure("Close");//关闭表格
                                Ex.OleFunction("Quit");//退出Excel
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
                                //Sheet.OlePropertyGet("Cells",iRows+2,4).OlePropertySet("Value","剩余能量:");
                                for(int i = 0;i<myobj->m_pBrief_RouteList->Count;i++)
                                {
                                        FCMsNode*obj4=(FCMsNode*)myobj->m_pBrief_RouteList->Items[i];
                                        Sheet.OlePropertyGet("Cells",iRows,i+5).OlePropertySet("Value",obj4->m_strName.c_str());
                                        obj4->energy=obj4->energy-1;
                                        Sheet.OlePropertyGet("Cells",iRows+1,i+5).OlePropertySet("Value",IntToStr(obj4->energy).c_str());
                                }
                                Wb.OleProcedure("Save");//保存工作簿
                                Wb.OleProcedure("Close");//关闭表格
                                Ex.OleFunction("Quit");//退出Excel
                                Ex.~Variant();
                                iRows=iRows+2;
                        }
                        //iRows++;//指向Excel的下一行
                        myobj->m_pRouteList->Clear();
                        myobj->m_pBrief_RouteList->Clear();

                        //myobj->InitialTriggeredList();//初始化节点myobj覆盖列表中每个节点的覆盖节点触发情况列表
                        for(int j=0;j<myobj->m_pCoveredList->Count;j++)
                        {
                                FCMsNode*obj=(FCMsNode*)myobj->m_pCoveredList->Items[j]; //依次提取出覆盖范围列表中的每个节点，求其覆盖范围
                                //obj->GetCoveredNodes();  //计算被提取出的节点的覆盖列表
                                //for(int k=0;k<obj->m_pCoveredList->Count;k++)
                                //{
                                //     FCMsNode*obj1=(FCMsNode*)obj->m_pCoveredList->Items[k];
                                //     obj->m_pTriggeredList->Add("False");    //将覆盖列表中每个节点的被触发情况初始化设置为False
                                //}

                                for(int r=0;r<obj->m_pCoveredList->Count;r++)  //在覆盖范围类表中查找到该节点所属的父节点，将父节点触发情况设置为True
                                {
                                        FCMsNode*obj2=(FCMsNode*)obj->m_pCoveredList->Items[r];
                                        if(obj2==myobj)
                                        {
                                                //int last_simTime=StrToInt(obj->m_psimTimeList->Items[r]);
                                                if(myobj->m_dValue)
                                                {
                                                        obj->m_pTriggeredList->Items[r]="True";   //更新触发情况列表
                                                        obj->m_psimTimeList->Items[r]=(void*)(simTime); //更新触发节拍列表
                                        
                                                }
                                                else
                                                        obj->m_pTriggeredList->Items[r]="False";
                                        }
                                }
                                obj->m_pCoveredList->Clear();//清空子节点覆盖范围列表
                        }
                        myobj->m_pCoveredList->Clear();//清空父节点覆盖范围列表
                        //break;
                }
                CanStart2->SetEvent();//设置当前数据传送完毕标志
                mutex=1;

        }
        //for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)//得到每个节点的覆盖范围列表
        //{
        //        FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        //        myobj->m_pCoveredList->Clear();    //清空覆盖范围列表
        //}

}
//***********************************************************************************

//******************By WYP at 20140505***********************************************
void __fastcall Simulator::RefreshMessage()  //线程：更新被触发情况列表，将长时间没被触发的节点的触发情况设置为"False"
{
        if(bRunning)
                return;
        bRunning=true;
        simTime++;
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
                FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                g_pProject->NodeTrigger(m_pUserList,myobj,simTime);//检测是否触发节点
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
             FCMsNode*myobj = (FCMsNode*)m_pMarkSensors->Items[comeindex];//随机选择节点
             frmMainFrame->ListBox1->Items->Add(myobj->m_strName);
             WalkingUser*user=new WalkingUser;
             user->m_iNum=g_pProject->m_pUserHistory->Count;
             user->m_iBegin=simTime;
             user->m_fMeanSpeed =g_pProject->m_dWalkingSpeed;
             user->m_fVariance=g_pProject->m_fAllVariance;
             user->m_fSpeed=g_pProject->grandn(g_pProject->m_dWalkingSpeed,user->m_fVariance);
             user->X=myobj->X;//设置行人的出生位置
             user->Y=myobj->Y;
             user->m_pLastSensor=myobj;//设置行人的出发点
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
                g_pProject->NodeTrigger(m_pUserList,myobj,simTime);//检测是否触发节点
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
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++) //在执行线程之前，先初始化各节点的触发情况列表和触发节拍列表
        {
             FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
             //myobj->GetCoveredNodes();    //得到覆盖范围列表
             myobj->InitialTriggeredList(); //初始化被触发情况列表
             myobj->InitialsimTimeList();   //初始化触发节拍列表
             myobj->InitialGetMessageList();//初始化信息接收列表
             //*********By WYP at 20140607**************************
             //myobj->energy=10000;//初始时每个节点的能量设定为10000
             //*****************************************************
             
        }

        /*SetCurrentDir("D:\smart-environment-simulator20140308");
        Boolean Excel_exist=FileExists("Thread_Record.xls");
        AnsiString ExcelFileName="D:\\smart-environment-simulator20140308\\Thread_Record.xls";
        if(!Excel_exist)//如果Excel表格不存在
        {
                ShowMessage("要进行操作的Excel表格不存在！");
                return;
        }
        Ex.OlePropertyGet("WorkBooks").OleFunction("Open",ExcelFileName.c_str());//打开工作簿
        Wb=Ex.OlePropertyGet("ActiveWorkBook");
        Sheet=Wb.OlePropertyGet("ActiveSheet");
        Sheet.OlePropertyGet("Cells",iRows,1).OlePropertySet("Value","触发节拍");
        Sheet.OlePropertyGet("Cells",iRows,2).OlePropertySet("Value","行人ID");
        Sheet.OlePropertyGet("Cells",iRows,3).OlePropertySet("Value","被触发节点");
        Sheet.OlePropertyGet("Cells",iRows,4).OlePropertySet("Value","Sink节点");
        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
                Sheet.OlePropertyGet("Cells",iRows,i+5).OlePropertySet("Value","路由");
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
                                        if(CanStart2->WaitFor(INFINITE)||mutex==1) //等待信息传送线程执行完成
                                        {
                                                Synchronize((TThreadMethod)&Calculate); //执行行人信息生成线程
                                                //CanStart1->SetEvent();   //发出行人信息生成线程完成信号
                                                //CanStart2->ResetEvent();
                                        }
                                        //pLock->Release();
                                        
                                       // pLock->Acquire();
                                       //if(CanStart1->WaitFor(INFINITE))  //等待行人信息生成线程执行完成
                                       //{
                                                Synchronize((TThreadMethod)&SendMessage); //执行信息传送线程
                                                //CanStart2->SetEvent();   //发出信息传送线程完成信号
                                                //CanStart1->ResetEvent();
                                       //}
                                       //pLock->Release();
                                }
                                else
                                {
                                       // pLock->Acquire();
                                        if(CanStart2->WaitFor(INFINITE)||mutex==1) //等待信息传送线程执行完成
                                        {
                                                Synchronize((TThreadMethod)&Calculate2); //执行行人信息生成线程
                                                //CanStart1->SetEvent();  //发出行人信息生成线程完成信号
                                               // CanStart2->ResetEvent();
                                        }
                                      // pLock->Release();

                                      // pLock->Acquire();
                                       //if(CanStart1->WaitFor(INFINITE)) //等待行人信息生成线程执行完成
                                       //{
                                                Synchronize((TThreadMethod)&SendMessage); //执行信息传送线程
                                                //CanStart2->SetEvent();   //发出信息传送线程完成信号
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
                //Wb.OleProcedure("Save");//保存工作簿
                //Wb.OleProcedure("Close");//关闭表格
               // Ex.OleFunction("Quit");//退出Excel
        }
}
//**********************************************************************************************************

 