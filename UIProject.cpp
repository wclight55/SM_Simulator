
#include "UIProject.h"
#include "MainFrame.h"
#include <Dialogs.hpp>
#include <math.h>

//DBEngine *dbEngine = NULL;
UIProject::UIProject()
{
        m_pSelectedList=new TList;
        m_pCopiedNodeList=new TList;
        m_pCopybufferList=new TList;
        m_pUserHistory=new TList;
        m_bModified=false;
        m_nMaxRuleSetID=0;
       	m_nMaxLineID=0;
        proportion=1;
         m_cBackGround=clWhite;
        m_MaxPoint.x = 0;
        m_MaxPoint.y = 0;

        m_FCMsNodeUI.m_tcLinePenColor=clBlack;  //连线颜色为黑色
        m_FCMsNodeUI.m_iLinePenWidth=1;
        m_FCMsNodeUI.m_tcBrushColor=clYellow;   //节点颜色为黄色
        m_FCMsNodeUI.m_tcFontColor=clBlack;     //字体颜色为黑色
        m_FCMsNodeUI.m_iFontSize=8;

        m_LineUI.m_tcLinePenColor=clOlive;
        m_LineUI.m_iLinePenWidth=1;
        m_LineUI.m_tcBrushColor=clBlack;
        m_LineUI.m_tcFontColor=clBlack;
        m_LineUI.m_iFontSize=8;

    m_dSimulateTime=0;
    m_dLambda=0.05;
    m_dUnitDistance=0.05;
    m_dSamplingTime=0.1;
    m_dWalkingSpeed=1;
    m_nIteratTime=1000;
    m_fAllVariance=0.1;
    m_iSwitch=true;
    stay = 0;
    estay = 1;
    flag = true;
    count = 0;
    ls = new FCMsNode;

}

__fastcall UIProject::~UIProject() //类UIProject的析构函数
{
        m_pSelectedList->Clear();
	delete m_pSelectedList;
        m_pCopiedNodeList->Clear();
	delete m_pCopiedNodeList;
        m_pCopybufferList->Clear();
	delete m_pCopybufferList;
        for(int i = 0;i<m_pUserHistory->Count;i++)
        {
          WalkingUser*pUser = (WalkingUser*)m_pUserHistory->Items[i];
          delete pUser;
        }

        m_pUserHistory->Clear();
        delete m_pUserHistory;
}


void UIProject::SetSelectedMouseD(POINT p)
{
       if(m_pSelectedList->Count==1)
       {
          BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[0];
          if(AnsiString(myobj->ClassName())=="LineEvent")
          {
             LineEvent*lk=(LineEvent*)myobj;
             lk->SetMouseDPosition(p.x,p.y,true);//
             return;
          }
          else
          {
             NodeEvent*node=(NodeEvent*)myobj;
             node->IsSelect(p);
          }
       }
       for(int i = 0;i<m_pSelectedList->Count;i++)
       {
          BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[i];
          if(AnsiString(myobj->ClassName())!="LineEvent")
          {
             NodeEvent*obj=(NodeEvent*)myobj;
             obj->SetMouseDPosition(p.x,p.y);//
          }
          else
          {
             LineEvent*lk=(LineEvent*)myobj;
             lk->SetMouseDPosition(p.x,p.y,false);//
          }

       }
}
void UIProject::ObjectSelected (FCMsNode*rulenode,NodeEvent*myobj)
{
   UnSelectAll();
   if(myobj==NULL)//选中某RuleSet
   {
        if(rulenode!=NULL)
        {
          rulenode->Select();
          m_pSelectedList->Add(rulenode);
        }
        return;
   }
   else//选中某RuleSet下的NodeEvent
   {
        if(rulenode!=NULL)
        {
            m_pSelectedList->Add(myobj);
        }
        return;
   }
}
BasicGraph*UIProject::IsSelect (POINT p,TShiftState Shift)
{
        if(!Shift.Contains(ssShift))
           UnSelectAll();
           for(int i = 0;i<m_pSelectedList->Count;i++)
           {
              BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[i];
              if(AnsiString(myobj->ClassName())!="LineEvent")
              {
                 NodeEvent*obj=(NodeEvent*)myobj;
                 obj->SetMouseDPosition(p.x,p.y);//
              }
           }
           for(int i = 0;i<m_pFCMsNodeList->Count;i++)
           {
              FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];

              if(!myobj->m_bSelected&&myobj->IsSelect(p))
              {
                 myobj->SetMouseDPosition(p.x,p.y);//
                 m_pSelectedList->Add(myobj);
                 return myobj;
              }
           }
           for(int i = 0;i<m_pLineEventList->Count;i++)
           {
              LineEvent*myobj = (LineEvent*)m_pLineEventList->Items[i];
              if(!myobj->m_bSelected&&myobj->IsSelect(p))
              {
                 m_pSelectedList->Add(myobj);
                 return myobj;
              }
           }
        return NULL;
}
BasicGraph*UIProject::SelectTest (POINT p)
{
           for(int i = 0;i<m_pFCMsNodeList->Count;i++)
           {
              FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
              if(myobj->SelectTest(p))
              {
                 return myobj;
              }
           }
           for(int i = 0;i<m_pLineEventList->Count;i++)
           {
              LineEvent*myobj = (LineEvent*)m_pLineEventList->Items[i];
              if(myobj->SelectTest(p))
              {
                 return myobj;
              }
           }
        return NULL;
}
Boolean UIProject::IsSelect (TRect rect)   //将被选中的节点和连线加入到链表中
{
        if(rect.Width()<4||rect.Height()<4)
             return false;
        UnSelectAll();
           for(int i = 0;i<m_pFCMsNodeList->Count;i++)
           {
              FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
              if(myobj->IsSelect(rect))
                 m_pSelectedList->Add(myobj);
           }
           for(int i = 0;i<m_pLineEventList->Count;i++)
           {
              LineEvent*myobj = (LineEvent*)m_pLineEventList->Items[i];
              if(myobj->IsSelect(rect))
                 m_pSelectedList->Add(myobj);
           }
        return true;
}

void UIProject::SelectAll ()
{
           for(int i = 0;i<m_pFCMsNodeList->Count;i++)
           {
              FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
              myobj->Select();
              m_pSelectedList->Add(myobj);
           }
}
void UIProject::CheckValid()
{
        ClearErrorMessages();
        int marknum=0;
           for(int i = 0;i<m_pFCMsNodeList->Count;i++)
           {
              FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
              if(myobj->CheckValid())
                 AddErrorMessage("sensor error",myobj);
              if(myobj->m_iType!=1)
                 marknum++;
           }
           if(marknum==0)
               AddErrorMessage("error:need marked sensor!",NULL);
        AddErrorMessage("Finish Checking!",NULL);
}
void UIProject::ZoomTo (double p)
{
        proportion=p;
           for(int i = 0;i<m_pFCMsNodeList->Count;i++)
           {
              FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
              myobj->Resize(p);
           }
           for(int i = 0;i<m_pLineEventList->Count;i++)
           {
              LineEvent*myobj = (LineEvent*)m_pLineEventList->Items[i];
              myobj->Resize(p);
           }
}
void UIProject::FitToWindow(long w_h,long w_w)
{
        if(w_h<=0||w_w<=0)return;
        long left=1000;
        long right=0;
        long top=1000;
        long bottom=0;
           for(int i = 0;i<m_pFCMsNodeList->Count;i++)
           {
              FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
              left=left<myobj->X?left:myobj->X;
              right=right>myobj->X?right:myobj->X;
              top=top<myobj->Y?top:myobj->Y;
              bottom=bottom>myobj->Y?bottom:myobj->Y;
           }
           double p1=(w_h)/double(bottom-top+2*gbl_ItemSize);
           double p2=(w_w)/double(right-left+2*gbl_ItemSize);
           proportion=p1<p2?p1:p2;
           XOrientation=(left-gbl_ItemSize);
           YOrientation=(top-gbl_ItemSize);
           for(int i = 0;i<m_pFCMsNodeList->Count;i++)
           {
              FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
              myobj->Resize(proportion);
              myobj->SetOrientation(XOrientation,YOrientation);
           }
           for(int i = 0;i<m_pLineEventList->Count;i++)
           {
              LineEvent*myobj = (LineEvent*)m_pLineEventList->Items[i];
              myobj->Resize(proportion);
              myobj->SetOrientation(XOrientation,YOrientation);
           }
}
void UIProject::SetOffset(long x0,long y0)
{
   XOrientation += x0;YOrientation += y0;
       for(int i = 0;i<m_pFCMsNodeList->Count;i++)
       {
          FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
          myobj->SetOrientation(XOrientation,YOrientation);
       }
       for(int i = 0;i<m_pLineEventList->Count;i++)
       {
          LineEvent*myobj = (LineEvent*)m_pLineEventList->Items[i];
          myobj->SetOrientation(XOrientation,YOrientation);
       }
}
void UIProject::SetOffsetTo(long x0,long y0)
{
   XOrientation = x0;YOrientation = y0;
       for(int i = 0;i<m_pFCMsNodeList->Count;i++)
       {
          FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
          myobj->SetOrientation(XOrientation,YOrientation);
       }
       for(int i = 0;i<m_pLineEventList->Count;i++)
       {
          LineEvent*myobj = (LineEvent*)m_pLineEventList->Items[i];
          myobj->SetOrientation(XOrientation,YOrientation);
       }
}
void UIProject::ZoomOut ()
{
   proportion=proportion*0.8;
   ZoomTo(proportion);
}

void UIProject::ZoomIn ()
{
   proportion=proportion*1.25;
   ZoomTo(proportion);
}

void UIProject::UnSelectAll ()  //取消所有选中的项目
{
      if(m_pSelectedList!=NULL)
      {
           for(int i = 0;i<m_pSelectedList->Count;i++)
           {
              BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[i];
              myobj->Select(false);
           }
           m_pSelectedList->Clear();
      }
}
FCMsNode* UIProject::AddFCMsNode(POINT p)   //添加节点
{
       m_bModified=true;
       m_nMaxRuleSetID++;
       FCMsNode*value=new FCMsNode;
       value->ID=m_nMaxRuleSetID;
       value->m_strName="m"+IntToStr(m_nMaxRuleSetID);
       value->X=p.x;
       value->Y=p.y;
       m_pFCMsNodeList->Add(value);
       UnSelectAll();
       m_pSelectedList->Add(value);
       value->Select();
       return value;
}

