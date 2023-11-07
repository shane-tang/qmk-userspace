/* Copyright 2021 customMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include "matrix.h"

#ifdef BONGOCAT

extern matrix_row_t matrix[MATRIX_ROWS];

#define ANIM_FRAME_DURATION 75
#define IDLE_FRAMES 5
#define IDLE_TIMEOUT 750
#define SLEEP_TIMEOUT 15000

static const uint8_t bongofont[] PROGMEM = { \
    0xFC, 0x60, 0x01, 0x01, 0x01, \
    0xE0, 0x18, 0x06, 0x01, 0x00, \
    0xC2, 0xCA, 0x24, 0x88, 0xF0, \
    0xC0, 0x30, 0x0C, 0x03, 0x00, \
    0x8C, 0x9C, 0x1C, 0x1E, 0x0E, \
    0x84, 0x44, 0x44, 0x42, 0x82, \
    0x80, 0x86, 0x86, 0x40, 0x40, \
    0x80, 0x83, 0x83, 0x40, 0x40, \
    0x80, 0x80, 0x40, 0x40, 0x40, \
    0x80, 0x80, 0x40, 0x40, 0x20, \
    0x80, 0x40, 0x40, 0x20, 0x20, \
    0x80, 0x00, 0x00, 0x60, 0x60, \
    0x40, 0x40, 0x40, 0x20, 0x10, \
    0x40, 0x40, 0x21, 0x22, 0x22, \
    0x40, 0x40, 0x20, 0x21, 0x21, \
    0x40, 0x00, 0x00, 0x30, 0x30, \
    0x3C, 0x78, 0xF8, 0xF0, 0x70, \
    0x30, 0x40, 0x80, 0x80, 0x00, \
    0x24, 0x98, 0xC0, 0x88, 0x88, \
    0x24, 0x18, 0x00, 0x00, 0x00, \
    0x20, 0x40, 0x40, 0x41, 0x42, \
    0x20, 0x20, 0x40, 0x80, 0x80, \
    0x20, 0x20, 0x20, 0x20, 0x20, \
    0x20, 0x11, 0x11, 0x10, 0x10, \
    0x20, 0x10, 0x10, 0x10, 0x10, \
    0x18, 0x19, 0x00, 0x05, 0xFE, \
    0x18, 0x04, 0x02, 0x01, 0x02, \
    0x10, 0x20, 0x40, 0x80, 0x80, \
    0x10, 0x08, 0x04, 0x02, 0x04, \
    0x08, 0x10, 0x20, 0x40, 0x80, \
    0x08, 0x10, 0x10, 0x20, 0x20, \
    0x08, 0x08, 0x08, 0x08, 0x04, \
    0x08, 0x08, 0x08, 0x04, 0x04, \
    0x08, 0x04, 0x02, 0x01, 0x02, \
    0x06, 0x00, 0x00, 0x00, 0x00, \
    0x04, 0x08, 0x10, 0x20, 0x40, \
    0x04, 0x08, 0x10, 0x20, 0x20, \
    0x04, 0x08, 0x10, 0x10, 0x20, \
    0x04, 0x08, 0x08, 0x10, 0x10, \
    0x04, 0x04, 0x04, 0x08, 0x08, \
    0x04, 0x04, 0x04, 0x04, 0x08, \
    0x04, 0x04, 0x04, 0x02, 0x02, \
    0x03, 0x03, 0x61, 0xF0, 0xF8, \
    0x02, 0x64, 0x18, 0x04, 0x12, \
    0x02, 0x04, 0x04, 0x08, 0x08, \
    0x02, 0x04, 0x04, 0x02, 0x02, \
    0x02, 0x02, 0x04, 0x04, 0x08, \
    0x02, 0x02, 0x02, 0x01, 0x01, \
    0x02, 0x02, 0x01, 0x01, 0x01, \
    0x02, 0x01, 0x01, 0x00, 0x00, \
    0x01, 0x01, 0x02, 0x02, 0x04, \
    0x01, 0x01, 0x01, 0x02, 0x02, \
    0x01, 0x01, 0x01, 0x00, 0x00, \
    0x01, 0x01, 0x00, 0x00, 0x00, \
    0x01, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x0C, 0x03, 0x00, 0x02, \
    0x00, 0x06, 0x0F, 0x0F, 0x07, \
    0x00, 0x06, 0x0D, 0x31, 0xC1, \
    0x00, 0x01, 0x86, 0x98, 0x60, \
    0x00, 0x01, 0x01, 0x02, 0x04, \
    0x00, 0x01, 0x01, 0x02, 0x02, \
    0x00, 0x00, 0x80, 0x00, 0x00, \
    0x00, 0x00, 0x40, 0x80, 0x80, \
    0x00, 0x00, 0x1C, 0x32, 0xC4, \
    0x00, 0x00, 0x01, 0x02, 0x04, \
    0x00, 0x00, 0x01, 0x01, 0x01, \
    0x00, 0x00, 0x00, 0x80, 0x80, \
    0x00, 0x00, 0x00, 0x7E, 0x82, \
    0x00, 0x00, 0x00, 0x3F, 0xC1, \
    0x00, 0x00, 0x00, 0x00, 0x80, \
    0x00, 0x00, 0x00, 0x00, 0x01, \
    0x00, 0x00, 0x00, 0x00, 0x00, \
    0x40, 0x40, 0x80, 0x80, 0x00, \
    0x80, 0x80, 0x00, 0x00, 0x00, \
    0x80, 0x00, 0x00, 0x00, 0x00}; 

uint8_t bongo_line_x[] = {63, 48, 50, 57};
uint8_t bongo_line_y[] = {0, 8, 16, 24};
uint8_t bongo_line_len[] = {5, 10, 10, 9};

uint8_t bongo_line_data[8][34] = {
    { //idle1
    9, 23, 27, 37, 73, \
    69, 51, 42, 55, 70, 63, 16, 71, 45, 28, \
    2, 72, 72, 8, 15, 25, 32, 41, 18, 59, \
    38, 21, 20, 72, 72, 72, 72, 66, 72}, \
    { //idle2
    67, 13, 34, 36, 74, \
    69, 51, 42, 53, 72, 62, 12, 65, 39, 22, \
    4, 72, 72, 7, 14, 24, 32, 41, 18, 59, \
    38, 21, 20, 72, 72, 72, 72, 66, 72}, \
    { //idle3
    67, 10, 29, 30, 75, \
    68, 47, 33, 50, 72, 62, 12, 60, 39, 22, \
    4, 72, 72, 7, 14, 24, 32, 41, 18, 59, \
    38, 21, 20, 72, 72, 72, 72, 66, 72}, \
    { //idle4
    67, 10, 29, 30, 75, \
    64, 40, 33, 50, 70, 63, 16, 61, 40, 28, \
    2, 72, 72, 8, 15, 25, 32, 41, 18, 59, \
    38, 21, 20, 72, 72, 72, 72, 66, 72}, \
    { //idle5
    9, 23, 27, 37, 73, \
    58, 52, 46, 55, 70, 63, 16, 71, 45, 28, \
    2, 72, 72, 8, 15, 25, 32, 41, 18, 59, \
    38, 21, 20, 72, 72, 72, 72, 66, 72}, \
    { //prep
    67, 11, 29, 31, 73, \
    69, 51, 6, 53, 70, 63, 16, 71, 44, 3, \
    2, 56, 26, 8, 15, 25, 32, 42, 49, 55, \
    48, 54, 72, 72, 72, 72, 72, 72, 72}, \
    { //tap1
    67, 11, 29, 31, 73, \
    69, 51, 42, 53, 70, 63, 16, 71, 44, 3, \
    2, 72, 72, 8, 15, 25, 32, 42, 49, 55, \
    38, 21, 19, 5, 35, 72, 72, 72, 72}, \
    { //tap2
    67, 11, 29, 31, 73, \
    69, 51, 6, 53, 70, 63, 16, 71, 45, 28, \
    2, 56, 26, 8, 15, 25, 32, 41, 18, 59, \
    48, 54, 72, 72, 72, 57, 43, 1, 17}
};

enum anin_states { sleep, idle, prep, tap };
uint8_t anim_state = idle;
uint32_t idle_timeout_timer = 0;
uint32_t anim_timer = 0;
uint8_t current_idle_frame = 0;
uint8_t current_tap_frame = 6;

void write_bongochar_at_pixel_xy(uint8_t x, uint8_t y, const char data, bool invert) {
    uint8_t i, j, temp;
    uint8_t cast_data = (uint8_t)data-1;
    const uint8_t *glyph = &bongofont[cast_data * 5]; // 5 = font width
    temp = pgm_read_byte(glyph);
    for (i = 0; i < 5 ; i++) { // 5 = font width
        for (j = 0; j < 8; j++) {  // 8 = font height
            if (temp & 0x01) {
                oled_write_pixel(x + i, y + j, !invert);
            } else {
                oled_write_pixel(x + i, y + j, invert);
            }
            temp >>= 1;
        }
        temp = pgm_read_byte(++glyph);
    }
}

bool is_key_down(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] > 0) {
            return true;
        }
    }
    return false;
}

void eval_anim_state(void) {
    bool key_down;
    key_down = is_key_down();

    switch (anim_state) {
        case sleep:
            if(key_down) { anim_state = tap; }
            break; 
        case idle:
            if(key_down) { anim_state = tap; }
            else if (timer_elapsed32(idle_timeout_timer) >= SLEEP_TIMEOUT) //prep to idle
                {
                    anim_state = sleep;
                    current_idle_frame = 0;
                }
            break;
        case prep:
            if(key_down) { anim_state = tap; }
            else if (timer_elapsed32(idle_timeout_timer) >= IDLE_TIMEOUT) //prep to idle
                {
                    anim_state = idle;
                    current_idle_frame = 0;
                }
            break;
        case tap:
            if (!key_down)
            {
                anim_state = prep;
                idle_timeout_timer = timer_read32();
            }
            break;
        default:
            break;
    }
}

void draw_bongo_table(void) {
    //draws the table edge for bongocat, this edge doesn't change during the animation
    uint8_t i;
    for (i = 27; i < 128; i++) {
        oled_write_pixel(i, 32 - ((i - 27) >> 2), true); //every four horizontal pixels, move up one pixel to make a diagonal line
    }
}

void draw_bongocat_frame(int framenumber) {
    static uint8_t last_bongo_frame = 0;
    //only redraw if the animation frame has changed
    if (framenumber != last_bongo_frame) {
        last_bongo_frame = framenumber;
        uint8_t i, j, current_bongochar = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < bongo_line_len[i]; j++) {
                write_bongochar_at_pixel_xy(bongo_line_x[i] + j*5, bongo_line_y[i], bongo_line_data[framenumber][current_bongochar], false);
                current_bongochar++;
            }
        }
    }
}

void draw_bongocat(void) {
    static bool already_tapped = false;
    eval_anim_state();
    switch (anim_state) {
        case sleep:
            draw_bongocat_frame(4);
            break;
        case idle:
            draw_bongocat_frame(4 - current_idle_frame);
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                current_idle_frame = (current_idle_frame + 1) % 5;
                anim_timer = timer_read32();
            }
            break;
        case prep:
            draw_bongocat_frame(5);
            already_tapped = false;
            break;
        case tap:
            draw_bongocat_frame(current_tap_frame);
            if (already_tapped == false) {
                if (current_tap_frame == 6) {
                    current_tap_frame = 7;
                }
                else {
                    current_tap_frame = 6;
                }
            }
            already_tapped = true;
            break;
        default:
            draw_bongocat_frame(4);
            already_tapped = false;
            break;

    }
}

void blank_oled(void) {
    int i, j;
    for (i = 0; i < 32 ; i++) {
        for (j = 0; j < 128; j++) {
            oled_write_pixel(j, i, false);
        }
    }
}

void matrix_scan_kb(void) {
    blank_oled();
    draw_bongo_table();
    draw_bongocat();
}

#endif
