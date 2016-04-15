//---------------------------------------------------------------------------

#ifndef UnitSimH
#define UnitSimH
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
//---------------------------------------------------------------------------
class TFormSim : public TForm
{
__published:	// IDE-managed Components
        TLabel *Label1;
        TListBox *ListBox1;
        TLabel *Label2;
        TListBox *ListBox2;
        TListBox *ListBox3;
        TLabel *Label4;
        TButton *Button1;
        //TButton *Button3;
        TButton *Button4;
        TButton *Button2;
        TButton *Button5;
        TButton *Button6;
        TButton *Button7;
        TButton *Button8;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
        void __fastcall Button5Click(TObject *Sender);
        void __fastcall Button6Click(TObject *Sender);
        void __fastcall Button7Click(TObject *Sender);
        void __fastcall Button8Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TFormSim(TComponent* Owner);
        int num;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormSim *FormSim;
//---------------------------------------------------------------------------
#endif
