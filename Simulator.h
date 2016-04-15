
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
   void __fastcall UserWalk();  //�����߳�
   void __fastcall SendMessage(); //�ڵ㴫����Ϣ�߳�
   //********************************
    //******By WYP at 20140504********
   void __fastcall RefreshMessage(); //���±���������б�
   //********************************


private:
    TCriticalSection *pLock;
    //*******By WYP at 20140511************
    TEvent *CanStart1;   //��д�ź�������ǰ���̵Ľ��б�ʶ��ȷ��������Ϣ�Ƿ����ɣ��Ӷ�ʹ�����̶߳���Ϣ���в���
    TEvent *CanStart2;   //�ɶ��ź�������ǰ���̵Ľ��б�ʶ��ȷ�������̶߳���Ϣ�Ĳ����Ƿ���ɣ��Ӷ�ʹ�����̲߳����µ���Ϣ
    //*************************************
public:
      void Initial();
    TList*m_pUserList;
    TList*m_pMarkSensors; //�ܲ������˵ĳ�ʼ�ڵ��
    int simTime;          //�̴߳�������
    Boolean m_bWorking;
    Boolean bRunning;
    int num;
    TStringList *txt;
    int mutex;
    //************By WYP at 20140528*************
    Variant Ex,Wb,Sheet,ERange,EBorders;
    //*******************************************
    //************By WYP at 20140530************
    int iRows;//�õ���ǰExcelҪ��ʼ����
    //*******************************************

};
#endif
