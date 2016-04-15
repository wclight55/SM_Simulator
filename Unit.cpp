//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormNS *FormNS;
//---------------------------------------------------------------------------
__fastcall TFormNS::TFormNS(TComponent* Owner)
        : TForm(Owner)
{
this->DataSelected = 0;
ListBox1->Items->Add("1");
ListBox1->Items->Add("2");
ListBox1->Items->Add("3");
ListBox1->Items->Add("4");
ListBox1->Items->Add("5");
ListBox1->Items->Add("6");
ListBox1->Items->Add("7");
ListBox1->Items->Add("8");
ListBox1->Items->Add("9");
}
//---------------------------------------------------------------------------

void __fastcall TFormNS::Button1Click(TObject *Sender)
{
Chart1->RemoveAllSeries();
//Series3->Clear();
ADOConnection1->Open();
ADOQuery1->Close();
String start = Edit1->Text;
String end = Edit2->Text;
while(start.Length()<17&&end.Length()<17){
    if(start.Length()<17){
        start.Insert("0",start.Length()+1);
    }
    if(end.Length()<17){
        end.Insert("0",end.Length()+1);
    }
}
int t = 0;
String target;
String text;
for(int i=0;i<ListBox1->Items->Count;i++){
    if(ListBox1->Selected[i]){
        target = ListBox1->Items->Strings[i];
        t = StrToInt(target);
        if(this->DataSelected ==0){
        text = "select * from simu where Time>"+start+" and Time<"+end+" and Node = "+t+"";
        //ADOQuery1->SQL->Text = "select * from simu where Time>"+start+" and Time<"+end+" and Node = "+t+"";
        }
        else if(this->DataSelected ==1){
        text = "select * from reality where Time>"+start+" and Time<"+end+" and Node = "+t+"";
        //ADOQuery1->SQL->Text = "select * from reality where Time>"+start+" and Time<"+end+" and Node = "+t+"";
        }
        ADOQuery1->SQL->Text = text;
        ADOQuery1->Open();
        while(!ADOQuery1->Eof)
        {
            String time = ADOQuery1->FieldByName("Time")->AsString;
            time = time.SubString(9,4);
            String hour = time.SubString(1,2);
            String minute = time.SubString(3,2);
            float h = StrToFloat(hour);
            float m = StrToFloat(minute);
            m = m/60;
            h = h+m;
            float j;
            String temp = FormatFloat("0.00",h);
            j = StrToFloat(temp);
            TFastLineSeries *series;
            series = new TFastLineSeries(this);
            series->ParentChart = Chart1;
            series->LinePen->Color = clRed;
            series->AddXY(j,0,"",clRed);
            series->AddXY(j,1,"",clRed);
            //Series3->LinePen->Color = clRed;
            //Series3->AddXY(j,1,"",clRed);
            //Series3->AddXY(j,1,"",clRed);
            //MessageBox(NULL,temp.c_str(),"ÌבÊ¾",MB_OK);
            //Series2->AddX(j,"",clRed);
            ADOQuery1->Next();
        }
    }
}
}
//---------------------------------------------------------------------------
void __fastcall TFormNS::Button2Click(TObject *Sender)
{
this->DataSelected = 0;
}
//---------------------------------------------------------------------------

void __fastcall TFormNS::Button3Click(TObject *Sender)
{
this->DataSelected = 1;
}
//---------------------------------------------------------------------------

void __fastcall TFormNS::Button4Click(TObject *Sender)
{
Series1->Clear();
ADOConnection1->Open();
ADOQuery1->Close();
ADOQuery2->Close();
float a = 0;
float b = 0;
String s = Edit1->Text;
for(int i=0;i<24;i++){
    a = 0;
    b = 0;
    String start = s;
    String end = s;
    String target;
    int t;
    if(i<=8){
        start = start+"0";
        start = start+IntToStr(i);
        end = end+"0";
        end = end+IntToStr(i+1);
    }
    else if(i==9){
        start = start+"0";
        start = start+IntToStr(i);
        end = end+IntToStr(i+1);
    }
    else{
        start = start+IntToStr(i);
        end = end+IntToStr(i+1);
    }
    while(start.Length()<17&&end.Length()<17){
        if(start.Length()<17){
            start.Insert("0",start.Length()+1);
        }
        if(end.Length()<17){
            end.Insert("0",end.Length()+1);
        }
    }
    for(int j=0;j<ListBox1->Items->Count;j++){
        if(ListBox1->Selected[j]){
            target = ListBox1->Items->Strings[j];
            t = StrToInt(target);
            }
    }
    if(this->DataSelected ==0){
        ADOQuery1->SQL->Text = "select * from simu where Time>"+start+" and Time<"+end+" and Node = "+t+"";
        ADOQuery1->Open();
        while(!ADOQuery1->Eof){
            a++;
            ADOQuery1->Next();
        }
        ADOQuery2->SQL->Text = "select * from simu where Time>"+start+" and Time<"+end+"";
        ADOQuery2->Open();
        while(!ADOQuery2->Eof){
            b++;
            ADOQuery2->Next();
        }
        if(b==0){
            b++;
         }
        /*TBarSeries *series;
        series = new TBarSeries(this);
        series->BarPen->Width = 30;
        series->BarPen->Color = clRed;
        series->ParentChart = Chart2;
        series->AutoBarSize = false;
        series->BarWidthPercent = 1;
        series->AddXY(i,a/b,"",clRed);*/
        Series1->AddXY(i,a/b,"",clRed);
    }
    else if(this->DataSelected ==1){
        ADOQuery1->SQL->Text = "select * from reality where Time>"+start+" and Time<"+end+" and Node = "+t+"";
        ADOQuery1->Open();
        while(!ADOQuery1->Eof){
            a++;
            ADOQuery1->Next();
        }
        ADOQuery2->SQL->Text = "select * from reality where Time>"+start+" and Time<"+end+"";
        ADOQuery2->Open();
        while(!ADOQuery2->Eof){
            b++;
            ADOQuery2->Next();
        }
        if(b==0){
            b++;
        }
        /*TBarSeries *series;
        series = new TBarSeries(this);
        series->BarPen->Color = clRed;
        series->ParentChart = Chart2;
        series->AddXY(i,a/b,"",clRed); */
        Series1->AddXY(i,a/b,"",clRed);
    }
}

}
//---------------------------------------------------------------------------


