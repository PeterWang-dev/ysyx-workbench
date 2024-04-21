#include "debug.h"
#include <elf.h>
#include <stdio.h>
#include <string.h>

static _Bool ftrace_enabled = 0;

static Elf32_Ehdr elf_header;
static Elf32_Phdr *program_header = NULL;
static Elf32_Shdr *section_header = NULL;

static void debug_print_headers();

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

    // read the program header
    program_header = malloc(elf_header.e_phentsize * elf_header.e_phnum);
    fseek(file, elf_header.e_phoff, SEEK_SET);

    // read the section header
    section_header = malloc(elf_header.e_shentsize * elf_header.e_shnum);
    fseek(file, elf_header.e_shoff, SEEK_SET);

    fclose(file);

    debug_print_headers();

    ftrace_enabled = 1;
  } else {
    panic("Failed to open elf file\n");
  }
}

static void debug_print_headers() {
  // print the elf header
  printf("ELF Header:\n");
  printf("  Magic: ");
  for (int i = 0; i < EI_NIDENT; i++) {
    printf("%02x ", elf_header.e_ident[i]);
  }
  printf("\n");
  printf("  Class: %d-bit\n",
         elf_header.e_ident[EI_CLASS] == ELFCLASS32 ? 32 : 64);
  printf("  Data: %s\n", elf_header.e_ident[EI_DATA] == ELFDATA2LSB
                             ? "Little Endian"
                             : "Big Endian");
  printf("  Version: %d\n", elf_header.e_ident[EI_VERSION]);
  printf("  OS/ABI: %d\n", elf_header.e_ident[EI_OSABI]);
  printf("  ABI Version: %d\n", elf_header.e_ident[EI_ABIVERSION]);
  printf("  Type: %d\n", elf_header.e_type);
  printf("  Machine: %d\n", elf_header.e_machine);
  printf("  Version: %d\n", elf_header.e_version);
  printf("  Entry point address: 0x%x\n", elf_header.e_entry);
  printf("  Start of program headers: %d (bytes into file)\n",
         elf_header.e_phoff);
  printf("  Start of section headers: %d (bytes into file)\n",
         elf_header.e_shoff);
  printf("  Flags: 0x%x\n", elf_header.e_flags);
  printf("  Size of this header: %d (bytes)\n", elf_header.e_ehsize);
  printf("  Size of program headers: %d (bytes)\n", elf_header.e_phentsize);
  printf("  Number of program headers: %d\n", elf_header.e_phnum);
  printf("  Size of section headers: %d (bytes)\n", elf_header.e_shentsize);
  printf("  Number of section headers: %d\n", elf_header.e_shnum);
  printf("  Section header string table index: %d\n", elf_header.e_shstrndx);

  // print the program header table
  printf("Program Header Table:\n");
  printf(
      "  Type\t\tOffset\t\tVirtAddr\tPhysAddr\tFileSiz\tMemSiz\tFlg\tAlign\n");
  for (int i = 0; i < elf_header.e_phnum; i++) {
    Elf32_Phdr *phdr = &program_header[i];
    printf("  %d\t\t0x%x\t0x%x\t0x%x\t0x%x\t0x%x\t%d\t0x%x\n", phdr->p_type,
           phdr->p_offset, phdr->p_vaddr, phdr->p_paddr, phdr->p_filesz,
           phdr->p_memsz, phdr->p_flags, phdr->p_align);
  }

  // print the section header table
  printf("Section Header Table:\n");
  printf(
      "  [Nr]\tName\t\tType\t\tAddr\t\tOff\t\tSize\t\tES\tFlg\tLk\tInf\tAl\n");
  for (int i = 0; i < elf_header.e_shnum; i++) {
    Elf32_Shdr *shdr = &section_header[i];
    printf(
        "  [%2d]\t%-16s\t%-16d\t0x%08x\t0x%08x\t0x%08x\t%d\t%d\t%d\t%d\t%d\n",
        i, (char *)(section_header + shdr->sh_name), shdr->sh_type,
        shdr->sh_addr, shdr->sh_offset, shdr->sh_size, shdr->sh_entsize,
        shdr->sh_flags, shdr->sh_link, shdr->sh_info, shdr->sh_addralign);
  }
}

char *find_symbol(vaddr_t addr) { TODO(); }
