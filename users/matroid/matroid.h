enum {
    LAYER_NORM_BASE,
    LAYER_NORM_EXTENSION,
    LAYER_RACE_BASE,
    LAYER_RACE_EXTENSION,
    LAYER_LEGACY_BASE,
    LAYER_LEGACY_EXTENSION,
    LAYER_CONTROL,
    LAYER_WINDOW,
    LAYER_DESKTOP,
    NUMBER_OF_LAYERS,
};

bool temporary[NUMBER_OF_LAYERS] = {
    [LAYER_NORM_BASE] = false,
    [LAYER_NORM_EXTENSION] = true,
    [LAYER_RACE_BASE] = false,
    [LAYER_RACE_EXTENSION] = true,
    [LAYER_LEGACY_BASE] = false,
    [LAYER_LEGACY_EXTENSION] = true,
    [LAYER_CONTROL] = false,
    [LAYER_WINDOW] = true,
    [LAYER_DESKTOP] = false,
};

#define KEY_FORWARD_LAYER(a) SAFE_RANGE + a

enum{
    DANCE_PGDN_BOTTOM,
    DANCE_PGUP_TOP,
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [DANCE_PGDN_BOTTOM] = ACTION_TAP_DANCE_DOUBLE(KC_PGDN, LGUI(KC_DOWN)),
    [DANCE_PGUP_TOP] = ACTION_TAP_DANCE_DOUBLE(KC_PGUP, LGUI(KC_UP)),
};

#define KEY_DANCE(a) TD(a)

enum custom_keycodes {
    KEY_BACK_LAYER = SAFE_RANGE + NUMBER_OF_LAYERS,
    KEY_INSERT_LINE_START,
    KEY_INSERT_HERE,
    KEY_INSERT_LINE_END,
    KEY_CREATE_PREVIOUS_LINE,
    KEY_CREATE_NEXT_LINE,
    KEY_DELETE_WORD,
    KEY_DELETE_LINE,
    KEY_CUT_WORD,
    KEY_CUT_LINE,
    KEY_CUT_SELECTION,
};

int layers[16];

struct {
    bool back;
} common_layer_data;
struct {
    int operator, multiplier;
} layer_control_data;

struct {
    int start_time;
} layer_window_data;

