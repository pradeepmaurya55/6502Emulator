#include "Instruction.h"
#include "CPU.h"

Instruction::~Instruction() {}

AccumulatorInstruction::AccumulatorInstruction(AccumulatorOperation* accumulatorOperation)
    : operation(accumulatorOperation) {}

void AccumulatorInstruction::execute(CPU& cpu) {
    (*operation)(cpu);
}

AccumulatorInstruction::~AccumulatorInstruction() {}

AddressedInstruction::AddressedInstruction(AddressingMode* addressingMode, Operation* operation)
    : addressingMode(addressingMode), operation(operation) {}

void AddressedInstruction::execute(CPU& cpu) {
    uint16_t effectiveAddress = (*addressingMode)(cpu);
    (*operation)(cpu, effectiveAddress);
}

AddressedInstruction::~AddressedInstruction() {}
