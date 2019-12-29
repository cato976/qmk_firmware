/*
Copyright 2017 Fred Sundvik
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "util.h"
#include "simple_visualizer.h"

enum _ergodox_layers {
    _QWERTY,
    _COLEMAK,
    // Intermediate layers
    _MDIA_MOUSE,
    _SYMB,
    _MACRO
};

static uint32_t next_led_target_color = 0;

//static const uint32_t led_emulation_colors[4] = {
//    LCD_COLOR(0, 0, 0),
//    LCD_COLOR(255, 255, 255),
//    LCD_COLOR(84, 255, 255),
//    LCD_COLOR(168, 255, 255),
//};

//typedef enum {
//    LCD_STATE_INITIAL,
//    LCD_STATE_LAYER_BITMAP,
//    LCD_STATE_BITMAP_AND_LEDS,
//} lcd_state_t;

//static lcd_state_t lcd_state = LCD_STATE_INITIAL;

typedef struct {
    uint8_t led_on;
    uint8_t led1;
    uint8_t led2;
    uint8_t led3;
} visualizer_user_data_t;

// The color animation animates the LCD color when you change layers
//static keyframe_animation_t one_led_color = {
//    .num_frames = 1,
//    .loop = false,
//    .frame_lengths = {gfxMillisecondsToTicks(0)},
//    .frame_functions = {lcd_backlight_keyframe_set_color},
//};

bool swap_led_target_color(keyframe_animation_t* animation, visualizer_state_t* state) {
    uint32_t temp = next_led_target_color;
    next_led_target_color = state->target_lcd_color;
    state->target_lcd_color = temp;
    return false;
}

// The color animation animates the LCD color when you change layers
//static keyframe_animation_t two_led_colors = {
//    .num_frames = 2,
//    .loop = true,
//    .frame_lengths = {gfxMillisecondsToTicks(1000), gfxMillisecondsToTicks(0)},
//    .frame_functions = {lcd_backlight_keyframe_set_color, swap_led_target_color},
//};

// The LCD animation alternates between the layer name display and a
// bitmap that displays all active layers
//static keyframe_animation_t lcd_bitmap_animation = {
//    .num_frames = 1,
//    .loop = false,
//    .frame_lengths = {gfxMillisecondsToTicks(0)},
//    .frame_functions = {lcd_keyframe_display_layer_bitmap},
//};
//
//static keyframe_animation_t lcd_bitmap_leds_animation = {
//    .num_frames = 2,
//    .loop = true,
//    .frame_lengths = {gfxMillisecondsToTicks(2000), gfxMillisecondsToTicks(2000)},
//    .frame_functions = {lcd_keyframe_display_layer_bitmap, lcd_keyframe_display_led_states},
//};

// This function should be implemented by the keymap visualizer
// Don't change anything else than state->target_lcd_color and state->layer_text as that's the only thing
// that the simple_visualizer assumes that you are updating
// Also make sure that the buffer passed to state->layer_text remains valid until the previous animation is
// stopped. This can be done by either double buffering it or by using constant strings
static void get_visualizer_layer_and_color(visualizer_state_t* state) {
    uint8_t saturation = 60;
    if (state->status.leds & (1u << USB_LED_CAPS_LOCK)) {
        saturation = 255;
    }

    uint8_t layer = biton32(state->status.layer);

    switch(layer) {
        case _COLEMAK:
        state->target_lcd_color = LCD_COLOR(84, saturation, 0xFF);
        state->layer_text = "Colemak";
        break;
        case _SYMB:
        state->target_lcd_color = LCD_COLOR(214, saturation, 0xFF);
        state->layer_text = "Symbols";
        break;
        case _MDIA_MOUSE:
        state->target_lcd_color = LCD_COLOR(130, saturation, 0xFF);
        state->layer_text = "Media & Mouse";
        break;
        case _MACRO:
        state->target_lcd_color = LCD_COLOR(130, saturation, 0xFF);
        state->layer_text = "Macro";
        break;
        default:
        state->target_lcd_color = LCD_COLOR(84, saturation, 0xFF);
        state->layer_text = "Default";
        break;
    }
}

//static inline bool is_led_on(visualizer_user_data_t* user_data, uint8_t num) {
//    return user_data->led_on & (1u << num);
//}

//static uint8_t get_led_index_master(visualizer_user_data_t* user_data) {
//    for (int i=0; i < 3; i++) {
//        if (is_led_on(user_data, i)) {
//            return i + 1;
//        }
//    }
//    return 0;
//}

//static uint8_t get_led_index_slave(visualizer_user_data_t* user_data) {
//    uint8_t master_index = get_led_index_master(user_data);
//    if (master_index!=0) {
//        for (int i=master_index; i < 3; i++) {
//            if (is_led_on(user_data, i)) {
//                return i + 1;
//            }
//        }
//    }
//
//    return 0;
//}
//
//static uint8_t get_secondary_led_index(visualizer_user_data_t* user_data) {
//    if (is_led_on(user_data, 0) &&
//            is_led_on(user_data, 1) &&
//            is_led_on(user_data, 2)) {
//        return 3;
//    }
//    return 0;
//}

//static uint8_t get_brightness(visualizer_user_data_t* user_data, uint8_t index) {
//    switch (index) {
//    case 1:
//        return user_data->led1;
//    case 2:
//        return user_data->led2;
//    case 3:
//        return user_data->led3;
//    }
//    return 0;
//}

//static void update_emulated_leds(visualizer_state_t* state, visualizer_keyboard_status_t* prev_status) {
//    visualizer_user_data_t* user_data_new = (visualizer_user_data_t*)state->status.user_data;
//    visualizer_user_data_t* user_data_old = (visualizer_user_data_t*)prev_status->user_data;
//
//    uint8_t new_index;
//    uint8_t old_index;
//
//    if (is_serial_link_master()) {
//        new_index = get_led_index_master(user_data_new);
//        old_index = get_led_index_master(user_data_old);
//    }
//    else {
//        new_index = get_led_index_slave(user_data_new);
//        old_index = get_led_index_slave(user_data_old);
//    }
//    uint8_t new_secondary_index = get_secondary_led_index(user_data_new);
//    uint8_t old_secondary_index = get_secondary_led_index(user_data_old);
//
//    uint8_t old_brightness = get_brightness(user_data_old, old_index);
//    uint8_t new_brightness = get_brightness(user_data_new, new_index);
//
//    uint8_t old_secondary_brightness = get_brightness(user_data_old, old_secondary_index);
//    uint8_t new_secondary_brightness = get_brightness(user_data_new, new_secondary_index);
//
//    if (lcd_state == LCD_STATE_INITIAL ||
//            new_index != old_index ||
//            new_secondary_index != old_secondary_index ||
//            new_brightness != old_brightness ||
//            new_secondary_brightness != old_secondary_brightness) {
//
//        if (new_secondary_index != 0) {
//            state->target_lcd_color = change_lcd_color_intensity(
//                led_emulation_colors[new_index], new_brightness);
//            next_led_target_color = change_lcd_color_intensity(
//                led_emulation_colors[new_secondary_index], new_secondary_brightness);
//
//            stop_keyframe_animation(&one_led_color);
//            start_keyframe_animation(&two_led_colors);
//        } else {
//            state->target_lcd_color = change_lcd_color_intensity(
//                led_emulation_colors[new_index], new_brightness);
//            stop_keyframe_animation(&two_led_colors);
//            start_keyframe_animation(&one_led_color);
//        }
//    }
//}

//static void update_lcd_text(visualizer_state_t* state, visualizer_keyboard_status_t* prev_status) {
//    if (state->status.leds) {
//        if (lcd_state != LCD_STATE_BITMAP_AND_LEDS ||
//                state->status.leds != prev_status->leds ||
//                state->status.layer != prev_status->layer ||
//                state->status.default_layer != prev_status->default_layer) {
//
//            // NOTE: that it doesn't matter if the animation isn't playing, stop will do nothing in that case
//            stop_keyframe_animation(&lcd_bitmap_animation);
//
//            lcd_state = LCD_STATE_BITMAP_AND_LEDS;
//            // For information:
//            // The logic in this function makes sure that this doesn't happen, but if you call start on an
//            // animation that is already playing it will be restarted.
//            start_keyframe_animation(&lcd_bitmap_leds_animation);
//        }
//    } else {
//        if (lcd_state != LCD_STATE_LAYER_BITMAP ||
//                state->status.layer != prev_status->layer ||
//                state->status.default_layer != prev_status->default_layer) {
//
//            stop_keyframe_animation(&lcd_bitmap_leds_animation);
//
//            lcd_state = LCD_STATE_LAYER_BITMAP;
//            start_keyframe_animation(&lcd_bitmap_animation);
//        }
//    }
//}

//void update_user_visualizer_state(visualizer_state_t* state, visualizer_keyboard_status_t* prev_status) {
//    // Check the status here to start and stop animations
//    // You might have to save some state, like the current animation here so that you can start the right
//    // This function is called every time the status changes
//
//    // NOTE that this is called from the visualizer thread, so don't access anything else outside the status
//    // This is also important because the slave won't have access to the active layer for example outside the
//    // status.
//
//    update_emulated_leds(state, prev_status);
//    update_lcd_text(state, prev_status);
//
//}
