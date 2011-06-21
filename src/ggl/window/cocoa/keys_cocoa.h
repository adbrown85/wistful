/*
 * keys_cocoa.h
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef GGL_KEYS_COCOA_H
#define GGL_KEYS_COCOA_H
#include "ggl/common.h"
#include <Cocoa/Cocoa.h>

/* TTY function keys */
#define GGL_BACKSPACE    010
#define GGL_TAB          011
#define GGL_RETURN       015
#define GGL_ESCAPE       033

/* Cursor control and motion */
#define GGL_INSERT       NSInsertFunctionKey
#define GGL_DELETE       NSDeleteFunctionKey
#define GGL_HOME         NSHomeFunctionKey
#define GGL_END          NSEndFunctionKey
#define GGL_PAGE_UP      NSPageUpFunctionKey
#define GGL_PAGE_DOWN    NSPageDownFunctionKey
#define GGL_LEFT         NSLeftArrowFunctionKey
#define GGL_RIGHT        NSRightArrowFunctionKey
#define GGL_UP           NSUpArrowFunctionKey
#define GGL_DOWN         NSDownArrowFunctionKey

/* Function keys */
#define GGL_F1           NSF1FunctionKey
#define GGL_F2           NSF2FunctionKey
#define GGL_F3           NSF3FunctionKey
#define GGL_F4           NSF4FunctionKey
#define GGL_F5           NSF5FunctionKey
#define GGL_F6           NSF6FunctionKey
#define GGL_F7           NSF7FunctionKey
#define GGL_F8           NSF8FunctionKey
#define GGL_F9           NSF9FunctionKey
#define GGL_F10          NSF10FunctionKey
#define GGL_F11          NSF11FunctionKey
#define GGL_F12          NSF12FunctionKey

/* ASCII */
#define GGL_SPACE        ' '
#define GGL_EXCLAM       '!'
#define GGL_QUOTEDBL     '"'
#define GGL_NUMBERSIGN   '#'
#define GGL_DOLLAR       '$'
#define GGL_PERCENT      '%'
#define GGL_AMPERSAND    '&'
#define GGL_APOSTROPHE   '\''
#define GGL_PARENLEFT    '('
#define GGL_PARENRIGHT   ')'
#define GGL_ASTERISK     '*'
#define GGL_PLUS         '+'
#define GGL_COMMA        ','
#define GGL_MINUS        '-'
#define GGL_PERIOD       '.'
#define GGL_SLASH        '/'
#define GGL_0            '0'
#define GGL_1            '1'
#define GGL_2            '2'
#define GGL_3            '3'
#define GGL_4            '4'
#define GGL_5            '5'
#define GGL_6            '6'
#define GGL_7            '7'
#define GGL_8            '8'
#define GGL_9            '9'
#define GGL_COLON        ':'
#define GGL_SEMICOLON    ';'
#define GGL_LESS         '<'
#define GGL_GREATER      '>'
#define GGL_QUESTION     '?'
#define GGL_AT           '@'
#define GGL_A            'A'
#define GGL_B            'B'
#define GGL_C            'C'
#define GGL_D            'D'
#define GGL_E            'E'
#define GGL_F            'F'
#define GGL_G            'G'
#define GGL_H            'H'
#define GGL_I            'I'
#define GGL_J            'J'
#define GGL_K            'K'
#define GGL_L            'L'
#define GGL_M            'M'
#define GGL_N            'N'
#define GGL_O            'O'
#define GGL_P            'P'
#define GGL_Q            'Q'
#define GGL_R            'R'
#define GGL_S            'S'
#define GGL_T            'T'
#define GGL_U            'U'
#define GGL_V            'V'
#define GGL_W            'W'
#define GGL_X            'X'
#define GGL_Y            'Y'
#define GGL_Z            'Z'
#define GGL_BRACKETLEFT  '['
#define GGL_BACKSLASH    '\\'
#define GGL_BRACKETRIGHT ']'
#define GGL_UNDERSCORE   '_'
#define GGL_GRAVE        '`'
#define GGL_a            'a'
#define GGL_b            'b'
#define GGL_c            'c'
#define GGL_d            'd'
#define GGL_e            'e'
#define GGL_f            'f'
#define GGL_g            'g'
#define GGL_h            'h'
#define GGL_i            'i'
#define GGL_j            'j'
#define GGL_k            'k'
#define GGL_l            'l'
#define GGL_m            'm'
#define GGL_n            'n'
#define GGL_o            'o'
#define GGL_p            'p'
#define GGL_q            'q'
#define GGL_r            'r'
#define GGL_s            's'
#define GGL_t            't'
#define GGL_u            'u'
#define GGL_v            'v'
#define GGL_w            'w'
#define GGL_x            'x'
#define GGL_y            'y'
#define GGL_z            'z'
#define GGL_BRACELEFT    '{'
#define GGL_BAR          '|'
#define GGL_BRACERIGHT   '}'
#define GGL_TILDE        '~'

#endif
