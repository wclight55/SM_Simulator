#include "property.h"
#include "Simulator.h"
void UIProject::SaveToXML(AnsiString fileName)
{
    TStrings* tstr = new TStringList();
    tstr->Add("<?xml version='1.0' encoding='gb2312'?>");
    tstr->Add("<Root>");
    tstr->Add("</Root>");
    XMLDoc->XML = tstr;
    IXMLNode *node1, *node2,*node3,*node4,*node5,*node6;
    if (! XMLDoc->Active)
        XMLDoc->Active = True;
    node1 = XMLDoc->DocumentElement->AddChild("ModelProperty");
    node2 = node1->AddChild("ModelName");
    node2->Text = m_strProjectName;
    node2 = node1->AddChild("Author");
    node2->Text = m_strProjectAuthor;
    node2 = node1->AddChild("ModelDiscript");
    node2->Text = m_strProjectDiscription;
    node2 = node1->AddChild("Lambda");
    node2->Text = AnsiString(m_dLambda);;
    node2 = node1->AddChild("UnitDistance");
    node2->Text = AnsiString(m_dUnitDistance);;
    node2 = node1->AddChild("SamplingTime");
    node2->Text = AnsiString(m_dSamplingTime);
    node2 = node1->AddChild("SpeedVariance");
    node2->Text = AnsiString(m_fAllVariance);
    node2 = node1->AddChild("WalkingSpeed");
    node2->Text = AnsiString(m_dWalkingSpeed);
    node2 = node1->AddChild("IterationTime");
    node2->Text = AnsiString(m_nIteratTime);

    node2 = node1->AddChild("XOFF");
    node2->Text = AnsiString(XOrientation);
    node2 = node1->AddChild("YOFF");
    node2->Text = AnsiString(YOrientation);
    node2 = node1->AddChild("Prop");
    node2->Text = AnsiString(proportion);

    node2 = node1->AddChild("LayoutFile");
    node2->Text = AnsiString(m_strLayout);

    node2 = node1->AddChild("NodeUI");  //定义节点属性
    node3 = node2->AddChild("LineColor");
    node3->Text = ColorToString(m_FCMsNodeUI.m_tcLinePenColor);
    node3 = node2->AddChild("LineWidth");
    node3->Text = AnsiString(m_FCMsNodeUI.m_iLinePenWidth);
    node3 = node2->AddChild("BrushColor");
    node3->Text = ColorToString(m_FCMsNodeUI.m_tcBrushColor);
    node3 = node2->AddChild("FontColor");
    node3->Text = ColorToString(m_FCMsNodeUI.m_tcFontColor);
    node3 = node2->AddChild("FontSize");
    node3->Text = IntToStr(m_FCMsNodeUI.m_iFontSize);

    node2 = node1->AddChild("LineUI");    //定义线条属性
    node3 = node2->AddChild("LineColor");
    node3->Text = ColorToString(m_LineUI.m_tcLinePenColor);
    node3 = node2->AddChild("LineWidth");
    node3->Text = AnsiString(m_LineUI.m_iLinePenWidth);
    node3 = node2->AddChild("BrushColor");
    node3->Text = ColorToString(m_LineUI.m_tcBrushColor);
    node3 = node2->AddChild("FontColor");
    node3->Text = ColorToString(m_LineUI.m_tcFontColor);
    node3 = node2->AddChild("FontSize");
    node3->Text = AnsiString(m_LineUI.m_iFontSize);

    node1 = XMLDoc->DocumentElement->AddChild("NodesList"); //添加节点列表
    for (int i = 0; i < m_pFCMsNodeList->Count; i++)
    {
        FCMsNode* myobj = (FCMsNode*) m_pFCMsNodeList->Items[i];//依次读取每一个节点，添加相应的属性。
        node2 = node1->AddChild("Node");
        node3 = node2->AddChild("ID");
        node3->Text = IntToStr(myobj->ID);
        node3 = node2->AddChild("Name");
        node3->Text = myobj->m_strName;
        node3 = node2->AddChild("Discription");
        node3->Text = myobj->m_strDiscrip;
        node3 = node2->AddChild("X");
        node3->Text = IntToStr(myobj->X);
        node3 = node2->AddChild("Y");
        node3->Text = IntToStr(myobj->Y);
        node3 = node2->AddChild("TriggerRange");
        node3->Text = AnsiString(myobj->m_fEffectDis);
        node3 = node2->AddChild("SensorType");
        node3->Text =AnsiString(myobj->m_iType);

       /*//***********By WYP at 20140319*********************************
        myobj->GetCoveredNodes();               //******获得节点myobj的覆盖范围列表***
        node3 = node2->AddChild("CoveredList");
        if(myobj->m_pCoveredList->Count==0)    //如果没有可覆盖的节点
                node3->Text=IntToStr("NULL");
        else
        {
                for(int j=0;j<myobj->m_pCoveredList->Count;j++)
                {
                        FCMsNode* obj=(FCMsNode*)myobj->m_pCoveredList->Items[j];
                        node3->Text=obj->m_strName;
                }
        }
        //************************************************************** */


        //***********By WYP at 20140321*****20140323****************************
        myobj->GetCoveredNodes();               //******获得节点myobj的覆盖范围列表***
        node3 = node2->AddChild("CoveredList");
        if(myobj->m_pCoveredList->Count==0)    //如果没有可覆盖的节点
                node3->Text="NULL";
        /*else
        {
                for(int j=0;j<myobj->m_pCoveredList->Count;j++)
                {
                        node4=node3->AddChild("s_list");
                        FCMsNode* obj=(FCMsNode*)myobj->m_pCoveredList->Items[j];
                        node4->Text=obj->m_strName;

                }
        }*/
        else
        {
               FCMsNode* obj=(FCMsNode*)myobj->m_pCoveredList->Items[0];
               node3->Text=obj->m_strName;
        }
        //**************************************************************
      
        //***********By WYP at 20140318*********************************//添加各节点覆盖范围数量到XML文件中
        node3 = node2->AddChild("CoveredList_Count");
        node3->Text=IntToStr(myobj->m_pCoveredList->Count);
        //node3->Text=IntToStr(myobj->m_Count);
        myobj->m_pCoveredList->Clear();//将节点myobj的覆盖范围列表清空******20140331*******
        //**************************************************************
        //***********By WYP at 20150415**********************************
        node3 = node2->AddChild("SensorPosition");
        node3->Text =AnsiString(myobj->m_iPosition);
        //***************************************************************

        //***********By WYP at 20150526**********************************
        node3 = node2->AddChild("NodeInfluence");
        node3->Text =AnsiString(myobj->m_iInf);
        //***************************************************************
    }
    node1 = XMLDoc->DocumentElement->AddChild("LineList");  //添加线条列表
    for (int i = 0; i < m_pLineEventList->Count; i++)
    {
       LineEvent* myobj = (LineEvent*) m_pLineEventList->Items[i];
       node2 = node1->AddChild("Node");
       node3 = node2->AddChild("ID");
       node3->Text = IntToStr(myobj->ID);
       node3 = node2->AddChild("InID");
       node3->Text = AnsiString(myobj->m_InID);
       node3 = node2->AddChild("OutID");
       node3->Text = AnsiString(myobj->m_OutID);
       if(myobj->m_strName.Length()>0)
       {
         node3 = node2->AddChild("Name");
         node3->Text = AnsiString(myobj->m_strName);
       }
       node3 = node2->AddChild("Effect");
       node3->Text = AnsiString(myobj->m_dDistance);
        if(myobj->points!=NULL&&myobj->points->Count>0)
        {
           node3 = node2->AddChild("Poins");
           for(int i=0;i<myobj->points->Count;i++)
           {
              INFLEXTION*d=(INFLEXTION*)myobj->points->Items[i];
              node4 = node3->AddChild("P");
              node5 = node4->AddChild("X");
              node5->Text = AnsiString(d->p.x);
              node5 = node4->AddChild("Y");
              node5->Text = AnsiString(d->p.y);
           }
        }
    }
   XMLDoc->XML->SaveToFile(fileName);
   XMLDoc->XML->Clear();
   return;
}

