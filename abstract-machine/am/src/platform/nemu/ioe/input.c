#include <am.h>
#include <nemu.h>
#include <stdio.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  uint32_t am_scancode = inl(KBD_ADDR);
  printf("%d\n", (int)(am_scancode & KEYDOWN_MASK));
  bool is_keydown = (am_scancode & KEYDOWN_MASK) ? true : false;
  kbd->keydown = is_keydown ? 1 : 0;
  kbd->keycode = is_keydown ? (am_scancode & ~KEYDOWN_MASK) : AM_KEY_NONE;
}
