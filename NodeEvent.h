
#ifndef BasicGraphH
#define BasicGraphH

#include <vcl.h>
#include <exception>
#include <deque>
#include <string.h>
#include <stdio.h>
#include <vector>

const MAXLINELENGTH=65535;//
const long gbl_ItemSize = 14;
const long gbl_ItemFontSize = 8;
const long gbl_TextDistance = 4;
extern long gbl_view;//
const int HISTCONTENT=1000000;//
extern Boolean CheckType(const Variant& v, Word type);
extern Boolean fscanfs(FILE*f,char*c,AnsiString& course,AnsiString& effect,AnsiString& oper);

extern AnsiString TrimString(AnsiString str,int size);
extern long StrInStringNum(AnsiString& str,AnsiString& strs);
class NodeEvent;
extern int IsConnected(NodeEvent*source,NodeEvent*dest);   //�ж������ڵ��Ƿ�����
extern int IsCovered(NodeEvent*n1,NodeEvent*n2);   //�ж������ڵ��Ƿ��Ǹ��ǹ�ϵ
class BasicGraph;
extern int IsObjInList(BasicGraph*obj,TList*list);
extern Boolean IsNameInList(AnsiString strName,BasicGraph*obj,TList*list);
extern void InitialWork(TList*variableList,Boolean bFather=false);
/*
typedef int (WINAPI * MySetPaserExpress)(char* str);
typedef int (WINAPI * MyCheckPaserExpression)(char* str);
typedef double(WINAPI * MyGetPaserResult)(int&s);
typedef char*(WINAPI * MyGetPaserStrResult)(int&s);
typedef void (WINAPI * MyExpressionVariables)(char* str);
typedef int (WINAPI * MyGetVariableCount)(int left);//left=0
typedef char* (WINAPI * MyGetVariableName)(int i,int left);//left=0
typedef void (WINAPI * MyClearPaserStrResult)();

typedef int (WINAPI * MyInitialPaser)();

extern HINSTANCE	m_hParserDll;
extern MyInitialPaser InitialPaser;
extern MySetPaserExpress SetPaserExpress;
extern MyCheckPaserExpression CheckPaserExpression;
extern MyGetPaserResult GetPaserResult;
extern MyGetPaserStrResult GetPaserStrResult;
extern MyExpressionVariables  ExpressionVariables;
extern MyGetVariableCount GetVariableCount;
extern MyGetVariableName GetVariableName;
extern MyClearPaserStrResult  ClearPaserStrResult;

extern double GetExpressValue(AnsiString& exp,int&s);
extern void SetExpressValue(AnsiString& exp);
extern void ExpressionVariable(AnsiString& exp);
extern AnsiString GetExpressStrValue(AnsiString& exp,int&s);
extern int CheckExpressValid(AnsiString& exp);
*/

extern Graphics::TBitmap *pBitmap;
extern void AddErrorMessage(AnsiString str,TObject* pObj);
extern void ClearErrorMessages();
//changed by jimmy
using namespace std ;
typedef deque<short> HISTORYDATA;//
/////
extern TStringList*     m_VariableStringList;//
enum TDrawingTool{dtFCMsNode,dtLineEvent,dtSelect,dtNothing};

struct UI
{
	TColor m_tcLinePenColor;
	int m_iLinePenWidth;
	TColor m_tcBrushColor;
	TColor m_tcFontColor;
	int m_iFontSize;
};
extern UI m_FCMsNodeUI;
extern UI m_LineUI;
 #include <stdexcept>
  using namespace std;

class RuleBasic:public TObject
{
	public:
		String m_strName;
		String m_strDiscrip;
	public:
		RuleBasic(){;};
		virtual __fastcall ~RuleBasic(){;}
};
class BasicGraph:public RuleBasic
{
	public:
		int ID;
    int OldID;//
		Boolean m_bVisible;
		Boolean m_bSelected;
    double proportion;
    long XOrientation,YOrientation;
    int d0_x;//
    int d0_y;//
    int d1_x;//
    int d1_y;//
  protected:
    Boolean m_bWorking;//
	public:
		BasicGraph();
		virtual __fastcall ~BasicGraph();
    Boolean Resize(double p){
       if (p>0)
       {  proportion = p;
          return true;
       }
       else return false;
    };
    Boolean SetOrientation(long x0,long y0);
    virtual void Draw (TCanvas* m_canvas){return;}
    virtual Boolean IsSelect (POINT p){return m_bSelected;}
    void Select (Boolean bSelect=true){m_bSelected=bSelect;}
    virtual Boolean IsSelect (TRect rect){return m_bSelected;}
    virtual void Simulate(){m_bWorking=false;}
    virtual void SetWorkStatus(){m_bWorking=true;}
};

class NodeEvent:public BasicGraph
{
private:
    int d0_x;//
    int d0_y;//
    int d1_x;//
    int d1_y;//
public:
    TList* m_pConnectedList; //�洢��������
    TList* pFCMsNodeList;
    TList* m_pCoveredList; //�ڵ��ܸ��ǵ��Ľڵ��б�

    //*************By WYP at 20140401********************
    TList* m_pRouteList; //�ڵ��·�ɱ�
    //***************************************************