void UIProject::ReDrawSelectObj(long x_1,long y_1,TCanvas*m_canvas)
{
   if(m_pSelectedList->Count==0)
     return;
   if(m_pSelectedList->Count==1)
   {

     BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[0];
     if(AnsiString(myobj->ClassName())=="LineEvent")
     {
       m_bModified=true;
       LineEvent*lk=(LineEvent*)myobj;
       lk->SetMouseMPosition(x_1,y_1,true);
       return;
     }
   }
   m_bModified=true;
   for(int i = 0;i<m_pSelectedList->Count;i++)
   {
      BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[i];
      if(AnsiString(myobj->ClassName())=="LineEvent")
      {
          LineEvent*obj=(LineEvent*)myobj;
          obj->MoveRelatedMouse(x_1,y_1);
          obj->SetMouseDPosition(x_1,y_1,true);
      }
      else
      {
          NodeEvent*obj=(NodeEvent*)myobj;
          obj->MoveRelatedMouse(x_1,y_1);
          obj->SetMouseDPosition(x_1,y_1);
          DrawLinkedEvent(m_canvas,obj,pmNotXor);
      }
   }
}
void UIProject::DrawLinkedEvent(TCanvas*m_canvas,NodeEvent*myobj,TPenMode m_mode)
{
    LineEvent* mylink;
    TPenMode md= m_canvas->Pen->Mode;
    for(int i=0;i<myobj->m_pConnectedList->Count;i++)
    {
         mylink = (LineEvent*)myobj->m_pConnectedList->Items[i];
         m_canvas->Pen->Mode = m_mode;
         mylink->SetLinkEventPosition();
    }
    m_canvas->Pen->Mode=md;
}

FCMsNode*UIProject::GetNodeEventByID(long id)    //通过ID号读取节点
{
   for(int i = 0;i<m_pFCMsNodeList->Count;i++)
   {
      FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
      if(myobj->ID==id)
         return myobj;
   }
   return NULL;
}
FCMsNode*UIProject::GetNodeEventByName(AnsiString str)   //通过名称读取节点
{
   for(int i = 0;i<m_pFCMsNodeList->Count;i++)
   {
      FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
      if(myobj->m_strName==str)
         return myobj;
   }
   return NULL;
}
LineEvent*UIProject::GetLineEventByID(long id)    //通过ID号读取连线
{
   for(int i = 0;i<m_pLineEventList->Count;i++)
   {
      LineEvent*myobj = (LineEvent*)m_pLineEventList->Items[i];
      if(myobj->ID==id)
         return myobj;
   }
   return NULL;
}
LineEvent* UIProject::AddLinkEvent(NodeEvent*source,NodeEvent*dest)
{
   if(source==NULL||dest==NULL||source==dest)
      return NULL;
       long t = IsConnected(source,dest);  //将source与dest的相连情况赋给t
       if(t ==0 )
       {
           POINT p1,p2;
           LineEvent* myobj = new LineEvent;
           m_pLineEventList->Add(myobj);

           m_nMaxLineID++;
           myobj->ID = m_nMaxLineID;
           myobj->m_InID = source->ID;
           myobj->m_OutID = dest->ID;
           myobj->ObjectSource = source;
           myobj->ObjectDest = dest;
           myobj->SetLinkEventPosition();
           dest->m_pConnectedList->Add(myobj);
           source->m_pConnectedList->Add(myobj);
           return myobj;
       }
       else
          return NULL ;
}
void UIProject::AddLinkEvent(NodeEvent*source,NodeEvent*dest,LineEvent*myobj)//若两个节点是相邻的关系，则连线,并将连线赋值给myobj。
{
   if(source==NULL||dest==NULL)
      return ;
       long t = IsConnected(source,dest);
       if(t ==0 )
       {
           POINT p1,p2;
           m_pLineEventList->Add(myobj);
           myobj->m_InID = source->ID;
           myobj->m_OutID = dest->ID;
           myobj->ObjectSource = source;
           myobj->ObjectDest = dest;
           dest->m_pConnectedList->Add(myobj);
           source->m_pConnectedList->Add(myobj);
           myobj->SetLinkEventPosition();
       }
}

/*void UIProject::AddLink_coveredEvent(NodeEvent*n1,NodeEvent*n2)//若两个节点是相互覆盖的关系，则认为两个节点之间相互关联
{
    if(n1==NULL||n2==NULL)
      return ;
    long t = IsCovered(n1,n2);
    if(t ==1 )
    {
        POINT p1,p2;
        LineEvent* myobj = new LineEvent;
        m_pLineEventList->Add(myobj);
        myobj->m_InID = n1->ID;
        myobj->m_OutID = n2->ID;
        myobj->ObjectSource = n1;
        myobj->ObjectDest = n2;
        n2->m_pCoveredList->Add(myobj);
        n1->m_pCoveredList->Add(myobj);
        myobj->SetLinkEventPosition();
    }
}*/
int __fastcall CompareNames(void *Item1, void *Item2)  //比较命名是否相同

{
  return CompareText(((RuleBasic*)Item1)->m_strName,((RuleBasic*)Item2)->m_strName);

}
Boolean UIProject::SortSelected()
{
   m_pFCMsNodeList->Sort(CompareNames);
   m_bModified=true;
   return true;
}
Boolean UIProject::DeleSelected()    //删除已被选中的节点
{
       while(m_pSelectedList->Count>0)
       {
          BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[0];
          m_pSelectedList->Delete(0);
          if(AnsiString(myobj->ClassName())=="FCMsNode")
              DeleFCMsNode((FCMsNode*)myobj);
          else if(AnsiString(myobj->ClassName())=="LineEvent")
              DeleLineEvent((LineEvent*)myobj);
       }
   m_bModified=true;
   return true;
}
Boolean UIProject::DeleFCMsNode(FCMsNode*node)    //删除节点
{
   for(int i=0;i<m_pFCMsNodeList->Count;i++)
   {
      FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
      if(myobj==node)
      {
         m_pFCMsNodeList->Delete(i);
         int count=myobj->m_pConnectedList->Count;
         for (int j = 0; j < count; j++)
         {
            LineEvent*lobj = (LineEvent*)myobj->m_pConnectedList->Items[0];  //删除与该节点相关的连线
            int pos;
            if((pos=IsObjInList(lobj,m_pSelectedList))>=0)
               m_pSelectedList->Delete(pos);
            DeleLineEvent(lobj);
         }
         delete myobj;
         myobj=NULL;
         return true;
      }
   }
   return false;
}

Boolean UIProject::DeleLineEvent(LineEvent*node)
{
      for (int i = 0; i < m_pLineEventList->Count; i++)
      {
          LineEvent*myobj = (LineEvent*)m_pLineEventList->Items[i];
          if(myobj== node)
          {
              NodeEvent*snode=myobj->ObjectSource;
              NodeEvent*dnode=myobj->ObjectDest;
              ///
              snode->DropLineEvent(myobj->ID);
              dnode->DropLineEvent(myobj->ID);
              m_pLineEventList->Delete(i);
              delete myobj;
              return true;
          }
      }
   return false;
}

Boolean UIProject::CopySelected()
{
   UnSelectAll();
   {
       for(int i=0;i<m_pCopybufferList->Count;i++)
       {
          BasicGraph*myobj = (BasicGraph*)m_pCopybufferList->Items[i];
          if(AnsiString(myobj->ClassName())=="FCMsNode")
          {
              FCMsNode*nn=CopyFCMsNode((FCMsNode*)myobj);
              nn->Select();
              m_pSelectedList->Add(nn);
          }
       }
       for(int i=0;i<m_pCopybufferList->Count;i++)
       {
          BasicGraph*myobj = (BasicGraph*)m_pCopybufferList->Items[i];
          if(AnsiString(myobj->ClassName())=="LineEvent")
          {
              LineEvent*nn=CopyLineEvent((LineEvent*)myobj,m_pCopiedNodeList);
              if(nn!=NULL)
              {
                nn->Select();
                nn->m_dDistance= ((LineEvent*)myobj)->m_dDistance;
                m_pSelectedList->Add(nn);
                ((LineEvent*)myobj)->CopyTo(nn);
              }
          }
       }
   }
   m_pCopiedNodeList->Clear();
   m_bModified=true;
   return true;
}
Boolean UIProject::PrepareCopy()
{
       m_pCopybufferList->Clear();
       for(int i=0;i<m_pSelectedList->Count;i++)
       {
          BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[i];
          m_pCopybufferList->Add(myobj);
       }
       return true;
}

