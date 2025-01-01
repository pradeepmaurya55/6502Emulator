#ifndef OPERATION_H
#define OPERATION_H

#include <cstdint>

class CPU;

class Operation {
public:
    virtual void operator()(CPU& cpu, uint16_t effectiveAddress) const = 0;
    virtual ~Operation() = default;
    const char* mnemonic;
};

class AccumulatorOperation : public Operation{
public:
    virtual void operator()(CPU& cpu) const = 0;
    virtual ~AccumulatorOperation() = default;
};

// Load and Store Operations
class LDAOperation : public Operation {
public:
    LDAOperation() { mnemonic = "LDA"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class LDXOperation : public Operation {
public:
    LDXOperation() { mnemonic = "LDX"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class LDYOperation : public Operation {
public:
    LDYOperation() { mnemonic = "LDY"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class STAOperation : public Operation {
public:
    STAOperation() { mnemonic = "STA"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class STXOperation : public Operation {
public:
    STXOperation() { mnemonic = "STX"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class STYOperation : public Operation {
public:
    STYOperation() { mnemonic = "STY"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

// Arithmetic Operations
class ADCOperation : public Operation {
public:
    ADCOperation() { mnemonic = "ADC"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class SBCOperation : public Operation {
public:
    SBCOperation() { mnemonic = "SBC"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class CMPOperation : public Operation {
public:
    CMPOperation() { mnemonic = "CMP"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class CPXOperation : public Operation {
public:
    CPXOperation() { mnemonic = "CPX"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class CPYOperation : public Operation {
public:
    CPYOperation() { mnemonic = "CPY"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

// Logical Operations
class ANDOperation : public Operation {
public:
    ANDOperation() { mnemonic = "AND"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class ORAOperation : public Operation {
public:
    ORAOperation() { mnemonic = "ORA"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class EOROperation : public Operation {
public:
    EOROperation() { mnemonic = "EOR"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class BITOperation : public Operation {
public:
    BITOperation() { mnemonic = "BIT"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};


// Increment and Decrement Operations
class INCOperation : public Operation {
public:
    INCOperation() { mnemonic = "INC"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class DECOperation : public Operation {
public:
    DECOperation() { mnemonic = "DEC"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class INXOperation : public Operation {
public:
    INXOperation() { mnemonic = "INX"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class INYOperation : public Operation {
public:
    INYOperation() { mnemonic = "INY"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class DEXOperation : public Operation {
public:
    DEXOperation() { mnemonic = "DEX"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class DEYOperation : public Operation {
public:
    DEYOperation() { mnemonic = "DEY"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

// Arithmetic Shift and Rotate Operations
class ASLOperation : public AccumulatorOperation {
public:
    ASLOperation() { mnemonic = "ASL"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
    void operator()(CPU& cpu) const override;
};

class LSROperation : public AccumulatorOperation {
public:
    LSROperation() { mnemonic = "LSR"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
    void operator()(CPU& cpu) const override;
};

class ROROperation : public AccumulatorOperation {
public:
    ROROperation() { mnemonic = "ROR"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
    void operator()(CPU& cpu) const override;
};

class ROLOperation : public AccumulatorOperation {
public:
    ROLOperation() { mnemonic = "ROL"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
    void operator()(CPU& cpu) const override;
};

// Branching Operations
class BCCOperation : public Operation {
public:
    BCCOperation() { mnemonic = "BCC"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class BCSOperation : public Operation {
public:
    BCSOperation() { mnemonic = "BCS"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class BEQOperation : public Operation {
public:
    BEQOperation() { mnemonic = "BEQ"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class BNEOperation : public Operation {
public:
    BNEOperation() { mnemonic = "BNE"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class BMIOperation : public Operation {
public:
    BMIOperation() { mnemonic = "BMI"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class BPLOperation : public Operation {
public:
    BPLOperation() { mnemonic = "BPL"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class BVCOperation : public Operation {
public:
    BVCOperation() { mnemonic = "BVC"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class BVSOperation : public Operation {
public:
    BVSOperation() { mnemonic = "BVS"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

// Status Flag Operations
class CLCOperation : public Operation {
public:
    CLCOperation() { mnemonic = "CLC"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class SECOperation : public Operation {
public:
    SECOperation() { mnemonic = "SEC"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class CLDOperation : public Operation {
public:
    CLDOperation() { mnemonic = "CLD"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class SEDOperation : public Operation {
public:
    SEDOperation() { mnemonic = "SED"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class CLIOperation : public Operation {
public:
    CLIOperation() { mnemonic = "CLI"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class SEIOperation : public Operation {
public:
    SEIOperation() { mnemonic = "SEI"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class CLVOperation : public Operation {
public:
    CLVOperation() { mnemonic = "CLV"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

// Jumps & Calls
class JMPOperation : public Operation {
public:
    JMPOperation() { mnemonic = "JMP"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class JSROperation : public Operation {
public:
    JSROperation() { mnemonic = "JSR"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class RTSOperation : public Operation {
public:
    RTSOperation() { mnemonic = "RTS"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

// No Operation and Break
class NOPOperation : public Operation {
public:
    NOPOperation() { mnemonic = "NOP"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class BRKOperation : public Operation {
public:
    BRKOperation() { mnemonic = "BRK"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class RTIOperation : public Operation {
public:
    RTIOperation() { mnemonic = "RTI"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

// Transfer Operations
class TAXOperation : public Operation {
public:
    TAXOperation() { mnemonic = "TAX"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class TAYOperation : public Operation {
public:
    TAYOperation() { mnemonic = "TAY"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class TXAOperation : public Operation {
public:
    TXAOperation() { mnemonic = "TXA"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class TYAOperation : public Operation {
public:
    TYAOperation() { mnemonic = "TYA"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

// Stack Operations
class TXSOperation : public Operation {
public:
    TXSOperation() { mnemonic = "TXS"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class TSXOperation : public Operation {
public:
    TSXOperation() { mnemonic = "TSX"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class PHAOperation : public Operation {
public:
    PHAOperation() { mnemonic = "PHA"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class PHPOperation : public Operation {
public:
    PHPOperation() { mnemonic = "PHP"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class PLAOperation : public Operation {
public:
    PLAOperation() { mnemonic = "PLA"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

class PLPOperation : public Operation {
public:
    PLPOperation() { mnemonic = "PLP"; }
    void operator()(CPU& cpu, uint16_t effectiveAddress) const override;
};

#endif
