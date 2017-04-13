------------------------------------------------------------------
    Microsoft Broadcast Architecture SDK UseVideo Readme File
                         August 1997
------------------------------------------------------------------

             (c) Copyright Microsoft Corporation, 1997

CONTENTS
========

Using the Video ActiveX Control


SUMMARY
=======

The UseVideo samples demonstrate presenting audio and video 
in an application, a Web browser, and in a control you create.
The following four programs are contained in the UseVideo sample:

1. Video Test Project (VidCntrl) demonstrates a project containing a 
   standard Microsoft(r) Visual Basic form that hosts and manipulates an instance 
   of the Microsoft(r) ActiveX(TM) control (the Video ActiveX control).

2. Video Web Page (WebTune) demonstrates embedding and using the 
   Video ActiveX control in a Web page.

3. Video Test Control (Vid_Tune) demonstrates creating a control that 
   contains the Video ActiveX control as a constituent control.

4. Video MFC Test describes building an application for Windows with 
   C++ classes from the Microsoft(r) Foundation Class Library (MFC).

In addition to presenting audio and video, these samples show how to embed 
a Video ActiveX control in your program and how to select different devices 
to provide input to such a control. If your computer contains a tuner card,
these samples show how to tune to a channel.

/////////////////////////////////////////////////////////////////////////////
MORE INFORMATION
================

The following information describes running the UseVideo samples.
For information on system requirements, see the Client Hardware Requirements 
section of the Broadcast Architecture Programmer's Reference or Broadcast 
Architecture Device-Driver Development Kit (DDK).

Note: For these samples to have maximum value, you should have the 
      following components installed:
      
   1. The Microsoft(r) Windows(r) 98 operating system, including the optional 
      TV Viewer component.

   2. Visual Basic version 5.0. For more information on installing 
      and using Visual Basic 5.0, see the Visual Basic 5.0 documentation.

   3. The Microsoft(r) Visual C++ development system, version 5.0. For more information 
      on installing and using Visual C++ 5.0, including MFC, see the Visual C++ 5.0 
      documentation. 


/////////////////////////////////////////////////////////////////////////////
To Run VidCntrl 
-----------------------------

1. Start Visual Basic 5.0.

2. When the New Project dialog box appears, click the Existing tab, and 
   open the VidCntrl.vbp project file.

3. On the Run menu, click Start.

4. When the Video Control Test form appears in run mode, click the 
   File Source (Async.) item in the list box to select it for the 
   video control's input source. Enter the file name of a particular 
   MPEG-1 file, along with the required path to locate the file, in 
   the text box, and click the Set Input button to assign the 
   file you specified as the input source for audio and video. Click the 
   Play button to play the file; click the Pause button to temporarily 
   suspend playing; click the Stop command button to stop the file. 
   Move the Volume slider to change the intensity of the video control's 
   sound and the Balance slider to change the video control's stereo balance.

5. If your computer contains a tuner card for analog television, click 
   the WDM TvTuner item in the list box to select it for the video control's 
   input source. Enter a channel number in the text box, and click the 
   Set Input button to tune your card to the channel number you specified.

VidCntrl Files
------------

VidCntrl.frm 
    This file contains the form image, in addition to the images of all the 
    elements on the form and the code to manipulate the video control. 
    The form's code uses the following properties and methods of the video control
    and other objects associated with video control. It:
    a. Declares and allocates storage for variables of BPCDevices and 
       BPCDeviceBase object types. 
    b. Obtains a reference to each device of the video control's Devices property. 
    c. Obtains the name of each device with the BPCDeviceBase Name property. 
    d. Determines if the computer contains any tuner cards that support the tuning 
       space for Analog Cable TV with the video control's TSDeviceCount method. 
    e. If the computer does, tunes to a channel with the video control's Tune 
       method.
    f. Sets the video control's Input property equal to one of the devices in
       the video control's Devices property. 
    g. Determines if the video control's input source is from a tuner with the 
       BPCDeviceBase HasChannel property. 
    h. If it is, sets the channel number of the tuner with the BPCDeviceBase Channel 
       property. 
    i. Determines if the video control's input source is from a file with the 
       BPCDeviceBase HasFilename property. 
    j. If it is, sets the name of the file with the BPCDeviceBase filename property. 
    k. For file sources, plays, pauses, stops, changes the volume and balance with the 
       video control's Run, Pause, Stop, Volume, and Balance properties respectively.

