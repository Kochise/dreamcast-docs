IE sample DLL -- VIBECTRL Vibration Pack sample ActiveX control
---------------------------------------------------------------

* Purpose:
This sample demonstrates how to create an ActiveX control to handle the 
vibration pack. It can be used as it is (see sample HTML pages to see how
to use the control), or you can modify it (see notes below).

* Used by:
The html control.

* Registry entries:
[HKEY_CLASSES_ROOT\VibeCtrl.VibeCtrl]
@="VibeCtrl Class"
[HKEY_CLASSES_ROOT\VibeCtrl.VibeCtrl\CLSID]
@="{12137082-A1CB-11d3-B16A-0008C76BE5B9}"
[HKEY_CLASSES_ROOT\CLSID\{12137082-A1CB-11d3-B16A-0008C76BE5B9}\InprocServer32]
@="vibectrl.dll"
[HKEY_CLASSES_ROOT\CLSID\{12137082-A1CB-11d3-B16A-0008C76BE5B9}\TypeLib]
@="{12137080-A1CB-11d3-B16A-0008C76BE5B9}"
[HKEY_CLASSES_ROOT\TypeLib\{12137080-A1CB-11d3-B16A-0008C76BE5B9}\1.0\0]
@="vibectrl.dll"
[HKEY_CLASSES_ROOT\CLSID\{12137082-A1CB-11d3-B16A-0008C76BE5B9}\MiscStatus\1]
@="132497"

* Vibration notes:
Since none of the initial vibration devices support arbitrary waveforms, this 
sample does not do anything with them. Likewise, since none of the initial 
vibration devices support multiple simultaneous sources, this sample does 
nothing with them either.

* ATL notes:
Please read the readme.txt file in the ATL directory (..\atl\readme.txt).

* MIDL notes:
Make sure you have this line:
    #define MIDL_INTERFACE(x)   struct __declspec(uuid(x)) __declspec(novtable)
in a header file (see stdafx.h) before you include your generated interface header.

* Making changes:
If you make changes to the IVibrationControl interface you should create a new 
guid for the class and interface. Otherwise, if another game developer creates a 
web page on the Internet for the default vibration control, but your game 
includes a modified control, the system may not work because the web page's 
script will be expecting the methods of the original control. If you are using a 
walled garden approach (i.e., the game limits the pages the user can visit), this 
may not be an issue for you.

* Return value notes:
When you return an error code from an automation method, the scripting engine 
will display a script error. In these sample methods, incorrect parameters that 
should be known at the time the script is created (such as port values should 
always be in the range of 1-4, device values should always be in the range of 
1-2, and source values should always be in the range of 1-15) are treated as 
script errors. Parameters that are dependent on what vibration device is actually 
plugged in (if any at all) are not treated as script errors, but the methods do 
return false so this can be detected from the script. Also, if the script tries 
to vibrate a device that is not plugged in (or is no longer plugged in), the 
methods return false so the script can handle that situation.

