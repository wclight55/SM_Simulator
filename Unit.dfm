object FormNS: TFormNS
  Left = 269
  Top = 19
  Width = 991
  Height = 694
  Caption = #33410#28857#35302#21457#32479#35745
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
  object SplitterLeftRight: TSplitter
    Left = 300
    Top = 0
    Width = 3
    Height = 656
    Cursor = crHSplit
  end
  object PanelLeft: TPanel
    Left = 0
    Top = 0
    Width = 300
    Height = 656
    Align = alLeft
    Caption = 'PanelLeft'
    TabOrder = 0
    object Splitter1: TSplitter
      Left = 1
      Top = 281
      Width = 298
      Height = 3
      Cursor = crVSplit
      Align = alTop
    end
    object PanelList: TPanel
      Left = 1
      Top = 1
      Width = 298
      Height = 280
      Align = alTop
      TabOrder = 0
      object LabelList: TLabel
        Left = 1
        Top = 1
        Width = 296
        Height = 89
        Align = alTop
        Caption = 'Select Node'
        Font.Charset = ANSI_CHARSET
        Font.Color = clWindowText
        Font.Height = -16
        Font.Name = 'Cambria Math'
        Font.Style = []
        ParentFont = False
        Layout = tlCenter
        WordWrap = True
      end
      object ListBox1: TListBox
        Left = 1
        Top = 90
        Width = 176
        Height = 189
        Align = alLeft
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 13
        TabOrder = 0
      end
    end
    object PanelOpreation: TPanel
      Left = 1
      Top = 284
      Width = 298
      Height = 371
      Align = alClient
      TabOrder = 1
      object Edit1: TEdit
        Left = 16
        Top = 50
        Width = 121
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 0
        Text = '20120919'
      end
      object Edit2: TEdit
        Left = 153
        Top = 50
        Width = 121
        Height = 21
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        TabOrder = 1
        Text = '20120920'
      end
      object Button1: TButton
        Left = 32
        Top = 166
        Width = 81
        Height = 25
        Caption = 'Single Node'
        TabOrder = 2
        OnClick = Button1Click
      end
      object Button2: TButton
        Left = 32
        Top = 102
        Width = 81
        Height = 25
        Caption = 'Simulation Data'
        TabOrder = 3
      end
      object Button3: TButton
        Left = 152
        Top = 102
        Width = 75
        Height = 25
        Caption = 'Reality Data'
        TabOrder = 4
      end
      object Button4: TButton
        Left = 152
        Top = 166
        Width = 89
        Height = 25
        Caption = 'Probability Table'
        TabOrder = 5
        OnClick = Button4Click
      end
      object Button5: TButton
        Left = 32
        Top = 214
        Width = 75
        Height = 25
        Caption = 'All Nodes'
        TabOrder = 6
        OnClick = Button5Click
      end
      object Button6: TButton
        Left = 151
        Top = 214
        Width = 75
        Height = 25
        Caption = 'Trajectory'
        TabOrder = 7
        OnClick = Button6Click
      end
    end
  end
  object PanelRight: TPanel
    Left = 303
    Top = 0
    Width = 672
    Height = 656
    Align = alClient
    Caption = 'PanelRight'
    TabOrder = 1
    object SplitterSingleNode: TSplitter
      Left = 1
      Top = 121
      Width = 670
      Height = 3
      Cursor = crVSplit
      Align = alTop
      AutoSnap = False
    end
    object SplitterRate: TSplitter
      Left = 1
      Top = 281
      Width = 670
      Height = 3
      Cursor = crVSplit
      Align = alTop
    end
    object SplitterAllNode: TSplitter
      Left = 1
      Top = 433
      Width = 670
      Height = 3
      Cursor = crVSplit
      Align = alTop
    end
    object SplitterBottom: TSplitter
      Left = 1
      Top = 625
      Width = 670
      Height = 3
      Cursor = crVSplit
      Align = alTop
    end
    object PanelSingleNode: TPanel
      Left = 1
      Top = 1
      Width = 670
      Height = 120
      Align = alTop
      Caption = 'PanelSingleNode'
      TabOrder = 0
      object Chart1: TChart
        Left = 1
        Top = 1
        Width = 668
        Height = 118
        AllowPanning = pmNone
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        LeftWall.Brush.Color = clWhite
        MarginBottom = 0
        MarginLeft = 4
        MarginRight = 4
        MarginTop = 0
        Title.Text.Strings = (
          'Trigger Frequency Table of Single Node')
        BottomAxis.Automatic = False
        BottomAxis.AutomaticMaximum = False
        BottomAxis.AutomaticMinimum = False
        BottomAxis.ExactDateTime = False
        BottomAxis.Increment = 0.01
        BottomAxis.Maximum = 24
        BottomAxis.Title.Caption = 'Time'
        LeftAxis.Automatic = False
        LeftAxis.AutomaticMaximum = False
        LeftAxis.AutomaticMinimum = False
        LeftAxis.Maximum = 1
        LeftAxis.Title.Caption = 'Frequency'
        LeftAxis.TitleSize = 8
        Legend.Visible = False
        View3D = False
        View3DWalls = False
        Align = alClient
        BevelWidth = 0
        TabOrder = 0
      end
    end
    object PanelRate: TPanel
      Left = 1
      Top = 124
      Width = 670
      Height = 157
      Align = alTop
      Caption = 'PanelRate'
      TabOrder = 1
      object Chart2: TChart
        Left = 1
        Top = 1
        Width = 668
        Height = 155
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        MarginRight = 4
        MarginTop = 10
        Title.AdjustFrame = False
        Title.Text.Strings = (
          'Trigger Probability Table of Single Node')
        BottomAxis.Automatic = False
        BottomAxis.AutomaticMaximum = False
        BottomAxis.AutomaticMinimum = False
        BottomAxis.ExactDateTime = False
        BottomAxis.Increment = 1
        BottomAxis.Maximum = 24
        BottomAxis.Title.Caption = 'Time'
        LeftAxis.Automatic = False
        LeftAxis.AutomaticMaximum = False
        LeftAxis.AutomaticMinimum = False
        LeftAxis.ExactDateTime = False
        LeftAxis.Increment = 0.1
        LeftAxis.Maximum = 1
        LeftAxis.Title.Caption = 'Probability'
        Legend.Visible = False
        View3D = False
        Align = alClient
        BevelOuter = bvNone
        TabOrder = 0
        object Series1: TBarSeries
          Marks.ArrowLength = 20
          Marks.Font.Charset = GB2312_CHARSET
          Marks.Font.Color = clBlack
          Marks.Font.Height = -11
          Marks.Font.Name = '@'#26032#23435#20307
          Marks.Font.Style = []
          Marks.Visible = True
          SeriesColor = clRed
          BarWidthPercent = 100
          OffsetPercent = 50
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Bar'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
      end
    end
    object PanelAllNode: TPanel
      Left = 1
      Top = 284
      Width = 670
      Height = 149
      Align = alTop
      Caption = 'PanelAllNode'
      TabOrder = 2
      object Chart3: TChart
        Left = 1
        Top = 1
        Width = 668
        Height = 147
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        MarginBottom = 0
        MarginTop = 0
        Title.Text.Strings = (
          'Trigger Frequency Table of All Nodes')
        BottomAxis.Automatic = False
        BottomAxis.AutomaticMaximum = False
        BottomAxis.AutomaticMinimum = False
        BottomAxis.ExactDateTime = False
        BottomAxis.Increment = 1
        BottomAxis.Maximum = 24
        BottomAxis.Title.Caption = 'Time'
        LeftAxis.Automatic = False
        LeftAxis.AutomaticMaximum = False
        LeftAxis.AutomaticMinimum = False
        LeftAxis.ExactDateTime = False
        LeftAxis.Increment = 1
        LeftAxis.Maximum = 100
        LeftAxis.Title.Caption = 'Frequency'
        Legend.Visible = False
        View3D = False
        Align = alClient
        TabOrder = 0
        object Series2: TBarSeries
          Marks.ArrowLength = 20
          Marks.Visible = True
          SeriesColor = clRed
          BarWidthPercent = 100
          OffsetPercent = 50
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Bar'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
      end
    end
    object PanelNode4: TPanel
      Left = 1
      Top = 436
      Width = 670
      Height = 189
      Align = alTop
      Caption = 'PanelNode4'
      TabOrder = 3
      object Chart4: TChart
        Left = 1
        Top = 1
        Width = 668
        Height = 187
        BackWall.Brush.Color = clWhite
        BackWall.Brush.Style = bsClear
        Title.Text.Strings = (
          'Trajectory')
        BottomAxis.Automatic = False
        BottomAxis.AutomaticMaximum = False
        BottomAxis.AutomaticMinimum = False
        BottomAxis.ExactDateTime = False
        BottomAxis.Increment = 0.01
        BottomAxis.Maximum = 24
        BottomAxis.Title.Caption = 'Time'
        ClipPoints = False
        LeftAxis.Automatic = False
        LeftAxis.AutomaticMaximum = False
        LeftAxis.AutomaticMinimum = False
        LeftAxis.ExactDateTime = False
        LeftAxis.Increment = 1
        LeftAxis.Maximum = 10
        LeftAxis.Title.Caption = 'Nodes'
        Legend.ColorWidth = 100
        Legend.ShadowSize = 0
        RightAxis.Visible = False
        View3D = False
        Align = alClient
        TabOrder = 0
        object Series5: TLineSeries
          Marks.ArrowLength = 8
          Marks.Visible = True
          SeriesColor = clRed
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = True
          XValues.DateTime = False
          XValues.Name = 'X'
          XValues.Multiplier = 1
          XValues.Order = loAscending
          YValues.DateTime = False
          YValues.Name = 'Y'
          YValues.Multiplier = 1
          YValues.Order = loNone
        end
      end
    end
  end
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=MSDASQL.1;Password=root;Persist Security Info=True;User' +
      ' ID=root;Data Source=sweb'
    Provider = 'MSDASQL.1'
    Left = 240
    Top = 40
  end
  object ADOQuery1: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 224
    Top = 160
  end
  object DataSource1: TDataSource
    DataSet = ADOQuery1
    Left = 232
    Top = 72
  end
  object ADOQuery2: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 216
    Top = 120
  end
end
