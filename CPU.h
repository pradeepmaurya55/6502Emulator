#ifndef CPU_H
#define CPU_H
 
#include <cstdint>
#include "Bus.h"
#include "Instruction.h"
#include "InstructionFactory.h"

class CPU {
private:
    Bus& bus;

    InstructionFactory* instructionFactory;

    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint8_t SP;
    uint16_t PC;
    
    union {
        struct {
            uint8_t C : 1;
            uint8_t Z : 1;
            uint8_t I : 1;
            uint8_t D : 1;
            uint8_t B : 1;
            uint8_t U : 1;
            uint8_t V : 1;
            uint8_t N : 1;
        };
        uint8_t StatusRegister;
    };

public:
    CPU(Bus& bus);
    
    void reset();
    void execute();
    
    //Memory Operations
    uint8_t fetch();
    uint8_t read(uint16_t address);
    void write(uint16_t address, uint8_t value);

    //Register Operations
    uint8_t getAccumulator() const;
    void setAccumulator(uint8_t value);
    uint8_t getX() const;
    void setX(uint8_t value);
    uint8_t getY() const;
    void setY(uint8_t value);
    uint16_t getPC() const;
    void setPC(uint16_t value);
    uint8_t getSP() const;
    void setSP(uint8_t value);
    
    //Status Register and Flags Operations
    bool getCarryFlag() const;
    void setCarryFlag(bool flag);
    bool getZeroFlag() const;
    void setZeroFlag(bool flag);
    bool getInterruptDisableFlag() const;
    void setInterruptDisableFlag(bool flag);
    bool getDecimalFlag() const;
    void setDecimalFlag(bool flag);
    bool getBreakFlag() const;
    void setBreakFlag(bool flag);
    bool getOverflowFlag() const;
    void setOverflowFlag(bool flag);
    bool getNegativeFlag() const;
    void setNegativeFlag(bool flag);
    bool getUnusedFlag() const;
    void setUnusedFlag(bool flag);

    void setFlags(uint8_t flags);
    void clearFlags(uint8_t flags);
    uint8_t getStatusRegister();
    void setStatusRegister(uint8_t value);

    //Stack Operations
    void pushStack(uint8_t value);
    uint8_t pullStack();

    void pushPC();
    uint16_t pullPC();

    //Debugging
    void printState();
    void printFlags();
};

#endif
