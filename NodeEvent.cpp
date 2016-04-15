//---------------------------------------------------------------------------
#pragma hdrstop
//---------------------------------------------------------------------------
#include <Math.h>
#include "NodeEvent.h"
#include "LineEvent.h"
//#include "WalkingUser.h"
#include "property.h"
#include "MainFrame.h"
//#include "projectModel.h"
//#include "property.h"

//#pragma package(smart_init)
//#pragma link "dxCntner"
//#pragma link "dxDBInsp"
//#pragma link "dxExEdtr"
//#pragma link "dxInspct"
//#pragma link "dxInspRw"
//#pragma resource "*.dfm"
extern UIProject*g_pProject;


UI m_FCMsNodeUI;
UI m_LineUI;
Graphics::TBitmap *pBitmap;
long gbl_view=0;//
TStringList*     m_VariableStringList;//
Boolean fscanfs(FILE*f,char*c,AnsiString& course,AnsiString& effect,AnsiString& oper)
{
   if(fgets(c,MAXLINELENGTH,f)==NULL)
    return false;
   int k=strlen(c);
   AnsiString str=c;
   AnsiString tmp="@";
   int t=str.Pos(tmp);
   course = str.SubString(1,t-1);
   course=course.TrimLeft();
   course=course.TrimRight();

   str=str.SubString(t+1,str.Length()-t);

   t=str.Pos(tmp);
   oper = str.SubString(1,t-1);
   oper=oper.TrimLeft();
   oper=oper.TrimRight();

   effect=str.SubString(t+1,str.Length()-t);
   effect=effect.TrimLeft();
   effect=effect.TrimRight();
   return true;
}
Boolean CheckType(const Variant& v, Word type)
{
  if (v.VType == type)
    return true;
  else
    return false;
}

long StrInStringNum(AnsiString& str,AnsiString& strs)
{
      AnsiString strtmp=strs;
      int a=strtmp.Pos(str);
      int count=0;
      while(a>0)
      {
        count++;
        strtmp=strtmp.SubString(a+1,strtmp.Length()-a);
        a=strtmp.Pos(str);
      }
      return count;
}
AnsiString TrimString(AnsiString str,int size)
{
      WideString str_wide= WideString(str);
       if(str_wide.Length()>size)
       {
          str_wide = str_wide.SubString(1,size);
          str_wide+="...";
       }
       str = AnsiString(str_wide);//
       return str;
}
int IsConnected(NodeEvent*source,NodeEvent*dest) //判断两个节点是否是相邻的
{
   if(source==NULL||dest==NULL)
      return -1;
  TList* list1 ;
  TList* list2 ;
  void*obj1;
  void*obj2;
  long time=0;

  list1 = source->m_pConnectedList;
  list2 = dest->m_pConnectedList;
  if(list1 != NULL&& list2 != NULL)
  {
  for(int i=0;i< list1->Count; i++)
  {
     obj1 = list1->Items[i];
     for(int j=0;j< list2->Count; j++)
     {
        obj2 = list2->Items[j];
        if(obj1 == obj2)
          time++;
     }
  }
  }
  return time;
}

//***********By WYP at 20140316*****************************************
int IsCovered(NodeEvent*n1,NodeEvent*n2)//判断两个节点是否是覆盖的关系
{
   if(n1==NULL||n2==NULL)
      return -1;
   long cover_sum=0;
   int R=10000;
   if(((n1->X-n2->X)*(n1->X-n2->X)+(n1->Y-n2->Y)*(n1->Y-n2->Y))<R)
   {
      cover_sum++;
   }
  return cover_sum;
}
//***********************************************************************

int IsObjInList(BasicGraph*obj,TList*list)
{
   if(obj==NULL||list==NULL||list->Count==0)
      return -1;
  for(int i=0;i< list->Count ; i++)
  {
     BasicGraph*obj1 = (BasicGraph*)list->Items[i];
     if(obj1 == obj)
        return i;
  }
  return -1;
}
Boolean IsNameInList(AnsiString strName,BasicGraph*obj,TList*list)
{
   if(obj==NULL||list==NULL||list->Count==0)
      return false;
  for(int i=0;i< list->Count ; i++)
  {
     BasicGraph*obj1 = (BasicGraph*)list->Items[i];
     if(obj1 == obj)
        continue;
     if(obj1->m_strName==strName)
        return true;
  }
  return false;
}

