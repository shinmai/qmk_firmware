#include QMK_KEYBOARD_H
#include <ctype.h>
#include <string.h>

extern keymap_config_t keymap_config;

enum planck_layers {
  _QWERTY = 0,
  _UCISB,
  _LOWER,
  _RAISE,
  _ADJUST,
  _HYPER,
  _SUPER,
  _HACKER,
  _OMEGA,
  _GREEK,
  _THETA,
  _DELTA,
  _GAMMA,
  _ALPHA,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE, 
  MUS1,
  TFLIP,
  UCLEAD,
  SHRUG,
  DSPRV,
  KAOMOJI_FACE,
  KAOMOJI_ACTION,
  KAOMOJI_ITEM,
  NOPEBAD,
  TABFW, TABBK,
};

bool did_leader_succeed;
float mushroom_sfx[][2] = SONG(MARIO_MUSHROOM);
float error_clanger[][2] = SONG(ERROR_CLANGER);
float leader_chime[][2] = SONG(LEADER_CHIME);
float leader_done[][2] = SONG(LEADER_DONE);
float leader_fdup[][2] = SONG(LEADER_FDUP);
LEADER_EXTERNS();

enum tapstates {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5,
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

enum tapkeys {
  LSCD = 0,
  RSCD,
  GRCL,
  BSPTD,
  DELPL,
  AUMENT,
  OUMAST,
  HPRLD,
  ZABRC,
  GUIMN,
  GRKTD,
  M1TD,
  M2TD,
};
int cur_dance (qk_tap_dance_state_t *state);

void ls_finished (qk_tap_dance_state_t *state, void *user_data);
void ls_reset (qk_tap_dance_state_t *state, void *user_data);
void rs_finished (qk_tap_dance_state_t *state, void *user_data);
void rs_reset (qk_tap_dance_state_t *state, void *user_data);
void bs_taphandler (qk_tap_dance_state_t *state, void *user_data);

#define M1 TD(M1TD)
#define M2 TD(M2TD)

enum combo_events {
  JK_ENTER,
  MM_F23
};

const uint16_t PROGMEM jkent_combo[] = {KC_J, KC_K, COMBO_END};
const uint16_t PROGMEM m1m2_combo[] = {M1, M2, COMBO_END};
combo_t key_combos[COMBO_COUNT] = {\
  [JK_ENTER] = COMBO(jkent_combo, KC_ENT),\
  [MM_F23] = COMBO_ACTION(m1m2_combo),\
};

bool cancel_next_macro_td;

void process_combo_event(uint8_t combo_index, bool pressed) {
  if(combo_index == MM_F23) {
    tap_code(KC_F23);
    cancel_next_macro_td = true;
  }
}

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
  [DEGREE]    = 0x000B0,
 };
#endif // UNICODEMAP_ENABLE

#ifdef UCIS_ENABLE
const qk_ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
   UCIS_SYM("poop", 0x1F4A9) // 💩
  ,UCIS_SYM("rofl", 0x1F923) // 🤣
  ,UCIS_SYM("kiss", 0x1F619) // 😙
  ,UCIS_SYM("lit",  0x1F525) // 🔥
  ,UCIS_SYM("b",    0x1F171) // 🅱
  ,UCIS_SYM("peen", 0x1F346) // 🍆
  ,UCIS_SYM("hund", 0x1F4AF) // 💯
  ,UCIS_SYM("snek", 0x1F40D) // 🐉
  ,UCIS_SYM("ok",   0x1F44C) // 👌
  ,UCIS_SYM("fu",   0x1F595) // 🖕
  ,UCIS_SYM("joy",  0x1F602) // 😂
  ,UCIS_SYM("cry",  0x1F62D) // 😭
  ,UCIS_SYM("bang", 0x0203D) //  ‽
  ,UCIS_SYM("irony",0x02E2E) //  ⸮
  ,UCIS_SYM("check",0x02714) // ✔️
);
void qk_ucis_start_user(void) {
  unicode_input_start();
  register_hex(0x25B7);
  unicode_input_finish();
  layer_on(_UCISB);
}
void qk_ucis_success(uint8_t symbol_index) {
  layer_off(_UCISB);
}
void qk_ucis_symbol_fallback (void) {
  layer_off(_UCISB); 
}
void qk_ucis_cancel (void) {
  layer_off(_UCISB);
}
#endif

/*
 * By drasha, kdb424 & Konstantin: https://github.com/qmk/qmk_firmware/pull/3828
 * Good STR->HEX converter courtesy of bocaj: https://r12a.github.io/app-conversion/
 * Modified by shinmai to return number of glyphs printed
 */
