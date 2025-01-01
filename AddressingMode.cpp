#include "AddressingMode.h"
#include "CPU.h"

//Implied Addressing Mode
uint16_t ImpliedAddressingMode::operator()(CPU& cpu) {
    return 0;  // Implied addressing mode doesn't need an operand
}

// Immediate Addressing Mode
uint16_t ImmediateAddressingMode::operator()(CPU& cpu) {
    cpu.setPC(cpu.getPC()+1);
    return cpu.getPC()-1;
}

// Zero Page Addressing Mode
uint16_t ZeroPageAddressingMode::operator()(CPU& cpu) {
    return cpu.fetch() & 0xFF; 
}

// Absolute Addressing Mode
uint16_t AbsoluteAddressingMode::operator()(CPU& cpu) {
    uint8_t lowByte = cpu.fetch();
    uint8_t highByte = cpu.fetch();
    return (highByte << 8) | lowByte; 
}

// Zero Page,X Addressing Mode
uint16_t ZeroPageXAddressingMode::operator()(CPU& cpu) {
    return (cpu.fetch() + cpu.getX()) & 0xFF;  
}

// Zero Page,Y Addressing Mode
uint16_t ZeroPageYAddressingMode::operator()(CPU& cpu) {
    return (cpu.fetch() + cpu.getY()) & 0xFF; 
}

// Absolute,X Addressing Mode
uint16_t AbsoluteXAddressingMode::operator()(CPU& cpu) {
    uint8_t lowByte = cpu.fetch();
    uint8_t highByte = cpu.fetch();
    uint16_t address = (highByte << 8) | lowByte;
    return address + cpu.getX();  
}

// Absolute,Y Addressing Mode
uint16_t AbsoluteYAddressingMode::operator()(CPU& cpu) {
    uint8_t lowByte = cpu.fetch();
    uint8_t highByte = cpu.fetch();
    uint16_t address = (highByte << 8) | lowByte;
    return address + cpu.getY(); 
}

// Indirect Addressing Mode
uint16_t IndirectAddressingMode::operator()(CPU& cpu) {
    uint8_t lowByte = cpu.fetch();
    uint8_t highByte = cpu.fetch();
    uint16_t address = (highByte << 8) | lowByte;

    uint8_t low = cpu.read(address);
    uint8_t high = cpu.read(address + 1);
    return (high << 8) | low;
}

// Indexed Indirect (X) Addressing Mode
uint16_t IndexedIndirectXAddressingMode::operator()(CPU& cpu) {
    uint8_t baseAddress = cpu.fetch();
    uint16_t address = (baseAddress + cpu.getX()) & 0xFF; 

    uint8_t low = cpu.read(address);
    uint8_t high = cpu.read(address + 1);
    return (high << 8) | low;  
}

// Indirect Indexed (Y) Addressing Mode
uint16_t IndirectIndexedYAddressingMode::operator()(CPU& cpu) {
    uint8_t baseAddress = cpu.fetch();
    uint16_t address = baseAddress;  

    uint8_t low = cpu.read(address);
    uint8_t high = cpu.read(address + 1);
    uint16_t indirectAddress = (high << 8) | low;
    return indirectAddress + cpu.getY();  
}

// Relative Addressing Mode
uint16_t RelativeAddressingMode::operator()(CPU& cpu) {
    int8_t offset = static_cast<int8_t>(cpu.fetch());
    return cpu.getPC() + offset;
}
