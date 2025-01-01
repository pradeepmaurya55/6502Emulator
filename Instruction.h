#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "AddressingMode.h"
#include "Operation.h"

class Instruction {
public:
    virtual void execute(CPU& cpu) = 0;
    virtual ~Instruction();
};

class AccumulatorInstruction : public Instruction {
protected:
    AccumulatorOperation* operation;
public:
    AccumulatorInstruction(AccumulatorOperation* accumulatorOperation);
    void execute(CPU& cpu) override;
    ~AccumulatorInstruction() override;
};

class AddressedInstruction : public Instruction {
protected:
    AddressingMode* addressingMode;
    Operation* operation;
public:
    AddressedInstruction(AddressingMode* addressingMode, Operation* operation);
    void execute(CPU& cpu) override;
    ~AddressedInstruction() override;
};

#endif
