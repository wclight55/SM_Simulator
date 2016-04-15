//---------------------------------------------------------------------------

#ifndef RelationShipH
#define RelationShipH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Grids.hpp>
#include "ReasonMachine.h"
//---------------------------------------------------------------------------
class Ttf_relationship : public TForm
{
__published:	// IDE-managed Components
        TStringGrid *ts_relation;
  void __fastcall FormShow(TObject *Sender);
  void __fastcall ts_relationDrawCell(TObject *Sender, int ACol, int ARow,
          TRect &Rect, TGridDrawState State);
private:	// User declarations

public:		// User declarations
        __fastcall Ttf_relationship(TComponent* Owner);
        void SetRelation();
         void FillGrid();
   TList*m_pHistory;
   int m_HasCircle;//
};
//---------------------------------------------------------------------------
extern PACKAGE Ttf_relationship *tf_relationship;
//---------------------------------------------------------------------------
#endif
