
#include "Memory.h"
#include <cstring> 
#include <fstream>
#include <iostream>

Memory::Memory() {
    std::memset(memory, 0, sizeof(memory));
}

uint8_t Memory::read(uint16_t address) {
    if (address < sizeof(memory)) {
        return memory[address];
    }
    return 0;
}

void Memory::write(uint16_t address, uint8_t data) {
    if (address < sizeof(memory)) {
        memory[address] = data;
    }
}

void Memory::loadProgram(const std::string& filepath, uint16_t startAddress) {
    std::ifstream file(filepath, std::ios::binary);
    if (!file) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return;
    }

    uint8_t byte;
    uint16_t address = startAddress;

    while (file.read(reinterpret_cast<char*>(&byte), sizeof(byte))) {
        if (address >= sizeof(memory)) {
            std::cerr << "Attempt to write past memory bounds at address " << std::hex << address << std::endl;
            break;
        }
        write(address++, byte);  
    }

    std::cout << "Program loaded into memory starting at address " << std::hex << startAddress;
    std::cout << " & ending at " << std::hex << address - 1 <<std::endl;
    file.close();
}

uint8_t& Memory::operator[](uint16_t address) {
    if (address >= sizeof(memory)) {
        throw std::out_of_range("Address is out of bounds");
    }
    return memory[address];
}