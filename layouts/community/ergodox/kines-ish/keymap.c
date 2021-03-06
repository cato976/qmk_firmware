#include QMK_KEYBOARD_H
#include <string.h>
#include "eeprom.h"
#include "debug.h"
#include "action_layer.h"

//#define BASE 0 // default layer
//#define TARMAK 1 // tarmak
//#define COLEMAK 2 // colemak
//#define SYMB 3 // symbols
//#define MDIA 4 // media keys
//#define MCRO 5 // macros
#define M_START_BREATHING M(5)
#define M_STOP_BREATHING M(3)
#define FN_O LT(2,KC_O)

typedef struct {
    bool is_press_action;
    int state;
} tap;

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
    TD_SYM_COLEMAK,
    ALT_OSL1
};

enum _ergodox_layers {
    _QWERTY = 0,
    _COLEMAK,
    // Intermediate layers
    _MDIA_MOUSE,
    _SYMB,
    _MACRO
};

uint32_t click_count;
char lcd2[17];
uint32_t last_save_time = 0;
uint32_t last_click_count;
const uint32_t START_CLICK_COUNT = 139;

int cur_dance (qk_tap_dance_state_t *state);
void alt_finished (qk_tap_dance_state_t *state, void *user_data);
void alt_reset (qk_tap_dance_state_t *state, void *user_data);

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    //Tap once for Esc, twice for Caps Lock
    [TD_ESC_CAPS]  = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_CAPS),
    // Other declarations would go here, separated by commas, if you have them
    [ALT_OSL1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, alt_finished, alt_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Keymap 0: Basic layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |   =    |   1  |   2  |   3  |   4  |   5  | ALT(LEFT) |      | ALT(RIGHT)|   6  |   7  |   8  |   9  |   0  |   -    |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   W  |   E  |   R  |   T  |  L1  |           |  L2  |   Y  |   U  |   I  |   O  |   P  |   \    |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Esc/Cap|   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |   '    |
     * |--------+------+------+------+------+------|  L3  |           | COL  |------+------+------+------+------+--------|
     * | LShift |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  | RShift |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   | L1   | Grv  |Insert| Left | Right|                                       |  Up  | Down |   [  |   ]  |  L2  |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        | Ctrl | Alt  |       | LGui | Ctrl |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      | Home |       | PgUp |      |      |
     *                                 |Backsp| Del  |------|       |------| Enter| Space|
     *                                 |ace   |      | End  |       | PgDn |      |      |
     *                                 `--------------------'       `--------------------'
     */
    // If it accepts an argument (i.e, is a function), it doesn't need KC_.
    // Otherwise, it needs KC_*
    [_QWERTY] = LAYOUT_ergodox(  // layer 0 : default
            // left hand
            KC_EQL,            KC_1,    KC_2,    KC_3,     KC_4,     KC_5,  LALT(KC_LEFT), 
            KC_TAB,            KC_Q,    KC_W,    KC_E,     KC_R,     KC_T,  TG(_SYMB),
            TD(TD_ESC_CAPS),   KC_A,    KC_S,    KC_D,     KC_F,     KC_G,
            KC_LSFT,           KC_Z,    KC_X,    KC_C,     KC_V,     KC_B,  KC_FN3,
            KC_FN1,            KC_GRV,  KC_INS,  KC_LEFT,  KC_RGHT,
            KC_LCTL,KC_LALT,
            KC_HOME,
            KC_BSPC,KC_DEL,KC_END,
            // right hand
            LALT(KC_RGHT), KC_6,   KC_7,   KC_8,   KC_9,   KC_0,     KC_MINS,
            TG(_MDIA_MOUSE),KC_Y,  KC_U,   KC_I,   KC_O,   KC_P,     KC_BSLS,
            KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,  KC_QUOT,
            TG(_COLEMAK),  KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,  KC_RSFT,
            KC_UP,  KC_DOWN,KC_LBRC,KC_RBRC,  KC_FN1,
            KC_LGUI, KC_RCTL,
            KC_PGUP,
            KC_PGDN, KC_ENT, KC_SPC
            ),
    /* keymap 1: colemak layer
     *
     * ,--------------------------------------------------.             ,--------------------------------------------------.
     * |   =    |   1  |   2  |   3  |   4  |   5  |CTRL(GUI(LEFT)) |   |CTRL(GUI(RIGHT))|6|7|   8  |   9  |   0  |   -    |
     * |--------+------+------+------+------+-------------|             |------+------+------+------+------+------+--------|
     * | Tab    |   Q  |   W  |   F  |   P  |   G  |  L1  |             |  L1  |   J  |   L  |   U  |   Y  |   ;  |   \    |
     * |--------+------+------+------+------+------|      |             |      |------+------+------+------+------+--------|
     * | Bksp   |   A  |   R  |   S  |   T  |   D  |------|             |------|   H  |   N  |   E  |   I  |O / L2|   '    |
     * |--------+------+------+------+------+------| Hyper|             |      |------+------+------+------+------+--------|
     * | LShift |Z/Ctrl|   X  |   C  |   V  |   B  |      |             |      |   K  |   M  |   ,  |   .  |//Ctrl| RShift |
     * `--------+------+------+------+------+-------------'             `-------------+------+------+------+------+--------'
     *   |Grv/L1|  '"  |Insert| Left | Right|                                         |  Up  | Down |   [  |   ]  | ~L1  |
     *   `----------------------------------'                                         `----------------------------------'
     *                                        ,-------------.           ,-------------.
     *                                        | Ctl  | Alt  |           | Gui  |Ctrl/Esc|
     *                                 ,------|------|------|           |------+--------+------.
     *                                 |      |      | Home |           | PgUp |        |      |
     *                                 | Bkspc| Del  |------|           |------| Enter  |Space |
     *                                 |      |      | End  |           | PgDn |        |      |
     *                                 `--------------------'           `----------------------'
     */
    // If it accepts an argument (i.e, is a function), it doesn't need KC_.
    // Otherwise, it needs KC_*
    [_COLEMAK] = LAYOUT_ergodox(  // layer 2 : colemak
            // left hand
            KC_EQL,         KC_1,         KC_2,   KC_3,   KC_4,   KC_5,   LGUI(LCTL(KC_LEFT)),
            KC_TAB,         KC_Q,         KC_W,   KC_F,   KC_P,   KC_G,   TG(_SYMB),
            TD(TD_ESC_CAPS),KC_A,         KC_R,   KC_S,   KC_T,   KC_D,
            KC_LSFT,        CTL_T(KC_Z),  KC_X,   KC_C,   KC_V,   KC_B,   KC_FN3,
            KC_FN2,KC_GRV,   KC_INS, KC_LEFT,KC_RGHT,
            KC_LCTL,TD(ALT_OSL1),
            KC_HOME,
            KC_BSPC,KC_DEL,KC_END,
            // right hand
            LGUI(LCTL(KC_RGHT)),KC_6,         KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,
            TG(_MDIA_MOUSE),    KC_J,         KC_L,   KC_U,   KC_Y,   KC_SCLN,KC_BSLS,
            KC_H,         KC_N,   KC_E,   KC_I,   FN_O,   KC_QUOT,
            KC_TRNS,            KC_K,         KC_M,   KC_COMM,KC_DOT, CTL_T(KC_SLSH),   KC_RSFT,
            KC_UP,  KC_DOWN,KC_LBRC,KC_RBRC,KC_FN1,
            KC_LGUI,        CTL_T(KC_ESC),
            KC_PGUP,
            KC_PGDN,KC_ENT, KC_SPC
            ),
    /* Keymap 2: Media and mouse keys
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * |        |      |      |      |      |      |      |           |      |      |MS_AC1|MS_AC2|MS_AC3|      |BL_INC  |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * |        |      |      | MsUp |      |      |      |           |      |      |MSWUP |MSWLT |MSWRT |      |BL_DEC  |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * |        |      |MsLeft|MsDown|MsRght|      |------|           |------|      |Lclk  |Rclk  |      |      |  Play  |
     * |--------+------+------+------+------+------|      |           |BL_ON |------+------+------+------+------+--------|
     * |        |      |      |      |      |      |      |           |      |      |MSWDN | Prev | Next |      |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |RESET |      | Lclk | Rclk |                                       |VolUp |VolDn | Mute |RESET |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |Brwser|
     *                                 |      |      |------|       |------|      |Back  |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
    // MEDIA AND MOUSE
    [_MDIA_MOUSE] = LAYOUT_ergodox(
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, RESET,   KC_TRNS, KC_BTN1, KC_BTN2,
            KC_TRNS, KC_TRNS,
            KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS,
            // right hand
            KC_TRNS,  KC_TRNS, KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, BL_INC,
            KC_TRNS,  KC_TRNS, KC_WH_U, KC_WH_L, KC_WH_R, KC_TRNS, BL_DEC,
            KC_TRNS, KC_BTN1, KC_BTN2, KC_TRNS, KC_TRNS, KC_MPLY,
            BL_ON,    KC_TRNS, KC_WH_D, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS,
            KC_VOLU, KC_VOLD, KC_MUTE, RESET,   KC_TRNS,

            KC_TRNS, KC_TRNS,
            KC_TRNS,
            KC_TRNS, KC_TRNS, KC_WBAK
            ),
    /* Keymap 3: Symbol Layer
     *
     * ,--------------------------------------------------.           ,--------------------------------------------------.
     * | PrScr  |  F1  |  F2  |  F3  |  F4  |  F5  |      |           |      |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
     * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
     * | ScrLk  |   !  |   @  |   {  |   }  |   |  |      |           |      |   Up |   7  |   8  |   9  |   *  |   F12  |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | Pause  |   #  |   $  |   (  |   )  |   `  |------|           |------| Down |   4  |   5  |   6  |   +  |        |
     * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
     * | NUMLK  |   %  |   ^  |   [  |   ]  |   ~  |      |           |      |   &  |   1  |   2  |   3  |   /  |        |
     * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
     *   |      |      |      |      |      |                                       |      |    . |   0  |   =  |      |
     *   `----------------------------------'                                       `----------------------------------'
     *                                        ,-------------.       ,-------------.
     *                                        |      |      |       |      |      |
     *                                 ,------|------|------|       |------+------+------.
     *                                 |      |      |      |       |      |      |      |
     *                                 |      |      |------|       |------|      |      |
     *                                 |      |      |      |       |      |      |      |
     *                                 `--------------------'       `--------------------'
     */
    // SYMBOLS
    [_SYMB] = LAYOUT_ergodox(
            // left hand
            KC_PSCR,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_TRNS,
            KC_SLCK,KC_EXLM,KC_AT,  KC_LCBR,KC_RCBR,KC_PIPE,KC_TRNS,
            KC_PAUS,KC_HASH,KC_DLR, KC_LPRN,KC_RPRN,KC_GRV,
            KC_NLCK,KC_PERC,KC_CIRC,KC_LBRC,KC_RBRC,KC_TILD,KC_TRNS,
            KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
            KC_TRNS,KC_TRNS,
            KC_TRNS,
            KC_TRNS,KC_TRNS,KC_TRNS,
            // right hand
            KC_TRNS, KC_F6,   KC_F7,  KC_F8,   KC_F9,   KC_F10,  KC_F11,
            KC_TRNS, KC_UP,   KC_P7,  KC_P8,   KC_P9,   KC_PAST, KC_F12,
            KC_DOWN, KC_P4,  KC_P5,   KC_P6,   KC_PPLS, KC_TRNS,
            KC_TRNS, KC_AMPR, KC_P1,  KC_P2,   KC_P3,   KC_PSLS, KC_TRNS,
            KC_TRNS,KC_PDOT, KC_P0,   KC_EQL,  KC_TRNS,
            KC_TRNS, KC_TRNS,
            KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS
            ),

            /* Keymap 4: Macros
             *
             * ,--------------------------------------------------.           ,--------------------------------------------------.
             * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
             * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
             * |        |      |      |      |      |      |      |           |      |      |      |      |      | PASS |        |
             * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
             * |        |      |      |      |      |      |------|           |------|      |      |      |      |      |        |
             * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
             * |        |      |      |CMDR  |      |BREATH|      |           |      |      |      |      |      |      |        |
             * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
             *   |      |      |      |      |ST_BRT|                                       |      |      |      |      |      |
             *   `----------------------------------'                                       `----------------------------------'
             *                                        ,-------------.       ,-------------.
             *                                        |      |      |       |      |      |
             *                                 ,------|------|------|       |------+------+------.
             *                                 |      |      |      |       |      |      |      |
             *                                 |      |      |------|       |------|      |      |
             *                                 |      |      |      |       |      |      |      |
             *                                 `--------------------'       `--------------------'
             */
    // MACROS
    [_MACRO] = LAYOUT_ergodox(
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, DF(_QWERTY), KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, DF(_COLEMAK), KC_TRNS, KC_TRNS,        KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, CMDER,          KC_TRNS, M_START_BREATHING, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,        M_STOP_BREATHING,
            KC_TRNS, KC_TRNS,
            KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS,
            // right hand
            KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, VERT_PASS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,

            KC_TRNS, KC_TRNS,
            KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS
            ),
};

