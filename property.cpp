//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "dxCntner"
#pragma link "dxDBInsp"
#pragma link "dxExEdtr"
#pragma link "dxInspct"
#pragma link "dxInspRw"
#pragma resource "*.dfm"

#include "property.h"
#include "MainFrame.h"
extern UIProject*g_pProject;

TFrameProperty *FrameProperty;
//---------------------------------------------------------------------------
__fastcall TFrameProperty::TFrameProperty(TComponent* Owner)
				: TFrame(Owner)
{
	m_pSelectedList=new TList;
}
//---------------------------------------------------------------------------

void TFrameProperty::RefreshProjectTree()
{
	TreeViewProject->Items->Clear();
	TTreeNode *pNodeLevel0,*pNodeLevel1,*pNodeLevel2,*pNodeLevel3,*pNodeLevel4;
	pNodeLevel0=this->TreeViewProject->Items->AddObject(NULL,"Project Model",g_pProject);
	pNodeLevel0->ImageIndex=1;
	pNodeLevel1=TreeViewProject->Items->AddChild(pNodeLevel0,"Sensors");
	pNodeLevel1->ImageIndex=6;
	TList* pFCMsNodeList=g_pProject->m_pFCMsNodeList;
	for(int i=0;i<pFCMsNodeList->Count;i++)
	{
		FCMsNode *pRulesetNode=(FCMsNode*) (pFCMsNodeList->Items[i]);
		String strNodeName=pRulesetNode->m_strName;
		pNodeLevel2=TreeViewProject->Items->AddChild(pNodeLevel1,strNodeName);
		pNodeLevel2->ImageIndex=7;
		pNodeLevel2->Data=pRulesetNode;

	}
	HideAllProperty();
}
void __fastcall TFrameProperty::TreeViewProjectClick(TObject *Sender)
{
	g_pProject->UnSelectAll();
	RefreshProperty();

}
//---------------------------------------------------------------------------


