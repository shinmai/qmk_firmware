#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

#ifdef AUDIO_ENABLE
    #define MN(note) {(NOTE##note), 1}
    #define SHINMAI_JINLGE \
    MN(_F7), MN(_A7), MN(_C8), MN(_A7), MN(_F7), MN(_A7), MN(_C8), MN(_A7), MN(_F7), MN(_A7), MN(_C8), MN(_A7), MN(_F7), MN(_A7), MN(_C8), MN(_A7), MN(_REST), \
    MN(_C7), MN(_E7), MN(_G7), MN(_B7), MN(_G7), MN(_E7), MN(_C7), MN(_E7), MN(_G7), MN(_B7), MN(_G7), MN(_E7), MN(_REST), \
    MN(_D7), MN(_F7), MN(_A7), MN(_C8), MN(_A7), MN(_F7), MN(_D7), MN(_F7), MN(_A7), MN(_C8), MN(_A7), MN(_F7), MN(_D7), MN(_F7), MN(_A7), MN(_C8),
    #define STARTUP_SONG SONG(SHINMAI_JINLGE)
    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND) }
    #define LEADER_CHIME SD_NOTE(_A6), S__NOTE(_REST), S__NOTE(_A7),
    #define LEADER_DONE S__NOTE(_G6), SD_NOTE(_REST), QD_NOTE(_A6),
    #define LEADER_FDUP S__NOTE(_A6), M__NOTE(_REST, 1), S__NOTE(_G6), M__NOTE(_REST, 1), S__NOTE(_F6), 
#endif

#define MUSIC_MASK (keycode != KC_NO)
#define AUTO_SHIFT_TIMEOUT 165
#define NO_AUTO_SHIFT_SPECIAL
#define TAPPING_TERM 136
#define LEADER_TIMEOUT 350
#define LEADER_PER_KEY_TIMING
#define USB_MAX_POWER_CONSUMPTION 50
#define DAC_SAMPLE_MAX 2047U
#endif // CONFIG_USER_H