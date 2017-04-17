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
//   X   Y Wid Hgt  Characters on key
//  ----------------------------------------------------------------------------------
    {0,  0,  1,  1,	{ROMAN_DOLLAR_SIGN,                 },  }, 
    {1,  0,  1,  1,	{ROMAN_PERCENT,                     },  },
    {2,  0,  1,  1,	{ROMAN_CIRCUMFLEX,                  },  },
    {3,  0,  1,  1,	{ROMAN_AMPERSAND,                   },  },
    {4,  0,  1,  1,	{ROMAN_ASTERISK,                    },  }, 
    {5,  0,  1,  1,	{ROMAN_MINUS,                       },  },
    {6,  0,  1,  1,	{ROMAN_LOWLINE,                     },  },
    {7,  0,  1,  1,	{ROMAN_LEFT_PAREN,                  },  },
    {8,  0,  1,  1,	{ROMAN_RIGHT_PAREN,                 },  }, 
    {9,  0,  1,  1,	{ROMAN_SEMICOLON,                   },  VK_SEMICOLON},
    {10, 0,  1,  1,	{ROMAN_SINGLE_QUOTE,                },  }, 
    {11, 0,  1,  1,	{ROMAN_DOUBLE_QUOTE,                },  }, 
    {12, 0,  1,  1,	{ROMAN_EXCLAMATION,                 },  },
    {13, 0,  1,  1,	{ROMAN_QUESTION,                    },  }, 
    {14, 0,  1,  1,	{ROMAN_PLUS,                        },  VK_ADD},
    {15, 0,  1,  1,	{ROMAN_ONE,                         },  VK_NUMPAD1},
    {16, 0,  1,  1,	{ROMAN_TWO,                         },  VK_NUMPAD2}, 
    {17, 0,  1,  1,	{ROMAN_THREE,                       },  VK_NUMPAD3}, 
    
    {0,  1,  1,  1,	{ROMAN_A,                           },  'A'},
    {1,  1,  1,  1,	{ROMAN_B,                           },  'B'},
    {2,  1,  1,  1,	{ROMAN_C,                           },  'C'},
    {3,  1,  1,  1,	{ROMAN_D,                           },  'D'},
    {4,  1,  1,  1,	{ROMAN_E,                           },  'E'},
    {5,  1,  1,  1,	{ROMAN_F,                           },  'F'},
    {6,  1,  1,  1,	{ROMAN_G,                           },  'G'},
    {7,  1,  1,  1,	{ROMAN_H,                           },  'H'},
    {8,  1,  1,  1,	{ROMAN_I,                           },  'I'},
    {9,  1,  1,  1,	{ROMAN_GRAVE_ACCENT,                },  }, 
    {10, 1,  1,  1,	{ROMAN_LESSTHAN,                    },  },
    {11, 1,  1,  1,	{ROMAN_GREATERTHAN,                 },  },
    {12, 1,  1,  1,	{ROMAN_VERTICAL_LINE,               },  },
    {13, 1,  1,  1,	{ROMAN_AT,                          },  },  
    {14, 1,  1,  1,	{ROMAN_MINUS,                       },  VK_SUBTRACT},
    {15, 1,  1,  1,	{ROMAN_FOUR,                        },  VK_NUMPAD4},
    {16, 1,  1,  1,	{ROMAN_FIVE,                        },  VK_NUMPAD5}, 
    {17, 1,  1,  1,	{ROMAN_SIX,                         },  VK_NUMPAD6}, 
    
    {0,  2,  1,  1,	{ROMAN_J,                           },  'J'},
    {1,  2,  1,  1,	{ROMAN_K,                           },  'K'},
    {2,  2,  1,  1,	{ROMAN_L,                           },  'L'},
    {3,  2,  1,  1,	{ROMAN_M,                           },  'M'},
    {4,  2,  1,  1,	{ROMAN_N,                           },  'N'},
    {5,  2,  1,  1,	{ROMAN_O,                           },  'O'},
    {6,  2,  1,  1,	{ROMAN_P,                           },  'P'},
    {7,  2,  1,  1,	{ROMAN_Q,                           },  'Q'},
    {8,  2,  1,  1,	{ROMAN_R,                           },  'R'},
    {9,  2,  1,  1,	{ROMAN_PERIOD,                      },  VK_PERIOD},
    {10, 2,  1,  1,	{ROMAN_LEFT_CURLY,                  },  },
    {11, 2,  1,  1,	{ROMAN_RIGHT_CURLY,                 },  }, 
    {12, 2,  1,  1,	{ROMAN_LEFT_BRACKET,                },  VK_LBRACKET}, 
    {13, 2,  1,  1,	{ROMAN_RIGHT_BRACKET,               },  VK_RBRACKET}, 
    {14, 2,  1,  1,	{ROMAN_SOLIDUS,                     },  VK_DIVIDE},
    {15, 2,  1,  1,	{ROMAN_SEVEN,                       },  VK_NUMPAD7},
    {16, 2,  1,  1,	{ROMAN_EIGHT,                       },  VK_NUMPAD8}, 
    {17, 2,  1,  1,	{ROMAN_NINE,                        },  VK_NUMPAD9}, 
    
    {0,  3,  1,  1,	{ROMAN_S,                           },  'S'},
    {1,  3,  1,  1,	{ROMAN_T,                           },  'T'},
    {2,  3,  1,  1,	{ROMAN_U,                           },  'U'},
    {3,  3,  1,  1,	{ROMAN_V,                           },  'V'},
    {4,  3,  1,  1,	{ROMAN_W,                           },  'W'},
    {5,  3,  1,  1,	{ROMAN_X,                           },  'X'},
    {6,  3,  1,  1,	{ROMAN_Y,                           },  'Y'},
    {7,  3,  1,  1,	{ROMAN_Z,                           },  'Z'},
    {8,  3,  1,  1,	{ROMAN_COMMA,                       },  VK_COMMA},
    {9,  3,  3,  1,	{KANJI_CAPSLOCK_0, KANJI_CAPSLOCK_1, KANJI_CAPSLOCK_2, KANJI_CAPSLOCK_3},	},
    {12, 3,  1,  1,	{ROMAN_COLON                        },  },
    {13, 3,  1,  1,	{ROMAN_REVERSE_SOLIDUS              },  },
    {14, 3,  1,  1,	{ROMAN_EQUALS,                      },  VK_EQUAL},
    {15, 3,  1,  1,	{ROMAN_ASTERISK,                    },  }, 
    {16, 3,  1,  1,	{ROMAN_ZERO,                        },  VK_NUMPAD0}, 
    {17, 3,  1,  1,	{ROMAN_NUMBER,                      },  },

    {0,  4,  2,  1,	{KANJI_DELETE_0, KANJI_DELETE_1     },  VK_BACK},
    {2,  4,  3,  1,	{KANJI_HALF_0, KANJI_HALF_1, KANJI_HALF_2, KANJI_HALF_3,},  },
    {5,  4,  2,  1,	{KANJI_SPACE_0, KANJI_SPACE_1       },  VK_SPACE}, 
    {7,  4,  3,  1,	{KANJI_CLOSE_0, KANJI_CLOSE_1,      },  VK_ESCAPE},
    {10, 4,  2,  1,	{KANJI_PHONETIC_0, KANJI_PHONETIC_1,},  },
    {12, 4,  2,  1,	{KANJI_SYMBOLS_0, KANJI_SYMBOLS_1,  },  },
    {14, 4,  1,  1,	{SYMBOL_LEFT_ARROW,                 },  VK_LEFT},
    {15, 4,  1,  1,	{SYMBOL_UP_ARROW,                   },  VK_UP}, 
    {16, 4,  1,  1,	{SYMBOL_RIGHT_ARROW,                },  VK_RIGHT},
    {17, 4,  1,  1,	{SYMBOL_DOWN_ARROW,                 },  VK_DOWN}, 
};

WORD g_cRomanjiKeys = sizeof(g_rgskRomanji) / sizeof(SOFTKEY); // number of keys on romanji keyboard
