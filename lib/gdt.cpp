#include <stdint.h>
#include "easy_printf.h"

void db() {
	printf("hello!");
	while (true) {}
}

struct segment_descriptor_t {
	uint16_t segment_limit_1;
	uint16_t base_address_1;
	uint8_t base_address_2;
	uint8_t type_and_flags;
	uint8_t segment_limit_2_and_flags;
	uint8_t base_address_3;
};

segment_descriptor_t gdt[3];

void init_null_sd(segment_descriptor_t &sd) {
	sd.segment_limit_1 = 0;
	sd.base_address_1 = 0;
	sd.base_address_2 = 0;
	sd.type_and_flags = 0;
	sd.segment_limit_2_and_flags = 0;
	sd.base_address_3 = 0;
}

void init_data_sd(segment_descriptor_t &sd) {
	sd.segment_limit_1 = 0xffff;
	sd.base_address_1 = 0;
	sd.base_address_2 = 0;
	sd.type_and_flags = (1 << 1) | (1 << 4) | (1 << 7);
	sd.segment_limit_2_and_flags = (0xff) | (1 << 6) | (1 << 7);
	sd.base_address_3 = 0;
}

void init_code_sd(segment_descriptor_t &sd) {
	sd.segment_limit_1 = 0xffff;
	sd.base_address_1 = 0;
	sd.base_address_2 = 0;
	sd.type_and_flags = (1 << 1) | (1 << 3) | (1 << 4) | (1 << 7);
	sd.segment_limit_2_and_flags = (0xff) | (1 << 6) | (1 << 7);
	sd.base_address_3 = 0;	
}

struct gdtr_t {
    uint16_t size;
    uint32_t addr;
} __attribute__((packed));

void load_gdt(segment_descriptor_t *gdt_ptr, uint16_t sz) {
	gdtr_t gdtr;
	gdtr.size = sz - 1;
	gdtr.addr = (uint32_t) gdt_ptr;
  	asm ("lgdt (%0)": : "a"(&gdtr));
  	asm(
    "ljmp $0x10, $reload_cs\n\t"
    "reload_cs:\n\t"
    "mov $0x08, %%ax\n\t"
    "mov %%ax, %%ds\n\t"
    :
    :
    : "ax");
}

extern "C" void init_gdt() {
	init_null_sd(gdt[0]);
	init_data_sd(gdt[1]);
	init_code_sd(gdt[2]); 
	load_gdt(gdt, sizeof(gdt));
}