__attribute__((weak))
int send_unicode_hex_string_mod(const char* str) {
  if (!str) { return -1; } // Safety net
  int num = 0;
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

    num += 1;
    str += n; // Move to the first ' ' (or '\0') after the current token
  }
  return num;
}

int kaomoji_list_position = 0;
int last_printed_kaomoji_len = 0;
int in_kaomoji_mode = 0;

const char *PROGMEM kaomoji_faces[] = {
  "0028 002A 0020 005E 0020 03C9 0020 005E 0029",
  "0028 256F 2727 25BD 2727 0029 256F",
  "0028 FF89 00B4 30EE 0060 0029 FF89",
  NULL,
};
const char *PROGMEM kaomoji_actions[] = {
  "2283 2501 708E 708E 708E 708E 708E",
  "002F 007E 007E 2606 2019 002E FF65 002E FF65 003A 2605 2019 002E FF65 002E FF65 003A 2606",
  "FF89 0020 2025 2026 2501 2501 2501 2605",
  NULL,
};
const char *PROGMEM kaomoji_items[] = {
  "256F 5F61 253B 2501 253B",
  "30CE 0020 FF40 3001 30FD FF40 2602 30FD FF40 3001 30FD",
  "00A4 003D 005B 005D 003A 003A 003A 003A 003A 003E",
  NULL,
};

const char* get_kaomoji(int index) {
  switch(in_kaomoji_mode) {
    case 1:
      return kaomoji_faces[index];
      break;
    case 2:
      return kaomoji_actions[index];
      break;
    case 3:
      return kaomoji_items[index];
      break;
    default:
      return NULL;
  }
}

void enter_kaomoji_mode(int mode) {
  in_kaomoji_mode = mode;
  kaomoji_list_position = 0;
  last_printed_kaomoji_len = send_unicode_hex_string_mod(get_kaomoji(kaomoji_list_position));  
}

#define LSPRSE LT(_RAISE, KC_SPC)
#define GRSE LT(_GRAISE, KC_RBRC)
#define RSPLWR LT(_LOWER, KC_BSPC) //KC_SPC)
#define LFTSPR LT(_SUPER, KC_LEFT)
#define HYPER TD(HPRLD)
#define LSHFT TD(LSCD)
#define RSHFT TD(RSCD)
#define ZANGB TD(ZABRC)
#define SUPER TD(GUIMN)
#define OEAST TD(OUMAST)
#define AE KC_QUOT
#define OSMAGR OSM(MOD_RALT)
#define KM_F KAOMOJI_FACE
#define KM_A KAOMOJI_ACTION
#define KM_I KAOMOJI_ITEM
#define GREEK TD(GRKTD)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  | '  Ö |   Ä  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |scadet|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   -  |scadet|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Hyper| Alt  | GUI  |    SLower   |    SRaise   |Greek |  M1  |  M2  |AltGr |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_2x2u(
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    NOPEBAD,//KC_DEL,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    OEAST,   AE,
    LSHFT,   ZANGB,   KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, RSHFT,
    KC_LCTL, HYPER,   KC_LALT, SUPER,       LSPRSE,           RSPLWR,       GREEK,   M1,      M2,      OSMAGR
),

/* UCIS BASE
 * ,-----------------------------------------------------------------------------------.
 * |      |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |      |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |    Space    |    Space    |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_UCISB] = LAYOUT_planck_2x2u(
    XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_ESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    XXXXXXX, KC_ENT,
    XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      KC_SPC,          KC_SPC,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |      |      |      |      |Enter |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |      |      |AltGr |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_2x2u(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, _______, KC_LBRC, KC_ENT,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______,         _______,      _______, _______, _______, _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |§/Calc|   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |  +   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      | Home | PgUp |PgDwn | End  |      | Left | Down |  Up  |Right |      | ¨^~  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      | AltGr|      |             |             | Home | PgUp | PgDwn| End  |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_planck_2x2u(
   TD(GRCL), KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,   KC_0,     KC_MINS,
    _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  _______, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_EQL,  KC_RBRC,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______,         _______,      _______, _______, _______, _______
),

/* Adjust
 * ,-----------------------------------------------------------------------------------.
 * | Reset|Mouse1|MouseU|Mouse2|      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |MouseL|MouseD|MouseR|      |      |      |      |      |      |      |   å  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_2x2u(
    RESET,   KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_U, _______, _______, _______, _______, _______, _______, _______,
    _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, _______, KC_MPLY, KC_VOLD, KC_VOLU, KC_MNXT, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______,         _______,      _______, _______, _______, _______
),

/* Hyper
 * ,-----------------------------------------------------------------------------------.
 * |MEHRIO| WINC |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      | Left | Down |  Up  |Right |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |´´´
 * `-----------------------------------------------------------------------------------'
 */
