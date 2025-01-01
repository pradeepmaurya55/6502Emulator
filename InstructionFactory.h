#ifndef INSTRUCTIONFACTORY_H
#define INSTRUCTIONFACTORY_H

#include <unordered_map>
#include <cstdint>
#include "Instruction.h"

class InstructionFactory {
private:
    ImpliedAddressingMode implied;
    ImmediateAddressingMode immediate;
    ZeroPageAddressingMode zeroPage;
    AbsoluteAddressingMode absolute;
    ZeroPageXAddressingMode zeroPageX;
    ZeroPageYAddressingMode zeroPageY;
    AbsoluteXAddressingMode absoluteX;
    AbsoluteYAddressingMode absoluteY;
    IndirectAddressingMode indirect;
    IndexedIndirectXAddressingMode indexedIndirectX;
    IndirectIndexedYAddressingMode indirectIndexedY;
    RelativeAddressingMode relative;

    LDAOperation lda;
    LDXOperation ldx;
    LDYOperation ldy;
    STAOperation sta;
    STXOperation stx;
    STYOperation sty;
    ADCOperation adc;
    SBCOperation sbc;
    CMPOperation cmp;
    CPXOperation cpx;
    CPYOperation cpy;
    ANDOperation andOp;
    ORAOperation ora;
    EOROperation eor;
    BITOperation bit;
    INCOperation inc;
    DECOperation dec;
    INXOperation inx;
    INYOperation iny;
    DEXOperation dex;
    DEYOperation dey;
    ASLOperation asl;
    LSROperation lsr;
    ROROperation ror;
    ROLOperation rol;
    BCCOperation bcc;
    BCSOperation bcs;
    BEQOperation beq;
    BNEOperation bne;
    BMIOperation bmi;
    BPLOperation bpl;
    BVCOperation bvc;
    BVSOperation bvs;
    CLCOperation clc;
    SECOperation sec;
    CLDOperation cld;
    SEDOperation sed;
    CLIOperation cli;
    SEIOperation sei;
    CLVOperation clv;
    JMPOperation jmp;
    JSROperation jsr;
    RTSOperation rts;
    NOPOperation nop;
    BRKOperation brk;
    RTIOperation rti;
    TAXOperation tax;
    TAYOperation tay;
    TYAOperation tya;
    TXAOperation txa;
    TXSOperation txs;
    TSXOperation tsx;
    PHAOperation pha;
    PHPOperation php;
    PLAOperation pla;
    PLPOperation plp;

    enum class AddressingModeType {
    Implied, Immediate, Relative,
    ZeroPage, ZeroPageX, ZeroPageY,
    Absolute, AbsoluteX, AbsoluteY,
    Indirect, IndexedIndirectX, IndirectIndexedY,
    Accumulator
    };

    enum class OperationType {
    LDA, LDX, LDY, STA, STX, STY,
    ADC, SBC, CMP, CPX, CPY,
    AND, ORA, EOR, BIT,
    INC, DEC, INX, INY, DEX, DEY,
    ASL, LSR, ROR, ROL,
    BCC, BCS, BEQ, BNE, BMI, BPL, BVC, BVS,
    CLC, SEC, CLD, SED, CLI, SEI, CLV,
    JMP, JSR, RTS,
    NOP, BRK, RTI,
    TAX, TAY, TXA, TYA,
    TXS, TSX, PHA, PHP, PLA, PLP
    };

    static InstructionFactory* instance;

    std::unordered_map<uint8_t, std::pair<AddressingModeType, OperationType>> instructionMap;
    AddressingMode* getAddressingMode(AddressingModeType addressingModeType);
    Operation* getOperation(OperationType operationType);
    InstructionFactory();

public:
    Instruction* createInstruction(uint8_t opcode);
    static InstructionFactory* getInstance();
    ~InstructionFactory();
};

#endif
