/*
 * wistful_keys_glx.h
 *
 * Author
 *     Andrew Brown <adb1413@rit.edu>
 */
#ifndef WISTFUL_KEYS_GLX_H
#define WISTFUL_KEYS_GLX_H
#include "wistful/common.h"

/* TTY function keys */
#define WISTFUL_KEY_BACKSPACE    XK_BACKSPACE
#define WISTFUL_KEY_TAB          XK_Tab
#define WISTFUL_KEY_RETURN       XK_Return
#define WISTFUL_KEY_ESCAPE       XK_Escape

/* Cursor control and motion */
#define WISTFUL_KEY_INSERT       XK_Insert
#define WISTFUL_KEY_DELETE       XK_Delete
#define WISTFUL_KEY_HOME         XK_Home
#define WISTFUL_KEY_END          XK_End
#define WISTFUL_KEY_PAGE_UP      XK_Page_Up
#define WISTFUL_KEY_PAGE_DOWN    XK_Page_Down
#define WISTFUL_KEY_LEFT         XK_Left
#define WISTFUL_KEY_RIGHT        XK_Right
#define WISTFUL_KEY_UP           XK_Up
#define WISTFUL_KEY_DOWN         XK_Down

/* Function keys */
#define WISTFUL_KEY_F1           XK_F1
#define WISTFUL_KEY_F2           XK_F2
#define WISTFUL_KEY_F3           XK_F3
#define WISTFUL_KEY_F4           XK_F4
#define WISTFUL_KEY_F5           XK_F5
#define WISTFUL_KEY_F6           XK_F6
#define WISTFUL_KEY_F7           XK_F7
#define WISTFUL_KEY_F8           XK_F8
#define WISTFUL_KEY_F9           XK_F9
#define WISTFUL_KEY_F10          XK_F10
#define WISTFUL_KEY_F11          XK_F11
#define WISTFUL_KEY_F12          XK_F12

/* ASCII */
#define WISTFUL_KEY_SPACE        XK_space
#define WISTFUL_KEY_EXCLAM       XK_exclam
#define WISTFUL_KEY_QUOTEDBL     XK_quotedbl
#define WISTFUL_KEY_NUMBERSIGN   XK_numbersign
#define WISTFUL_KEY_DOLLAR       XK_dollar
#define WISTFUL_KEY_PERCENT      XK_percent
#define WISTFUL_KEY_AMPERSAND    XK_ampersand
#define WISTFUL_KEY_APOSTROPHE   XK_apostrophe
#define WISTFUL_KEY_PARENLEFT    XK_parenleft
#define WISTFUL_KEY_PARENRIGHT   XK_parenright
#define WISTFUL_KEY_ASTERISK     XK_asterisk
#define WISTFUL_KEY_PLUS         XK_plus
#define WISTFUL_KEY_COMMA        XK_comma
#define WISTFUL_KEY_MINUS        XK_minus
#define WISTFUL_KEY_PERIOD       XK_period
#define WISTFUL_KEY_SLASH        XK_slash
#define WISTFUL_KEY_0            XK_0
#define WISTFUL_KEY_1            XK_1
#define WISTFUL_KEY_2            XK_2
#define WISTFUL_KEY_3            XK_3
#define WISTFUL_KEY_4            XK_4
#define WISTFUL_KEY_5            XK_5
#define WISTFUL_KEY_6            XK_6
#define WISTFUL_KEY_7            XK_7
#define WISTFUL_KEY_8            XK_8
#define WISTFUL_KEY_9            XK_9
#define WISTFUL_KEY_COLON        XK_colon
#define WISTFUL_KEY_SEMICOLON    XK_semicolon
#define WISTFUL_KEY_LESS         XK_less
#define WISTFUL_KEY_GREATER      XK_greater
#define WISTFUL_KEY_QUESTION     XK_question
#define WISTFUL_KEY_AT           XK_at
#define WISTFUL_KEY_A            XK_A
#define WISTFUL_KEY_B            XK_B
#define WISTFUL_KEY_C            XK_C
#define WISTFUL_KEY_D            XK_D
#define WISTFUL_KEY_E            XK_E
#define WISTFUL_KEY_F            XK_F
#define WISTFUL_KEY_G            XK_G
#define WISTFUL_KEY_H            XK_H
#define WISTFUL_KEY_I            XK_I
#define WISTFUL_KEY_J            XK_J
#define WISTFUL_KEY_K            XK_K
#define WISTFUL_KEY_L            XK_L
#define WISTFUL_KEY_M            XK_M
#define WISTFUL_KEY_N            XK_N
#define WISTFUL_KEY_O            XK_O
#define WISTFUL_KEY_P            XK_P
#define WISTFUL_KEY_Q            XK_Q
#define WISTFUL_KEY_R            XK_R
#define WISTFUL_KEY_S            XK_S
#define WISTFUL_KEY_T            XK_T
#define WISTFUL_KEY_U            XK_U
#define WISTFUL_KEY_V            XK_V
#define WISTFUL_KEY_W            XK_W
#define WISTFUL_KEY_X            XK_X
#define WISTFUL_KEY_Y            XK_Y
#define WISTFUL_KEY_Z            XK_Z
#define WISTFUL_KEY_BRACKETLEFT  XK_bracketleft
#define WISTFUL_KEY_BACKSLASH    XK_backslash
#define WISTFUL_KEY_BRACKETRIGHT XK_bracketright
#define WISTFUL_KEY_UNDERSCORE   XK_underscore
#define WISTFUL_KEY_GRAVE        XK_grave
#define WISTFUL_KEY_a            XK_a
#define WISTFUL_KEY_b            XK_b
#define WISTFUL_KEY_c            XK_c
#define WISTFUL_KEY_d            XK_d
#define WISTFUL_KEY_e            XK_e
#define WISTFUL_KEY_f            XK_f
#define WISTFUL_KEY_g            XK_g
#define WISTFUL_KEY_h            XK_h
#define WISTFUL_KEY_i            XK_i
#define WISTFUL_KEY_j            XK_j
#define WISTFUL_KEY_k            XK_k
#define WISTFUL_KEY_l            XK_l
#define WISTFUL_KEY_m            XK_m
#define WISTFUL_KEY_n            XK_n
#define WISTFUL_KEY_o            XK_o
#define WISTFUL_KEY_p            XK_p
#define WISTFUL_KEY_q            XK_q
#define WISTFUL_KEY_r            XK_r
#define WISTFUL_KEY_s            XK_s
#define WISTFUL_KEY_t            XK_t
#define WISTFUL_KEY_u            XK_u
#define WISTFUL_KEY_v            XK_v
#define WISTFUL_KEY_w            XK_w
#define WISTFUL_KEY_x            XK_x
#define WISTFUL_KEY_y            XK_y
#define WISTFUL_KEY_z            XK_z
#define WISTFUL_KEY_BRACELEFT    XK_braceleft
#define WISTFUL_KEY_BAR          XK_bar
#define WISTFUL_KEY_BRACERIGHT   XK_braceright
#define WISTFUL_KEY_TILDE        XK_asciitilde

#endif