bool handle_layer_key(uint16_t key, keyrecord_t* record) {
    switch (layers[layers[0] + 1]) {
        case LAYER_CONTROL:
            switch (key) {
                case KC_0:
                    if (record->event.pressed) {
                        layer_control_data.multiplier = layer_control_data.multiplier * 10;
                        if (layer_control_data.multiplier < 0) layer_control_data.multiplier = 0;
                    }
                    return false;
                case KC_1:
                    if (record->event.pressed) {
                        layer_control_data.multiplier = layer_control_data.multiplier * 10 + 1;
                        if (layer_control_data.multiplier < 0) layer_control_data.multiplier = 0;
                    }
                    return false;
                case KC_2:
                    if (record->event.pressed) {
                        layer_control_data.multiplier = layer_control_data.multiplier * 10 + 2;
                        if (layer_control_data.multiplier < 0) layer_control_data.multiplier = 0;
                    }
                    return false;
                case KC_3:
                    if (record->event.pressed) {
                        layer_control_data.multiplier = layer_control_data.multiplier * 10 + 3;
                        if (layer_control_data.multiplier < 0) layer_control_data.multiplier = 0;
                    }
                    return false;
                case KC_4:
                    if (record->event.pressed) {
                        layer_control_data.multiplier = layer_control_data.multiplier * 10 + 4;
                        if (layer_control_data.multiplier < 0) layer_control_data.multiplier = 0;
                    }
                    return false;
                case KC_5:
                    if (record->event.pressed) {
                        layer_control_data.multiplier = layer_control_data.multiplier * 10 + 5;
                        if (layer_control_data.multiplier < 0) layer_control_data.multiplier = 0;
                    }
                    return false;
                case KC_6:
                    if (record->event.pressed) {
                        layer_control_data.multiplier = layer_control_data.multiplier * 10 + 6;
                        if (layer_control_data.multiplier < 0) layer_control_data.multiplier = 0;
                    }
                    return false;
                case KC_7:
                    if (record->event.pressed) {
                        layer_control_data.multiplier = layer_control_data.multiplier * 10 + 7;
                        if (layer_control_data.multiplier < 0) layer_control_data.multiplier = 0;
                    }
                    return false;
                case KC_8:
                    if (record->event.pressed) {
                        layer_control_data.multiplier = layer_control_data.multiplier * 10 + 8;
                        if (layer_control_data.multiplier < 0) layer_control_data.multiplier = 0;
                    }
                    return false;
                case KC_9:
                    if (record->event.pressed) {
                        layer_control_data.multiplier = layer_control_data.multiplier * 10 + 9;
                        if (layer_control_data.multiplier < 0) layer_control_data.multiplier = 0;
                    }
                    return false;
                case KEY_INSERT_LINE_START:
                    if (record->event.pressed) common_layer_data.back = true;
                    return true;
                case KEY_INSERT_HERE:
                    if (record->event.pressed) common_layer_data.back = true;
                    return true;
                case KEY_INSERT_LINE_END:
                    if (record->event.pressed) common_layer_data.back = true;
                    return true;
                case KEY_CREATE_PREVIOUS_LINE:
                    if (record->event.pressed) common_layer_data.back = true;
                    return true;
                case KEY_CUT_WORD:
                    if (record->event.pressed) {
                        if (layer_control_data.operator== - 1) {
                            register_code(KC_LALT);
                            tap_code(KC_LEFT);
                            tap_code(KC_RIGHT);
                            unregister_code(KC_LALT);
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(LALT(KC_LEFT)));
                            tap_code16(LGUI(KC_X));
                        }
                        layer_control_data.multiplier = 0;
                        layer_control_data.operator   = - 1;
                    }
                    return false;
                case LALT(KC_LEFT):
                    if (layer_control_data.operator== - 1 && layer_control_data.multiplier == 0) return true;
                    if (record->event.pressed) {
                        if (layer_control_data.operator== - 1)
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LALT(KC_LEFT));
                        else if (layer_control_data.operator== KC_BSPC) {
                            register_code(KC_LALT);
                            tap_code(KC_LEFT);
                            tap_code(KC_RIGHT);
                            unregister_code(KC_LALT);
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(LALT(KC_LEFT)));
                            tap_code16(LGUI(KC_X));
                        } else if (layer_control_data.operator== LGUI(KC_C)) {
                            register_code(KC_LALT);
                            tap_code(KC_LEFT);
                            tap_code(KC_RIGHT);
                            unregister_code(KC_LALT);
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(LALT(KC_LEFT)));
                            tap_code16(LGUI(KC_C));
                            tap_code(KC_RIGHT);
                        }
                        layer_control_data.multiplier = 0;
                        layer_control_data.operator   = - 1;
                    }
                    return false;
                case LALT(KC_RIGHT):
                    if (layer_control_data.operator== - 1 && layer_control_data.multiplier == 0) return true;
                    if (record->event.pressed) {
                        if (layer_control_data.operator== - 1)
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LALT(KC_RIGHT));
                        else if (layer_control_data.operator== KC_BSPC) {
                            register_code(KC_LALT);
                            tap_code(KC_RIGHT);
                            tap_code(KC_LEFT);
                            unregister_code(KC_LALT);
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(LALT(KC_RIGHT)));
                            tap_code16(LGUI(KC_X));
                        } else if (layer_control_data.operator== LGUI(KC_C)) {
                            register_code(KC_LALT);
                            tap_code(KC_RIGHT);
                            tap_code(KC_LEFT);
                            unregister_code(KC_LALT);
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(LALT(KC_RIGHT)));
                            tap_code16(LGUI(KC_C));
                            tap_code(KC_LEFT);
                        }
                        layer_control_data.multiplier = 0;
                        layer_control_data.operator   = - 1;
                    }
                    return false;
                case LGUI(KC_LEFT):
                    if (record->event.pressed) {
                        if (layer_control_data.operator== - 1)
                            tap_code16(LGUI(KC_LEFT));
                        else if (layer_control_data.operator== KC_BSPC) {
                            tap_code16(LSFT(LGUI(KC_LEFT)));
                            tap_code16(LGUI(KC_X));
                        } else if (layer_control_data.operator== LGUI(KC_C)) {
                            tap_code16(LSFT(LGUI(KC_LEFT)));
                            tap_code16(LGUI(KC_C));
                            tap_code(KC_RIGHT);
                        }
                        layer_control_data.multiplier = 0;
                        layer_control_data.operator   = - 1;
                    }
                    return false;
                case LCTL(KC_E):
                    if (record->event.pressed) {
                        if (layer_control_data.operator== - 1)
                            tap_code16(LCTL(KC_E));
                        else if (layer_control_data.operator== KC_BSPC) {
                            tap_code16(LSFT(LCTL(KC_E)));
                            tap_code16(LGUI(KC_X));
                        } else if (layer_control_data.operator== LGUI(KC_C)) {
                            tap_code16(LSFT(LCTL(KC_E)));
                            tap_code16(LGUI(KC_C));
                            tap_code(KC_LEFT);
                        }
                        layer_control_data.multiplier = 0;
                        layer_control_data.operator   = - 1;
                    }
                    return false;
                case KC_BSPC:
                    if (record->event.pressed) {
                        if (get_mods() & MOD_MASK_SHIFT) {
                            unregister_code(KC_LSHIFT);
                            tap_code16(LGUI(KC_X));
                            register_code(KC_LSHIFT);
                            layer_control_data.multiplier = 0;
                            layer_control_data.operator   = - 1;
                        } else if (layer_control_data.operator== - 1)
                            layer_control_data.operator= KC_BSPC;
                        else {
                            if (layer_control_data.operator== KC_BSPC) {
                                tap_code16(LCTL(KC_A));
                                for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(KC_DOWN));
                                tap_code16(LGUI(KC_X));
                            }
                            layer_control_data.multiplier = 0;
                            layer_control_data.operator   = - 1;
                        }
                    }
                    return false;
                case KC_LEFT:
                    if (layer_control_data.operator== - 1 && layer_control_data.multiplier == 0) return true;
                    if (record->event.pressed) {
                        if (layer_control_data.operator== - 1)
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code(KC_LEFT);
                        else if (layer_control_data.operator== KC_BSPC) {
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(KC_LEFT));
                            tap_code16(LGUI(KC_X));
                        } else if (layer_control_data.operator== LGUI(KC_C)) {
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(KC_LEFT));
                            tap_code16(LGUI(KC_C));
                            tap_code(KC_RIGHT);
                        }
                        layer_control_data.multiplier = 0;
                        layer_control_data.operator   = - 1;
                    }
                    return false;
                case KC_DOWN:
                    if (layer_control_data.operator== - 1 && layer_control_data.multiplier == 0) return true;
                    if (record->event.pressed) {
                        if (layer_control_data.operator== - 1)
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code(KC_DOWN);
                        else if (layer_control_data.operator== KC_BSPC) {
                            tap_code16(LCTL(KC_A));
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(KC_DOWN));
                            tap_code16(LGUI(KC_X));
                        } else if (layer_control_data.operator== LGUI(KC_C)) {
                            tap_code16(LCTL(KC_A));
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(KC_DOWN));
                            tap_code16(LGUI(KC_C));
                            tap_code(KC_LEFT);
                        }
                        layer_control_data.multiplier = 0;
                        layer_control_data.operator   = - 1;
                    }
                    return false;
                case KC_UP:
                    if (layer_control_data.operator== - 1 && layer_control_data.multiplier == 0) return true;
                    if (record->event.pressed) {
                        if (layer_control_data.operator== - 1)
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code(KC_UP);
                        else if (layer_control_data.operator== KC_BSPC) {
                            tap_code16(LCTL(KC_E));
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(KC_UP));
                            tap_code16(LSFT(LCTL(KC_E)));
                            tap_code16(LGUI(KC_X));
                        } else if (layer_control_data.operator== LGUI(KC_C)) {
                            tap_code16(LCTL(KC_E));
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(KC_UP));
                            tap_code16(LSFT(LCTL(KC_E)));
                            tap_code16(LGUI(KC_C));
                            tap_code(KC_RIGHT);
                        }
                        layer_control_data.multiplier = 0;
                        layer_control_data.operator   = - 1;
                    }
                    return false;
                case KC_RIGHT:
                    if (layer_control_data.operator== - 1 && layer_control_data.multiplier == 0) return true;
                    if (record->event.pressed) {
                        if (layer_control_data.operator== - 1)
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code(KC_RIGHT);
                        else if (layer_control_data.operator== KC_BSPC) {
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(KC_RIGHT));
                            tap_code16(LGUI(KC_X));
                        } else if (layer_control_data.operator== LGUI(KC_C)) {
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(KC_RIGHT));
                            tap_code16(LGUI(KC_C));
                            tap_code(KC_LEFT);
                        }
                        layer_control_data.multiplier = 0;
                        layer_control_data.operator   = - 1;
                    }
                    return false;
                case KEY_CREATE_NEXT_LINE:
                    if (record->event.pressed) common_layer_data.back = true;
                    return true;
                case LGUI(KC_Z):
                    if (layer_control_data.operator== - 1 && layer_control_data.multiplier == 0) return true;
                    if (record->event.pressed) {
                        if (layer_control_data.operator== - 1)
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LGUI(KC_Z));
                        layer_control_data.multiplier = 0;
                        layer_control_data.operator   = - 1;
                    }
                    return false;
                case LGUI(KC_C):
                    if (record->event.pressed) {
                        if (get_mods() & MOD_MASK_SHIFT) {
                            unregister_code(KC_LSHIFT);
                            tap_code16(LGUI(KC_C));
                            register_code(KC_LSHIFT);
                            layer_control_data.multiplier = 0;
                            layer_control_data.operator   = - 1;
                        } else if (layer_control_data.operator== - 1)
                            layer_control_data.operator= LGUI(KC_C);
                        else {
                            if (layer_control_data.operator== LGUI(KC_C)) {
                                tap_code16(LCTL(KC_A));
                                for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LSFT(KC_DOWN));
                                tap_code16(LGUI(KC_C));
                                tap_code(KC_LEFT);
                            }
                            layer_control_data.multiplier = 0;
                            layer_control_data.operator   = - 1;
                        }
                    }
                    return false;
                case LGUI(KC_V):
                    if (record->event.pressed) {
                        if (get_mods() & MOD_MASK_SHIFT) {
                            unregister_code(KC_LSHIFT);
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LGUI(KC_V));
                            register_code(KC_LSHIFT);
                            layer_control_data.multiplier = 0;
                            layer_control_data.operator   = - 1;
                        } else {
                            for (int i = 0; i < (layer_control_data.multiplier ? layer_control_data.multiplier : 1); ++i) tap_code16(LGUI(KC_V));
                            layer_control_data.multiplier = 0;
                            layer_control_data.operator   = - 1;
                        }
                    }
                    return false;
            }
            layer_control_data.multiplier = 0;
            layer_control_data.operator   = - 1;
            return true;
        case LAYER_WINDOW:
            switch (key) {
                case SAFE_RANGE + LAYER_WINDOW:
                    if (!record->event.pressed) {
                        if (timer_elapsed(layer_window_data.start_time) < 200)
                            temporary[LAYER_WINDOW] = true;
                        else
                            temporary[LAYER_WINDOW] = false;
                    }
                    return true;
                case KEY_BACK_LAYER:
                    if (record->event.pressed) tap_code(KC_ENTER);
                    return true;
            }
            return true;
        case LAYER_DESKTOP:
            switch (key) {
                case KEY_BACK_LAYER:
                    if (record->event.pressed) tap_code16(LCTL(KC_UP));
                    return true;
            }
            return true;
    }
    return true;
}

