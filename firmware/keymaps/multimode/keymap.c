// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#ifndef QK_RGBLIGHT_TOGGLE
#define QK_RGBLIGHT_TOGGLE        0x0A90
#define QK_RGBLIGHT_MODE_NEXT      0x0A91
#define QK_RGBLIGHT_INCREASE_VAL   0x0A92
#define QK_RGBLIGHT_DECREASE_VAL   0x0A93
#define QK_RGBLIGHT_INCREASE_HUE   0x0A94
#define QK_RGBLIGHT_INCREASE_SAT   0x0A95
#endif

#define RGB_TOG QK_RGBLIGHT_TOGGLE
#define RGB_MOD QK_RGBLIGHT_MODE_NEXT
#define RGB_VAI QK_RGBLIGHT_INCREASE_VAL
#define RGB_VAD QK_RGBLIGHT_DECREASE_VAL
#define RGB_HUI QK_RGBLIGHT_INCREASE_HUE
#define RGB_SAI QK_RGBLIGHT_INCREASE_SAT

#include QMK_KEYBOARD_H
#include "rgblight.h"

// Layers - modes
enum layers {
    _MEDIA,   // Default - system sound control
    _APP,     // App-specific shortcuts
    _RGB,     // RGB control
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_MEDIA] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },  // Volume down/up
    [_APP]   = { ENCODER_CCW_CW(KC_MPRV, KC_MNXT) },  // Prev/Next track
    [_RGB]   = { ENCODER_CCW_CW(RGB_VAD, RGB_VAI) },  // RGB brightness
};
#endif

// Keymaps 
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [_MEDIA] = LAYOUT(
        KC_MPLY,   KC_MSTP,             // Play/Pause,  Stop
        KC_MUTE,   MO(_APP),            // Mute, Hold -> App mode
        KC_VOLD,   KC_VOLU,   KC_MSEL  // Vol-, Vol+, Open media player
    ),

    [_APP] = LAYOUT(
        LCTL(LSFT(KC_M)),   LCTL(LSFT(KC_K)),    // Discord: Mute, Toggle Camera (Custom keybind Ctrl + Shift + K)
        KC_TRNS,   KC_TRNS,
        KC_TRNS,   KC_TRNS,   MO(_RGB) // Hold -> RGB mode
    ),

    [_RGB] = LAYOUT(
        RGB_TOG,   RGB_MOD,
        RGB_HUI,   KC_TRNS,
        RGB_SAI,   RGB_VAI,   KC_TRNS
    ),
};

// RGB mode color indicators
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _MEDIA:
            rgblight_setrgb(0, 100, 255);   // Blue for sound control
            break;
        case _APP:
            rgblight_setrgb(0, 255, 100);   // Green for apps
            break;
        case _RGB:
            rgblight_setrgb(255, 100, 0);   // Orange for LED control
            break;
    }
    return state;
}

// OLED display
#ifdef OLED_ENABLE

static void render_layer_status(void) {
    oled_write_P(PSTR("LAYER: "), false);
    switch (get_highest_layer(layer_state)) {
        case _MEDIA:
            oled_write_ln_P(PSTR("MEDIA"), false);
            break;
        case _APP:
            oled_write_ln_P(PSTR("APP  "), false);
            break;
        case _RGB:
            oled_write_ln_P(PSTR("RGB  "), false);
            break;
        default:
            oled_write_ln_P(PSTR("CRAZY SHOT BRO"), false);
    }
}

static void render_volume_bar(uint8_t vol) {
    oled_write_P(PSTR("VOL: "), false);
    // Simple ASCII bar (0–15 blocks)
    uint8_t filled = vol / 8;
    for (uint8_t i = 0; i < 16; i++) {
        oled_write_char(i < filled ? '#' : '-', false);
    }
    oled_write_ln_P(PSTR(""), false);
}

// Track simulated volume (because the pad can't know the real value)
static uint8_t sim_volume = 64;  // 0–127

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch (keycode) {
            case KC_VOLU:
                if (sim_volume < 120) sim_volume += 8;
                break;
            case KC_VOLD:
                if (sim_volume > 7)   sim_volume -= 8;
                break;
            case KC_MUTE:
                sim_volume = (sim_volume > 0) ? 0 : 64;
                break;
        }
    }
    return true;
}

bool oled_task_user(void) {
    oled_write_ln_P(PSTR("  SOUND CENTER  "), true);  // inverted header
    oled_write_ln_P(PSTR(""), false);
    render_layer_status();
    oled_write_ln_P(PSTR(""), false);
    render_volume_bar(sim_volume);
    oled_write_ln_P(PSTR("ENC: Vol / Track"), false);
    return false;
}

#endif // OLED_ENABLE