///////////////////////////////////////////////////////
BasicGraph::BasicGraph()
{
proportion=1;
XOrientation=0;
YOrientation=0;
m_bWorking=false;
}

__fastcall BasicGraph::~BasicGraph()
{
}
Boolean BasicGraph::SetOrientation(long x0,long y0)
{
  XOrientation = x0;
  YOrientation = y0;
  return true;
}

/////////////////////////////////
///////////////////////////////////
NodeEvent::NodeEvent()
{
  m_pConnectedList=new TList;
  m_pCoveredList=new TList;
  //************By WYP at 20140402*************
  m_pRouteList=new TList;
  //*******************************************
  //************By WYP at 20140504*************
  m_pTriggeredList=new TList;
  //*******************************************
  //************By WYP at 20140507*************
  m_psimTimeList=new TList;
  //*******************************************
  //************By WYP at 20140513*************
  m_pGetMessageList=new TList;
  //*******************************************
  //************By WYP at 20140522*************
  m_pBrief_RouteList=new TList;
  //*******************************************
  //************By WYP at 20150424*************
  m_pShorestRoute=new TList;
  m_pRandRoute=new TList;
  m_pBrief_RandRoute=new TList;
  //*******************************************
  m_pSTE=new TList;
  m_bError=false;
 }
void NodeEvent::ClearListData()
{
   m_pConnectedList->Clear();
   m_pCoveredList->Clear();
   //************By WYP at 20140402*************
   m_pRouteList->Clear();
   //*******************************************

   //************By WYP at 20140504*************
   m_pTriggeredList->Clear();
   //*******************************************

   //************By WYP at 20140507*************
   m_psimTimeList->Clear();
   //*******************************************

   //************By WYP at 20140513*************
   m_pGetMessageList->Clear();
   //*******************************************
   //************By WYP at 20140522*************
   m_pBrief_RouteList->Clear();
   //*******************************************
   m_pShorestRoute->Clear();
   m_pRandRoute->Clear();
   m_pBrief_RandRoute->Clear();
   m_pSTE->Clear();
}
__fastcall NodeEvent::~NodeEvent()
{
  ClearListData();
  delete m_pConnectedList;
  delete m_pCoveredList;
  //************By WYP at 20140402*************
  delete m_pRouteList;
  //*******************************************
  //************By WYP at 20140504*************
  delete m_pTriggeredList;
  //*******************************************
  //************By WYP at 20140507*************
  delete m_psimTimeList;
  //*******************************************
  //************By WYP at 20140513*************
  delete m_pGetMessageList;
  //*******************************************
  //************By WYP at 20140522*************
  delete m_pBrief_RouteList;
  //*******************************************
  //************By WYP at 20150424*************
  delete m_pShorestRoute;
  //*******************************************
}
void NodeEvent::SetMouseDPosition(int m_x,int m_y)
{
        d0_x = m_x;
        d0_y = m_y;
}
void NodeEvent::SetMouseMPosition(int m_x,int m_y)
{
        d1_x = m_x;
        d1_y = m_y;
}
void NodeEvent::MoveRelatedMouse(int m_x,int m_y)
{
        SetMouseMPosition(m_x,m_y);
        X = X+d1_x-d0_x;
        Y = Y+d1_y-d0_y;
}

void NodeEvent::GetParentNodes (TList*list)   //得到前一个节点
{
     if(list==NULL)return;
     for(int i=0;i<m_pConnectedList->Count;i++)
     {
        LineEvent*lobj=(LineEvent*)m_pConnectedList->Items[i];
        NodeEvent*obj=lobj->ObjectSource;
        list->Add(obj);
     }
}

void NodeEvent::GetChildrenNodes(TList*list)   //得到后一个节点
{
     if(list==NULL)return;
     for(int i=0;i<m_pConnectedList->Count;i++)
     {
        LineEvent*lobj=(LineEvent*)m_pConnectedList->Items[i];
        NodeEvent*obj=lobj->ObjectDest;
        list->Add(obj);
     }
     return;
}

