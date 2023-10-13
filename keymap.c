/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

#include QMK_KEYBOARD_H

#define _BASE 0
#define _NUMBERS 1
#define _SYMBOLS 2
#define _ADJUST 3

enum {
    TD_SEMI,
    TD_SLSH,
    TD_SIPE,
    TD_NARR,
    TD_UNDS,
    TD_EQQU
};

enum custom_keycodes {
    M_ENHE = SAFE_RANGE,
    M_HARRW,
    M_EARRW
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case M_ENHE:
            if (record->event.pressed) {
                register_mods(MOD_LALT);
                tap_code(KC_N);
                unregister_mods(MOD_LALT);
                tap_code(KC_N);
            }
            break;
        case M_HARRW:
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            break;
        case M_EARRW:
            if (record->event.pressed) {
                SEND_STRING("=>");
            }
            break;
    }
    return true;
}

/* void n_harrw(tap_dance_state_t *state, void *user_data) { */
/*     switch (state->count) { */
/*         case 1: */
/*             tap_code16(KC_N); */
/*             break; */
/*         case 2: */
/*             tap_code16(KC_MINS); */
/*             tap_code16(KC_GT); */
/*             break; */
/*         case 3: */
/*             tap_code16(KC_EQL); */
/*             tap_code16(KC_GT); */
/*             break; */
/*     } */
/* }; */

tap_dance_action_t tap_dance_actions[] = {
    // [TD_SEMI] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN, KC_COLN),
    // [TD_SLSH] = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_BSLS),
    // [TD_SIPE] = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_PIPE),
    // [TD_UNDS] = ACTION_TAP_DANCE_DOUBLE(KC_COMM, KC_UNDS),
    // [TD_HYPN] = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_MINS)
    // [TD_EQQU] = ACTION_TAP_DANCE_DOUBLE(KC_I, KC_EQL),
};

#define KC_EURO LSFT(LALT(KC_2))
#define KC_CAPP LGUI(LSFT(KC_4))
#define KC_SLOK LGUI(LCTL(KC_Q))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
LCTL_T(KC_ESC),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          OSL(1),  KC_LGUI,  KC_SPC,     KC_ENT, OSM(MOD_RALT), OSL(2)
                                      //`--------------------------'  `--------------------------'

  ),

    [_NUMBERS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_TAB,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, KC_CAPP, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP,KC_RIGHT, KC_PMNS, KC_PPLS,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_SLOK, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME,  KC_END, KC_COMM,  KC_DOT, KC_UNDS, KC_CAPS,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, KC_LGUI,  KC_SPC,     KC_ENT, KC_RALT,  MO(3)
                                      //`--------------------------'  `--------------------------'
  ),

    [_SYMBOLS] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV, KC_EXLM,   KC_AT, KC_HASH,  KC_DLR, KC_PERC,                      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL, KC_MINS, KC_PLUS, M_HARRW, KC_EURO,  M_ENHE,                      KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT, KC_UNDS,  KC_EQL, M_EARRW, XXXXXXX, XXXXXXX,                      KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                            MO(3), KC_LGUI,  KC_SPC,     KC_ENT, KC_RALT, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [_ADJUST] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_VOLU, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, KC_BRIU,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, KC_BRID,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          KC_LGUI, _______,  KC_SPC,     KC_ENT, _______, KC_RALT
                                      //`--------------------------'  `--------------------------'
  )
};

const rgblight_segment_t PROGMEM layer_numbers[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_GREEN}
);
const rgblight_segment_t PROGMEM layer_symbols[] = RGBLIGHT_LAYER_SEGMENTS(
    {27, 7, HSV_BLUE}
);
const rgblight_segment_t PROGMEM layer_adjust[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 7, HSV_PURPLE},
    {27, 7, HSV_PURPLE}
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
        layer_numbers,
        layer_symbols,
        layer_adjust
);

void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers;
};

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _NUMBERS));
    rgblight_set_layer_state(1, layer_state_cmp(state, _SYMBOLS));
    rgblight_set_layer_state(2, layer_state_cmp(state, _ADJUST));
    return state;
};
