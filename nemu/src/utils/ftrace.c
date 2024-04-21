#include "debug.h"
#include <elf.h>
#include <stdio.h>
#include <string.h>

static _Bool ftrace_enabled = 0;

static Elf32_Ehdr elf_header;
static Elf32_Phdr program_header;
static Elf32_Shdr section_header;

void init_ftrace(const char *elf_file) {
  FILE *file = fopen(elf_file, "rb");
  if (file) {
    // read the elf_header
    fread(&elf_header, sizeof(elf_header), 1, file);

    // check so its really an elf file
    if (memcmp(elf_header.e_ident, ELFMAG, SELFMAG) != 0) {
      // invalid elf file
      panic("Invalid elf file\n");
    }

    fread(&program_header, sizeof(program_header), 1, file);
    fread(&section_header, sizeof(section_header), 1, file);

    // debug print all headers
    printf("ELF Header:\n");
    printf("  Magic: ");
    for (int i = 0; i < EI_NIDENT; i++) {
      printf("%02x ", elf_header.e_ident[i]);
    }
    printf("\n");
    printf("  Type: %d\n", elf_header.e_type);
    printf("  Machine: %d\n", elf_header.e_machine);
    printf("  Version: %d\n", elf_header.e_version);
    printf("  Entry point address: %x\n", elf_header.e_entry);
    printf("  Program header offset: %d\n", elf_header.e_phoff);
    printf("  Section header offset: %d\n", elf_header.e_shoff);
    printf("  Flags: %d\n", elf_header.e_flags);
    printf("  Size of this header: %d\n", elf_header.e_ehsize);
    printf("  Size of program headers: %d\n", elf_header.e_phentsize);
    printf("  Number of program headers: %d\n", elf_header.e_phnum);
    printf("  Size of section headers: %d\n", elf_header.e_shentsize);
    printf("  Number of section headers: %d\n", elf_header.e_shnum);
    printf("  Section header string table index: %d\n", elf_header.e_shstrndx);

    printf("Program Header:\n");
    printf("  Type: %d\n", program_header.p_type);
    printf("  Offset: %d\n", program_header.p_offset);
    printf("  Virtual address: %x\n", program_header.p_vaddr);
    printf("  Physical address: %x\n", program_header.p_paddr);
    printf("  File size: %d\n", program_header.p_filesz);
    printf("  Memory size: %d\n", program_header.p_memsz);
    printf("  Flags: %d\n", program_header.p_flags);
    printf("  Alignment: %d\n", program_header.p_align);

    printf("Section Header:\n");
    printf("  Name: %d\n", section_header.sh_name);
    printf("  Type: %d\n", section_header.sh_type);
    printf("  Flags: %d\n", section_header.sh_flags);
    printf("  Address: %x\n", section_header.sh_addr);
    printf("  Offset: %d\n", section_header.sh_offset);
    printf("  Size: %d\n", section_header.sh_size);
    printf("  Link: %d\n", section_header.sh_link);
    printf("  Info: %d\n", section_header.sh_info);
    printf("  Address alignment: %d\n", section_header.sh_addralign);
    printf("  Entry size: %d\n", section_header.sh_entsize);

    fclose(file);

    ftrace_enabled = 1;
  } else {
    panic("Failed to open elf file\n");
  }
}

char *find_symbol(vaddr_t addr) { TODO(); }
