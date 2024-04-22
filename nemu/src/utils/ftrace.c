#include "debug.h"
#include <elf.h>
#include <stdio.h>
#include <string.h>

static _Bool ftrace_enabled = 0;

static Elf32_Sym **sym_table = NULL; // symbol table
static char *str_table = NULL; // string table

void init_ftrace(const char *elf_path) {
  Elf32_Ehdr elf_header;
  FILE *file = fopen(elf_path, "rb");

  if (file) {
    // read the elf_header
    fread(&elf_header, sizeof(elf_header), 1, file);

    // check magic number so its really an elf file
    if (memcmp(elf_header.e_ident, ELFMAG, SELFMAG) != 0) {
      // invalid elf file
      panic("Invalid elf file\n");
    }

    // read the section header to find symbol table and string table
    if (elf_header.e_shoff == 0) {
      panic("No section header found\n");
    }

    int i;
    Elf32_Shdr *entry = malloc(sizeof(Elf32_Shdr));
    Elf32_Addr symtab_addr = 0, strtab_addr = 0;
    Elf32_Off symtab_offset = 0, strtab_offset = 0;

    fseek(file, elf_header.e_shoff, SEEK_SET);
    for (i = 0; i < elf_header.e_shnum; i++) {
      fread(entry, sizeof(Elf32_Shdr), 1, file);
      if (entry->sh_type == SHT_SYMTAB) {
        symtab_addr = entry->sh_addr;
        symtab_offset = entry->sh_offset;
      } else if (entry->sh_type == SHT_STRTAB) {
        strtab_addr = entry->sh_addr;
        strtab_offset = entry->sh_offset;
      }
    }

    // TODO: read symbol table and string table
    // read symbol table
    fseek(file, symtab_addr + symtab_offset, SEEK_SET);
    uint32_t sym_count = entry->sh_size / sizeof(Elf32_Sym);
    sym_table = malloc(sym_count * sizeof(Elf32_Sym *));
    for (i = 0; i < sym_count; i++) {
      sym_table[i] = malloc(sizeof(Elf32_Sym));
      fread(sym_table[i], sizeof(Elf32_Sym), 1, file);
    }

    // read string table
    fseek(file, strtab_addr + strtab_offset, SEEK_SET);
    str_table = malloc(entry->sh_size);
    fread(str_table, entry->sh_size, 1, file);

    ftrace_enabled = 1;
  } else {
    panic("Failed to open elf file\n");
  }
}

char *find_symbol(vaddr_t addr) {
  TODO(); // Implement symble lookup
}