[_HYPER] = LAYOUT_planck_2x2u(                            
    MUS1,    UCLEAD,  _______, _______, _______, _______, _______, _______, _______, _______, TABBK,  TABFW,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______,         _______,      _______, _______, _______, _______
),

/* Super
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_SUPER] = LAYOUT_planck_2x2u(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______,         _______,      _______, _______, _______, _______
),

/* Hacker
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_HACKER] = LAYOUT_planck_2x2u(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______,         _______,      _______, _______, _______, _______
),

/* Omega
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |KmojiF|KmojiA|KmojiI|      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_OMEGA] = LAYOUT_planck_2x2u(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, KM_F,    KM_A,    KM_I,    _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______,         _______,      _______, _______, _______, _______
),

/* Greek
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GREEK] = LAYOUT_planck_2x2u(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______,         _______,      _______, _______, _______, _______
),

/* Theta
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_THETA] = LAYOUT_planck_2x2u(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______,         _______,      _______, _______, _______, _______
),

/* Gamma
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_GAMMA] = LAYOUT_planck_2x2u(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______,         _______,      _______, _______, _______, _______
),

/* Delta
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_DELTA] = LAYOUT_planck_2x2u(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______,         _______,      _______, _______, _______, _______
),

/* Alpha
 * ,-----------------------------------------------------------------------------------.
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |             |             |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_ALPHA] = LAYOUT_planck_2x2u(
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______,      _______,         _______,      _______, _______, _______, _______
),

};


uint32_t layer_state_set_user(uint32_t state) {
  state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
  state = update_tri_layer_state(state, _HYPER, _RAISE, _SUPER);
  state = update_tri_layer_state(state, _HYPER, _LOWER, _HACKER);
  state = update_tri_layer_state(state, _SUPER, _LOWER, _OMEGA);
  state = update_tri_layer_state(state, _GREEK, _ADJUST, _DELTA);
  state = update_tri_layer_state(state, _OMEGA, _GREEK, _ALPHA);
  state = update_tri_layer_state(state, _SUPER, _GREEK, _THETA);
  state = update_tri_layer_state(state, _HACKER, _GREEK, _GAMMA);
  return state;
}

static bool tabbing = false;
static uint16_t tabtimer;
#define TABBING_TIMER 2500
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(record->event.pressed) {
    if (keycode == TABFW || keycode == TABBK) {
      tabtimer = timer_read();
      if(!tabbing) {
        register_code(KC_LALT);
        tabbing = true;
      }
      if(keycode == TABBK) register_code(KC_LSHIFT);
      tap_code(KC_TAB);
      if(keycode == TABBK) unregister_code(KC_LSHIFT);
      return false;
    } else {
      if(tabbing) {
        unregister_code(KC_LALT);
        tabbing = false;
      }
    }
  } else {
    if(tabbing) {
      if(keycode == HYPER) {
        unregister_code(KC_LALT);
        tabbing = false;
      }
    }
  }
  if(in_kaomoji_mode > 0) {
    if (record->event.pressed)
    switch (keycode) {
      case KC_DOWN:
        kaomoji_list_position++;
        if(get_kaomoji(kaomoji_list_position) == NULL) kaomoji_list_position = 0;
        for(int i=0;i<last_printed_kaomoji_len;i++) tap_code(KC_BSPC);
        last_printed_kaomoji_len = send_unicode_hex_string_mod(get_kaomoji(kaomoji_list_position));
        return false;
        break;
      case KC_ESC:
        for(int i=0;i<last_printed_kaomoji_len;i++) tap_code(KC_BSPC);
      case KC_ENT:
        in_kaomoji_mode = 0;
        return false;
        break;
    }
  }
  switch (keycode) {
    case KAOMOJI_FACE:
      if (record->event.pressed) {
        enter_kaomoji_mode(1);
      }
      return false;
      break;
    case KAOMOJI_ACTION:
      if (record->event.pressed) {
        enter_kaomoji_mode(2);
      }
      return false;
      break;
    case KAOMOJI_ITEM:
      if (record->event.pressed) {
        enter_kaomoji_mode(3);
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed)
        set_single_persistent_default_layer(_QWERTY);
      return false;
      break;
    case MUS1:
      if (record->event.pressed)
        PLAY_SONG(mushroom_sfx);
      return false;
      break;
    case NOPEBAD:
      if(record->event.pressed)
        PLAY_SONG(error_clanger);
        return false;
        break;
    case TFLIP:
      if (record->event.pressed)
        send_unicode_hex_string("0028 30CE 0CA0 75CA 0CA0 0029 30CE 5F61 253B 2501 253B");
      return false;
      break;
    case SHRUG:
      if (record->event.pressed)
        send_unicode_hex_string("00AF 005C 005F 0028 30C4 0029 005F 002F 00AF");
      return false;
      break;
    case DSPRV:
      if (record->event.pressed)
        send_unicode_hex_string("0CA0 005F 0CA0");
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

    SEQ_ONE_KEY(KC_S) {
      SEND_STRING(SS_TAP(X_PSCREEN));
      did_leader_succeed = true;
    } else 
    SEQ_TWO_KEYS(KC_S, KC_S) {
      SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_PSCREEN)SS_UP(X_LALT));
      did_leader_succeed = true;
    }
    leader_end();
  }
  if(tabbing)
    if (timer_elapsed(tabtimer) > TABBING_TIMER) {
      unregister_code(KC_LALT);
      tabbing = false; 
    }
}

void leader_start(void) {
    PLAY_SONG(leader_chime);
}

void leader_end(void) {
  if (did_leader_succeed) {
    PLAY_SONG(leader_done);
  } else {
    PLAY_SONG(leader_fdup);
  }
}

/*
 * both dance parser by DanielGGordon
 */
