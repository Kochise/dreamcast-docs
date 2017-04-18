Dreamcast Peripheral Model Data

All models were created using "LIGHT WAVE 3D 5.6J".


<> Data Format
  Data are in the following formats:

  Nj------ Data of model (extension: nja), texture (extension: pvr) and 
           motion (extension: nam) which is converted by Ninja_Export

  Parts--- Data of each part created by modeler of "LIGHT WAVE 3D 5.6J" 
           (extension: lwo)

  Scene--- Data of parts set in place in the layout of "LIGHT WAVE 3D 5.6J" 
           (extension: lws)


<> Data Structure
  Data are composed as follows.

  ArcadeStick------Nj-----Arcadestick.nja       Data of Dreamcast arcade stick
                |      |                        
                |      |--Arcadestick_VM.nja    Data of Dreamcast arcade stick 
                |                               with visual memory attached
                |
                |--Parts--Arcadestick.lwo etc.  Data of each part, such as unit, buttons and stick
                |
                |--Scene--Arcadestick.lws       Scene file of Dreamcast arcade stick
                        |
                        |-Arcadestick_VM.lws    Scene file of Dreamcast arcade stick
                                                with visual memory attached

  Controller-------Nj-----DC_Controller.nja     Data of Dreamcast controller
                |      |
                |      |--DC_Controller_VM.nja  Data of Dreamcast controller 
                |                               with visual memory attached
                |                               
                |--Parts--CPBody12.lwo etc.     Data of each part, such as unit, buttons and stick
                |
                |--Scene--DC_Controller.lws     Scene file of Dreamcast controller
                        |
                        |-DC_Controller_VM.lws  Scene file of Dreamcast controller
                                                with visual memory attached

  LightGun---------Nj-----Gun.nja               Data of Dreamcast gun
                |                               (with visual memory attached)
                |--Parts--Gun05.lwo etc.        Data of each part, such as unit, buttons and trigger
                |
                |--Scene--Gun.lws               Scene file of Dreamcast gun
                                                (with visual memory attached)

  Dreamcast--------Nj-----Dreamcast04.nam       Motion data of Dreamcast unit
                |      |                        (Rotation of GD, Open/close of the disc door)
                |      |--Dreamcast04.nja       Data of Dreamcast unit
                |      |
                |      |--GD-R.pvr              Texture data of GD label
                |                               
                |--Parts--Dreamcast etc.        Data of each part, such as unit, 
                |                               disc door and buttons
                |
                |--Scene--Dreamcast04.lws       Scene file of Dreamcast unit

  Fishing----------Nj-----FishCon1.nam          Motion data of fishing controller
                |      |                        (Rotation of the reel handle, movement
                |      |                         of the unit and thumb pad)
                |      |--FishCon1.nja          Model data of fishing controller
                |
                |--Parts--Fish_stick.lwo        Data of each part, such as unit, 
                |                               reel handle and buttons
                |
                |--Scene--FishCont1.lws         Scene file of fishing controller

  Vibration--NJ-------------------Puru_pack.nja Data of puru-puru pack
           |    |
           |    |--Puru_pack_DCCon_CPBody12.nam Motion data of puru-puru pack attached to 
           |    |                               Dreamcast controller (vibrating)
           |    |--Puru_pack_DCCon_CPBody12.nja Data of puru-puru pack attached to 
           |                                    Dreamcast controller
           |-Parts----------------Puru_Pack.lwo Data of puru-puru pack
           |                                    
           |-Scene----------------Puru_pack.lws Scene file of puru-puru pack 
                      |
                      |-----Puru_pack_DCCon.lws Scene file of puru-puru pack attached to 
                                                Dreamcast controller

  Racing-----------Nj-----Racing_Cont.nja       Model data of racing controller with 
                |                               visual memory attached
                |--Parts--Unite.lwo etc.        Data of each part, such as unit, steering wheel, 
                |                               lever and buttons
                |
                |--Scene--Racing_Cont.lws       Scene file of racing controller with 
                                                visual memory attached

  VisualMemory-----Nj--------VM.nja             Data of visual memory with the cap on
                |                               
                |--Parts-----VM_cap.lwo         Data of Visual Memory's cap
                |         |
                |         |--VM_nocap.lwo       Data of Visual Memory without the cap
                |
                |--Scene-----Controller_VM.lws  Scene file of visual memory attached to 
                          |                     Dreamcast controller
                          |--VM.lws             Scene file of visual memory with the cap on
                                                
  SIP--------------Nj--------SIP.nja            Data of sound input peripheral 
                |         |                     with microphone attached
                |         |                     
                |         |--SIP_VM_Contro.nja  Data of Dreamcast controller with 
                |                               visual memory and sound input peripheral attached
                |--Parts-----Mic.lwo            Data of microphone
                |         |
                |         |--SIP.lwo            Data of sound input peripheral
                |
                |--Scene-----SIP.lws            Scene file of sound input peripheral with microphone
                          |                     attached
                          |                     
                          |--SIP_VM_Contro.lws  Scene file of Dreamcast controller with 
                                                visual memory and sound input peripheral attached

