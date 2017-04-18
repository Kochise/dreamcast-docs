/*----------------------------------------------------------------------------
|	biff.h
|
|		This contains BIFF record numbers
|
----------------------------------------------------------------------------*/

/* Maximum record size */
#define cbBiffMax 2080
#define wBiff2Mask 0xf1ff

/* BIFF record types */
#define rtNil	-1
#define rtDimensions 0
/* external copy expects these to be together */
#define rtBlank 1
#define rtInteger 2
#define rtNumber 3
#define rtLabel 4
#define rtBoolErr 5
#define rtFormula 6
#define rtString 7
/* end special order */
#define rtRw 8
#define rtBOF 9
#define rtEOF 10
#define rtIndex 11
#define rtCalcCount 12
#define rtCalcMode 13
#define rtPrec 14
#define rtRefMode 15
#define rtDelta 16
#define rtIter 17
#define rtProtect 18
#define rtPassword 19
#define rtHeader 20
#define rtFooter 21
#define rtExtCount 22
#define rtExtSheet 23
#define rtLbl 24
#define rtWnProtect 25
#define rtColBrk 26
#define rtRwBrk 27
#define rtNote 28
#define rtSel 29
#define rtFmt 30
 
#define rtGhostRw 32
#define rtMatrix 33
#define rt1904 34
#define rtExtName 35
#define rtColWidth 36
#define rtMiyRwGhost 37
#define rtLeftMargin 38
#define rtRightMargin 39
#define rtTopMargin 40
#define rtBottomMargin 41
#define rtPrintRwCol 42
#define rtPrintGrid 43

#define rtFilePass 47
#define rtFontCount 48		/* Chart files only */
#define rtFont 49
#define rtWin15Font 50
#define rtPrintSize 51		/* Chart files only */

#define rtInfoOpts 53		/* Workspace files only */
#define rtTbl 54
#define rtTbl2 55
#define rtWnDesk 56		/* Workspace files only */
#define rtZoom 57		/* Workspace files only */
#define rtBeginPref 58		/* Workspace files only */
#define rtEndPref 59		/* Workspace files only */
#define rtContinue 60
#define rtWindow1 61
#define rtWindow2 62
#define rtOldPane 63
#define rtBackup  64
#define rtPane    65
#define rtCodePage 66   /* Character set file was saved in */

#define rtCodePageTable 87 /* Mapping from file char-set to Super Code Page */

#define rtToolBar      88	/* Workspace files only */
#define rtXct          89
#define rtCrn          90
#define rtFileSharing  91
#define rtWriteAccess  92
#define rtObj          93
#define rtUncalced     94
#define rtSaveRecalc   95
#define rtTemplate     96
#define rtIntl         97	/* International macro */
#define rtClrtEntry    98
#define rtObjProtect   99

#define rtMpMacroCh 100       /* Multiplan's one or two command characters */
#define rtMpWindow  101       /* All Multiplan window info for ONE window */
#define rtMpOptions 102       /* Multiplan specific Options */
#define rtMpRecept  103       /* External Copy Recept */
#define rtMpStyle   104       /* Multiplan style info */
#define rtMpHeader  105       /* Multiplan Print Header reference */
#define rtMpFooter  106       /* Multiplan Print Footer reference */
#define rtMpPrint   107       /* Multiplan Print Options */
#define rtMpFormula 108       /* A MP formula which would not convert to Biff */
#define rtMpSplit   109       /* MP window split structures */
#define rtMpAlias   110       /* A MP alias structure */
#define rtMpEcr     111       /* A MP ecr structure */
#define rtMpFormat  112       /* Multiplan Default Format and Format Options */
#define rtMpString  113       /* Multiplan string (used with rtMpFormula) */
#define rtMpSel     114       /* Multiplan selection; same as rtSel */
#define rtMpColDef  115       /* Same as an rtGhostRw due to an Excel bug */
#define rtMpRowDef  116       /* Similar to a rtGhostRw due to an Excel bug */
#define rtMpGrid    117       /* Multiplan gridline record */
#define rtMpFmt     118       /* Same as an rtFmt for pics Excel can't parse */

