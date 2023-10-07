#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "oled.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}


void oled_render_mod_status(void) {
    const uint8_t modifiers = get_mods() | get_oneshot_mods();
    for (uint8_t i = 0; i < 2; i++) {
        oled_set_cursor(15,i);
        oled_write_P(gui_icon[(modifiers & MOD_MASK_GUI) ? 1 : 0][i], false);
        oled_write_P(ctrl_icon[(modifiers & MOD_MASK_CTRL) ? 1 : 0][i], false);
        oled_set_cursor(15,i+2);
        oled_write_P(alt_icon[(modifiers & MOD_MASK_ALT) ? 1 : 0][i], false);
        oled_write_P(shift_icon[(modifiers & MOD_MASK_SHIFT) ? 1 : 0][i], false);
    }
}

uint8_t last_row = 0;
uint8_t last_col = 0;

void set_keylog(uint16_t keycode, keyrecord_t *record) {
  last_row = record->event.key.row;
  last_col = record->event.key.col;
}

void oled_render_keylog(void) {
    oled_write_char(last_row + '0', false);
    oled_write_char('x', false);
    oled_write_char(last_col + '0', false);
}

void oled_render_logo(void) {
    static const char PROGMEM dp_logo[][3] = {
        {0x82, 0x83, 0},
        {0x80, 0x81, 0},
        {0xa0, 0xa1, 0},
        {0xc0, 0xc1, 0}
    };
    for (uint8_t i = 0; i < 4; i++) {
        oled_write_ln_P(dp_logo[i], false);
    }
}

bool oled_task_user(void) {
    if (is_keyboard_master ()) {
        oled_render_keylog();
        oled_render_mod_status();
    } else {
        oled_render_logo();
        oled_scroll_right();
        oled_scroll_set_speed(4);
    }
    return false;
}
