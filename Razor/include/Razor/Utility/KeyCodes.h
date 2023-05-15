#pragma once

/* Mire, 5/15/2023 
   GLFW KeyCode values are currently used as the KeyCodes 
   for the Razor engine. In the future, if the library which
   is used changes (for example based on the platform), these
   KeyCodes shall be updated accordingly. TODO */

/* The unknown key */
#define RZR_KEY_UNKNOWN            -1

/* Printable keys */
#define RZR_KEY_SPACE              32
#define RZR_KEY_APOSTROPHE         39  /* ' */
#define RZR_KEY_COMMA              44  /* , */
#define RZR_KEY_MINUS              45  /* - */
#define RZR_KEY_PERIOD             46  /* . */
#define RZR_KEY_SLASH              47  /* / */
#define RZR_KEY_0                  48
#define RZR_KEY_1                  49
#define RZR_KEY_2                  50
#define RZR_KEY_3                  51
#define RZR_KEY_4                  52
#define RZR_KEY_5                  53
#define RZR_KEY_6                  54
#define RZR_KEY_7                  55
#define RZR_KEY_8                  56
#define RZR_KEY_9                  57
#define RZR_KEY_SEMICOLON          59  /* ; */
#define RZR_KEY_EQUAL              61  /* = */
#define RZR_KEY_A                  65
#define RZR_KEY_B                  66
#define RZR_KEY_C                  67
#define RZR_KEY_D                  68
#define RZR_KEY_E                  69
#define RZR_KEY_F                  70
#define RZR_KEY_G                  71
#define RZR_KEY_H                  72
#define RZR_KEY_I                  73
#define RZR_KEY_J                  74
#define RZR_KEY_K                  75
#define RZR_KEY_L                  76
#define RZR_KEY_M                  77
#define RZR_KEY_N                  78
#define RZR_KEY_O                  79
#define RZR_KEY_P                  80
#define RZR_KEY_Q                  81
#define RZR_KEY_R                  82
#define RZR_KEY_S                  83
#define RZR_KEY_T                  84
#define RZR_KEY_U                  85
#define RZR_KEY_V                  86
#define RZR_KEY_W                  87
#define RZR_KEY_X                  88
#define RZR_KEY_Y                  89
#define RZR_KEY_Z                  90
#define RZR_KEY_LEFT_BRACKET       91  /* [ */
#define RZR_KEY_BACKSLASH          92  /* \ */
#define RZR_KEY_RIGHT_BRACKET      93  /* ] */
#define RZR_KEY_GRAVE_ACCENT       96  /* ` */
#define RZR_KEY_WORLD_1            161 /* non-US #1 */
#define RZR_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define RZR_KEY_ESCAPE             256
#define RZR_KEY_ENTER              257
#define RZR_KEY_TAB                258
#define RZR_KEY_BACKSPACE          259
#define RZR_KEY_INSERT             260
#define RZR_KEY_DELETE             261
#define RZR_KEY_RIGHT              262
#define RZR_KEY_LEFT               263
#define RZR_KEY_DOWN               264
#define RZR_KEY_UP                 265
#define RZR_KEY_PAGE_UP            266
#define RZR_KEY_PAGE_DOWN          267
#define RZR_KEY_HOME               268
#define RZR_KEY_END                269
#define RZR_KEY_CAPS_LOCK          280
#define RZR_KEY_SCROLL_LOCK        281
#define RZR_KEY_NUM_LOCK           282
#define RZR_KEY_PRINT_SCREEN       283
#define RZR_KEY_PAUSE              284
#define RZR_KEY_F1                 290
#define RZR_KEY_F2                 291
#define RZR_KEY_F3                 292
#define RZR_KEY_F4                 293
#define RZR_KEY_F5                 294
#define RZR_KEY_F6                 295
#define RZR_KEY_F7                 296
#define RZR_KEY_F8                 297
#define RZR_KEY_F9                 298
#define RZR_KEY_F10                299
#define RZR_KEY_F11                300
#define RZR_KEY_F12                301
#define RZR_KEY_F13                302
#define RZR_KEY_F14                303
#define RZR_KEY_F15                304
#define RZR_KEY_F16                305
#define RZR_KEY_F17                306
#define RZR_KEY_F18                307
#define RZR_KEY_F19                308
#define RZR_KEY_F20                309
#define RZR_KEY_F21                310
#define RZR_KEY_F22                311
#define RZR_KEY_F23                312
#define RZR_KEY_F24                313
#define RZR_KEY_F25                314
#define RZR_KEY_KP_0               320
#define RZR_KEY_KP_1               321
#define RZR_KEY_KP_2               322
#define RZR_KEY_KP_3               323
#define RZR_KEY_KP_4               324
#define RZR_KEY_KP_5               325
#define RZR_KEY_KP_6               326
#define RZR_KEY_KP_7               327
#define RZR_KEY_KP_8               328
#define RZR_KEY_KP_9               329
#define RZR_KEY_KP_DECIMAL         330
#define RZR_KEY_KP_DIVIDE          331
#define RZR_KEY_KP_MULTIPLY        332
#define RZR_KEY_KP_SUBTRACT        333
#define RZR_KEY_KP_ADD             334
#define RZR_KEY_KP_ENTER           335
#define RZR_KEY_KP_EQUAL           336
#define RZR_KEY_LEFT_SHIFT         340
#define RZR_KEY_LEFT_CONTROL       341
#define RZR_KEY_LEFT_ALT           342
#define RZR_KEY_LEFT_SUPER         343
#define RZR_KEY_RIGHT_SHIFT        344
#define RZR_KEY_RIGHT_CONTROL      345
#define RZR_KEY_RIGHT_ALT          346
#define RZR_KEY_RIGHT_SUPER        347
#define RZR_KEY_MENU               348

#define RZR_KEY_LAST               RZR_KEY_MENU

/* Mouse KeyCodes */
#define RZR_MOUSE_BUTTON_1         0
#define RZR_MOUSE_BUTTON_2         1
#define RZR_MOUSE_BUTTON_3         2
#define RZR_MOUSE_BUTTON_4         3
#define RZR_MOUSE_BUTTON_5         4
#define RZR_MOUSE_BUTTON_6         5
#define RZR_MOUSE_BUTTON_7         6
#define RZR_MOUSE_BUTTON_8         7
#define RZR_MOUSE_BUTTON_LAST      RZR_MOUSE_BUTTON_8
#define RZR_MOUSE_BUTTON_LEFT      RZR_MOUSE_BUTTON_1
#define RZR_MOUSE_BUTTON_RIGHT     RZR_MOUSE_BUTTON_2
#define RZR_MOUSE_BUTTON_MIDDLE    RZR_MOUSE_BUTTON_3

/******************** KeyCodes STOP ***********************/