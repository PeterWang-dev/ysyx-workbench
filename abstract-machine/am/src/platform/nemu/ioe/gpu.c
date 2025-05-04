#include <am.h>
#include <nemu.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

static int width = 0;
static int height = 0;
static int vmem_size = 0;
static uint32_t *fb = NULL;

void __am_gpu_init() {
  uint32_t screen_size = inl(VGACTL_ADDR);
  width = screen_size >> 16;
  height = screen_size & 0xffff;
  vmem_size = width * height * sizeof(uint32_t);
  fb = (uint32_t *)(uintptr_t)FB_ADDR;
  outl(SYNC_ADDR, 0);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  // dynamic resolution not supported as NEMU not support
  *cfg = (AM_GPU_CONFIG_T){.present = true,
                           .has_accel = false,
                           .width = width,
                           .height = height,
                           .vmemsz = vmem_size};
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  for (int y = 0; y < ctl->h; y++) {
    for (int x = 0; x < ctl->w; x++) {
      fb[(ctl->y + y) * width + ctl->x + x] =
          ((uint32_t *)ctl->pixels)[y * ctl->w + x];
    }
  }
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) { status->ready = true; }
