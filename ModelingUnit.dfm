object Form1: TForm1
  Left = 69
  Top = 0
  Caption = #1052#1086#1076#1077#1083#1080#1088#1086#1074#1072#1085#1080#1077' '#1080#1079#1084#1077#1088#1077#1085#1080#1081' '#1057#1054#1069#1042#1054
  ClientHeight = 802
  ClientWidth = 958
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesigned
  OnActivate = FormActivate
  OnClose = FormClose
  OnCreate = FormCreate
  DesignSize = (
    958
    802)
  PixelsPerInch = 96
  TextHeight = 13
  object Label18: TLabel
    Left = 8
    Top = 55
    Width = 130
    Height = 13
    Caption = #1053#1072#1087#1088#1072#1074#1083#1103#1102#1097#1080#1077' '#1082#1086#1089#1080#1085#1091#1089#1099
  end
  object Label19: TLabel
    Left = 8
    Top = 77
    Width = 13
    Height = 13
    Caption = 'L='
  end
  object Label20: TLabel
    Left = 62
    Top = 77
    Width = 16
    Height = 13
    Caption = 'M='
  end
  object Label21: TLabel
    Left = 117
    Top = 77
    Width = 15
    Height = 13
    Caption = 'N='
  end
  object Label39: TLabel
    Left = 384
    Top = 680
    Width = 37
    Height = 13
    Caption = 'Label39'
  end
  object ButtonClose: TButton
    Left = 243
    Top = 772
    Width = 53
    Height = 25
    Caption = #1042#1099#1093#1086#1076
    TabOrder = 0
    OnClick = ButtonCloseClick
  end
  object ButtonSimulate: TButton
    Left = 5
    Top = 772
    Width = 137
    Height = 25
    Caption = #1055#1088#1086#1074#1077#1089#1090#1080' '#1084#1086#1076#1077#1083#1080#1088#1086#1074#1072#1085#1080#1077
    TabOrder = 1
    OnClick = ButtonSimulateClick
  end
  object L: TEdit
    Left = 27
    Top = 74
    Width = 25
    Height = 21
    Alignment = taCenter
    Enabled = False
    TabOrder = 2
    Text = '0'
  end
  object M: TEdit
    Left = 84
    Top = 74
    Width = 25
    Height = 21
    Alignment = taCenter
    Enabled = False
    TabOrder = 3
    Text = '0'
  end
  object N: TEdit
    Left = 138
    Top = 74
    Width = 25
    Height = 21
    Alignment = taCenter
    Enabled = False
    TabOrder = 4
    Text = '1'
  end
  object Chart1: TChart
    Left = 302
    Top = -8
    Width = 658
    Height = 813
    Legend.Visible = False
    Title.Font.Color = clBlack
    Title.Font.Height = -16
    Title.Font.Style = [fsBold]
    Title.Text.Strings = (
      #1052#1086#1076#1077#1083#1080#1088#1086#1074#1072#1085#1080#1077' '#1088#1077#1079#1091#1083#1100#1090#1072#1090#1086#1074' '#1080#1079#1084#1077#1088#1077#1085#1080#1081)
    DepthAxis.Visible = True
    DepthTopAxis.Visible = True
    LeftAxis.Inverted = True
    TopAxis.Axis.Color = clDefault
    TopAxis.Labels = False
    TopAxis.LabelsFormat.Visible = False
    View3D = False
    TabOrder = 5
    Anchors = [akLeft, akTop, akRight, akBottom]
    DefaultCanvas = 'TGDIPlusCanvas'
    PrintMargins = (
      15
      13
      15
      13)
    ColorPaletteIndex = 13
    object Series1: TPointSeries
      HorizAxis = aTopAxis
      ClickableLine = False
      Pointer.Brush.Gradient.EndColor = 10708548
      Pointer.Gradient.EndColor = 10708548
      Pointer.InflateMargins = True
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
    end
    object Series2: TArrowSeries
      HorizAxis = aTopAxis
      Marks.Frame.Visible = False
      Marks.Transparent = True
      SeriesColor = clRed
      ClickableLine = False
      Pointer.Brush.Gradient.EndColor = clRed
      Pointer.Gradient.EndColor = clRed
      Pointer.InflateMargins = False
      Pointer.Style = psRectangle
      XValues.Name = 'X'
      XValues.Order = loAscending
      YValues.Name = 'Y'
      YValues.Order = loNone
      EndXValues.Name = 'EndX'
      EndXValues.Order = loNone
      EndYValues.Name = 'EndY'
      EndYValues.Order = loNone
      StartXValues.Name = 'X'
      StartXValues.Order = loAscending
      StartYValues.Name = 'Y'
      StartYValues.Order = loNone
    end
  end
  object CheckBoxDist: TCheckBox
    Left = 8
    Top = 101
    Width = 275
    Height = 17
    Caption = #1052#1086#1076#1077#1083#1080#1088#1086#1074#1072#1090#1100' '#1074#1083#1080#1103#1085#1080#1077' '#1076#1080#1089#1090#1086#1088#1089#1080#1080
    TabOrder = 6
    OnClick = CheckBoxDistClick
  end
  object EditFileDist: TEdit
    Left = 8
    Top = 124
    Width = 202
    Height = 21
    TabOrder = 7
  end
  object ButtonOpenDist: TButton
    Left = 216
    Top = 122
    Width = 75
    Height = 25
    Caption = #1042#1099#1073#1088#1072#1090#1100'..'
    TabOrder = 8
    OnClick = ButtonOpenDistClick
  end
  object GroupBox1: TGroupBox
    Left = 5
    Top = 605
    Width = 291
    Height = 164
    TabOrder = 9
    object Label23: TLabel
      Left = 13
      Top = 44
      Width = 114
      Height = 13
      Caption = #1057#1050#1054' '#1087#1086#1083#1086#1078#1077#1085#1080#1103' '#1090#1086#1095#1077#1082
    end
    object Label22: TLabel
      Left = 223
      Top = 44
      Width = 27
      Height = 13
      Caption = #1087#1080#1082#1089'.'
    end
    object Label25: TLabel
      Left = 16
      Top = 86
      Width = 160
      Height = 13
      Caption = #1057#1050#1054' '#1091#1075#1083#1086#1074' '#1087#1086#1074#1086#1088#1086#1090#1072' '#1074#1086#1082#1088#1091#1075' OZ'
    end
    object Label24: TLabel
      Left = 223
      Top = 81
      Width = 60
      Height = 13
      Caption = #1091#1075#1083'. '#1089#1077#1082#1091#1085#1076
    end
    object Label27: TLabel
      Left = 16
      Top = 114
      Width = 160
      Height = 13
      Caption = #1057#1050#1054' '#1091#1075#1083#1086#1074' '#1087#1086#1074#1086#1088#1086#1090#1072' '#1074#1086#1082#1088#1091#1075' OX'
    end
    object Label26: TLabel
      Left = 223
      Top = 108
      Width = 60
      Height = 13
      Caption = #1091#1075#1083'. '#1089#1077#1082#1091#1085#1076
    end
    object Label28: TLabel
      Left = 13
      Top = 143
      Width = 153
      Height = 13
      Caption = #1050#1086#1101#1092#1092'. '#1084#1072#1089#1096#1090#1072#1073#1072' '#1086#1090#1082#1083#1086#1085#1077#1085#1080#1081
    end
    object CheckBoxCoordError: TCheckBox
      Left = 13
      Top = 13
      Width = 275
      Height = 17
      Caption = #1059#1095#1080#1090#1099#1074#1072#1090#1100' '#1086#1090#1082#1083#1086#1085#1077#1085#1080#1103' '#1087#1086' '#1082#1086#1086#1088#1076#1080#1085#1072#1090#1072#1084
      TabOrder = 0
      OnClick = CheckBoxCoordErrorClick
    end
    object EditCoordError: TEdit
      Left = 182
      Top = 36
      Width = 35
      Height = 21
      Enabled = False
      TabOrder = 1
      Text = '0'
    end
    object CheckBoxAngleError: TCheckBox
      Left = 13
      Top = 63
      Width = 243
      Height = 17
      Caption = #1059#1095#1080#1090#1099#1074#1072#1090#1100' '#1086#1090#1082#1083#1086#1085#1077#1085#1080#1103' '#1087#1086' '#1091#1075#1083#1072#1084' '#1087#1086#1074#1086#1088#1086#1090#1072
      TabOrder = 2
      OnClick = CheckBoxAngleErrorClick
    end
    object EditAngleErrorOZ: TEdit
      Left = 182
      Top = 81
      Width = 35
      Height = 21
      Enabled = False
      TabOrder = 3
      Text = '0'
    end
    object EditAngleErrorOX: TEdit
      Left = 182
      Top = 108
      Width = 35
      Height = 21
      Enabled = False
      TabOrder = 4
      Text = '0'
    end
    object EditScale: TEdit
      Left = 182
      Top = 135
      Width = 35
      Height = 21
      Enabled = False
      TabOrder = 5
      Text = '1'
    end
  end
  object GroupBox2: TGroupBox
    Left = 606
    Top = 114
    Width = 291
    Height = 81
    TabOrder = 10
    Visible = False
    object Label29: TLabel
      Left = 231
      Top = 39
      Width = 55
      Height = 13
      Caption = '-'#1081' '#1087#1086#1074#1086#1088#1086#1090
    end
    object Label31: TLabel
      Left = 3
      Top = 62
      Width = 154
      Height = 13
      Caption = #1055#1088#1086#1094#1077#1085#1090' '#1084#1086#1076#1077#1083#1080#1088#1091#1077#1084#1099#1093' '#1090#1086#1095#1077#1082
    end
    object Label30: TLabel
      Left = 231
      Top = 68
      Width = 11
      Height = 13
      Caption = '%'
    end
    object CheckBoxEqualNet: TCheckBox
      Left = 3
      Top = 12
      Width = 222
      Height = 17
      Caption = #1052#1086#1076#1077#1083#1080#1088#1086#1074#1072#1090#1100' '#1088#1072#1074#1085#1086#1084#1077#1088#1085#1091#1102' '#1089#1077#1090#1082#1091
      TabOrder = 0
    end
    object CheckBoxModelCentre: TCheckBox
      Left = 3
      Top = 39
      Width = 181
      Height = 17
      Caption = #1052#1086#1076#1077#1083#1080#1088#1086#1074#1072#1090#1100' '#1094#1077#1085#1090#1088' '#1082#1072#1078#1076#1099#1081
      TabOrder = 1
      OnClick = CheckBoxModelCentreClick
    end
    object EditCentrePoint: TEdit
      Left = 190
      Top = 35
      Width = 35
      Height = 21
      Enabled = False
      TabOrder = 2
      Text = '2'
    end
    object EditPercent: TEdit
      Left = 190
      Top = 62
      Width = 35
      Height = 21
      Enabled = False
      TabOrder = 3
      Text = '75'
    end
  end
  object GroupBox4: TGroupBox
    AlignWithMargins = True
    Left = 2
    Top = 8
    Width = 286
    Height = 41
    Caption = #1050#1091#1076#1072' '#1089#1084#1086#1090#1088#1080#1090' '#1086#1089#1100' OX '#1055#1057#1050'?'
    TabOrder = 11
    object UpRadioButton: TRadioButton
      Left = 3
      Top = 16
      Width = 55
      Height = 17
      Caption = #1042#1074#1077#1088#1093
      Checked = True
      TabOrder = 0
      TabStop = True
    end
    object DownRadioButton: TRadioButton
      Left = 80
      Top = 16
      Width = 55
      Height = 17
      Caption = #1042#1085#1080#1079
      TabOrder = 1
    end
    object LeftRadioButton: TRadioButton
      Left = 144
      Top = 16
      Width = 55
      Height = 17
      Caption = #1042#1083#1077#1074#1086
      TabOrder = 2
    end
    object RightRadioButton: TRadioButton
      Left = 208
      Top = 16
      Width = 55
      Height = 17
      Caption = #1042#1087#1088#1072#1074#1086
      TabOrder = 3
    end
  end
  object PageControl1: TPageControl
    Left = 2
    Top = 371
    Width = 294
    Height = 232
    ActivePage = Углы
    Style = tsFlatButtons
    TabOrder = 12
    object Углы: TTabSheet
      Caption = #1059#1075#1083#1099
      object GroupBox3: TGroupBox
        Left = 0
        Top = -4
        Width = 323
        Height = 208
        TabOrder = 0
        object Label32: TLabel
          Left = 3
          Top = 20
          Width = 24
          Height = 13
          Caption = #945'1_y'
        end
        object Label36: TLabel
          Left = 3
          Top = 47
          Width = 24
          Height = 13
          Caption = #945'2_y'
        end
        object Label40: TLabel
          Left = 6
          Top = 74
          Width = 18
          Height = 13
          Caption = #947'_y'
        end
        object Label44: TLabel
          Left = 6
          Top = 101
          Width = 18
          Height = 13
          Caption = #955'_y'
        end
        object Label34: TLabel
          Left = 142
          Top = 23
          Width = 24
          Height = 13
          Caption = #945'1_x'
        end
        object Label37: TLabel
          Left = 142
          Top = 50
          Width = 24
          Height = 13
          Caption = #945'2_x'
        end
        object Label42: TLabel
          Left = 150
          Top = 74
          Width = 18
          Height = 13
          Caption = #947'_x'
        end
        object Label46: TLabel
          Left = 151
          Top = 103
          Width = 18
          Height = 13
          Caption = #955'_x'
        end
        object Label33: TLabel
          Left = 74
          Top = 25
          Width = 47
          Height = 13
          Caption = #1075#1088#1072#1076#1091#1089#1086#1074
        end
        object Label48: TLabel
          Left = 73
          Top = 50
          Width = 47
          Height = 13
          Caption = #1075#1088#1072#1076#1091#1089#1086#1074
        end
        object Label49: TLabel
          Left = 74
          Top = 79
          Width = 47
          Height = 13
          Caption = #1075#1088#1072#1076#1091#1089#1086#1074
        end
        object Label50: TLabel
          Left = 73
          Top = 106
          Width = 47
          Height = 13
          Caption = #1075#1088#1072#1076#1091#1089#1086#1074
        end
        object Label51: TLabel
          Left = 221
          Top = 25
          Width = 47
          Height = 13
          Caption = #1075#1088#1072#1076#1091#1089#1086#1074
        end
        object Label52: TLabel
          Left = 221
          Top = 52
          Width = 47
          Height = 13
          Caption = #1075#1088#1072#1076#1091#1089#1086#1074
        end
        object Label53: TLabel
          Left = 221
          Top = 80
          Width = 47
          Height = 13
          Caption = #1075#1088#1072#1076#1091#1089#1086#1074
        end
        object Label54: TLabel
          Left = 221
          Top = 105
          Width = 47
          Height = 13
          Caption = #1075#1088#1072#1076#1091#1089#1086#1074
        end
        object Ошибки: TLabel
          Left = 3
          Top = 128
          Width = 44
          Height = 13
          Caption = #1054#1096#1080#1073#1082#1080':'
        end
        object Label47: TLabel
          Left = 3
          Top = 155
          Width = 105
          Height = 13
          Caption = #1054#1096#1080#1073#1082#1072' '#947'_z, '#1091#1075#1083'.'#1089#1077#1082
        end
        object EditAlpha1OY: TEdit
          Left = 33
          Top = 20
          Width = 35
          Height = 21
          TabOrder = 0
          Text = '0'
        end
        object EditAlpha2OY: TEdit
          Left = 33
          Top = 47
          Width = 35
          Height = 21
          TabOrder = 1
          Text = '0'
        end
        object EditGammaOY: TEdit
          Left = 32
          Top = 74
          Width = 35
          Height = 21
          TabOrder = 2
          Text = '0'
        end
        object EditLambdaOY: TEdit
          Left = 32
          Top = 101
          Width = 35
          Height = 21
          TabOrder = 3
          Text = '0'
        end
        object EditAlpha1OX: TEdit
          Left = 180
          Top = 18
          Width = 35
          Height = 21
          TabOrder = 4
          Text = '0'
        end
        object EditAlpha2OX: TEdit
          Left = 180
          Top = 45
          Width = 35
          Height = 21
          TabOrder = 5
          Text = '0'
        end
        object EditGammaOX: TEdit
          Left = 180
          Top = 72
          Width = 35
          Height = 21
          TabOrder = 6
          Text = '0'
        end
        object EditLambdaOX: TEdit
          Left = 180
          Top = 99
          Width = 35
          Height = 21
          TabOrder = 7
          Text = '0'
        end
        object EditGammaErrorZ: TEdit
          Left = 115
          Top = 152
          Width = 113
          Height = 21
          TabOrder = 8
          Text = '0'
        end
      end
    end
    object Точки: TTabSheet
      Caption = #1058#1086#1095#1082#1080
      ImageIndex = 1
      object GroupBox6: TGroupBox
        Left = -4
        Top = 0
        Width = 316
        Height = 201
        TabOrder = 0
        object Label3: TLabel
          Left = 15
          Top = 35
          Width = 133
          Height = 13
          Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1087#1077#1088#1074#1086#1081' '#1090#1086#1095#1082#1080':'
          FocusControl = ButtonClose
        end
        object Label35: TLabel
          Left = 19
          Top = 54
          Width = 101
          Height = 13
          Caption = #1057#1084#1077#1097#1077#1085#1080#1077' '#1087#1086' X, '#1084#1080#1085
        end
        object Label1: TLabel
          Left = 19
          Top = 84
          Width = 101
          Height = 13
          Caption = #1057#1084#1077#1097#1077#1085#1080#1077' '#1087#1086' Y, '#1084#1080#1085
        end
        object Label38: TLabel
          Left = 15
          Top = 116
          Width = 133
          Height = 13
          Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1074#1090#1086#1088#1086#1081' '#1090#1086#1095#1082#1080':'
        end
        object Label41: TLabel
          Left = 19
          Top = 135
          Width = 101
          Height = 13
          Caption = #1057#1084#1077#1097#1077#1085#1080#1077' '#1087#1086' X, '#1084#1080#1085
        end
        object Label43: TLabel
          Left = 19
          Top = 166
          Width = 101
          Height = 13
          Caption = #1057#1084#1077#1097#1077#1085#1080#1077' '#1087#1086' Y, '#1084#1080#1085
        end
        object EditFirstPointY: TEdit
          Left = 131
          Top = 81
          Width = 145
          Height = 21
          Align = alCustom
          TabOrder = 0
          Text = '15'
        end
        object EditSecondPointX: TEdit
          Left = 131
          Top = 135
          Width = 145
          Height = 21
          TabOrder = 1
          Text = '15'
        end
        object EditSecondPointY: TEdit
          Left = 131
          Top = 162
          Width = 145
          Height = 21
          TabOrder = 2
          Text = '-15'
        end
        object AddPointsCheckBox: TCheckBox
          Left = 15
          Top = 12
          Width = 217
          Height = 17
          Caption = #1052#1086#1076#1077#1083#1080#1088#1086#1074#1072#1090#1100' '#1076#1086#1087'.'#1090#1086#1095#1082#1080
          TabOrder = 3
        end
      end
      object EditFirstPointX: TEdit
        Left = 127
        Top = 54
        Width = 145
        Height = 21
        Align = alCustom
        TabOrder = 1
        Text = '15'
      end
    end
  end
  object GroupBox5: TGroupBox
    Left = 5
    Top = 153
    Width = 291
    Height = 216
    BiDiMode = bdLeftToRight
    Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1086#1087#1090#1080#1095#1077#1089#1082#1086#1081' '#1089#1080#1089#1090#1077#1084#1099
    ParentBiDiMode = False
    TabOrder = 13
    object Label2: TLabel
      Left = 3
      Top = 37
      Width = 110
      Height = 13
      Caption = #1060#1086#1082#1091#1089#1085#1086#1077' '#1088#1072#1089#1089#1090#1086#1103#1085#1080#1077
    end
    object Label17: TLabel
      Left = 237
      Top = 29
      Width = 12
      Height = 13
      Caption = #1084#1084
    end
    object Label8: TLabel
      Left = 3
      Top = 56
      Width = 165
      Height = 13
      Caption = #1056#1072#1079#1084#1077#1088' '#1101#1083#1077#1084#1077#1085#1090#1072' '#1076#1080#1089#1082#1088#1077#1090#1080#1079#1072#1094#1080#1080
    end
    object Label9: TLabel
      Left = 237
      Top = 56
      Width = 12
      Height = 13
      Caption = #1084#1084
    end
    object Label4: TLabel
      Left = 3
      Top = 88
      Width = 95
      Height = 13
      Caption = #1056#1072#1079#1088#1077#1096#1077#1085#1080#1077' '#1082#1072#1076#1088#1072
    end
    object Label7: TLabel
      Left = 163
      Top = 85
      Width = 6
      Height = 13
      Caption = #1093
    end
    object Label10: TLabel
      Left = 236
      Top = 83
      Width = 23
      Height = 13
      Caption = #1087#1080#1082#1089
    end
    object Label5: TLabel
      Left = 3
      Top = 115
      Width = 101
      Height = 13
      Caption = #1056#1072#1076#1080#1091#1089' '#1087#1086#1083#1103' '#1079#1088#1077#1085#1080#1103
    end
    object Label11: TLabel
      Left = 236
      Top = 110
      Width = 47
      Height = 13
      Caption = #1075#1088#1072#1076#1091#1089#1086#1074
    end
    object Label6: TLabel
      Left = 3
      Top = 144
      Width = 177
      Height = 13
      Caption = #1064#1080#1088#1080#1085#1072' '#1087#1086#1083#1103' '#1079#1088#1077#1085#1080#1103' '#1087#1086' '#1076#1080#1072#1075#1086#1085#1072#1083#1080
    end
    object Label12: TLabel
      Left = 237
      Top = 139
      Width = 47
      Height = 13
      Caption = #1075#1088#1072#1076#1091#1089#1086#1074
    end
    object Label13: TLabel
      Left = 3
      Top = 171
      Width = 147
      Height = 13
      Caption = #1064#1072#1075' '#1087#1086#1074#1086#1088#1086#1090#1072' '#1074#1086#1082#1088#1091#1075' '#1086#1089#1080' '#1054#1061
    end
    object Label14: TLabel
      Left = 236
      Top = 164
      Width = 47
      Height = 13
      Caption = #1075#1088#1072#1076#1091#1089#1086#1074
    end
    object Label15: TLabel
      Left = 3
      Top = 199
      Width = 147
      Height = 13
      Caption = #1064#1072#1075' '#1087#1086#1074#1086#1088#1086#1090#1072' '#1074#1086#1082#1088#1091#1075' '#1086#1089#1080' '#1054'Z'
    end
    object Label16: TLabel
      Left = 236
      Top = 191
      Width = 47
      Height = 13
      Caption = #1075#1088#1072#1076#1091#1089#1086#1074
    end
    object EditFoc: TEdit
      Left = 185
      Top = 29
      Width = 46
      Height = 21
      TabOrder = 0
      Text = '32'
      OnChange = EditFocChange
    end
    object EditElem: TEdit
      Left = 185
      Top = 56
      Width = 46
      Height = 21
      TabOrder = 1
      Text = '0.0055'
      OnChange = EditElemChange
    end
    object EditWidth: TEdit
      Left = 111
      Top = 83
      Width = 46
      Height = 21
      Alignment = taCenter
      TabOrder = 2
      Text = '2048'
      OnChange = EditWidthChange
    end
    object EditHeight: TEdit
      Left = 184
      Top = 83
      Width = 46
      Height = 21
      Alignment = taCenter
      TabOrder = 3
      Text = '2048'
    end
    object EditRad: TEdit
      Left = 184
      Top = 110
      Width = 46
      Height = 21
      Enabled = False
      TabOrder = 4
      Text = '9.9'
    end
    object EditDiag: TEdit
      Left = 186
      Top = 137
      Width = 45
      Height = 21
      Enabled = False
      TabOrder = 5
      Text = '28'
    end
    object EditStepOX: TEdit
      Left = 186
      Top = 164
      Width = 44
      Height = 21
      TabOrder = 6
      Text = '1'
    end
    object EditStepOZ: TEdit
      Left = 185
      Top = 191
      Width = 45
      Height = 21
      TabOrder = 7
      Text = '10'
    end
  end
  object Button1: TButton
    Left = 144
    Top = 769
    Width = 93
    Height = 25
    Caption = #1055#1086' '#1082#1072#1090#1072#1083#1086#1075#1072#1084
    TabOrder = 14
    OnClick = Button1Click
  end
  object OpenDialogDist: TOpenDialog
    Left = 240
    Top = 64
  end
  object BindingsList1: TBindingsList
    Methods = <>
    OutputConverters = <>
    Left = 844
    Top = 21
    object LinkControlToPropertyEnabled: TLinkControlToProperty
      Category = 'Quick Bindings'
      Control = AddPointsCheckBox
      Track = True
      Component = EditSecondPointX
      ComponentProperty = 'Enabled'
    end
    object LinkControlToPropertyEnabled2: TLinkControlToProperty
      Category = 'Quick Bindings'
      Control = AddPointsCheckBox
      Track = True
      Component = EditSecondPointY
      ComponentProperty = 'Enabled'
      InitializeControlValue = False
    end
    object LinkControlToPropertyEnabled3: TLinkControlToProperty
      Category = 'Quick Bindings'
      Control = AddPointsCheckBox
      Track = True
      Component = EditFirstPointY
      ComponentProperty = 'Enabled'
      InitializeControlValue = False
    end
    object LinkControlToPropertyEnabled4: TLinkControlToProperty
      Category = 'Quick Bindings'
      Control = AddPointsCheckBox
      Track = True
      Component = EditFirstPointX
      ComponentProperty = 'Enabled'
      InitializeControlValue = False
    end
  end
  object OpenDialog: TOpenDialog
    Left = 269
    Top = 629
  end
end
