
#include "ReasonMachine.h"
#include "MainFrame.h"
#include <math.h>
#pragma package(smart_init)

__fastcall ReasonMachine::ReasonMachine()
{
  m_pFCMsHistory=new TList;
}
__fastcall ReasonMachine::~ReasonMachine()
{
    for(int i=0;i<m_pFCMsHistory->Count;i++)
    {
        Matrix *node=(Matrix *)m_pFCMsHistory->Items[i];
        delete node;
    }
    m_pFCMsHistory->Clear();
    delete m_pFCMsHistory;
}
void __fastcall ReasonMachine::GetCanBeginWorkRuleSetList()
{

}

void __fastcall ReasonMachine::BeginWork()
{
}
void __fastcall ReasonMachine::GetRootNodesList()
{

}
NodeEvent* __fastcall ReasonMachine::GetBeginNode()
{
  return m_pReasonNode;
}
void __fastcall ReasonMachine::GetParentChild()
{
   if(m_pReasonNode->m_pConnectedList->Count==0)
      m_pReasonNode=NULL;
   else
   {
      LineEvent*lk=(LineEvent*)m_pReasonNode->m_pConnectedList->Items[0];
      m_pReasonNode=lk->ObjectDest;
   }
}
void ReasonMachine::ConstructMatrix(Matrix *FCMsM)
{
    long a=0;
    for(int i=0;i<g_pProject->m_pFCMsNodeList->Count;i++)
    {
        FCMsNode*out=(FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        for(int j=0;j<g_pProject->m_pFCMsNodeList->Count;j++)
        {
           if(i==j)//自己不能导致自己发生
           {
             (*FCMsM)(i+1,j+1)=0;
             a++;
             continue;
           }
           FCMsNode*in=(FCMsNode*)g_pProject->m_pFCMsNodeList->Items[j];
           LineEvent*link=g_pProject->GetLineEventBetweenNodes(out,in);
           if(link==NULL)
           {
             (*FCMsM)(i+1,j+1)=0;
             a++;
             continue;
           }
           (*FCMsM)(i+1,j+1)=link->m_dDistance;
             a++;
        }
    }
    a=a;
}
void ReasonMachine::GetValueOfFCMs(Matrix&FCMsM)
{
    for(int i=0;i<g_pProject->m_pFCMsNodeList->Count;i++)
    {
        FCMsNode*out=(FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        FCMsM(1,i+1)=1;
    }
}
void ReasonMachine::SetValueOfFCMs(Matrix&FCMsM)
{
    for(int i=0;i<g_pProject->m_pFCMsNodeList->Count;i++)
    {
        FCMsNode*out=(FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
      
    }
}
void ReasonMachine::ThresholdFCMs(Matrix&FCMsM)
{
    double dReturn;
    for(int i=0;i<FCMsM.GetCol() ;i++)
    {
        double dValue=FCMsM(1,i+1);
        FCMsM(1,i+1)= dReturn;
    }
}
int ReasonMachine::HasCircle()//
{
     if(m_pFCMsHistory->Count<2)return -1;
     Matrix*newone = (Matrix*)m_pFCMsHistory->Items[m_pFCMsHistory->Count-1];
     for (int i = 0; i < m_pFCMsHistory->Count-1; i++)
     {
         Matrix*obj = (Matrix*)m_pFCMsHistory->Items[i];
         if((*newone)==(*obj))
           return i;
     }
     return -1;
}

void __fastcall ReasonMachine::Calculate()
{
     for(int i=0;i<g_pProject->m_pLineEventList->Count;i++)
     {
          LineEvent*obj1 = (LineEvent*)g_pProject->m_pLineEventList->Items[i];
          FCMsNode*s=(FCMsNode*)obj1->ObjectSource;
          FCMsNode*d=(FCMsNode*)obj1->ObjectDest;

          if(obj1->points!=NULL&&obj1->points->Count>0)
          {
           float tmp=0;
           INFLEXTION*p;
           for(int j=0;j<obj1->points->Count;j++)
           {
              p=(INFLEXTION*)obj1->points->Items[j];
              tmp=tmp+sqrt((s->X-p->p.x)*(s->X-p->p.x)+(s->Y-p->p.y)*(s->Y-p->p.y));
           }
           tmp=tmp+sqrt((d->X-p->p.x)*(d->X-p->p.x)+(d->Y-p->p.y)*(d->Y-p->p.y));
           obj1->m_dDistance=g_pProject->m_dUnitDistance*tmp;
         }
         else
         {
           float dis=sqrt((s->X-d->X)*(s->X-d->X)+(s->Y-d->Y)*(s->Y-d->Y));
           obj1->m_dDistance=g_pProject->m_dUnitDistance*dis;
         }
     }
}


