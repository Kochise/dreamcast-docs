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

SOFTKEY g_rgskPhonetic[] = 
{
//   X   Y Wid Hgt  Characters on Key
//  ------------------------------------------------------------------------------------
    {0,  0,  1,  1, {PHON_B,                            },  },
    {1,  0,  1,  1, {PHON_D,                            },  },
    {2,  0,  1,  1, {PHON_TONE3,                        },  },
    {3,  0,  1,  1, {PHON_TONE4,                        },  },
    {4,  0,  1,  1, {PHON_ZHI,                          },  },
    {5,  0,  1,  1, {PHON_TONE2,                        },  },
    {6,  0,  1,  1, {PHON_TONE0,                        },  },
    {7,  0,  1,  1, {PHON_A,                            },  },
    {8,  0,  1,  1, {PHON_AI,                           },  },
    {9,  0,  1,  1, {PHON_AN,                           },  },
    {10, 0,  1,  1, {PHON_ER,                           },  }, 
    {11, 0,  1,  1, {ROMAN_PLUS,                        },  },
    {12, 0,  1,  1, {ROMAN_ONE,                         },  },
    {13, 0,  1,  1, {ROMAN_TWO,                         },  }, 
    {14, 0,  1,  1, {ROMAN_THREE,                       },  },

    {0,  1,  1,  1, {PHON_P,                            },  },
    {1,  1,  1,  1, {PHON_T,                            },  },
    {2,  1,  1,  1, {PHON_G,                            },  },
    {3,  1,  1,  1, {PHON_J,                            },  },
    {4,  1,  1,  1, {PHON_CHI,                          },  },
    {5,  1,  1,  1, {PHON_ZI,                           },  },
    {6,  1,  1,  1, {PHON_YI,                           },  },
    {7,  1,  1,  1, {PHON_O,                            },  },
    {8,  1,  1,  1, {PHON_EI,                           },  },
    {9, 1,  1,  1, {PHON_EN,                           },  },
    {10, 1,  1,  1, {SYMBOL_IDEO_COMMA,                 },  },
    {11, 1,  1,  1, {ROMAN_MINUS,                       },  },
    {12, 1,  1,  1, {ROMAN_FOUR,                        },  },
    {13, 1,  1,  1, {ROMAN_FIVE,                        },  }, 
    {14, 1,  1,  1, {ROMAN_SIX,                         },  },

    {0,  2,  1,  1, {PHON_M,                            },  },
    {1,  2,  1,  1, {PHON_N,                            },  },
    {2,  2,  1,  1, {PHON_K,                            },  },
    {3,  2,  1,  1, {PHON_Q,                            },  },
    {4,  2,  1,  1, {PHON_SHI,                          },  },
    {5,  2,  1,  1, {PHON_CI,                           },  },
    {6,  2,  1,  1, {PHON_WU,                           },  },
    {7,  2,  1,  1, {PHON_E,                            },  },
    {8,  2,  1,  1, {PHON_AO,                           },  },
    {9,  2,  1,  1, {PHON_ANG,                          },  },
    {10, 2,  1,  1, {SYMBOL_FW_COMMA,                   },  },
    {11, 2,  1,  1, {ROMAN_SOLIDUS,                     },  },
    {12, 2,  1,  1, {ROMAN_SEVEN,                       },  },
    {13, 2,  1,  1, {ROMAN_EIGHT,                       },  }, 
    {14, 2,  1,  1, {ROMAN_NINE,                        },  },

    {0,  3,  1,  1, {PHON_F,                            },  },
    {1,  3,  1,  1, {PHON_L,                            },  },
    {2,  3,  1,  1, {PHON_H,                            },  },
    {3,  3,  1,  1, {PHON_X,                            },  },
    {4,  3,  1,  1, {PHON_RI,                           },  },
    {5,  3,  1,  1, {PHON_SI,                   	    },  },
    {6,  3,  1,  1, {PHON_YU,                   	    },  },
    {7,  3,  1,  1, {PHON_IE,                           },  },
    {8,  3,  1,  1, {PHON_OU,                           },  },
    {9,  3,  1,  1, {PHON_ENG,                          },  },
    {10, 3,  1,  1, {SYMBOL_IDEO_FULLSTOP,              },  },
    {11, 3,  1,  1, {ROMAN_EQUALS,                      },  },
    {12, 3,  1,  1, {ROMAN_ASTERISK,                    },  },
    {13, 3,  1,  1, {ROMAN_ZERO,                        },  }, 
    {14, 3,  1,  1, {ROMAN_NUMBER,                      },  },

    {0,  4,  2,  1,	{KANJI_DELETE_0, KANJI_DELETE_1     },  VK_BACK},
    {2,  4,  3,  1, {KANJI_SPACE_0, KANJI_SPACE_1,      },  VK_SPACE},
    {5,  4,  2,  1, {KANJI_CLOSE_0,	KANJI_CLOSE_1,      },  VK_ESCAPE},
    {7,  4,  2,  1, {KANJI_ENGLISH_0, KANJI_ENGLISH_1,  },  },
    {9,  4,  2,  1, {KANJI_SYMBOLS_0, KANJI_SYMBOLS_1,  },  },
    {11, 4,  1,  1, {SYMBOL_LEFT_ARROW,                 },  VK_LEFT}, 
    {12, 4,  1,  1, {SYMBOL_UP_ARROW,                   },  VK_UP}, 
    {13, 4,  1,  1, {SYMBOL_RIGHT_ARROW,                },  VK_RIGHT}, 
    {14, 4,  1,  1, {SYMBOL_DOWN_ARROW,                 },  VK_DOWN}, 
};

WORD g_cPhoneticKeys = sizeof(g_rgskPhonetic) / sizeof(SOFTKEY);  // number of keys on PHonetic keyboard

// phonetic.cxx
