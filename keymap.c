#include QMK_KEYBOARD_H

enum my_layers {
  BASE_LAYER,
  SYM_LAYER,
  NAV_LAYER,
  NUM_LAYER,
  SCUT_LAYER
};

enum my_keycodes {
    M_ALTT = SAFE_RANGE,
    M_APP1,
    M_APP2,
    M_APP3,
    M_APP4,
    M_APP5,
    M_LIKE,
    M_1PASS,
    M_HIDE,
    M_MAX,
    M_CLOSE,
    M_NDESK,
    M_PDESK,
    M_NTRM,
    M_EMOJI,
    M_ISCROS,
    M_ISWIN
};

// Stores state of M_ALTT macro - true if we are currently tabbing between
// windows.
static bool m_altt_pressed = false;

// Toggle for keys that affect the the desktop - value can be changed in
// function layer
static bool m_is_chromebook = false;

// Used to temporarily store the state of the mod keys.
static uint8_t mod_state = 0;

// State for managing shift backspace behaviour.
static bool kc_del_registered = false;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE_LAYER] = LAYOUT_split_3x5_2(
    KC_Q,          LCTL_T(KC_W),           LALT_T(KC_F),           LGUI_T(KC_P),   KC_B,  KC_J,  LGUI_T(KC_L),  LALT_T(KC_U),  LCTL_T(KC_Y),  KC_BSPC,
    KC_A,          KC_R,                   KC_S,                   KC_T,           KC_G,  KC_M,  KC_N,          KC_E,          KC_I,          KC_O,
    KC_Z,          KC_X,                   KC_C,                   KC_D,           KC_V,  KC_K,  KC_H,          KC_COMM,       KC_DOT,        KC_SLSH,
    OSM(MOD_LSFT),  LT(NAV_LAYER, KC_SPC),  LT(NUM_LAYER, KC_ENT),  OSL(SYM_LAYER)
  ),

  [SYM_LAYER] = LAYOUT_split_3x5_2(
    KC_EXLM,  LSFT(KC_2),     LSFT(KC_3),  KC_DLR,   KC_PERC,  KC_CIRC,  KC_AMPR,        KC_ASTR,        KC_NO,    KC_NO,
    KC_GRV,   LSFT(KC_NUBS),  KC_LBRC,     KC_LCBR,  KC_LPRN,  KC_COLN,  LSFT(KC_QUOT),  LSFT(KC_BSLS),  KC_UNDS,  KC_PLUS,
    KC_CAPS,  KC_NUBS,        KC_RBRC,     KC_RCBR,  KC_RPRN,  KC_SCLN,  KC_QUOT,        KC_BSLS,        KC_MINS,  KC_EQL,
    KC_TRNS,  KC_TRNS,        KC_TRNS,     KC_TRNS
  ),

  [NAV_LAYER] = LAYOUT_split_3x5_2(
    KC_PSCR,  KC_MNXT,     KC_MPLY,     KC_VOLU,           KC_BRIU,     KC_NO,    M_PDESK,  LCTL(KC_TAB),  M_ALTT,   M_NDESK,
    KC_NO,   KC_MPRV,     KC_MUTE,     KC_VOLD,           KC_BRID,     KC_WH_U,  KC_LEFT,  KC_DOWN,       KC_UP,    KC_RGHT,
    KC_NO,  LCTL(KC_X),  LCTL(KC_C),  LSFT(LCTL(KC_C)),  LCTL(KC_V),  KC_WH_D,  KC_HOME,  KC_PGDN,       KC_PGUP,  KC_END,
    KC_TRNS,  KC_TRNS,     KC_ESC,      OSL(SCUT_LAYER)
  ),

  [NUM_LAYER] = LAYOUT_split_3x5_2(
    KC_PAST,  KC_1,    KC_2,     KC_3,    KC_PPLS,  KC_NO,  KC_F1,  KC_F2,  KC_F3,  KC_BSPC,
    KC_PSLS,  KC_4,    KC_5,     KC_6,    KC_PMNS,  KC_NO,  KC_F4,  KC_F5,  KC_F6,  KC_NO,
    KC_0,     KC_7,    KC_8,     KC_9,    KC_DOT,   KC_NO,  KC_F7,  KC_F8,  KC_F9,  KC_F10,
    CW_TOGG,  KC_TAB,  KC_TRNS,  KC_TRNS
  ),

  [SCUT_LAYER] = LAYOUT_split_3x5_2(
    KC_NO,    M_NTRM,   KC_NO,    KC_NO,    M_LIKE,  KC_NO,  M_HIDE,  M_MAX,    M_CLOSE,  KC_NO,
    M_APP1,   M_APP2,   M_APP3,   M_APP4,   M_APP5,  KC_NO,  KC_NO,   M_EMOJI,  KC_NO,    M_ISWIN,
    KC_NO,    KC_NO,    KC_NO,    M_1PASS,  KC_NO,   KC_NO,  KC_NO,   KC_NO,    KC_NO,    M_ISCROS,
    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

  // Stop pressing the alt key once a key other than the alt-tab macro has been
  // pressed.
  if (keycode != M_ALTT && m_altt_pressed) {
    unregister_code(KC_LALT);
    m_altt_pressed = false;
  }

  mod_state = get_mods();

  switch (keycode) {
    // Shift-backspace produces delete.
    case KC_BSPC:
      if (record->event.pressed) {
        if (mod_state & MOD_MASK_SHIFT) {
          del_mods(MOD_MASK_SHIFT);
          register_code(KC_DEL);
          kc_del_registered = true;
          set_mods(mod_state);
          return false;
        }
      } else {
        if (kc_del_registered) {
          unregister_code(KC_DEL);
          kc_del_registered = false;
          return false;
        }
      }
      break;
    case M_ALTT:
      if (record->event.pressed) {
        if (!m_altt_pressed) {
          register_code(KC_LALT);
          m_altt_pressed = true;
        }
        tap_code(KC_TAB);
      }
      break;
    case M_APP1:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_1));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_1));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP2:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_2));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_2));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP3:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_3));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_3));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP4:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_4));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_4));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_APP5:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_5));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_5));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_LIKE:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_5)SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_5));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
        SEND_STRING(SS_DELAY(100));
        SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LALT));
        SEND_STRING(SS_TAP(X_B));
        SEND_STRING(SS_UP(X_LALT)SS_UP(X_LSFT));
      }
      break;
    case M_1PASS:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT)SS_TAP(X_1)SS_UP(X_LALT));
          SEND_STRING(SS_DELAY(100));
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL));
          SEND_STRING(SS_TAP(X_X));
          SEND_STRING(SS_UP(X_LCTL)SS_UP(X_LSFT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL));
          SEND_STRING(SS_TAP(X_SPC));
          SEND_STRING(SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_HIDE:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_MINS));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_M));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_MAX:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LALT));
          SEND_STRING(SS_TAP(X_EQL));
          SEND_STRING(SS_UP(X_LALT));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_A));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_CLOSE:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LSFT));
          SEND_STRING(SS_TAP(X_W));
          SEND_STRING(SS_UP(X_LSFT)SS_UP(X_LCTL));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_K));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LALT)SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_NDESK:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_RBRC));
          SEND_STRING(SS_UP(X_LGUI));
        } else {
          SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_RGHT));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LCTL));
        }
      }
      break;
    case M_PDESK:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_LBRC));
          SEND_STRING(SS_UP(X_LGUI));
        } else {
          SEND_STRING(SS_DOWN(X_LCTL)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_LEFT));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LCTL));
        }
      }
      break;
    case M_NTRM:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LCTL)SS_TAP(X_T)SS_UP(X_LCTL));
        } else {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LCTL));
          SEND_STRING(SS_TAP(X_1));
          SEND_STRING(SS_UP(X_LCTL)SS_UP(X_LSFT));
        }
      }
      break;
    case M_EMOJI:
      if (record->event.pressed) {
        if (m_is_chromebook) {
          SEND_STRING(SS_DOWN(X_LSFT)SS_DOWN(X_LGUI));
          SEND_STRING(SS_TAP(X_SPC));
          SEND_STRING(SS_UP(X_LGUI)SS_UP(X_LSFT));
        } else {
          SEND_STRING(SS_DOWN(X_LGUI)SS_TAP(X_SCLN)SS_UP(X_LGUI));
        }
      }
      break;
    case M_ISCROS:
      if (record->event.pressed) {
        m_is_chromebook = true;
      }
      break;
    case M_ISWIN:
      if (record->event.pressed) {
        m_is_chromebook = false;
      }
      break;
  }

  return true;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // Set the tapping term for the homerow mods.
    case LCTL_T(KC_W):
    case LALT_T(KC_F):
    case LGUI_T(KC_P):
    case LGUI_T(KC_L):
    case LALT_T(KC_U):
    case LCTL_T(KC_Y):
      return TAPPING_TERM_MODS;
    default:
      return TAPPING_TERM;
  }
}

bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    // Keycodes that continue caps word with shift applied.
    case KC_A ... KC_Z:
      // Apply shift to next key.
      add_weak_mods(MOD_BIT(KC_LSFT));
      return true;
    // Keycodes that continue caps word without shifting.
    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_DEL:
    case KC_UNDS:
      return true;
    // Deactivate caps word by default.
    default:
      return false;
  }
}
