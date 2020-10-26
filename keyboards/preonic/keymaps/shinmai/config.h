#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

#ifdef AUDIO_ENABLE
    #define MN(note) {(NOTE##note), 1}
    #define SHINMAI_JINLGE \
    MN(_F7), MN(_A7), MN(_C8), MN(_A7), MN(_F7), MN(_A7), MN(_C8), MN(_A7), MN(_F7), MN(_A7), MN(_C8), MN(_A7), MN(_F7), MN(_A7), MN(_C8), MN(_A7), MN(_REST), \
    MN(_C7), MN(_E7), MN(_G7), MN(_B7), MN(_G7), MN(_E7), MN(_C7), MN(_E7), MN(_G7), MN(_B7), MN(_G7), MN(_E7), MN(_REST), \
    MN(_D7), MN(_F7), MN(_A7), MN(_C8), MN(_A7), MN(_F7), MN(_D7), MN(_F7), MN(_A7), MN(_C8), MN(_A7), MN(_F7), MN(_D7), MN(_F7), MN(_A7), MN(_C8),
    #define ERROR_CLANGER \
    MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), \
    MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_REST), \
    MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), \
    MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_REST), \
    MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), \
    MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_A4), MN(_B8), MN(_REST),
    #define STARTUP_SONG SONG(SHINMAI_JINLGE)
    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), SONG(VICTORY_FANFARE_SHORT) }
    #define LEADER_CHIME SD_NOTE(_A6), S__NOTE(_REST), S__NOTE(_A7),
    #define LEADER_DONE S__NOTE(_G6), SD_NOTE(_REST), QD_NOTE(_A6),
    #define LEADER_FDUP S__NOTE(_A6), M__NOTE(_REST, 1), S__NOTE(_G6), M__NOTE(_REST, 1), S__NOTE(_F6),
#endif

#define AUTO_SHIFT_TIMEOUT 165
#define NO_AUTO_SHIFT_SPECIAL
#define TAPPING_TERM 137
#define LEADER_TIMEOUT 350
#define LEADER_PER_KEY_TIMING
#define USB_MAX_POWER_CONSUMPTION 50
#define DAC_SAMPLE_MAX 2047U
#define COMBO_COUNT 2
#define COMBO_TERM 35
#define MOUSEKEY_INTERVAL 16
#define MOUSEKEY_DELAY 0
#define MOUSEKEY_TIME_TO_MAX 180
#define MOUSEKEY_MAX_SPEED 5
#define MOUSEKEY_WHEEL_DELAY 0
#define MOUSEKEY_WHEEL_MAX_SPEED   8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40
#define ONESHOT_TAP_TOGGLE 2
#define ONESHOT_TIMEOUT 5000u
#define UNICODE_WINC_KEY KC_RCTL
//#define NUMBER_OF_ENCODERS 1
#define ENCODERS_PAD_A { B12 }
#define ENCODERS_PAD_B { B13 }
#define ENCODER_RESOLUTION 4
#endif // CONFIG_USER_H
