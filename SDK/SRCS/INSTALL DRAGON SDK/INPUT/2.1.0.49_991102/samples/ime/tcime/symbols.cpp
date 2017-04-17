/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1998 Microsoft Corporation

Module Name:

    Phonetic.cxx

Abstract:

    This file initializes an array of keys in the phonetic layout.

Environment:

    Runs on Dreamcast under Windows CE.

-------------------------------------------------------------------*/


#include "precomp.hxx"

				
// This array defines the layout for the Phonetic software keyboard.
// Keys must be listed in sorted order by location on keyboard, 
// left to right, and then top to bottom.  The binary search 
// is dependent on this sort order.

// Virtual Key codes are filled in, but many are not used; instead, we just send
// the unicode for the character in a WM_CHAR message.

SOFTKEY g_rgskSymbol[] = 
{
//   X   Y Wid Hgt  Characters on Key
//  ------------------------------------------------------------------------------------
    {0,  0,  1,  1, {SYMBOL_BD_DOWN_RIGHT,              },  },
    {1,  0,  1,  1, {SYMBOL_BD_DOWN_HORZ,               },  },
    {2,  0,  1,  1, {SYMBOL_BD_DOWN_LEFT,               },  },
    {3,  0,  1,  1, {SYMBOL_LEFT_DB_PRIME_QUOT,         },  },
    {4,  0,  1,  1, {SYMBOL_RIGHT_DB_PRIME_QUOT,        },  },
    {5,  0,  1,  1, {SYMBOL_LEFT_SINGLE_QUOT,           },  },
    {6,  0,  1,  1, {SYMBOL_RIGHT_SINGLE_QUOT,          },  },
    {7,  0,  1,  1, {SYMBOL_LEFT_DOUBLE_QUOT,           },  },
    {8,  0,  1,  1, {SYMBOL_RIGHT_DOUBLE_QUOT,          },  },
    {9,  0,  1,  1, {SYMBOL_LEFT_WT_CORNER_BRACKET,     },  },
    {10, 0,  1,  1, {SYMBOL_RIGHT_WT_CORNER_BRACKET,    },  }, 
    {11, 0,  1,  1, {SYMBOL_LEFT_CORNER_BRACKET,        },  }, 
    {12, 0,  1,  1, {SYMBOL_RIGHT_CORNER_BRACKET,       },  }, 
    {13, 0,  1,  1, {ROMAN_PLUS,                        },  },
    {14, 0,  1,  1, {ROMAN_ONE,                         },  },
    {15, 0,  1,  1, {ROMAN_TWO,                         },  }, 
    {16, 0,  1,  1, {ROMAN_THREE,                       },  },

    {0,  1,  1,  1, {SYMBOL_BD_VERT_RIGHT,              },  },
    {1,  1,  1,  1, {SYMBOL_BD_VERT_HORZ,               },  },
    {2,  1,  1,  1, {SYMBOL_BD_VERT_LEFT,               },  },
    {3,  1,  1,  1, {SYMBOL_REFERENCE,                  },  },
    {4,  1,  1,  1, {SYMBOL_LEFT_ANGLE_BRACKET,         },  },
    {5,  1,  1,  1, {SYMBOL_RIGHT_ANGLE_BRACKET,        },  },
    {6,  1,  1,  1, {SYMBOL_LEFT_DB_ANGLE_BRACKET,      },  },
    {7,  1,  1,  1, {SYMBOL_RIGHT_DB_ANGLE_BRACKET,     },  },
    {8,  1,  1,  1, {SYMBOL_LEFT_BK_LENTIC_BRACKET,     },  },
    {9,  1,  1,  1, {SYMBOL_RIGHT_BK_LENTIC_BRACKET,    },  },
    {10, 1,  1,  1, {SYMBOL_LEFT_TORT_SHELL_BRACKET,    },  },
    {11, 1,  1,  1, {SYMBOL_RIGHT_TORT_SHELL_BRACKET,   },  },
    {12, 1,  1,  1, {SYMBOL_FW_REVERSE_SOLIDUS,         },  },
    {13, 1,  1,  1, {ROMAN_MINUS,                       },  },
    {14, 1,  1,  1, {ROMAN_FOUR,                        },  },
    {15, 1,  1,  1, {ROMAN_FIVE,                        },  }, 
    {16, 1,  1,  1, {ROMAN_SIX,                         },  },

    {0,  2,  1,  1, {SYMBOL_BD_UP_RIGHT,                },  },
    {1,  2,  1,  1, {SYMBOL_BD_UP_HORZ,                 },  },
    {2,  2,  1,  1, {SYMBOL_BD_UP_LEFT,                 },  },
    {3,  2,  1,  1, {SYMBOL_WHITE_CIRCLE,               },  },
    {4,  2,  1,  1, {SYMBOL_BLACK_CIRCLE,               },  },
    {5,  2,  1,  1, {SYMBOL_UP_ARROW,                   },  },
    {6,  2,  1,  1, {SYMBOL_DOWN_ARROW,                 },  },
    {7,  2,  1,  1, {SYMBOL_FW_EXCLAMATION,             },  },
    {8,  2,  1,  1, {SYMBOL_FW_COLON,                   },  },
    {9,  2,  1,  1, {SYMBOL_FW_SEMICOLON,               },  },
    {10, 2,  1,  1, {SYMBOL_IDEO_COMMA,                 },  },
    {11, 2,  1,  1, {SYMBOL_WHITE_STAR,                 },  },
    {12, 2,  1,  1, {SYMBOL_BLACK_STAR,                 },  },
    {13, 2,  1,  1, {ROMAN_SOLIDUS,                     },  },
    {14, 2,  1,  1, {ROMAN_SEVEN,                       },  },
    {15, 2,  1,  1, {ROMAN_EIGHT,                       },  }, 
    {16, 2,  1,  1, {ROMAN_NINE,                        },  },

    {0,  3,  1,  1, {SYMBOL_BD_HORZONTAL,               },  },
    {1,  3,  1,  1, {SYMBOL_BD_VERTICAL,                },  },
    {2,  3,  1,  1, {SYMBOL_BULLSEYE,                   },  },
    {3,  3,  1,  1, {SYMBOL_SECTION,                    },  },
    {4,  3,  1,  1, {SYMBOL_LEFT_ARROW,                 },  },
    {5,  3,  1,  1, {SYMBOL_RIGHT_ARROW,                },  },
    {6,  3,  1,  1, {SYMBOL_IDEO_FULLSTOP,              },  },
    {7,  3,  1,  1, {SYMBOL_FW_COMMA,                   },  },
    {8,  3,  1,  1, {SYMBOL_FW_FULLSTOP,                },  },
    {9,  3,  1,  1, {SYMBOL_FW_QUESTION,                },  },
    {10, 3,  1,  1, {SYMBOL_LESS_OVER_EQUAL,            },  },
    {11, 3,  1,  1, {SYMBOL_GREATER_OVER_EQUAL,         },  },
    {12, 3,  1,  1, {SYMBOL_NOT_EQUAL,                  },  },
    {13, 3,  1,  1, {ROMAN_EQUALS,                      },  },
    {14, 3,  1,  1, {ROMAN_ASTERISK,                    },  },
    {15, 3,  1,  1, {ROMAN_ZERO,                        },  }, 
    {16, 3,  1,  1, {ROMAN_NUMBER,                      },  },

    {0,  4,  2,  1,	{KANJI_DELETE_0, KANJI_DELETE_1     },  VK_BACK},
    {2,  4,  4,  1, {KANJI_SPACE_0, KANJI_SPACE_1,      },  VK_SPACE},
    {6,  4,  3,  1, {KANJI_CLOSE_0,	KANJI_CLOSE_1,      },  VK_ESCAPE},
    {9,  4,  2,  1, {KANJI_PHONETIC_0, KANJI_PHONETIC_1,},  },
    {11, 4,  2,  1, {KANJI_ENGLISH_0, KANJI_ENGLISH_1,  },  },
    {13, 4,  1,  1, {SYMBOL_LEFT_ARROW,                 },  VK_LEFT}, 
    {14, 4,  1,  1, {SYMBOL_UP_ARROW,                   },  VK_UP}, 
    {15, 4,  1,  1, {SYMBOL_RIGHT_ARROW,                },  VK_RIGHT}, 
    {16, 4,  1,  1, {SYMBOL_DOWN_ARROW,                 },  VK_DOWN}, 
};

WORD g_cSymbolKeys = sizeof(g_rgskSymbol) / sizeof(SOFTKEY);  // number of keys on PHonetic keyboard

// phonetic.cxx
