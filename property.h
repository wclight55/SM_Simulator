//---------------------------------------------------------------------------


#ifndef propertyH
#define propertyH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include "dxCntner.hpp"
#include "dxDBInsp.hpp"
#include "dxExEdtr.hpp"
#include "dxInspct.hpp"
#include <ComCtrls.hpp>
#include <ExtCtrls.hpp>
#include "dxInspRw.hpp"
#include <Dialogs.hpp>

#include "UIProject.h"
//---------------------------------------------------------------------------
class TFrameProperty : public TFrame
{
__published:	// IDE-managed Components
	TdxInspector *dxInspector;
	TdxInspectorTextRow *rowNode;
	TTreeView *TreeViewProject;
	TSplitter *Splitter1;
	TLabel *Label1;
	TdxInspectorTextRow *rowUI;
	TdxInspectorTextRow *rowCommon;
	TdxInspectorTextButtonRow *rowUIFontColor;
	TdxInspectorTextButtonRow *rowUIBrushColor;
	TdxInspectorTextButtonRow *rowUILineColor;
	TdxInspectorTextRow *rowProject;
	TdxInspectorTextRow *rowProjectAuthor;
	TColorDialog *ColorDialog;
	TdxInspectorTextSpinRow *rowUIFontSize;
	TdxInspectorTextSpinRow *rowUILineWidth;
	TOpenDialog *OpenDialog;
	TdxInspectorTextRow *rowCommonName;
	TdxInspectorTextRow *rowCommonDescription;
        TdxInspectorTextRow *rowTriggerRange;
        TdxInspectorTextRow *rowVariance;
        TdxInspectorTextRow *rowLine;
        TdxInspectorTextRow *rowDistance;
        TdxInspectorTextRow *rowCoveredList_Count;
        TdxInspectorTextPickRow *dxrowSensorType;
        TdxInspectorTextPickRow *dxrowCoverList; //覆盖范围列表下拉框
  TdxInspectorTextRow *rowUnitDistance;
  TdxInspectorTextRow *rowIteratTime;
  TdxInspectorTextRow *rowLambda;
  TdxInspectorTextRow *rowSamplingTime;
  TdxInspectorTextRow *rowWalkingSpeed;
        TdxInspectorTextPickRow *dxrowPosition;
        TdxInspectorTextRow *rowInfluence;
  //****************************

        void __fastcall TreeViewProjectClick(TObject *Sender);
	void __fastcall dxInspectorEdited(TObject *Sender, TdxInspectorNode *Node,
          TdxInspectorRow *Row);
	void __fastcall rowUIBrushColorButtonClick(TObject *Sender,
          int AbsoluteIndex);
	void __fastcall rowUILineColorButtonClick(TObject *Sender,
          int AbsoluteIndex);
	void __fastcall rowUIFontColorButtonClick(TObject *Sender,
          int AbsoluteIndex);
	void __fastcall rowUILineWidthChange(TObject *Sender);
  void __fastcall TreeViewProjectDblClick(TObject *Sender);
	void __fastcall dxInspectorEnter(TObject *Sender);
private:
	TList* m_pSelectedList;
	void ShowRowsByName(TStringList* a_pStringList);
	void HideRowsNotInNames(TStringList* a_pStringList);
	void ShowAllProperty();
	void ChangeRowsBySourceType();
public:		// User declarations
	__fastcall TFrameProperty(TComponent* Owner);
	void RefreshProjectTree();
	void RefreshProperty();
	void HideAllProperty();
	TTreeNode* FindNodeByData(void* pObj);
	void ChangeTreeNodeText(TObject* a_pObj, String a_strNewText);
	void OnPropertyChange(TdxInspectorRow* Row);
	void SetUIFromProperty(UI &a_UI, TdxInspectorRow *Row);
	void SetUIProperty(UI a_UI);
	void EditExpression();
	void DeleteSelectedFromTree();
	void AddSelectedToTree();
	virtual __fastcall ~TFrameProperty();
	void ChangeTreeSelectStatus();
};
//---------------------------------------------------------------------------
extern void AddSelectedToTree();
extern void DeleteSelectedFromTree();
extern PACKAGE TFrameProperty *FrameProperty;


//---------------------------------------------------------------------------
#endif