FCMsNode* UIProject::CopyFCMsNode(FCMsNode*myobj)
{
       m_nMaxRuleSetID++;
       FCMsNode*value=new FCMsNode;
       value->ID=m_nMaxRuleSetID;
       value->OldID=myobj->ID;
       value->X=myobj->X+gbl_ItemSize;
       value->Y=myobj->Y+gbl_ItemSize;
       value->proportion=myobj->proportion;
       value->XOrientation=myobj->XOrientation;
       value->YOrientation=myobj->YOrientation;

       value->m_strName="m"+IntToStr(m_pFCMsNodeList->Count+1);
       value->m_strDiscrip=myobj->m_strDiscrip;
       m_pFCMsNodeList->Add(value);
       myobj->CopyTo(value);
       m_pCopiedNodeList->Add(value);
       return value;
}
LineEvent* UIProject::CopyLineEvent(LineEvent*myobj,TList*list)
{
     NodeEvent*s=NULL;
     NodeEvent*d=NULL;
     for(int i=0;i<m_pCopiedNodeList->Count;i++)
     {
          FCMsNode*obj1 = (FCMsNode*)m_pCopiedNodeList->Items[i];
          if(obj1->OldID==myobj->ObjectSource->ID)
            s= obj1;
          else if(obj1->OldID==myobj->ObjectDest->ID)
            d= obj1;
     }
     if(s==NULL||d==NULL)return NULL;
     return AddLinkEvent(s,d);
}
LineEvent* UIProject::GetLineEventBetweenNodes(NodeEvent*s,NodeEvent*d)  //得到节点s和节点d之间的连线
{
     for(int i=0;i<m_pLineEventList->Count;i++)
     {
          LineEvent*obj1 = (LineEvent*)m_pLineEventList->Items[i];
          if((s==obj1->ObjectSource && d==obj1->ObjectDest)||(d==obj1->ObjectSource && s==obj1->ObjectDest))
            return obj1;
     }
     return NULL;
}
void UIProject::GetNoConnectedNodes(FCMsNode*pNode,TList*list)  //得到与节点pNode不相邻的节点
{
      TList*mcl=new TList;
      pNode->GetConnectedNodes(mcl);  //得到与pNode相邻的节点，赋给列表mcl
      for(int i=0;i<m_pFCMsNodeList->Count;i++)
      {
         FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
         bool bF=false;
         for(int j=0;j<mcl->Count;j++)
         {
             FCMsNode*myobj2 = (FCMsNode*)mcl->Items[j];
             if(myobj==myobj2)
             {
               bF=true;
               break;
             }
         }
         if(!bF&&myobj!=pNode)
           list->Add(myobj);
      }
}
Boolean UIProject::IsSelectFCMsNode()
{
        if( m_pSelectedList->Count==1)
        {
           BasicGraph*obj=(BasicGraph*)m_pSelectedList->Items[0];
           if(AnsiString(obj->ClassName())=="FCMsNode")
               return true;
        }
        return false;
}
Boolean UIProject::IsSelectLineEvent()
{
        if( m_pSelectedList->Count==1)
        {
           BasicGraph*obj=(BasicGraph*)m_pSelectedList->Items[0];
           if(AnsiString(obj->ClassName())=="LineEvent")
               return true;
        }
        return false;
}


POINT UIProject::ScreenToReal(long dx,long dy)
{
   POINT p;
   p.x = ((double)dx) /proportion + XOrientation;
   p.y = ((double)dy) /proportion + YOrientation;

   return p;
}

void UIProject::ToLeft(TCanvas* m_canvas)
{
        if(m_pSelectedList->Count==0)return;
        long left=9999999999;
         for(int i = 0;i<m_pSelectedList->Count;i++)
         {
            BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[i];
            if(AnsiString(myobj->ClassName())!="LineEvent")
            {
                NodeEvent*mynode = (NodeEvent*)myobj;
                left=left<mynode->X?left:mynode->X;
            }
         }
 //       if(m_pActiveRuleset==NULL)
        {
           for(int i = 0;i<m_pSelectedList->Count;i++)
           {
              BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[i];
              if(AnsiString(myobj->ClassName())!="LineEvent")
              {
                ((NodeEvent*)myobj)->X=left;
                DrawLinkedEvent(m_canvas,(NodeEvent*)myobj,pmNotXor);
              }
           }
        }
}
void UIProject::ToRight(TCanvas* m_canvas)
{
        if(m_pSelectedList->Count==0)return;
        long right=-999999999;
         for(int i = 0;i<m_pSelectedList->Count;i++)
         {
            BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[i];
            if(AnsiString(myobj->ClassName())!="LineEvent")
            {
                NodeEvent*mynode = (NodeEvent*)myobj;
                right=right>mynode->X?right:mynode->X;
            }
         }
//        if(m_pActiveRuleset==NULL)
        {
           for(int i = 0;i<m_pSelectedList->Count;i++)
           {
              BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[i];
              if(AnsiString(myobj->ClassName())!="LineEvent")
              {
                ((NodeEvent*)myobj)->X=right;
                DrawLinkedEvent(m_canvas,(NodeEvent*)myobj,pmNotXor);
              }
           }
        }
}
void UIProject::ToTop(TCanvas* m_canvas)
{
        if(m_pSelectedList->Count==0)return;
        long top=99999999999;
         for(int i = 0;i<m_pSelectedList->Count;i++)
         {
            BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[i];
            if(AnsiString(myobj->ClassName())!="LineEvent")
            {
                NodeEvent*mynode = (NodeEvent*)myobj;
                top=top<mynode->Y?top:mynode->Y;
            }
         }
//        if(m_pActiveRuleset==NULL)
        {
           for(int i = 0;i<m_pSelectedList->Count;i++)
           {
              BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[i];
              if(AnsiString(myobj->ClassName())!="LineEvent")
              {
                ((NodeEvent*)myobj)->Y=top;
                DrawLinkedEvent(m_canvas,(NodeEvent*)myobj,pmNotXor);
              }
           }
        }
}
void UIProject::ToBottom(TCanvas* m_canvas)
{
        if(m_pSelectedList->Count==0)return;
        long bottom=-999999999;
         for(int i = 0;i<m_pSelectedList->Count;i++)
         {
            BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[i];
            if(AnsiString(myobj->ClassName())!="LineEvent")
            {
                NodeEvent*mynode = (NodeEvent*)myobj;
                bottom=bottom>mynode->Y?bottom:mynode->Y;
            }
         }
//        if(m_pActiveRuleset==NULL)
        {
           for(int i = 0;i<m_pSelectedList->Count;i++)
           {
              BasicGraph*myobj = (BasicGraph*)m_pSelectedList->Items[i];
              if(AnsiString(myobj->ClassName())!="LineEvent")
              {
                ((NodeEvent*)myobj)->Y=bottom;
                DrawLinkedEvent(m_canvas,(NodeEvent*)myobj,pmNotXor);
              }
           }
        }
}
void UIProject::ClearHistory()
{
     for(int i = 0;i<m_pFCMsNodeList->Count;i++)
     {
      FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
      myobj->m_dqHistoryData->clear();
      if(!myobj->m_dqHistoryData->empty())
         int wat=1;
     }
}
void UIProject::GetAllMarkSensors(TList*pList)
{
     for(int i = 0;i<m_pFCMsNodeList->Count;i++)
     {
      FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
      if(myobj->m_iType!=1)pList->Add(myobj);
     }
}
void UIProject::SaveUserHistory(AnsiString strName)
{
        FILE *ff;
        ff=fopen(strName.c_str(),"w");
        if(ff == NULL)
          return ;
        int validpath=0;
       for(int i = 0;i<m_pUserHistory->Count;i++)
       {
          WalkingUser*pUser = (WalkingUser*)m_pUserHistory->Items[i];
          if(pUser->m_pPathList->Count>=3)validpath++;
          fprintf (ff, "User:%d  begin:%d  end:%d  ",i+1,int(pUser->m_iBegin*m_dSamplingTime),int(pUser->m_iEnd*m_dSamplingTime));
          float pathlength=0;
          for(int j=0;j<pUser->m_pPathList->Count;j++)
          {
                HISNODE*n1=(HISNODE*)pUser->m_pPathList->Items[j];
                FCMsNode*myobj = n1->pNode;
                if(j>0)
                {
                  HISNODE*n2=(HISNODE*)pUser->m_pPathList->Items[j-1];
                  FCMsNode*myobj2 = n2->pNode;

                  LineEvent*pline=GetLineEventBetweenNodes(myobj,myobj2);
                  if(pline!=NULL)
                  {
                     pathlength=pathlength+pline->m_dDistance;
                  }
                }
                fprintf (ff, "%s  ",myobj->m_strName.c_str());
          }
          fprintf (ff,"length:%f  average speed:%f  \n",pathlength,pathlength/((pUser->m_iEnd-pUser->m_iBegin)*m_dSamplingTime));
       }
       fprintf (ff,"valide trajectory:%d        Total trajectory:%d\n",validpath,m_pUserHistory->Count);

       fclose(ff);
}
void UIProject::SaveUserHistory2(AnsiString strName)
{
        FILE *ff;
        ff=fopen(strName.c_str(),"w");
        if(ff == NULL)
          return ;
        int validpath=0;
       for(int i = 0;i<m_pUserHistory->Count;i++)
       {
          if(i==0)fprintf (ff, "                 %d",i+1);
          else fprintf (ff, "           %d",i+1);
       }
       fprintf (ff, "\n");
       for(int i = 0;i<m_pFCMsNodeList->Count;i++)
       {
            FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
            for(int j=0;j<m_nIteratTime;j++)
            {
               bool bTri=false;
               AnsiString row;
               for(int ii = 0;ii<m_pUserHistory->Count;ii++)
               {
                  WalkingUser*pUser = (WalkingUser*)m_pUserHistory->Items[ii];
                  bool uTr=false;
                  for(int jj=0;jj<pUser->m_pPathList->Count;jj++)
                  {
                        HISNODE*n1=(HISNODE*)pUser->m_pPathList->Items[jj];
                        FCMsNode*myobj2 = n1->pNode;
                        if(myobj2==myobj)
                           row=row;
                        if(n1->iTime==j+1&&myobj2==myobj)
                        {
                           bTri=true;
                           uTr=true;
                           row=row+"1           ";
                           break;
                        }
                  }
                  if(!uTr)
                     row=row+"            ";
               }
               if(bTri)
               {
                   row=IntToStr(i+1)+"."+IntToStr(j+2)+"            "+row;
                   fprintf (ff, "%s\n",row);
               }
          }
       }
       fclose(ff);
}

