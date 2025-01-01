#include<iostream>
#include <bitset>
#include "CPU.h"
#include "Instruction.h"
#include "InstructionFactory.h"

CPU::CPU(Bus& bus) 
    : bus(bus),instructionFactory(InstructionFactory::getInstance()),A(0), X(0), Y(0), SP(0xFD), PC(0x0000), StatusRegister(0x34) {}

void CPU::reset() {
    A = 0;
    X = 0;
    Y = 0;
    SP = 0xFF;
    StatusRegister = 0x34;
    PC = bus.readMemory(0xFFFC) | (bus.readMemory(0xFFFD) << 8);
}

void CPU::execute() {
    uint8_t opcode = fetch();
    Instruction* instruction = instructionFactory->createInstruction(opcode); 
    if (instruction) {
        instruction->execute(*this);
        delete instruction;
    } else {
        std::cout << "Invalid opcode: " << std::hex << (int)opcode << std::dec << std::endl;
    }
}

//Memory Operations
uint8_t CPU::fetch() {
    return bus.readMemory(PC++);
}

uint8_t CPU::read(uint16_t address) {
    return bus.readMemory(address);
}

void CPU::write(uint16_t address, uint8_t value) {
    bus.writeMemory(address, value);
}

//Register Operations
uint8_t CPU::getAccumulator() const {
    return A;
}

void CPU::setAccumulator(uint8_t value) {
    A = value;
}

uint8_t CPU::getX() const {
    return X;
}

void CPU::setX(uint8_t value) {
    X = value;
}

uint8_t CPU::getY() const {
    return Y;
}

void CPU::setY(uint8_t value) {
    Y = value;
}

uint16_t CPU::getPC() const {
    return PC;
}

void CPU::setPC(uint16_t value) {
    PC = value;
}

uint8_t CPU::getSP() const {
    return SP;
}

void CPU::setSP(uint8_t value) {
    SP = value;
}

//Status Register and Flags Operations
bool CPU::getCarryFlag() const {
    return C;
}

void CPU::setCarryFlag(bool flag) {
    C = flag;
}

bool CPU::getZeroFlag() const {
    return Z;
}

void CPU::setZeroFlag(bool flag) {
    Z = flag;
}

bool CPU::getInterruptDisableFlag() const {
    return I;
}

void CPU::setInterruptDisableFlag(bool flag) {
    I = flag;
}

bool CPU::getDecimalFlag() const {
    return D;
}

void CPU::setDecimalFlag(bool flag) {
    D = flag;
}

bool CPU::getBreakFlag() const {
    return B;
}

void CPU::setBreakFlag(bool flag) {
    B = flag;
}

bool CPU::getOverflowFlag() const {
    return V;
}

void CPU::setOverflowFlag(bool flag) {
    V = flag;
}

bool CPU::getNegativeFlag() const {
    return N;
}

void CPU::setNegativeFlag(bool flag) {
    N = flag;
}

bool CPU::getUnusedFlag() const {
    return U;
}

void CPU::setUnusedFlag(bool flag) {
    U = flag;
}

void CPU::setFlags(uint8_t flags) {
    StatusRegister |= flags;
}

void CPU::clearFlags(uint8_t flags) {
    StatusRegister &= ~flags;
}

uint8_t CPU::getStatusRegister()
{
    return StatusRegister;
}

void CPU::setStatusRegister(uint8_t value)
{
    StatusRegister = value;
}

//Stack Operations
void CPU::pushStack(uint8_t value) {
    bus.writeMemory(0x0100 | SP, value);
    SP--;
}

uint8_t CPU::pullStack() {
    SP++;
    return bus.readMemory(0x0100 | SP);
}

void CPU::pushPC() {
    pushStack(PC >> 8);
    pushStack(PC & 0xFF);
}

uint16_t CPU::pullPC() {
    uint8_t low = pullStack();
    uint8_t high = pullStack();
    return (high << 8) | low;
}

void CPU::printState() {
    // Print Register Values
    std::cout << "A (Accumulator): " << std::hex << (int)A << std::endl;
    std::cout << "X (Index Register X): " << std::hex << (int)X << std::endl;
    std::cout << "Y (Index Register Y): " << std::hex << (int)Y << std::endl;
    std::cout << "SP (Stack Pointer): " << std::hex << (int)SP << std::endl;
    std::cout << "PC (Program Counter): " << std::hex << (int)PC << std::endl;

    std::cout << "Status Register: " << std::bitset<8>(StatusRegister) << std::endl;

    std::cout << "Carry Flag: " << getCarryFlag() << std::endl;
    std::cout << "Zero Flag: " << getZeroFlag() << std::endl;
    std::cout << "Interrupt Disable Flag: " << getInterruptDisableFlag() << std::endl;
    std::cout << "Decimal Flag: " << getDecimalFlag() << std::endl;
    std::cout << "Break Flag: " << getBreakFlag() << std::endl;
    std::cout << "Unused Flag: " << getUnusedFlag() << std::endl;
    std::cout << "Overflow Flag: " << getOverflowFlag() << std::endl;
    std::cout << "Negative Flag: " << getNegativeFlag() << std::endl;
}

void CPU::printFlags() {
    std::cout << "C=" << (int)getCarryFlag() << " ";
    std::cout << "Z=" << (int)getZeroFlag() << " ";
    std::cout << "I=" << (int)getInterruptDisableFlag() << " ";
    std::cout << "D=" << (int)getDecimalFlag() << " ";
    std::cout << "B=" << (int)getBreakFlag() << " ";
    std::cout << "U=" << (int)getUnusedFlag() << " ";
    std::cout << "V=" << (int)getOverflowFlag() << " ";
    std::cout << "N=" << (int)getNegativeFlag() << " ";
    std::cout << "A=" << std::hex << (int)getAccumulator() << " ";
    std::cout << "X=" << std::hex << (int)getX() << " ";
    std::cout << "Y=" << std::hex << (int)getY() << " ";
    }