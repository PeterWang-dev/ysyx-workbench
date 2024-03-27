/*******************************************************************************
 * Copyright (c) 2023-2024 PeterWang-dev (https://github.com/PeterWang-dev)
 *
 * NEMU is licensed under Mulan PSL v2.
 * You can use this software according to the terms and conditions of the Mulan
 * PSL v2. You may obtain a copy of Mulan PSL v2 at:
 *          http://license.coscl.org.cn/MulanPSL2
 *
 * THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY
 * KIND, EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
 * NON-INFRINGEMENT, MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
 *
 * See the Mulan PSL v2 for more details.
 ******************************************************************************/
#include "utils.h"

void ringbuf_init(RingBuf *rb) {
  rb->head = 0;
  rb->tail = 0; // empty, tail always points to the next empty slot
}

void ringbuf_push(RingBuf *rb, const char *str) {
  int head = rb->head;
  int tail = rb->tail;
  char *buf = rb->buf[tail];

  snprintf(buf, 128, "%s", str);

  rb->tail = (tail + 1) % RINGBUF_SIZE;
  if (rb->tail == head) { // move head forward to discard oldest log
    rb->head = (head + 1) % RINGBUF_SIZE;
  }
}

char *ringbuf_pop(RingBuf *rb, char *buf) {
  int head = rb->head;
  int tail = rb->tail;

  if (head == tail) {
    return NULL;
  }

  snprintf(buf, 128, "%s", rb->buf[head]);
  rb->head = (head + 1) % RINGBUF_SIZE;

  return buf;
}

char *ringbuf_iter(RingBuf *rb) {
  static int pos = -1;

  // init iterator
  if (pos == -1) {
    pos = rb->head;
  }

  // end of iteration
  if (pos == rb->tail) {
    pos = -1; // reset iterator
    return NULL;
  }

  return rb->buf[pos];
}