void UIProject::SaveHistory(AnsiString strName)
{
        int frequence=60/m_dSamplingTime;

        FILE *ff;
        FILE *ff1;
        ff=fopen(strName.c_str(),"w");
        ff1=fopen("statistic.txt","w");
        if(ff == NULL)
          return ;
        if(ff1 == NULL)
          return ;
       for(int i = 0;i<m_pFCMsNodeList->Count;i++)
       {
          FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
          myobj->m_iCurrentNum=0;
          fprintf (ff, "%s  ",myobj->m_strName.c_str());
          fprintf (ff1, "%s  ",myobj->m_strName.c_str());
       }
       fprintf (ff,"\n");
       fprintf (ff1,"\n");
       int jjj=0;
       for(int j=0;j<m_nIteratTime;j++)
       {
              jjj++;
              for(int i = 0;i<m_pFCMsNodeList->Count;i++)
              {
                        FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
                        if(myobj->m_dqHistoryData->at(j)>0)
                          myobj->m_iCurrentNum++;
                        if(jjj==frequence)
                        {
                          fprintf (ff1, "%d  ",myobj->m_iCurrentNum);
                          myobj->m_iCurrentNum=0;
                        }
                        AnsiString SS;
                        AnsiString Ki=IntToStr(i+1);
                        for(int jjj=0;jjj<Ki.Length();jjj++)
                           SS=SS+" ";
                        SS="%d  "+SS;
                        fprintf (ff,SS.c_str(),myobj->m_dqHistoryData->at(j));
              }
              fprintf (ff,"\n");
              if(jjj==frequence)
              {
               jjj=0;
               fprintf (ff1,"\n");
              }
       }
       fclose(ff);
       fclose(ff1);
}
void UIProject::SaveHistory2(AnsiString strName)
{
        int frequence=60/m_dSamplingTime;

        FILE *ff;
        FILE *ff1;
        ff=fopen(strName.c_str(),"w");
        if(ff == NULL)
          return ;
       for(int i = 0;i<m_nIteratTime;i++)
       {
          fprintf (ff, "%d  ",i+1);
       }
       fprintf (ff,"\n");
              for(int i = 0;i<m_pFCMsNodeList->Count;i++)
              {
                  FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
                  myobj->m_iCurrentNum=0;
                        AnsiString SS;
                        AnsiString Ki=IntToStr(i+1);
                        for(int jjj=0;jjj<Ki.Length();jjj++)
                           SS=SS+" ";
                        SS="%d  "+SS;
                  fprintf (ff,SS.c_str(),i+1);
                  for(int j=0;j<m_nIteratTime;j++)
                  {
                        if(myobj->m_dqHistoryData->at(j)>0)
                          myobj->m_iCurrentNum++;
                        AnsiString SS;
                        AnsiString Ki=IntToStr(j+1);
                        for(int jjj=0;jjj<Ki.Length();jjj++)
                           SS=SS+" ";
                        SS="%d  "+SS;
                        fprintf (ff,SS.c_str(),myobj->m_dqHistoryData->at(j));
                   }
                   fprintf (ff,"\n");
              }
       fclose(ff);
}
const int MAX_VAL = 32767;
double UIProject::grandn(const double Mean, const double SquareMargin)
{
 const double PI = 3.1415926;
 double model = 4294967296.0;
double multiplicator = 663608941.0;
double temp_a, temp_b;
static double seed = (double)time(NULL);

seed *= multiplicator;
seed -= (int)(seed/model) * model;
temp_a = seed/model;

seed *= multiplicator;
seed -= (int)(seed/model) * model;
temp_b = seed/model;

double norm_randn = sqrt(-2*log(temp_a))*cos(2*PI*temp_b);
double gauss_rand = Mean + norm_randn*SquareMargin;
return(gauss_rand);
}
double UIProject::U_Rand( double a,double b )           // uniform distribution 32767
{
    double x=rand();
    return a + (b - a)*x/(MAX_VAL - 1);
}
double UIProject::P_Rand( double Lamda )             // poisson distribution
{
    double x=0,b=1,c=exp( -Lamda ),u;
    do{
        u = U_Rand( 0,1 );
        b *= u;
        if( b >= c )
            x ++;
    }while( b >= c );
    return x;
}
int UIProject::FindSensor(TList*pList,FCMsNode* pFind)
{
	for(int i=0;i<pList->Count;i++)
	{
		FCMsNode* pNode=(FCMsNode*)pList->Items[i];
                if(pFind==pNode)return 1;
	}
        return 0;
}
TList* UIProject::FindDifferentSensors(TList*pList1,TList*pList2)
{
        TList*tmplist=new TList;
	for(int i=0;i<pList1->Count;i++)
	{
		FCMsNode* pNode=(FCMsNode*)pList1->Items[i];
                bool bFount=false;
                for(int i=0;i<pList2->Count;i++)
        	{
		        HISNODE* n1=(HISNODE*)pList2->Items[i];
                        if(pNode==n1->pNode)bFount=true;
	        }
                if(!bFount)
                {tmplist->Add(pNode);}
	}
        return tmplist;
}
int UIProject::Detect(WalkingUser*user,FCMsNode*pNode,int simtime)
{
   float di=sqrt((user->X-pNode->X)*(user->X-pNode->X)+(user->Y-pNode->Y)*(user->Y-pNode->Y));
   FCMsNode* myobj = new FCMsNode;
   FCMsNode* eobj = new FCMsNode;
   if(frmMainFrame->dxBarCombo1->Text=="ON"){
       eobj = (FCMsNode*)user->route->Items[user->route->Count-1]; //提取出行人行走路线上的最后一点
   }
   if(di<(pNode->m_fEffectDis/m_dUnitDistance))
   {
     pNode->m_dValue=1;
     //选择等待时间
     if(frmMainFrame->dxBarCombo1->Text=="ON"){
         /*////////////////////////////////////////
         if(ls->m_strName!=pNode->m_strName){
             flag = true;
             count = 0;
         }
         if(pNode->at->Count==0){
             if(flag==true){
                 ShowMessage("异常路径:自身节点异常");
                 ls = pNode;
                 flag = false;
             }
             else{
                 ls = pNode;
             }
         }
         else{
             if(ls->m_strName!=""){
                 bool b = true;
                 bool l = true;
                 for(int i=0;i<pNode->at->Count;i++){
                     NodeRecord*nr = (NodeRecord*) pNode->at->Items[i];
                     FCMsNode* pn = nr->node;
                     ns = new FCMsNode;
                     ls = pNode;
                     for(int i=0;i<user->route->Count;i++){
                         FCMsNode* ps = (FCMsNode*) user->route->Items[i];
                         if(ps->m_strName == pNode->m_strName){
                             if(i==0){
                                 ns = (FCMsNode*) user->route->Items[i];
                             }
                             else{
                                 ns = (FCMsNode*) user->route->Items[i-1];
                             }
                         }
                     }
                     if(pn->m_strName==ns->m_strName){
                         b = false;
                         //if(pNode->m_iType!=1){
                             count++;
                             if(count>nr->count+3){
                                 if(flag){
                                     ShowMessage("异常路径:停留时间异常");
                                     flag = false;
                                     break;
                                 }
                             }
                             else{
                                 break;
                             }
                         //}
                     }
                 }
                 for(int i=0;i<pNode->at->Count;i++){
                     NodeRecord* nr = (NodeRecord*) pNode->at->Items[i];
                     if(pNode->at->Count>1){
                         NodeRecord* nr = (NodeRecord*) pNode->at->Items[i];
                     }
                 }
                 if(b&&flag){
                     ShowMessage("异常路径:上一节点异常");
                     flag = false;
                     ls = pNode;
                 }
             }
             else{
                 ls = pNode;
                 count++;
             }
         }
         */////////////////////////////////////////pNode->m_iType!=1&&user->waitedSensor!=pNode
         if(stay==0&&user->waitedSensor!=pNode&&user->num<user->route->Count-1){
             user->waitedSensor = pNode;
             int wt = rand()%(5);
             if(wt == 0){
                 int vari = rand()%(5);
                 stay = 10+vari;
                 //试验用
                 stay = 5;
             }
             if(wt == 1){
                 int vari = rand()%(5);
                 stay = 15+vari;
                 //试验用
                 stay = 10;
             }
             if(wt == 2){
                 int vari = rand()%(5);
                 stay = 20+vari;
                 //试验用
                 stay = 15;
             }
             if(wt == 3){
                 int vari = rand()%(5);
                 stay = 20+vari;
                 //试验用
                 stay = 20;
             }
             if(wt == 4){
                 int vari = rand()%(5);
                 stay = 20+vari;
                 //试验用
                 stay = 25;
             }
             wt = rand()%(5);
             if(wt == 0){
                 int vari = rand()%(5);
                 estay = 10+vari;
                 //试验用
                 estay = 5;
             }
             if(wt == 1){
                 int vari = rand()%(5);
                 estay = 15+vari;
                 //试验用
                 estay = 10;
             }
             if(wt == 2){
                 int vari = rand()%(5);
                 estay = 20+vari;
                 //试验用
                 estay = 15;
             }
             if(wt == 3){
                 int vari = rand()%(5);
                 estay = 20+vari;
                 //试验用
                 estay = 20;
             }
             if(wt == 4){
                 int vari = rand()%(5);
                 estay = 20+vari;
                 //试验用
                 estay = 25;
             }
             //estay = stay;
             TListBox* tlb = frmMainFrame->ListBox1;
             tlb->Items->Add(IntToStr(stay));
             tlb->Items->Add(IntToStr(estay));
         //frmMainFrame->ListBox1->Items->Add(IntToStr(user->num));
         }
     }

     //设置节点等待 pNode->m_iType!=1&&
     if(frmMainFrame->dxBarCombo1->Text=="ON"){
         if(stay!=0&&user->waitedSensor==pNode&&user->num!=user->route->Count){
             user->X = pNode->X;
             user->Y = pNode->Y;
             stay--;
         }
     }

     //设置结束节点等待
     if(frmMainFrame->dxBarCombo1->Text=="ON"){
         if(estay!=0&&user->num==user->route->Count-1&&pNode->m_iType!=1&&eobj==pNode){
             user->X = eobj->X;
             user->Y = eobj->Y;
             estay--;
         }
     }

    //寻找触发节点在列表中的位置，并记录下一节点名称
     if(frmMainFrame->dxBarCombo1->Text=="ON"){
     //eobj = (FCMsNode*)user->route->Items[user->route->Count-1];
     if(pNode!=user->m_pLastSensor&&user->num<user->route->Count-1){
         FCMsNode*myobj = (FCMsNode*)user->route->Items[user->num+1];
         user->num++;
         user->m_pNextSensor = myobj;
         user->m_pLastSensor = pNode;
         user->dx = myobj->X;
         user->dy = myobj->Y;
         user->sx = pNode->X;
         user->sy = pNode->Y;
         user->m_pLine=GetLineEventBetweenNodes(user->m_pLastSensor,user->m_pNextSensor);
         frmMainFrame->ListBox1->Items->Add(user->m_pLastSensor->m_strName+"q");
         frmMainFrame->ListBox1->Items->Add(user->m_pNextSensor->m_strName+"q");
         //ls = user->m_pLastSensor;
         //ns = user->m_pNextSensor;
     }
     if(pNode!=user->m_pLastSensor&&user->num==user->route->Count-1&&pNode==eobj){
         FCMsNode*myobj = (FCMsNode*)user->route->Items[user->route->Count-2];
         //FCMsNode*myobj = (FCMsNode*)user->route->Items[user->route->Count-1];
         //user->num++;
         //frmMainFrame->ListBox1->Items->Add(IntToStr(user->num));
         //frmMainFrame->ListBox1->Items->Add(IntToStr(user->route->Count));
         user->m_pNextSensor = myobj;
         user->m_pLastSensor = pNode;
         user->dx = myobj->X;
         user->dy = myobj->Y;
         user->sx = pNode->X;
         user->sy = pNode->Y;
         //ls = user->m_pLastSensor;
         //ns = user->m_pNextSensor;
         //frmMainFrame->ListBox1->Items->Add(IntToStr(user->num));
         user->m_pLine=GetLineEventBetweenNodes(user->m_pLastSensor,user->m_pNextSensor);
         frmMainFrame->ListBox1->Items->Add(user->m_pLastSensor->m_strName+"w");
         frmMainFrame->ListBox1->Items->Add(user->m_pNextSensor->m_strName+"w");
     }
     /*for(int i=0;i<user->route->Count;i++){
             FCMsNode*my = (FCMsNode*)user->route->Items[i];
             if(my->m_strName==pNode->m_strName&&i<user->route->Count-1){
                 myobj = (FCMsNode*)user->route->Items[i+1];
                 user->m_pNextSensor = myobj;
                 user->m_pLastSensor = pNode;
                 user->dx = myobj->X;
                 user->dy = myobj->Y;
                 user->sx = pNode->X;
                 user->sy = pNode->Y;
                 user->m_pLine=GetLineEventBetweenNodes(user->m_pLastSensor,user->m_pNextSensor);
                 ls = user->m_pLastSensor;
                 ns = user->m_pNextSensor;
                 break;
             }
             if(my->m_strName==pNode->m_strName&&i==user->route->Count-1){
                 myobj = (FCMsNode*)user->route->Items[i-1];
                 //user->m_pNextSensor = myobj;
                 user->m_pNextSensor = myobj;
                 //user->m_pLastSensor = pNode;
                 user->m_pLastSensor = pNode;
                 user->dx = myobj->X;
                 user->dy = myobj->Y;
                 user->sx = pNode->X;
                 user->sy = pNode->Y;
                 ls = user->m_pLastSensor;
                 ns = user->m_pNextSensor;
                 user->m_pLine=GetLineEventBetweenNodes(user->m_pLastSensor,user->m_pNextSensor);
                 break;
             }
         }*/

         //if(user->X==eobj->X&&user->Y==eobj->Y&&estay==0){
         //    delete user;
             //return -1;
         //}

         }

          /*
                HISNODE*n1=(HISNODE*)user->m_pPathList->Items[user->m_pPathList->Count-1];
                FCMsNode*myobj = n1->pNode;
                if(myobj==pNode )
                {
                   n1->iTime= simtime;
                }
          */
     if(m_nWorkType==1){
       String s = pNode->m_strName;
       String e = IntToStr(user->m_iNum);
       e = "@"+e;
       String str = s+e;
       user->str = str;
       //AddSimulatingOutput(pNode->m_strName,pNode);
       //加入人物ID
       AddSimulatingOutput(str,pNode);
       }
     return 1;
   }
   return 0;
}
const float Sensitive= 0.16;
int UIProject::NextStep(WalkingUser*user,int simtime)
{
     if(user->m_pNextSensor!=NULL)
     {
     //has arrived the next sensor or not
        float x1=user->sx;float y1=user->sy;
        float x2=user->dx;float y2=user->dy;
        float x3=user->X;float y3=user->Y;
        float dis=m_dSamplingTime*user->m_fSpeed/m_dUnitDistance;
        float x4;float y4;
        if(x1==x2)//1
        {  x4=x1;
           if(y2>y1)y4=y3+dis;
           if(y2<y1)y4=y3-dis;
           user->X=x4;
           user->Y=y4;
           Detect(user,user->m_pLastSensor,simtime);
           Detect(user,user->m_pNextSensor,simtime);
           if((y4>y1&&y4>y2)||(y4<y1&&y4<y2))
           {
              if(user->m_pLine->points==NULL||user->m_pLine->points->Count==0||user->m_iPoint==-2)
              {
                      user->m_pLastSensor=user->m_pNextSensor;
                      user->X=user->m_pLastSensor->X;
                      user->Y=user->m_pLastSensor->Y;
                      user->sx=user->m_pLastSensor->X;
                      user->sy=user->m_pLastSensor->Y;
                      user->m_pNextSensor=NULL;
                      user->m_iPoint=-1;
                      HISNODE*n1=new HISNODE;
                      n1->pNode=user->m_pLastSensor;
                      n1->iTime=simtime;
                      user->m_pPathList->Add(n1);
                      if(user->m_pLastSensor->m_iType!=1){user->m_pNextSensor=NULL;return -1;}//sign leave
              }
              else//have points
              {
                  if(user->m_iDirection==1&&user->m_iPoint<user->m_pLine->points->Count)
                  {
                      user->m_iPoint=user->m_iPoint+1;
                      user->sx=user->dx;
                      user->sy=user->dy;
                      user->X=user->sx;
                      user->Y=user->sy;
                      if(user->m_iPoint>=user->m_pLine->points->Count)
                      {
                              user->dx=user->m_pNextSensor->X;
                              user->dy=user->m_pNextSensor->Y;
                              user->m_iPoint=-2;
                      }
                      else
                      {
                              INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                              user->dx=p->p.x;user->dy=p->p.y;
                      }
                  }//increase
                  else if(user->m_iDirection==-1&&user->m_iPoint>=0)
                  {
                      user->m_iPoint=user->m_iPoint-1;
                      user->sx=user->dx;
                      user->sy=user->dy;
                      user->X=user->sx;
                      user->Y=user->sy;
                      if(user->m_iPoint<0)
                      {
                              user->dx=user->m_pNextSensor->X;
                              user->dy=user->m_pNextSensor->Y;
                              user->m_iPoint=-2;
                      }
                      else
                      {
                              INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                              user->dx=p->p.x;user->dy=p->p.y;
                      }
                  }//decrease
              }//end have points
           }//end (y4>y1&&y4>y2)||(y4<y1&&y4<y2)
        }//end 1
        else//have degree
        {
           float degree=atan(fabs((y2-y1)/(x2-x1)));
           if(degree==0)
           {if(x1>x2){x4=x3-dis;y4=y2;}
            else{x4=x3+dis;y4=y2;}}
           else
           {
               if(x1>x2&&y1>y2)
               {x4=x3-dis*cos(fabs(degree));
                y4=y3-dis*sin(fabs(degree));}
               else if(x1<x2&&y1>y2)
               {x4=x3+dis*cos(fabs(degree));
                y4=y3-dis*sin(fabs(degree));}
               else if(x1>x2&&y1<y2)
               {x4=x3-dis*cos(fabs(degree));
                y4=y3+dis*sin(fabs(degree));}
               else if(x1<x2&&y1<y2)
               {x4=x3+dis*cos(fabs(degree));
                 y4=y3+dis*sin(fabs(degree));}
           }
           user->X=x4;user->Y=y4;
           Detect(user,user->m_pLastSensor,simtime);
           Detect(user,user->m_pNextSensor,simtime);
           if((x4>x1&&x4>x2)||(x4<x1&&x4<x2))//off the line
           {
             if(user->m_pLine->points==NULL||user->m_pLine->points->Count==0||user->m_iPoint==-2)
             {
              user->m_pLastSensor=user->m_pNextSensor;
              user->X=user->m_pLastSensor->X;
              user->Y=user->m_pLastSensor->Y;
              user->m_pNextSensor=NULL;
              user->m_iPoint=-1;
              user->sx=user->m_pLastSensor->X;
              user->sy=user->m_pLastSensor->Y;
              HISNODE*n1=new HISNODE;
              n1->pNode=user->m_pLastSensor;
              n1->iTime=simtime;
              user->m_pPathList->Add(n1);
              if(m_iSwitch&&user->m_pLastSensor->m_iType!=1){user->m_pNextSensor=NULL;return -1;}//sign leave
             }
             else //have points
             {
                  if(user->m_iDirection==1&&user->m_iPoint<user->m_pLine->points->Count)
                  {
                      user->m_iPoint=user->m_iPoint+1;
                      user->sx=user->dx;
                      user->sy=user->dy;
                      user->X=user->sx;
                      user->Y=user->sy;

                      if(user->m_iPoint>=user->m_pLine->points->Count)
                      {
                              user->dx=user->m_pNextSensor->X;
                              user->dy=user->m_pNextSensor->Y;
                              user->m_iPoint=-2;
                      }
                      else
                      {
                              INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                              user->dx=p->p.x;user->dy=p->p.y;
                      }
                  }//increase
                  else if(user->m_iDirection==-1&&user->m_iPoint>=0)
                  {
                      user->m_iPoint=user->m_iPoint-1;
                      user->sx=user->dx;
                      user->sy=user->dy;
                      user->X=user->sx;
                      user->Y=user->sy;
                      if(user->m_iPoint<0)
                      {
                              user->dx=user->m_pNextSensor->X;
                              user->dy=user->m_pNextSensor->Y;
                              user->m_iPoint=-2;
                      }
                      else
                      {
                              INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                              user->dx=p->p.x;user->dy=p->p.y;
                      }
                  }//decrease
              }//end have points
           }//end off the line
           else//in the line
           {
               float di=sqrt((y2-y4)*(y2-y4)+(x2-x4)*(x2-x4));
               if(di<Sensitive)
               {
                     if(user->m_pLine->points==NULL||user->m_pLine->points->Count==0||user->m_iPoint==-2)
                     {
                               user->m_pLastSensor=user->m_pNextSensor;
                               user->X=user->m_pLastSensor->X;
                               user->Y=user->m_pLastSensor->Y;
                               user->m_pNextSensor=NULL;
                               user->m_iPoint=-1;
                               HISNODE*n1=new HISNODE;
                               n1->pNode=user->m_pLastSensor;
                               n1->iTime=simtime;
                               user->m_pPathList->Add(n1);

                               user->sx=user->m_pLastSensor->X;
                               user->sy=user->m_pLastSensor->Y;
                               if(m_iSwitch&&user->m_pLastSensor->m_iType!=1){user->m_pNextSensor=NULL;return -1;}//sign leave
                     }
                     else
                     {
                        if(user->m_iDirection==1&&user->m_iPoint<user->m_pLine->points->Count)
                        {
                                user->m_iPoint=user->m_iPoint+1;
                                user->sx=user->dx;
                                user->sy=user->dy;
                                user->X=user->sx;
                                user->Y=user->sy;

                                if(user->m_iPoint>=user->m_pLine->points->Count)
                                {
                                        user->dx=user->m_pNextSensor->X;
                                        user->dy=user->m_pNextSensor->Y;
                                        user->m_iPoint=-2;
                                }
                                else
                                {
                                        INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                                        user->dx=p->p.x;user->dy=p->p.y;
                                }
                        }//increase
                        else if(user->m_iDirection==-1&&user->m_iPoint>=0)
                        {
                                user->m_iPoint=user->m_iPoint-1;
                                user->sx=user->dx;
                                user->sy=user->dy;
                                user->X=user->sx;
                                user->Y=user->sy;

                                if(user->m_iPoint<0)
                                {
                                        user->dx=user->m_pNextSensor->X;
                                        user->dy=user->m_pNextSensor->Y;
                                        user->m_iPoint=-2;
                                }
                                else
                                {
                                        INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                                        user->dx=p->p.x;user->dy=p->p.y;
                                }
                        }//decrease
                     }// into sensitive
               }
           }
        }//
     }
     if(user->m_pNextSensor==NULL)
     {
          FCMsNode* pNode;
          if(m_iSwitch)
          {
                TList*pConnected=new TList;
                user->m_pLastSensor->GetConnectedNodes(pConnected);
                TList*tmplist=FindDifferentSensors(pConnected,user->m_pPathList);
                pConnected->Clear();
                delete pConnected;
                if(tmplist->Count==0){user->m_pNextSensor=NULL;return -1;}//no more option
                int next=rand()%(tmplist->Count);
                pNode=(FCMsNode*)tmplist->Items[next];
                tmplist->Clear();
                delete tmplist;
          }
          else
          {
                TList*pConnected=new TList;
                user->m_pLastSensor->GetConnectedNodes(pConnected);
                int next=rand()%(pConnected->Count);
                pNode=(FCMsNode*)pConnected->Items[next];
                pConnected->Clear();
                delete pConnected;
          }
          user->m_pNextSensor=pNode;
          user->m_pLine=GetLineEventBetweenNodes(user->m_pLastSensor,user->m_pNextSensor);
          frmMainFrame->ListBox1->Items->Add(user->m_pLastSensor->m_strName+"p");
          frmMainFrame->ListBox1->Items->Add(user->m_pNextSensor->m_strName+"p");
          if(user->m_pLine->points==NULL||user->m_pLine->points->Count==0)
          {
                  user->dx=pNode->X;
                  user->dy=pNode->Y;
                  user->m_iPoint=-1;
          }
          else
          {
           if(user->m_pNextSensor==user->m_pLine->ObjectDest)
           {
              user->m_iDirection=1;
              user->m_iPoint=0;
              INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
              user->dx=p->p.x;user->dy=p->p.y;
           }
           else
           {
              user->m_iDirection=-1;
              user->m_iPoint=user->m_pLine->points->Count-1;
              INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
              user->dx=p->p.x;user->dy=p->p.y;
           }
          }
          Detect(user,user->m_pLastSensor,simtime);
          Detect(user,user->m_pNextSensor,simtime);
     }
     return 1;
}
int UIProject::NextStep2(WalkingUser*user,int simtime)
{
     //结束，等待时间重置
     //if(frmMainFrame->dxBarCombo1->Text=="ON"&&user->m_pLastSensor==user->m_pNextSensor){
         //delete user;
     if(frmMainFrame->dxBarCombo1->Text=="ON"&&estay==0)
     {
         //if(user==NULL||user->m_pLastSensor==user->m_pNextSensor){
         //    Sleep(500);
         //    AddSimulatingOutput(user->str,user->m_pLastSensor);
             stay = 0;
             estay = 0;
             ShowMessage("计算");
             //Application->ProcessMessages();
            //delete user;
            return -1;
         //}
     }
     if(user->m_pNextSensor==NULL)
     {
          //设置下一节点
          if(frmMainFrame->dxBarCombo1->Text=="ON")
          {
              FCMsNode* myobj;
              for(int i=0;i<user->route->Count;i++)
              {
                        FCMsNode*my = (FCMsNode*)user->route->Items[i];
                        if(my->m_strName==user->m_pLastSensor->m_strName&&i!=user->route->Count-1)
                        {
                                myobj = (FCMsNode*)user->route->Items[i+1];
                                break;
                        }
                        if(my->m_strName==user->m_pLastSensor->m_strName&&i==user->route->Count-1)
                        {
                                myobj = (FCMsNode*)user->route->Items[i];
                                break;
                        }
                }
               //user->m_pNextSensor = myobj;
               //user->dx = myobj->X;
               //user->dy = myobj->Y;
               //user->m_pLine=GetLineEventBetweenNodes(user->m_pLastSensor,user->m_pNextSensor);
               if(user->num<user->route->Count-1)
               {
                  user->m_pNextSensor = (FCMsNode*)user->route->Items[user->num];
                  user->m_pLine=GetLineEventBetweenNodes(user->m_pLastSensor,user->m_pNextSensor);
                  //frmMainFrame->ListBox1->Items->Add(user->m_pLastSensor->m_strName+"u");
                  //frmMainFrame->ListBox1->Items->Add(user->m_pNextSensor->m_strName+"u");
              }
              else if(user->num==user->route->Count-1)
              {
                  user->m_pNextSensor = (FCMsNode*)user->route->Items[user->route->Count-2];
                  user->m_pLine=GetLineEventBetweenNodes(user->m_pLastSensor,user->m_pNextSensor);
                  //frmMainFrame->ListBox1->Items->Add(user->m_pLastSensor->m_strName+"u");
                  //frmMainFrame->ListBox1->Items->Add(user->m_pNextSensor->m_strName+"u");
              }
         }



          FCMsNode* pNode;
          if(m_iSwitch)
          {
                TList*pConnected=new TList;
                user->m_pLastSensor->GetConnectedNodes(pConnected);
                TList*tmplist=FindDifferentSensors(pConnected,user->m_pPathList);
                pConnected->Clear();
                delete pConnected;
                if(tmplist->Count==0){user->m_pNextSensor=NULL;return -1;}//no more option
                int next=rand()%(tmplist->Count);
                pNode=(FCMsNode*)tmplist->Items[next];
                tmplist->Clear();
                delete tmplist;
          }
          else
          {
                TList*pConnected=new TList;
                user->m_pLastSensor->GetConnectedNodes(pConnected);
                int next=rand()%(pConnected->Count);
                pNode=(FCMsNode*)pConnected->Items[next];
                pConnected->Clear();
                delete pConnected;
          }

          if(frmMainFrame->dxBarCombo1->Text=="OFF")
          {
              user->m_pNextSensor=pNode;
              user->m_pLine=GetLineEventBetweenNodes(user->m_pLastSensor,user->m_pNextSensor);
              //frmMainFrame->ListBox1->Items->Add(user->m_pLastSensor->m_strName+"a");
              //frmMainFrame->ListBox1->Items->Add(user->m_pNextSensor->m_strName+"a");
          }
          else if(frmMainFrame->dxBarCombo1->Text=="ON")
          {
                  user->m_pLine=GetLineEventBetweenNodes(user->m_pLastSensor,user->m_pNextSensor);
                  //frmMainFrame->ListBox1->Items->Add(user->m_pLastSensor->m_strName+"e");
                  //frmMainFrame->ListBox1->Items->Add(user->m_pNextSensor->m_strName+"e");
          }
          if(user->m_pLine->points==NULL||user->m_pLine->points->Count==0)
          {
                  user->dx=pNode->X;
                  user->dy=pNode->Y;
                  user->m_iPoint=-1;
          }
          else
          {
                if(user->m_pNextSensor==user->m_pLine->ObjectDest)
                {
                        user->m_iDirection=1;
                        user->m_iPoint=0;
                        INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                        user->dx=p->p.x;user->dy=p->p.y;
                }
                else
                {
                        user->m_iDirection=-1;
                        user->m_iPoint=user->m_pLine->points->Count-1;
                        INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                        user->dx=p->p.x;user->dy=p->p.y;
                }
          }
     }
     if(user->m_pNextSensor!=NULL)
     {
     //has arrived the next sensor or not
        float x1=user->sx;float y1=user->sy;
        float x2=user->dx;float y2=user->dy;
        float x3=user->X;float y3=user->Y;
        float dis=m_dSamplingTime*user->m_fSpeed/m_dUnitDistance;
        float x4;float y4;
        if(x1==x2)//1
        {
                x4=x1;
                if(y2>=y1)
                        y4=y3+dis;
                if(y2<=y1)
                        y4=y3-dis;
                user->X=x4;
                user->Y=y4;
                if((y4>=y1&&y4>=y2)||(y4<=y1&&y4<=y2))
                {
                        if(frmMainFrame->dxBarCombo1->Text=="ON")
                        {
                                user->m_pLine=GetLineEventBetweenNodes(user->m_pLastSensor,user->m_pNextSensor);
                                //frmMainFrame->ListBox1->Items->Add(user->m_pLastSensor->m_strName+"r");
                                //frmMainFrame->ListBox1->Items->Add(user->m_pNextSensor->m_strName+"r");
                        }
                        if(user->m_pLine->points==NULL||user->m_pLine->points->Count==0||user->m_iPoint==-2)
                        {
                                if(frmMainFrame->dxBarCombo1->Text=="OFF")
                                {
                                        user->m_pLastSensor=user->m_pNextSensor;
                                }
                                user->X=user->m_pLastSensor->X;
                                user->Y=user->m_pLastSensor->Y;
                                user->sx=user->m_pLastSensor->X;
                                user->sy=user->m_pLastSensor->Y;
                                if(frmMainFrame->dxBarCombo1->Text=="OFF")
                                {
                                        user->m_pNextSensor=NULL;
                                }
                                user->m_iPoint=-1;
                                HISNODE*n1=new HISNODE;
                                n1->pNode=user->m_pLastSensor;
                                n1->iTime=simtime;
                                user->m_pPathList->Add(n1);

                                if(frmMainFrame->dxBarCombo1->Text=="OFF")
                                {
                                        if(user->m_pLastSensor->m_iType!=1){user->m_pNextSensor=NULL;return -1;}
                                }
                                //if(user->m_pLastSensor->m_iType!=1){user->m_pNextSensor=NULL;return -1;}//sign leave
                        }
                        else//have points
                        {
                                if(user->m_iDirection==1&&user->m_iPoint<user->m_pLine->points->Count)
                                {
                                        user->m_iPoint=user->m_iPoint+1;
                                        user->sx=user->dx;
                                        user->sy=user->dy;
                                        user->X=user->sx;
                                        user->Y=user->sy;
                                        if(user->m_iPoint>=user->m_pLine->points->Count)
                                        {
                                                user->dx=user->m_pNextSensor->X;
                                                user->dy=user->m_pNextSensor->Y;
                                                user->m_iPoint=-2;
                                        }
                                else
                                {
                                        INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                                        user->dx=p->p.x;user->dy=p->p.y;
                                }
                        }//increase
                        else if(user->m_iDirection==-1&&user->m_iPoint>=0)
                        {
                                user->m_iPoint=user->m_iPoint-1;
                                user->sx=user->dx;
                                user->sy=user->dy;
                                user->X=user->sx;
                                user->Y=user->sy;
                                if(user->m_iPoint<0)
                                {
                                        user->dx=user->m_pNextSensor->X;
                                        user->dy=user->m_pNextSensor->Y;
                                        user->m_iPoint=-2;
                                }
                                else
                                {
                                        INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                                        user->dx=p->p.x;user->dy=p->p.y;
                                }
                        }//decrease
                }//end have points
              //////////////

              }//end (y4>y1&&y4>y2)||(y4<y1&&y4<y2)
        }//end 1
        else//have degree
        {
           float degree=atan(fabs((y2-y1)/(x2-x1)));
           if(degree==0)
           {if(x1>x2){x4=x3-dis;y4=y2;}
            else{x4=x3+dis;y4=y2;}}
           else
           {
               if(x1>x2&&y1>y2)
               {x4=x3-dis*cos(fabs(degree));
                y4=y3-dis*sin(fabs(degree));}
               else if(x1<x2&&y1>y2)
               {x4=x3+dis*cos(fabs(degree));
                y4=y3-dis*sin(fabs(degree));}
               else if(x1>x2&&y1<y2)
               {x4=x3-dis*cos(fabs(degree));
                y4=y3+dis*sin(fabs(degree));}
               else if(x1<x2&&y1<y2)
               {x4=x3+dis*cos(fabs(degree));
                 y4=y3+dis*sin(fabs(degree));}
           }
           user->X=x4;user->Y=y4;
           if((x4>=x1&&x4>=x2)||(x4<=x1&&x4<=x2))//off the line
           {
             if(frmMainFrame->dxBarCombo1->Text=="ON"){
                 user->m_pLine=GetLineEventBetweenNodes(user->m_pLastSensor,user->m_pNextSensor);
                 frmMainFrame->ListBox1->Items->Add(user->m_pLastSensor->m_strName+"t");
                 frmMainFrame->ListBox1->Items->Add(user->m_pNextSensor->m_strName+"t");
             }
             if(user->m_pLine->points==NULL||user->m_pLine->points->Count==0||user->m_iPoint==-2)
             {
              //防止点的瞬移
              if(frmMainFrame->dxBarCombo1->Text=="OFF"){
                  user->m_pLastSensor=user->m_pNextSensor;
              }
              user->X=user->m_pLastSensor->X;
              user->Y=user->m_pLastSensor->Y;
              if(frmMainFrame->dxBarCombo1->Text=="OFF"){
              user->m_pNextSensor=NULL;
              }
              user->m_iPoint=-1;
              user->sx=user->m_pLastSensor->X;
              user->sy=user->m_pLastSensor->Y;
              HISNODE*n1=new HISNODE;
              n1->pNode=user->m_pLastSensor;
              n1->iTime=simtime;
              user->m_pPathList->Add(n1);
              if(frmMainFrame->dxBarCombo1->Text=="OFF"){
                  if(user->m_pLastSensor->m_iType!=1){user->m_pNextSensor=NULL;return -1;}
                  }
              //if(m_iSwitch&&user->m_pLastSensor->m_iType!=1){user->m_pNextSensor=NULL;return -1;}//sign leave
             }
             else //have points
             {
                  if(user->m_iDirection==1&&user->m_iPoint<user->m_pLine->points->Count)
                  {
                      user->m_iPoint=user->m_iPoint+1;
                      user->sx=user->dx;
                      user->sy=user->dy;
                      user->X=user->sx;
                      user->Y=user->sy;

                      if(user->m_iPoint>=user->m_pLine->points->Count)
                      {
                              user->dx=user->m_pNextSensor->X;
                              user->dy=user->m_pNextSensor->Y;
                              user->m_iPoint=-2;
                      }
                      else
                      {
                              INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                              user->dx=p->p.x;user->dy=p->p.y;
                      }
                  }//increase
                  else if(user->m_iDirection==-1&&user->m_iPoint>=0)
                  {
                      user->m_iPoint=user->m_iPoint-1;
                      user->sx=user->dx;
                      user->sy=user->dy;
                      user->X=user->sx;
                      user->Y=user->sy;
                      if(user->m_iPoint<0)
                      {
                              user->dx=user->m_pNextSensor->X;
                              user->dy=user->m_pNextSensor->Y;
                              user->m_iPoint=-2;
                      }
                      else
                      {
                              INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                              user->dx=p->p.x;user->dy=p->p.y;
                      }
                  }//decrease
              }//end have points



           }//end off the line
           else//in the line
           {
               float di=sqrt((y2-y4)*(y2-y4)+(x2-x4)*(x2-x4));
               if(di<Sensitive)
               {
                     if(frmMainFrame->dxBarCombo1->Text=="ON"){
                         user->m_pLine=GetLineEventBetweenNodes(user->m_pLastSensor,user->m_pNextSensor);
                         frmMainFrame->ListBox1->Items->Add(user->m_pLastSensor->m_strName+"y");
                         frmMainFrame->ListBox1->Items->Add(user->m_pNextSensor->m_strName+"y");
                     }
                     //防止点的瞬移.
                     if(user->m_pLine->points==NULL||user->m_pLine->points->Count==0||user->m_iPoint==-2)
                     {
                               if(frmMainFrame->dxBarCombo1->Text=="OFF"){
                                   user->m_pLastSensor=user->m_pNextSensor;
                               }
                               user->X=user->m_pLastSensor->X;
                               user->Y=user->m_pLastSensor->Y;
                               if(frmMainFrame->dxBarCombo1->Text=="OFF"){
                                    user->m_pNextSensor=NULL;
                               }
                               user->m_iPoint=-1;
                               HISNODE*n1=new HISNODE;
                               n1->pNode=user->m_pLastSensor;
                               n1->iTime=simtime;
                               user->m_pPathList->Add(n1);

                               user->sx=user->m_pLastSensor->X;
                               user->sy=user->m_pLastSensor->Y;
                               if(frmMainFrame->dxBarCombo1->Text=="OFF"){
                                   if(user->m_pLastSensor->m_iType!=1){user->m_pNextSensor=NULL;return -1;}
                               }
                               //if(m_iSwitch&&user->m_pLastSensor->m_iType!=1){user->m_pNextSensor=NULL;return -1;}//sign leave
                     }
                     else
                     {
                        if(user->m_iDirection==1&&user->m_iPoint<user->m_pLine->points->Count)
                        {
                                user->m_iPoint=user->m_iPoint+1;
                                user->sx=user->dx;
                                user->sy=user->dy;
                                user->X=user->sx;
                                user->Y=user->sy;

                                if(user->m_iPoint>=user->m_pLine->points->Count)
                                {
                                        user->dx=user->m_pNextSensor->X;
                                        user->dy=user->m_pNextSensor->Y;
                                        user->m_iPoint=-2;
                                }
                                else
                                {
                                        INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                                        user->dx=p->p.x;user->dy=p->p.y;
                                }
                        }//increase
                        else if(user->m_iDirection==-1&&user->m_iPoint>=0)
                        {
                                user->m_iPoint=user->m_iPoint-1;
                                user->sx=user->dx;
                                user->sy=user->dy;
                                user->X=user->sx;
                                user->Y=user->sy;

                                if(user->m_iPoint<0)
                                {
                                        user->dx=user->m_pNextSensor->X;
                                        user->dy=user->m_pNextSensor->Y;
                                        user->m_iPoint=-2;
                                }
                                else
                                {
                                        INFLEXTION*p=(INFLEXTION*)user->m_pLine->points->Items[user->m_iPoint];
                                        user->dx=p->p.x;user->dy=p->p.y;
                                }
                        }//decrease
                     }// into sensitive
               }
           }
        }//
     }

     return 1;
}
//********************By WYP at 20140527****************************************
int UIProject::NodeTrigger(TList*myUserList,FCMsNode*myNode,int simtime)
{
     for(int i=0;i<myUserList->Count;i++)
     {
          WalkingUser*user=(WalkingUser*)myUserList->Items[i];
          if(Detect(user,myNode,simtime)>0)
                return i+1;
     }
     return 0;
}
//******************************************************************************

