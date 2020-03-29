/* Cato976 layout for the Dactyl Manuform 5x6 Keyboard */ 

#include QMK_KEYBOARD_H
#include "action_layer.h"


/*#define _QWERTY 0*/
/*#define _LOWER 1*/
#define _RAISE 2

#define RAISE MO(_RAISE)
/*#define LOWER MO(_LOWER)*/

typedef struct {
    bool is_press_action;
    int state;
} tap;

enum _ergodox_layers {
    _COLEMAK = 0,
    _QWERTY,
    // Intermediate layers
    _MDIA_MOUSE,
    _SYMB,
    _MACRO
};

enum custom_keycodes {
    CMDER = SAFE_RANGE,
    VERT_PASS
};

//Tap Dance Declarations
enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    TRIPLE_TAP = 5,
    TRIPLE_HOLD = 6
};

enum {
    TD_ESC_CAPS = 0,
    TD_HOM_INSR,
    TD_SYM_COLEMAK,
    ATL_OSL2,
    GUI_OSL1,
    END_OSL3
};

int cur_dance (qk_tap_dance_state_t *state);
void alt_finished (qk_tap_dance_state_t *state, void *user_data);
void gui_finished (qk_tap_dance_state_t *state, void *user_data);
void end_finished (qk_tap_dance_state_t *state, void *user_data);
void alt_reset (qk_tap_dance_state_t *state, void *user_data);
void gui_reset (qk_tap_dance_state_t *state, void *user_data);
void end_reset (qk_tap_dance_state_t *state, void *user_data);

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    //Tap once for Esc, twice for Caps Lock
    [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    //Tap once for Home, twice for insert 
    [TD_HOM_INSR]  = ACTION_TAP_DANCE_DOUBLE(KC_HOME, KC_INS),
    // Other declarations would go here, separated by commas, if you have them
    [ATL_OSL2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_finished, alt_reset),
    [GUI_OSL1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, gui_finished, gui_reset),
    [END_OSL3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, end_finished, end_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* keymap 0: colemak layer
     *
     * ,-------------------------------------------.                                                     ,-------------------------------------------.
     * |   =    |   1  |   2  |   3  |   4  |   5  |                                                     |  6   |   7  |   8  |   9  |   0  |   -    |
     * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
     * | Tab    |   Q  |   W  |   F  |   P  |   G  |                                                     |   J  |   L  |   U  |   Y  |   ;  |   \    |
     * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
     * | Esc/CAP|   A  |   R  |   S  |   T  |   D  |                                                     |   H  |   N  |   E  |   I  |O / L2|   '    |
     * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
     * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |                                                     |   K  |   M  |   ,  |   .  |//Ctrl| RShift |
     * `---------------+------+------+-------------'                                                     `------+------+------+------+------+--------'
     *                 | Left | Right|                                                                                 |  Up  | Down |
     *                 `-------------'                                                                                 `-------------'
     *                                       ,-------------.                                     ,-------------.         
     *                                       |      |      |                                     |      |      |         
     *                                       | BS/GV| Del  |                                     | Enter|Space |         
     *                                       |      |      +---------------.     ,---------------+      |      |         
     *                                       `-------------|Alt/L2 | Ctrl  |     |Gui/L1 |Ctl/Esc|-------------'         
     *                                                     |-------+-------|     |-------+-------|                       
     *                                                     |End/Mac|HM/Ins |     | PgUp  | PgDn  |                       
     *                                                     `---------------'     `---------------`
     */

  [_COLEMAK] = LAYOUT_5x6(
     KC_EQL         , KC_1       , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0         ,KC_MINS,
     KC_TAB         , KC_Q       , KC_W  , KC_F  , KC_P  , KC_G  ,                         KC_J  , KC_L  , KC_U  , KC_Y  ,KC_SCLN       ,KC_BSLS,
     TD(TD_ESC_CAPS), KC_A       , KC_R  , KC_S  , KC_T  , KC_D  ,                         KC_H  , KC_N  , KC_E  , KC_I  , KC_O         ,KC_QUOT,
     KC_LSFT        , CTL_T(KC_Z), KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_K  , KC_M  ,KC_COMM,KC_DOT ,CTL_T(KC_SLSH),KC_RSFT,
                      KC_LEFT,KC_RGHT,                                                       KC_UP  , KC_DOWN,
                                      KC_BSPC     , KC_DEL,                             KC_ENT      ,  KC_SPC,
                                      TD(ATL_OSL2), KC_LCTL,                            TD(GUI_OSL1), CTL_T(KC_ESC),
                                      TD(END_OSL3), TD(TD_HOM_INSR),                    KC_PGUP     , KC_PGDN
  ),

    /* keymap 1: qwerty layer
     *
     * ,-------------------------------------------.                                                     ,-------------------------------------------.
     * |   =    |   1  |   2  |   3  |   4  |   5  |                                                     |  6   |   7  |   8  |   9  |   0  |   -    |
     * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
     * | Tab    |   Q  |   W  |   E  |   R  |   T  |                                                     |   Y  |   U  |   I  |   O  |   P  |   \    |
     * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
     * | Esc/CAP|   A  |   S  |   D  |   F  |   G  |                                                     |   H  |   J  |   K  |   L  |; / L2|   '    |
     * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
     * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |                                                     |   N  |   M  |   ,  |   .  |//Ctrl| RShift |
     * `---------------+------+------+-------------'                                                     `------+------+------+------+------+--------'
     *                 | Left | Right|                                                                                 |  Up  | Down |
     *                 `-------------'                                                                                 `-------------'
     *                                       ,-------------.                                     ,-------------.         
     *                                       |      |      |                                     |      |      |         
     *                                       | BS/GV| Del  |                                     | Enter|Space |         
     *                                       |      |      +---------------.     ,---------------+      |      |         
     *                                       `-------------| Alt/L2| Ctrl  |     |Gui/L1 |Ctl/Esc|-------------'         
     *                                                     |-------+-------|     |-------+-------|                       
     *                                                     |End/Mac| HM/Ins|     | PgUp  | PgDn  |                       
     *                                                     `---------------'     `---------------`
     */

  [_QWERTY] = LAYOUT_5x6(
     KC_ESC , KC_1       , KC_2  , KC_3  , KC_4  , KC_5  ,                         KC_6  , KC_7  , KC_8  , KC_9  , KC_0         ,KC_BSPC,
     KC_TAB , KC_Q       , KC_W  , KC_E  , KC_R  , KC_T  ,                         KC_Y  , KC_U  , KC_I  , KC_O  , KC_P         ,KC_MINS,
     KC_ESC , KC_A       , KC_S  , KC_D  , KC_F  , KC_G  ,                         KC_H  , KC_J  , KC_K  , KC_L  ,KC_SCLN       ,KC_QUOT,
     KC_LSFT, CTL_T(KC_Z), KC_X  , KC_C  , KC_V  , KC_B  ,                         KC_N  , KC_M  ,KC_COMM,KC_DOT ,CTL_T(KC_SLSH),KC_BSLASH,
                      KC_LEFT,KC_RGHT,                                               KC_UP    , KC_DOWN,
                                      KC_BSPC     , KC_DEL,                       KC_ENT      ,  KC_SPC,
                                      TD(ATL_OSL2), KC_LCTL,                      TD(GUI_OSL1), CTL_T(KC_ESC),
                                      TD(END_OSL3), TD(TD_HOM_INSR),              KC_PGUP     , KC_PGDN
  ),

    /* keymap 3: symbols layer
     *
     * ,-------------------------------------------.                                                     ,-------------------------------------------.
     * | PrntScr|  F1  |  F2  |  F3  |  F4  |  F5  |                                                     | F6   |  F7  |  F8  |  F9  |  F10 |  F11   |
     * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
     * | ScrlLk |   !  |   @  |   {  |   }  |   |  |                                                     |  UP  |   7  |   8  |   9  |   *  |  F12   |
     * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
     * | Pause  |   #  |   $  |   (  |   )  |   `  |                                                     | DOWN |   4  |   5  |   6  |   +  |        |
     * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
     * | NumLck |   %  |   ^  |   [  |   ]  |   ~  |                                                     |   &  |   1  |   2  |   3  |   /  |        |
     * `---------------+------+------+-------------'                                                     `------+------+------+------+------+--------'
     *                 |      |      |                                                                                 |   .  |   0  |
     *                 `-------------'                                                                                 `-------------'
     *                                       ,-------------.                                     ,-------------.         
     *                                       |      |      |                                     |      |      |         
     *                                       |      |      |                                     |      |      |         
     *                                       |      |      +---------------.     ,---------------+      |      |         
     *                                       `-------------|       |       |     |       |       |-------------'         
     *                                                     |-------+-------|     |-------+-------|                       
     *                                                     |       |       |     |       |       |                       
     *                                                     `---------------'     `---------------`
     */

  // SYMBOLS
  [_SYMB] = LAYOUT_5x6(
     KC_PSCR        , KC_F1      , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                         KC_F6  , KC_F7 , KC_F8 , KC_F9 , KC_F10, KC_F11  ,
     KC_SLCK        , KC_EXLM    , KC_AT ,KC_LCBR,KC_RCBR,KC_PIPE,                         KC_UP  , KC_P7 , KC_P8 , KC_P9 ,KC_PAST, KC_F12  ,
     KC_PAUS        , KC_HASH    , KC_DLR,KC_LPRN,KC_RPRN, KC_GRV,                         KC_DOWN, KC_P4 , KC_P5 , KC_P6 ,KC_PPLS,  _______,
     KC_NLCK        , KC_PERC    ,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,                         KC_AMPR, KC_P1 , KC_P2 , KC_P3 ,KC_PSLS,  _______,
                      _______,_______,                                                       KC_PDOT, KC_P0,
                                      _______,_______,                        _______, _______,
                                      _______,_______,                        _______, _______,
                                      _______,_______,                        _______, _______
  ),

    /* keymap 4: macro layer
     *
     * ,-------------------------------------------.                                                     ,-------------------------------------------.
     * |        |      |      |      |      |      |                                                     |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |                                                     |      |      |      |      | PASS |        |
     * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |                                                     |      |      |      |      |      |        |
     * |--------+------+------+------+------+------|                                                     |------+------+------+------+------+--------|
     * |        |      |      | CMDR |      |      |                                                     |      |      |      |      |      |        |
     * `---------------+------+------+-------------'                                                     `------+------+------+------+------+--------'
     *                 |      |      |                                                                                 |      |      |
     *                 `-------------'                                                                                 `-------------'
     *                                       ,-------------.                                     ,-------------.         
     *                                       |      |      |                                     |      |      |         
     *                                       |      |      |                                     |      |      |         
     *                                       |      |      +---------------.     ,---------------+      |      |         
     *                                       `-------------|       |       |     |       |       |-------------'         
     *                                                     |-------+-------|     |-------+-------|                       
     *                                                     |       |       |     |       |       |                       
     *                                                     `---------------'     `---------------`
     */

  // MACRO
  [_MACRO] = LAYOUT_5x6(
     _______, _______     , _______, _______, _______, _______,                         _______, _______, _______, _______, _______  , _______,
     _______, DF(_QWERTY) , _______, _______, _______, _______,                         _______, _______, _______, _______, VERT_PASS, _______,
     _______, DF(_COLEMAK), _______, _______, _______, _______,                         _______, _______, _______, _______, _______  , _______,
     _______, _______     , _______, CMDER  , _______, _______,                         _______, _______, _______, _______, _______  , _______,
                      _______, _______,                                                       _______, _______,
                                      _______, _______,                        _______, _______,
                                      _______, _______,                        _______, _______,
                                      _______, _______,                        _______, _______
  ),

  /*[_LOWER] = LAYOUT_5x6(*/

     /*KC_TILD,KC_EXLM, KC_AT ,KC_HASH,KC_DLR ,KC_PERC,                        KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_DEL,*/
     /*_______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC, KC_P7 , KC_P8 , KC_P9 ,_______,KC_PLUS,*/
     /*_______,KC_HOME,KC_PGUP,KC_PGDN,KC_END ,KC_LPRN,                        KC_RPRN, KC_P4 , KC_P5 , KC_P6 ,KC_MINS,KC_PIPE,*/
     /*_______,_______,_______,_______,_______,_______,                        _______, KC_P1 , KC_P2 , KC_P3 ,KC_EQL ,KC_UNDS,*/
                                             /*_______,KC_PSCR,            _______, KC_P0,*/
                                             /*_______,_______,            _______,_______,*/
                                             /*_______,_______,            _______,_______,*/
                                             /*_______,_______,            _______,_______*/

  /*),*/

  [_RAISE] = LAYOUT_5x6(
       KC_F12 , KC_F1 , KC_F2 , KC_F3 , KC_F4 , KC_F5 ,                        KC_F6  , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11 ,
       _______,_______,_______,_______,_______,KC_LBRC,                        KC_RBRC,_______,KC_NLCK,KC_INS ,KC_SLCK,KC_MUTE,
       _______,KC_LEFT,KC_UP  ,KC_DOWN,KC_RGHT,KC_LPRN,                        KC_RPRN,KC_MPRV,KC_MPLY,KC_MNXT,_______,KC_VOLU,
       _______,_______,_______,_______,_______,_______,                        _______,_______,_______,_______,_______,KC_VOLD,
                                               _______,_______,            KC_EQL ,_______,
                                               _______,_______,            _______,_______,
                                               _______,_______,            _______,_______,
                                               _______,_______,            _______,_______
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *  record) {

    switch(keycode) {
        case CMDER:
            if ( record->event.pressed) {
                SEND_STRING(SS_TAP(X_LGUI)SS_TAP(X_C)SS_LSFT(SS_TAP(X_SCOLON))SS_TAP(X_BSLASH)SS_TAP(X_T)SS_TAP(X_O)SS_TAP(X_O)SS_TAP(X_L)SS_TAP(X_S)SS_TAP(X_BSLASH)SS_TAP(X_C)SS_TAP(X_M)SS_TAP(X_D)SS_TAP(X_E)SS_TAP(X_R)SS_TAP(X_BSLASH)SS_TAP(X_C)SS_TAP(X_M)SS_TAP(X_D)SS_TAP(X_E)SS_TAP(X_R)SS_TAP(X_DOT)SS_TAP(X_E)SS_TAP(X_X)SS_TAP(X_E)SS_LCTRL(SS_LSFT(SS_TAP(X_ENTER))));
                return false;
            }
            break;
        case VERT_PASS:
            if ( record->event.pressed) {
                //SEND_STRING("V3rt@f0r3");
                SEND_STRING(SS_LSFT(SS_TAP(X_V))SS_TAP(X_3)SS_TAP(X_R)SS_TAP(X_T)SS_LSFT(SS_TAP(X_2))SS_TAP(X_F)SS_TAP(X_0)SS_TAP(X_R)SS_TAP(X_3));
                return false;
            }
            break;
        default:
            return true;
            break;
    }
    return true;
}

static tap tap_state = {
    .is_press_action = true,
    .state = 0
};

int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->pressed) return SINGLE_HOLD;
        else return SINGLE_TAP;
    }
    else if (state->count == 2) {
        if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    else if (state->count == 3) {
        if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    else return 8;
}

void alt_finished (qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case SINGLE_TAP: set_oneshot_layer(_SYMB, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
        case SINGLE_HOLD: register_code(KC_LALT); break;
        case DOUBLE_TAP: set_oneshot_layer(_SYMB, ONESHOT_START); set_oneshot_layer(_SYMB, ONESHOT_PRESSED); break;
        case DOUBLE_HOLD: register_code(KC_LALT); layer_on(_SYMB); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
}

void end_finished (qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case SINGLE_TAP: set_oneshot_layer(_MACRO, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
        case SINGLE_HOLD: register_code(KC_END); break;
        case DOUBLE_TAP: set_oneshot_layer(_MACRO, ONESHOT_START); set_oneshot_layer(_MACRO, ONESHOT_PRESSED); break;
        case DOUBLE_HOLD: register_code(KC_END); layer_on(_MACRO); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
}

void gui_finished (qk_tap_dance_state_t *state, void *user_data) {
    tap_state.state = cur_dance(state);
    switch (tap_state.state) {
        case SINGLE_TAP: set_oneshot_layer(_MDIA_MOUSE, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
        case SINGLE_HOLD: register_code(KC_RGUI); break;
        case DOUBLE_TAP: set_oneshot_layer(_MDIA_MOUSE, ONESHOT_START); set_oneshot_layer(_MDIA_MOUSE, ONESHOT_PRESSED); break;
        case DOUBLE_HOLD: register_code(KC_RGUI); layer_on(_MDIA_MOUSE); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
}

void alt_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP: break;
        case SINGLE_HOLD: unregister_code(KC_LALT); break;
        case DOUBLE_TAP: break;
        case DOUBLE_HOLD: layer_off(_SYMB); unregister_code(KC_LALT); break;
    }
    tap_state.state = 0;
}

void end_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP: break;
        case SINGLE_HOLD: unregister_code(KC_END); break;
        case DOUBLE_TAP: break;
        case DOUBLE_HOLD: layer_off(_MACRO); unregister_code(KC_END); break;
    }
    tap_state.state = 0;
}

void gui_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (tap_state.state) {
        case SINGLE_TAP: break;
        case SINGLE_HOLD: unregister_code(KC_RGUI); break;
        case DOUBLE_TAP: break;
        case DOUBLE_HOLD: layer_off(_MDIA_MOUSE); unregister_code(KC_RGUI); break;
    }
    tap_state.state = 0;
}