//ObjectSource是前一个节点；ObjectDest是后一个节点
void NodeEvent::GetConnectedNodes(TList*list) //得到相邻节点
{
     if(list==NULL)return;
     for(int i=0;i<m_pConnectedList->Count;i++)
     {
        LineEvent*lobj=(LineEvent*)m_pConnectedList->Items[i];
        NodeEvent*obj1=lobj->ObjectDest;
        if( obj1!=this)
        {
            list->Add(obj1);
            continue;
        }
        else
        {
            NodeEvent*obj2=lobj->ObjectSource;
            list->Add(obj2);
        }
     }
     return;
}

/*//Solution1:取出每个节点的相邻连线，得到线条另一端的节点，判断是否覆盖
//********By WYP at 20140312***20140321***************************************
void NodeEvent::GetCoveredNodes()//得到某个节点可以覆盖的节点范围列表
{
    int R=100000000000;
   // FCMsNode*obj=new FCMsNode;
    for(int i=0;i<m_pConnectedList->Count;i++)
    {
       //obj = (FCMsNode*)m_pFCMsNodeList->Items[i];
       LineEvent*lobj=(LineEvent*)m_pConnectedList->Items[i]; //依次取出每一条连线
       NodeEvent*obj1=lobj->ObjectDest;                       //取出连线上的两个端点
       NodeEvent*obj2=lobj->ObjectSource;
       if((this!=obj1)&&((this->X-obj1->X)*(this->X-obj1->X)+(this->Y-obj1->Y)*(this->Y-obj1->Y))<R)
       {
                this->m_pCoveredList->Add(obj1);
       }
      // if((this!=obj2)&&((this->X-obj2->X)*(this->X-obj2->X)+(this->Y-obj2->Y)*(this->Y-obj2->Y))<R)
      // {
      //          this->m_pCoveredList->Add(obj2);
      // }
    }
}
//*********************************************************************
*/
 /*Solution2:取出环境中的每条连线，取出每条连线的左端点，判断是否覆盖
//********By WYP at 20140331*****************************************************
void NodeEvent::GetCoveredNodes()//得到某个节点可以覆盖的节点范围列表
{
    int R=100000000000;
   // FCMsNode*obj=new FCMsNode;
    for(int i=0;i<g_pProject->m_pLineEventList->Count;i++)
    {
       //obj = (FCMsNode*)m_pFCMsNodeList->Items[i];
       LineEvent*lobj=(LineEvent*)g_pProject->m_pLineEventList->Items[i]; //依次取出每一条连线
       NodeEvent*obj1=lobj->ObjectDest;                       //取出连线上的两个端点
       NodeEvent*obj2=lobj->ObjectSource;
       if((this!=obj1)&&((this->X-obj1->X)*(this->X-obj1->X)+(this->Y-obj1->Y)*(this->Y-obj1->Y))<R)
       {
                this->m_pCoveredList->Add(obj1);
       }
      // if((this!=obj2)&&((this->X-obj2->X)*(this->X-obj2->X)+(this->Y-obj2->Y)*(this->Y-obj2->Y))<R)
      // {
      //          this->m_pCoveredList->Add(obj2);
      // }
    }
}
//*********************************************************************
*/

//Solution3:取出环境中的每个节点，判断是否覆盖
//********By WYP at 20140331****************************************************
void NodeEvent::GetCoveredNodes()//得到某个节点可以覆盖的节点范围列表
{
    int R=100000;
    for(int i=0;i<g_pProject->m_pFCMsNodeList->Count;i++)
    {
       FCMsNode*obj1=(FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i]; //依次取出每个节点
       if((this!=obj1)&&((this->X-obj1->X)*(this->X-obj1->X)+(this->Y-obj1->Y)*(this->Y-obj1->Y))<R)
       {
                this->m_pCoveredList->Add(obj1);
       }
    }
}
//********************************************************************************

//*************By WYP at 20140409*************************************************
Boolean NodeEvent::IsInList(TList*list)//判断当前节点是否在列表list中
{
        for(int i=0;i<list->Count;i++)
        {
            FCMsNode*obj=(FCMsNode*)list->Items[i];
            if(this==obj)
                return true;
        }
        return false;
}
//********************************************************************************

