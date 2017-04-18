/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    romanji.cxx

Abstract:

    This file initializes an array of keys in the romanji layout.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/

				
#include "precomp.hxx"


// This array defines the layout for the Romanji software keyboard.
// Keys must be listed in sorted order by location on keyboard, 
// left to right, and then top to bottom.  The binary search 
// is dependent on this sort order.

// Virtual Key codes are filled in, but many are not used; instead, we just send
// the unicode for the character in a WM_CHAR message.

SOFTKEY g_rgskRomanji[] = 
    {
//       X   Y Wid Hgt               characters on key
//       ----------------------------------------------------------------------------------
        {0,  0,  1,  1,				{SYMBOLS_DOLLAR_SIGN,       },	}, 
        {1,  0,  1,  1,				{SYMBOLS_PERCENT,           },	},
        {2,  0,  1,  1,				{SYMBOLS_CIRCUMFLEX,        },	},
        {3,  0,  1,  1,				{SYMBOLS_AMPERSAND,         },	},
        {4,  0,  1,  1,				{SYMBOLS_ASTERISK,          },	}, 
        {5,  0,  1,  1,				{SYMBOLS_EMDASH,            },	},
#ifdef KANJI
        {6,  0,  1,  1,				{SYMBOLS_LOWLINE,           },	},
#else  // KANJI
        {6,  0,  1,  1,				{SYMBOLS_ROMAN_LOWLINE,     },	},
#endif // KANJI
        {7,  0,  1,  1,				{SYMBOLS_ROMAN_LEFT_PAREN,  },	},
        {8,  0,  1,  1,				{SYMBOLS_ROMAN_RIGHT_PAREN, },	}, 
        {9,  0,  1,  1,				{SYMBOLS_SEMICOLON,         },	VK_SEMICOLON},
        {10, 0,  1,  1,				{SYMBOLS_SINGLE_QUOTE,      },	}, 
        {11, 0,  1,  1,				{SYMBOLS_DOUBLE_QUOTE,      },	}, 
        {12, 0,  1,  1,				{SYMBOLS_EXCLAMATION,       },	},
        {13, 0,  1,  1,				{SYMBOLS_QUESTION,          },	}, 
        {14, 0,  1,  1,				{ROMAN_PLUS,                },	VK_ADD},
        {15, 0,  1,  1,				{ROMAN_ONE,                 },	VK_NUMPAD1},
        {16, 0,  1,  1,				{ROMAN_TWO,                 },	VK_NUMPAD2}, 
        {17, 0,  1,  1,				{ROMAN_THREE,               },	VK_NUMPAD3}, 
        
        {0,  1,  1,  1,				{ROMAN_A,                   },	'A'},
        {1,  1,  1,  1,				{ROMAN_B,                   },	'B'},
        {2,  1,  1,  1,				{ROMAN_C,                   },	'C'},
        {3,  1,  1,  1,				{ROMAN_D,                   },	'D'},
        {4,  1,  1,  1,				{ROMAN_E,                   },	'E'},
        {5,  1,  1,  1,				{ROMAN_F,                   },	'F'},
        {6,  1,  1,  1,				{ROMAN_G,                   },	'G'},
        {7,  1,  1,  1,				{ROMAN_H,                   },	'H'},
        {8,  1,  1,  1,				{ROMAN_I,                   },	'I'},
        {9,  1,  1,  1,				{SYMBOLS_GRAVE_ACCENT,      },	}, 
        {10, 1,  1,  1,				{SYMBOLS_LESSTHAN,          },	},
        {11, 1,  1,  1,				{SYMBOLS_GREATERTHAN,       },	},
        {12, 1,  1,  1,				{SYMBOLS_VERTICAL_LINE,     },	},
        {13, 1,  1,  1,				{SYMBOLS_AT,                },	},  
        {14, 1,  1,  1,				{ROMAN_MINUS,               },	VK_SUBTRACT},
        {15, 1,  1,  1,				{ROMAN_FOUR,                },	VK_NUMPAD4},
        {16, 1,  1,  1,				{ROMAN_FIVE,                },	VK_NUMPAD5}, 
        {17, 1,  1,  1,				{ROMAN_SIX,                 },	VK_NUMPAD6}, 
        
        {0,  2,  1,  1,				{ROMAN_J,                   },	'J'},
        {1,  2,  1,  1,				{ROMAN_K,                   },	'K'},
        {2,  2,  1,  1,				{ROMAN_L,                   },	'L'},
        {3,  2,  1,  1,				{ROMAN_M,                   },	'M'},
        {4,  2,  1,  1,				{ROMAN_N,                   },	'N'},
        {5,  2,  1,  1,				{ROMAN_O,                   },	'O'},
        {6,  2,  1,  1,				{ROMAN_P,                   },	'P'},
        {7,  2,  1,  1,				{ROMAN_Q,                   },	'Q'},
        {8,  2,  1,  1,				{ROMAN_R,                   },	'R'},
        {9,  2,  1,  1,				{SYMBOLS_ROMAN_PERIOD,      },	VK_PERIOD},
        {10, 2,  1,  1,				{SYMBOLS_LEFT_CURLY,        },	},
        {11, 2,  1,  1,				{SYMBOLS_RIGHT_CURLY,       },	}, 
        {12, 2,  1,  1,				{SYMBOLS_LEFT_BRACKET,      },	VK_LBRACKET}, 
        {13, 2,  1,  1,				{SYMBOLS_RIGHT_BRACKET,     },	VK_RBRACKET}, 
        {14, 2,  1,  1,				{ROMAN_SOLIDUS,             },	VK_DIVIDE},
        {15, 2,  1,  1,				{ROMAN_SEVEN,               },	VK_NUMPAD7},
        {16, 2,  1,  1,				{ROMAN_EIGHT,               },	VK_NUMPAD8}, 
        {17, 2,  1,  1,				{ROMAN_NINE,                },	VK_NUMPAD9}, 
        
        {0,  3,  1,  1,				{ROMAN_S,                   },	'S'},
        {1,  3,  1,  1,				{ROMAN_T,                   },	'T'},
        {2,  3,  1,  1,				{ROMAN_U,                   },	'U'},
        {3,  3,  1,  1,				{ROMAN_V,                   },	'V'},
        {4,  3,  1,  1,				{ROMAN_W,                   },	'W'},
        {5,  3,  1,  1,				{ROMAN_X,                   },	'X'},
        {6,  3,  1,  1,				{ROMAN_Y,                   },	'Y'},
        {7,  3,  1,  1,				{ROMAN_Z,                   },	'Z'},
        {8,  3,  1,  1,             {SYMBOLS_ROMAN_COMMA,       },  VK_COMMA},
#ifdef KANJI
        {9,  3,  3,  1,             KANJI_CAPSLOCK,                 },
        {12, 3,  2,  1,             KANJI_CONFIRM,                  VK_NOCONVERT},
#else  // KANJI
        {9,  3,  5,  1,             US_CAPSLOCK,                    },
#endif
        {14, 3,  1,  1,				{ROMAN_EQUALS,              },	VK_EQUAL},
        {15, 3,  1,  1,				{ROMAN_ASTERISK,            },	}, 
        {16, 3,  1,  1,				{ROMAN_ZERO,                },	VK_NUMPAD0}, 
        {17, 3,  1,  1,             {ROMAN_TILDE,               },  },

#ifdef KANJI
        {12, 4,  2,  1,             KANJI_SYMBOLS,                  },
#endif
        {14, 4,  1,  1,				{ROMAN_COLON,               },	}, 
#ifdef KANJI
        {15, 4,  1,  1,				{SYMBOLS_YEN,               },	}, 
#else  // KANJI
        {15, 4,  1,  1,				{SYMBOLS_BACKSLASH,         },	}, 
#endif // KANJI
        {16, 4,  1,  1,				{ROMAN_DECIMAL,             },	VK_DECIMAL},
        {17, 4,  1,  1,				{ROMAN_NUMBER,              },	}, 

#ifdef KANJI
        {0,  5,  2,  1,             KANJI_DELETE,                   VK_BACK},
        {2,  5,  3,  1,             KANJI_HALF,                     },
        {5,  5,  2,  1,             KANJI_SPACE,                    VK_SPACE},
        {7,  5,  5,  1,             KANJI_CLOSE,                    VK_ESCAPE},
        {12, 5,  1,  1,				{HIRAGANA_SWITCH,               },	},
        {13, 5,  1,  1,             {KATAKANA_SWITCH,               },  },
#else
        {0,  5,  4,  1,             US_BACKSPACE,                   VK_BACK},
        {4,  5,  5,  1,             US_SPACE,                       VK_SPACE},
        {9,  5,  5,  1,             US_CLOSE,                       VK_ESCAPE},
#endif
        {14, 5,  1,  1,				{SYMBOLS_LEFT,              },	VK_LEFT}, 
        {15, 5,  1,  1,				{SYMBOLS_UP,                },	VK_UP}, 
        {16, 5,  1,  1,				{SYMBOLS_RIGHT,             },	VK_RIGHT},
        {17, 5,  1,  1,				{SYMBOLS_DOWN,              },	VK_DOWN}, 
    };

WORD g_cRomanjiKeys = sizeof(g_rgskRomanji) / sizeof(SOFTKEY); // number of keys on romanji keyboard
