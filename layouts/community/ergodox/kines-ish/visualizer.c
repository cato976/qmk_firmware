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

#include "syscalls.c"
#include <string.h>
#include "util.h"
#include "simple_visualizer.h"
#include "eeprom.h"
#include "eeconfig.h"

enum _ergodox_layers {
    _QWERTY,
    _COLEMAK,
    // Intermediate layers
    _MDIA_MOUSE,
    _SYMB,
    _MACRO
};

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

    int click_count = eeprom_read_dword(EECONFIG_CLICK_COUNT);
    char* s = "Default  ";
    char *p;
    char snum[7];
    for(int i = 0; i < 7; i++)
    {
        snum[i] = '\0';
    }

    switch(layer) {
        case _COLEMAK:
            state->target_lcd_color = LCD_COLOR(84, saturation, 0xFF);
            s = "Colemak ";
            p = malloc(7);
            strcpy(p, s); // puts string into buffer
            itoa(click_count, snum, 7);
            strcat(p, snum);
            state->layer_text = p;
            free(p);
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
            p = malloc(7);
            strcpy(p, s); // puts string into buffer
            itoa(click_count, snum, 7);
            strcat(p, snum);
            state->layer_text = p;
            free(p);
        break;
    }
}