void TFrameProperty::RefreshProperty()
{
	m_pSelectedList->Clear();
	if( g_pProject->m_pSelectedList->Count>0)  //如果已经有被选中的节点，则将已被选中的节点添加到m_pSelectedList中。
	{
		for(int i=0;i<g_pProject->m_pSelectedList->Count;i++)
		{
			m_pSelectedList->Add(g_pProject->m_pSelectedList->Items[i]);
		}
	}
	else //如果没有被选中的节点，则选中一个节点并添加。
	{
		for(int i=0;i<TreeViewProject->SelectionCount;i++)
		{
			TTreeNode* pNode=TreeViewProject->Selections[i];
			if(pNode->Data!=NULL)
				m_pSelectedList->Add(pNode->Data);
		}
	}

	dxInspector->BeginUpdate();
	HideAllProperty();

	if (m_pSelectedList->Count==0)
	{
		dxInspector->EndUpdate();
		return;
	}
	else	ShowAllProperty();

	if(m_pSelectedList->Count>1)
	{

		rowCommonName->Visible=false;
	}
	TStringList *pRowNames=new TStringList; //pRowNames是字符串列表对象
	for (int i=0;i<m_pSelectedList->Count;i++)
	{
		TObject *pItem=(TObject*)m_pSelectedList->Items[i];
		String strClassName=pItem->ClassName();

	//Hide something
		if(strClassName=="UIProject")    //在用户界面上添加文本框
		{
			pRowNames->Clear();
//			pRowNames->Add("rowCommonName");
			pRowNames->Add("rowCommonDescription");
			pRowNames->Add("rowProjectAuthor");
			pRowNames->Add("rowIteratTime");
			pRowNames->Add("rowUnitDistance");
			pRowNames->Add("rowSamplingTime");
			pRowNames->Add("rowWalkingSpeed");
			pRowNames->Add("rowVariance");
			pRowNames->Add("rowLambda");
			this->HideRowsNotInNames(pRowNames);

			UIProject*pObj=(UIProject*)pItem;   //对文本框中要显示的内容进行编辑。
			rowCommonName->Text=pObj->m_strProjectName;
			rowCommonDescription->Text=pObj->m_strProjectDiscription;
			rowProjectAuthor->Text=pObj->m_strProjectAuthor;
                        rowIteratTime->Text=AnsiString(pObj->m_nIteratTime);
                        rowUnitDistance->Text=AnsiString(pObj->m_dUnitDistance);
                        rowSamplingTime->Text=AnsiString(pObj->m_dSamplingTime);
                        rowWalkingSpeed->Text=AnsiString(pObj->m_dWalkingSpeed);
                        rowVariance->Text=AnsiString(pObj->m_fAllVariance);
                        rowLambda->Text=AnsiString(pObj->m_dLambda);
                }
		else if(strClassName=="LineEvent")     //关于连线的界面显示，添加属性文本框。
		{
			pRowNames->Clear();
			pRowNames->Add("rowCommonName");
			pRowNames->Add("rowUILineColor");
			pRowNames->Add("rowUILineWidth");
			pRowNames->Add("rowDistance");
			this->HideRowsNotInNames(pRowNames);

			LineEvent* pObj=(LineEvent*)pItem;
                        rowDistance->Text=AnsiString(pObj->m_dDistance);
			rowCommonName->Text=pObj->m_strName;
			SetUIProperty(m_LineUI);
		}
		else if(strClassName=="FCMsNode")  //关于节点的界面显示，添加属性文本框。
		{
			pRowNames->Clear();
			pRowNames->Add("rowCommonName");
			pRowNames->Add("rowCommonDescription");
			pRowNames->Add("rowUIBrushColor");
			pRowNames->Add("rowUIFontSize");
			pRowNames->Add("rowUIFontColor");
			pRowNames->Add("rowUILineColor");
			pRowNames->Add("rowUILineWidth");
			pRowNames->Add("dxrowSensorType");
			pRowNames->Add("rowTriggerRange");
                        //pRowNames->Add("dxInspectorRow25");

                        //***By WYP at 20140312*******
                        pRowNames->Add("dxrowCoverList");  //添加节点覆盖范围的列表。
                        //*****************************

                        //***By WYP at 20140318****************
                        pRowNames->Add("rowCoveredList_Count");
                        //*************************************

                        //***By WYP at 20150415****************
                        pRowNames->Add("dxrowPosition");
                        //*************************************

                        //***By WYP at 20150526****************
                        pRowNames->Add("rowInfluence");
                        //*************************************

			this->HideRowsNotInNames(pRowNames);

			FCMsNode* pObj=(FCMsNode*)pItem;
                        //pObj->GetCoveredNodes();           //获取节点pObj的覆盖范围列表
			rowCommonName->Text=pObj->m_strName;
			rowCommonDescription->Text=pObj->m_strDiscrip;
                        rowTriggerRange->Text=AnsiString(pObj->m_fEffectDis);
			//rowTriggerRange->Text=AnsiString(pObj->m_fEffectDis);

                         //***By WYP at 20140312***********************
                        dxrowCoverList->Text=pObj->c_list; //在覆盖范围文本框中显示覆盖数量。
                        //*********************************************

                        //***By WYP at 20140321*****20140324******************
                        /*for(int j=0;j<pObj->m_pCoveredList->Count;j++)
                        {
                                FCMsNode* obj=(FCMsNode*)pObj->m_pCoveredList->Items[j];
                                dxrowCoverList->Text=obj->m_strName;
                        } */
                        //*********************************************

                        //***By WYP at 20140318******************************//在覆盖范围文本框中显示覆盖数量。
                        rowCoveredList_Count->Text=AnsiString(pObj->m_Count);
                        //***************************************************

                        if(pObj->m_iType==1)
                                dxrowSensorType->Text="Sensor in Aisle";
                        else if(pObj->m_iType==2)
                                 dxrowSensorType->Text="Sensor in Room";
                             else
                                 dxrowSensorType->Text="Sensor in Gateway";

                        /*if(pObj->m_iPosition==1)
                                dxrowPosition->Text="Sensor in Aisle";
                        else if(pObj->m_iPosition==2)
                                 dxrowPosition->Text="Sensor in Room";
                             else
                                 dxrowPosition->Text="Sensor in Gateway"; */

                        //***By WYP at 20150415***********************
                       if(pObj->m_iPosition==1)
                                dxrowPosition->Text="washer";
                        else if(pObj->m_iPosition==2)
                                 dxrowPosition->Text="fridge";
                        else if(pObj->m_iPosition==3)
                                 dxrowPosition->Text="piano";
                        else if(pObj->m_iPosition==4)
                                 dxrowPosition->Text="closestool";
                        else if(pObj->m_iPosition==5)
                                 dxrowPosition->Text="TV";
                        else if(pObj->m_iPosition==6)
                                 dxrowPosition->Text="table";
                        else if(pObj->m_iPosition==7)
                                 dxrowPosition->Text="bathtub";
                        else if(pObj->m_iPosition==8)
                                 dxrowPosition->Text="stove";
                        else if(pObj->m_iPosition==9)
                                 dxrowPosition->Text="bed";
                        else if(pObj->m_iPosition==10)
                                 dxrowSensorType->Text="sink";
                        else if(pObj->m_iPosition==11)
                                 dxrowPosition->Text="sofa";
                        else if(pObj->m_iPosition==12)
                                 dxrowPosition->Text="r_aisle";
                        else if(pObj->m_iPosition==13)
                                 dxrowPosition->Text="aisle";
                        else
                            dxrowSensorType->Text="else";
                        //*********************************************

                        //***By WYP at 20150526******************************//显示节点影响度
                        rowInfluence->Text=AnsiString(pObj->m_iInf);
                        //***************************************************
			SetUIProperty(m_FCMsNodeUI);

		}

	}
	dxInspector->EndUpdate();
	delete pRowNames;

}