//*************By WYP at 20140504***20140521**********************************************
void NodeEvent::InitialTriggeredList()  //得到某个节点覆盖列表中所有节点的触发列表
{
         this->GetCoveredNodes();    //得到覆盖范围列表
         for(int j=0;j<this->m_pCoveredList->Count;j++)
         {
                this->m_pTriggeredList->Add("False");
                //FCMsNode*obj=(FCMsNode*)this->m_pCoveredList->Items[j]; //依次提取出覆盖范围列表中的每个节点，求其覆盖范围
                //obj->GetCoveredNodes();  //计算被提取出的节点的覆盖列表
                //for(int k=0;k<obj->m_pCoveredList->Count;k++)
                //{
                //        //FCMsNode*obj1=(FCMsNode*)obj->m_pCoveredList->Items[k];
                //        if(obj->m_pTriggeredList->Count!=obj->m_pCoveredList->Count)
                //        {
                //                obj->m_pTriggeredList->Add("False");    //将覆盖列表中每个节点的被触发情况初始化设置为False
                //        }
                //}
                //obj->m_pCoveredList->Clear();
         }
         this->m_pCoveredList->Clear();
}
//********************************************************************************

//*************By WYP at 20140505***20140521**********************************************
void NodeEvent::InitialsimTimeList()
{
         this->GetCoveredNodes();    //得到覆盖范围列表
         for(int j=0;j<this->m_pCoveredList->Count;j++)
         {
                this->m_psimTimeList->Add("0");
                //FCMsNode*obj=(FCMsNode*)this->m_pCoveredList->Items[j]; //依次提取出覆盖范围列表中的每个节点，求其覆盖范围
                //obj->GetCoveredNodes();  //计算被提取出的节点的覆盖列表
                //for(int k=0;k<obj->m_pCoveredList->Count;k++)
                //{
                //        //FCMsNode*obj1=(FCMsNode*)obj->m_pCoveredList->Items[k];
                //        if(obj->m_psimTimeList->Count!=obj->m_pCoveredList->Count)
                //        {
                //                obj->m_psimTimeList->Add("0");    //将覆盖列表中每个节点的被触发节拍设置为0
                //        }
                //}
                //obj->m_pCoveredList->Clear();
         }
         this->m_pCoveredList->Clear();

}
//********************************************************************************

//*************By WYP at 20140513*************************************************
void NodeEvent::InitialGetMessageList() //初始化信息接收列表
{
         for(int i=0;i<g_pProject->m_pFCMsNodeList->Count;i++)
         {
                this->m_pGetMessageList->Add("False");
         }
}
//********************************************************************************

//*************By WYP at 20140522***20140523**********************************************
int NodeEvent::GetLastIndex(TList*list)
{
        int Last_index;
        for(int i=0;i<list->Count;i++)
        {
            FCMsNode*obj=(FCMsNode*)list->Items[i];
            if(this==obj)
                Last_index=i;
        }
        return Last_index;
}
//********************************************************************************

//*************By WYP at 20140522***20140523**********************************************
void NodeEvent::GetBriefRouteList()//得到某节点的最简路由表
{
        //this->m_pBrief_RouteList->Add(this);
        int lastindex=this->GetLastIndex(this->m_pRouteList);
        while(lastindex<this->m_pRouteList->Count)
        {
             FCMsNode*obj=(FCMsNode*)this->m_pRouteList->Items[lastindex];
             lastindex=obj->GetLastIndex(this->m_pRouteList);
             FCMsNode*obj1=(FCMsNode*)this->m_pRouteList->Items[lastindex];
             this->m_pBrief_RouteList->Add(obj1);
             lastindex=lastindex+1;
        }
}
//*****************************************************************************

//*************By WYP**********************************************
void NodeEvent::GetBriefRandRoute()//得到某节点的最简随机路径
{
        int lastindex=this->GetLastIndex(this->m_pRandRoute);
        while(lastindex<this->m_pRandRoute->Count)
        {
             FCMsNode*obj=(FCMsNode*)this->m_pRandRoute->Items[lastindex];
             lastindex=obj->GetLastIndex(this->m_pRandRoute);
             FCMsNode*obj1=(FCMsNode*)this->m_pRandRoute->Items[lastindex];
             this->m_pBrief_RandRoute->Add(obj1);
             lastindex=lastindex+1;
        }
}
//********************************************************************************

