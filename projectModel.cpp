
#include "ProjectModel.h"

ProjectModel::ProjectModel()
{
	m_pFCMsNodeList=new TList;
	m_pLineEventList=new TList;
}

__fastcall ProjectModel::~ProjectModel()
{
        ClearNodeList();
	delete m_pFCMsNodeList;
	delete m_pLineEventList;
}
void ProjectModel::ClearNodeList()
{
  for(int i = 0;i<m_pFCMsNodeList->Count;i++)
   {
      FCMsNode*myobj = (FCMsNode*)m_pFCMsNodeList->Items[i];
      //******************By WYP at 20140331****************************
      myobj->m_pCoveredList->Clear();   //���ڵ�myobj�ĸ��Ƿ�Χ�б����
      //****************************************************************
      delete myobj;
   }
   m_pFCMsNodeList->Clear();
   for(int i = 0;i<m_pLineEventList->Count;i++)
   {
      LineEvent*myobj = (LineEvent*)m_pLineEventList->Items[i];
      delete myobj;
   }
   m_pLineEventList->Clear();
}


