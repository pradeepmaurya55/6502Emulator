// Memory.h
#ifndef MEMORY_H
#define MEMORY_H

#include <cstdint>
#include <string>

class Memory {
private:
    uint8_t memory[1024 * 64];

public:
    Memory();
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t data);
    void loadProgram(const std::string& filepath, uint16_t startAddress);
    uint8_t& operator[](uint16_t address);//debugging
};

#endif 
