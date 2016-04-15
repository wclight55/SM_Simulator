object frm_BelongFunction: Tfrm_BelongFunction
  Left = 350
  Top = 283
  Width = 762
  Height = 255
  Caption = 'Belong Function Setup'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnResize = FormResize
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Panel4: TPanel
    Left = 1
    Top = -8
    Width = 336
    Height = 233
    Align = alCustom
    BevelOuter = bvLowered
    BorderStyle = bsSingle
    TabOrder = 0
    object st_function: TStringGrid
      Left = 0
      Top = 48
      Width = 337
      Height = 177
      Align = alCustom
      Color = clWhite
      ColCount = 3
      FixedCols = 0
      RowCount = 1
      FixedRows = 0
      Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goThumbTracking]
      TabOrder = 0
      OnDblClick = st_functionDblClick
      ColWidths = (
        213
        54
        57)
    end
    object StaticText1: TStaticText
      Left = 112
      Top = 8
      Width = 76
      Height = 17
      Caption = 'Function Setup'
      TabOrder = 1
    end
  end
  object Panel5: TPanel
    Left = 336
    Top = 0
    Width = 417
    Height = 217
    Align = alCustom
    Caption = 'Panel1'
    TabOrder = 1
    object pb_function: TPaintBox
      Left = 1
      Top = 49
      Width = 415
      Height = 167
      Align = alClient
      Color = clBtnFace
      ParentColor = False
      OnPaint = pb_functionPaint
    end
    object Panel6: TPanel
      Left = 1
      Top = 1
      Width = 415
      Height = 48
      Align = alTop
      BevelOuter = bvLowered
      Caption = 'Diagram'
      TabOrder = 0
      object sp_refresh: TSpeedButton
        Left = 48
        Top = 8
        Width = 89
        Height = 25
        Caption = 'Refresh View'
        Glyph.Data = {
          F6060000424DF606000000000000360000002800000018000000180000000100
          180000000000C0060000C40E0000C40E00000000000000000000C0C0C0C0C0C0
          C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
          C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0848284C0
          C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
          C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
          C0C0C0C0CED3D6C0C0C0C0C0C0CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CE
          D3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6
          CED3D6CED3D6CED3D6CED3D6CED3D6C0C0C0C0C0C0CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D6CED3D6840000840000840000840000840000840000CED3D6CE
          D3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6C0C0C0C0C0C0CED3D6
          CED3D6008200840000CED3D6CED3D68400000082000082000082000082000082
          00008200840000840000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6C0
          C0C0C0C0C0CED3D6CED3D6008200008200840000840000008200008200008200
          008200008200008200008200008200008200840000CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D6C0C0C0C0C0C0CED3D6CED3D600820000820000820000820000
          820000820000FF0000FF0000FF0000FF0000FF00008200008200008200840000
          CED3D6CED3D6CED3D6CED3D6CED3D6C0C0C0C0C0C0CED3D6CED3D60082000082
          0000820000820000820000FF00CED3D6CED3D6CED3D6CED3D6CED3D600FF0000
          8200008200008200840000CED3D6CED3D6CED3D6CED3D6C0C0C0C0C0C0CED3D6
          CED3D6008200008200008200008200008200CED3D6CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D600FF00008200008200840000CED3D6CED3D6CED3D6CED3D6C0
          C0C0C0C0C0CED3D6CED3D6008200008200008200008200008200008200CED3D6
          CED3D6CED3D6CED3D6CED3D6CED3D600FF00840000840000840000CED3D6CED3
          D6CED3D6CED3D6C0C0C0C0C0C0CED3D6CED3D600FF0000FF0000FF0000FF0000
          FF0000FF0000FF00CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6
          CED3D6CED3D6CED3D6CED3D6CED3D6C0C0C0C0C0C0CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CE
          D3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6C0C0C0C0C0C0CED3D6
          CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
          D6CED3D6840000840000840000840000840000840000CED3D6CED3D6CED3D6C0
          C0C0C0C0C0CED3D6CED3D600FF00840000840000840000CED3D6CED3D6CED3D6
          CED3D6CED3D6CED3D600FF00008200008200008200008200008200840000CED3
          D6CED3D6CED3D6C0C0C0C0C0C0CED3D6CED3D600FF00008200008200840000CE
          D3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600FF00008200008200008200
          008200840000CED3D6CED3D6CED3D6C0C0C0C0C0C0CED3D6CED3D6CED3D600FF
          00008200008200840000CED3D6CED3D6CED3D6CED3D6CED3D684000084000000
          8200008200008200008200840000CED3D6CED3D6CED3D6C0C0C0C0C0C0CED3D6
          CED3D6CED3D600FF000082000082000082008400008400008400008400008400
          00008200008200008200008200008200008200840000CED3D6CED3D6CED3D6C0
          C0C0C0C0C0CED3D6CED3D6CED3D6CED3D600FF00008200008200008200008200
          00820000820000820000820000820000820000FF0000FF00008200840000CED3
          D6CED3D6CED3D6C0C0C0C0C0C0CED3D6CED3D6CED3D6CED3D6CED3D600FF0000
          FF0000820000820000820000820000820000820000FF0000FF00CED3D6CED3D6
          00FF00CED3D6CED3D6CED3D6CED3D6C0C0C0C0C0C0CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D6CED3D600FF0000FF0000FF0000FF0000FF0000FF00CED3D6CE
          D3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6C0C0C0C0C0C0CED3D6
          CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6C0
          C0C0C0C0C0CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6
          CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D6C0C0C0C0C0C0CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CE
          D3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6
          CED3D6CED3D6CED3D6CED3D6C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
          C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0
          C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0C0}
        OnClick = sp_refreshClick
      end
      object sb_close: TSpeedButton
        Left = 296
        Top = 8
        Width = 81
        Height = 25
        Caption = 'Save&Close'
        Glyph.Data = {
          26040000424D2604000000000000360000002800000012000000120000000100
          180000000000F0030000C40E0000C40E00000000000000000000CED3D6CED3D6
          CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D6CED3D6CED3D6CED3D60000CED3D6CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CE
          D3D6CED3D6CED3D60000CED3D6CED3D6CED3D6CED3D6CED3D6840000840000CE
          D3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6
          0000CED3D6CED3D6CED3D6CED3D6840000008200008200840000CED3D6CED3D6
          CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D60000CED3D6CED3D6
          CED3D6840000008200008200008200008200840000CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D6CED3D6CED3D6CED3D60000CED3D6CED3D68400000082000082
          00008200008200008200008200840000CED3D6CED3D6CED3D6CED3D6CED3D6CE
          D3D6CED3D6CED3D60000CED3D684000000820000820000820000FF0000820000
          8200008200008200840000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6
          0000CED3D600820000820000820000FF00CED3D600FF00008200008200008200
          840000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D60000CED3D600FF00
          00820000FF00CED3D6CED3D6CED3D600FF00008200008200008200840000CED3
          D6CED3D6CED3D6CED3D6CED3D6CED3D60000CED3D6CED3D600FF00CED3D6CED3
          D6CED3D6CED3D6CED3D600FF00008200008200008200840000CED3D6CED3D6CE
          D3D6CED3D6CED3D60000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CE
          D3D6CED3D600FF00008200008200008200840000CED3D6CED3D6CED3D6CED3D6
          0000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6
          00FF00008200008200008200840000CED3D6CED3D6CED3D60000CED3D6CED3D6
          CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600FF000082
          00008200008200840000CED3D6CED3D60000CED3D6CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D600FF0000820000820000
          8200840000CED3D60000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CE
          D3D6CED3D6CED3D6CED3D6CED3D6CED3D600FF00008200008200840000CED3D6
          0000CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6
          CED3D6CED3D6CED3D6CED3D600FF00008200008200CED3D60000CED3D6CED3D6
          CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D600FF00CED3D6CED3D60000CED3D6CED3D6CED3D6CED3D6CED3
          D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CED3D6CE
          D3D6CED3D6CED3D60000}
        OnClick = sb_closeClick
      end
    end
  end
end
