
/***********************************************************************
 * Module:  Simulator.h

 ***********************************************************************/
#ifndef SimulatorH
#define SimulatorH
#include "NodeEvent.h"
#include <Classes.hpp>
#include <SyncObjs.hpp>
//*******By WYP at 20140528***********
#include "Excel_2K_SRVR.h"
//************************************
class Simulator : public TThread
{
public:
   
   int StartReasoning(void);
   Simulator(bool CreateSuspended);
protected:
    void __fastcall Execute();
    void __fastcall DoTerminate();
    void __fastcall RefreshFrame();
    void __fastcall SendData();
     void __fastcall Calculate();
   void __fastcall Calculate2();//fixed user number
   //******By WYP at 20140428********
   void __fastcall UserWalk();  //行人线程
   void __fastcall SendMessage(); //节点传送信息线程
   //********************************
    //******By WYP at 20140504********
   void __fastcall RefreshMessage(); //更新被触发情况列表
   //********************************


private:
    TCriticalSection *pLock;
    //*******By WYP at 20140511************
    TEvent *CanStart1;   //可写信号量：当前进程的进行标识，确定行人信息是否生成，从而使其他线程对信息进行操作
    TEvent *CanStart2;   //可读信号量：当前进程的进行标识，确定其他线程对信息的操作是否完成，从而使行人线程产生新的信息
    //*************************************
public:
      void Initial();
    TList*m_pUserList;
    TList*m_pMarkSensors; //能产生行人的初始节点表
    int simTime;          //线程触发节拍
    Boolean m_bWorking;
    Boolean bRunning;
    int num;
    TStringList *txt;
    int mutex;
    //************By WYP at 20140528*************
    Variant Ex,Wb,Sheet,ERange,EBorders;
    //*******************************************
    //************By WYP at 20140530************
    int iRows;//得到当前Excel要开始的行
    //*******************************************

};
#endif