int cur_dance (qk_tap_dance_state_t *state) {
  // Favors being held
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

int cur_dance_tap (qk_tap_dance_state_t *state) {
  // Favors being tapped
  if (state->count == 1) {
    if (state->interrupted) {
      return SINGLE_TAP;
    }
    else {
      if (!state->pressed) return SINGLE_TAP;
      else return SINGLE_HOLD;
    }
  }
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  else if ((state->count == 3) && ((state->interrupted) || (!state->pressed))) return TRIPLE_TAP;
  else if (state->count == 3) return TRIPLE_HOLD;
  else return 8;
}

static int lstap_state, rstap_state, wktap_state, hltap_state, grtap_state;

void ls_finished (qk_tap_dance_state_t *state, void *user_data) {
  lstap_state = cur_dance(state);
  switch (lstap_state) {
    case SINGLE_TAP: register_mods(MOD_BIT(KC_LSHIFT));register_code(KC_8); break;
    case SINGLE_HOLD: register_code(KC_LSHIFT); break;
    case DOUBLE_HOLD:
    case DOUBLE_TAP: register_mods(MOD_BIT(KC_RALT));register_code(KC_7); break;
    case TRIPLE_HOLD:
    case TRIPLE_TAP: register_mods(MOD_BIT(KC_RALT));register_code(KC_8); break;
    case DOUBLE_SINGLE_TAP: register_mods(MOD_BIT(KC_RALT));register_code(KC_7); break;
  }
}

void ls_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (lstap_state) {
    case SINGLE_TAP: unregister_code(KC_8);unregister_mods(MOD_BIT(KC_LSHIFT)); break;
    case SINGLE_HOLD: unregister_code(KC_LSHIFT); break;
    case DOUBLE_HOLD:
    case DOUBLE_TAP: unregister_code(KC_7);unregister_mods(MOD_BIT(KC_RALT)); break;
    case TRIPLE_HOLD:
    case TRIPLE_TAP: unregister_code(KC_8);unregister_mods(MOD_BIT(KC_RALT)); break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_7);unregister_mods(MOD_BIT(KC_RALT));
  }
  lstap_state = 0;
}

void rs_finished (qk_tap_dance_state_t *state, void *user_data) {
  rstap_state = cur_dance(state);
  switch (rstap_state) {
    case SINGLE_TAP: register_mods(MOD_BIT(KC_LSHIFT));register_code(KC_9); break;
    case SINGLE_HOLD: register_code(KC_LSHIFT); break;
    case DOUBLE_HOLD:
    case DOUBLE_TAP: register_mods(MOD_BIT(KC_RALT));register_code(KC_0); break;
    case TRIPLE_HOLD:
    case TRIPLE_TAP: register_mods(MOD_BIT(KC_RALT));register_code(KC_9); break;
    case DOUBLE_SINGLE_TAP: register_mods(MOD_BIT(KC_RALT));register_code(KC_0); break;
  }
}

