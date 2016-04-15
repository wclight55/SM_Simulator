//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("Output.cpp", FrameOutput); /* TFrame: File Type */
USEFORM("property.cpp", FrameProperty); /* TFrame: File Type */
USEFORM("MainFrame.cpp", frmMainFrame);
USEFORM("BelongFunction.cpp", frm_BelongFunction);
USEFORM("RelationShip.cpp", tf_relationship);
USEFORM("Find.cpp", frmFind);
USEFORM("ShowResult.cpp", frmShowResult);
USEFORM("About.cpp", frmAbout);
USEFORM("UnitSim.cpp", FormSim);
USEFORM("UnitEvac.cpp", FormEvac);
USEFORM("UnitSim2.cpp", FormSim2);
USEFORM("Unit.cpp", FormNS);
USEFORM("Transfer.cpp", Form1);
USEFORM("CreatPattern.cpp", Form2);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
        try
        {
                 Application->Initialize();
                 Application->CreateForm(__classid(TfrmMainFrame), &frmMainFrame);
                 Application->CreateForm(__classid(Tfrm_BelongFunction), &frm_BelongFunction);
                 Application->CreateForm(__classid(Ttf_relationship), &tf_relationship);
                 Application->CreateForm(__classid(TfrmFind), &frmFind);
                 Application->CreateForm(__classid(TfrmShowResult), &frmShowResult);
                 Application->CreateForm(__classid(TfrmAbout), &frmAbout);
                 Application->Run();
        }
        catch (Exception &exception)
        {
                 Application->ShowException(&exception);
        }
        catch (...)
        {
                 try
                 {
                         throw Exception("");
                 }
                 catch (Exception &exception)
                 {
                         Application->ShowException(&exception);
                 }
        }
        return 0;
}
//---------------------------------------------------------------------------
