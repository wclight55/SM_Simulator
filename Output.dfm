object FrameOutput: TFrameOutput
  Left = 0
  Top = 0
  Width = 320
  Height = 240
  Font.Charset = ANSI_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = #23435#20307
  Font.Style = []
  ParentFont = False
  TabOrder = 0
  object PageControl: TPageControl
    Left = 0
    Top = 0
    Width = 320
    Height = 240
    ActivePage = TabSheetSearch
    Align = alClient
    MultiLine = True
    TabIndex = 2
    TabOrder = 0
    TabPosition = tpBottom
    object TabSheetOutputList: TTabSheet
      Caption = 'Results Output'
      object ListBoxOutput: TListBox
        Left = 0
        Top = 0
        Width = 312
        Height = 215
        Align = alClient
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 12
        TabOrder = 0
      end
    end
    object TabSheetErrorList: TTabSheet
      Caption = 'Error List'
      ImageIndex = 1
      object ListBoxError: TListBox
        Left = 0
        Top = 0
        Width = 312
        Height = 215
        Align = alClient
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 12
        TabOrder = 0
        OnDblClick = ListBoxErrorDblClick
      end
    end
    object TabSheetSearch: TTabSheet
      Caption = 'Finding results'
      ImageIndex = 2
      object ListBoxSearch: TListBox
        Left = 0
        Top = 0
        Width = 312
        Height = 215
        Align = alClient
        ImeName = #20013#25991' ('#31616#20307') - '#25628#29399#25340#38899#36755#20837#27861
        ItemHeight = 12
        TabOrder = 0
        OnDblClick = ListBoxSearchDblClick
      end
    end
  end
end