void TFrameProperty::HideAllProperty()
{
//Hide All

	int nCount=dxInspector->TotalRowCount;
	for(int i=0;i<nCount;i++)
	{
		dxInspector->Rows[i]->Visible=false;
	}
}

void TFrameProperty::ShowRowsByName(TStringList* a_pStringList)  //显示界面列表
{
	int nCount=dxInspector->TotalRowCount;
	for(int i=0;i<nCount;i++)
	{
		TdxInspectorRow* pRow=dxInspector->Rows[i];
		int nIndex;
		if (a_pStringList->Find(pRow->Name,nIndex))
                        pRow->Visible=true;
	}

}

void TFrameProperty::HideRowsNotInNames(TStringList* a_pStringList)
{
	int nCount=dxInspector->TotalRowCount;
	a_pStringList->Sort();
	for(int i=0;i<nCount;i++)
	{
		TdxInspectorRow* pRow=dxInspector->Rows[i];
		int nIndex;
		if (!a_pStringList->Find(pRow->Name,nIndex))
		{
			pRow->Visible=false;
		}
	}
}

void TFrameProperty::ShowAllProperty() //显示所有的属性。
{
//show All
/*
	int nCount=dxInspector->TotalRowCount;
	for(int i=0;i<nCount;i++)
	{
		dxInspector->Rows[i]->Visible=true;
	}*/
			rowCommonName->Visible=true;
			rowCommonDescription->Visible=true;

			rowUIBrushColor->Visible=true;
			rowUIFontSize->Visible=true;
			rowUIFontColor->Visible=true;
			rowUILineColor->Visible=true;
			rowUILineWidth->Visible=true;
			rowProjectAuthor->Visible=true;
                        rowIteratTime->Visible=true;
                        rowSamplingTime->Visible=true;
                        dxrowSensorType->Visible=true;

                        //***By WYP at 20140312********
                        dxrowCoverList->Visible=true;
                        //*****************************

                        //***By WYP at 20140318************
                        rowCoveredList_Count->Visible=true;
                        //*********************************

                        rowWalkingSpeed->Visible=true;
			rowUnitDistance->Visible=true;
			rowLambda->Visible=true;
			rowDistance->Visible=true;
                        dxrowSensorType->Visible=true;

                        //******By WYP at 20140312********
                        dxrowCoverList->Visible=true;
                        //********************************

                        //******By WYP at 20140318********
                        rowCoveredList_Count->Visible=true;
                        //********************************

			rowTriggerRange->Visible=true;
			rowVariance->Visible=true;

                        //********By WYP at 20150415********
                        dxrowPosition->Visible=true;
                        //**********************************

                        //********By WYP at 20150527********
                        rowInfluence->Visible=true;
                        //**********************************
}