//**************By WYP************************************************
int NodeEvent::MinDisNode_Index(TList*list) //得到距离当前节点最近的节点的序号
{
         long Min_distance;
         long current_distance;
         int Min_Index=0;
         FCMsNode*obj=(FCMsNode*)list->Items[0];
         if(this!=obj)
         {
                 Min_distance=(this->X-obj->X)*(this->X-obj->X)+(this->Y-obj->Y)*(this->Y-obj->Y);
         }
         else
         {
                 obj=(FCMsNode*)list->Items[list->Count-1];
                 Min_distance=(this->X-obj->X)*(this->X-obj->X)+(this->Y-obj->Y)*(this->Y-obj->Y);
         }

         for(int i=0;i<list->Count;i++)
         {
                  FCMsNode*obj1=(FCMsNode*)list->Items[i];
                  if(this!=obj1)
                  {
                        current_distance=(this->X-obj1->X)*(this->X-obj1->X)+(this->Y-obj1->Y)*(this->Y-obj1->Y);
                        if(current_distance<Min_distance)
                        {
                              Min_distance=current_distance;
                              Min_Index=i;
                        }
                  }
         }
         return Min_Index;
}
//****************************************************************************************

/*
//**************By WYP*********************************************
void NodeEvent::GetShorestRoute(NodeEvent*node)  //得到当前节点到node的最短路径
{
        long Min_route_length;//当前路径中的最大长度
        long current_length=0;
        int Min_Index=this->MinDisNode_Index(this->m_pConnectedList);
        FCMsNode*obj=(FCMsNode*)this->m_pConnectedList->Items[Min_Index];//取出与起点最近的那个节点
        Min_route_length=(this->X-obj->X)*(this->X-obj->X)+(this->Y-obj->Y)*(this->Y-obj->Y);
        this->m_pShorestRoute->Add(obj);
        while(this->m_pShorestRoute->Items[this->m_pShorestRoute->Count-1]!=node)
        {
                FCMsNode*current_obj=(FCMsNode*)this->m_pShorestRoute->Items[this->m_pShorestRoute->Count-1];//找到最短路径当前所到节点
                current_obj->MinDisNode_Index(current_obj->m_pConnectedList);
                FCMsNode*next_obj=(FCMsNode*)current_obj->m_pConnectedList->Items[Min_Index];

        }
        for(int i=1;i<this->m_pConnectedList->Count;i++)
        {
             FCMsNode*obj=(FCMsNode*)this->m_pConnectedList->Items[i];
             current_length=(this->X-obj->X)*(this->X-obj->X)+(this->Y-obj->Y)*(this->Y-obj->Y);
        }

}
//********************************************************************************
*/

//**************By WYP at 20150606********************************************************
void NodeEvent::GetRandRoute(NodeEvent*node)
{
        TList* CurrentList=new TList;
        this->GetConnectedNodes(CurrentList);
        int Min_Index=this->MinDisNode_Index(CurrentList);
        this->m_pRandRoute->Add(this);
        FCMsNode*obj=(FCMsNode*)CurrentList->Items[Min_Index];//取出与起点最近的那个节点
        this->m_pRandRoute->Add(obj);
        CurrentList->Clear();

        String s = obj->m_strName;
        s = s.SubString(2,s.Length()-1);

        while(this->m_pRandRoute->Items[this->m_pRandRoute->Count-1]!=node)
        {
                FCMsNode*current_obj=(FCMsNode*)this->m_pRandRoute->Items[this->m_pRandRoute->Count-1];//找到最短路径当前所到节点
                current_obj->GetConnectedNodes(CurrentList);
                int index=random(CurrentList->Count); //从当前节点的相邻列表中随机选择一个节点作为下一到达点
                FCMsNode*next_obj=(FCMsNode*)CurrentList->Items[index];
                this->m_pRandRoute->Add(next_obj);
                CurrentList->Clear();

                //String s1 = current_obj->m_strName;
                //s1 = s1.SubString(2,s1.Length()-1);
                /*for(int i=0;i<g_pProject->m_pFCMsNodeList->Count;i++)
                {
                      FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                      String s2 = myobj->m_strName;
                      s2 = s2.SubString(2,s2.Length()-1);
                      if(StrToInt(s1)==StrToInt(s2))
                      {
                             int index=random(myobj->m_pConnectedList->Count); //从当前节点的相邻列表中随机选择一个节点作为下一到达点
                             FCMsNode*next_obj=(FCMsNode*)myobj->m_pConnectedList->Items[index];
                             this->m_pRandRoute->Add(next_obj);
                             break;
                      }
                }*/

        }
        this->GetBriefRandRoute();
}
//****************************************************************************************

