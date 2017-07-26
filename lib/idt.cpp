#include <stdint.h>
#include "pic.h"

#define PIC_OFFSET 0x20
#define KBD_IRQ 0x1

struct interrapt_gate {
	uint16_t offset_1;
	uint16_t segment_selector;
	uint8_t reserved;
	uint8_t flags;
	uint16_t offset_2;
} __attribute__((packed));

interrapt_gate idt[256];

extern "C" void on_key_pressed_start();
extern "C" void ignore_start();

void init_interrapt_gate(void* function_addr, int interrapt_id) {
	uint32_t fa = (uint32_t) function_addr;
	idt[interrapt_id].offset_1 = fa & 0xffff;
	idt[interrapt_id].segment_selector = 0x10;
	idt[interrapt_id].reserved = 0;
	idt[interrapt_id].flags = (0xe) | (1 << 7);
	idt[interrapt_id].offset_2 = (uint16_t) (fa >> 16);
}

struct idtr_t {
	uint16_t size;
	uint32_t addr;
} __attribute__((packed));

void load_idt(uint16_t sz, interrapt_gate *idt_addr) {
	idtr_t idtr;
	idtr.size = sz - 1;
	idtr.addr = (uint32_t) idt_addr;
	asm ("lidt (%0)": : "a"(&idtr) : "memory" );
}

extern "C" void init_idt() {
	pic_remap(PIC1, PIC2);
	init_interrapt_gate((void*)&on_key_pressed_start, PIC_OFFSET + KBD_IRQ);
	init_interrapt_gate((void*)&ignore_start, PIC_OFFSET);
	load_idt(sizeof(idt), idt);
}


