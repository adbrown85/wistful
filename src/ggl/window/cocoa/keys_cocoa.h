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
#define GGL_KEY_BACKSPACE    010
#define GGL_KEY_TAB          011
#define GGL_KEY_RETURN       015
#define GGL_KEY_ESCAPE       033

/* Cursor control and motion */
#define GGL_KEY_INSERT       NSInsertFunctionKey
#define GGL_KEY_DELETE       NSDeleteFunctionKey
#define GGL_KEY_HOME         NSHomeFunctionKey
#define GGL_KEY_END          NSEndFunctionKey
#define GGL_KEY_PAGE_UP      NSPageUpFunctionKey
#define GGL_KEY_PAGE_DOWN    NSPageDownFunctionKey
#define GGL_KEY_LEFT         NSLeftArrowFunctionKey
#define GGL_KEY_RIGHT        NSRightArrowFunctionKey
#define GGL_KEY_UP           NSUpArrowFunctionKey
#define GGL_KEY_DOWN         NSDownArrowFunctionKey

/* Function keys */
#define GGL_KEY_F1           NSF1FunctionKey
#define GGL_KEY_F2           NSF2FunctionKey
#define GGL_KEY_F3           NSF3FunctionKey
#define GGL_KEY_F4           NSF4FunctionKey
#define GGL_KEY_F5           NSF5FunctionKey
#define GGL_KEY_F6           NSF6FunctionKey
#define GGL_KEY_F7           NSF7FunctionKey
#define GGL_KEY_F8           NSF8FunctionKey
#define GGL_KEY_F9           NSF9FunctionKey
#define GGL_KEY_F10          NSF10FunctionKey
#define GGL_KEY_F11          NSF11FunctionKey
#define GGL_KEY_F12          NSF12FunctionKey

/* ASCII */
#define GGL_KEY_SPACE        ' '
#define GGL_KEY_EXCLAM       '!'
#define GGL_KEY_QUOTEDBL     '"'
#define GGL_KEY_NUMBERSIGN   '#'
#define GGL_KEY_DOLLAR       '$'
#define GGL_KEY_PERCENT      '%'
#define GGL_KEY_AMPERSAND    '&'
#define GGL_KEY_APOSTROPHE   '\''
#define GGL_KEY_PARENLEFT    '('
#define GGL_KEY_PARENRIGHT   ')'
#define GGL_KEY_ASTERISK     '*'
#define GGL_KEY_PLUS         '+'
#define GGL_KEY_COMMA        ','
#define GGL_KEY_MINUS        '-'
#define GGL_KEY_PERIOD       '.'
#define GGL_KEY_SLASH        '/'
#define GGL_KEY_0            '0'
#define GGL_KEY_1            '1'
#define GGL_KEY_2            '2'
#define GGL_KEY_3            '3'
#define GGL_KEY_4            '4'
#define GGL_KEY_5            '5'
#define GGL_KEY_6            '6'
#define GGL_KEY_7            '7'
#define GGL_KEY_8            '8'
#define GGL_KEY_9            '9'
#define GGL_KEY_COLON        ':'
#define GGL_KEY_SEMICOLON    ';'
#define GGL_KEY_LESS         '<'
#define GGL_KEY_GREATER      '>'
#define GGL_KEY_QUESTION     '?'
#define GGL_KEY_AT           '@'
#define GGL_KEY_A            'A'
#define GGL_KEY_B            'B'
#define GGL_KEY_C            'C'
#define GGL_KEY_D            'D'
#define GGL_KEY_E            'E'
#define GGL_KEY_F            'F'
#define GGL_KEY_G            'G'
#define GGL_KEY_H            'H'
#define GGL_KEY_I            'I'
#define GGL_KEY_J            'J'
#define GGL_KEY_K            'K'
#define GGL_KEY_L            'L'
#define GGL_KEY_M            'M'
#define GGL_KEY_N            'N'
#define GGL_KEY_O            'O'
#define GGL_KEY_P            'P'
#define GGL_KEY_Q            'Q'
#define GGL_KEY_R            'R'
#define GGL_KEY_S            'S'
#define GGL_KEY_T            'T'
#define GGL_KEY_U            'U'
#define GGL_KEY_V            'V'
#define GGL_KEY_W            'W'
#define GGL_KEY_X            'X'
#define GGL_KEY_Y            'Y'
#define GGL_KEY_Z            'Z'
#define GGL_KEY_BRACKETLEFT  '['
#define GGL_KEY_BACKSLASH    '\\'
#define GGL_KEY_BRACKETRIGHT ']'
#define GGL_KEY_UNDERSCORE   '_'
#define GGL_KEY_GRAVE        '`'
#define GGL_KEY_a            'a'
#define GGL_KEY_b            'b'
#define GGL_KEY_c            'c'
#define GGL_KEY_d            'd'
#define GGL_KEY_e            'e'
#define GGL_KEY_f            'f'
#define GGL_KEY_g            'g'
#define GGL_KEY_h            'h'
#define GGL_KEY_i            'i'
#define GGL_KEY_j            'j'
#define GGL_KEY_k            'k'
#define GGL_KEY_l            'l'
#define GGL_KEY_m            'm'
#define GGL_KEY_n            'n'
#define GGL_KEY_o            'o'
#define GGL_KEY_p            'p'
#define GGL_KEY_q            'q'
#define GGL_KEY_r            'r'
#define GGL_KEY_s            's'
#define GGL_KEY_t            't'
#define GGL_KEY_u            'u'
#define GGL_KEY_v            'v'
#define GGL_KEY_w            'w'
#define GGL_KEY_x            'x'
#define GGL_KEY_y            'y'
#define GGL_KEY_z            'z'
#define GGL_KEY_BRACELEFT    '{'
#define GGL_KEY_BAR          '|'
#define GGL_KEY_BRACERIGHT   '}'
#define GGL_KEY_TILDE        '~'

#endif
