
#include "LineEvent.h"
class WalkingUser:public TObject
{
	public:
                int m_iNum;
                TList* route;
		float m_fMeanSpeed;
		float m_fVariance;
                float m_fSpeed;
                float X;
                float Y;
                int m_iBegin;
                int m_iEnd;
                float sx;
                float sy;
                float dx;
                float dy;
                FCMsNode*m_pLastSensor;
                FCMsNode*m_pNextSensor;
                FCMsNode*waitedSensor;
                TList*m_pPathList;
                LineEvent*m_pLine;
                int m_iPoint;
                String str;
                int num;
                int m_iDirection;//1:increase the points index;-1:decrease the points index
	public:
		WalkingUser(){m_pPathList=new TList;m_pLastSensor=NULL;m_pNextSensor=NULL;m_pLine=NULL;m_iPoint=-1;};
                __fastcall ~WalkingUser();
                void Walk(FCMsNode*pLast,FCMsNode*pNext);
                void InitialSpeed();
};