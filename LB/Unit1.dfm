object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 350
  ClientWidth = 567
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = Create
  PixelsPerInch = 96
  TextHeight = 13
  object Memo1: TMemo
    Left = 8
    Top = 8
    Width = 193
    Height = 257
    Lines.Strings = (
      'a:=16*3+1;'
      'b:=11+2*a;'
      'c:=3*a+2;'
      'if(b!=c) a:=4*b; else a:=2*b+3;'
      'k:=0; s:=0;'
      'repeat'
      '  k:=k+1;'
      '  s:=s+k;'
      'until k=10;')
    TabOrder = 0
  end
  object StringGrid1: TStringGrid
    Left = 207
    Top = 8
    Width = 170
    Height = 257
    ColCount = 2
    RowCount = 10
    TabOrder = 1
    ColWidths = (
      64
      82)
  end
  object StringGrid2: TStringGrid
    Left = 383
    Top = 8
    Width = 154
    Height = 257
    ColCount = 2
    RowCount = 10
    TabOrder = 2
  end
  object Button1: TButton
    Left = 8
    Top = 271
    Width = 513
    Height = 66
    Caption = #1040#1085#1072#1083#1080#1079#1080#1088#1086#1074#1072#1090#1100
    TabOrder = 3
    OnClick = Button1Click
  end
end