//**************By WYP********************************************************
void NodeEvent::GetSTE(TList*list)//简化轨迹函数STE
{
         int i=0;
         while(i<list->Count)
         {
               FCMsNode*obj=(FCMsNode*)list->Items[i];
               if(obj->m_iType==1)
               {
                      this->m_pSTE->Add(obj);
                      FCMsNode*nextobj=(FCMsNode*)list->Items[++i];
                      while(nextobj->m_iType==1)
                      {
                            i++;
                            nextobj=(FCMsNode*)list->Items[i];
                      }
               }
               else
               {
                     this->m_pSTE->Add(obj);
                     i++;
               }
         }
}
//****************************************************************************************
Boolean NodeEvent::CheckValid ()
{
 return true;
}
Boolean NodeEvent::DropLineEvent (long id)
{    
     for(int i=0;i<m_pConnectedList->Count;i++)
     {
        LineEvent*lobj=(LineEvent*)m_pConnectedList->Items[i];
        if(lobj->ID==id)
        {
           m_pConnectedList->Delete(i);
           return true;
        }
     }
     return false;
}

////////////////////////////////////
NodeRecord::NodeRecord()
{
    count = 7;
}
__fastcall NodeRecord::~NodeRecord()
{


}
////Calculate//////////
FCMsNode::FCMsNode()
{
      m_dqHistoryData=new HISTORYDATA;
      m_fEffectDis=1;
      m_iType=1;
      m_iPosition=1;
}
__fastcall FCMsNode::~FCMsNode()    //类FCMsNode的析构函数
{
   m_dqHistoryData->clear();
   delete m_dqHistoryData;
}
void FCMsNode::Simulate()
{

}