TTreeNode* TFrameProperty::FindNodeByData(void* pObj)
{
	TTreeNodes* pNodes=TreeViewProject->Items;
	TTreeNode* pNode;
	for(int i=0;i<pNodes->Count;i++)
	{
		pNode=pNodes->Item[i];
		if(pNode->Data==pObj)
                        return pNode;
	}
	return NULL;
}

void __fastcall TFrameProperty::dxInspectorEdited(TObject *Sender,
			TdxInspectorNode *Node, TdxInspectorRow *Row)
{
	OnPropertyChange(Row);
}
//---------------------------------------------------------------------------



void TFrameProperty::ChangeTreeNodeText(TObject* a_pObj, String a_strNewText)
{
	TTreeNode* pTreeNode=this->FindNodeByData(a_pObj);
	if(pTreeNode!=NULL)	pTreeNode->Text=a_strNewText;
}
void __fastcall TFrameProperty::rowUIBrushColorButtonClick(TObject *Sender,
			int AbsoluteIndex)
{
	ColorDialog->Color=TColor(atoi(rowUIBrushColor->Text.c_str()));
	if (ColorDialog->Execute())
	{
		rowUIBrushColor->Text=String(ColorDialog->Color);
                m_FCMsNodeUI.m_tcBrushColor=ColorDialog->Color;
		OnPropertyChange(rowUIBrushColor);
	}

}
//---------------------------------------------------------------------------

void __fastcall TFrameProperty::rowUILineColorButtonClick(TObject *Sender,
			int AbsoluteIndex)
{
	ColorDialog->Color=TColor(atoi(rowUILineColor->Text.c_str()));
	if (ColorDialog->Execute())
	{
		rowUILineColor->Text=String(ColorDialog->Color);
		OnPropertyChange(rowUILineColor);
	}

}
//---------------------------------------------------------------------------

void __fastcall TFrameProperty::rowUIFontColorButtonClick(TObject *Sender,
			int AbsoluteIndex)
{
	ColorDialog->Color=TColor(atoi(rowUIBrushColor->Text.c_str()));
	if (ColorDialog->Execute())
	{
		rowUIFontColor->Text=String(ColorDialog->Color);
		OnPropertyChange(rowUIFontColor);
	}
}
//---------------------------------------------------------------------------


void TFrameProperty::SetUIFromProperty(UI &a_UI, TdxInspectorRow * Row)
{

	if(Row->Name=="rowUIBrushColor")
	{
		int i=atoi(rowUIBrushColor->Text.c_str());
		a_UI.m_tcBrushColor=(TColor)(i);
	}
	else if(Row->Name=="rowUILineColor")
	{
		int i=atoi(rowUILineColor->Text.c_str());
		a_UI.m_tcLinePenColor=(TColor)(i);
	}
	else if(Row->Name=="rowUIFontColor")
	{
		int i=atoi(rowUIFontColor->Text.c_str());
		a_UI.m_tcFontColor=(TColor)(i);
	}
	else if(Row->Name=="rowUILineWidth")
		a_UI.m_iLinePenWidth=atoi(rowUILineWidth->Text.c_str());
	else if(Row->Name=="rowUIFontSize")
		a_UI.m_iFontSize=atoi(rowUIFontSize->Text.c_str());
}

