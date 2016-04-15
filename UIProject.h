
#ifndef UIProjectH
#define UIProjectH
#include <vcl.h>
#include "projectModel.h"
//#include "DBEngine.h"

class UIProject:public ProjectModel
{
	public:

		double proportion;
    long  XOrientation;
    long  YOrientation;
		TList* m_pSelectedList; //
		TList* m_pCopybufferList; //
		TList* m_pCopiedNodeList; //
                TList*m_pUserHistory;
    Boolean m_bModified;
    TColor m_cBackGround;

    NodeEvent*DrawLine_Start;
    NodeEvent*DrawLine_End;
    AnsiString m_strFileName;
    POINT m_MaxPoint;
    int m_dSimulateTime;
    int stay;
    int estay;
    FCMsNode*ls;
    FCMsNode*ns;
    bool flag;
    int count;
double m_dLambda;
double m_dUnitDistance;
double m_dSamplingTime;
double m_dWalkingSpeed;
double m_fAllVariance;
AnsiString m_strLayout;
long m_nIteratTime;
    int m_nWorkType;
	public:
		UIProject();
		virtual __fastcall ~UIProject();

		void Draw (TCanvas* m_canvas);
    void ReDrawSelectObj(long x_1,long y_1,TCanvas*m_canvas);
    void DrawLinkedEvent(TCanvas*m_canvas,NodeEvent*myobj,TPenMode m_mode);

		Boolean IsSelect (TRect rect);
		BasicGraph*IsSelect (POINT p,TShiftState Shift);

		void ObjectSelected (FCMsNode*rulenode,NodeEvent*myobj=NULL);

    BasicGraph*SelectTest (POINT p);

    void SetSelectedMouseD(POINT p);

		void ZoomTo (double p);
		void ZoomIn ();
		void ZoomOut ();

    void SetOffset(long x0,long y0);
    void SetOffsetTo(long x0,long y0);
    

    POINT ScreenToReal(long dx,long dy);
    void FitToWindow(long w_h,long w_w);

		void UnSelectAll ();
    void SelectAll ();

    FCMsNode*GetNodeEventByID(long id);
    FCMsNode*GetNodeEventByName(AnsiString str);
    LineEvent*GetLineEventByID(long id);


    FCMsNode* AddFCMsNode(POINT p);
    LineEvent* AddLinkEvent(NodeEvent*source,NodeEvent*dest);
    void AddLinkEvent(NodeEvent*source,NodeEvent*dest,LineEvent*myobj);
    void AddLink_coveredEvent(NodeEvent*n1,NodeEvent*n2);//若两个节点是相互覆盖的关系，则认为两个节点之间相互关联
    ///
    Boolean DeleSelected();
    Boolean DeleFCMsNode(FCMsNode*node);
    Boolean DeleLineEvent(LineEvent*node);

    Boolean SortSelected();
    Boolean PrepareCopy();
    Boolean CopySelected();
    FCMsNode* CopyFCMsNode(FCMsNode*myobj);
    LineEvent* CopyLineEvent(LineEvent*myobj,TList*list);

    Boolean IsSelectFCMsNode();
    Boolean IsSelectLineEvent();
    int FindSensor(TList*pList,FCMsNode* pFind);
    TList* FindDifferentSensors(TList*pList1,TList*pList2);
    LineEvent* GetLineEventBetweenNodes(NodeEvent*s,NodeEvent*d);
    void CheckValid();
    void Simulate();
    void Simulate2();//fixed user
    void GetAllMarkSensors(TList*pList);    
    double U_Rand( double a,double b );
    double P_Rand( double Lamda );
    double grandn(const double Mean, const double SquareMargin);
    void ClearHistory();
    void SaveHistory(AnsiString strName);
    void SaveHistory2(AnsiString strName);
    void SaveUserHistory(AnsiString strName);
    void SaveUserHistory2(AnsiString strName);
    int NextStep(WalkingUser*user,int simtime);
    int NextStep2(WalkingUser*user,int simtime);
    int NodeTrigger(TList*myUserList,FCMsNode*myNode,int simtime);
    int Detect(WalkingUser*user,FCMsNode*pNode,int simtime);
    void GetNoConnectedNodes(FCMsNode*pNode,TList*list);
    //***********By WYP at 20150525*********************
    double Similarity(TList* list1,TList* list2);//计算两轨迹间的相似度
    //**************************************************
public:
    void SaveToXML(AnsiString fileName);  //***************************
    long LoadFromXML(AnsiString fileName);     //***************************
    long LoadFromText(AnsiString fileName);
    long ImportModelFromXML(AnsiString fileName);

    void GetOtherOutPutList(TList*list,FCMsNode*node=NULL);
    void ToLeft(TCanvas* m_canvas);//
    void ToRight(TCanvas* m_canvas);//
    void ToTop(TCanvas* m_canvas);//
    void ToBottom(TCanvas* m_canvas);//

    bool m_iSwitch;//
    bool m_bSQL;//
    
};

#endif
