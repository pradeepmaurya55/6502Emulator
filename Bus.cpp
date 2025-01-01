#include "Bus.h"

Bus::Bus(Memory& mem) : memory(mem) {}

uint8_t Bus::readMemory(uint16_t address) {
    return memory.read(address);
}

void Bus::writeMemory(uint16_t address, uint8_t data) {
    memory.write(address, data);
}