void TFrameProperty::SetUIProperty(UI a_UI)  //设置用户界面属性
{
	rowUIBrushColor->Text=String(a_UI.m_tcBrushColor);
	rowUIFontColor->Text=String(a_UI.m_tcFontColor);
	rowUIFontSize->Text=String(a_UI.m_iFontSize);
	rowUILineColor->Text=String(a_UI.m_tcLinePenColor);
	rowUILineWidth->Text=String(a_UI.m_iLinePenWidth);
}
bool ValidateNameProperty(String a_strName, TObject* a_pObj)
{

//check whether the name is used by another
	String strClassName=a_pObj->ClassName();
	if (strClassName=="FCMsNode")
	{

		if(IsNameInList(a_strName,(BasicGraph*)a_pObj,g_pProject->m_pFCMsNodeList))
		{
			String msg="Name'"+a_strName+"'cannot exsit,rename please！";
			MessageBox(NULL,msg.c_str(),"Hint",MB_OK+MB_ICONEXCLAMATION);
			return false;
		}
	}

	return true;
}
void TFrameProperty::DeleteSelectedFromTree()
{
	TList* pList=g_pProject->m_pSelectedList;
	for(int i=0;i<pList->Count;i++)
	{
		TTreeNode* pNode=this->FindNodeByData(pList->Items[i]);
		if (pNode==NULL)
                        continue;
		else
                        pNode->Delete();

	}
}

void TFrameProperty::AddSelectedToTree()
{
	TList* pList=g_pProject->m_pSelectedList;
	TTreeNode* pTreeNode;
	for(int i=0;i<pList->Count;i++)
	{
		TObject* pObj=(TObject*)pList->Items[i];
		String strClassName=pObj->ClassName();
		if(strClassName=="FCMsNode")
		{
			pTreeNode=TreeViewProject->Items->GetFirstNode();//get rrot node
			if (pTreeNode==NULL) continue;
			pTreeNode=pTreeNode->GetLastChild();//
			if (pTreeNode==NULL) continue;

			FCMsNode *pRulesetNode=(FCMsNode*) pObj;
			String strNodeName=pRulesetNode->m_strName;
			pTreeNode=TreeViewProject->Items->AddChild(pTreeNode,strNodeName);
			pTreeNode->ImageIndex=7;
			pTreeNode->Data=pObj;
		}
	}
	if(pTreeNode!=NULL) pTreeNode->Selected=true;
}



//---------------------------------------------------------------------------
void __fastcall TFrameProperty::rowUILineWidthChange(TObject *Sender)
{
	dxInspector->PostEditor();

}
//---------------------------------------------------------------------------

__fastcall TFrameProperty::~TFrameProperty()
{
	delete m_pSelectedList;
}

