object Form1: TForm1
  Left = 451
  Top = 213
  Width = 1007
  Height = 517
  Caption = 'FormTransfer'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDefault
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object Label2: TLabel
    Left = 768
    Top = 11
    Width = 97
    Height = 13
    AutoSize = False
    Caption = 'New Environment'
  end
  object Label4: TLabel
    Left = 880
    Top = 24
    Width = 81
    Height = 20
    AutoSize = False
    Caption = 'NewStartNodes'
  end
  object Label3: TLabel
    Left = 704
    Top = 240
    Width = 59
    Height = 13
    Caption = 'New Pattern'
  end
  object Label5: TLabel
    Left = 536
    Top = 8
    Width = 48
    Height = 13
    Caption = 'StartNode'
  end
  object Label6: TLabel
    Left = 648
    Top = 8
    Width = 45
    Height = 13
    Caption = 'EndNode'
  end
  object Label7: TLabel
    Left = 880
    Top = 96
    Width = 81
    Height = 20
    AutoSize = False
    Caption = 'NewEndNodes'
  end
  object ListBox1: TListBox
    Left = 528
    Top = 27
    Width = 89
    Height = 137
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 0
  end
  object ListBox2: TListBox
    Left = 768
    Top = 27
    Width = 89
    Height = 137
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 1
  end
  object ListBox3: TListBox
    Left = 880
    Top = 40
    Width = 73
    Height = 41
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 2
  end
  object Button3: TButton
    Left = 712
    Top = 187
    Width = 75
    Height = 25
    Caption = 'Patch'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 576
    Top = 187
    Width = 75
    Height = 25
    Caption = 'Add File'
    TabOrder = 4
    OnClick = Button4Click
  end
  object Button2: TButton
    Left = 856
    Top = 187
    Width = 75
    Height = 25
    Caption = 'Exit'
    TabOrder = 5
    OnClick = Button2Click
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 513
    Height = 473
    Align = alCustom
    BevelOuter = bvLowered
    TabOrder = 6
    OnResize = PanelPaintResize
    object PaintBox1: TPaintBox
      Left = 0
      Top = 1
      Width = 513
      Height = 472
      Align = alCustom
      Color = clCream
      ParentColor = False
      OnPaint = TForm1BoxPaint
    end
  end
  object ListBox4: TListBox
    Left = 520
    Top = 257
    Width = 441
    Height = 208
    ItemHeight = 13
    TabOrder = 7
  end
  object ListBox7: TListBox
    Left = 880
    Top = 112
    Width = 73
    Height = 41
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 8
  end
  object ListBox5: TListBox
    Left = 632
    Top = 27
    Width = 89
    Height = 137
    ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
    ItemHeight = 13
    TabOrder = 9
  end
  object OpenDialog: TOpenDialog
    Filter = 'All Files (*.*)|*.*'
    Options = [ofHideReadOnly, ofAllowMultiSelect, ofEnableSizing]
    Left = 216
    Top = 160
  end
  object XMLDoc: TXMLDocument
    Left = 264
    Top = 208
    DOMVendorDesc = 'MSXML'
  end
end
