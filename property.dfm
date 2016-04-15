object FrameProperty: TFrameProperty
  Left = 0
  Top = 0
  Width = 223
  Height = 470
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -13
  Font.Name = #23435#20307
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object Splitter1: TSplitter
    Left = 0
    Top = 161
    Width = 223
    Height = 2
    Cursor = crVSplit
    Align = alTop
  end
  object Label1: TLabel
    Left = 0
    Top = 163
    Width = 223
    Height = 13
    Align = alTop
    Caption = #23646#24615#31383#21475
  end
  object dxInspector: TdxInspector
    Left = 0
    Top = 176
    Width = 223
    Height = 294
    Align = alClient
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = #23435#20307
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    OnEnter = dxInspectorEnter
    DividerPos = 130
    PaintStyle = ipsExtended
    RowHeight = 21
    OnEdited = dxInspectorEdited
    Data = {
      E002000009000000080000000100000007000000726F774C696E650800000000
      0000000B000000726F7744697374616E6365080000000200000007000000726F
      774E6F646508000000000000000F0000006478726F7753656E736F7254797065
      08000000000000000F000000726F775472696767657252616E67650800000000
      00000005000000726F775549080000000500000009000000726F77436F6D6D6F
      6E08000000000000000E000000726F7755494C696E6557696474680800000000
      0000000E000000726F775549466F6E74436F6C6F7208000000000000000F0000
      00726F7755494272757368436F6C6F7208000000000000000E000000726F7755
      494C696E65436F6C6F7208000000000000000D000000726F77436F6D6D6F6E4E
      616D6508000000090000000A000000726F7750726F6A65637408000000000000
      000B000000726F7756617269616E6365080000000000000010000000726F7750
      726F6A656374417574686F7208000000000000000D000000726F775549466F6E
      7453697A65080000000000000014000000726F77436F6D6D6F6E446573637269
      7074696F6E08000000000000000D000000726F7749746572617454696D650800
      0000000000000F000000726F77556E697444697374616E636508000000000000
      0009000000726F774C616D62646108000000000000000F000000726F7753616D
      706C696E6754696D6508000000000000000F000000726F7757616C6B696E6753
      7065656408000000000000000E0000006478726F77436F7665724C6973740800
      00000000000014000000726F77436F76657265644C6973745F436F756E740800
      0000000000000D0000006478726F77506F736974696F6E08000000000000000C
      000000726F77496E666C75656E63650400000008000000EC340B0D0700000072
      6F774C696E6508000000F4350B0D07000000726F774E6F64650800000018380B
      0D09000000726F77436F6D6D6F6E080000000C390B0D0A000000726F7750726F
      6A656374}
    object rowNode: TdxInspectorTextRow
      Caption = 'Node Feature'
      IsCategory = True
    end
    object rowUI: TdxInspectorTextRow
      Caption = 'Appearance'
      IsCategory = True
    end
    object rowCommon: TdxInspectorTextRow
      Caption = 'Common Feature'
      IsCategory = True
    end
    object rowUIFontColor: TdxInspectorTextButtonRow
      Caption = 'Font Color'
      ReadOnly = True
      Buttons = <
        item
          Default = True
        end>
      OnButtonClick = rowUIFontColorButtonClick
    end
    object rowUIBrushColor: TdxInspectorTextButtonRow
      Caption = 'Fill Color'
      ReadOnly = True
      Buttons = <
        item
          Default = True
        end>
      OnButtonClick = rowUIBrushColorButtonClick
    end
    object rowUILineColor: TdxInspectorTextButtonRow
      Caption = 'Line Color'
      ReadOnly = True
      Buttons = <
        item
          Default = True
        end>
      OnButtonClick = rowUILineColorButtonClick
    end
    object rowProject: TdxInspectorTextRow
      Caption = 'Project Feature'
      IsCategory = True
    end
    object rowProjectAuthor: TdxInspectorTextRow
      Caption = 'Author'
    end
    object rowUIFontSize: TdxInspectorTextSpinRow
      Caption = 'Font Size'
      MinValue = 8
      MaxValue = 20
    end
    object rowUILineWidth: TdxInspectorTextSpinRow
      Caption = 'Line Width'
      OnChange = rowUILineWidthChange
      MinValue = 1
      MaxValue = 5
    end
    object rowCommonName: TdxInspectorTextRow
      Caption = 'Name'
      MaxLength = 100
    end
    object rowCommonDescription: TdxInspectorTextRow
      Caption = 'Description'
    end
    object rowTriggerRange: TdxInspectorTextRow
      Caption = 'Trigger Range'
      Text = '1'
    end
    object dxrowSensorType: TdxInspectorTextPickRow
      Caption = 'Sensor Type'
      Items.Strings = (
        'Sensor in Aisle'
        'Sensor in Room'
        'Sensor in Gateway')
    end
    object rowVariance: TdxInspectorTextRow
      Caption = 'Speed Variance'
    end
    object rowLine: TdxInspectorTextRow
      Caption = 'Line Feature'
      IsCategory = True
    end
    object rowDistance: TdxInspectorTextRow
      Caption = 'Distance(m)'
    end
    object rowUnitDistance: TdxInspectorTextRow
      Caption = 'Unit Distance(m/pixel)'
      Text = '0.1'
    end
    object rowIteratTime: TdxInspectorTextRow
      Caption = 'Iteration'
      Text = '10'
    end
    object rowLambda: TdxInspectorTextRow
      Caption = 'Lambda'
      Text = '2'
    end
    object rowSamplingTime: TdxInspectorTextRow
      Caption = 'SamplingTime(s)'
    end
    object rowWalkingSpeed: TdxInspectorTextRow
      Caption = 'WalkingSpeed(m/s)'
      Text = '1'
    end
    object dxrowCoverList: TdxInspectorTextPickRow
      Caption = 'CoveredList'
    end
    object rowCoveredList_Count: TdxInspectorTextRow
      Caption = 'CoveredList_Count'
    end
    object dxrowPosition: TdxInspectorTextPickRow
      Caption = 'Sensor Position'
    end
    object rowInfluence: TdxInspectorTextRow
      Caption = 'Node Influence'
      MaxLength = 0
    end
  end
  object TreeViewProject: TTreeView
    Left = 0
    Top = 0
    Width = 223
    Height = 161
    Align = alTop
    Constraints.MinHeight = 20
    Indent = 19
    MultiSelect = True
    ReadOnly = True
    SortType = stText
    TabOrder = 1
    OnClick = TreeViewProjectClick
    OnDblClick = TreeViewProjectDblClick
  end
  object ColorDialog: TColorDialog
    Ctl3D = True
    CustomColors.Strings = (
      'ColorA=FFFFFFFF'
      'ColorB=FFFFFFFF'
      'ColorC=FFFFFFFF'
      'ColorD=FFFFFFFF'
      'ColorE=FFFFFFFF'
      'ColorF=FFFFFFFF'
      'ColorG=FFFFFFFF'
      'ColorH=FFFFFFFF'
      'ColorI=FFFFFFFF'
      'ColorJ=FFFFFFFF'
      'ColorK=FFFFFFFF'
      'ColorL=FFFFFFFF'
      'ColorM=FFFFFFFF'
      'ColorN=FFFFFFFF'
      'ColorO=FFFFFFFF'
      'ColorP=FFFFFFFF')
    Left = 172
    Top = 188
  end
  object OpenDialog: TOpenDialog
    Left = 96
    Top = 224
  end
end
