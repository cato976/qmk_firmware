#include QMK_KEYBOARD_H

extern uint8_t is_master;

enum layer_names {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST
};

#define LOWER  MO(_LOWER)
#define RAISE  MO(_RAISE)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { \
  /* Qwerty
   * ,-----------------------------------------.             ,-----------------------------------------.
   * | Esc  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |BSpace|
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | Tab  |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |Shift | GUI  |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |Space |   Z  |   X  |   C  |   V  |   B  |             |   N  |   M  | Ctrl |  .   | Alt  | SCMD |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * | GUI  |      |      |      |Lower |Enter |             |Enter |Raise |      |      |      |      |
   * `-----------------------------------------'             `-----------------------------------------'
   */
  [_BASE] = LAYOUT_ortho_4x12(
   KC_ESC, KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,             KC_Y,  KC_U,  KC_I, KC_O,   KC_P, KC_BSPACE, \
   KC_TAB, KC_A,  KC_S,  KC_D,  KC_F,  KC_G,             KC_H,  KC_J,  KC_K, KC_L,   SFT_T(KC_SCLN), KC_RGUI,
   KC_SPC, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,             KC_N,  KC_M,  KC_RCTL, KC_DOT, KC_RALT, RGUI(KC_RSFT), \
   KC_RGUI, _______, _______, _______, LOWER, KC_ENT,    KC_ENT, RAISE, _______, _______, _______, _______ \
   ),

  /* Lower
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |   ~  |   !  |   @  |   #  |   $  |   %  |             |  ^   |  &   |  *   |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   <  |   >  |   (  |   )  |   `  |             |  -   |  {   |  }   |   [  |   ]  |  |   |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |   =  |   ?  |             |  _   |  +   |  ,   |   .  |   /  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |------| TRSP |             | TRSP | GUI  |      |      |      |      |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_LOWER] =  LAYOUT_ortho_4x12( \
      KC_TILD, KC_EXLM, KC_AT, KC_HASH, KC_DLR,  KC_PERC,    KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, _______,\
      _______, KC_LT, KC_GT, KC_LPRN, KC_RPRN, KC_GRV,       KC_MINS, KC_LCBR, KC_RCBR, KC_LBRC, KC_RBRC, KC_PIPE, \
      KC_LALT, _______, _______, _______, KC_EQL, KC_QUES,   KC_UNDS, KC_PLUS, KC_COMM, _______, KC_SLSH, _______, \
      _______, _______, _______, KC_TRNS, _______, KC_TRNS,  ADJUST, KC_RGUI, _______, _______, _______, _______ \
      ),

  /* Raise
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |   1  |   2  |   3  |  4   |   5  |             |   6  |   7  |   8  |   9  |   0  |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |   :  |   ;  |  "   |  '   |  \   |             | Left | Down | Up   |Right |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |ADJUST|      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      | GUI  |Shift |             |Shift |------|      |      |      |      |
   * `-----------------------------------------'             `-----------------------------------------'
   */
  [_RAISE] = LAYOUT_ortho_4x12( \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,  _______, \
  _______, KC_COLN, KC_SCLN, KC_DQT, KC_QUOT, KC_BSLS,         KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______, _______, \
  _______, _______, _______, _______, _______, _______,        ADJUST, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, KC_LGUI, KC_LSFT,        KC_LSFT, _______, _______, _______, _______, _______ \
  ),

  /* Adjust (Lower + Raise)
   * ,-----------------------------------------.             ,-----------------------------------------.
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |      |             |      |      |      |      |      |      |
   * |------+------+------+------+------+------|             |------+------+------+------+------+------|
   * |      |      |      |      |      |RESET |             |------|      |      |      |      |      |
   * `-----------------------------------------'             `-----------------------------------------'
   */
    [_ADJUST] =  LAYOUT_ortho_4x12( \
      _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, \
      _______, _______, _______, _______, _______, RESET,  _______, _______, _______, _______, _______, _______ \
      ),

};