Boolean FCMsNode::IsSelect (TRect rect)    //判断面板是否被选中
{
   long x=X;
   long y=Y;
   if(x>rect.left&&x<rect.right&&y>rect.top&&y<rect.Bottom)
   {
        m_bSelected=true;
        return true;
   }
   m_bSelected=false;
   return false;
}
Boolean FCMsNode::SelectTest(POINT p)
{
  if(abs(X-p.x)<=gbl_ItemSize&&abs(Y-p.y)<=gbl_ItemSize)
     return true;
  else
     return false;
}
Boolean FCMsNode::IsSelect (POINT p) //判断节点是否被选中
{
  if(abs(X-p.x)<=gbl_ItemSize&&abs(Y-p.y)<=gbl_ItemSize)
  {
     m_bSelected=true;
     return true;
  }
  else
     m_bSelected=false;
     return false;
}
void FCMsNode::Draw (TCanvas* m_canvas)
{
/*

   XY

*/
  TRect rect;

  rect.Left = (X- gbl_ItemSize- XOrientation)*proportion;
  rect.Top = (Y-gbl_ItemSize- YOrientation)*proportion;
  rect.right =(X+gbl_ItemSize- XOrientation)*proportion;
  rect.Bottom = (Y+gbl_ItemSize- YOrientation)*proportion;

  TColor cl= m_canvas->Brush->Color;
  TColor c2= m_canvas->Pen->Color;
  int ls=m_canvas->Pen->Width;

  TBrushStyle bs= m_canvas->Brush->Style;
  if(m_bError)
    m_canvas->Brush->Style = bsHorizontal;
  if(m_iType==2)
    m_canvas->Brush->Style = bsClear;
  else if(m_iType==3)
    m_canvas->Brush->Style = bsCross;
  else
    m_canvas->Brush->Style = bsSolid;

  m_canvas->Pen->Color = m_FCMsNodeUI.m_tcLinePenColor;
  m_canvas->Pen->Width =m_FCMsNodeUI.m_iLinePenWidth;
  if(m_iType!=2)
        m_canvas->Brush->Color = m_FCMsNodeUI.m_tcBrushColor;
  else
        m_canvas->Brush->Color = clWhite;
  m_canvas->Ellipse(rect);
  m_canvas->Brush->Color = cl;
  m_canvas->Pen->Color = c2;
  m_canvas->Pen->Width=ls;
  TPoint points[4];
  points[0].x = (X- XOrientation)*proportion;
  points[0].y = (Y-gbl_ItemSize- YOrientation)*proportion;
  points[1].x = (X+gbl_ItemSize- XOrientation)*proportion;
  points[1].y = (Y- YOrientation)*proportion;
  points[2].x = (X- XOrientation)*proportion;
  points[2].y = (Y+gbl_ItemSize- YOrientation)*proportion;
  points[3].x = (X-gbl_ItemSize- XOrientation)*proportion;
  points[3].y = (Y- YOrientation)*proportion;
  if(m_bWorking)
     m_canvas->Draw(points[0].x,points[0].y-16,pBitmap);
  if (m_bSelected)
  {
     TColor cl= m_canvas->Brush->Color;

     m_canvas->Brush->Color = clBlack;
     m_canvas->Brush->Style = bsSolid;
     m_canvas->FillRect(TRect(points[0].x-2,points[0].y-2,points[0].x+2,points[0].y+2));
     m_canvas->FillRect(TRect(points[1].x-2,points[1].y-2,points[1].x+2,points[1].y+2));
     m_canvas->FillRect(TRect(points[2].x-2,points[2].y-2,points[2].x+2,points[2].y+2));
     m_canvas->FillRect(TRect(points[3].x-2,points[3].y-2,points[3].x+2,points[3].y+2));
     m_canvas->Brush->Color = cl;
  }

  AnsiString idname;
  idname = m_strName;//
  idname=TrimString(idname,80);

  TColor cl1 = m_canvas->Font->Color;
  m_canvas->Font->Color = m_FCMsNodeUI.m_tcFontColor ;
  int fsize=m_canvas->Font->Size;
  m_canvas->Brush->Style = bs;
  if(m_canvas->CopyMode !=  cmSrcInvert)
  {  m_canvas->Font->Size = m_FCMsNodeUI.m_iFontSize;
     TBrushStyle bs= m_canvas->Brush->Style;
     m_canvas->Brush->Style = bsClear;

     long texth= m_canvas->TextHeight(idname);
     long count= StrInStringNum('/',idname)+1;
     long left=(count*texth)/2;

       int a=idname.Pos('/');
       int i=0;
       while(a>0)
       {
         AnsiString strtemp=idname.SubString(1,a-1);
         idname=idname.SubString(a+1,idname.Length()-a);
         m_canvas->TextOutA((X- XOrientation)*proportion - m_canvas->TextWidth(strtemp)/2
          ,(Y- YOrientation)*proportion-left+i*texth,strtemp);
         a=idname.Pos('/');
         i++;
       }
     m_canvas->TextOutA((X- XOrientation)*proportion - m_canvas->TextWidth(idname)/2
        ,(Y- YOrientation)*proportion-left+i*texth,idname);
     m_canvas->Brush->Style = bs;
  }
  m_canvas->Font->Size=fsize;
  m_canvas->Font->Color = cl1;
}
POINT FCMsNode::GetPoint(int x,int y) //得到坐标为x,y的点
{
    TPoint points; points.x=-1;points.y=-1;
    if(((x-X)*(x-X)+(y-Y)*(y-Y))>gbl_ItemSize)
    {
        points.x=X+(x-X)*gbl_ItemSize/sqrt((x-X)*(x-X)+(y-Y)*(y-Y));
        points.y=Y+(y-Y)*gbl_ItemSize/sqrt((x-X)*(x-X)+(y-Y)*(y-Y));
    }


    return points ;
}
Boolean FCMsNode::CheckValid ()
{
   m_bError=false;

   if(m_strName.Length()==0||this->m_pConnectedList->Count==0)
   {
     m_bError=true;
     return m_bError;
   }
   return m_bError;
}
Boolean FCMsNode::Calculate ()
{

}

void FCMsNode::StoreOldData(short data)
{
   if(m_dqHistoryData->size()==HISTCONTENT)
      m_dqHistoryData->erase(m_dqHistoryData->begin());
   m_dqHistoryData->insert(m_dqHistoryData->end(),data);
}
void FCMsNode::CopyTo(FCMsNode*value)
{
}
/////////////////////////////
void WalkingUser::Walk(FCMsNode*pLast,FCMsNode*pNext)
{

}
void WalkingUser::InitialSpeed()
{

}
__fastcall WalkingUser::~WalkingUser()
{
  for(int i=0;i<m_pPathList->Count;i++)
  {
        HISNODE*n1=(HISNODE*)m_pPathList->Items[i];
        delete n1;
  }
  m_pPathList->Clear();
  delete m_pPathList;
}