VidCntrl.vbp 
    This file is the makefile for the project.


/////////////////////////////////////////////////////////////////////////////
To Run WebTune
-------------

1. Start Microsoft Internet Explorer 4.0.

2. In Internet Explorer, click the Open command on the File menu. 
   When the Open dialog box appears, click Browse and locate
   the Vid_Test.htm file, and then click Open. When the Open 
   dialog box reappears, click OK.

3. When the Web page loads and Internet Explorer displays the page's 
   text and objects, enter the file name of a particular MPEG-1 file along
   with the required path to locate this file in the text box. Click 
   Set File to assign the file you specified as the input source
   for audio and video and to play the file, and click Stop File
   to stop the file.

4. If your computer contains a tuner card for analog television, enter 
   a channel number in the text box and click Set Chan to tune your card 
   to the channel number you specified.

WebTune File
------------

Vid_Test.htm 
    This file is an HTML document that contains the text, input elements,
    the Video ActiveX control object, and code written in
    Microsoft(r) Visual Basic(r) Scripting Edition (VBScript) that manipulates 
    the video control. The code enclosed in the SCRIPT tag uses all the same 
    properties and methods as those used in the VidCntrl.frm code.


/////////////////////////////////////////////////////////////////////////////
To Run Vid_Tune
-------------

1. Start Microsoft Visual Basic 5.0.

2. When the New Project dialog box appears, click the Existing tab and 
   open the Vid_Tune.vbg group project file.

3. On the Run menu, click Start.

4. When the form for the video test control appears in run mode, enter 
   the file name of a particular MPEG-1 file along with the required path 
   to locate this file in the text box.

5. Click File to assign the MPEG-1 file you specified as the 
   input source for audio and video and to play the file, and click Stop 
   to stop playing the file.

6. If your computer contains a tuner card for analog television, click any 
   of the channel buttons to assign the WDM TvTuner as the input source for 
   audio and video and to tune your card to the channel number specified by 
   the button.

Vid_Tune Files
------------

Vid_Tune.ctl 
    This file contains the images of all the elements on the control's 
    designer and the code to manipulate the video control. The designer's code 
    uses all the same properties and methods as those used in the VidCntrl.frm 
    code. In addition, code in the designer exposes custom properties, creates
    and sends a click event, and creates the MyTune method.

Test_Vid.frm 
    This file contains the form image, the image of the Video Test control, 
    and the code to manipulate the Video Test control. The form's code contains 
    the click event procedure that calls the Video Test control's MyTune method.

Vid_Tune.vbp 
    This file is the makefile for the Video Test Control project.

Test_Vid.vbp 
    This file is the makefile for the test project that verifies the Video 
    Test Control.

Vid_Tune.vbg 
    This file is the group file containing the Control project and the test 
    project.
   

/////////////////////////////////////////////////////////////////////////////
To Run VideoMFC
-----------------------------

1. Start Visual C++ 5.0.

2. On the File menu, click Open Workspace.

3. When the Open Workspace dialog box appears, go to the appropriate 
   directory and open the VdMFC.mak file. 

4. On the Build menu, click the Win32 Release configuration from 
   the Set Active Configuration menu item. After setting the project 
   configuration, click Build VdMFC.exe on the Build menu. After 
   building the project, click Execute VdMFC.exe on the Build menu. 
   
5. When the VdMFC application starts, click the File Source (Async.) 
   item in the list box to select it for the Vid control's input source. 
   Enter the file name of a particular MPEG-1 file along with the required 
   path to locate this file in the edit box. Click Set Input to assign the 
   MPEG-1 file you specified as the input source for audio and video. Click 
   Set File Name and then Play to start playing the MPEG-1 file you  
   specified. Click Pause to temporarily suspend playing. Click Stop to stop
   playing the file.

