#include QMK_KEYBOARD_H
#include <ctype.h>
#include <string.h>

enum preonic_layers {
  _QWERTY,
  _LOWER,
  _RAISE,
  _ADJUST,
  _HYPER,
  _SUPER,
  _HACKER,
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  MUS1, SUPERT, HACKERT, HYPERT,
  ADJUST, TFLIP, UCLEAD
};

bool did_leader_succeed;
float m1[][2] = SONG(PLOVER_GOODBYE_SOUND);
float m3[][2] = SONG(COIN_SOUND);
float m4[][2] = SONG(MARIO_MUSHROOM);
float leader_startt[][2] = SONG(ONE_UP_SOUND );
LEADER_EXTERNS();

#define LSPRSE LT(_RAISE, KC_SPC)
#define RSPLWR LT(_LOWER, KC_SPC)
#define LFTSPR LT(_SUPER, KC_LEFT)
#define HYPER MO(_HYPER)

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5,
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

enum {
  LSCD = 0,
  RSCD,
  GRCL,
  BSPTD,
  DELPL,
  AUMENT,
  OUMAST,
  HPRLD,
  ZABRC,
};
int cur_dance (qk_tap_dance_state_t *state);

void ls_finished (qk_tap_dance_state_t *state, void *user_data);
void ls_reset (qk_tap_dance_state_t *state, void *user_data);
void rs_finished (qk_tap_dance_state_t *state, void *user_data);
void rs_reset (qk_tap_dance_state_t *state, void *user_data);
void bs_taphandler (qk_tap_dance_state_t *state, void *user_data);

void send_unicode_hex_string(const char* str);

/* use X(n) to call the  */
#ifdef UNICODEMAP_ENABLE
enum unicode_name {
  THINK, // thinking face 🤔
  GRIN, // grinning face 😊
  SMRK, // smirk 😏
  WEARY, // good shit 😩
  UNAMU, // unamused 😒

  SNEK, // snke 🐍
  PENGUIN, // 🐧
  DRAGON, // 🐉
  MONKEY, // 🐒
  CHICK, // 🐥
  BOAR, // 🐗

  OKOK, // 👌
  EFFU, // 🖕
  INUP, // 👆
  THUP, // 👍
  THDN, // 👎

  BBB, // dat B 🅱
  POO, // poop 💩
  HUNDR, // 100 💯
  EGGPL, // EGGPLANT 🍆
  WATER, // wet 💦
  TUMBLER, // 🥃

  LIT, // fire 🔥
  BANG, // ‽
  IRONY, // ⸮
  DEGREE // °
};


const uint32_t PROGMEM unicode_map[] = {
  [THINK]     = 0x1F914,
  [GRIN]      = 0x1F600,
  [BBB]       = 0x1F171,
  [POO]       = 0x1F4A9,
  [HUNDR]     = 0x1F4AF,
  [SMRK]      = 0x1F60F,
  [WEARY]     = 0x1F629,
  [EGGPL]     = 0x1F346,
  [WATER]     = 0x1F4A6,
  [LIT]       = 0x1F525,
  [UNAMU]     = 0x1F612,
  [SNEK]      = 0x1F40D,
  [PENGUIN]   = 0x1F427,
  [BOAR]      = 0x1F417,
  [MONKEY]    = 0x1F412,
  [CHICK]     = 0x1F425,
  [DRAGON]    = 0x1F409,
  [OKOK]      = 0x1F44C,
  [EFFU]      = 0x1F595,
  [INUP]      = 0x1F446,
  [THDN]      = 0x1F44E,
  [THUP]      = 0x1F44D,
  [TUMBLER]   = 0x1F943,
  [BANG]      = 0x0203D,
  [IRONY]     = 0x02E2E,
  [DEGREE]    = 0x000B0
 };
#endif // UNICODEMAP_ENABLE