const uint16_t PROGMEM fn_actions[] = {
    [1] = ACTION_LAYER_TAP_TOGGLE(_MDIA_MOUSE),         // FN1 - Momentary Layer 1 (Media)
    [2] = ACTION_LAYER_TAP_TOGGLE(_SYMB),               // FN2 - Momentary Layer 2 (Symbols)
    [3] = ACTION_LAYER_TAP_TOGGLE(_MACRO)               // FN3 - Momentary Layer 3 (Macro)
};


void save_click_count(bool ignore_time)
{
    // If no more key clicks, don't bother saving
    if (last_click_count != click_count) {
        //Note: The ATMEGA32u4 has a limited number of writes before the memory becomes
        //unstable.  This routine attempts to limit the number of saves for that reason

        // if already saved in the last time period, don't bother saving
        uint32_t cur_time = timer_read32();
        eeprom_update_dword(EECONFIG_CLICK_COUNT, click_count);
        if (cur_time - last_save_time > 3600000 || ignore_time) { //if unsaved for an hour (3600000) ->3 min (180000)
            //update will only write if the value differs in the eeprom
            eeprom_update_dword(EECONFIG_CLICK_COUNT, click_count);

            click_count = 0;
            last_click_count = click_count;
            last_save_time = cur_time;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *  record) {

    // Display key click count
    if(record->event.pressed)
    {
        click_count++;
        save_click_count(false);
    }

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

bool process_record_keymap(uint16_t keycode, keyrecord_t *  record) {
    switch(keycode) {
        case KC_TRNS:
        case KC_NO:
            /* Always cancel one-shot layer when another key gets pressed */
            if (record->event.pressed && is_oneshot_layer_active())
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            return true;
        case RESET:
            /* Don't allow reset from oneshot layer state */
            if (record->event.pressed && is_oneshot_layer_active()){
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                return false;
            }   
            return true;
        default:
            return true;
            break;
    }
    return true;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) 
{
    //click_count = eeprom_read_dword(EECONFIG_CLICK_COUNT);
    click_count = START_CLICK_COUNT > click_count ? START_CLICK_COUNT : click_count;

    last_click_count = click_count;
    last_save_time = timer_read32();
    //lcd_init(LCD_DISP_OFF);
    //memset(lcd2,0,sizeof(lcd2));
    save_click_count(true);
}

//// Runs constantly in the background, in a loop.
void matrix_scan_user(void){
    //if(record->event.pressed)
    //{
    //    save_click_count(false);
    //}
}

static tap alttap_state = {
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
    alttap_state.state = cur_dance(state);
    switch (alttap_state.state) {
        case SINGLE_TAP: set_oneshot_layer(_SYMB, ONESHOT_START); clear_oneshot_layer_state(ONESHOT_PRESSED); break;
        case SINGLE_HOLD: register_code(KC_LALT); break;
        case DOUBLE_TAP: set_oneshot_layer(_SYMB, ONESHOT_START); set_oneshot_layer(_SYMB, ONESHOT_PRESSED); break;
        case DOUBLE_HOLD: register_code(KC_LALT); layer_on(_SYMB); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
    }
}

void alt_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (alttap_state.state) {
        case SINGLE_TAP: break;
        case SINGLE_HOLD: unregister_code(KC_LALT); break;
        case DOUBLE_TAP: break;
        case DOUBLE_HOLD: layer_off(_SYMB); unregister_code(KC_LALT); break;
    }
    alttap_state.state = 0;
}
