#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
//#define _COLEMAK 1
//#define _DVORAK 2
#define _LOWER 1
#define _RAISE 2
#define _MOUSE 3
#define _ADJUST 16

#define M_START_CMDER M(0)

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  //COLEMAK,
  //DVORAK,
  LOWER,
  RAISE,
  MOUSE,
  ADJUST,
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Qwerty
 * ,-----------------------------------------.    ,-----------------------------------------.
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |    |   Y  |   U  |   I  |   O  |   P  |  -   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Esc  |   A  |   S  |   D  |   F  |   G  |    |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |    |   N  |   M  |   ,  |   .  |   /  |Shift |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lw/Bk |Del   |    |Enter |Ris/Sp| Left | Down |  Up  |Right |
 * `-----------------------------------------'    `-----------------------------------------'
 */
[_QWERTY] = LAYOUT_ortho_4x12( \
  KC_TAB,   	   KC_Q,    KC_W,    KC_E,    KC_R,                  KC_T,   KC_Y,   KC_U,               KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_ESC,   	   KC_A,    KC_S,    KC_D,    KC_F,                  KC_G,   KC_H,   KC_J,               KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  OSM(MOD_LSFT), KC_Z,    KC_X,    KC_C,    KC_V,                  KC_B,   KC_N,   KC_M,               KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT , \
  ADJUST,  	     KC_LCTL, KC_LALT, KC_LGUI, LT(_LOWER, KC_BSPC),   KC_DEL, KC_ENT,  LT(_RAISE, KC_SPC),  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),

/* Colemak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |  '   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
/*[_COLEMAK] = LAYOUT_ortho_4x12( \
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSPC, \
  KC_ESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , \
  ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
),*/

/* Dvorak
 * ,-----------------------------------------------------------------------------------.
 * | Tab  |   '  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Esc  |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |  /   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |Adjust| Ctrl | Alt  | GUI  |Lower |Space |Space |Raise | Left | Down |  Up  |Right |
 * `-----------------------------------------------------------------------------------'
 */
/*[_DVORAK] = KEYMAP(                                                   \
  KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,    KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_BSPC, \
  KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,    KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_SLSH, \
  KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_ENT , \
  ADJUST,  KC_LCTL, KC_LALT, KC_LGUI, LOWER,   KC_SPC,  KC_SPC,  RAISE,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT \
  ),*/

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   ~  |   !  |   @  |   #  |   $  |   %  |   ^  |   &  |   *  |   (  |   )  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   _  |   +  |   {  |   }  |  |   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO ~ |ISO | |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12( \
  KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_DEL, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,S(KC_NUHS),S(KC_NUBS),_______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Raise
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |ISO # |ISO / |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |             |      | Next | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12( \
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, \
  KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS, \
  _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_NUHS, KC_NUBS, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_MNXT, KC_VOLD, KC_VOLU, KC_MPLY \
),

/* Mouse
 * ,-----------------------------------------.    ,-----------------------------------------.
 * |      |      |      |      |      |      |    |      | ACL0 | ACL1 | ACL2 |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      | MB1  | MB2  |      |    | MoLt | MoDn | MoUp | MoRt |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |Mcr1  |Mcr2  |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * `-----------------------------------------'    `-----------------------------------------'
 */
[_MOUSE] = LAYOUT_ortho_4x12( \
  _______,  _______,  _______,  _______,    _______,    _______,   _______,   KC_ACL0,   KC_ACL1,  KC_ACL2,   _______, _______, \
  _______,  _______,  _______,  KC_BTN1,    KC_BTN2,    _______,   KC_MS_L,   KC_MS_D,   KC_MS_U,  KC_MS_R,   _______, _______, \
  _______,  _______,  _______,  _______,    _______,    _______,   M_START_CMDER,      M(1),      _______,  _______,   _______, _______, \
  _______,  _______,  _______,  _______,    _______,    _______,   _______,   _______,   _______,  _______,   _______, _______ \
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------.    ,-----------------------------------------.
 * |      | Reset|      |      |      |      |    |      |      |      |      |      |  Del |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |Aud on|Audoff|AGnorm|    |AGswap|Qwerty|Colemk|Dvorak|Mouse |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |    |      |      |      |      |      |      |
 * `-----------------------------------------'    `-----------------------------------------'
 */
[_ADJUST] =  LAYOUT_ortho_4x12( \
  _______, RESET,   _______, _______, _______, _______, _______, _______, _______, _______, _______,    KC_DEL, \
  _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______,  TG(_MOUSE), _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______ \
)


};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
 //   case COLEMAK:
 //     if (record->event.pressed) {
 //       #ifdef AUDIO_ENABLE
 //         PLAY_SONG(tone_colemak);
 //       #endif
 //       persistent_default_layer_set(1UL<<_COLEMAK);
 //     }
 //     return false;
 //     break;
 //   case DVORAK:
 //     if (record->event.pressed) {
 //       #ifdef AUDIO_ENABLE
 //         PLAY_SONG(tone_dvorak);
 //       #endif
 //       persistent_default_layer_set(1UL<<_DVORAK);
 //     }
 //     return false;
 //     break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
    case COLEMAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_COLEMAK);
      }
      return false;
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
  }
  return true;
}

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt){
  if(record->event.pressed){
    switch(id){
    case 0:
      return MACRO(D(LGUI), U(LGUI), T(C), D(LSFT), T(SCLN), U(LSFT), T(BSLS), T(T), T(O), T(O), T(L), T(S), T(BSLS), T(C), T(M), T(D), T(E), T(R), T(BSLS), T(C), T(M), T(D), T(E), T(R), T(DOT), T(E), T(X), T(E), D(ENT), U(ENT), END);
      break;
    case 1:
      return MACRO(D(LSFT), T(B), U(LSFT), T(Y), T(E), D(LSFT), T(1), U(LSFT), END);
      break;
    }
  }

  return MACRO_NONE;
};
