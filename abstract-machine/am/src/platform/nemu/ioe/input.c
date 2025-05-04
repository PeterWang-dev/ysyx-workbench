#include <am.h>
#include <klib.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint32_t am_scancode = inl(KBD_ADDR);
  bool is_keydown = (am_scancode & KEYDOWN_MASK) >> 15;
  kbd->keydown = is_keydown ? 1 : 0;
  kbd->keycode = is_keydown ? (am_scancode & ~KEYDOWN_MASK) : AM_KEY_NONE;
}
