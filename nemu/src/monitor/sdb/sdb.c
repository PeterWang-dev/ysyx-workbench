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
 *******************************************************************************/

#include "sdb.h"
#include "common.h"
#include "debug.h"
#include "memory/paddr.h"
#include "utils.h"
#include <cpu/cpu.h>
#include <isa.h>
#include <readline/history.h>
#include <readline/readline.h>

static int is_batch_mode = false;

extern void init_regex();
extern void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin.
 */
static char *rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args);
static int cmd_q(char *args);
static int cmd_help(char *args);
static int cmd_si(char *args);
static int cmd_info(char *args);
static int cmd_x(char *args);
static int cmd_p(char *args);
static int cmd_w(char *args);
static int cmd_d(char *args);

static struct {
  const char *name;
  const char *description;
  int (*handler)(char *);
} cmd_table[] = {
    {"help", "Display information about all supported commands", cmd_help},
    {"c", "Continue the execution of the program", cmd_c},
    {"q", "Exit NEMU", cmd_q},
    {"si",
     "Let the program execute N instructions in a single step "
     "and then pause execution. When N is not given, the default is 1 ",
     cmd_si},
    {"info", "Print register status or watchpoint information", cmd_info},
    {"x",
     "Evaluate EXPR, use the result as the starting memory address, "
     "and output N consecutive 4 bytes in hexadecimal form",
     cmd_x},
    {"p", "Find the value of the expression EXPR", cmd_p},
    {"w", "Set a watchpoint for an expression EXPR", cmd_w},
    {"d", "Delete the watchpoint of the given index NO", cmd_d}};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  } else {
    for (i = 0; i < NR_CMD; i++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}

static int cmd_q(char *args) {
  nemu_state.state = NEMU_QUIT;
  return -1;
}

static int cmd_si(char *args) {
  uint64_t exec_num = 0;

  if (args == NULL) {
    exec_num = 1;
  } else if (sscanf(args, "%ld", &exec_num) < 1) {
    printf("Invalid argument '%s'\n", args);
    return 1;
  }

  cpu_exec(exec_num);
  return 0;
}

extern void print_wp_pool();

static int cmd_info(char *args) {
  if (args == NULL) {
    printf("Expect argument\n");
    return 1;
  }

  char sub_command;
  if (sscanf(args, "%c", &sub_command) < 1) {
    printf("Invalid argument '%s'\n", args);
    return 1;
  }

  if (sub_command == 'r') {
    isa_reg_display();
  } else if (sub_command == 'w') {
    print_wp_pool();
  } else {
    printf("Unknown subcommand '%c'\n", sub_command);
    return 1;
  }

  return 0;
}

static int cmd_x(char *args) {
  if (args == NULL) {
    printf("Expect argument\n");
    return 1;
  }

  uint32_t max_offset = 0;
  char *e = malloc(strlen(args) + 1);

  if (sscanf(args, "%u %s", &max_offset, e) < 2) {
    printf("Invalid argument '%s'\n", args);
    free(e);
    return 1;
  }

  bool success = false;

  paddr_t base_addr = expr(e, &success);
  if (success == false) {
    printf("Invalid expression '%s'\n", e);
    free(e);
    return 1;
  }

  for (int i = 0; i < max_offset; i++) {
    printf("0x%x\n", paddr_read(base_addr + 4 * i, 4));
  }

  free(e);
  return 0;
}

static int print_counter = 0;
static int cmd_p(char *args) {
  if (args == NULL) {
    printf("Expect argument\n");
    return 1;
  }

  bool stat = false;
  word_t result = expr(args, &stat);

  if (stat == true) {
    printf("$%d = %u\n", ++print_counter, result);
  } else {
    printf("Evaluation error\n");
    return 1;
  }

  return 0;
}

extern void set_wp(char *e, bool *success);

static int cmd_w(char *args) {
  if (args == NULL) {
    printf("Expect argument\n");
    return 1;
  }

  bool stat = false;
  set_wp(args, &stat);

  if (stat == false) {
    printf("Failed to set watchpoint\n");
    return 1;
  }

  printf("Watchpoint set successfully\n");
  return 0;
}

extern void del_wp(int NO, bool *success);

static int cmd_d(char *args) {
  if (args == NULL) {
    printf("Expect argument\n");
    return 1;
  }

  int wp_index = 0;
  if (sscanf(args, "%d", &wp_index) < 1) {
    printf("Invalid argument '%s'\n", args);
    return 1;
  }

  bool stat = false;
  del_wp(wp_index, &stat);

  if (stat == false) {
    printf("Failed to delete watchpoint %d\n", wp_index);
    return 1;
  }

  printf("Watchpoint %d deleted successfully\n", wp_index);
  return 0;
}

void sdb_set_batch_mode() { is_batch_mode = true; }

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL;) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) {
      continue;
    }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) {
          return;
        }
        break;
      }
    }

    if (i == NR_CMD) {
      printf("Unknown command '%s'\n", cmd);
    }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
