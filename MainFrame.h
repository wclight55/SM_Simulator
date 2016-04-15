//----------------------------------------------------------------------------
#ifndef MainFrameH
#define MainFrameH
//----------------------------------------------------------------------------
#include <DBGrids.hpp>
#include <vcl\ComCtrls.hpp>
#include <vcl\ExtCtrls.hpp>
#include <vcl\Buttons.hpp>
#include <vcl\StdCtrls.hpp>
#include <vcl\Dialogs.hpp>
#include <vcl\Menus.hpp>
#include <vcl\Controls.hpp>
#include <vcl\Forms.hpp>
#include <vcl\Graphics.hpp>
#include <vcl\Classes.hpp>
#include <vcl\Windows.hpp>
#include <vcl\System.hpp>
#include <ActnList.hpp>
#include <ImgList.hpp>
#include <StdActns.hpp>
#include <ToolWin.hpp>
#include <ADODB.hpp>
#include "dxBar.hpp"
#include "dxBarExtItems.hpp"
#include "Output.h"
#include "NodeEvent.h"
#include "UIProject.h"
#include "SelectRect.h"
#include <msxmldom.hpp>
#include <XMLDoc.hpp>
#include <xmldom.hpp>
#include <XMLIntf.hpp>
#include "dxCntner.hpp"
#include "dxExEdtr.hpp"
#include "dxInspct.hpp"
#include "property.h"
#include "Simulator.h"
#include "ReasonMachine.h"
#include "dxInspRw.hpp"
#include <NMMSG.hpp>
#include <Psock.hpp>
#include <DB.hpp>
//#include "GIFImage.hpp "

#include <Grids.hpp>
#include<math.h>
#include<io.h>

extern UIProject*g_pProject;


//----------------------------------------------------------------------------
class TfrmMainFrame : public TForm
{
__published:
  TOpenDialog *OpenDialog;
  TSaveDialog *SaveDialog;
  TActionList *ActionList1;
  TAction *FileNew;
  //TAction *FileOpen;
  TAction *FileSave;
  TAction *FileSaveAs;
  TAction *FileExit;
  TEditCut *EditCut;
  TEditCopy *EditCopy;
  TEditPaste *EditPaste;
  TAction *HelpAbout;
  TStatusBar *StatusBar;
  TAction *ModelDataSet;
	TAction *ModeDBSource;
	TImageList *Images;
	TdxBarManager *dxBarManager;
	TdxBarSubItem *siFile;
	TdxBarSubItem *siEdit;
	TdxBarSubItem *siView;
	TdxBarSubItem *siWindow;
	TdxBarSubItem *siHelp;
	TdxBarButton *btnNewBlankModal;
	TdxBarButton *btnOpen;
	TdxBarButton *btnClose;
	TdxBarButton *btnSave;
	TdxBarButton *btnPrintPreview;
	TdxBarButton *btnPrint;
	TdxBarButton *btnPrintSetup;
	TdxBarButton *btnProperties;
	TdxBarButton *btnExit;
	TdxBarButton *btnCut;
	TdxBarButton *btnCopy;
	TdxBarButton *btnPaste;
	TdxBarButton *btnDelete;
	TdxBarButton *dxBarButton1;
	TdxBarButton *btnFind;
	TdxBarCombo *cbZoom;
	TdxBarButton *btnZoom100;
	TdxBarButton *btnFitToWindow;
	TdxBarButton *btnNormal;
	TdxBarSubItem *siToolBars;
	TdxBarFontNameCombo *cbFontName;
	TdxBarCombo *cnFontSize;
	TdxBarCombo *cbStyle;
	TdxBarButton *btnBold;
	TdxBarButton *btnItalic;
	TdxBarButton *btnUnderline;
	TdxBarButton *btnFontColor;
	TdxBarButton *btnHightlight;
	TdxBarButton *btnNewWindow;
	TdxBarButton *btnArrangeAll;
	TdxBarButton *btnSplit;
	TdxBarButton *btnNextWindow;
	TdxBarButton *btnPreviousWindow;
	TdxBarButton *dxBarButton7;
	TdxBarButton *dxBarButton8;
	TdxBarButton *dxBarButton9;
	TdxBarButton *dxBarButton10;
	TdxBarButton *dxBarButton12;
	TdxBarButton *dxBarButton13;
	TdxBarButton *dxBarButton14;
	TFontDialog *FontDialog;
	TPanel *PanelMain;
	TPanel *PanelBottom;
        TdxBarButton *btnFCMsNode;
	TPanel *PanelTop;
	TSplitter *Splitter1;
	TPanel *PanelPaint;
	TPanel *PanelLeft;
	TSplitter *Splitter2;
        TPopupMenu *PopupMenu1;
  TdxBarButton *btnAddLine;
	TFrameOutput *FrameOutput;
	TFrameProperty *FrameProperty;
        TXMLDocument *XMLDocument1;
  TPaintBox *MainPaintBox;
  TScrollBar *srb_v;
  TScrollBar *srb_h;
  TdxBarButton *dxBarCheckValid;
  TPrintDialog *PrintDialog1;
  TdxBarButton *btnCursor;
  TdxBarButton *dxReason;
  TdxBarButton *dxSimulate;
  TdxBarSubItem *dxBarSubItem1;
  TdxBarButton *dxCheckValueofFCMs;
  TdxBarButton *dxLeft;
  TdxBarButton *dxRight;
  TdxBarButton *dxTop;
  TdxBarButton *dxBottome;
  TdxBarButton *dxSort;
  TdxBarButton *dxBarViewControl;
        TdxBarButton *dxSimulatStep;
        TdxBarButton *dxStopSimulate;
        TdxBarButton *dxPause;
        TdxBarButton *dxOpenLayout;
        TdxBarButton *dxVisual;
        TNMMsg *NMMsg1;
        TNMMSGServ *NMMSGServ1;
        TdxBarButton *dxOpenDataBase;
        TADOConnection *ADOConnection1;
        TADOQuery *ADOQuery1;
        TADOTable *ADOTable1;
        TdxBarEdit *dxBarEdit1;
        TdxBarButton *dxBarButton2;
        TdxBarEdit *dxBarEdit2;
        TImage *Image3;
        TdxBarButton *dxBarButton3;
        TdxBarButton *dxBarButton4;
        TdxBarButton *dxBarButton5;
        TListBox *ListBoxSim;
        TdxBarCombo *dxBarCombo1;
        TListBox *ListBox1;
        TdxBarButton *dxBarButton6;
        TdxBarCombo *dxBarCombo2;
        TdxBarButton *dxBarButton11;
        TdxBarButton *dxBarButton15;
        TButton *Button1;
        TButton *Button2;
        TTimer *Timer1;
        TdxBarButton *dxBarButton16;
        TdxBarButton *dxBarButton17;
        TdxBarButton *dxBarButton18;
        TdxBarButton *dxBarButton19;
        TdxBarButton *dxBarButton20;
        TdxBarButton *dxBarButton21;

