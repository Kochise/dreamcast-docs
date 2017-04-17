Direct3D sample program -- ComplexModifierVolumes
-----------------------------------------

* Purpose:
This sample demonstrates how to use complex modifier volumes on WinCE
for Dreamcast.  This is also known as "Parameter Selection Mode modifier
volumes".  The sample displays a rotating sphere with a triangle above it;
the triangle "casts" a volume onto the sphere -- any pixels in that volume
are rendered with a different texture than the rest of the sphere.

Multitexturing while using complex modifier volumes is not supported --
Texture0 and Texture1 are treated as the 'outside' and 'inside' volumes,
respectively.  If only Texture0 is set then the same texture and U, V
coordinates are used both inside and outside the volume.

This sample does not demonstrate how to modify lighting values via modifier
volumes, but it is simple enough to do -- Two new flags in the FVF definition
(D3DFVF_DIFFUSE1 and D3DFVFSPECULAR1) control the presence of alternative
lighting values for vertices that are used within the volume, similarly the 
D3DDP_DONOTLIGHT1 flag used when rendering prevents lighting the 'inside' color
values in the same way that D3DDP_DONOTLIGHT prevents lighting the 'outside'
color values.

* Required Files\Parameters:
None

* To exit this sample, press the 'Send ESC' button in DCTool or
press <Esc> on the keyboard