    //*************By WYP at 20140504********************
    TList* m_pTriggeredList; //�ɸ��ǽڵ�ı���������б�
    //***************************************************

    //*************By WYP at 20140505********************
    TList* m_psimTimeList; //�ɸ��ǽڵ�Ĵ��������б�
    //***************************************************

    //*************By WYP at 20140513********************
    TList* m_pGetMessageList;//������Ϣ����б�
    //***************************************************

    //*************By WYP at 20140522********************
    TList* m_pBrief_RouteList;//�ڵ�����·�ɱ�
    //***************************************************

    //*************By WYP at 20150424********************
    TList* m_pShorestRoute;//�ڵ����·��
    //***************************************************

    //*************By WYP at 20150424********************
    TList* m_pRandRoute;//�ڵ����·��
    TList* m_pBrief_RandRoute;//�ڵ�������·��
    //***************************************************

    //*************By WYP at 20150525********************
    TList* m_pSTE;//�ڵ��·��
    //***************************************************

    Boolean m_bCalculated;
    int X;
    int Y;
    Boolean m_bError;
    //**************By WYP at 20140607********************
    int energy;//��ǰ�ڵ��ʣ������
    //****************************************************
public:
    NodeEvent();
    void ClearListData();
    virtual __fastcall ~NodeEvent();
    virtual void Draw (TCanvas* m_canvas){return;}
    virtual Boolean IsSelect (POINT p){return m_bSelected;}
    virtual Boolean SelectTest (POINT p){return m_bSelected;}
    virtual Boolean IsSelect (TRect rect){return m_bSelected;}
    void GetParentNodes (TList*list);
    void GetChildrenNodes (TList*list);
    void GetConnectedNodes(TList*list);
    void GetCoveredNodes();//�õ�ĳ�ڵ�ĸ����б�

    //*************By WYP at 20140504**********************************
    void InitialTriggeredList();//��ʼ���ڵ�ı���������б�
    //*****************************************************************

    //*************By WYP at 20140505**********************************
    void InitialsimTimeList();//��ʼ���ڵ�Ĵ��������б�
    //*****************************************************************

    //*************By WYP at 20140513**********************************
    void InitialGetMessageList();//��ʼ���ڵ����Ϣ��������б�
    //*****************************************************************
    virtual Boolean CheckValid ();
    void SetMouseDPosition(int m_x,int m_y);
    void SetMouseMPosition(int m_x,int m_y);
    void MoveRelatedMouse(int m_x,int m_y);
    virtual POINT GetPoint(int x,int y){TPoint points; points.x=-1;points.y=-1;return points;};//
    Boolean DropLineEvent(long id);
    //*************By WYP at 20140409**********************************
    Boolean IsInList(TList*list);//�жϵ�ǰ�ڵ��Ƿ����б�list��
    //*****************************************************************

    //*************By WYP at 20140522**********************************
    void GetBriefRouteList();//�õ��������ظ�Ԫ�ص��б�
    int GetLastIndex(TList*list);//�õ�ĳԪ�����б��������ֵ��±�
    //*****************************************************************

    //*************By WYP at 20150424**********************************
    int MinDisNode_Index(TList*list);//�����뵱ǰ�ڵ�����Ľڵ����
    //*****************************************************************

    //*************By WYP at 20150422**********************************
    void GetShorestRoute(NodeEvent*node);//�õ�����ڵ�n�����·��
    //*****************************************************************

    //*************By WYP at 20150424**********************************
    void GetRandRoute(NodeEvent*node);//�õ�����ڵ�n��һ�����·��
    void GetBriefRandRoute();//�õ��������ظ��ڵ��·��
    //*****************************************************************

    //*************By WYP at 20150525**********************************
    void GetSTE(TList*list);
    //*****************************************************************
};
class FCMsNode : public NodeEvent
{
public:
    ///
    int m_iType;//marked sensor
    /////////////
    int m_iPosition;
    //*******By WYP at 20150526*************
    double m_iInf; //�ڵ�Ӱ���
    //**************************************
    short m_dValue;
    int capa;
    HISTORYDATA* m_dqHistoryData;//
    float m_fEffectDis;//
    int m_iCurrentNum;// fro statistic

    //*******By WYP at 20140315*************
    int m_Count; //�ýڵ�ɸ��Ƿ�Χ�Ľڵ�����
    //**************************************

    //*******By WYP at 20140319*************
    String c_list;  //�ýڵ�ɸ��Ƿ�Χ��
    //**************************************
    
    TList* at;
    /////
	public:
    FCMsNode();
		virtual __fastcall ~FCMsNode();
		void Draw (TCanvas* m_canvas);
		Boolean SelectTest (POINT p);
    Boolean IsSelect (POINT p);
		Boolean IsSelect (TRect rect);
    POINT GetPoint(int x,int y);
		Boolean Calculate ();

    void CopyTo(FCMsNode*value);
    Boolean CheckValid ();
    virtual void Simulate();
    void StoreOldData(short data);

};
class NodeRecord : public NodeEvent{
public:
       FCMsNode* node;
       int count;
public:
       NodeRecord();
       virtual __fastcall ~NodeRecord();
};
struct HISNODE//
{
  int iTime;//
  FCMsNode* pNode;//
};
#endif