#define rtCells     120   // state info only.  Does not occur in files
#define rtCell0     121   // state info only.  Does not occur in files
#define rtCell1     122   // state info only.  Does not occur in files
#define rtColInfo     125
#define rtRk          126
#define rtImData      127
#define rtGuts	      128
#define rtWsBool      129
#define rtGridSet     130
#define rtHCenter     131
#define rtVCenter     132
#define rtBundleSheet 133  /* only used in Workspace files */
#define rtWriteProt   134
#define rtAddIn       135
#define rtEdg	      136
#define rtPub	      137
#define rtNoteOff     138
#define rtISI	      139
#define rtCountry     140
#define rtHideObj     141
#define rtIbBundles   142
#define rtBundleHdr   143
#define rtSort		144
#define rtSub		145
#define rtPalette	146
#define rtStyle	147
#define rtISIRecord 	148
#define rtISINGraph	149
#define rtSound	150
#define rtSync		151
#define rtLpr		152
#define rtDxGCol       153 /* Global Column Width info */
#define rtRgGCW_DEBUG   154   /* Changed to 171 to avoid conflicts */

#define rtFnGroup	   154     /* Function group name */
#define rtFilterMode          155
#define rtBuiltinFnGroupCount 156     /* Count of builtin function groups */
#define rtEzFilterInfo	157
#define rtEzFilter	158

#define rtScl          160
#define rtSetup        161
#define rtFnProto      162     /* Function prototype: Addins only */
#define rtProjExtSh    163
/* XLB Files only: */
#define rtToolbarVer   164
#define rtImOOM		   165
#define rtToolbarPos   166
#define rtToolbarDef   167
#define rtDragDrop	  168		 /* Workspace Files only */
#define rtCoordList   169
#define rtDocDim	170	/* Graph only */
#define rtRgGCW        171
/* Chart colors (Graph only) */
#define rtChartColors	172
#define rtMovie			173
#define rtScenMan		174
#define rtScenario	175
#define rtSxview 176  /* View data structure */
#define rtSxvd 177  /* View dimensions */
#define rtSxvi 178  /* View items */
#define rtSxsi 179  /* View subitem list */
#define rtSxivd 180 /* Row and column dimensions */
#define rtSxli 181  /* Line items */
#define rtSxpi 182  /* Page items */
#define rtFaceNum    183
/* Document Routing */
#define rtDocRoute   184
#define rtRecipName  185

#define rtSSList 186 // AutoFill User-Defined Smart String List for XLB file

#define rtMaskImData 187 /* Same struct as rtImData */
#define rtShrFmla 188
#define rtMulRk	189
#define rtMulBlank 190

#define rtToolbarHdr 191 /* Toolbar header for toolbars attached to sheets */
#define rtToolbarEnd 192
#define rtMms        193 /* Menu modification */
#define rtAddMenu    194
#define rtDelMenu    195

#define rtTipHistory 196 // Rember Tip Wizard state across sessions.

#define rtSxdi 197
#define rtSxDb 198
#define rtSxFdb 199
#define rtSxDbb 200
#define rtSxNum  201
#define rtSxBool 202
#define rtSxErr  203	
#define rtSxInt  204
#define rtSxString  205
#define rtSxDtr 206
#define rtSxNil 207
#define rtSxTbl 208
#define rtSxTbrgiitm 209
#define rtSxTbpg 210
#define rtOBProj	211
#define rtWStgBook	212
#define rtSxIdstm   213
#define rtRString 214
#define rtDbCell 215
#define rtSxRng 216
#define rtSxIsxoper 217
#define rtBookBool 218
#define rtRevert 219
#define rtSxExt 220
#define rtScenProtect   221 /* scenarios protected on sheet ? */
#define rtOleSize	222
#define rtUDDesc 223 /*charting user-defined template description*/
#define rtXfv5 224
#define rtInterfaceHdr 225 /* Begin interface elements */
#define rtInterfaceEnd 226 /* End interface elements */
#define rtSxVs 227 // just a (swapped) word corresponding to the view's vs

