//---------------------------------------------------------------------
#pragma hdrstop

#include <vcl.h>
#include <excpt.h>

#include "MainFrame.h"
#include "Simulator.h"
#include <Math.h>
#include "About.h"
#include "Unit.h"
#include "UnitSim.h"
#include "Transfer.h"
#include "CreatPattern.h"
#include "UnitEvac.h"
//---------------------------------------------------------------------
#pragma link "dxBar"
#pragma link "dxBarExtItems"
#pragma link "Property"
#pragma link "property"
#pragma link "Output"
#pragma link "dxCntner"
#pragma link "dxExEdtr"
#pragma link "dxInspct"
#pragma link "property"
#include "RelationShip.h"
#include "Find.h"
//#include "ApplicationManager.h"
#include "ShowResult.h"
#pragma link "dxInspRw"
#pragma resource "*.dfm"
TfrmMainFrame *frmMainFrame;
UIProject*g_pProject;

/*
HINSTANCE	m_hParserDll;
MyInitialPaser InitialPaser;
MySetPaserExpress SetPaserExpress;
MyCheckPaserExpression CheckPaserExpression;
MyGetPaserResult GetPaserResult;
MyGetPaserStrResult GetPaserStrResult;
MyExpressionVariables  ExpressionVariables;
MyGetVariableCount GetVariableCount;
MyGetVariableName GetVariableName;
MyClearPaserStrResult  ClearPaserStrResult;

void ExpressionVariable(AnsiString& exp)
{
    char*str = (char*)malloc(exp.Length()+1);
    strcpy(str,exp.c_str());
    ExpressionVariables(str);
    free(str);
}
void SetExpressValue(AnsiString& exp)
{
    char*str = (char*)malloc(exp.Length()+1);
    strcpy(str,exp.c_str());
    SetPaserExpress(str);
    free(str);
}
double GetExpressValue(AnsiString& exp,int&s)
{
    char*str = (char*)malloc(exp.Length()+1);
    strcpy(str,exp.c_str());
    SetPaserExpress(str);
    double r=GetPaserResult(s);
    free(str);
    return r;
}
AnsiString GetExpressStrValue(AnsiString& exp,int&s)
{
    char*str = (char*)malloc(exp.Length()+1);
    strcpy(str,exp.c_str());
    SetPaserExpress(str);
    char*ss=GetPaserStrResult(s);
    AnsiString r=AnsiString(ss);
   // ClearPaserStrResult();
    free(str);
    return r;
}
int CheckExpressValid(AnsiString& exp)
{
    char*str = (char*)malloc(exp.Length()+1);
    strcpy(str,exp.c_str());
    int r =CheckPaserExpression(str);
    free(str);
    return r;
}  */
void AddErrorMessage(AnsiString str,TObject* pObj)
{
//pObj=NULL: finish check Hint
	if(frmMainFrame->FrameOutput->PageControl->ActivePageIndex!=1)
		frmMainFrame->FrameOutput->PageControl->ActivePageIndex=1;
	TListBox* pListBox=frmMainFrame->FrameOutput->ListBoxError;
	if(pObj!=NULL)
		str="Error" + String(pListBox->Count+1)+":   "+str;
	pListBox->AddItem(str,pObj);
}
void AddSimulatingOutput(AnsiString str,TObject* pObj)
{
//pObj=NULL: finish check Hint

	TListBox* pListBox=frmMainFrame->FrameOutput->ListBoxOutput;
        FCMsNode* f = (FCMsNode*)pObj;
        int node;
        int client;
        String sss = f->m_strName;
        //String ss = str.SubString(2,1);
        String ss = sss.SubString(2,sss.Length()-1);
        String ee = str.SubString(str.Pos("@")+1,str.Length()-str.Pos("@"));
        client = StrToInt(ee);
        node = StrToInt(ss);
	if(pObj!=NULL)
           str="Triggered Sensor:" + String(pListBox->Count+1)+":   "+str;
	pListBox->AddItem(str,pObj);
        pListBox->ItemIndex=pListBox->Items->Count-1;
        String s;
        DateTimeToString(s,"YYYYMMDDHHMMSSSSZZZ",Now());
        String sql = "insert into sensormotion(SensorTime,NodeAddress,SensorSqno) values(";
        sql+=AnsiString(node)+",";
        sql+=AnsiString(node)+",";
        sql+=AnsiString(client)+")";
        TADOConnection* t = frmMainFrame->ADOConnection1;
        t->Open();
        TADOQuery* q = frmMainFrame->ADOQuery1;
        q->SQL->Clear();
        //q->SQL->Add("insert into simu(Time,Node,ClientID) values("+s+","+node+","+client+")");
        q->SQL->Add(sql);
        //q->SQL->Add("insert into sensormotion(SensorTime,NodeAddress,SensorSqno) values(:SensorTime,:NodeAddress,:SensorSqno)");
        //q->Parameters->ParamByName("SensorTime")->Value=node;
        //q->Parameters->ParamByName("NodeAddress")->Value=node;
        //q->Parameters->ParamByName("SensorSqno")->Value=client;
        q->ExecSQL();
        //q->Close();
}
void ClearSimulatingOutput()
{
	frmMainFrame->FrameOutput->ListBoxOutput->Clear();
}

void ClearErrorMessages()
{
	frmMainFrame->FrameOutput->ListBoxError->Clear();
}

void AddSearchResult(AnsiString str,TObject* pObj)
{
//pObj=NULL:“finish finding”Hint
	if(frmMainFrame->FrameOutput->PageControl->ActivePageIndex!=2)
		frmMainFrame->FrameOutput->PageControl->ActivePageIndex=2;
	TListBox* pListBox=frmMainFrame->FrameOutput->ListBoxSearch;
	if(pObj!=NULL)
		str="Finding results" + String(pListBox->Count+1)+":   "+str;
	pListBox->AddItem(str,pObj);
}

void ClearSearchResult()
{
	frmMainFrame->FrameOutput->ListBoxSearch->Clear();
}

void AddSelectedToTree()
{
	frmMainFrame->FrameProperty->AddSelectedToTree();

}

void DeleteSelectedFromTree()
{
	frmMainFrame->FrameProperty->DeleteSelectedFromTree();

}
//---------------------------------------------------------------------
__fastcall TfrmMainFrame::TfrmMainFrame(TComponent *AOwner)
	: TForm(AOwner)
{
   this->route1 = new TList;
   this->route2 = new TList;
   this->route3 = new TList;
   this->route4 = new TList;
   //*****By WYP at 20150426******************************
   this->route5=new TList;
   this->route6=new TList;
   this->route7=new TList;
   this->route8=new TList;
   this->route9=new TList;
   //*****************************************************
   this->RouteOfTemp.reserve(9);

   TADOConnection* tado = frmMainFrame->ADOConnection1;
   tado->Open();
   this->fofrtt = true;
   m_pReasonMachine = new ReasonMachine();
   m_pSimulator=NULL;
   graphic=NULL;
   //Form1Exsit = 0;
}
//---------------------------------------------------------------------

