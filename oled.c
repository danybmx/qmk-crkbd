#include QMK_KEYBOARD_H
#include "keycodes.h"
#include "oled.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180; // flips the display 180 degrees if offhand
    }
    return rotation;
}

void oled_render_mod_status(void) {
    const uint8_t modifiers = get_mods() | get_oneshot_mods();
    for (uint8_t i = 0; i < 2; i++) {
        oled_set_cursor(15, i);
        oled_write_P(gui_icon[(modifiers & MOD_MASK_GUI) ? 1 : 0][i], false);
        oled_write_P(ctrl_icon[(modifiers & MOD_MASK_CTRL) ? 1 : 0][i], false);
        oled_set_cursor(15, i + 2);
        oled_write_P(alt_icon[(modifiers & MOD_MASK_ALT) ? 1 : 0][i], false);
        oled_write_P(shift_icon[(modifiers & MOD_MASK_SHIFT) || host_keyboard_led_state().caps_lock ? 1 : 0][i], false);
    }
}

void oled_render_led_state(void) {
    oled_write_P(PSTR("CAP"), host_keyboard_led_state().caps_lock);
    oled_advance_page(false);
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

static const char PROGMEM dp_logo[] = {
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0xC5, 0x00,
};

void oled_render_logo(void) {
    oled_write_P(dp_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_led_state();
        oled_render_keylog();
        oled_render_mod_status();
    } else {
        oled_render_logo();
        oled_scroll_right();
        oled_scroll_set_speed(4);
    }
    return false;
}