6. If your computer contains a tuner card for analog television, click the 
   WDM TvTuner item in the list box and then the Set Input button 
   to select it for the video control's input source. Enter a channel number 
   in the edit box, and then click Set Channels to tune your card to the 
   channel number you specified. Click On/Off Video to allow the Vid 
   control to receive video or to prevent it from receiving video.

/////////////////////////////////////////////////////////////////////////////
To Run VideoMFC from the Command Line 
-----------------------------

1. Open a Command Prompt window, switch to the directory on your 
   computer that contains the makefile (VdMFC.mak) and the source files 
   for the video MFC application, and then type the following exactly 
   as shown including the case of the text:
   NMAKE /f "VdMFC.mak" CFG="VdMFC - Win32 Release"

2. To run the built VdMFC application, switch to the \Release directory 
   created within the directory containing the source files, and type VdMFC.

VideoMFC Files
------------
The MFC AppWizard created all but one of the skeleton files for the VdMFC  
application. Most of the files did not require modification. The following 
summaries of the contents of each of the files that make up VdMFC are divided 
into the group requiring modifications and the group not requiring modifications. 

*********************
NOT CREATED BY MFC APPWIZARD
*********************
Vidtypes.h
    This file contains the definitions for all the constants and interfaces 
    that make up the Vid control. This file was not generated by the MFC
    AppWizard. This file was added to the project.

*********************
NO EDITING REQUIRED
*********************
VdMFC.h
    Main header file for the application that includes other project-specific 
    headers (including Resource.h) and defines the CVdMFCApp application class.
    This file was generated by the MFC AppWizard and did not require editing.

VdMFC.cpp
    This file is the main application source file that contains the application
    class CVdMFCApp. This file was generated by the MFC AppWizard and did not 
    require editing.

VdMFC.rc
    This file lists all the Microsoft Windows resources that the VdMFC application
    uses, including the icon stored in the RES subdirectory. This file was 
    generated by the MFC AppWizard and did not require editing.

Res\VdMFC.ico
    This is an icon file that is used as the application's icon.  This
    icon is included by the main resource file VdMFC.rc.

Res\VdMFC.rc2
    This file contains resources that are not edited by Microsoft Developer 
    Studio. This file was generated by the MFC AppWizard and did not 
    require editing.

VdMFC.mak 
    This file is the makefile for the project.

VdMFC.dsp 
    This file is the project file.

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named VdMFC.pch and a precompiled types file named StdAfx.obj. 
    These files were generated by the MFC AppWizard and did not 
    require editing.

Resource.h
    This is the standard header file, which defines new resource identifiers.
    This file was generated by the MFC AppWizard and did not 
    require editing. 

Bpcvid.h, Bpcvid.cpp 
    These files contain the CBPCVid class, which defines the behavior 
    of the object that provides streaming video functionality. These 
    files were generated by the MFC AppWizard and did not require editing.

Bpcbase.h, Bpcbase.cpp 
    These files contain the CBPCDeviceBase class, which defines the behavior 
    of the object that represents either an input or an output device for 
    the Vid control. These files were generated by the MFC AppWizard and 
    did not require editing.