#define rtNop 255

#define rtPublicHB 0x8000   /* High bit that marks public records */

// Charting rt's:
#define rtChartMin       0x1000
#define rtUnits          0x1001
#define rtChart          0x1002
#define rtSeries         0x1003
#define rtDL             0x1004
#define rtParseInfo      0x1005
#define rtDF             0x1006
#define rtLF             0x1007
#define rtBF             0x1008
#define rtMF             0x1009
#define rtAF             0x100a
#define rtPF             0x100b
#define rtAL             0x100c
#define rtST             0x100d
#define rtDataSequence   0x100e
#define rtDataScale      0x100f
#define rtTimeUnit       0x1010
#define rtSeriesFormula  0x1011
#define rtDatalabelFormat 0x1012
#define rtFormatIndex    0x1013
#define rtCrt            0x1014
#define rtLegend         0x1015
#define rtSeriesList     0x1016
#define rtBar            0x1017
#define rtLine           0x1018
#define rtPie            0x1019
#define rtArea           0x101a
#define rtScatter        0x101b
#define rtCrtLine        0x101c
#define rtAxis           0x101d
#define rtTick           0x101e
#define rtYRange         0x101f
#define rtXRange         0x1020
#define rtAxisLine       0x1021
#define rtCrtLink        0x1022
#define rtChartFormatSelection 0x1023
#define rtDefaultText    0x1024
#define rtText           0x1025
#define rtFontX          0x1026
#define rtObjLink        0x1027
#define rtExternalLink   0x1028
#define rtTextRotation   0x1029
#define rtTextScale      0x102a
#define rtTextBullet     0x102b
#define rtPicture        0x102c
#define rtArw            0x102d
#define rtArwLink        0x102e
#define rtArwHead        0x102f
#define rtChartLink      0x1030
#define rtChartSelection 0x1031
#define rtFrame          0x1032
#define rtBegin          0x1033
#define rtEnd            0x1034
#define rtPlotArea       0x1035
#define rtChartSize      0x1036
#define rtRelPos         0x1037
#define rtArwRelPos      0x1038
#define rtDlText         0x1039
#define rt3d             0x103a
#define rtRefSt          0x103b
#define rtPicF           0x103c
#define rtDropBar        0x103d
#define rtRadar          0x103e
#define rtSurf           0x103f
#define rtRadarArea      0x1040
#define rtAxisParent     0x1041
#define rtCrtAxis        0x1042
#define rtLegendXn       0x1043
#define rtShtProps       0x1044
#define rtSerToCrt       0x1045
#define rtAxesUsed       0x1046
#define rtDTVisible      0x1047
#define rtSBaseRef       0x1048
#define rtSerFirstChild  0x1049
#define rtSerParent      0x104a
#define rtSerAuxTrend    0x104b
                                   // 104c is missing: use me first
#define rtUnlinkedifmt   0x104d
#define rtIfmt           0x104e
#define rtPosCh          0x104f
#define rtAlRuns         0x1050
#define rtBRAI           0x1051
#define rtSSBOF          0x1052
#define rtExcludeRows    0x1053
#define rtExcludeCols    0x1054
#define rtOrient         0x1055
#define rtImport         0x1056
#define rtWinDoc         0x1057
#define rtMaxStatus      0x1058
#define rtMainWindow     0x1059
#define rtTargPrinter    0x105a
#define rtSerAuxErrbar   0x105b
#define rtClrtClient     0x105c
#define rtSerFmt		 0x105d
#define	rtLinkSel        0x105e

#define rtDebugVers      0x1100
