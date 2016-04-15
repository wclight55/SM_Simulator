object tf_relationship: Ttf_relationship
  Left = 428
  Top = 215
  Width = 696
  Height = 480
  Caption = 'Matrix'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object ts_relation: TStringGrid
    Left = 0
    Top = 0
    Width = 680
    Height = 442
    Align = alClient
    Options = [goFixedVertLine, goFixedHorzLine, goVertLine, goHorzLine, goRangeSelect, goColSizing, goThumbTracking]
    TabOrder = 0
    OnDrawCell = ts_relationDrawCell
    RowHeights = (
      24
      25
      24
      24
      24)
  end
end