*********************
EDITING REQUIRED
*********************
VdMFCDlg.h, VdMFCDlg.cpp -- the dialog box
    These files contain the CVdMFCDlg class. This class defines the 
    behavior of the application's main dialog box. These files were generated 
    by the MFC AppWizard. The following additions were made to these files:
    a. The header files that define the CBPCVid, CBPCDevices, and 
       CBPCDeviceBase classes and the data types and interfaces for the Vid
       control were included.
    b. ClassWizard was used to create variable names for the Vid control and 
       for values typed in the edit box for setting channels (m_channel) and 
       for strings typed in the edit box for setting file names (m_filename).
       The class definition was edited to create protected variables for the
       list box (box) and an available input or output device for the Vid
       control (m_id). The class definition was also edited to create a private 
       variable for a pointer to the IBPCDeviceBase interface.
    c. The constructor for this class was modified by the ClassWizard to assign 
       initial values to the channel and file name variables (m_channel = 0, 
       m_filename = _T("")). 
    d. The DoDataExchange method for this class was modified by the ClassWizard to associate 
       information stored in variables with the appropriate elements of the 
       application. This method associates variable information by using the 
       DDX_Control macro. 
    e. The class definition was edited to declare methods that are implemented  
       in the class. In the class implementation, the BEGIN_MESSAGE_MAP macro 
       was edited to associate click events of user-interface elements with 
       some class methods by using the ON_BN_CLICKED macro.
    f. The OnInitDialog method for this class was edited to: 
       Assign the list-box control of the user interface to the CListBox 
       variable, box.
       Obtain pointers to unknown and enumerate-variant objects that are part 
       of the MFC library.
       Declare and allocate a CBPCDevices object and assign the collection of 
       all the available input and output devices for the Vid control to this object.
       Assign the unknown object to the value returned from the custom 
       CBPCDevices::GetNewEnum method.
       Query the unknown object to obtain an enumerate-variant object and then 
       release the unknown object.
       Enter a while loop set to repeat until there are no more variants in 
       the enumerate-variant object. 
       Get the next variant in the enumerate-variant object and obtain a dispatch 
       for such a variant. Declare and allocate a CBPCDeviceBase object and assign 
       the dispatch value of the obtained variant to this object. Retrieve the 
       name of the device-base object with the CBPCDeviceBase::GetName method 
       and add it to the list box. Clear the variant.
       After exiting the while loop, release the enumerate-variant object. 
    g. The OnSetInput and OnSetOutput methods for this class were implemented to:
       Obtain pointers to unknown and enumerate-variant objects.
       Obtain an interface pointer to IBPCDeviceBase defined in Vidtypes.h.
       Declare and allocate a CBPCDevices object and assign the collection of 
       all the available input and output devices for the Vid control to it.
       Assign the unknown object to the value returned from the custom 
       CBPCDevices::GetNewEnum method.
       Query the unknown object to obtain an enumerate-variant object and then 
       release the unknown object.
       Enter a for loop set to repeat the number of times determined by the 
       CBPCVid::GetDeviceCount method.
       For each iteration of the loop, the methods were implemented to: 
         Obtain the next variant in the enumerate-variant object.
         Query the variant object to obtain an IBPCDeviceBase interface pointer.
         Get the name property of the device with the interface's get_Name method.
         Get the selected item in the list box and then get the string 
         associated with the item.
         If this string is the same as the device name, assign the video control's 
         input and output to that particular device with the SetInput and 
         SetOutput methods of the CBPCVid class. Also, assign the device to
         the private member variable for the device, m_pDeviceBase.
    h. The OnSetChannel method for this class was implemented to dispatch a 
       pointer to the selected item of the list box, then attach this pointer 
       to a CBPCDeviceBase variable with the CBPCDeviceBase::AttachDispatch 
       method, and then assign the channel number specified in the edit box with 
       the CBPCDeviceBase::SetChannel method.
    i. The OnVideoOn method for this class was implemented to reverse the 
       VideoOn value of the Vid control by first retrieving this value and then 
       setting it to the opposite value.
    j. The OnSetFile method for this class was implemented to assign the file 
       name specified in the edit box with the CBPCVid::SetFileName method.
    k. The OnPlay, OnPause, and OnStop methods for this class were 
       implemented to play, suspend play, and stop the file with the Run, 
       Pause, and Stop methods respectively of the CBPCVid class.

Bpcdev.h, Bpcdev.cpp 
    These files contain the CBPCDevices class, which defines the behavior 
    of the object that represents a collection of all the available input 
    and output devices for the Vid control. These files were generated 
    by the MFC AppWizard. 
    A declaration and an implementation were added for the GetNewEnum 
    method. This method retrieves an unknown object that refers to an 
    enumerate-variant object.

