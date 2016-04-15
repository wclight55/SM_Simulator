object frmFind: TfrmFind
  Left = 282
  Top = 191
  Width = 309
  Height = 184
  Caption = 'Find'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
  PixelsPerInch = 96
  TextHeight = 13
  object btnOK: TButton
    Left = 60
    Top = 108
    Width = 75
    Height = 25
    Caption = 'Find'
    Default = True
    TabOrder = 2
    OnClick = btnOKClick
  end
  object btnCancel: TButton
    Left = 176
    Top = 108
    Width = 75
    Height = 25
    Cancel = True
    Caption = 'Cancel'
    TabOrder = 1
    OnClick = btnCancelClick
  end
  object Panel1: TPanel
    Left = 16
    Top = 16
    Width = 273
    Height = 81
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 28
      Width = 86
      Height = 13
      Caption = 'Name of Object'#65306
    end
    object edtSearch: TEdit
      Left = 96
      Top = 24
      Width = 141
      Height = 21
      TabOrder = 0
    end
  end
end
