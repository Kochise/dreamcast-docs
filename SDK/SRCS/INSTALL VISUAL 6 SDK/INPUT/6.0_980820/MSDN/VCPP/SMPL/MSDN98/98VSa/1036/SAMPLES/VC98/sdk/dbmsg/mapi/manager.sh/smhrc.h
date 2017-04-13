/*
 *  S M H R C . H
 *
 *  Sample mail handling hook
 *  Resource IDs and configuration defines
 *
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#ifdef WIN16
#define DS_3DLOOK           0
#define RICHEDIT_CLASS      "RichEd16"
#else
#ifndef RICHEDIT_CLASS
#define RICHEDIT_CLASS      "RichEdit"
#endif
#endif

/*
 *  Configuration Property Sheets
 */

#define SMH_ProviderName    100
#define SMH_GeneralTab      101
#define SMH_GeneralPage     101
#define SMH_FilterTab       102
#define SMH_FilterPage      102
#define SMH_ExclusionPage   103
#define SMH_ExclusionTab    103
#define SMH_OofPage         104
#define SMH_OofTab          104
#define SMH_PropertiesPage  105
#define SMH_ResponsePage    106
#define SMH_ResponseTab     106
#define SMH_SoundsPage      107
#define SMH_SoundsTab       107

/*
 *  Misc. String Resources
 */

#define SMH_FolderComment   150

/*
 *  Property Sheet Control IDs
 */

#define ID_AddToPab         200
#define ID_DeletedGrp       201
#define ID_DownArrow        202
#define ID_DownArrowDis     203
#define ID_DownArrowInv     204
#define ID_EditFilter       205
#define ID_ExclusionLB      207
#define ID_FilterDown       208
#define ID_FilterOrderLB    209
#define ID_FilterUp         210
#define ID_InboundGrp       211
#define ID_NewExclusion     212
#define ID_NewFilter        213
#define ID_OofEnabled       214
#define ID_OofText          215
#define ID_RmvExclusion     216
#define ID_RmvFilter        217
#define ID_SentMailGrp      218
#define ID_UpArrow          219
#define ID_UpArrowDis       220
#define ID_UpArrowInv       221

#define ID_Frame            222
#define ID_Toolbar          223

#define ID_Font             224
#define ID_FontSize         225

#define ID_Bold             226
#define ID_Italic           227
#define ID_Underline        228

#define ID_Bullet           229
#define ID_Left             230
#define ID_Center           231
#define ID_Right            232
#define ID_Indent           233
#define ID_Collapse         234

#define ID_Import           235
#define ID_Export           236

#define ID_Color            250
#define ID_ColorAuto        251
#define ID_ColorBlack       252
#define ID_ColorMaroon      253
#define ID_ColorGreen       254
#define ID_ColorOlive       255
#define ID_ColorBlue        256
#define ID_ColorPurple      257
#define ID_ColorTeal        258
#define ID_ColorGray        259
#define ID_ColorSilver      260
#define ID_ColorRed         261
#define ID_ColorLime        262
#define ID_ColorYellow      263
#define ID_ColorNavy        264
#define ID_ColorFuchia      265
#define ID_ColorAqua        266
#define ID_ColorWhite       267

#define ID_NYI              999

/*
 *  Configuration Propertysheets
 */

#define ID_AnyRecip         301
#define ID_BccRecip         302
#define ID_Body             303
#define ID_CcRecip          304
#define ID_HasAttach        305
#define ID_MsgClass         306
#define ID_Sender           307
#define ID_Subject          308
#define ID_ToRecip          309

#define ID_ArchTarg         319
#define ID_ArchTargYr       320
#define ID_LeaveMsg         321
#define ID_DeleteMsg        322
#define ID_FilterMsg        323
#define ID_Folder           324
#define ID_Name             325
#define ID_NotMatch         326
#define ID_ReplyFwd         327

#define ID_Sound            330
#define ID_Store            331
#define ID_TargetGrp        332
#define ID_Txt1             333
#define ID_Txt2             334
#define ID_Txt3             335
#define ID_Txt4             336
#define ID_Txt5             337
#define ID_Txt6             338
#define ID_TypeGrp          339
#define ID_Value            340

#define SMH_ExclusionEdit   400
#define ID_ExclusionClass   401

#define ID_Reply            501
#define ID_Forward          502
#define ID_Recip            503
#define ID_Email            504
#define ID_Type             505
#define ID_Annotation       506
#define ID_PickRecip        507

#define ID_SoundsGrp        600
#define ID_LoPri            601
#define ID_NormPri          602
#define ID_HiPri            603

/*
 *  DLL Icon
 */

#define ID_Icon             431

/*
 *  Configuration Wizard
 */

#define WIZ_BASE            500
#define PAGE_INC             10
#define szWizardDialog      "SMH_WizardDialog"
#define ID_SentMailTxt      500
#define ID_SentMail         501
#define ID_SentMailYr       502
#define ID_DeletedTxt       510
#define ID_Deleted          511
#define ID_DeletedYr        512
#define ID_InboundTxt       520
#define ID_Inbound          521
#define ID_UnreadTxt        530
#define ID_UnreadTxt2       531
#define ID_Unread           532
