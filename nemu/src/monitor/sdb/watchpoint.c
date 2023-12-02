/*******************************************************************************
 * Copyright (c) 2014-2022 Zihao Yu, Nanjing University
 *               2023-2024 PeterWang-dev (https://github.com/PeterWang-dev)
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

#include "sdb.h"

#define NR_WP 32

typedef struct watchpoint {
  int NO;
  char *expr;
  word_t val;
  struct watchpoint *next;
} WP;

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}

static WP *new_wp(char* expr, word_t expr_val) {
  if (free_ == NULL) {
    // panic when no more free watch points here
    // use error handler is a better choice, not implemented yet for now
    panic("error: no more watchpoint");
  }

  WP *new_wp = free_;
  free_ = free_->next;

  new_wp->expr = (char *)malloc(strlen(expr) + 1);
  strcpy(new_wp->expr, expr);
  new_wp->val = expr_val;

  new_wp->next = head;
  head = new_wp;

  return new_wp;
}

static void free_wp(WP *wp) {
  Assert(wp != NULL, "error: trying to free a null watchpoint");

  free(wp->expr);
  wp->expr = NULL;

  wp->next = free_;
  free_ = wp;
}

void set_wp(char *e, bool *success) {
  word_t expr_val = expr(e, success);
  if (!success) {
    printf("Evaluation error\n");
    return;
  }

  WP *wp = new_wp(e, expr_val);
  printf("Watchpoint %d: %s\n", wp->NO, wp->expr);

  *success = true;
}

void del_wp(int NO, bool *success) {
  WP *wp = head, *prev = NULL;

  while (wp != NULL) {
    if (wp->NO == NO) {
      if (prev == NULL) {
        head = wp->next;
      }
      else {
        prev->next = wp->next;
      }

      free_wp(wp);
      printf("Watchpoint %d deleted\n", NO);

      *success = true;
      return;
    }

    prev = wp;
    wp = wp->next;
  }

  *success = false;
  printf("Watchpoint %d not found\n", NO);
}

void print_wp_pool() {
  WP *wp = head;

  if (wp == NULL) {
    printf("No watchpoint\n");
    return;
  }

  printf("NO\tExpression\n");
  while (wp != NULL) {
    printf("%d\t%s\n", wp->NO, wp->expr);
    wp = wp->next;
  }
}

void check_wp_pool() {
  WP *wp = head;

  while (wp != NULL) {
    word_t expr_val = expr(wp->expr, NULL);
    if (expr_val != wp->val) {
      printf("Watchpoint %d: %s\n", wp->NO, wp->expr);
      printf("Old value = %u\n", wp->val);
      printf("New value = %u\n", expr_val);
      wp->val = expr_val;

      nemu_state.state = NEMU_STOP;
    }

    wp = wp->next;
  }
}
