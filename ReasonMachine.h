#ifndef ReasonMachineH
#define ReasonMachineH

#include "NodeEvent.h"
#include "UIProject.h"
#include <Classes.hpp>
#include <SyncObjs.hpp>
#include "matrix.h"
extern UIProject*g_pProject;
//
class ReasonMachine : public TObject
{
protected:
    void __fastcall GetCanBeginWorkRuleSetList();
    void __fastcall BeginWork();
    void __fastcall GetRootNodesList();
    NodeEvent* __fastcall GetBeginNode();
    void __fastcall GetParentChild();

    void ConstructMatrix(Matrix *FCMsM);
    void GetValueOfFCMs(Matrix &FCMsM);
    void SetValueOfFCMs(Matrix&FCMsM);
    void ThresholdFCMs(Matrix&FCMsM);
    int HasCircle();//
private:
    FCMsNode*m_pReasonObj;//
    NodeEvent*m_pReasonNode;//
    UIProject*m_pProject;//
public:
    __fastcall ReasonMachine();
    virtual __fastcall ~ReasonMachine();
    void __fastcall Calculate();

    TList*m_pFCMsHistory;//
    int m_HasCircle;//
};
#endif
