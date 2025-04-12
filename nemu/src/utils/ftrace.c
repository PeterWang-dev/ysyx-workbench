#include "debug.h"
#include <elf.h>
#include <stdio.h>
#include <string.h>

bool ftrace_enabled = 0;

static Elf32_Sym **sym_table = NULL; // symbol table
static uint32_t sym_count;           // number of symbol table entries
static char *str_table = NULL;       // string table

//! WARNING: Not freeing the memory allocated for sym_table and str_table,
//! memory leaks, skipping free for now

char *find_symbol(vaddr_t addr) {
  int i;
  for (i = 0; i < sym_count; i++) {
    if (ELF32_ST_TYPE(sym_table[i]->st_info) == STT_FUNC) {
      if (addr >= sym_table[i]->st_value &&
          addr < sym_table[i]->st_value + sym_table[i]->st_size) {
        return str_table + sym_table[i]->st_name;
      }
    }
  }
  return NULL;
}

void init_ftrace(const char *elf_path) {
  FILE *file = fopen(elf_path, "rb");

  if (file == NULL) {
    panic("Failed to open elf file: %s\n", elf_path);
  }

  // read the elf_header
  Elf32_Ehdr elf_header;
  if (fread(&elf_header, sizeof(elf_header), 1, file) != 1) {
    panic("Failed to read elf header\n");
  }

  // check magic number so its really an elf file
  if (memcmp(elf_header.e_ident, ELFMAG, SELFMAG) != 0) {
    panic("Invalid elf file\n");
  }

  // check if section header table offset is zero which means SHT not exists
  if (elf_header.e_shoff == 0) {
    panic("No section header table found\n");
  }

  // read the section header tables to find the symbol table and string table
  Elf32_Addr symtab_addr = 0, strtab_addr = 0;
  Elf32_Off symtab_offset = 0, strtab_offset = 0;
  uint32_t symtab_size = 0, strtab_size = 0;

  fseek(file, elf_header.e_shoff, SEEK_SET);
  for (int i = 0; i < elf_header.e_shnum; i++) {
    Elf32_Shdr sh_entry;
    if (fread(&sh_entry, sizeof(Elf32_Shdr), 1, file) != 1) {
      panic("Failed to read section header\n");
    }
    if (sh_entry.sh_type == SHT_SYMTAB) {
      symtab_addr = sh_entry.sh_addr;
      symtab_offset = sh_entry.sh_offset;
      symtab_size = sh_entry.sh_size;
    } else if (sh_entry.sh_type == SHT_STRTAB) {
      strtab_addr = sh_entry.sh_addr;
      strtab_offset = sh_entry.sh_offset;
      strtab_size = sh_entry.sh_size;
      // only read the first string table (strtab not shstrtab)
      // strtab stores the names of the symbols
      // shstrtab stores the names of the sections
      break;
    }
    //! WARNNING: Missing error handling for
    //! when no symbol table or string table is found
  }

  // read symbol table
  fseek(file, symtab_addr + symtab_offset, SEEK_SET);
  sym_count = symtab_size / sizeof(Elf32_Sym);
  sym_table = malloc(sym_count * sizeof(Elf32_Sym *));
  for (int i = 0; i < sym_count; i++) {
    sym_table[i] = malloc(sizeof(Elf32_Sym));
    if (fread(sym_table[i], sizeof(Elf32_Sym), 1, file) != 1) {
      panic("Failed to read symbol table\n");
    }
  }

  // read string table
  fseek(file, strtab_addr + strtab_offset, SEEK_SET);
  str_table = malloc(strtab_size);
  if (fread(str_table, strtab_size, 1, file) != 1) {
    panic("Failed to read string table\n");
  }

  ftrace_enabled = 1;
}

// Loging logic is implemented in log.c
// void log_ftrace(vaddr_t dnpc, int type);
