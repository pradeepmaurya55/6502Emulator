#ifndef BUS_H
#define BUS_H

#include "Memory.h"
#include <cstdint>


class Bus {
private:
    Memory& memory;
public:
    Bus(Memory& mem);
    uint8_t readMemory(uint16_t address);
    void writeMemory(uint16_t address, uint8_t data);
};

#endif 