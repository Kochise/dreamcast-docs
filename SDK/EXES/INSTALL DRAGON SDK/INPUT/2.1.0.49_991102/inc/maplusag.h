#ifndef _MAPLUSAG_H_
#define _MAPLUSAG_H_


// These match the numbers from HID
#define USAGE_PAGE_AXES     0x01  
#define USAGE_PAGE_BUTTONS  0x09
#define USAGE_GAMEPAD       0x05
#define USAGE_KEYBOARD      0x06
#define USAGE_X_AXIS        0x30
#define USAGE_Y_AXIS        0x31
#define USAGE_Z_AXIS        0x32
#define USAGE_RX_AXIS       0x33
#define USAGE_RY_AXIS       0x34
#define USAGE_RZ_AXIS       0x35
#define USAGE_SLIDER        0x36
#define USAGE_DIAL_AXIS     0x37
#define USAGE_WHEEL_AXIS    0x38


// These do not exist in HID, so we made the numbers up
#define USAGE_FIRST_BUTTON  0xFF00
#define USAGE_LAST_BUTTON   0xFF15
// Max num buttons is USAGE_LAST_BUTTON - USAGE_FIRST_BUTTON + 1
#define USAGE_A_BUTTON      0xFF00
#define USAGE_B_BUTTON      0xFF01
#define USAGE_C_BUTTON      0xFF02
#define USAGE_START_BUTTON  0xFF03
#define USAGE_LA_BUTTON     0xFF04
#define USAGE_RA_BUTTON     0xFF05
#define USAGE_DA_BUTTON     0xFF06
#define USAGE_UA_BUTTON     0xFF07
#define USAGE_X_BUTTON      0xFF08
#define USAGE_Y_BUTTON      0xFF09
#define USAGE_Z_BUTTON      0xFF0A
#define USAGE_D_BUTTON      0xFF0B
#define USAGE_LB_BUTTON     0xFF0C
#define USAGE_RB_BUTTON     0xFF0D
#define USAGE_DB_BUTTON     0xFF0E
#define USAGE_UB_BUTTON     0xFF0F
#define USAGE_RTRIG_BUTTON  0xFF10
#define USAGE_LTRIG_BUTTON  0xFF11
#define USAGE_AN3_BUTTON    0xFF12
#define USAGE_AN4_BUTTON    0xFF13
#define USAGE_AN5_BUTTON    0xFF14
#define USAGE_AN6_BUTTON    0xFF15


#endif //_MAPLUSAG_H_