void handle_layer_start(void) {
    rgblight_disable_noeeprom();
    switch (layers[layers[0] + 1]) {
        case LAYER_RACE_BASE:
            tap_code16(LGUI(KC_SPACE));
            SEND_STRING("25005380");
            tap_code(KC_ENT);
        case LAYER_RACE_EXTENSION:
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_BLUE);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            return;
        case LAYER_LEGACY_BASE:
        case LAYER_LEGACY_EXTENSION:
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_GREEN);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            return;
        case LAYER_CONTROL:
            layer_control_data.operator   = - 1;
            layer_control_data.multiplier = 0;
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_RED);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            return;
        case LAYER_WINDOW:
            register_code(KC_LGUI);
            tap_code(KC_TAB);
            layer_window_data.start_time = timer_read();
            return;
        case LAYER_DESKTOP:
            tap_code16(LCTL(KC_UP));
            return;
    }
}

void handle_layer_return(void) {
    rgblight_disable_noeeprom();
    switch (layers[layers[0] + 1]) {
        case LAYER_RACE_BASE:
        case LAYER_RACE_EXTENSION:
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_GREEN);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            return;
        case LAYER_LEGACY_BASE:
        case LAYER_LEGACY_EXTENSION:
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_RED);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            return;
        case LAYER_CONTROL:
            layer_control_data.operator   = - 1;
            layer_control_data.multiplier = 0;
            rgblight_enable_noeeprom();
            rgblight_sethsv_noeeprom(HSV_BLUE);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
            return;
    }
}

