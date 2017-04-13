// Menu ID's

#define IDM_EXIT            (WM_USER+4)

#define IDM_GAME_CHECKERS   (WM_USER+10)
#define IDM_GAME_GIVEAWAY   (WM_USER+11)
#define IDM_PLAYERS         (WM_USER+13)

#define IDM_BACK            (WM_USER+20)
#define IDM_FORWARD         (WM_USER+21)
#define IDM_SETUP_BOARD     (WM_USER+22)
#define IDM_CONTINUE        (WM_USER+23)

#define IDM_FLIP            (WM_USER+53)
#define IDM_SETDRAWMOVES    (WM_USER+72)
#define IDM_MUST_JUMP       (WM_USER+73)

#define IDM_ABOUT           (WM_USER+79)

// Some dialog ID's

#define IDT_COMPANY_NAME    (WM_USER+80)
#define IDT_FILE_DESC       (WM_USER+81)
#define IDT_PROD_VER        (WM_USER+82)
#define IDT_COPYRIGHT       (WM_USER+83)
#define IDT_TRADEMARKS      (WM_USER+84)

#define DLG_VERFIRST        IDT_COMPANY_NAME
#define DLG_VERLAST         IDT_TRADEMARKS

// Setup menu ID's

#define IDM_SETUP_EXIT      (WM_USER+93)

// Other ID's

#define WM_OTHERINIT        (WM_USER+100)


// SetWeights dialog

#define IDEC_PIECE                  111
#define IDEC_BLANK                  112
#define IDEC_MOVE_THEORY            113
#define IDEC_CENTER_POSITION        114
#define IDEC_DOUBLE_CORNERS         115
#define IDEC_KING_ROW               116
#define IDEC_KING                   118
#define IDEC_EDGES                  119

// Config Depth Dialog

#define IDEC_RECURSION_DEPTH        201
#define ID_HELP                     203
#define IDEC_PRUNING_DEPTH          204
#define IDEC_PRUNING_WIDTH          206
#define IDRB_P1_HUMAN               103
#define IDRB_P1_COMPUTER            110
#define IDRB_P1_NETWORK             117
#define IDRB_P2_HUMAN               121
#define IDRB_P2_COMPUTER            122
#define IDRB_P2_NETWORK             123
#define IDB_P1_COMPUTER_SETUP       3
#define IDB_P1_NETWORK_SETUP        4
#define IDB_P2_COMPUTER_SETUP       8
#define IDB_P2_NETWORK_SETUP        9
#define IDCB_MUST_JUMP              101
#define IDCB_OPENING_BOOK           102
#define IDCB_SHOW_COMMAND_WIN       105
#define IDCB_SHOW_MOVES             106
#define IDCB_SHOW_TIMER             107
#define IDCB_SHOW_COMMAND           108
#define IDCB_SHOW_OPEN_INFO         129
#define IDCB_SHOW_DEBUG             130
#define IDCB_USE_MEM_POSITIONS      104
#define IDCB_USE_MOVE_THEORY        109
#define IDCB_MOVE_SHUFFLING         120
#define IDB_WEIGHTS                 124
#define IDCB_EQUAL_MOVE_SKIPPING    125
#define IDCB_GOOD_MOVE_SKIPPING     126
#define IDCB_ALPHA_BETA_PRUNING     127
#define IDCB_USE_OPENING_BOOK       128
#define IDEC_BOOK_MOVE_DEPTH        131
#define IDEC_FORMATION              132
#define IDEC_FORMATION_CUTOFF       133
#define IDB_PLAYER1                 137
#define IDB_PLAYER2                 138
#define IDCB_SHORT_JUMP_EVAL        134
#define IDRB_SHORT_JUMP_EVAL        135
#define IDEC_MAX_MOVES              136

// Form specific menu items and helper messages

#ifndef NO_FORM
#define EM_GIVEFORMTOHWND           (WM_USER + 1000)
#define IDM_ADDRESS                 (WM_USER + 1001)
#define IDM_HINT                    (WM_USER + 1002)
#define IDM_SAVE                    (WM_USER+2)
#endif

#define IDM_BASE_LEVEL              (WM_USER + 5000) // from IDM_BASE_LEVEL through base level plus 20 are reserved