* Functions in IVibrationControl (also see documentation on IVib and source code):
  C prototype: HRESULT Scan(void);
  From script: VibeCtrl.Scan();
    This function enumerates though all the contollers and internally keeps track
    of the vibration devices plugged in at the time this function is called. If 
    you think your user may be unplugging controllers and/or devices, you may want
    to call this on a timer or right before doing a vibration operation. If the
    user unplugs and replugs the vibration device (or controller), you will still
    need to call Scan again before you can access the device. Not calling Scan
    before you do other vibration control functions will simply result in that
    function returning false (and not generate a script error).
  C prototype: HRESULT IsPluggedIn(short nPort, short nDevice, BOOL *pbPlugged);
  From script: bool_result = VibeCtrl.IsPluggedIn(nPort, nDevice);
    This function returns whether the specified port (controller 1 - 4) and device
    (1 - 2) is currently plugged in. Scan must have been called sometime earlier,
    but if the device has been removed since Scan was called, it will return false.
  C prototype: HRESULT GetNumberOfSources(short nPort, short nDevice, short *pnSources);
  From script: num_sources = VibeCtrl.GetNumberOfSources(nPort, nDevice);
    Returns the number of vibration sources within the specified device.
  C prototype: HRESULT GetNumberOfSimultaneousSources(short nPort, short nDevice, short *pnSources);
  From script: num_sources = VibeCtrl.GetNumberOfSimultaneousSources(nPort, nDevice);
    Returns the number of simultation vibration sources that the specified device
    can handle.
  C prototype: HRESULT GetMinimumFrequency(short nPort, short nDevice, short nSource, double *pnFreq);
  From script: dbl_freq = VibeCtrl.GetMinimumFrequency(nPort, nDevice, nSource);
    Returns the minimum frequency that the specified vibration source can produce
    in *hertz*.
  C prototype: HRESULT GetMaximumFrequency(short nPort, short nDevice, short nSource, double *pnFreq);
  From script: dbl_freq = VibeCtrl.GetMaximumFrequency(nPort, nDevice, nSource);
    Returns the maximum frequency that the specified vibration source can produce
    in *hertz*.
  C prototype: HRESULT GetAxisOfVibration(short nPort, short nDevice, short nSource, BSTR *pbstrAxis);
  From script: str_axis = VibeCtrl.GetAxisOfVibration(nPort, nDevice, nSource);
    Returns the axis of vibration of the specified vibration source as a string 
    ("x", "y", "z", or "none").
  C prototype: HRESULT GetPosition(short nPort, short nDevice, short nSource, BSTR *pbstrPos);
  From script: str_pos = VibeCtrl.GetPosition(nPort, nDevice, nSource);
    Returns the position of the specified vibration source as a string ("front", 
    "back", "left", or "right").
  C prototype: HRESULT HasVariableIntensityCapability(short nPort, short nDevice, short nSource, VARIANT_BOOL *pbCap);
  From script: bool_cap = VibeCtrl.HasVariableInstensityCapability(nPort, nDevice, nSource);
    Returns true/false on whether the specified vibration source has the capability to
    produce variable intensities.
  C prototype: HRESULT HasContinuousVibrationCapability(short nPort, short nDevice, short nSource, VARIANT_BOOL *pbCap);
  From script: bool_cap = VibeCtrl.HasContinuousVibrationCapability(nPort, nDevice, nSource);
    Returns true/false on whether the specified vibration source has the capability to
    produce continuous vibration (based on auto stop time).
  C prototype: HRESULT HasDirectionalCapability(short nPort, short nDevice, short nSource, VARIANT_BOOL *pbCap);
  From script: bool_cap = VibeCtrl.HasDirectionalCapability(nPort, nDevice, nSource);
    Returns true/false on whether the specified vibration source has the capability to
    vibrate in a certain direction.
  C prototype: HRESULT HasArbitraryWaveformCapability(short nPort, short nDevice, short nSource, VARIANT_BOOL *pbCap);
  From script: bool_cap = VibeCtrl.HasArbitraryWaveformCapability(nPort, nDevice, nSource);
    Returns true/false on whether the specified vibration source has the capability to
    produce arbitrary waveforms.
  C prototype: HRESULT GetAutoStopTime(short nPort, short nDevice, short nSource, double *pfTime);
  From script: dbl_time = VibeCtrl.GetAutoStopTime(nPort, nDevice, nSource);
    Returns the auto stop time that the specified vibration source is set to produce in
    *seconds*. 
  C prototype: HRESULT SetAutoStopTime(short nPort, short nDevice, short nSource, double fTime);
  From script: bool_result = VibeCtrl.SetAutoStopTime(nPort, nDevice, nSource, fTime);
    Sets the auto stop time of the specified vibration source to the specified value in
    *seconds*. Note: this is set in the vibration device itself. Going to a new web page
    does not reset this value. It will keep this value until the device/controller is 
    unplugged or this value is changed via the control or IVib interface.
  C prototype: HRESULT Vibrate(short nPort, short nDevice, short nSource, VARIANT_BOOL bContinuousVib, BSTR bstrVibType, short nInitialPower, BSTR bstrDirection, double fFrequency, short nWavesPerStep, VARIANT_BOOL *pbResult);
  From script: bool_result = VibeCtrl.Vibrate(nPort, nDevice, nSource, bContinuousVib, bstrVibType, nInitialPower, bstrDirection, fFrequency, nWavesPerStep);
    Vibrates the specified device using the specified vibration parameters. bContinuesVib: 
    true/false. bstrVibType: "continuous"/"convergent"/"divergent". nInitialPower: 1-7. 
    bstrDirection: "forward"/"reverse". fFrequency (in hertz).

* Sample Web Pages:
  vibtest.html: main table of contents page for vibration control tests.
  vibstatus.html: displays status of plugged in vibration packs at the time the page is
    loaded. If the user unplugs a pack/controller while this page is up, the status change
    is not indicated.
  vibautostat.html: displays simpler status of currently plugged in vibration packs. As
    the user unplugs/replugs packs/controllers, the status is updated once a second.
  vibintensity.html: shows how to use the intensity parameter of the Vibrate function.
    The user must choose the pack on which to vibrate (it will always vibrate on the first
    source in the specified pack). Packs are scanned after the user clicks the Test button,
    so the packs/controllers can be unplugged and replugged while on this page.
  vibautostop.html: shows how to use the auto stop value of a vibration source. The user 
    must choose the pack on which to vibrate (it will always vibrate on the first source in 
    the specified pack). Packs are scanned after the user clicks the Test button, so the 
    packs/controllers can be unplugged and replugged while on this page.
  vibverge.html: shows how to use the convergent and divergent vibration types in the
    Vibrate function. The user must choose the pack on which to vibrate (it will always 
    vibrate on the first source in the specified pack). Packs are scanned after the user 
    clicks the Test buttons, so the packs/controllers can be unplugged and replugged while 
    on this page.
  vibfrequency.html: shows how to use the frequency parameter of the Vibrate function.
    The user must choose the pack on which to vibrate (it will always vibrate on the first
    source in the specified pack). Packs are scanned after the user clicks the Test button,
    so the packs/controllers can be unplugged and replugged while on this page.
  vibfunctions.html: allows the user to try out any of the Vibration Control functions 
    with his own parameters. The result of the function call (or script error) will be 
    displayed to the user. The control has not had Scan called on it when the page is loaded,
    so the user will likely want to click on the Scan button before doing anything else
    (although the user can use this page to see what the other functions return when Scan
    has *not* been called first).
