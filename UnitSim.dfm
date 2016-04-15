object FormSim: TFormSim
  Left = 873
  Top = 370
  Width = 483
  Height = 306
  Caption = 'FormSim'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 40
    Width = 113
    Height = 13
    AutoSize = False
    Caption = 'Sensors for Selection'
    WordWrap = True
  end
  object Label2: TLabel
    Left = 184
    Top = 40
    Width = 97
    Height = 13
    AutoSize = False
    Caption = 'Sensors in Gateway'
  end
  object Label4: TLabel
    Left = 360
    Top = 37
    Width = 73
    Height = 20
    AutoSize = False
    Caption = 'Route'
  end
  object ListBox1: TListBox
    Left = 16
    Top = 72
    Width = 121
    Height = 137
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 0
  end
  object ListBox2: TListBox
    Left = 168
    Top = 72
    Width = 121
    Height = 137
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 1
  end
  object ListBox3: TListBox
    Left = 328
    Top = 72
    Width = 121
    Height = 137
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 2
  end
  object Button1: TButton
    Left = 40
    Top = 232
    Width = 75
    Height = 25
    Caption = 'Select'
    TabOrder = 3
    OnClick = Button1Click
  end
  object Button3: TButton
    Left = 264
    Top = 232
    Width = 75
    Height = 25
    Caption = 'Clear'
    TabOrder = 4
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 152
    Top = 232
    Width = 75
    Height = 25
    Caption = 'Add Route'
    TabOrder = 5
    OnClick = Button4Click
  end
  object Button2: TButton
    Left = 376
    Top = 232
    Width = 75
    Height = 25
    Caption = 'Exit'
    TabOrder = 6
    OnClick = Button2Click
  end
  object Button5: TButton
    Left = 104
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Training'
    TabOrder = 7
    OnClick = Button5Click
  end
  object Button6: TButton
    Left = 208
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Save'
    TabOrder = 8
    OnClick = Button6Click
  end
  object Button7: TButton
    Left = 320
    Top = 8
    Width = 75
    Height = 25
    Caption = 'T'
    TabOrder = 9
    OnClick = Button7Click
  end
  object Button8: TButton
    Left = 24
    Top = 8
    Width = 75
    Height = 25
    Caption = 'Test'
    TabOrder = 10
    OnClick = Button8Click
  end
end