  void __fastcall FileNewExecute(TObject *Sender);
  void __fastcall FileOpenExecute(TObject *Sender);
  void __fastcall FileSaveExecute(TObject *Sender);
  void __fastcall FileExitExecute(TObject *Sender);
  void __fastcall MainPaintBoxPaint(TObject *Sender);
  void __fastcall FormCreate(TObject *Sender);
  void __fastcall FormDestroy(TObject *Sender);
	void __fastcall PanelLeftDockOver(TObject *Sender,
          TDragDockObject *Source, int X, int Y, TDragState State,
          bool &Accept);
	void __fastcall PanelBottomDockOver(TObject *Sender,
          TDragDockObject *Source, int X, int Y, TDragState State,
          bool &Accept);
	void __fastcall btnNormalClick(TObject *Sender);
	void __fastcall Splitter2Moved(TObject *Sender);
	void __fastcall Splitter2CanResize(TObject *Sender, int &NewSize,
          bool &Accept);
	void __fastcall Splitter1CanResize(TObject *Sender, int &NewSize,
          bool &Accept);
	void __fastcall Splitter1Moved(TObject *Sender);
	void __fastcall FramePropertyEndDock(TObject *Sender, TObject *Target,
          int X, int Y);
        void __fastcall MainPaintBoxMouseDown(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
        void __fastcall btnFCMsNodeClick(TObject *Sender);
        void __fastcall btnAddLineClick(TObject *Sender);
        void __fastcall MainPaintBoxMouseMove(TObject *Sender,
          TShiftState Shift, int X, int Y);
        void __fastcall PanelPaintResize(TObject *Sender);
        void __fastcall MainPaintBoxMouseUp(TObject *Sender,
          TMouseButton Button, TShiftState Shift, int X, int Y);
	void __fastcall FrameOutputEndDock(TObject *Sender, TObject *Target,
          int X, int Y);
        void __fastcall btnDeleteClick(TObject *Sender);
        void __fastcall dxBarButton1Click(TObject *Sender);
        void __fastcall btnCopyClick(TObject *Sender);
        void __fastcall btnPasteClick(TObject *Sender);
        void __fastcall cbZoomChange(TObject *Sender);
        void __fastcall MainPaintBoxDblClick(TObject *Sender);
        void __fastcall btnSaveClick(TObject *Sender);
  void __fastcall btnOpenClick(TObject *Sender);
  void __fastcall cbZoomKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
  void __fastcall srb_vChange(TObject *Sender);
  void __fastcall srb_hChange(TObject *Sender);
  void __fastcall dxBarCheckValidClick(TObject *Sender);
  void __fastcall btnFitToWindowClick(TObject *Sender);
  void __fastcall btnPrintClick(TObject *Sender);
  void __fastcall FramePropertyTreeViewProjectClick(TObject *Sender);
  void __fastcall FrameOutputMemo1Click(TObject *Sender);
  void __fastcall MainPaintBoxClick(TObject *Sender);
  void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
  void __fastcall btnCursorClick(TObject *Sender);
  void __fastcall btnNewBlankModalClick(TObject *Sender);
  void __fastcall dxReasonClick(TObject *Sender);
  void __fastcall dxSimulateClick(TObject *Sender);
  void __fastcall dxCheckValueofFCMsClick(TObject *Sender);
  void __fastcall dxLeftClick(TObject *Sender);
  void __fastcall dxRightClick(TObject *Sender);
  void __fastcall dxTopClick(TObject *Sender);
  void __fastcall dxBottomeClick(TObject *Sender);
  void __fastcall dxSortClick(TObject *Sender);
  void __fastcall btnCloseClick(TObject *Sender);
  void __fastcall btnExitClick(TObject *Sender);
  void __fastcall btnFindClick(TObject *Sender);
  void __fastcall dxBarViewControlClick(TObject *Sender);
        void __fastcall dxSimulatStepClick(TObject *Sender);
        void __fastcall dxPauseClick(TObject *Sender);
        void __fastcall dxStopSimulateClick(TObject *Sender);
        void __fastcall dxOpenLayoutClick(TObject *Sender);
        void __fastcall dxVisualClick(TObject *Sender);
        void __fastcall dxBarButton12Click(TObject *Sender);
        void __fastcall NMMSGServ1MSG(TComponent *Sender,
          const AnsiString sFrom, const AnsiString sMsg);
        void __fastcall NMMsg1ConnectionFailed(TObject *Sender);
        void __fastcall NMMsg1InvalidHost(bool &Handled);
        void __fastcall dxOpenDataBaseClick(TObject *Sender);
        void __fastcall dxBarButton2Click(TObject *Sender);
        void __fastcall dxBarButton3Click(TObject *Sender);
        void __fastcall dxBarButton4Click(TObject *Sender);
        void __fastcall dxBarButton5Click(TObject *Sender);
        void __fastcall dxBarButton6Click(TObject *Sender);
        void __fastcall dxBarButton11Click(TObject *Sender);
        void __fastcall dxBarButton15Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        //***************By WYP at 20140414********************************************
        void __fastcall MyRadioGroupClick(TObject *Sender);
        void __fastcall dxBarButton18Click(TObject *Sender);
        void __fastcall dxBarButton16Click(TObject *Sender);
        void __fastcall dxBarButton20Click(TObject *Sender);
        void __fastcall dxBarButton21Click(TObject *Sender); //对动态生成的单选按钮响应
        //*****************************************************************************
private:
	int m_nFramePropertyWidth,m_nFrameOutputHeight;
        //int Form1Exsit;
public:
	virtual __fastcall TfrmMainFrame(TComponent *AOwner);
	void __fastcall AppException(TObject * Sender, Exception * E);
public:
        TSelectRect* m_selectRect;
        Boolean m_bEditCanvas;
        Simulator*m_pSimulator;
        Graphics::TBitmap* graphic;
        bool m_bSendingData;
        bool flag;
        bool fofrtt;
        int DatabaseSelected;
        int num;
        TList* route1;
        TList* route2;
        TList* route3;
        TList* route4;
//******By WYP at 20150426************
        TList* route5;
        TList* route6;
        TList* route7;
        TList* route8;
        TList* route9;
//************************************
        TList* ListForRTT;
        vector<TList*>RouteOfTemp; //存放已有的活动模式
        TStringList *mytxt;
private:
				Graphics::TBitmap *bmp;

				POINT   p_start,p_end;
				long Current_X,Current_Y;
				TColor backColor;
				Boolean m_bMouseMove;
				Boolean m_bCopy;
        ReasonMachine*m_pReasonMachine;
        AnsiString m_SensorHist;
        AnsiString m_UserHist;
public:
        void Refresh();
        void SaveCommand();
        void SaveCommandAs();
        void NodeInCenter(NodeEvent*pNode);
        void ViewIsChanged();
        void __fastcall PrintPage(int page);
        void InitialProject();
        void ClearProject();
        void SendData();
};
//----------------------------------------------------------------------------
extern TfrmMainFrame *frmMainFrame;
extern void AddErrorMessage(AnsiString str,TObject* pObj);
extern void AddSimulatingOutput(AnsiString str,TObject* pObj);

extern void ClearErrorMessages();
extern void ClearSimulatingOutput();

extern void AddSearchResult(AnsiString str,TObject* pObj);
extern void ClearSearchResult();

//----------------------------------------------------------------------------
#endif