void __fastcall TfrmMainFrame::FileNewExecute(TObject *Sender)
{
  // Do nothing
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::FileOpenExecute(TObject *Sender)
{
  OpenDialog->Execute();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::FileSaveExecute(TObject *Sender)
{
  SaveDialog->Execute();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::FileExitExecute(TObject *Sender)
{
  Close();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::MainPaintBoxPaint(TObject *Sender)
{
  Refresh();
}
//---------------------------------------------------------------------------



void __fastcall TfrmMainFrame::AppException(TObject * Sender, Exception * E)
{
  Application->ShowException(E);
//  Application->Terminate();
}
void TfrmMainFrame::InitialProject()
{
   g_pProject=new UIProject;
   g_pProject->DrawingType = dtSelect;
   m_bCopy=false;
   m_bEditCanvas=true;
   this->FrameProperty->RefreshProjectTree();
}
void TfrmMainFrame::ClearProject()
{
   delete g_pProject;
   delete graphic;graphic=NULL;
}
void __fastcall TfrmMainFrame::FormCreate(TObject *Sender)
{
   m_selectRect = new TSelectRect;
   m_VariableStringList=new TStringList;
   bmp = new Graphics::TBitmap();
   PanelPaint->DoubleBuffered=true;

	Application->OnException = AppException;

	FrameProperty->ManualDock(PanelLeft,NULL,alClient);
	FrameOutput->ManualDock(PanelBottom,NULL,alClient);
	this->m_nFrameOutputHeight=FrameOutput->Height;
	this->m_nFramePropertyWidth=FrameProperty->Width;
  InitialProject();
  pBitmap = new Graphics::TBitmap();
  try
  {
    pBitmap->LoadFromFile("flag.bmp");
    pBitmap->Transparent = true;
    pBitmap->TransparentColor = pBitmap->Canvas->Pixels[16][16];
  }
  catch (...)
  {
    delete pBitmap;
    pBitmap=NULL;
  }
  /*
   m_hParserDll = LoadLibrary("DllParser.dll");
   InitialPaser = (MyInitialPaser)GetProcAddress((HINSTANCE)m_hParserDll,"Initial");
   SetPaserExpress = (int (WINAPI*)(char* str))GetProcAddress((HINSTANCE)m_hParserDll,"SetExpression");
   CheckPaserExpression = (int (WINAPI*)(char* str))GetProcAddress((HINSTANCE)m_hParserDll,"CheckExpression");
   GetPaserResult = (double (WINAPI*)(int&s))GetProcAddress((HINSTANCE)m_hParserDll,"GetResult");
   GetPaserStrResult = (char* (WINAPI*)(int&s))GetProcAddress((HINSTANCE)m_hParserDll,"GetStrResult");
   GetVariableCount = (int (WINAPI*)(int left))GetProcAddress((HINSTANCE)m_hParserDll,"GetVariableCount");
   GetVariableName = (char* (WINAPI*)(int i,int left))GetProcAddress((HINSTANCE)m_hParserDll,"GetVariableName");
   ExpressionVariables = (void (WINAPI*)(char* str))GetProcAddress((HINSTANCE)m_hParserDll,"ExpressionVariables");
   ClearPaserStrResult = (void (WINAPI*)())GetProcAddress((HINSTANCE)m_hParserDll,"ClearStrResult");
   InitialPaser(); */
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::FormDestroy(TObject *Sender)
{
  ClearProject();
  delete m_selectRect;
  if(bmp!=NULL)
    delete  bmp;
  if(pBitmap!=NULL)
  {
    delete pBitmap;
    pBitmap=NULL;
  }
  if(graphic!=NULL)
  {
    delete graphic;
    pBitmap=graphic;
  }

   delete m_pReasonMachine;
}
//---------------------------------------------------------------------------




void __fastcall TfrmMainFrame::PanelLeftDockOver(TObject *Sender,
			TDragDockObject *Source, int X, int Y, TDragState State,
			bool &Accept)
{
	if(Source->Control->Name =="FrameProperty")
	{
		Accept=true;
		TPoint pointLT=PanelLeft->ClientToScreen(TPoint(0,0));
		TPoint pointRB=PanelLeft->ClientToScreen(TPoint(Source->Control->Width,Source->Control->Height));
		TRect rect=TRect(pointLT.x,pointLT.y,pointRB.x,pointRB.y);
		Source->DockRect=rect;

	}
	else
	{
		Accept=false;
		TRect rect=TRect(0,0,0,0);
		Source->DockRect=rect;
	}

}
//---------------------------------------------------------------------------
void __fastcall TfrmMainFrame::PanelBottomDockOver(TObject *Sender,
      TDragDockObject *Source, int X, int Y, TDragState State,
      bool &Accept)
{
	if(Source->Control->Name =="FrameOutput")
	{
		Accept=true;
		TPoint pointLT=PanelBottom->ClientToScreen(TPoint(0,0));
		TPoint pointRB=PanelBottom->ClientToScreen(TPoint(Source->Control->Width,Source->Control->Height));
		TRect rect=TRect(pointLT.x,pointLT.y,pointRB.x,pointRB.y);
		Source->DockRect=rect;

	}
	else
	{
		Accept=false;
		TRect rect=TRect(0,0,0,0);
		Source->DockRect=rect;
	}
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::btnNormalClick(TObject *Sender)
{

	PanelLeft->AutoSize=false;
	FrameProperty->Width=m_nFramePropertyWidth;
	PanelLeft->Width= FrameProperty->Width;
	FrameProperty->Show();
	PanelLeft->Show();
	PanelLeft->AutoSize=true;

	PanelBottom->AutoSize=false;
	FrameOutput->Height=m_nFrameOutputHeight;
	PanelBottom->Height= FrameOutput->Height;
	PanelBottom->Show();
	FrameOutput->Show();
	PanelBottom->AutoSize=true;

	Splitter1->Align=alNone;
	Splitter2->Align=alNone;
	Splitter2->Left=PanelLeft->Width+2;
	Splitter1->Top=PanelBottom->Top-4;
	Splitter1->Align=alBottom;
	Splitter2->Align=alLeft;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::Splitter2Moved(TObject *Sender)
{
	PanelLeft->AutoSize=true;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::Splitter2CanResize(TObject *Sender,
			int &NewSize, bool &Accept)
{
	PanelLeft->AutoSize=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::Splitter1CanResize(TObject *Sender,
			int &NewSize, bool &Accept)
{
	PanelBottom->AutoSize=false;

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::Splitter1Moved(TObject *Sender)
{
	PanelBottom->AutoSize=true;

}
//---------------------------------------------------------------------------



void __fastcall TfrmMainFrame::FramePropertyEndDock(TObject *Sender,
			TObject *Target, int X, int Y)
{
        if(Target==NULL) FrameProperty->ManualDock(PanelLeft,NULL,alClient);
	Splitter2->Align=alNone;
	Splitter2->Left=PanelLeft->Width+2;
	Splitter2->Align=alLeft;

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::MainPaintBoxMouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    long RealX,RealY;
    RealX = ((double)(X)/g_pProject->proportion)+ g_pProject->XOrientation;
    RealY = ((double)(Y)/g_pProject->proportion)+ g_pProject->YOrientation;
    POINT p;
    p.x = RealX;
    p.y = RealY;
    Current_X=RealX;Current_Y=RealY;
    if (Button == mbRight)
    {
       if(g_pProject->IsSelect(p,Shift)==NULL)
       {
           p.x = X;
           p.y = Y;
           p = MainPaintBox->ClientToScreen(p);

           //tp_back->Popup(p.x,p.y); Interface feature
            return;
       }
       p.x = X;
       p.y = Y;
       p = MainPaintBox->ClientToScreen(p);
       //tp_obj->Popup(p.x,p.y)    Selected object feature
       return;
    }//right
    if(g_pProject->DrawingType != dtLineEvent)
    {
      BasicGraph*obj;
      if((obj=g_pProject->SelectTest(p))!=NULL)
      {
        if(obj->m_bSelected)
             g_pProject->DrawingType=dtNothing;
        else
             g_pProject->DrawingType=dtSelect;
      }
    }
    switch (g_pProject->DrawingType)
    {
        case dtFCMsNode:
        {
           FCMsNode*event=g_pProject->AddFCMsNode(p);
           if(event!=NULL)
           {
              event->Resize(g_pProject->proportion);
              event->SetOrientation(g_pProject->XOrientation,g_pProject->YOrientation);
              this->FrameProperty->AddSelectedToTree();
              ViewIsChanged();
           }
           else
              g_pProject->DrawingType=dtSelect;
           break;
        }
        case dtLineEvent:
        {
           if((g_pProject->DrawLine_Start=(NodeEvent*)g_pProject->IsSelect(p,Shift))!=NULL&&!g_pProject->IsSelectLineEvent())
           {
                p_start = p;
                p_end = p;
             }
           else
              g_pProject->DrawingType= dtSelect;
           break;
        }
        case dtSelect:
        {
          if(!Shift.Contains(ssShift))
					{
              p_start=p;
              m_selectRect->Resize(g_pProject->proportion);
              m_selectRect->SetOrientation(g_pProject->XOrientation,g_pProject->YOrientation);
              m_selectRect->SetRect(RealX,RealY,RealX,RealY);
          }
          if(g_pProject->IsSelect(p,Shift)!=NULL)
          {
            g_pProject->DrawingType=dtSelect;
            g_pProject->SetSelectedMouseD(p);
            ViewIsChanged();
          }


          break;
        }
        case dtNothing:
        {
           g_pProject->SetSelectedMouseD(p);
           break;
        }
        default:
        {
            break;
        }
    }
    TDrawingTool tool=g_pProject->DrawingType;
    btnCursor->Down = tool==dtNothing||tool==dtSelect?true:false;
    btnAddLine->Down = tool==dtLineEvent?true:false;
    btnFCMsNode->Down = tool==dtFCMsNode?true:false;
    Refresh();
    return;

}
//---------------------------------------------------------------------------



void __fastcall TfrmMainFrame::btnFCMsNodeClick(TObject *Sender)
{

    if (!btnFCMsNode->Down)
      g_pProject->DrawingType = dtNothing;
    else
    {
      g_pProject->DrawingType = dtFCMsNode;
      btnFCMsNode->Down=false;
      btnAddLine->Down=false;
      btnCursor->Down=false;
    }
}
//---------------------------------------------------------------------------
void TfrmMainFrame::NodeInCenter(NodeEvent*pNode)
{
   if(AnsiString(pNode->ClassName())=="FCMsNode")
   {
      pNode->Select();
      g_pProject->m_pSelectedList->Add(pNode);
      long dx= bmp->Width/2;
      long dy=bmp->Height/2;
      POINT p=g_pProject->ScreenToReal(dx,dy);
      g_pProject->SetOffset(pNode->X-p.x,pNode->Y-p.y);
      srb_h->Position = 0;
      srb_v->Position = 0;
      Refresh();
   }

}
void TfrmMainFrame::ViewIsChanged()
{
		FrameProperty->ChangeTreeSelectStatus();
    FrameProperty->RefreshProperty();
}
void __fastcall TfrmMainFrame::btnAddLineClick(TObject *Sender)
{

    if (!btnAddLine->Down)
      g_pProject->DrawingType = dtNothing;
    else
    {
      g_pProject->DrawingType = dtLineEvent;
      btnFCMsNode->Down=false;
      btnCursor->Down=false;
    }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void TfrmMainFrame::Refresh()
{
     bmp->Canvas->Brush->Color = g_pProject->m_cBackGround;
     bmp->Canvas->FillRect(MainPaintBox->ClientRect);

     if(graphic!=NULL)
       bmp->Canvas->StretchDraw(TRect(-g_pProject->XOrientation*g_pProject->proportion,-g_pProject->YOrientation*g_pProject->proportion
      ,(graphic->Width-g_pProject->XOrientation) * g_pProject->proportion,(graphic->Height-g_pProject->YOrientation) * g_pProject->proportion)
      ,graphic);


     bmp->Canvas->CopyMode= cmSrcCopy;

     if(g_pProject->DrawingType == dtLineEvent&&m_bMouseMove)
     {
        double xt,yt,xg,yg;TPoint arrow[3];

        long x1 =((double)(p_start.x-g_pProject->XOrientation))*g_pProject->proportion;
        long y1 = ((double)(p_start.y-g_pProject->YOrientation))*g_pProject->proportion;
        long x2 =((double)(p_end.x-g_pProject->XOrientation))*g_pProject->proportion;
        long y2 =((double)(p_end.y-g_pProject->YOrientation))*g_pProject->proportion;

        if(y2!=y1)
        {

            yg=y2-16*(y2-y1)*sqrt(1.0/(double)((y2-y1)*(y2-y1)+(x2-x1)*(x2-x1)));
            xg=x2-((double)(x2-x1))/((double)(y2-y1))*(y2-yg);
            xt=xg+8*sqrt((y2-yg)*(y2-yg)/((x2-xg)*(x2-xg)+(y2-yg)*(y2-yg)))/2;
            yt=yg-(x2-xg)/(y2-yg)*(xt-xg);
            arrow[0].x=x2;arrow[0].y=y2;
            arrow[1].x=xt;arrow[1].y=yt;
            xt=xg-8*sqrt((y2-yg)*(y2-yg)/((x2-xg)*(x2-xg)+(y2-yg)*(y2-yg)))/2;
            yt=yg-(x2-xg)/(y2-yg)*(xt-xg);
            arrow[2].x=xt;arrow[2].y=yt;

        }
        else
        {
            yg=y2;
            if(x2>x1)
                xg=x2-16;
            else
                xg=x2+16;
            arrow[0].x=x2;arrow[0].y=y2;
            arrow[1].x=xg;arrow[1].y=yg+8/2 ;
            arrow[2].x=xg;arrow[2].y=yg-8/2 ;
        }
        bmp->Canvas->MoveTo(x1,y1);
        bmp->Canvas->LineTo(x2,y2);
        bmp->Canvas->Polygon(arrow,2);
     }
     g_pProject->Draw(bmp->Canvas);
     ////
     MainPaintBox->Canvas->CopyRect(MainPaintBox->ClientRect,bmp->Canvas,MainPaintBox->ClientRect);
}
void __fastcall TfrmMainFrame::MainPaintBoxMouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
    long RealX,RealY;
    RealX = ((double)(X)/g_pProject->proportion)+ g_pProject->XOrientation;
    RealY = ((double)(Y)/g_pProject->proportion)+ g_pProject->YOrientation;
    if(Shift.Contains(ssLeft))
    {
        m_bMouseMove = true;
        POINT p;
        p.x = RealX;
        p.y = RealY;

        switch (g_pProject->DrawingType)
        {
        case dtLineEvent:
        {
           p_end = p;
           Refresh();
           break;
        }
        case dtNothing:
        {
           if(g_pProject->m_pSelectedList->Count>0)
           {
                 g_pProject->ReDrawSelectObj(RealX,RealY,MainPaintBox->Canvas);
                 Refresh();
           }
           break;
        }
        case dtSelect:
        {
           if(g_pProject->m_pSelectedList->Count>0)
           {
                 g_pProject->ReDrawSelectObj(RealX,RealY,MainPaintBox->Canvas);
                 Refresh();
           }
           else if(!Shift.Contains(ssShift))
           {
                m_selectRect->OnDraw(MainPaintBox->Canvas,pmNotXor);
                m_selectRect->SetRect(p_start.x,p_start.y,RealX,RealY);
                m_selectRect->OnDraw(MainPaintBox->Canvas,pmNotXor);
           }
           break;
        }
        }
    }
    else
    {
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::PanelPaintResize(TObject *Sender)
{
  g_pProject->m_MaxPoint.x=MainPaintBox->Width;
  g_pProject->m_MaxPoint.y=MainPaintBox->Height;
  bmp->Width=MainPaintBox->Width;
  bmp->Height=MainPaintBox->Height;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::MainPaintBoxMouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
    long RealX,RealY;
    RealX = ((double)(X)/g_pProject->proportion)+ g_pProject->XOrientation;
    RealY = ((double)(Y)/g_pProject->proportion)+ g_pProject->YOrientation;

    m_bMouseMove = false;

    switch (g_pProject->DrawingType)
    {
        case dtLineEvent:
        {
           POINT p;
           p.x = RealX;
           p.y = RealY;
           p_end = p;
           if((g_pProject->DrawLine_End=(NodeEvent*)g_pProject->IsSelect(p,Shift))!=NULL&&!g_pProject->IsSelectLineEvent())
           {
              if(IsConnected(g_pProject->DrawLine_Start,g_pProject->DrawLine_End)>0)
              {
                 Application->MessageBox("Exist line!","Hint",MB_OK);
                 g_pProject->UnSelectAll();
                 break;
              }
              LineEvent*event = g_pProject->AddLinkEvent(g_pProject->DrawLine_Start,g_pProject->DrawLine_End);
              if(event!=NULL)
              {
                 event->Resize(g_pProject->proportion);
                 event->SetOrientation(g_pProject->XOrientation,g_pProject->YOrientation);
              }
              else
              {
                 Application->MessageBox("Line setup Error！","Hint",MB_OK);
                 g_pProject->UnSelectAll();
              }
           }
           else
              Application->MessageBox("Line should be between objects","Hint",MB_OK);
           break;
        }
        case dtNothing:
        {
             g_pProject->DrawingType=dtSelect;
             break;
        }
        case dtSelect:
        {
            if(!Shift.Contains(ssShift))
            {
                g_pProject->IsSelect(m_selectRect->GetRect());
                ViewIsChanged();
            }
            break;
        }
    }

    Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::FrameOutputEndDock(TObject *Sender,
      TObject *Target, int X, int Y)
{
        if(Target==NULL) FrameOutput->ManualDock(PanelBottom,NULL,alClient);

	Splitter1->Align=alNone;
	Splitter1->Top=PanelBottom->Top-4;
	Splitter1->Align=alBottom;

}
//---------------------------------------------------------------------------




void __fastcall TfrmMainFrame::btnDeleteClick(TObject *Sender)
{
    if(!m_bEditCanvas)return;
      switch (Application->MessageBox("Delete Selected object？","Hint",MB_YESNOCANCEL))
      {  case ID_YES :
         {
            this->FrameProperty->DeleteSelectedFromTree();
            g_pProject->DeleSelected();
            Refresh();
            break;
         }
         case ID_CANCEL :
            return;
      }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxBarButton1Click(TObject *Sender)
{
     g_pProject->SelectAll();
     Refresh();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::btnCopyClick(TObject *Sender)
{
       if(!m_bEditCanvas)return;
       g_pProject->PrepareCopy();
       if(g_pProject->m_pCopybufferList->Count>0)
               m_bCopy=true;
       else
               m_bCopy=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::btnPasteClick(TObject *Sender)
{
    if(!m_bEditCanvas)return;
     if(m_bCopy)
     {
       g_pProject->CopySelected();
       this->FrameProperty->AddSelectedToTree();
       Refresh();
       g_pProject->m_pCopybufferList->Clear();
       m_bCopy=false;
     }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::cbZoomChange(TObject *Sender)
{
     double p;
     switch(cbZoom->ItemIndex)
     {
     case 0:
     {
          p=5;
          break;
     }
     case 1:
     {
          p=2;
          break;
     }
     case 2:
     {
          p=1.5;
          break;
     }
     case 3:
     {
          p=1;
          break;
     }
     case 4:
     {
          p=0.75;
          break;
     }
     case 5:
     {
          p=0.5;
          break;
     }
     case 6:
     {
          p=0.25;
          break;
     }
     case 7:
     {
          p=0.1;
          break;
     }
     default:
     {
          p=1;
          break;
     }
     }
     g_pProject->ZoomTo(p);
     Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::MainPaintBoxDblClick(TObject *Sender)
{
    g_pProject->DrawingType = dtNothing;
    TShiftState Shift;
    Shift << ssDouble;
    BasicGraph*myobj;
    POINT p;
    p.x = Current_X;
    p.y = Current_Y;
    if((myobj=g_pProject->IsSelect(p,Shift))!=NULL)
    {
        if(g_pProject->IsSelectFCMsNode())
          {;}
        else if(g_pProject->IsSelectLineEvent())
        {
          ((LineEvent*)myobj)->ClearPoints();
        }
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::btnSaveClick(TObject *Sender)
{
     SaveCommand();
}
//---------------------------------------------------------------------------
void  TfrmMainFrame::SaveCommand()
{
     if(g_pProject->m_strFileName.Length()>6)
     {
         g_pProject->XMLDoc = XMLDocument1;
         g_pProject->SaveToXML(g_pProject->m_strFileName);
     }
     else
     {
        SaveDialog->DefaultExt =  "*.xml";
        SaveDialog->FileName = "*.xml";
        SaveDialog->Filter = "Model File|XML File|*.xml";
        if(SaveDialog->Execute())
        {
            g_pProject->m_strFileName=SaveDialog->FileName;
            g_pProject->XMLDoc = XMLDocument1;
            g_pProject->SaveToXML(g_pProject->m_strFileName);
        }
     }
     g_pProject->UnSelectAll();
     g_pProject->m_bModified = false;
}

void __fastcall TfrmMainFrame::btnOpenClick(TObject *Sender)
{
    OpenDialog->Filter = "Model File|*.xml";
    OpenDialog->DefaultExt = "*.XML";
    OpenDialog->FileName = "*.XML";
    if(g_pProject->m_bModified)
    {
      switch (Application->MessageBox("Model File has been modified, save？","Hint",MB_YESNOCANCEL))
      {  case ID_YES :
            SaveCommand();
            break;
         case ID_CANCEL :
            return;
      }
    }
    ClearProject();
    InitialProject();
    if(OpenDialog->Execute())
    {
        g_pProject->m_strFileName=OpenDialog->FileName;
        AnsiString exten = ExtractFileExt(OpenDialog->FileName);
        exten = exten.UpperCase();
        if(exten == ".XML")
        {
          g_pProject->XMLDoc = XMLDocument1;
          g_pProject->LoadFromXML(g_pProject->m_strFileName);

          if( graphic==NULL)
             graphic=new Graphics::TBitmap();
          if(g_pProject->m_strLayout.Length()>2)
          {
           try {
              graphic->LoadFromFile(g_pProject->m_strLayout);
           } catch (Exception &e)
           {  ShowMessage(e.Message);delete graphic;graphic=NULL;
           }
          }
          this->Caption="Smart Environment----"+g_pProject->m_strFileName;
        }
        else
        {
          return;
        }
        FrameProperty->RefreshProjectTree();
        Refresh();
    }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::cbZoomKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
       if(Key == VK_RETURN )
       {
         AnsiString temp1;
         double temp2;
         temp1=cbZoom->Text;
         try
         {
            int pos=temp1.Pos('%');
            if(pos>0)
            {
              temp1=temp1.SubString(1,pos-1);
              temp2=temp1.ToDouble();
              temp2=temp2/100;
            }
            else
               temp2=temp1.ToDouble();
            if(temp2<0.05||temp2>5)
            { Application->MessageBox("0.05~5！","Hint",MB_OK);return;}
            g_pProject->ZoomTo(temp2);
            Refresh();
        }
        catch(EConvertError &)
        {    Application->MessageBox("0.05~5!","Hint",MB_OK); }
       }

}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::srb_vChange(TObject *Sender)
{
   g_pProject->SetOffset(0,5*srb_v->Position);
   srb_v->Position = 0;
   Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::srb_hChange(TObject *Sender)
{
   g_pProject->SetOffset(5*srb_h->Position,0);
   srb_h->Position = 0;
   Refresh();

}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::dxBarCheckValidClick(TObject *Sender)
{
   g_pProject->CheckValid();
   Refresh();
            FILE *ff;
        ff=fopen("work.dat","w");
        if(ff == NULL)
          return ;
        int num=0;

        int first=g_pProject->m_pFCMsNodeList->Count;
   int Len=1;
   //int time[10];
   //time[0]=10;time[1]=20;time[2]=50;time[3]=100;time[4]=150;time[5]=200;time[6]=250;time[7]=300;time[8]=500;time[9]=1000;
   int time[1];
   time[0]=20;
   for(int roll=0;roll<Len;roll++)
   {
       for(int i = 1;i<=first;i++)
       {
               FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i-1];
//            for(int j = 1;j<=time-1;j++)
            {
               AnsiString strE;
               for(int jj = 1;jj<=g_pProject->m_pFCMsNodeList->Count;jj++)
               {
                  if(i!=jj)
                  {
                    FCMsNode*myobj2 = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[jj-1];
                    if(IsConnected(myobj,myobj2)==0)
                    {
                       if(strE.Length()==0)
                           strE="[0,";
                       else
                           strE=strE+"0,";
                    }
                    else
                    {
                       if(strE.Length()==0)
                           strE="[1,";
                       else
                           strE=strE+"1,";
                    }
                  }
                  else
                  {
                       if(strE.Length()==0)
                           strE="[0,";
                       else
                           strE=strE+"0,";
                  }
               }
               strE=strE+"]\n";
               fprintf(ff,strE.c_str());
            }
       }


        for(int i = 1;i<=first;i++)
       {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i-1];
          TList*cl=new TList;
          g_pProject->GetNoConnectedNodes(myobj,cl);

          for(int k=1;k<=cl->Count;k++)
          {
              int cc=1;
             for(int j = 1;j<=time[roll]-1;j++)
             {
               cc++;
               fprintf (ff, "e7_%d_%d_%d(j),",i,j,k);
               if(cc==30)
               {
                  fprintf (ff, "\n");
                  cc=1;
               }
             }
          }
          cl->Clear();
          delete cl;
          fprintf (ff, "\n");
       }
       fprintf (ff, ";\n\n\n");


        for(int i = 1;i<=first;i++)
       {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i-1];
          TList*cl=new TList;
          g_pProject->GetNoConnectedNodes(myobj,cl);
          for(int k=1;k<=cl->Count;k++)
          {
             int index=-1;
             FCMsNode*mycon = (FCMsNode*)cl->Items[k-1];
             for(int ii=1;ii<=first;ii++)
             {
                FCMsNode*myobj2 = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[ii-1];
                if(myobj2==mycon)
                {
                  index=ii;
                  break;
                }
             }
            for(int j = 1;j<=time[roll]-1;j++)
             {
               fprintf (ff, "e7_%d_%d_%d(j)..x('%d','%d',j)+x('%d','%d',j)=l= 1;\n",i,j,k,i,j,index,j+1);
             }
          }
          cl->Clear();
          delete cl;
       }
     fprintf (ff, "-------------------------\n\n\n");
    }

   int cc=1;
   for(int roll=0;roll<Len;roll++)
   {
             for(int j = 2;j<=time[roll];j++)
             {
               cc++;
               fprintf (ff, "n1_%d_(si,j),",j-1);
               if(cc==30)
               {
                  fprintf (ff, "\n");
                  cc=1;
               }
             }
       fprintf (ff, "\n\n\n");
       cc=1;
             for(int j = 2;j<=time[roll];j++)
             {
               cc++;
               fprintf (ff, "n2_%d_(si,j),",j-1);
               if(cc==30)
               {
                  fprintf (ff, "\n");
                  cc=1;
               }
             }
       fprintf (ff, "\n\n\n");
       cc=1;
             for(int j = 1;j<time[roll];j++)
             {
               cc++;
               fprintf (ff, "n3_%d_(si,j),",j);
               if(cc==30)
               {
                  fprintf (ff, "\n");
                  cc=1;
               }
             }
       fprintf (ff, "\n\n\n");


         cc=1;

        for(int i = 1;i<=first;i++)
       {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i-1];
          TList*cl=new TList;
          g_pProject->GetNoConnectedNodes(myobj,cl);

          for(int k=1;k<=cl->Count;k++)
          {
             int index=-1;
             FCMsNode*mycon = (FCMsNode*)cl->Items[k-1];
             for(int ii=1;ii<=first;ii++)
             {
                FCMsNode*myobj2 = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[ii-1];
                if(myobj2==mycon)
                {
                  index=ii;
                  break;
                }
             }
               fprintf (ff, "n4_%d_%d_(t,j),",i,index);
               if(cc==30)
               {
                  fprintf (ff, "\n");
                  cc=1;
               }
          }
          cl->Clear();
          delete cl;
          fprintf (ff, "\n");
       }
       fprintf (ff, "\n\n\n");


       cc=1;
             for(int j = 2;j<=time[roll];j++)
             {
               cc++;
               fprintf (ff, "n1_%d_(si,j)..x(si,'%d',j)=l=alpha(si,'%d',j);\n",j-1,j-1,j);
               if(cc==30)
               {
                  fprintf (ff, "\n");
                  cc=1;
               }
             }
       fprintf (ff, ";\n\n\n");
       cc=1;
             for(int j = 2;j<=time[roll];j++)
             {
               cc++;
               fprintf (ff, "n2_%d_(si,j)..e(si,'%d',j)=l=alpha(si,'%d',j);\n",j-1,j-1,j);
               if(cc==30)
               {
                  fprintf (ff, "\n");
                  cc=1;
               }
             }
       fprintf (ff, ";\n\n\n");
       cc=1;
             for(int j = 1;j<time[roll];j++)
             {
               cc++;
               fprintf (ff, "n3_%d_(si,j)..gamma(si,'%d',j)=l=x(si,'%d',j);\n",j,j,j+1);
               if(cc==30)
               {
                  fprintf (ff, "\n");
                  cc=1;
               }
             }
       fprintf (ff, ";\n\n\n");

        cc=1;
         for(int i = 1;i<=first;i++)
       {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i-1];
          TList*cl=new TList;
          g_pProject->GetNoConnectedNodes(myobj,cl);

          for(int k=1;k<=cl->Count;k++)
          {
               cc++;
              int index=-1;
             FCMsNode*mycon = (FCMsNode*)cl->Items[k-1];

              for(int ii=1;ii<=first;ii++)
             {
                FCMsNode*myobj2 = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[ii-1];
                if(myobj2==mycon)
                {
                  index=ii;
                  break;
                }
             }

               fprintf (ff, "n4_%d_%d_(t,j)..e('%d',t,j)+o('%d',t,j)=l=1;",i,index,i,index);
               if(cc==30)
               {
                  fprintf (ff, "\n");
                  cc=1;
               }
          }
          cl->Clear();
          delete cl;
          fprintf (ff, "\n");
       }
       fprintf (ff, ";\n\n\n");

     fprintf (ff, "-------------------------\n\n\n");
    }




       fclose(ff);
}
//---------------------------------------------------------------------------




void __fastcall TfrmMainFrame::btnFitToWindowClick(TObject *Sender)
{
   g_pProject->FitToWindow(MainPaintBox->Height-60,MainPaintBox->Width-60);
   Refresh();


}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::btnPrintClick(TObject *Sender)
{
     if (!PrintDialog1->Execute())
          return;
     Printer()->BeginDoc();

     PrintPage(0);
     Printer()->EndDoc();
}
//---------------------------------------------------------------------------
void __fastcall TfrmMainFrame::PrintPage(int page)
{
     bmp->Canvas->Brush->Color = g_pProject->m_cBackGround;
     bmp->Canvas->FillRect(MainPaintBox->ClientRect);

     bmp->Canvas->CopyMode= cmSrcCopy;
     g_pProject->FitToWindow(Printer()->PageHeight-60,Printer()->PageWidth-60);

    g_pProject->Draw(Printer()->Canvas);

    g_pProject->FitToWindow(MainPaintBox->Height-60,MainPaintBox->Width-60);
    Refresh();
}
void __fastcall TfrmMainFrame::FramePropertyTreeViewProjectClick(
      TObject *Sender)
{
  FrameProperty->TreeViewProjectClick(Sender);
  m_bEditCanvas=false;

}
//---------------------------------------------------------------------------



void __fastcall TfrmMainFrame::FrameOutputMemo1Click(TObject *Sender)
{
     m_bEditCanvas=false;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::MainPaintBoxClick(TObject *Sender)
{
     m_bEditCanvas=true;
}
//---------------------------------------------------------------------------


void TfrmMainFrame::SaveCommandAs()
{
     if(g_pProject->m_strFileName.Length()>6)
     {
        AnsiString exten = ExtractFileExt(g_pProject->m_strFileName);
        SaveDialog->DefaultExt =  exten;
        SaveDialog->FileName = g_pProject->m_strFileName;
        SaveDialog->Filter = "Model File|XML File|*.XML";

        if(SaveDialog->Execute())
        {
           g_pProject->XMLDoc = XMLDocument1;
           g_pProject->SaveToXML(SaveDialog->FileName);
           g_pProject->m_strFileName=SaveDialog->FileName;
           this->Caption="Smart Environment----"+g_pProject->m_strFileName;
        }
     }
     else
     {
        SaveDialog->DefaultExt =  "*.xml";
        SaveDialog->FileName = "*.xml";
        SaveDialog->Filter = "Model File|XML File|*.xml";
        if(SaveDialog->Execute())
        {
            g_pProject->m_strFileName=ExtractFileName(SaveDialog->FileName);
            g_pProject->XMLDoc = XMLDocument1;
            g_pProject->SaveToXML(g_pProject->m_strFileName);
            this->Caption="Smart Environment----"+g_pProject->m_strFileName;

        }
     }
     g_pProject->UnSelectAll();
     g_pProject->m_bModified = false;
}


void __fastcall TfrmMainFrame::FormClose(TObject *Sender,
      TCloseAction &Action)
{
    if(g_pProject->m_bModified)
    {
      switch (Application->MessageBox("Model File has been modified, save？","Hint",MB_YESNOCANCEL))
      {  case ID_YES :
            SaveCommand();
            break;
         case ID_CANCEL :
            Action=caNone;
      }
    }
}
//---------------------------------------------------------------------------



void __fastcall TfrmMainFrame::btnCursorClick(TObject *Sender)
{
    g_pProject->DrawingType = dtNothing;

    if (btnCursor->Down)
    {
      btnFCMsNode->Down=false;
      btnAddLine->Down=false;
    }

}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::btnNewBlankModalClick(TObject *Sender)
{
    if(g_pProject->m_bModified)
    {
      switch (Application->MessageBox("Model File has been modified, save？","Hint",MB_YESNOCANCEL))
      {  case ID_YES :
            SaveCommand();
            break;
         case ID_CANCEL :
            return;
      }
    }
    ClearProject();
    InitialProject();
    g_pProject->proportion = 1;
    g_pProject->SetOffsetTo(0,0);
    Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxReasonClick(TObject *Sender)
{
   //tf_relationship->m_pHistory->Clear();
   m_pReasonMachine->Calculate();
   Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxSimulateClick(TObject *Sender)
{
   m_pReasonMachine->Calculate();
   g_pProject->m_nWorkType=0;
   g_pProject->m_dSimulateTime=0;
   g_pProject->ClearHistory();
   for(int i=0;i<g_pProject->m_pUserHistory->Count;i++)
   {
        WalkingUser*user=(WalkingUser*)g_pProject->m_pUserHistory->Items[i];
        delete user;
   }
   if(g_pProject->m_iSwitch)
        g_pProject->Simulate();
   else
        g_pProject->Simulate2();
   Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxCheckValueofFCMsClick(TObject *Sender)
{
        AnsiString m_SensorHist;
        AnsiString m_UserHis;
        SaveDialog->DefaultExt =  "*.txt";
        SaveDialog->FileName = "*.txt";
        SaveDialog->Filter = "Sensor History|TEXT File|*.txt";
        if(SaveDialog->Execute())
        {
            m_SensorHist=SaveDialog->FileName;
            if(g_pProject->m_iSwitch)
                g_pProject->SaveHistory(m_SensorHist);
            else
                g_pProject->SaveHistory2(m_SensorHist);
        }

        SaveDialog->DefaultExt =  "*.txt";
        SaveDialog->FileName = "*.txt";
        SaveDialog->Filter = "User History|TEXT File|*.txt";
        if(SaveDialog->Execute())
        {
            m_UserHist=SaveDialog->FileName;
            if(g_pProject->m_iSwitch)
                g_pProject->SaveUserHistory(m_UserHist);
            else
            {
                AnsiString m_UserHist2=m_UserHist;
                int findi=m_UserHist2.Pos(".txt");
                m_UserHist2=m_UserHist2.Delete(findi,4);
                m_UserHist2=m_UserHist2.Insert("2.txt",findi);
                g_pProject->SaveUserHistory(m_UserHist);
                g_pProject->SaveUserHistory2(m_UserHist2);
            }
        }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxLeftClick(TObject *Sender)
{
   g_pProject->ToLeft(MainPaintBox->Canvas);
   Refresh();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxRightClick(TObject *Sender)
{
   g_pProject->ToRight(MainPaintBox->Canvas);
   Refresh();
  
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxTopClick(TObject *Sender)
{
   g_pProject->ToTop(MainPaintBox->Canvas);
   Refresh();

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxBottomeClick(TObject *Sender)
{
   g_pProject->ToBottom(MainPaintBox->Canvas);
   Refresh();

}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::dxSortClick(TObject *Sender)
{
      switch (Application->MessageBox("Are you sure to sort those selected objects?","Hint",MB_YESNOCANCEL))
      {  case ID_YES :
         {
            g_pProject->SortSelected();
            ViewIsChanged();
            Refresh();
            break;
         }
         case ID_CANCEL :
            return;
      }

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::btnCloseClick(TObject *Sender)
{
    if(g_pProject->m_bModified)
    {
      switch (Application->MessageBox("Model File has been modified, save？","Hint",MB_YESNOCANCEL))
      {  case ID_YES :
            SaveCommand();
            break;
         case ID_CANCEL :
            return;
      }
    }
    ClearProject();
    InitialProject();
    g_pProject->proportion = 1;
    g_pProject->SetOffsetTo(0,0);
    Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::btnExitClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::btnFindClick(TObject *Sender)
{
  TTreeView* pTreeView=FrameProperty->TreeViewProject;
	TList* pNodeList=new TList;
  TTreeNode* pTreeNode=pTreeView->Selected;
  if(pTreeNode!=NULL) pNodeList->Add(pTreeNode);
	frmFind->ShowModal();
	pTreeView->Select(pNodeList);
	delete pNodeList;  
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::dxBarViewControlClick(TObject *Sender)
{
  gbl_view=(gbl_view<=0?1:0);
  Refresh();
}
//---------------------------------------------------------------------------



void __fastcall TfrmMainFrame::dxSimulatStepClick(TObject *Sender)
{
   ClearSimulatingOutput();
   if(  m_pSimulator==NULL)
       m_pSimulator=new Simulator(false);
   else
   {
   if(g_pProject->m_iSwitch)
   {
        for(int i = 0;i<g_pProject->m_pUserHistory->Count;i++)
        {
          WalkingUser*pUser = (WalkingUser*)g_pProject->m_pUserHistory->Items[i];
          delete pUser;
        }
        if(m_pSimulator->m_bWorking=false)
        {
                m_pSimulator->m_pUserList->Clear();
        }
        g_pProject->m_pUserHistory->Clear();
   }
   else
   {
        for(int i = 0;i<g_pProject->m_pUserHistory->Count;i++)
        {
            WalkingUser*pUser = (WalkingUser*)g_pProject->m_pUserHistory->Items[i];
            for(int i=0;i<pUser->m_pPathList->Count;i++)
            {
                HISNODE*n1=(HISNODE*)pUser->m_pPathList->Items[i];
                delete n1;
            }
            pUser->m_pPathList->Clear();
            delete pUser;
        }
        g_pProject->m_pUserHistory->Clear();
        m_pSimulator->m_pUserList->Clear();
        m_pSimulator->Initial();
   }
   }
   if(!g_pProject->m_iSwitch)
           m_bSendingData=false;//set true if you want to send data to other
   g_pProject->m_nWorkType=1;
   m_pSimulator->simTime=0;
   m_pSimulator->m_bWorking=true;
   m_pSimulator->Resume();
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::dxPauseClick(TObject *Sender)
{
    if(m_pSimulator!=NULL)
    {
       m_pSimulator->m_bWorking = !m_pSimulator->m_bWorking;
    }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxStopSimulateClick(TObject *Sender)
{
ClearSimulatingOutput();
if(m_pSimulator!=NULL)
{
   m_pSimulator->m_bWorking=false;
   m_pSimulator->simTime=0;
   for(int i = 0;i<g_pProject->m_pUserHistory->Count;i++)
   {
          WalkingUser*pUser = (WalkingUser*)g_pProject->m_pUserHistory->Items[i];
          delete pUser;
   }
   g_pProject->m_pUserHistory->Clear();
   m_pSimulator->m_pUserList->Clear();
   delete m_pSimulator;
   m_pSimulator=NULL;
 }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxOpenLayoutClick(TObject *Sender)
{
   OpenDialog->Filter = "Layout File|*.bmp";
    OpenDialog->DefaultExt = "*.bmp";
    OpenDialog->FileName = "*.bmp";
    if(OpenDialog->Execute())
    {
        graphic=new Graphics::TBitmap();
        try {
        graphic->LoadFromFile(OpenDialog->FileName);
       } catch (Exception &e)
       {  ShowMessage(e.Message);delete graphic;graphic=NULL;return;
       }
       g_pProject->m_strLayout=OpenDialog->FileName;
       g_pProject->m_bModified=true;
       Refresh();
    }
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::dxVisualClick(TObject *Sender)
{
    frmShowResult->g_pProject = g_pProject;
    frmShowResult->labTotal->Caption=AnsiString(g_pProject->m_nIteratTime);
    frmShowResult->Show();
}
//---------------------------------------------------------------------------



void __fastcall TfrmMainFrame::dxBarButton12Click(TObject *Sender)
{
frmAbout->Show();
}
//---------------------------------------------------------------------------
void  TfrmMainFrame::SendData()
{
     if(!m_bSendingData)return;
   AnsiString ls_msg;

        for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          ls_msg += myobj->m_strName+":"+FloatToStrF(myobj->m_dValue,ffFixed,1,0)+";";
        }
   AnsiString str;
   try
   {
      str = NMMsg1->PostIt(ls_msg);
   }
   catch (Exception &exception)
   {
     m_bSendingData = false;
   }
}
void __fastcall TfrmMainFrame::NMMSGServ1MSG(TComponent *Sender,
      const AnsiString sFrom, const AnsiString sMsg)
{
   AnsiString ls_msg = sMsg;
   if (sFrom == "ReasoningMachine")
   {
        if(ls_msg=="FAULT_HAPPEN")
        {
           m_bSendingData = false;
        }
        else if(ls_msg=="FAULT_CLEAR")
        {
           m_bSendingData = true;
        }
   }
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::NMMsg1ConnectionFailed(TObject *Sender)
{
     m_bSendingData= false;

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::NMMsg1InvalidHost(bool &Handled)
{
     m_bSendingData = false;
     Application->MessageBox("请输入正确的IP地址","提示",MB_OK);return;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::dxOpenDataBaseClick(TObject *Sender)
{
FormNS = new TFormNS(Application);
FormNS->Visible = true;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::dxBarButton2Click(TObject *Sender)   // 查询某一时间段内的数据，根据数据内的节点信息，让相应的节点闪烁
{
float p = 1;
TCanvas* tc = MainPaintBox->Canvas;
TdxBarEdit* tbe1 = frmMainFrame->dxBarEdit1;
String start = tbe1->Text;
TdxBarEdit* tbe2 = frmMainFrame->dxBarEdit2;
String end = tbe2->Text;
while(start.Length()<17&&end.Length()<17){
    if(start.Length()<17){
        start.Insert("0",start.Length()+1);
    }
    if(end.Length()<17){
        end.Insert("0",end.Length()+1);
    }
}
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
        {
          FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
          p = myobj->proportion;
        }
TADOConnection* tado = frmMainFrame->ADOConnection1;
tado->Open();
TADOQuery* tadoq = frmMainFrame->ADOQuery1;
tadoq->Close();
if(frmMainFrame->DatabaseSelected == 0){
tadoq->SQL->Text = "select * from simu where Time > "+start+" and Time < "+end+"";
}
else if(frmMainFrame->DatabaseSelected == 1){
tadoq->SQL->Text = "select * from reality where Time > "+start+" and Time < "+end+"";
}
tadoq->Open();
while(!tadoq->Eof){
String a=tadoq->FieldByName("Node")->AsString;
int node = StrToInt(a);
FCMsNode*myobj;
for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
    FCMsNode*obj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
    String s = obj->m_strName;
    s = s.SubString(2,s.Length()-1);
    if(s==node){
        myobj = obj;
        break;
    }
}
TRect rect;                                                             //让相应节点闪烁
rect.Left = (myobj->X-14-myobj->XOrientation)*myobj->proportion;
rect.Top = (myobj->Y-14- myobj->YOrientation)*myobj->proportion;
rect.right =(myobj->X+14- myobj->XOrientation)*myobj->proportion;
rect.Bottom = (myobj->Y+14- myobj->YOrientation)*myobj->proportion;
tc->Pen->Color = m_FCMsNodeUI.m_tcLinePenColor;
tc->Pen->Width =m_FCMsNodeUI.m_iLinePenWidth;
tc->Brush->Color = clRed;
tc->Ellipse(rect);
Sleep(200);
myobj->Draw(tc);
Application-> ProcessMessages();
tadoq->Next();
}
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxBarButton3Click(TObject *Sender)
{
frmMainFrame->DatabaseSelected = 0;
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxBarButton4Click(TObject *Sender)
{
frmMainFrame->DatabaseSelected = 1;
}
//---------------------------------------------------------------------------




void __fastcall TfrmMainFrame::dxBarButton5Click(TObject *Sender)
{
TFormSim *FormSim;
FormSim = new TFormSim(Application);           //添加路径
FormSim->Visible = true;

}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxBarButton6Click(TObject *Sender)
{
TFormEvac *FormEvac;
FormEvac = new TFormEvac(Application);
FormEvac->Visible = true;
}


//****************By WYP at 20140414***20140416***20140418****************************************************
void __fastcall TfrmMainFrame::MyRadioGroupClick(TObject *Sender) //对动态生成的单选按钮响应
{
     TRadioGroup* tlb=(TRadioGroup*)Sender;
     //ShowMessage(tlb->Items->Strings[tlb->ItemIndex]);
     //tlb->Caption="Clicked!";

     int node_index=StrToInt(tlb->Caption);  //读取当前选择的单选按钮组序号
     FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[node_index]; //读取当前单选按钮组代表的节点
     //myobj->GetCoveredNodes();   //读取该节点的覆盖范围列表
     myobj->m_pRouteList->Add(myobj);//将myobj节点本身添加进自己的路由表中
     FCMsNode*obj1=(FCMsNode*)myobj->m_pCoveredList->Items[tlb->ItemIndex]; //取出在该节点覆盖列表中被选中的那个节点
     if(!(obj1->IsInList(myobj->m_pRouteList)))
     {
        myobj->m_pRouteList->Add(obj1);
        //ShowMessage("节点"+obj1->m_strName+"添加成功！");
     }
     else
        ShowMessage("该节点已经在路由表中，请重新选择节点！");

     for(int k = 0;k<g_pProject->m_pFCMsNodeList->Count;k++)//******计算节点myobj到各个节点的路由******
     {
        FCMsNode*ob_obj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[k];//依次读取每一个节点
        while(myobj->m_pRouteList->Items[myobj->m_pRouteList->Count-1]!=ob_obj&&myobj!=ob_obj)//当没有找到回路的时候，则执行循环选择
        {
                FCMsNode*obj2=(FCMsNode*)myobj->m_pRouteList->Items[myobj->m_pRouteList->Count-1];//查找路由列表的最后一个节点，如果与列表所属节点不相同，则添加进路由表
                //TRadioGroup* tlb1 = (TRadioGroup*) ListForRTT->Items[obj->ID-1];  //读取被选节点所在的单选按钮组
                //tlb1=(TRadioGroup*)Sender;
                //FCMsNode*obj=(FCMsNode*)myobj->m_pCoveredList->Items[tlb1->ItemIndex]; //再次选择节点
                int index=random(obj2->m_pCoveredList->Count); //从当前节点的覆盖范围列表中随机选择一个节点作为路由表中的下一跳
                FCMsNode*obj3=(FCMsNode*)obj2->m_pCoveredList->Items[index];
                if(!(obj3->IsInList(myobj->m_pRouteList)))
                {
                        myobj->m_pRouteList->Add(obj3);
                        //ShowMessage("节点添加成功！");
                }
        }
        //myobj->m_pRouteList->Add(myobj);//将myobj节点本身添加进自己的路由表中，形成通信回路

        SetCurrentDir("D:\smart-environment-simulator20140308");
        Boolean file_exist=FileExists("RouteListFile.txt");
        int current_long=myobj->m_strName.Length();
        if(file_exist) //如果文件已经存在，则直接对文件进行写操作
        {
                //int file_open= FileOpen("D:\\smart-environment-simulator20140308\\RouteListFile.txt",fmOpenReadWrite|fmShareExclusive);
                //FileWrite(file_open,myobj->m_strName.c_str(),current_long);
                //FileClose(file_open);
                TStringList *txt=new TStringList;
                txt->LoadFromFile("D:\\smart-environment-simulator20140308\\RouteListFile.txt");
                txt->Add("************************");
                txt->Add("节点"+myobj->m_strName+"到"+ob_obj->m_strName+"的路由表是：");
                for(int i = 0;i<myobj->m_pRouteList->Count;i++)//******依次读取路由中的每个节点******
                {
                        FCMsNode*obj4=(FCMsNode*)myobj->m_pRouteList->Items[i];
                        txt->Add(obj4->m_strName);
                        txt->SaveToFile("D:\\smart-environment-simulator20140308\\RouteListFile.txt");
                        //int l=obj4->m_strName.Length();
                        //FileWrite(file_open,obj4->m_strName.c_str(),l);
                        //ShowMessage("路由表："+obj4->m_strName);
                }
                //FileClose(file_open);
                txt->Add("************************");
        }
        else   //如果文件不存在，则创建文件，再对文件进行写操作
        {
                int routefile=FileCreate("RouteListFile.txt");
                //int file_open=FileOpen("D:\\smart-environment-simulator20140308\\RouteListFile.txt",fmOpenReadWrite|fmShareExclusive);
                //FileWrite(file_open,myobj->m_strName.c_str(),current_long);
                //FileClose(file_open);
                TStringList *txt=new TStringList;
                txt->LoadFromFile("D:\\smart-environment-simulator20140308\\RouteListFile.txt");
                txt->Add("************************");
                txt->Add("节点"+myobj->m_strName+"到"+ob_obj->m_strName+"的路由是：");
                for(int i = 0;i<myobj->m_pRouteList->Count;i++)
                {
                        FCMsNode*obj4=(FCMsNode*)myobj->m_pRouteList->Items[i];
                        txt->Add(obj4->m_strName);
                        txt->SaveToFile("D:\\smart-environment-simulator20140308\\RouteListFile.txt");
                        //int l=obj4->m_strName.Length();
                        //FileWrite(file_open,obj4->m_strName.c_str(),l);
                        //ShowMessage("路由表："+obj4->m_strName);
                }
                //FileClose(file_open);
                txt->Add("************************");
        }

        //for(int i = 0;i<myobj->m_pRouteList->Count;i++)
        //{
        //   FCMsNode*obj4=(FCMsNode*)myobj->m_pRouteList->Items[i];
        //   ShowMessage("路由表："+obj4->m_strName);
        //}


        //myobj->m_pCoveredList->Clear();//将myobj节点的覆盖范围列表清空
        myobj->m_pRouteList->Clear();
        myobj->m_pRouteList->Add(myobj);
        myobj->m_pRouteList->Add(obj1);
    }
    ShowMessage("节点"+myobj->m_strName+"的路由表生成成功！");
}
//********************************************************************************************


//---------------------------------------------------------------------------
//**************By WYP at 20140330**********20140331****************************
void __fastcall TfrmMainFrame::dxBarButton11Click(TObject *Sender)     //RTT按钮
{
    ListForRTT = new TList;
   /*
    String maxID;
    TADOConnection* tado = frmMainFrame->ADOConnection1;
    tado->Open();
    TADOQuery* tadoq = frmMainFrame->ADOQuery1;
    tadoq->Close();
    tadoq->SQL->Text = "select * from reality where ID  in (select max(ID) from reality)";
    tadoq->Open();
    while(!tadoq->Eof)
    {
        maxID=tadoq->FieldByName("ID")->AsString; //取出ID号最大的那个节点
        tadoq->Next();
    }
    tadoq->Close();
    */
    for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)//******在每个节点的旁边添加一个单选按钮框******
    {
        FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];//依次读取每一个节点

        TRadioGroup* tlb = new TRadioGroup(this); //在每一个节点的后面添加一个文本框，用来显示节点覆盖范围列表
        tlb->Parent = MainPaintBox->Parent;
        tlb->Width = 60;      //设置文本框尺寸
        tlb->Height = 85;
        tlb->Left = (myobj->X+14- myobj->XOrientation)*myobj->proportion; //设置文本框位置
        tlb->Top = (myobj->Y-14- myobj->YOrientation)*myobj->proportion;
        tlb->Visible = true;
        tlb->Caption=myobj->ID-1;
        tlb->OnClick=MyRadioGroupClick;  //******点击单选按钮事件******
        ListForRTT->Add(tlb);  //将文本框添加到文本框列表中
    }
    for(int i=0;i<ListForRTT->Count;i++)//******在每个节点对应的文本框中显示覆盖范围列表******
    {
        TRadioGroup* tlb = (TRadioGroup*) ListForRTT->Items[i];  //依次读取每一个文本框
        FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i]; //依次读取每一个节点
        myobj->GetCoveredNodes();      //读取该节点可覆盖范围的列表
        for(int j=0;j<myobj->m_pCoveredList->Count;j++)
        {
                FCMsNode*obj=(FCMsNode*)myobj->m_pCoveredList->Items[j];
                tlb->Items->Add(obj->m_strName);
                //tlb->Caption=obj->m_strName;
        }
        //myobj->m_pCoveredList->Clear();//将myobj节点的覆盖范围列表清空



    }
        //tlb->Items->Add(maxID);
    while(this->fofrtt)
    {
        /*
        TADOConnection* tado = frmMainFrame->ADOConnection1;
        tado->Open();
        TADOQuery* tadoq = frmMainFrame->ADOQuery1;
        tadoq->Close();
        tadoq->SQL->Text = "select * from reality where Time > "+start+" and Time < "+end+"";
        tadoq->Open();
        while(!tadoq->Eof)
        {

        }
        */
        Application->ProcessMessages();
    }
    
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::dxBarButton15Click(TObject *Sender) //将通过点击RTT按钮显示的信息清空
{
        this->fofrtt = false;
        for(int i=0;i<ListForRTT->Count;i++)
        {
                //FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i]; //依次读取每一个节点
                TListBox* tlb = (TListBox*) ListForRTT->Items[i];
                tlb->~TListBox();  //调用析构函数清空数据列表
                FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i]; //依次读取每一个节点
                myobj->m_pCoveredList->Clear();//将myobj节点的覆盖范围列表清空
                myobj->m_pRouteList->Clear(); //将myobj节点的路由清空
        }
        //Application->MessageBoxA("节点覆盖范围计算已经结束！","提示",MB_OK);
}
//---------------------------------------------------------------------------
//************************************************************************************

void __fastcall TfrmMainFrame::Button1Click(TObject *Sender)
{
int n[12];
for(int i=0;i<12;i++){
    n[i] = 0;
}
String node;
String cnode;
int num = 0;
int j = 0;
FCMsNode*pobj;
TADOConnection* tado = frmMainFrame->ADOConnection1;
tado->Open();
TADOQuery* tadoq = frmMainFrame->ADOQuery1;
tadoq->Close();
tadoq->SQL->Text = "select * from simu";
tadoq->Open();
while(!tadoq->Eof&&j<20){
    node=tadoq->FieldByName("Node")->AsString;
    int i = StrToInt(node);
    i = i-3;
    FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
    frmMainFrame->ListBox1->Items->Add(myobj->m_strName);
    if(node==cnode||j==0){
        if(myobj->m_iType==1){
            num++;
            //frmMainFrame->ListBoxSim->Items->Add(IntToStr(j));
        }
        j++;
    }
    if(node!=cnode&&j==0){
        if(myobj->m_iType==1){
            if(pobj->m_iType==1){
                if(num=6&&pobj->m_strName=="m25"){
                    n[0]++;
                }
                else if(num=16&&pobj->m_strName=="m25"){
                    n[1]++;
                }
                else if(num=26&&pobj->m_strName=="m25"){
                    n[2]++;
                }
                else if(num=6&&pobj->m_strName=="m11"){
                    n[3]++;
                }
                else if(num=16&&pobj->m_strName=="m11"){
                    n[4]++;
                }
                else if(num=26&&pobj->m_strName=="m11"){
                    n[5]++;
                }
                else if(num=6&&pobj->m_strName=="m2"){
                    n[6]++;
                }
                else if(num=16&&pobj->m_strName=="m2"){
                    n[7]++;
                }
                else if(num=26&&pobj->m_strName=="m2"){
                    n[8]++;
                }
                else if(num=6&&pobj->m_strName=="m23"){
                    n[9]++;
                }
                else if(num=16&&pobj->m_strName=="m23"){
                    n[10]++;
                }
                else if(num=26&&pobj->m_strName=="m23"){
                    n[11]++;
                }
            }
            num=1;
        }
    }
    pobj = myobj;
    cnode = node;
    tadoq->Next();
}
tadoq->Close();
for(int i=0;i<12;i++){
    frmMainFrame->ListBox1->Items->Add(IntToStr(n[i]));
}
}
//---------------------------------------------------------------------------

void __fastcall TfrmMainFrame::Button2Click(TObject *Sender)
{
    for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        myobj->at = new TList;
        String s = myobj->m_strName;
        s = s.SubString(2,s.Length()-1);
        if(s == 12){
            myobj->at = new TList;
            NodeRecord* nr2 = new NodeRecord();
            nr2->node = myobj;
            nr2->count = 27;
            myobj->at->Add(nr2);
        }
        else if(s == 31){
            myobj->at = new TList;
            NodeRecord* nr2 = new NodeRecord();
            nr2->node = myobj;
            nr2->count = 27;
            myobj->at->Add(nr2);
        }
        else if(s == 19){
            myobj->at = new TList;
            NodeRecord* nr2 = new NodeRecord();
            nr2->node = myobj;
            nr2->count = 27;
            myobj->at->Add(nr2);
        }
        else if(s == 2){
            myobj->at = new TList;
            for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
                FCMsNode*mobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                String s = mobj->m_strName;
                s = s.SubString(2,s.Length()-1);
                if(s==13){
                    FCMsNode*pobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                    NodeRecord* nr2 = new NodeRecord();
                    nr2->node = pobj;
                    nr2->count = 27;
                    myobj->at->Add(nr2);
                }
            }
        }
        else if(s == 23){
            myobj->at = new TList;
            for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
                FCMsNode*mobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                String s = mobj->m_strName;
                s = s.SubString(2,s.Length()-1);
                if(s==24){
                    FCMsNode*pobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                    NodeRecord* nr2 = new NodeRecord();
                    nr2->node = pobj;
                    nr2->count = 27;
                    myobj->at->Add(nr2);
                }
            }
        }
        else if(s == 18){
            myobj->at = new TList;
            for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
                FCMsNode*mobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                String s = mobj->m_strName;
                s = s.SubString(2,s.Length()-1);
                if(s==19){
                    FCMsNode*pobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                    NodeRecord* nr1 = new NodeRecord();
                    nr1->node = pobj;
                    myobj->at->Add(nr1);
                }
            }
        }
        else if(s == 10){
            myobj->at = new TList;
            for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
                FCMsNode*mobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                String s = mobj->m_strName;
                s = s.SubString(2,s.Length()-1);
                if(s==18){
                    FCMsNode*pobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                    NodeRecord* nr1 = new NodeRecord();
                    nr1->node = pobj;
                    myobj->at->Add(nr1);
                }
            }
        }
        else if(s == 9){
            myobj->at = new TList;
            for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
                FCMsNode*mobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                String s = mobj->m_strName;
                s = s.SubString(2,s.Length()-1);
                if(s==10){
                    FCMsNode*pobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                    NodeRecord* nr1 = new NodeRecord();
                    nr1->node = pobj;
                    myobj->at->Add(nr1);
                }
            }
        }
        else if(s == 14){
            myobj->at = new TList;
            for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
                FCMsNode*mobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                String s = mobj->m_strName;
                s = s.SubString(2,s.Length()-1);
                if(s==12){
                    FCMsNode*pobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                    NodeRecord* nr1 = new NodeRecord();
                    nr1->node = pobj;
                    myobj->at->Add(nr1);
                }
            }
        }
        else if(s == 13){
            myobj->at = new TList;
            for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
                FCMsNode*mobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                String s = mobj->m_strName;
                s = s.SubString(2,s.Length()-1);
                if(s==14){
                    FCMsNode*pobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                    NodeRecord* nr1 = new NodeRecord();
                    nr1->node = pobj;
                    myobj->at->Add(nr1);
                }
            }
        }
        else if(s == 29){
            myobj->at = new TList;
            for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
                FCMsNode*mobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                String s = mobj->m_strName;
                s = s.SubString(2,s.Length()-1);
                if(s==31){
                    FCMsNode*pobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                    NodeRecord* nr1 = new NodeRecord();
                    nr1->node = pobj;
                    myobj->at->Add(nr1);
                }
            }
        }
        else if(s == 21){
            myobj->at = new TList;
            for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
                FCMsNode*mobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                String s = mobj->m_strName;
                s = s.SubString(2,s.Length()-1);
                if(s==29){
                    FCMsNode*pobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                    NodeRecord* nr1 = new NodeRecord();
                    nr1->node = pobj;
                    myobj->at->Add(nr1);
                }
            }
        }
        else if(s == 24){
            myobj->at = new TList;
            for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
                FCMsNode*mobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                String s = mobj->m_strName;
                s = s.SubString(2,s.Length()-1);
                if(s==21){
                    FCMsNode*pobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                    NodeRecord* nr1 = new NodeRecord();
                    nr1->node = pobj;
                    myobj->at->Add(nr1);
                }
            }
        }
        else if(s == 11){
            myobj->at = new TList;
            for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
                FCMsNode*mobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                String s = mobj->m_strName;
                s = s.SubString(2,s.Length()-1);
                if(s==9){
                    FCMsNode*pobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
                    NodeRecord* nr2 = new NodeRecord();
                    nr2->node = pobj;
                    nr2->count = 27;
                    myobj->at->Add(nr2);
                }
            }
        }
    }
    for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++){
        FCMsNode*myobj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
        if(myobj->at->Count!=0){
            frmMainFrame->ListBox1->Items->Add(myobj->m_strName);
            for(int i=0;i<myobj->at->Count;i++){
                NodeRecord*mobj = (NodeRecord*)myobj->at->Items[i];
                frmMainFrame->ListBox1->Items->Add(mobj->node->m_strName);
                frmMainFrame->ListBox1->Items->Add(IntToStr(mobj->count));
            }
        }
    }

}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------




static int originalnode=0;
static int originalid=0;
void __fastcall TfrmMainFrame::Timer1Timer(TObject *Sender)   //每间隔100毫秒钟触发一次
{

    String maxID;
    String id;
    String bat;
    String tem;
    String hum;
    String motion;
    int currentid;
    int currentnode;
    int currentmotion;

    TCanvas* tc = MainPaintBox->Canvas;
    ListForRTT = new TList;
    TList* pFCMsNodeList=g_pProject->m_pFCMsNodeList;
    FCMsNode*myobj;
    TADOConnection* tado = frmMainFrame->ADOConnection1;
    tado->Open();
    TADOQuery* tadoq = frmMainFrame->ADOQuery1;
    tadoq->Close();
    tadoq->SQL->Text = "select DataId,NodeAddress,Temperature,Humidity from sensorboard where NodeAddress=(select NodeAddress from sensormotion where DataId = (select max(DataId) from sensormotion) and MotionData!=0) order by DataId DESC limit 1"; //SQL语句查询sensorboard数据库表中的相应属性
    tadoq->Open();
    if(tadoq->IsEmpty())
       return;
    maxID=tadoq->FieldByName("NodeAddress")->AsString;
    id=tadoq->FieldByName("DataId")->AsString;
    currentnode = StrToInt(maxID);
    currentid = StrToInt(id);
    currentmotion = StrToInt(maxID);
    tem=tadoq->FieldByName("Temperature")->AsString;
    hum=tadoq->FieldByName("Humidity")->AsString;
    for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)   //依次搜索每个节点，寻找名称相符的那个节点
    {
           FCMsNode*obj = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
           String s = obj->m_strName;
           s = s.SubString(2,s.Length()-1);
           if(StrToInt(s) == currentnode)                                      //找到名称相符的节点，取出。
           {
              myobj = obj;
              break;
           }
    }
    if(myobj == NULL)
       return;
   TRect rect;
   if((currentnode!=originalnode) || (currentid!=originalid))//若下次接收的数据来自不同的节点，或来自相同的节点，但数据序号不同，则节点闪烁。
   {
         rect.Left = (myobj->X-14-myobj->XOrientation)*myobj->proportion;
         rect.Top = (myobj->Y-14- myobj->YOrientation)*myobj->proportion;
         rect.right =(myobj->X+14- myobj->XOrientation)*myobj->proportion;
         rect.Bottom = (myobj->Y+14- myobj->YOrientation)*myobj->proportion;
         tc->Pen->Color = m_FCMsNodeUI.m_tcLinePenColor;
         tc->Pen->Width =m_FCMsNodeUI.m_iLinePenWidth;
         tc->Brush->Color = clRed;
         tc->Ellipse(rect);
         tc->TextOutA(myobj->X+14- myobj->XOrientation,myobj->Y-20- myobj->YOrientation,"温度为:");
         tc->TextOutA(myobj->X+66- myobj->XOrientation,myobj->Y-20- myobj->YOrientation,tem);
         tc->TextOutA(myobj->X+14- myobj->XOrientation,myobj->Y+12- myobj->YOrientation,"湿度为:");
         tc->TextOutA(myobj->X+66- myobj->XOrientation,myobj->Y+12- myobj->YOrientation,hum);
         Sleep(100);
         myobj->Draw(tc);
         tc->Refresh();
         //Application-> ProcessMessages();
         //tadoq->Next();
   }
   originalnode=currentnode;   //更新上条数据的序号，以及其来源的节点号，以便与下条数据进行比较，确定是否有新数据传来。
   originalid=currentid;
}
//---------------------------------------------------------------------------





void __fastcall TfrmMainFrame::Button3Click(TObject *Sender)
{
    this->Timer1->Enabled=true;
}
//---------------------------------------------------------------------------















void __fastcall TfrmMainFrame::dxBarButton18Click(TObject *Sender)
{
    this->Timer1->Enabled=true;
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::dxBarButton16Click(TObject *Sender) //进行活动迁移
{
      vector<double>MaxSim;
      vector<int>MaxSimIndex;
      TList *TempList=new TList;
      double FinalSim=0;
      int FinalIndex;
      double Threshold=0;//轨迹相似度阈值
      mytxt=new TStringList;
      for(int i = 0;i<g_pProject->m_pFCMsNodeList->Count;i++)
      {
            FCMsNode*obj1 = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[i];
            for(int j = 0;j<g_pProject->m_pFCMsNodeList->Count;j++)
            {
                  FCMsNode*obj2 = (FCMsNode*)g_pProject->m_pFCMsNodeList->Items[j];
                  if(obj1!=obj2)
                  {
                        FinalSim=0;
                        obj1->GetRandRoute(obj2);
                        for(int k=0;k<frmMainFrame->RouteOfTemp.capacity();k++)
                        {
                                TempList=frmMainFrame->RouteOfTemp.at(k);
                                double sim=g_pProject->Similarity(obj1->m_pBrief_RandRoute,TempList);
                                //Similarity(obj1->m_pBrief_RandRoute,TempList);
                                if(sim>FinalSim)
                                {
                                      FinalSim=sim;
                                      FinalIndex=k;
                                }
                                TempList->Clear();
                        }
                        if(FinalSim>Threshold)
                        {
                                SetCurrentDir("D:\smart-environment-simulator20140308");
                                Boolean file_exist=FileExists("Trajectory_Mapping.txt");
                                if(file_exist) //如果文件已经存在，则直接对文件进行写操作
                                {
                                       mytxt->LoadFromFile("D:\\smart-environment-simulator20140308\\Trajectory_Mapping.txt");
                                       mytxt->Add("************************");
                                       mytxt->Add("节点"+obj1->m_strName+"到节点"+obj2->m_strName+"的路径是：");
                                       for(int i = 0;i<obj1->m_pBrief_RandRoute->Count;i++)
                                       {
                                                FCMsNode*obj=(FCMsNode*)obj1->m_pBrief_RandRoute->Items[i];
                                                mytxt->Add(obj->m_strName);
                                       }
                                       mytxt->SaveToFile("D:\\smart-environment-simulator20140308\\Trajectory_Mapping.txt");
                                       mytxt->Clear();
                                }
                                else   //如果文件不存在，则创建文件，再对文件进行写操作
                                {
                                       int routefile=FileCreate("Trajectory_Mapping.txt");
                                       mytxt->LoadFromFile("D:\\smart-environment-simulator20140308\\Trajectory_Mapping.txt");
                                       mytxt->Add("************************");
                                       mytxt->Add("节点"+obj1->m_strName+"到节点"+obj2->m_strName+"的路径是：");
                                       for(int i = 0;i<obj1->m_pBrief_RandRoute->Count;i++)
                                       {
                                                FCMsNode*obj=(FCMsNode*)obj1->m_pBrief_RandRoute->Items[i];
                                                mytxt->Add(obj->m_strName);
                                       }
                                       mytxt->SaveToFile("D:\\smart-environment-simulator20140308\\Trajectory_Mapping.txt");
                                       mytxt->Clear();
                                }
                         }//end if
                         obj1->m_pBrief_RandRoute->Clear();
                         obj1->m_pRandRoute->Clear();
                  }//end if
            }//end for
      }//end for
}
//---------------------------------------------------------------------------


void __fastcall TfrmMainFrame::dxBarButton20Click(TObject *Sender)
{
        TForm1 *Form1;
        Form1 = new TForm1(Application);
        Form1->Visible = true;

}
//---------------------------------------------------------------------------
void __fastcall TfrmMainFrame::dxBarButton21Click(TObject *Sender)
{
        TForm2 *Form2;
        Form2 = new TForm2(Application);
        Form2->Visible = true;
}
//---------------------------------------------------------------------------