void handle_layer_end(void) {
    switch (layers[layers[0] + 1]) {
        case LAYER_WINDOW:
            unregister_code(KC_LGUI);
            return;
    }
}

void update_layer(void) {
    layer_clear();
    common_layer_data.back = false;
    layer_on(layers[layers[0] + 1]);
}

bool handle_call_key(uint16_t key, keyrecord_t* record) {
    switch (key) {
        case KEY_BACK_LAYER:
            if (record->event.pressed) {
                if (layers[0]) {
                    handle_layer_end();
                    --layers[0];
                    update_layer();
                    handle_layer_return();
                }
            }
            return false;
    }
    if (key >= SAFE_RANGE && key < SAFE_RANGE + NUMBER_OF_LAYERS) {
        int new_layer = key - SAFE_RANGE;
        if (record->event.pressed) {
            if (layers[layers[0] + 1] != new_layer) {
                if (temporary[layers[layers[0] + 1]]) {
                    handle_layer_end();
                    layers[layers[0] + 1] = new_layer;
                } else
                    layers[++layers[0] + 1] = new_layer;
                update_layer();
                handle_layer_start();
            }
        } else {
            if (layers[layers[0] + 1] == new_layer && temporary[layers[layers[0] + 1]]) {
                handle_layer_end();
                --layers[0];
                update_layer();
                handle_layer_return();
            }
        }
        return false;
    }
    if (common_layer_data.back) {
        if (layers[0]) {
            handle_layer_end();
            --layers[0];
            update_layer();
            handle_layer_return();
        }
    }
    return true;
}

