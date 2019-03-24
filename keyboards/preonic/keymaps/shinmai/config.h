#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "config_common.h"

#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(COLEMAK_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND) }
#endif

#define MUSIC_MASK (keycode != KC_NO)
#define AUTO_SHIFT_TIMEOUT 165
#define NO_AUTO_SHIFT_SPECIAL
#define TAPPING_TERM 136
#define LEADER_TIMEOUT 350

#endif // CONFIG_USER_H