void __fastcall TFormNS::Button5Click(TObject *Sender)
{
//Chart3->RemoveAllSeries();
Series2->Clear();
ADOConnection1->Open();
ADOQuery1->Close();
float a = 0;
String s = Edit1->Text;
for(int i=0;i<24;i++){
    a = 0;
    String start = s;
    String end = s;
    if(i<=8){
        start = start+"0";
        start = start+IntToStr(i);
        end = end+"0";
        end = end+IntToStr(i+1);
    }
    else if(i==9){
        start = start+"0";
        start = start+IntToStr(i);
        end = end+IntToStr(i+1);
    }
    else{
        start = start+IntToStr(i);
        end = end+IntToStr(i+1);
    }
    while(start.Length()<17&&end.Length()<17){
        if(start.Length()<17){
            start.Insert("0",start.Length()+1);
        }
        if(end.Length()<17){
            end.Insert("0",end.Length()+1);
        }
    }
    if(this->DataSelected ==0){
        ADOQuery1->SQL->Text = "select * from simu where Time>"+start+" and Time<"+end+"";
        ADOQuery1->Open();
        while(!ADOQuery1->Eof){
            a++;
            ADOQuery1->Next();
        }
        Series2->AddXY(i,a,"",clRed);
        /*TFastLineSeries *series;
        series = new TFastLineSeries(this);
        series->ParentChart = Chart3;
        series->LinePen->Color = clRed;
        series->AddXY(i,0,"",clRed);
        series->AddXY(i,a,"",clRed); */
    }
    else if(this->DataSelected ==1){
        ADOQuery1->SQL->Text = "select * from reality where Time>"+start+" and Time<"+end+"";
        ADOQuery1->Open();
        while(!ADOQuery1->Eof){
            a++;
            ADOQuery1->Next();
        }
        Series2->AddXY(i,a,"",clRed);
        /*TFastLineSeries *series;
        series = new TFastLineSeries(this);
        series->ParentChart = Chart3;
        series->LinePen->Color = clRed;
        series->AddXY(i,0,"",clRed);
        series->AddXY(i,a,"",clRed); */
    }
}
}
//---------------------------------------------------------------------------

void __fastcall TFormNS::Button6Click(TObject *Sender)
{
int select=0;
int ColorList[]={clRed,clGreen,clYellow,clPurple,clWhite,clGray,clAqua,clOlive,clTeal};
String s = Edit1->Text;
String e = Edit2->Text;
float Pn = 0;
float Pj = 0;
String text = "";
ADOConnection1->Open();
ADOQuery1->Close();
while(s.Length()<17&&e.Length()<17){
    if(s.Length()<17){
        s.Insert("0",s.Length()+1);
    }
    if(e.Length()<17){
        e.Insert("0",e.Length()+1);
    }
}
Chart4->RemoveAllSeries();
bool b = true;
for(int i = 0;i<8;i++){
    if(this->DataSelected ==0){
        text = "select * from simu where Time>"+s+" and Time<"+e+" and ClientID = "+i+"";
        }
    else if(this->DataSelected ==1){
        text = "select * from reality where Time>"+s+" and Time<"+e+" and ClientID = "+i+"";
        }
        ADOQuery1->SQL->Text = text;
        ADOQuery1->Open();
        TLineSeries *series;
        series = new TLineSeries(this);
        series->ParentChart = Chart4;
        //series->Pointer->Visible = true;
       // series->ColorEachLine = true;
        series->Pointer->Visible = true;
        series->Pointer->Style = psCircle;
        if(select==7){
            select=0;
        }
        String s = IntToStr(i);
        while(!ADOQuery1->Eof){
            String node = ADOQuery1->FieldByName("Node")->AsString;
            float n = StrToFloat(node);
            String time = ADOQuery1->FieldByName("Time")->AsString;
            time = time.SubString(9,4);
            String hour = time.SubString(1,2);
            String minute = time.SubString(3,2);
            float h = StrToFloat(hour);
            float m = StrToFloat(minute);
            m = m/60;
            h = h+m;
            float j;
            String temp = FormatFloat("0.00",h);
            j = StrToFloat(temp);
            String s = IntToStr(i);
            series->Title = IntToStr(i);
            if(Pn==0){
                Pn = n;
                Pj = j;
                series->AddXY(Pj,Pn,"",series->LegendItemColor(i));
            }
            else{
                series->AddXY(Pj,Pn,"",series->LegendItemColor(i));
                Pj = j;
                Pn = n;
                series->AddXY(j,n,"",series->LegendItemColor(i));
            }
            ADOQuery1->Next();
        }
        select++;
        Pn = 0;
}
}
//---------------------------------------------------------------------------