#ifdef UCIS_ENABLE
const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
  UCIS_SYM("poop", 0x1F4A9), // 💩
  UCIS_SYM("rofl", 0x1F923), // 🤣
  UCIS_SYM("kiss", 0x1F619), // 😙
  UCIS_SYM("lit", 0x1F525),  // 🔥
  UCIS_SYM("b", 0x1F171),    // 🅱
  UCIS_SYM("peen", 0x1F346) // 🍆
);
void qk_ucis_start_user(void) {
  unicode_input_start();
  // register_hex(0x2328);
  register_hex(0x25B7);
  unicode_input_finish();
}
void qk_ucis_symbol_fallback (void) {
  // for (uint8_t i = 0; i < qk_ucis_state.count - 1; i++) {
  //   uint8_t code = qk_ucis_state.codes[i];
  //   register_code(code);
  //   unregister_code(code);
  //   wait_ms(UNICODE_TYPE_DELAY);
  // }
}
#endif
__attribute__((weak))
void send_unicode_hex_string(const char* str) {
  if (!str) { return; } // Safety net

  while (*str) {
    // Find the next code point (token) in the string
    for (; *str == ' '; str++);
    size_t n = strcspn(str, " "); // Length of the current token
    char code_point[n+1];
    strncpy(code_point, str, n);
    code_point[n] = '\0'; // Make sure it's null-terminated

    // Normalize the code point: make all hex digits lowercase
    for (char *p = code_point; *p; p++) {
      *p = tolower((unsigned char)*p);
    }

    // Send the code point as a Unicode input string
    unicode_input_start();
    send_string(code_point);
    unicode_input_finish();

    str += n; // Move to the first ' ' (or '\0') after the current token
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * |   §  | TFLIP|      |      |      |      |      |      |      |      |      | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del+ |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | '  Ö |EnterÄ|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |scadet|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  |scadet|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Hyper| Alt  | GUI  |SLower|    Space    |SRaise|LeftSu| Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_1x2uC( \
TD(GRCL),  TFLIP,   _______, _______, _______, _______, _______, _______, _______, _______, _______,    TD(BSPTD),  \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,       TD(DELPL),  \
  KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    TD(OUMAST), TD(AUMENT), \
TD(LSCD), TD(ZABRC),KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,    TD(RSCD),   \
 KC_LCTL, TD(HPRLD),KC_LALT, KC_LGUI, LSPRSE,        KC_SPC,     RSPLWR,  KC_LEFT, KC_DOWN, KC_UP,      KC_RGHT     \
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |      |      |      | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | home | pgup | pgdn | end  |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_1x2uC( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, _______, KC_ENT,  \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      KC_SPC,      _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |  å   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | ¨^~  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      | Enter|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | AltGr|      |      |             |      | home | pgup | pgdn | end  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_preonic_1x2uC( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LBRC, \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,   KC_0,     KC_RBRC, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_ENT,  \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, KC_RALT, _______, _______,      KC_SPC,      _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END   \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------.
 * | Reset|      |      |      |      |      |      |   7  |   8  |  9   |  *   |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   4  |   5  |  6   |  -   |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |   1  |   2  |  3   |  +   |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      | ADJU |      |      |   0  |   ,  |  /   |Enter |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  m1  |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_preonic_1x2uC( \
  RESET,   UC_M_WC, _______, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PAST, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, _______, \
  _______, _______, _______, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PPLS, _______, \
  _______, _______, _______, _______, ADJUST,  _______, _______, KC_P0,   KC_PDOT, KC_PSLS, KC_PENT, _______, \
  MUS1,    _______, _______, _______, _______,      KC_SPC,      _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY  \
),

/* Hyper
 * ,-----------------------------------------------------------------------------------.
 * |MEHRIO| WINC |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      | HYPA |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_HYPER] = LAYOUT_preonic_1x2uC( \
  MUS1,    UCLEAD,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, _______, _______, \
  _______, _______, _______, _______, HYPERT,  _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      KC_SPC,      _______, _______, _______, _______, _______  \
),

/* Super
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      | SUPA |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SUPER] = LAYOUT_preonic_1x2uC( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, SUPERT,  _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      KC_SPC,      _______, _______, _______, _______, _______  \
),


/* Hacker
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      | HACK |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_HACKER] = LAYOUT_preonic_1x2uC( \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______,_______,  HACKERT, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______,      KC_SPC,      _______, _______, _______, _______, _______  \
)
};

uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _HYPER, _RAISE, _SUPER);
  state = update_tri_layer_state(state, _HYPER, _LOWER, _HACKER);
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  return state;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case MUS1:
      if (record->event.pressed)
        PLAY_SONG(m4);
      return false;
      break;
    case SUPERT:
      if (record->event.pressed)
        SEND_STRING("SUPA");
      return false;
      break;
    case HACKERT:
      if (record->event.pressed)
        SEND_STRING("HACK");
      return false;
      break;
    case HYPERT:
      if (record->event.pressed)
        SEND_STRING("HYPA");
      return false;
      break;
    case ADJUST:
      if (record->event.pressed)
        SEND_STRING("ADJU");
      return false;
      break;
    case TFLIP:
      if (record->event.pressed)
        send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
      return false;
      break;
    case UCLEAD:
      if (!record->event.pressed)
        qk_ucis_start();
      return false;
      break;
  }
  return true;
};

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    did_leader_succeed = leading = false;

    SEQ_ONE_KEY(KC_E) {
      SEND_STRING("eka");
      did_leader_succeed = true;
    } else 
    SEQ_TWO_KEYS(KC_E, KC_D) {
      SEND_STRING("toka");
      did_leader_succeed = true;
    }
    leader_end();
  }
}

void leader_start(void) {
    PLAY_SONG(leader_startt);
}

void leader_end(void) {
  if (did_leader_succeed) {
    PLAY_SONG(m3);
  } else {
    PLAY_SONG(m1);
  }
}

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted) {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  else if (state->count == 2) {
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if (state->count == 3) {
    if (!state->pressed) return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8;
}

static tap tap_state = {
  .is_press_action = true,
  .state = 0
};

void ls_finished (qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  switch (tap_state.state) {
    case SINGLE_TAP: register_mods(MOD_BIT(KC_LSHIFT));register_code(KC_8); break;
    case SINGLE_HOLD: register_code(KC_LSHIFT); break;
    case DOUBLE_TAP: register_mods(MOD_BIT(KC_RALT));register_code(KC_7); break;
    case TRIPLE_TAP: register_mods(MOD_BIT(KC_RALT));register_code(KC_8); break;
    case DOUBLE_SINGLE_TAP: register_mods(MOD_BIT(KC_LSHIFT));register_code(KC_8);unregister_code(KC_8);register_code(KC_8);
  }
}

void ls_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_8);unregister_mods(MOD_BIT(KC_LSHIFT)); break;
    case SINGLE_HOLD: unregister_code(KC_LSHIFT); break;
    case DOUBLE_TAP: unregister_code(KC_7);unregister_mods(MOD_BIT(KC_RALT)); break;
    case TRIPLE_TAP: unregister_code(KC_8);unregister_mods(MOD_BIT(KC_RALT)); break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_8);unregister_mods(MOD_BIT(KC_LSHIFT));
  }
  tap_state.state = 0;
}

void rs_finished (qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  switch (tap_state.state) {
    case SINGLE_TAP: register_mods(MOD_BIT(KC_LSHIFT));register_code(KC_9); break;
    case SINGLE_HOLD: register_code(KC_LSHIFT); break;
    case DOUBLE_TAP: register_mods(MOD_BIT(KC_RALT));register_code(KC_0); break;
    case TRIPLE_TAP: register_mods(MOD_BIT(KC_RALT));register_code(KC_9); break;
    case DOUBLE_SINGLE_TAP: register_mods(MOD_BIT(KC_LSHIFT));register_code(KC_9);unregister_code(KC_9);register_code(KC_9);
  }
}

void rs_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tap_state.state) {
    case SINGLE_TAP: unregister_code(KC_9);unregister_mods(MOD_BIT(KC_LSHIFT)); break;
    case SINGLE_HOLD: unregister_code(KC_LSHIFT); break;
    case DOUBLE_TAP: unregister_code(KC_0);unregister_mods(MOD_BIT(KC_RALT)); break;
    case TRIPLE_TAP: unregister_code(KC_9);unregister_mods(MOD_BIT(KC_RALT)); break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_9);unregister_mods(MOD_BIT(KC_LSHIFT));
  }
  tap_state.state = 0;
}

void bs_taphandler (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: register_code(KC_BSPC);unregister_code(KC_BSPC); break;
    case 2: register_mods(MOD_BIT(KC_LCTL));register_code(KC_BSPC);unregister_code(KC_BSPC);unregister_mods(MOD_BIT(KC_LCTL)); break;
  }
}

void hyperlead_finished (qk_tap_dance_state_t *state, void *user_data) {
  tap_state.state = cur_dance(state);
  switch (tap_state.state) {
    case SINGLE_TAP:
      qk_leader_start();
      break;
    case SINGLE_HOLD:
      layer_on(_HYPER);
      break;
  }
}

void hyperlead_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (tap_state.state) {
    case SINGLE_HOLD:
      layer_off(_HYPER);
      break;
  }
  tap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [LSCD]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,ls_finished, ls_reset),
  [RSCD]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,rs_finished, rs_reset),
  [HPRLD]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL,hyperlead_finished, hyperlead_reset),
  [BSPTD]    = ACTION_TAP_DANCE_FN_ADVANCED_TIME(bs_taphandler, NULL, NULL, 120), 
  [GRCL]     = ACTION_TAP_DANCE_DOUBLE(KC_GRV,  KC_CALCULATOR),
  [AUMENT]   = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_ENT),
  [OUMAST]   = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_BSLS),
  [DELPL]    = ACTION_TAP_DANCE_DOUBLE(KC_DEL,  KC_MINS),
  [ZABRC]    = ACTION_TAP_DANCE_DOUBLE(KC_Z,    KC_NUBS),
};