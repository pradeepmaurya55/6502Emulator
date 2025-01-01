#ifndef ADDRESSINGMODE_H
#define ADDRESSINGMODE_H

#include <cstdint>

class CPU;

class AddressingMode {
public:
    virtual uint16_t operator()(CPU& cpu) = 0;  
    virtual ~AddressingMode() = default;
    const char* mnemonic; // Constant mnemonic for the addressing mode
};

// Implied Addressing Mode - No operand, just operation
class ImpliedAddressingMode : public AddressingMode {
public:
    ImpliedAddressingMode() { mnemonic = "IMP"; }
    uint16_t operator()(CPU& cpu) override;
};

// Immediate Addressing Mode
class ImmediateAddressingMode : public AddressingMode {
public:
    ImmediateAddressingMode() { mnemonic = "IMM"; }
    uint16_t operator()(CPU& cpu) override;
};

// Zero Page Addressing Mode
class ZeroPageAddressingMode : public AddressingMode {
public:
    ZeroPageAddressingMode() { mnemonic = "ZP"; }
    uint16_t operator()(CPU& cpu) override;
};

// Absolute Addressing Mode
class AbsoluteAddressingMode : public AddressingMode {
public:
    AbsoluteAddressingMode() { mnemonic = "ABS"; }
    uint16_t operator()(CPU& cpu) override;
};

// Zero Page,X Addressing Mode
class ZeroPageXAddressingMode : public AddressingMode {
public:
    ZeroPageXAddressingMode() { mnemonic = "ZPX"; }
    uint16_t operator()(CPU& cpu) override;
};

// Zero Page,Y Addressing Mode
class ZeroPageYAddressingMode : public AddressingMode {
public:
    ZeroPageYAddressingMode() { mnemonic = "ZPY"; }
    uint16_t operator()(CPU& cpu) override;
};

// Absolute,X Addressing Mode
class AbsoluteXAddressingMode : public AddressingMode {
public:
    AbsoluteXAddressingMode() { mnemonic = "ABS,X"; }
    uint16_t operator()(CPU& cpu) override;
};

// Absolute,Y Addressing Mode
class AbsoluteYAddressingMode : public AddressingMode {
public:
    AbsoluteYAddressingMode() { mnemonic = "ABS,Y"; }
    uint16_t operator()(CPU& cpu) override;
};

// Indirect Addressing Mode
class IndirectAddressingMode : public AddressingMode {
public:
    IndirectAddressingMode() { mnemonic = "IND"; }
    uint16_t operator()(CPU& cpu) override;
};

// Indirect Indexed (X) Addressing Mode
class IndexedIndirectXAddressingMode : public AddressingMode {
public:
    IndexedIndirectXAddressingMode() { mnemonic = "IX"; }
    uint16_t operator()(CPU& cpu) override;
};

// Indirect Indexed (Y) Addressing Mode
class IndirectIndexedYAddressingMode : public AddressingMode {
public:
    IndirectIndexedYAddressingMode() { mnemonic = "IY"; }
    uint16_t operator()(CPU& cpu) override;
};

// Relative Addressing Mode
class RelativeAddressingMode : public AddressingMode {
public:
    RelativeAddressingMode() { mnemonic = "REL"; }
    uint16_t operator()(CPU& cpu) override;
};

#endif
