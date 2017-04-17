#ifndef __INPUT_H               // guard against multiple inclusion
#define __INPUT_H

/********************************************************************
 * input.h
 *
 * Description
 *    DInput wrappers and helpers
 ********************************************************************/

/********************************************************************
 * Includes
 ********************************************************************/
#include <dinput.h>             // DInput data types and prototypes
#include <maplusag.h>           // Controller defines

/********************************************************************
 * Defines
 * (make referencing controller buttons a little more convenient)
 ********************************************************************/
#define JOYSTICK_IDX_A          (USAGE_A_BUTTON     - USAGE_FIRST_BUTTON)      // 0         
#define JOYSTICK_IDX_B          (USAGE_B_BUTTON     - USAGE_FIRST_BUTTON)      // 1         
#define JOYSTICK_IDX_C          (USAGE_C_BUTTON     - USAGE_FIRST_BUTTON)      // 2         
#define JOYSTICK_IDX_START      (USAGE_START_BUTTON - USAGE_FIRST_BUTTON)      // 3         
#define JOYSTICK_IDX_LA         (USAGE_LA_BUTTON    - USAGE_FIRST_BUTTON)      // 4         
#define JOYSTICK_IDX_RA         (USAGE_RA_BUTTON    - USAGE_FIRST_BUTTON)      // 5         
#define JOYSTICK_IDX_DA         (USAGE_DA_BUTTON    - USAGE_FIRST_BUTTON)      // 6         
#define JOYSTICK_IDX_UA         (USAGE_UA_BUTTON    - USAGE_FIRST_BUTTON)      // 7         
#define JOYSTICK_IDX_X          (USAGE_X_BUTTON     - USAGE_FIRST_BUTTON)      // 8         
#define JOYSTICK_IDX_Y          (USAGE_Y_BUTTON     - USAGE_FIRST_BUTTON)      // 9         
#define JOYSTICK_IDX_Z          (USAGE_Z_BUTTON     - USAGE_FIRST_BUTTON)      // 10        
#define JOYSTICK_IDX_D          (USAGE_D_BUTTON     - USAGE_FIRST_BUTTON)      // 11        
#define JOYSTICK_IDX_LB         (USAGE_LB_BUTTON    - USAGE_FIRST_BUTTON)      // 12        
#define JOYSTICK_IDX_RB         (USAGE_RB_BUTTON    - USAGE_FIRST_BUTTON)      // 13        
#define JOYSTICK_IDX_DB         (USAGE_DB_BUTTON    - USAGE_FIRST_BUTTON)      // 14        
#define JOYSTICK_IDX_UB         (USAGE_UB_BUTTON    - USAGE_FIRST_BUTTON)      // 15        
#define JOYSTICK_IDX_RTRIG      (USAGE_RTRIG_BUTTON - USAGE_FIRST_BUTTON)      // 16        
#define JOYSTICK_IDX_LTRIG      (USAGE_LTRIG_BUTTON - USAGE_FIRST_BUTTON)      // 17        
#define JOYSTICK_IDX_AN3        (USAGE_AN3_BUTTON   - USAGE_FIRST_BUTTON)      // 18        
#define JOYSTICK_IDX_AN4        (USAGE_AN4_BUTTON   - USAGE_FIRST_BUTTON)      // 19        
#define JOYSTICK_IDX_AN5        (USAGE_AN5_BUTTON   - USAGE_FIRST_BUTTON)      // 20        
#define JOYSTICK_IDX_AN6        (USAGE_AN6_BUTTON   - USAGE_FIRST_BUTTON)      // 21        
#define JOYSTICK_IDX_POS        (USAGE_LAST_BUTTON  - USAGE_FIRST_BUTTON + 1)  // 22        
#define JOYSTICKMAXBUTTONS      (USAGE_LAST_BUTTON  - USAGE_FIRST_BUTTON + 1)  // 22

#define JOYSTICK_A          (1 << JOYSTICK_IDX_A)      // 1 << 0         0x000001
#define JOYSTICK_B          (1 << JOYSTICK_IDX_B)      // 1 << 1         0x000002
#define JOYSTICK_C          (1 << JOYSTICK_IDX_C)      // 1 << 2         0x000004
#define JOYSTICK_START      (1 << JOYSTICK_IDX_START)  // 1 << 3         0x000008
#define JOYSTICK_LA         (1 << JOYSTICK_IDX_LA)     // 1 << 4         0x000010
#define JOYSTICK_RA         (1 << JOYSTICK_IDX_RA)     // 1 << 5         0x000020
#define JOYSTICK_DA         (1 << JOYSTICK_IDX_DA)     // 1 << 6         0x000040
#define JOYSTICK_UA         (1 << JOYSTICK_IDX_UA)     // 1 << 7         0x000080
#define JOYSTICK_X          (1 << JOYSTICK_IDX_X)      // 1 << 8         0x000100
#define JOYSTICK_Y          (1 << JOYSTICK_IDX_Y)      // 1 << 9         0x000200
#define JOYSTICK_Z          (1 << JOYSTICK_IDX_Z)      // 1 << 10        0x000400
#define JOYSTICK_D          (1 << JOYSTICK_IDX_D)      // 1 << 11        0x000800
#define JOYSTICK_LB         (1 << JOYSTICK_IDX_LB)     // 1 << 12        0x001000
#define JOYSTICK_RB         (1 << JOYSTICK_IDX_RB)     // 1 << 13        0x002000
#define JOYSTICK_DB         (1 << JOYSTICK_IDX_DB)     // 1 << 14        0x004000
#define JOYSTICK_UB         (1 << JOYSTICK_IDX_UB)     // 1 << 15        0x008000
#define JOYSTICK_RTRIG      (1 << JOYSTICK_IDX_RTRIG)  // 1 << 16        0x010000
#define JOYSTICK_LTRIG      (1 << JOYSTICK_IDX_LTRIG)  // 1 << 17        0x020000
#define JOYSTICK_AN3        (1 << JOYSTICK_IDX_AN3)    // 1 << 18        0x040000
#define JOYSTICK_AN4        (1 << JOYSTICK_IDX_AN4)    // 1 << 19        0x080000
#define JOYSTICK_AN5        (1 << JOYSTICK_IDX_AN5)    // 1 << 20        0x100000
#define JOYSTICK_AN6        (1 << JOYSTICK_IDX_AN6)    // 1 << 21        0x200000
#define JOYSTICK_POS        (1 << JOYSTICK_IDX_POS)    // 1 << 22        0x400000

/********************************************************************
 * Macros
 ********************************************************************/
#define ISDOWN(Value)       (Value   & 0x80)
#define WM_JOYSTICK         (WM_USER + 2000)

/********************************************************************
 * Public functions - Create/Destroy
 ********************************************************************/
BOOL    CreateDirectInput(HINSTANCE hinstApp, HWND hwndApp);
void    DestroyDirectInput(void);

/********************************************************************
 * Public functions - Helpers
 ********************************************************************/
DWORD   ReadDirectInputDevices(void);
HRESULT GetIMEInput(LPTSTR pszText);

/********************************************************************
 * Global variables
 ********************************************************************/
extern LPDIRECTINPUTDEVICE2 g_pdidevice2Joystick;
extern BYTE                 g_rgvButtons[JOYSTICKMAXBUTTONS];

#endif // __INPUT_H
