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

    // print file header
    printf("ELF Header:\n");
    printf("  Magic: ");
    for (int i = 0; i < SELFMAG; i++) {
      printf("%02x ", elf_header.e_ident[i]);
    }
    printf("\n");
    printf("  Class: %d-bit\n", elf_header.e_ident[EI_CLASS] == ELFCLASS32 ? 32 : 64);
    printf("  Data: %s\n", elf_header.e_ident[EI_DATA] == ELFDATA2LSB ? "2's complement, little endian" : "2's complement, big endian");
    printf("  Version: %d\n", elf_header.e_ident[EI_VERSION]);
    printf("  OS/ABI: %s\n", elf_header.e_ident[EI_OSABI] == ELFOSABI_SYSV ? "UNIX - System V" : "Unknown");
    printf("  ABI Version: %d\n", elf_header.e_ident[EI_ABIVERSION]);
    printf("  Type: %s\n", elf_header.e_type == ET_EXEC ? "Executable file" : "Unknown");
    printf("  Machine: %s\n", elf_header.e_machine == EM_386 ? "Intel 80386" : "Unknown");
    printf("  Version: 0x%x\n", elf_header.e_version);
    printf("  Entry point address: 0x%x\n", elf_header.e_entry);
    printf("  Start of program headers: %d (bytes into file)\n", elf_header.e_phoff);
    printf("  Start of section headers: %d (bytes into file)\n", elf_header.e_shoff);
    printf("  Flags: 0x%x\n", elf_header.e_flags);
    printf("  Size of this header: %d (bytes)\n", elf_header.e_ehsize);
    printf("  Size of program headers: %d (bytes)\n", elf_header.e_phentsize);
    printf("  Number of program headers: %d\n", elf_header.e_phnum);
    printf("  Size of section headers: %d (bytes)\n", elf_header.e_shentsize);
    printf("  Number of section headers: %d\n", elf_header.e_shnum);
    printf("  Section header string table index: %d\n", elf_header.e_shstrndx);

    fclose(file);

    ftrace_enabled = 1;
  } else {
    panic("Failed to open elf file\n");
  }
}

char *find_symbol(vaddr_t addr) { TODO(); }
