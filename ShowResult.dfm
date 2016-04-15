object frmShowResult: TfrmShowResult
  Left = 128
  Top = 196
  Width = 928
  Height = 480
  Caption = 'frmShowResult'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 97
    Height = 442
    Align = alLeft
    Alignment = taLeftJustify
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 16
      Width = 25
      Height = 13
      Caption = 'Start:'
    end
    object Label2: TLabel
      Left = 16
      Top = 56
      Width = 22
      Height = 13
      Caption = 'End:'
    end
    object labTotal: TLabel
      Left = 8
      Top = 176
      Width = 24
      Height = 13
      Caption = '1000'
    end
    object Label3: TLabel
      Left = 8
      Top = 160
      Width = 76
      Height = 13
      Caption = 'Simulating Num:'
    end
    object edStart: TEdit
      Left = 16
      Top = 32
      Width = 49
      Height = 21
      TabOrder = 0
      Text = '1'
    end
    object edEnd: TEdit
      Left = 16
      Top = 72
      Width = 49
      Height = 21
      TabOrder = 1
      Text = '100'
    end
    object Button1: TButton
      Left = 16
      Top = 104
      Width = 49
      Height = 25
      Caption = 'Refresh'
      TabOrder = 2
      OnClick = Button1Click
    end
  end
  object Panel2: TPanel
    Left = 97
    Top = 0
    Width = 815
    Height = 442
    Align = alClient
    Caption = 'Panel2'
    TabOrder = 1
    object PageControl1: TPageControl
      Left = 1
      Top = 1
      Width = 813
      Height = 440
      ActivePage = tabHistoryDetail
      Align = alClient
      TabIndex = 2
      TabOrder = 0
      object tabSensorHistory: TTabSheet
        Caption = 'SensorHistory'
        object paintSensorHistory: TPaintBox
          Left = 0
          Top = 0
          Width = 788
          Height = 395
          Align = alClient
          OnPaint = paintSensorHistoryPaint
        end
        object scHSensorHistory: TScrollBar
          Left = 0
          Top = 395
          Width = 805
          Height = 17
          Align = alBottom
          PageSize = 0
          TabOrder = 0
        end
        object scVSensorHistory: TScrollBar
          Left = 788
          Top = 0
          Width = 17
          Height = 395
          Align = alRight
          Kind = sbVertical
          PageSize = 0
          TabOrder = 1
        end
      end
      object tabUserPath: TTabSheet
        Caption = 'UserPath'
        ImageIndex = 1
        object paintUserPath: TPaintBox
          Left = 0
          Top = 0
          Width = 788
          Height = 395
          Align = alClient
          OnPaint = paintUserPathPaint
        end
        object scHUserPath: TScrollBar
          Left = 0
          Top = 395
          Width = 805
          Height = 17
          Align = alBottom
          PageSize = 0
          TabOrder = 0
        end
        object scVUserPath: TScrollBar
          Left = 788
          Top = 0
          Width = 17
          Height = 395
          Align = alRight
          Kind = sbVertical
          PageSize = 0
          TabOrder = 1
        end
      end
      object tabHistoryDetail: TTabSheet
        Caption = 'HistoryDetail'
        ImageIndex = 2
        object paintHistoryDetail: TPaintBox
          Left = 0
          Top = 0
          Width = 805
          Height = 412
          Align = alClient
          OnPaint = paintHistoryDetailPaint
        end
      end
    end
  end
end