void TFrameProperty::OnPropertyChange(TdxInspectorRow* Row)
{
	if (m_pSelectedList->Count==0) return;
	for (int i=0;i<m_pSelectedList->Count;i++)
	{

		TObject *pItem=(TObject*)(m_pSelectedList->Items[i]);
		String strClassName=pItem->ClassName();

		if(strClassName=="UIProject")
		{
			UIProject*pObj=(UIProject*)pItem;
			if (Row->Name=="rowCommonName")
			{
				String strName=rowCommonName->Text;
				if(ValidateNameProperty(strName, pItem))
				{
					pObj->m_strProjectName=strName;
					this->ChangeTreeNodeText(pItem,strName);
				}
				else
				{
					dxInspector->SetFocus();
					rowCommonName->Node->Focused=true;
				}
			}
			else if (Row->Name=="rowCommonDescription")
			{
				String str=rowCommonDescription->Text;
				pObj->m_strProjectDiscription=str;
			}
			else if (Row->Name=="rowSamplingTime")
			{
				float tmp;
				try
				{
					tmp=StrToFloat( rowSamplingTime->Text);
				}
				catch(...)
				{
					MessageBox(NULL,"Value is wrong, reinput please!","Hint",MB_OK+MB_ICONEXCLAMATION);
					dxInspector->SetFocus();
					rowSamplingTime->Node->Focused=true;
				return;
				}
                                 if(tmp<0||tmp>1)
                                {
   					MessageBox(NULL,"Value is wrong,reinput please!","Hint",MB_OK+MB_ICONEXCLAMATION);
  					dxInspector->SetFocus();
  					rowSamplingTime->Node->Focused=true;
                                        return;
                                }
                                 pObj->m_dSamplingTime=StrToFloat(rowSamplingTime->Text);
			}
			else if (Row->Name=="rowWalkingSpeed")
			{
                                float tmp;
				try
				{
					tmp=StrToFloat( rowWalkingSpeed->Text);
				}
				catch(...)
				{
					MessageBox(NULL,"Value is wrong,reinput please!!","Hint",MB_OK+MB_ICONEXCLAMATION);
					dxInspector->SetFocus();
					rowWalkingSpeed->Node->Focused=true;
                                        return;
				}
                                if(tmp<0)
                                {
   					MessageBox(NULL,"Value is wrong,reinput please!","Hint",MB_OK+MB_ICONEXCLAMATION);
  					dxInspector->SetFocus();
  					rowWalkingSpeed->Node->Focused=true;
                                        return;
                                }
                                pObj->m_dWalkingSpeed=StrToFloat(rowWalkingSpeed->Text);
			}
			else if (Row->Name=="rowProjectAuthor")
				pObj->m_strProjectAuthor=rowProjectAuthor->Text;
			else if (Row->Name=="rowIteratTime")
				pObj->m_nIteratTime=StrToInt(rowIteratTime->Text);
			else if (Row->Name=="rowUnitDistance")
				pObj->m_dUnitDistance=StrToFloat(rowUnitDistance->Text);
			else if (Row->Name=="rowLambda")
				pObj->m_dLambda=StrToFloat(rowLambda->Text);
			else if (Row->Name=="rowSamplingTime")
				pObj->m_dSamplingTime=StrToFloat(rowSamplingTime->Text);
			else if (Row->Name=="rowWalkingSpeed")
				pObj->m_dWalkingSpeed=StrToFloat(rowWalkingSpeed->Text);
			else if (Row->Name=="rowVariance")
				pObj->m_fAllVariance=StrToFloat(rowVariance->Text);

		}
		else if(strClassName=="FCMsNode")
		{
			FCMsNode* pNode=(FCMsNode*)pItem;
			if(Row->Name=="rowCommonName")
			{
				String strName=rowCommonName->Text;
				if(ValidateNameProperty(strName, pItem))
				{
                                        pNode->m_strName=strName;
					this->ChangeTreeNodeText(pItem,strName);
				}
				else
				{
					dxInspector->SetFocus();
					rowCommonName->Node->Focused=true;
				}
			}
			else if (Row->Name=="rowCommonDescription")
				pNode->m_strDiscrip=rowCommonDescription->Text;
			else if(Row->Name=="rowTriggerRange")
			{
				try
				{
					pNode->m_fEffectDis=StrToFloat( rowTriggerRange->Text);
				}
				catch(...)
				{
					MessageBox(NULL,"Value is wrong,reinput please!!","Hint",MB_OK+MB_ICONEXCLAMATION);
					dxInspector->SetFocus();
					rowTriggerRange->Node->Focused=true;
				}
			}
                        else if (Row->Name=="dxrowSensorType")
                        {
                         if(dxrowSensorType->Text=="Sensor in Aisle")
                           pNode->m_iType=1;
                         else if(dxrowSensorType->Text=="Sensor in Room")
                           pNode->m_iType=2;
                         else
                           pNode->m_iType=3;
                        }


                       /* else if (Row->Name=="dxrowPosition")
                        {
                         if(dxrowPosition->Text=="Sensor in Aisle")
                           pNode->m_iPosition=1;
                         else if(dxrowPosition->Text=="Sensor in Room")
                           pNode->m_iPosition=2;
                         else
                           pNode->m_iPosition=3;
                        }    */
                        else if(Row->Name=="dxrowPosition")
                        {
                              if(dxrowPosition->Text=="washer")
                                    pNode->m_iPosition=1;
                              else if(dxrowPosition->Text=="fridge")
                                    pNode->m_iPosition=2;
                              else if(dxrowPosition->Text=="piano")
                                    pNode->m_iPosition=3;
                              else if(dxrowPosition->Text=="closestool")
                                    pNode->m_iPosition=4;
                              else if(dxrowPosition->Text=="TV")
                                    pNode->m_iPosition=5;
                              else if(dxrowPosition->Text=="table")
                                    pNode->m_iPosition=6;
                              else if(dxrowPosition->Text=="bathtub")
                                    pNode->m_iPosition=7;
                              else if(dxrowPosition->Text=="stove")
                                   pNode->m_iPosition=8;
                              else if(dxrowPosition->Text=="bed")
                                   pNode->m_iPosition=9;
                              else if(dxrowSensorType->Text=="sink")
                                   pNode->m_iPosition=10;
                              else if(dxrowPosition->Text=="sofa")
                                   pNode->m_iPosition=11;
                              else if(dxrowPosition->Text=="r_aisle")
                                   pNode->m_iPosition=12;
                              else if(dxrowPosition->Text=="aisle")
                                   pNode->m_iPosition=13;
                              else
                                   pNode->m_iPosition=14;
                        }
                        //****************By WYP at 20140316****************
                        else if (Row->Name=="dxrowCoverList")
                               pNode->c_list=dxrowCoverList->Text;
                        //**************************************************

                        //****************By WYP at 20140318***********************
                        else if (Row->Name=="rowCoveredList_Count")
                               pNode->m_Count=StrToInt(rowCoveredList_Count->Text);
                        //*********************************************************

                        //****************By WYP at 20150528***********************
                        else if (Row->Name=="rowInfluence")
                        {
                              pNode->m_iInf=StrToInt(rowInfluence->Text);
                        }
                        //*********************************************************
		}
		else if(strClassName=="LineEvent")
		{
			LineEvent* pObj=(LineEvent*)pItem;
			if(Row->Name=="rowCommonName")
			{
				String strName=rowCommonName->Text;
				if(ValidateNameProperty(strName, pItem))
				{
                                        pObj->m_strName=strName;
					this->ChangeTreeNodeText(pItem,strName);
				}
				else
				{
					dxInspector->SetFocus();
					rowCommonName->Node->Focused=true;
				}
			}
			else if(Row->Name=="rowDistance")
			{
				try
				{
					pObj->m_dDistance=StrToFloat( rowDistance->Text);
				}
				catch(...)
				{
					MessageBox(NULL,"Value is wrong,reinput please!","Hint",MB_OK+MB_ICONEXCLAMATION);
					dxInspector->SetFocus();
					rowDistance->Node->Focused=true;
				}
			}
			SetUIFromProperty(m_LineUI,Row);
		}
	}
}

void __fastcall TFrameProperty::TreeViewProjectDblClick(TObject *Sender)
{
  TTreeNode* pTreeNode=TreeViewProject->Selected;
  if(pTreeNode==NULL) return;
  TObject* pObj=(TObject*)pTreeNode->Data;
  if(pObj==NULL) return;
  String strClassName=pObj->ClassName();
  if (!(strClassName=="FCMsNode"))
    return;

  frmMainFrame->NodeInCenter((NodeEvent*)pObj);
}
//---------------------------------------------------------------------------


void __fastcall TFrameProperty::dxInspectorEnter(TObject *Sender)
{
	frmMainFrame->m_bEditCanvas=false;

}
//---------------------------------------------------------------------------


void TFrameProperty::ChangeTreeSelectStatus()
{
	TreeViewProject->SetFocus();
	TList* pNodeList=new TList;
	for(int i=0;i<g_pProject->m_pSelectedList->Count;i++)
	{
		TTreeNode* pTreeNode=FindNodeByData(g_pProject->m_pSelectedList->Items[i]);
		if(pTreeNode!=NULL) pNodeList->Add(pTreeNode);
	}
	TreeViewProject->Select(pNodeList);
	delete pNodeList;
}
//---------------------------------------------------------------------------