long UIProject::LoadFromText(AnsiString fileName)
{
    FILE*f=fopen(fileName.c_str(), "r");
    if(f==NULL)
       return false;
    TCursor Save_Cursor = Screen->Cursor;
    Screen->Cursor = crHourGlass;    // Show hourglass cursor
    try{
        char strTmp[512];
        AnsiString course,effect,oper;
        while(fscanfs(f,strTmp,course,effect,oper)==true)
        {
           FCMsNode*node1=GetNodeEventByName(course);
           if(node1==NULL)
           {
              POINT p;
              p.x=100;
              p.y=100;
              node1=AddFCMsNode(p);
              node1->m_strName=course;
           }
           FCMsNode*node2=GetNodeEventByName(effect);
           if(node2==NULL)
           {
              POINT p;
              p.x=100;
              p.y=100;
              node2=AddFCMsNode(p);
              node2->m_strName=effect;
           }
           LineEvent*link=AddLinkEvent(node1,node2);
           if(link==NULL)
             continue;
           if(oper=="+")
             link->m_dDistance=1;
           else if(oper=="-")
             link->m_dDistance=-1;
        }
        fclose(f);
    }
    catch (Exception &exception)
    {
       if(f!=NULL)
        fclose(f);
       Screen->Cursor = Save_Cursor; // always restore the cursor
       return false;
    }

  	Screen->Cursor = Save_Cursor; // always restore the cursor
    return true;
}
long UIProject::LoadFromXML(AnsiString fileName)
{
      XMLDoc->LoadFromFile(fileName);
      XMLDoc->AsyncLoadState;
      _di_IXMLNodeList nodes= XMLDoc->DocumentElement->ChildNodes;
      _di_IXMLNode node = nodes->First();
      _di_IXMLNodeList nodes2,nodes3,nodes4,nodes5;

      if(node->GetNodeName()==AnsiString("ModelProperty"))
      {
        nodes = node->ChildNodes;

        node = nodes->FindNode("ModelName");
        if(node->GetIsTextElement())
           m_strProjectName =  node->GetNodeValue();
   /////////////////////////////////////////////////////////////
        node = nodes->FindNode("Author");
        if(node->GetIsTextElement())
           m_strProjectAuthor  =  node->GetNodeValue();
     //////////////////////////////////////////////////////////
        node = nodes->FindNode("ModelDiscript");
        if(node->GetIsTextElement())
           m_strProjectDiscription  =  node->GetNodeValue();
      //////////////////////////////////////////////////////////
        node = nodes->FindNode("Lambda");
        if(node!=NULL&&node->GetIsTextElement())
           m_dLambda  =  StrToFloat(node->GetNodeValue());
       /////////////////////////////////////////////////////////////
        node = nodes->FindNode("UnitDistance");
        if(node!=NULL&&node->GetIsTextElement())
           m_dUnitDistance  =  StrToFloat(node->GetNodeValue());
      ////////////////////////////////////////////////////////////////
        node = nodes->FindNode("SamplingTime");
        if(node!=NULL&&node->GetIsTextElement())
           m_dSamplingTime  =  StrToFloat(node->GetNodeValue());
     /////////////////////////////////////////////////////////////////////
        node = nodes->FindNode("SpeedVariance");
        if(node!=NULL&&node->GetIsTextElement())
           m_fAllVariance  =  StrToFloat(node->GetNodeValue());
       //////////////////////////////////////////////////////////////////
        node = nodes->FindNode("WalkingSpeed");
        if(node!=NULL&&node->GetIsTextElement())
           m_dWalkingSpeed  =  StrToFloat(node->GetNodeValue());
       //////////////////////////////////////////////////////////////////
        node = nodes->FindNode("IterationTime");
        if(node!=NULL&&node->GetIsTextElement())
           m_nIteratTime  =  StrToInt(node->GetNodeValue());
       }
       ////////////////////////////////////////////////////////////
        node = nodes->FindNode("XOFF"); //找到X坐标？？？
        if(node!=NULL&&node->GetIsTextElement())
        {
           XOrientation=StrToInt(node->GetNodeValue());
        }
       /////////////////////////////////////////////////////////////////
        node = nodes->FindNode("YOFF");  //找到Y坐标？？？
        if(node!=NULL&&node->GetIsTextElement())
        {
           YOrientation=StrToInt(node->GetNodeValue());
        }
        ////////////////////////////////////////////////////////////////
        node = nodes->FindNode("Prop");
        if(node!=NULL&&node->GetIsTextElement())
        {
           proportion=StrToFloat(node->GetNodeValue());
        }
       ////////////////////////////////////////////////////////////////
        node = nodes->FindNode("LayoutFile");
        if(node!=NULL&&node->GetIsTextElement())
        {
           m_strLayout=(node->GetNodeValue());
        }
        /////////////////////////////////////////////////////////////
        node = nodes->FindNode("NodeUI");     //读取节点的图像显示
        nodes2= node->ChildNodes;

        node = nodes2->FindNode("LineColor");
        if(node!=NULL&&node->GetIsTextElement())
           m_FCMsNodeUI.m_tcLinePenColor  =  StringToColor(node->GetNodeValue());
        ////////////////////////////////////////////////////////////////
        node = nodes2->FindNode("LineWidth");
        if(node!=NULL&&node->GetIsTextElement())
           m_FCMsNodeUI.m_iLinePenWidth  =  StrToInt(node->GetNodeValue());
       ///////////////////////////////////////////////////////////////////
        node = nodes2->FindNode("BrushColor");
        if(node!=NULL&&node->GetIsTextElement())
           m_FCMsNodeUI.m_tcBrushColor  =  StringToColor(node->GetNodeValue());
       //////////////////////////////////////////////////////////////////////
        node = nodes2->FindNode("FontColor");
        if(node!=NULL&&node->GetIsTextElement())
           m_FCMsNodeUI.m_tcFontColor  =  StringToColor(node->GetNodeValue());
        /////////////////////////////////////////////////////////////////////
        node = nodes2->FindNode("FontSize");
        if(node!=NULL&&node->GetIsTextElement())
           m_FCMsNodeUI.m_iFontSize  =  StrToInt(node->GetNodeValue());
        ///////////////////////////////////////////////////////////////
        node = nodes->FindNode("LineUI");
        nodes2= node->ChildNodes;

        node = nodes2->FindNode("LineColor");
        if(node!=NULL&&node->GetIsTextElement())
           m_LineUI.m_tcLinePenColor  =  StringToColor(node->GetNodeValue());
        ///////////////////////////////////////////////////////////////
        node = nodes2->FindNode("LineWidth");
        if(node!=NULL&&node->GetIsTextElement())
           m_LineUI.m_iLinePenWidth  =  StrToInt(node->GetNodeValue());
        //////////////////////////////////////////////////////////////////
        node = nodes2->FindNode("BrushColor");
        if(node!=NULL&&node->GetIsTextElement())
           m_LineUI.m_tcBrushColor  =  StringToColor(node->GetNodeValue());
        /////////////////////////////////////////////////////////////////////
        node = nodes2->FindNode("FontColor");
        if(node!=NULL&&node->GetIsTextElement())
           m_LineUI.m_tcFontColor  =  StringToColor(node->GetNodeValue());
         ///////////////////////////////////////////////////////////////////
        node = nodes2->FindNode("FontSize");
        if(node!=NULL&&node->GetIsTextElement())
           m_LineUI.m_iFontSize  =  StrToInt(node->GetNodeValue());

////////////////////////////////////////

      nodes= XMLDoc->DocumentElement->ChildNodes;
      node = nodes->GetNode(AnsiString("NodesList"));
      nodes = node->ChildNodes;
      for (int i = 0; i < nodes->Count; i++)
      {
        node = nodes->GetNode(i);   //node为获取到第i个节点
        nodes2 = node->ChildNodes;

        AnsiString ID;
        AnsiString Name;
        AnsiString X;
        AnsiString Y;
        AnsiString disc;
        AnsiString Range;
        AnsiString Type;
        //*****By WYP at 20150415******
        AnsiString Position;
        //*****************************

        //******By WYP at 20140315*********
        AnsiString cc_list;                 //节点能覆盖到的范围
        //*********************************

        //******By WYP at 20140318*********
        AnsiString c_count;                 //节点能覆盖到的范围数量
        //*********************************

        //******By WYP at 20140526*********
        AnsiString Influence;                 //节点影响度
        //*********************************


        node = nodes2->FindNode("ID");
        ID =  node->GetNodeValue();
        node = nodes2->FindNode("Name");
        Name = node->GetNodeValue();
        node = nodes2->FindNode("Discription");
        if(node!=NULL&&node->GetIsTextElement())
           disc = node->GetNodeValue();

        node = nodes2->FindNode("X");
        X =  node->GetNodeValue();
        node = nodes2->FindNode("Y");
        Y = node->GetNodeValue();

        node = nodes2->FindNode("TriggerRange");
        Range =  node->GetNodeValue();

        node = nodes2->FindNode("SensorType");
        Type =  node->GetNodeValue();

        //******By WYP at 20140317***********
        node = nodes2->FindNode("CoveredList");
        cc_list=node->GetNodeValue();
        //***********************************

        //******By WYP at 20140318***********
        node = nodes2->FindNode("CoveredList_Count");
        c_count=node->GetNodeValue();
        //***********************************

        //*******By WYP at 20150415****************
        node = nodes2->FindNode("SensorPosition");
        Position =  node->GetNodeValue();
        //*****************************************

        //*******By WYP at 20150526****************
        node = nodes2->FindNode("NodeInfluence");
        Influence =  node->GetNodeValue();
        //*****************************************

        FCMsNode*value=new FCMsNode;
        //******By WYP at 20140319***********
        //value->GetCoveredNodes();
        //***********************************
        value->ID=StrToInt(ID);
        value->X=StrToInt(X);
        value->Y=StrToInt(Y);
        value->m_strName=Name;
        value->m_strDiscrip=disc;
        value->m_fEffectDis=StrToFloat(Range);
        value->m_iType=StrToInt(Type);

        value->c_list=cc_list;


       /* //******By WYP at 20140319***********
        if(value->m_pCoveredList->Count==0)
                value->c_list= StrToInt(cc_list);  //为属性c_list赋值。
        else
        {
                for(int i=0;i<value->m_pCoveredList->Count;i++)
                {
                        FCMsNode* obj=(FCMsNode*)value->m_pCoveredList->Items[i];
                        value->c_list[i]= obj->m_strName;  //为属性c_list[i]赋值。
                }
        }
        //***********************************
        */
        //******By WYP at 20140318***********
        value->m_Count= StrToInt(c_count);  //为属性m_Count赋值。
        //***********************************

        //**********By WYP at 20150415***********
        value->m_iPosition=StrToInt(Position);
        //***************************************

        //**********By WYP at 20150415***********
        value->m_iInf=StrToInt(Influence);
        //***************************************
        
        m_pFCMsNodeList->Add(value);  //将该节点添加到节点列表中。

        //***********By WYP at 20140331****************************************
        //value->m_pCoveredList->Clear();
        //*********************************************************************
        
        m_nMaxRuleSetID = value->ID>m_nMaxRuleSetID?value->ID:m_nMaxRuleSetID;
        m_MaxPoint.x = value->X>m_MaxPoint.x?value->X:m_MaxPoint.x;
        m_MaxPoint.y = value->Y>m_MaxPoint.y?value->Y:m_MaxPoint.y;
        /////////////////
      }
////////////////////////////////////////
     nodes= XMLDoc->DocumentElement->ChildNodes;
      node = nodes->GetNode(AnsiString("LineList"));
      nodes = node->ChildNodes;
      for (int i = 0; i < nodes->Count; i++)
      {
        node = nodes->GetNode(i);
        nodes2 = node->ChildNodes;
        AnsiString ID;
        AnsiString InID;
        AnsiString OutID;
        AnsiString Effect;
        AnsiString Name;

        node = nodes2->FindNode("ID");
        ID = node->GetNodeValue();
        node = nodes2->FindNode("InID");
        InID = node->GetNodeValue();
        node = nodes2->FindNode("OutID");
        OutID =  node->GetNodeValue();
        node = nodes2->FindNode("Name");
        if(node!=NULL&&node->GetIsTextElement())
          Name =  node->GetNodeValue();
        node = nodes2->FindNode("Effect");
        Effect =  node->GetNodeValue();
        LineEvent*c_value=new LineEvent;
        c_value->ID=StrToInt(ID);
        c_value->m_dDistance=StrToFloat(Effect);
        c_value->m_strName=Name;

        m_nMaxLineID = c_value->ID>m_nMaxLineID?c_value->ID:m_nMaxLineID;
        NodeEvent*source=GetNodeEventByID(StrToInt(InID));
        NodeEvent*dest=GetNodeEventByID(StrToInt(OutID));
        AddLinkEvent(source,dest,c_value);

        node = nodes2->FindNode("Poins");
        if(node!=NULL)
        {
            nodes2 = node->ChildNodes;
            for (int j = 0; j < nodes2->Count; j++)
            {
              node = nodes2->GetNode(j);
              nodes3 = node->ChildNodes;
              node = nodes3->FindNode("X");
              POINT p;
              p.x=StrToInt(node->GetNodeValue());
              node = nodes3->FindNode("Y");
              p.y=StrToInt(node->GetNodeValue());
              c_value->CopyNewPoint(p);
           }
        }
        ZoomTo(proportion);
        SetOffsetTo(XOrientation,YOrientation);
    } 
    return 1;

}
long UIProject::ImportModelFromXML(AnsiString fileName)
{
      XMLDoc->LoadFromFile(fileName);
      XMLDoc->AsyncLoadState;
      _di_IXMLNodeList nodes;
      _di_IXMLNode node;
      _di_IXMLNodeList nodes2,nodes3,nodes4,nodes5;
////////////////////////////////////////
      nodes= XMLDoc->DocumentElement->ChildNodes;
      node = nodes->GetNode(AnsiString("NodesList"));
      nodes = node->ChildNodes;
      for (int i = 0; i < nodes->Count; i++)
      {
        node = nodes->GetNode(i);
        nodes2 = node->ChildNodes;
        AnsiString ID;
        AnsiString Name;
        AnsiString X;
        AnsiString Y;
        AnsiString disc;
        AnsiString Initial;
        node = nodes2->FindNode("ID");
        ID =  node->GetNodeValue();
        node = nodes2->FindNode("Name");
        Name = node->GetNodeValue();
        NodeEvent*nodeobj=GetNodeEventByID(StrToInt(ID));
        if(nodeobj==NULL)
        {
          Application->MessageBox("Input Node From Model should be consistent","提示");
          return -1;
        }
        if(nodeobj->m_strName!= Name)
        {
          Application->MessageBox("Input Node From Model should be consistent","Hint");
          return -1;
        }
        /////////////////
      }
/////////////// 
    for (int i = 0; i < m_pLineEventList->Count; i++)
    {
       LineEvent* myobj = (LineEvent*) m_pLineEventList->Items[i];
       myobj->m_dDistance=myobj->m_dDistance/2;
    }
///////////////
////////////////////////////////////////
      nodes= XMLDoc->DocumentElement->ChildNodes;
      node = nodes->GetNode(AnsiString("LineList"));
      nodes = node->ChildNodes;
      long oldlineid= m_nMaxLineID;
      for (int i = 0; i < nodes->Count; i++)
      {
        node = nodes->GetNode(i);
        nodes2 = node->ChildNodes;
        AnsiString ID;
        AnsiString InID;
        AnsiString OutID;
        AnsiString Effect;

        node = nodes2->FindNode("ID");
        ID = node->GetNodeValue();
        node = nodes2->FindNode("InID");
        InID = node->GetNodeValue();
        node = nodes2->FindNode("OutID");
        OutID =  node->GetNodeValue();
        node = nodes2->FindNode("Effect");
        Effect =  node->GetNodeValue();

        NodeEvent*source=GetNodeEventByID(StrToInt(InID));
        NodeEvent*dest=GetNodeEventByID(StrToInt(OutID));
        LineEvent*objp=GetLineEventBetweenNodes(source,dest);
        if(objp!=NULL)
        {
           double t=StrToFloat(Effect)/2.0;
           objp->m_dDistance=objp->m_dDistance+t;
           continue;
        }
        LineEvent*c_value=new LineEvent;
        c_value->ID=StrToInt(ID)+oldlineid;
        c_value->m_dDistance=StrToFloat(Effect)/2.0;
        m_nMaxLineID = c_value->ID>m_nMaxLineID?c_value->ID:m_nMaxLineID;
        AddLinkEvent(source,dest,c_value);

        node = nodes2->FindNode("Poins");
        if(node!=NULL)
        {
            nodes2 = node->ChildNodes;
            for (int j = 0; j < nodes2->Count; j++)
            {
              node = nodes2->GetNode(j);
              nodes3 = node->ChildNodes;
              node = nodes3->FindNode("X");
              POINT p;
              p.x=StrToInt(node->GetNodeValue());
              node = nodes3->FindNode("Y");
              p.y=StrToInt(node->GetNodeValue());
              c_value->CopyNewPoint(p);
           }
        }
/////////////////
      }
}


