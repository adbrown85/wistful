/*
 * keys_cocoa.h
 * 
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WISTFUL_KEYS_COCOA_H
#define WISTFUL_KEYS_COCOA_H
#include "wistful/common.h"
#include <Cocoa/Cocoa.h>

/* TTY function keys */
#define WISTFUL_KEY_BACKSPACE    010
#define WISTFUL_KEY_TAB          011
#define WISTFUL_KEY_RETURN       015
#define WISTFUL_KEY_ESCAPE       033

/* Cursor control and motion */
#define WISTFUL_KEY_INSERT       NSInsertFunctionKey
#define WISTFUL_KEY_DELETE       NSDeleteFunctionKey
#define WISTFUL_KEY_HOME         NSHomeFunctionKey
#define WISTFUL_KEY_END          NSEndFunctionKey
#define WISTFUL_KEY_PAGE_UP      NSPageUpFunctionKey
#define WISTFUL_KEY_PAGE_DOWN    NSPageDownFunctionKey
#define WISTFUL_KEY_LEFT         NSLeftArrowFunctionKey
#define WISTFUL_KEY_RIGHT        NSRightArrowFunctionKey
#define WISTFUL_KEY_UP           NSUpArrowFunctionKey
#define WISTFUL_KEY_DOWN         NSDownArrowFunctionKey

/* Function keys */
#define WISTFUL_KEY_F1           NSF1FunctionKey
#define WISTFUL_KEY_F2           NSF2FunctionKey
#define WISTFUL_KEY_F3           NSF3FunctionKey
#define WISTFUL_KEY_F4           NSF4FunctionKey
#define WISTFUL_KEY_F5           NSF5FunctionKey
#define WISTFUL_KEY_F6           NSF6FunctionKey
#define WISTFUL_KEY_F7           NSF7FunctionKey
#define WISTFUL_KEY_F8           NSF8FunctionKey
#define WISTFUL_KEY_F9           NSF9FunctionKey
#define WISTFUL_KEY_F10          NSF10FunctionKey
#define WISTFUL_KEY_F11          NSF11FunctionKey
#define WISTFUL_KEY_F12          NSF12FunctionKey

/* ASCII */
#define WISTFUL_KEY_SPACE        ' '
#define WISTFUL_KEY_EXCLAM       '!'
#define WISTFUL_KEY_QUOTEDBL     '"'
#define WISTFUL_KEY_NUMBERSIGN   '#'
#define WISTFUL_KEY_DOLLAR       '$'
#define WISTFUL_KEY_PERCENT      '%'
#define WISTFUL_KEY_AMPERSAND    '&'
#define WISTFUL_KEY_APOSTROPHE   '\''
#define WISTFUL_KEY_PARENLEFT    '('
#define WISTFUL_KEY_PARENRIGHT   ')'
#define WISTFUL_KEY_ASTERISK     '*'
#define WISTFUL_KEY_PLUS         '+'
#define WISTFUL_KEY_COMMA        ','
#define WISTFUL_KEY_MINUS        '-'
#define WISTFUL_KEY_PERIOD       '.'
#define WISTFUL_KEY_SLASH        '/'
#define WISTFUL_KEY_0            '0'
#define WISTFUL_KEY_1            '1'
#define WISTFUL_KEY_2            '2'
#define WISTFUL_KEY_3            '3'
#define WISTFUL_KEY_4            '4'
#define WISTFUL_KEY_5            '5'
#define WISTFUL_KEY_6            '6'
#define WISTFUL_KEY_7            '7'
#define WISTFUL_KEY_8            '8'
#define WISTFUL_KEY_9            '9'
#define WISTFUL_KEY_COLON        ':'
#define WISTFUL_KEY_SEMICOLON    ';'
#define WISTFUL_KEY_LESS         '<'
#define WISTFUL_KEY_GREATER      '>'
#define WISTFUL_KEY_QUESTION     '?'
#define WISTFUL_KEY_AT           '@'
#define WISTFUL_KEY_A            'A'
#define WISTFUL_KEY_B            'B'
#define WISTFUL_KEY_C            'C'
#define WISTFUL_KEY_D            'D'
#define WISTFUL_KEY_E            'E'
#define WISTFUL_KEY_F            'F'
#define WISTFUL_KEY_G            'G'
#define WISTFUL_KEY_H            'H'
#define WISTFUL_KEY_I            'I'
#define WISTFUL_KEY_J            'J'
#define WISTFUL_KEY_K            'K'
#define WISTFUL_KEY_L            'L'
#define WISTFUL_KEY_M            'M'
#define WISTFUL_KEY_N            'N'
#define WISTFUL_KEY_O            'O'
#define WISTFUL_KEY_P            'P'
#define WISTFUL_KEY_Q            'Q'
#define WISTFUL_KEY_R            'R'
#define WISTFUL_KEY_S            'S'
#define WISTFUL_KEY_T            'T'
#define WISTFUL_KEY_U            'U'
#define WISTFUL_KEY_V            'V'
#define WISTFUL_KEY_W            'W'
#define WISTFUL_KEY_X            'X'
#define WISTFUL_KEY_Y            'Y'
#define WISTFUL_KEY_Z            'Z'
#define WISTFUL_KEY_BRACKETLEFT  '['
#define WISTFUL_KEY_BACKSLASH    '\\'
#define WISTFUL_KEY_BRACKETRIGHT ']'
#define WISTFUL_KEY_UNDERSCORE   '_'
#define WISTFUL_KEY_GRAVE        '`'
#define WISTFUL_KEY_a            'a'
#define WISTFUL_KEY_b            'b'
#define WISTFUL_KEY_c            'c'
#define WISTFUL_KEY_d            'd'
#define WISTFUL_KEY_e            'e'
#define WISTFUL_KEY_f            'f'
#define WISTFUL_KEY_g            'g'
#define WISTFUL_KEY_h            'h'
#define WISTFUL_KEY_i            'i'
#define WISTFUL_KEY_j            'j'
#define WISTFUL_KEY_k            'k'
#define WISTFUL_KEY_l            'l'
#define WISTFUL_KEY_m            'm'
#define WISTFUL_KEY_n            'n'
#define WISTFUL_KEY_o            'o'
#define WISTFUL_KEY_p            'p'
#define WISTFUL_KEY_q            'q'
#define WISTFUL_KEY_r            'r'
#define WISTFUL_KEY_s            's'
#define WISTFUL_KEY_t            't'
#define WISTFUL_KEY_u            'u'
#define WISTFUL_KEY_v            'v'
#define WISTFUL_KEY_w            'w'
#define WISTFUL_KEY_x            'x'
#define WISTFUL_KEY_y            'y'
#define WISTFUL_KEY_z            'z'
#define WISTFUL_KEY_BRACELEFT    '{'
#define WISTFUL_KEY_BAR          '|'
#define WISTFUL_KEY_BRACERIGHT   '}'
#define WISTFUL_KEY_TILDE        '~'

#endif