void rs_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (rstap_state) {
    case SINGLE_TAP: unregister_code(KC_9);unregister_mods(MOD_BIT(KC_LSHIFT)); break;
    case SINGLE_HOLD: unregister_code(KC_LSHIFT); break;
    case DOUBLE_HOLD:
    case DOUBLE_TAP: unregister_code(KC_0);unregister_mods(MOD_BIT(KC_RALT)); break;
    case TRIPLE_HOLD:
    case TRIPLE_TAP: unregister_code(KC_9);unregister_mods(MOD_BIT(KC_RALT)); break;
    case DOUBLE_SINGLE_TAP: unregister_code(KC_0);unregister_mods(MOD_BIT(KC_RALT));
  }
  rstap_state = 0;
}

void m1tapdance (qk_tap_dance_state_t *state, void *user_data) {
  if(cancel_next_macro_td) {
    cancel_next_macro_td = false;
    return;
  }
  switch (state->count) {
    case 1: tap_code(KC_F13);break;
    case 2: tap_code(KC_F14);break;
    case 3: tap_code(KC_F15);break;
    case 4: tap_code(KC_F16);break;
    case 5: tap_code(KC_F17);break;
  }
}

void m2tapdance (qk_tap_dance_state_t *state, void *user_data) {
  if(cancel_next_macro_td) {
    cancel_next_macro_td = false;
    return;
  }
  switch (state->count) {
    case 1: tap_code(KC_F18);break;
    case 2: tap_code(KC_F19);break;
    case 3: tap_code(KC_F20);break;
    case 4: tap_code(KC_F21);break;
    case 5: tap_code(KC_F22);break;
  }
}

void bs_taphandler (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: tap_code(KC_BSPC);break;
    case 2: register_mods(MOD_BIT(KC_LCTL));tap_code(KC_BSPC);unregister_mods(MOD_BIT(KC_LCTL)); break;
  }
}

void wk_finished (qk_tap_dance_state_t *state, void *user_data) {
  wktap_state = cur_dance(state);
  switch (wktap_state) {
    case SINGLE_TAP:
      tap_code(KC_LGUI);
      break;
    case SINGLE_HOLD:
      register_code(KC_LGUI);
      break;
    case DOUBLE_TAP:
      tap_code(KC_APP);
      break;
  }
}

void wk_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (wktap_state) {
    case SINGLE_HOLD:
      unregister_code(KC_LGUI);
      break;
  }
  wktap_state = 0;
}

void hyperlead_finished (qk_tap_dance_state_t *state, void *user_data) {
  hltap_state = cur_dance(state);
  switch (hltap_state) {
    case SINGLE_TAP:
      qk_leader_start();
      break;
    case SINGLE_HOLD:
      layer_on(_HYPER);
      break;
  }
}

void hyperlead_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (hltap_state) {
    case SINGLE_HOLD:
      layer_off(_HYPER);
      break;
  }
  hltap_state = 0;
}

void greek_finished (qk_tap_dance_state_t *state, void *user_data) {
  grtap_state = cur_dance(state);
  switch (grtap_state) {
    case SINGLE_TAP:
      tap_code(KC_F24);
      break;
    case SINGLE_HOLD:
      layer_on(_GREEK);
      break;
  }
}

void greek_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (grtap_state) {
    case SINGLE_HOLD:
      layer_off(_GREEK);
      break;
  }
  grtap_state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [LSCD]     = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL,ls_finished, ls_reset, 185),
  [RSCD]     = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL,rs_finished, rs_reset, 185),
  [M1TD]     = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, m1tapdance, NULL, 350),
  [M2TD]     = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, m2tapdance, NULL, 350),
  [HPRLD]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL,hyperlead_finished, hyperlead_reset),
  [GRKTD]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL,greek_finished, greek_reset),
  [GUIMN]    = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, wk_finished, wk_reset, 250), 
  [BSPTD]    = ACTION_TAP_DANCE_FN_ADVANCED_TIME(bs_taphandler, NULL, NULL, 120), 
  [GRCL]     = ACTION_TAP_DANCE_DOUBLE(KC_GRV,  KC_CALCULATOR),
//  [AUMENT]   = ACTION_TAP_DANCE_DOUBLE(KC_QUOT, KC_ENT),
  [OUMAST]   = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_BSLS),
  [DELPL]    = ACTION_TAP_DANCE_DOUBLE(KC_DEL,  KC_MINS),
  [ZABRC]    = ACTION_TAP_DANCE_DOUBLE(KC_Z,    KC_NUBS),
};