bool handle_common_key(uint16_t key, keyrecord_t* record) {
    switch (key) {
        case KC_0:
            if (record->event.pressed && get_mods() & MOD_MASK_SHIFT) tap_code16(LGUI(LSFT(KC_4)));
            return false;
        case KC_1:
            if (record->event.pressed && get_mods() & MOD_MASK_SHIFT) tap_code16(KC_AT);
            return false;
        case KC_2:
            if (record->event.pressed && get_mods() & MOD_MASK_SHIFT) tap_code16(KC_TILD);
            return false;
        case KEY_INSERT_LINE_START:
            if (record->event.pressed) tap_code16(LGUI(KC_LEFT));
            return false;
        case KEY_INSERT_HERE:
            return false;
        case KEY_INSERT_LINE_END:
            if (record->event.pressed) tap_code16(LGUI(KC_RIGHT));
            return false;
        case KEY_CREATE_PREVIOUS_LINE:
            if (record->event.pressed) {
                tap_code16(LGUI(KC_LEFT));
                tap_code(KC_ENTER);
                tap_code(KC_UP);
            }
            return false;
        case KEY_CREATE_NEXT_LINE:
            if (record->event.pressed) {
                tap_code16(LGUI(KC_RIGHT));
                tap_code(KC_ENTER);
            }
            return false;
        case KEY_DELETE_WORD:
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_LEFT);
                tap_code(KC_RIGHT);
                unregister_code(KC_LALT);
                tap_code16(LSFT(LALT(KC_LEFT)));
                tap_code(KC_BSPC);
            }
            return false;
        case KEY_DELETE_LINE:
            if (record->event.pressed) {
                tap_code16(LGUI(KC_RIGHT));
                tap_code16(LSFT(LGUI(KC_LEFT)));
                tap_code(KC_BSPC);
            }
            return false;
        case KEY_CUT_WORD:
            if (record->event.pressed) {
                register_code(KC_LALT);
                tap_code(KC_LEFT);
                tap_code(KC_RIGHT);
                unregister_code(KC_LALT);
                tap_code16(LSFT(LALT(KC_LEFT)));
                tap_code16(LGUI(KC_X));
            }
            return false;
        case KEY_CUT_LINE:
            if (record->event.pressed) {
                tap_code16(LGUI(KC_RIGHT));
                tap_code16(LSFT(LGUI(KC_LEFT)));
                tap_code16(LGUI(KC_X));
            }
            return false;
        case KEY_CUT_SELECTION:
            if (record->event.pressed) {
                if (get_mods() & MOD_MASK_SHIFT) {
                    unregister_code(KC_LSHIFT);
                    tap_code16(LGUI(KC_X));
                    register_code(KC_LSHIFT);
                } else
                    tap_code16(LGUI(KC_X));
            }
            return false;
    }
    return true;
}

bool process_record_user(uint16_t key, keyrecord_t* record) {
    if (!handle_layer_key(key, record)) return false;
    if (!handle_call_key(key, record)) return false;
    return handle_common_key(key, record);
}

void keyboard_post_init_user() {
    rgblight_disable_noeeprom();
    rgb_matrix_disable();
    common_layer_data.back = false;
}
