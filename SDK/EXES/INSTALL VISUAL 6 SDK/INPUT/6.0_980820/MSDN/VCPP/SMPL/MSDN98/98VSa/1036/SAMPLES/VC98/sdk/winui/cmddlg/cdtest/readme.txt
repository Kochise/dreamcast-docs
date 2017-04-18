Common Dialogs


SUMMARY
=======

The CDTest sample demonstrates how to use the common dialog boxes provided 
in the Win32 API. In addition to displaying each default dialog box, the 
sample also allows you to modify the parameters passed to the functions to 
create variations of the common dialog boxes.

MORE INFORMATION
================

The CDTest sample dialog box makes use of the following controls:

  - The NULL structure check box.

    If you check this box, CDTest sends a NULL value for the common dialog 
    box creation structure to the common dialog box function. The common 
    dialog box should fail at startup. The common dialog box function 
    should return FALSE and set the correct CommDlgExtendedError.

  - The Preloaded Template check box(es)

    If you check this box, CDTest preloads a custom template resource and 
    puts the value of the handle to the resource in the hInstance member of 
    the common dialog box structure. CDTest does not create a custom
    template dialog box with this preloaded custom template unless you 
    also put the XXX_ENABLETEMPLATEHANDLE flag in the Flags box. For 
    example, to create a GetOpenFileName dialog box with a multiple
    selection files list box and a preloaded custom dialog box template, 
    put the following in the Flags box: 

        OFN_ENABLETEMPLATEHANDLE | OFN_ALLOWMULTISELECT 

    Check the Preloaded Template box.

  - The Reset button.

    The Reset button sets all the values for the common dialog box creation 
    structure back to the default values.

  - The Add and Clear buttons.

    These buttons are used to edit arrays that might be needed in common 
    dialog box creation. The Clear button clears the whole array. The Add 
    button adds what you have typed into the edit control of the combo box 
    to the left of these buttons.

  - The Multithread buttons.

    These buttons create two threads and two dialog boxes.

There is no way to create a NULL pointer as a value to be used for one of 
the dialog box elements that require a string pointer, such as the 
lpstrFile element of the GetOpenFileName structure. If you leave this field 
blank, CDTest will call GetOpenFileName with a valid pointer to a string 
containing a NULL character as its first value.

Notes:

  - ChooseFont dialog box.

    When you open the ChooseFont dialog box, you see a list of flags and 
    fonts on the right of the vertical dividing line. These do not affect 
    the ChooseFont dialog box creation. These only exist to allow the user 
    to compare the fonts found by ChooseFont with a list of fonts found 
    independently of ChooseFont. The lists should be identical when the 
    same flags are used. 

    If you want printer fonts to be listed in the ChooseFont dialog box, you 
    have to mark the Printer radio button in the "HDC Type" group.

    The ChooseFont dialog box is designed to give you a "No fonts found" 
    error if you don't include the CF_SCREENFONTS or CF_PRINTERFONTS flag 
    as part of the value in the Flags box. 

  - Open/Save dialog box.

    If you want to create a custom template dialog box with the 
    OFN_ENABLETEMPLATE flag, you need to specify the name of the template 
    in the lpTemplateName structure field. The names are:

      - opentemp1 (single selection files list box)
      - opentemp2 (multiple selection files list box)

  - Find/Replace dialog box.

    If you want to create a custom template dialog box with the 
    FR_ENABLETEMPLATE flag, you need to specify the name of the template
    in the lpTemplateName structure field. The names are:

      - frtemp1 (find template)
      - frtemp2 (replace template)