//******************************************************************************
double UIProject::Similarity(TList* list1,TList* list2)  //计算两轨迹间的相似度
{
      vector<FCMsNode*>union1;
      vector<FCMsNode*>union2;
      vector<FCMsNode*>union11;
      vector<FCMsNode*>union22;
      int min_count=0;
      double sim=0;
      double sum_list1=0;
      double sum_list2=0;
      double sum_union=0;

      for(int i=0;i<list1->Count;i++)
      {
             FCMsNode*obj1=(FCMsNode*)list1->Items[i];
             for(int j=0;j<list2->Count;j++)
             {
                  FCMsNode*obj2=(FCMsNode*)list2->Items[j];
                  if(obj1->m_iPosition==obj2->m_iPosition)
                  {
                        union1.push_back(obj1);
                        break;
                  }
             }
      }

      for(int i=0;i<list2->Count;i++)
      {
             FCMsNode*obj2=(FCMsNode*)list2->Items[i];
             for(int j=0;j<list1->Count;j++)
             {
                  FCMsNode*obj1=(FCMsNode*)list1->Items[j];
                  if(obj2->m_iPosition==obj1->m_iPosition)
                  {
                        union2.push_back(obj2);
                        break;
                  }
             }
      }

      if(union1.capacity()<union2.capacity())
      {
            min_count=union1.capacity();
      }
      else
      {
            min_count=union2.capacity();
      }

      for(int i=0;i<min_count;i++)
      {
               FCMsNode*node1=union1.at(i);
               FCMsNode*node2=union2.at(i);
               if(node1->m_iPosition==node2->m_iPosition)
               {
                     union11.push_back(node1);
                     union22.push_back(node2);
               }
      }

     for(int i=0;i<list1->Count;i++)
     {
            FCMsNode*obj1=(FCMsNode*)list1->Items[i];
            sum_list1+=obj1->m_iInf*obj1->m_iInf;
     }

     for(int i=0;i<list2->Count;i++)
     {
            FCMsNode*obj2=(FCMsNode*)list2->Items[i];
            sum_list2+=obj2->m_iInf*obj2->m_iInf;
     }

     for(int i=0;i<union11.capacity();i++)
     {
            FCMsNode*node1=union1.at(i);
            FCMsNode*node2=union2.at(i);
            sum_union+=node1->m_iInf*node2->m_iInf;
     }

     sim=sum_union/(sqrt(sum_list1)*sqrt(sum_list2));
     return sim;
}
//******************************************************************************

//*******************By WYP at 20150601*****************************************

//******************************************************************************

void UIProject::Simulate()
{
       int frequence=60/m_dSamplingTime;
       TList*pUserList=new TList;
       m_pUserHistory->Clear();
       srand((unsigned)time(0));
       TList*pMarkSensors;
       if(m_iSwitch)
       {
               pMarkSensors=new TList;
               GetAllMarkSensors(pMarkSensors);
       }
       else
               pMarkSensors=this->m_pFCMsNodeList;
       ClearSimulatingOutput();
       int jjj=0;

       FILE *ff;
       ff=fopen("density.txt","w");
       if(ff == NULL)
          return ;

       for (int simTime=1;simTime<=m_nIteratTime;simTime++)
       {
         jjj++;
         if(jjj==frequence)
         {
                jjj=0;
                fprintf (ff, "%d\n",pUserList->Count);

         }
       //all sensor has triggered data =0;
        for(int i = 0;i<m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
          myobj->m_dValue=0;
        }
        //current user keep walking
        for(int i=0;i<pUserList->Count;i++)
        {
          WalkingUser*user=(WalkingUser*)pUserList->Items[i];
          if(NextStep2(user,simTime)<0)
          {
            user->m_iEnd=simTime;
            pUserList->Delete(i);i--;
          }
        }
        for(int i = 0;i<m_pFCMsNodeList->Count;i++)
        {
                FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
                NodeTrigger(pUserList,myobj,simTime);
        }
        //new user or not
        int tmp=(int)P_Rand(m_dLambda);
        if (tmp>0.1)//new user
        {
           //SignCome;
           TList*newUserList=new TList;
           for(int k=0;k<tmp;k++)
           {
             //int comeindex=rand()%(m_pFCMsNodeList->Count);
             int comeindex=rand()%(pMarkSensors->Count);
             FCMsNode*myobj = (FCMsNode*)pMarkSensors->Items[comeindex];
             WalkingUser*user=new WalkingUser;
             user->m_iNum=m_pUserHistory->Count;
             user->m_iBegin=simTime;
             user->m_fMeanSpeed =m_dWalkingSpeed;
             user->m_fVariance=m_fAllVariance;
             user->m_fSpeed=grandn(m_dWalkingSpeed,user->m_fVariance);
             user->X=myobj->X;
             user->Y=myobj->Y;
             user->m_pLastSensor=myobj;
             user->sx=myobj->X;
             user->sy=myobj->Y;
             user->m_iPoint=-1;
             HISNODE*n1=new HISNODE;
             n1->pNode=myobj;
             n1->iTime=simTime;
             user->m_pPathList->Add(n1);
             newUserList->Add(user);
             pUserList->Add(user);
             m_pUserHistory->Add(user);
           }
           for(int i = 0;i<m_pFCMsNodeList->Count;i++)
           {
                FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
                NodeTrigger(newUserList,myobj,simTime);
           }
           newUserList->Clear();
           delete newUserList;
        }
        //save all sensor triggered data
        for(int i = 0;i<m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
          myobj->StoreOldData(myobj->m_dValue);
        }
       }
       if(m_iSwitch)
       {
               pMarkSensors->Clear();
               delete pMarkSensors;
       }
       fclose(ff);
       pUserList->Clear();
       delete pUserList;
}
void UIProject::Simulate2()
{
       int frequence=60/m_dSamplingTime;
       TList*pUserList=new TList;
       m_pUserHistory->Clear();
       srand((unsigned)time(0));
       TList*pMarkSensors;
       if(m_iSwitch)
       {
               pMarkSensors=new TList;
               GetAllMarkSensors(pMarkSensors);
       }
       else
               pMarkSensors=this->m_pFCMsNodeList;
       ClearSimulatingOutput();
       int jjj=0;

       FILE *ff;
       ff=fopen("density.txt","w");
       if(ff == NULL)
          return ;
               //new user or not
        int tmp=m_dLambda;
        if (tmp>0)//new user
        {
           //SignCome;
           for(int k=0;k<tmp;k++)
           {
             //int comeindex=rand()%(m_pFCMsNodeList->Count);
             int comeindex=rand()%(pMarkSensors->Count);
             FCMsNode*myobj = (FCMsNode*)pMarkSensors->Items[comeindex];
             WalkingUser*user=new WalkingUser;
             user->m_iNum=m_pUserHistory->Count;
             user->m_iBegin=1;
             user->m_fMeanSpeed =m_dWalkingSpeed;
             user->m_fVariance=m_fAllVariance;
             user->m_fSpeed=grandn(m_dWalkingSpeed,user->m_fVariance);
             user->X=myobj->X;
             user->Y=myobj->Y;
             user->m_pLastSensor=myobj;
             user->sx=myobj->X;
             user->sy=myobj->Y;
             user->m_iPoint=-1;
             HISNODE*n1=new HISNODE;
             n1->pNode=myobj;
             n1->iTime=1;
             user->m_pPathList->Add(n1);
             pUserList->Add(user);
             m_pUserHistory->Add(user);
           }
           for(int i = 0;i<m_pFCMsNodeList->Count;i++)
           {
                FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
                NodeTrigger(pUserList,myobj,1);
           }
        }
               //save all sensor triggered data
        for(int i = 0;i<m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
          myobj->StoreOldData(myobj->m_dValue);
        }
       for (int simTime=1;simTime<=m_nIteratTime;simTime++)
       {
         jjj++;
         if(jjj==frequence)
         {
                jjj=0;
                fprintf (ff, "%d\n",pUserList->Count);

         }
       //all sensor has triggered data =0;
        for(int i = 0;i<m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
          myobj->m_dValue=0;
        }
        //current user keep walking
        for(int i=0;i<pUserList->Count;i++)
        {
          WalkingUser*user=(WalkingUser*)pUserList->Items[i];
          NextStep2(user,simTime);
        }
           for(int i = 0;i<m_pFCMsNodeList->Count;i++)
           {
                FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
                NodeTrigger(pUserList,myobj,simTime);
           }
        //save all sensor triggered data
        for(int i = 0;i<m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
          myobj->StoreOldData(myobj->m_dValue);
        }
       }
       if(m_iSwitch)
       {
               pMarkSensors->Clear();
               delete pMarkSensors;
       }
       fclose(ff);
       pUserList->Clear();
       delete pUserList;
}
void UIProject::Draw (TCanvas* m_canvas) //图像显示
{
      if(m_pFCMsNodeList!=NULL)
       {
          for (int i = 0; i < m_pFCMsNodeList->Count; i++)
          {
            FCMsNode* myobj = (FCMsNode*) m_pFCMsNodeList->Items[i];
            myobj->Draw(m_canvas);     //调用NodeEvent.cpp中对节点进行显示的Draw方法
          }
       }
       if(m_pLineEventList!=NULL)
       {
          for (int i = 0; i < m_pLineEventList->Count; i++)
          {
            LineEvent* myobj = (LineEvent*) m_pLineEventList->Items[i];
            myobj->Draw(m_canvas);
          }
       }
       //draw users
       if(frmMainFrame->m_pSimulator!=NULL)
       {

                  TColor cl= m_canvas->Brush->Color;
                  m_canvas->Brush->Color=clRed;

                for(int i=0;i<frmMainFrame->m_pSimulator->m_pUserList->Count;i++)
                {
                  WalkingUser*user=(WalkingUser*)frmMainFrame->m_pSimulator->m_pUserList->Items[i];
                  TRect rect;
                  rect.Left = (user->X- gbl_ItemSize/2- XOrientation)*proportion;
                  rect.Top = (user->Y-gbl_ItemSize/2- YOrientation)*proportion;
                  rect.right =(user->X+gbl_ItemSize/2- XOrientation)*proportion;
                  rect.Bottom = (user->Y+gbl_ItemSize/2- YOrientation)*proportion;
                  m_canvas->Ellipse(rect);

                  m_canvas->TextOutA((user->X- XOrientation)*proportion - m_canvas->TextWidth(IntToStr(i+1))/2
                  ,(user->Y- YOrientation)*proportion,IntToStr(i+1));

                }
                   m_canvas->Brush->Color=cl;
       }
}


