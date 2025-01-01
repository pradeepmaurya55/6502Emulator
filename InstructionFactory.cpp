#include "InstructionFactory.h"
#include "AddressingMode.h"
#include "Operation.h"
#include "CPU.h"

InstructionFactory* InstructionFactory::instance = nullptr;

InstructionFactory* InstructionFactory::getInstance() {
    if (instance == nullptr) {
        // Initialize the instance when first needed
        instance = new InstructionFactory();
    }
    return instance;
}

AddressingMode *InstructionFactory::getAddressingMode(AddressingModeType addressingModeType)
{
    AddressingMode* addressingMode;

    switch (addressingModeType) {
            case AddressingModeType::Implied:
                addressingMode = &implied;
                break;
            case AddressingModeType::Immediate:
                addressingMode = &immediate;
                break;
            case AddressingModeType::ZeroPage:
                addressingMode = &zeroPage;
                break;
            case AddressingModeType::Absolute:
                addressingMode = &absolute;
                break;
            case AddressingModeType::ZeroPageX:
                addressingMode = &zeroPageX;
                break;
            case AddressingModeType::ZeroPageY:
                addressingMode = &zeroPageY;
                break;
            case AddressingModeType::AbsoluteX:
                addressingMode = &absoluteX;
                break;
            case AddressingModeType::AbsoluteY:
                addressingMode = &absoluteY;
                break;
            case AddressingModeType::Indirect:
                addressingMode = &indirect;
                break;
            case AddressingModeType::IndexedIndirectX:
                addressingMode = &indexedIndirectX;
                break;
            case AddressingModeType::IndirectIndexedY:
                addressingMode = &indirectIndexedY;
                break;
            case AddressingModeType::Relative:
                addressingMode = &relative;
                break;
            default:
                addressingMode = nullptr;
                break;
        }

}

Operation *InstructionFactory::getOperation(OperationType operationType)
{
    Operation* operation = nullptr;

    switch (operationType) {
            case OperationType::LDA:
                operation = &lda;
                break;
            case OperationType::LDX:
                operation = &ldx;
                break;
            case OperationType::LDY:
                operation = &ldy;
                break;
            case OperationType::STA:
                operation = &sta;
                break;
            case OperationType::STX:
                operation = &stx;
                break;
            case OperationType::STY:
                operation = &sty;
                break;
            case OperationType::ADC:
                operation = &adc;
                break;
            case OperationType::SBC:
                operation = &sbc;
                break;
            case OperationType::CMP:
                operation = &cmp;
                break;
            case OperationType::CPX:
                operation = &cpx;
                break;
            case OperationType::CPY:
                operation = &cpy;
                break;
            case OperationType::AND:
                operation = &andOp;
                break;
            case OperationType::ORA:
                operation = &ora;
                break;
            case OperationType::EOR:
                operation = &eor;
                break;
            case OperationType::BIT:
                operation = &bit;
                break;
            case OperationType::INC:
                operation = &inc;
                break;
            case OperationType::DEC:
                operation = &dec;
                break;
            case OperationType::INX:
                operation = &inx;
                break;
            case OperationType::INY:
                operation = &iny;
                break;
            case OperationType::DEX:
                operation = &dex;
                break;
            case OperationType::DEY:
                operation = &dey;
                break;
            case OperationType::ASL:
                operation = &asl;
                break;
            case OperationType::LSR:
                operation = &lsr;
                break;
            case OperationType::ROR:
                operation = &ror;
                break;
            case OperationType::ROL:
                operation = &rol;
                break;
            case OperationType::BCC:
                operation = &bcc;
                break;
            case OperationType::BCS:
                operation = &bcs;
                break;
            case OperationType::BEQ:
                operation = &beq;
                break;
            case OperationType::BNE:
                operation = &bne;
                break;
            case OperationType::BMI:
                operation = &bmi;
                break;
            case OperationType::BPL:
                operation = &bpl;
                break;
            case OperationType::BVC:
                operation = &bvc;
                break;
            case OperationType::BVS:
                operation = &bvs;
                break;
            case OperationType::CLC:
                operation = &clc;
                break;
            case OperationType::SEC:
                operation = &sec;
                break;
            case OperationType::CLD:
                operation = &cld;
                break;
            case OperationType::SED:
                operation = &sed;
                break;
            case OperationType::CLI:
                operation = &cli;
                break;
            case OperationType::SEI:
                operation = &sei;
                break;
            case OperationType::CLV:
                operation = &clv;
                break;
            case OperationType::JMP:
                operation = &jmp;
                break;
            case OperationType::JSR:
                operation = &jsr;
                break;
            case OperationType::RTS:
                operation = &rts;
                break;
            case OperationType::NOP:
                operation = &nop;
                break;
            case OperationType::BRK:
                operation = &brk;
                break;
            case OperationType::RTI:
                operation = &rti;
                break;
            case OperationType::TAX:
                operation = &tax;
                break;
            case OperationType::TAY:
                operation = &tay;
                break;
            case OperationType::TYA:
                operation = &tya;
                break;
            case OperationType::TXA:
                operation = &txa;
                break;
            case OperationType::TXS:
                operation = &txs;
                break;
            case OperationType::TSX:
                operation = &tsx;
                break;
            case OperationType::PHA:
                operation = &pha;
                break;
            case OperationType::PHP:
                operation = &php;
                break;
            case OperationType::PLA:
                operation = &pla;
                break;
            case OperationType::PLP:
                operation = &plp;
                break;
            default:
                operation = nullptr;
                break;
        }
        
}

Instruction *InstructionFactory::createInstruction(uint8_t opcode)
{
    auto it = instructionMap.find(opcode);
    if (it != instructionMap.end()) {
        AddressingModeType addressingModeType = it->second.first;
        OperationType operationType = it->second.second;

        AddressingMode* addressingMode = getAddressingMode(addressingModeType);    
        Operation* operation = getOperation(operationType);
        
        if (auto accumulatorOp = dynamic_cast<AccumulatorOperation*>(operation)) {
            if (addressingModeType == AddressingModeType::Accumulator) {
                return new AccumulatorInstruction(accumulatorOp);
            } else {
                return new AddressedInstruction(addressingMode, operation);
            }
        } else {
            return new AddressedInstruction(addressingMode, operation);
        }
    } else {
        return nullptr;
    }
}

InstructionFactory::InstructionFactory() {

    //Load & Store Operations
    // LDA - Load Accumulator
    instructionMap[0xA9] = std::make_pair(AddressingModeType::Immediate, OperationType::LDA);   // LDA Immediate
    instructionMap[0xA5] = std::make_pair(AddressingModeType::ZeroPage, OperationType::LDA);   // LDA ZeroPage
    instructionMap[0xA1] = std::make_pair(AddressingModeType::IndexedIndirectX, OperationType::LDA);  // LDA (Indirect,X)
    instructionMap[0xAD] = std::make_pair(AddressingModeType::Absolute, OperationType::LDA);  // LDA Absolute
    instructionMap[0xB5] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::LDA); // LDA ZeroPage,X
    instructionMap[0xB1] = std::make_pair(AddressingModeType::IndirectIndexedY, OperationType::LDA); // LDA (Indirect),Y
    instructionMap[0xBD] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::LDA);  // LDA Absolute,X
    instructionMap[0xB9] = std::make_pair(AddressingModeType::AbsoluteY, OperationType::LDA);  // LDA Absolute,Y

    // LDX - Load X Register
    instructionMap[0xA2] = std::make_pair(AddressingModeType::Immediate, OperationType::LDX);  // LDX Immediate
    instructionMap[0xA6] = std::make_pair(AddressingModeType::ZeroPage, OperationType::LDX);   // LDX ZeroPage
    instructionMap[0xAE] = std::make_pair(AddressingModeType::Absolute, OperationType::LDX);   // LDX Absolute
    instructionMap[0xB6] = std::make_pair(AddressingModeType::ZeroPageY, OperationType::LDX);  // LDX ZeroPage,Y
    instructionMap[0xBE] = std::make_pair(AddressingModeType::AbsoluteY, OperationType::LDX);  // LDX Absolute,Y

    // LDY - Load Y Register
    instructionMap[0xA0] = std::make_pair(AddressingModeType::Immediate, OperationType::LDY);  // LDY Immediate
    instructionMap[0xA4] = std::make_pair(AddressingModeType::ZeroPage, OperationType::LDY);   // LDY ZeroPage
    instructionMap[0xAC] = std::make_pair(AddressingModeType::Absolute, OperationType::LDY);   // LDY Absolute
    instructionMap[0xB4] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::LDY);  // LDY ZeroPage,X
    instructionMap[0xBC] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::LDY);  // LDY Absolute,X

    // STA - Store Accumulator
    instructionMap[0x8D] = std::make_pair(AddressingModeType::Absolute, OperationType::STA);    // STA Absolute
    instructionMap[0x85] = std::make_pair(AddressingModeType::ZeroPage, OperationType::STA);    // STA ZeroPage
    instructionMap[0x81] = std::make_pair(AddressingModeType::IndexedIndirectX, OperationType::STA); // STA (Indirect,X)
    instructionMap[0x95] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::STA);   // STA ZeroPage,X
    instructionMap[0x91] = std::make_pair(AddressingModeType::IndirectIndexedY, OperationType::STA); // STA (Indirect),Y
    instructionMap[0x99] = std::make_pair(AddressingModeType::AbsoluteY, OperationType::STA);   // STA Absolute,Y
    instructionMap[0x9D] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::STA);   // STA Absolute,X

    // STX - Store X Register
    instructionMap[0x8E] = std::make_pair(AddressingModeType::Absolute, OperationType::STX);    // STX Absolute
    instructionMap[0x86] = std::make_pair(AddressingModeType::ZeroPage, OperationType::STX);    // STX ZeroPage
    instructionMap[0x96] = std::make_pair(AddressingModeType::ZeroPageY, OperationType::STX);   // STX ZeroPage,Y

    // STY - Store Y Register
    instructionMap[0x8C] = std::make_pair(AddressingModeType::Absolute, OperationType::STY);    // STY Absolute
    instructionMap[0x84] = std::make_pair(AddressingModeType::ZeroPage, OperationType::STY);    // STY ZeroPage
    instructionMap[0x94] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::STY);   // STY ZeroPage,X

    // Transfer Operations
    instructionMap[0xAA] = std::make_pair(AddressingModeType::Implied, OperationType::TAX);  // TAX
    instructionMap[0xA8] = std::make_pair(AddressingModeType::Implied, OperationType::TAY);  // TAY
    instructionMap[0x8A] = std::make_pair(AddressingModeType::Implied, OperationType::TXA);  // TXA
    instructionMap[0x98] = std::make_pair(AddressingModeType::Implied, OperationType::TYA);  // TYA

    // Stack Operations
    instructionMap[0xBA] = std::make_pair(AddressingModeType::Implied, OperationType::TSX);  // TSX
    instructionMap[0x9A] = std::make_pair(AddressingModeType::Implied, OperationType::TXS);  // TXS
    instructionMap[0x48] = std::make_pair(AddressingModeType::Implied, OperationType::PHA);  // PHA
    instructionMap[0x08] = std::make_pair(AddressingModeType::Implied, OperationType::PHP);  // PHP
    instructionMap[0x68] = std::make_pair(AddressingModeType::Implied, OperationType::PLA);  // PLA
    instructionMap[0x28] = std::make_pair(AddressingModeType::Implied, OperationType::PLP);  // PLP


    // Logical Instructions
    // AND - Logical AND
    instructionMap[0x29] = std::make_pair(AddressingModeType::Immediate, OperationType::AND);  // AND Immediate
    instructionMap[0x25] = std::make_pair(AddressingModeType::ZeroPage, OperationType::AND);  // AND ZeroPage
    instructionMap[0x21] = std::make_pair(AddressingModeType::IndexedIndirectX, OperationType::AND);  // AND (Indirect,X)
    instructionMap[0x2D] = std::make_pair(AddressingModeType::Absolute, OperationType::AND);  // AND Absolute
    instructionMap[0x35] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::AND);  // AND ZeroPage,X
    instructionMap[0x31] = std::make_pair(AddressingModeType::IndirectIndexedY, OperationType::AND);  // AND (Indirect),Y
    instructionMap[0x3D] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::AND);  // AND Absolute,X
    instructionMap[0x39] = std::make_pair(AddressingModeType::AbsoluteY, OperationType::AND);  // AND Absolute,Y

    // EOR - Exclusive OR
    instructionMap[0x49] = std::make_pair(AddressingModeType::Immediate, OperationType::EOR);  // EOR Immediate
    instructionMap[0x45] = std::make_pair(AddressingModeType::ZeroPage, OperationType::EOR);  // EOR ZeroPage
    instructionMap[0x41] = std::make_pair(AddressingModeType::IndexedIndirectX, OperationType::EOR);  // EOR (Indirect,X)
    instructionMap[0x4D] = std::make_pair(AddressingModeType::Absolute, OperationType::EOR);  // EOR Absolute
    instructionMap[0x55] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::EOR);  // EOR ZeroPage,X
    instructionMap[0x51] = std::make_pair(AddressingModeType::IndirectIndexedY, OperationType::EOR);  // EOR (Indirect),Y
    instructionMap[0x5D] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::EOR);  // EOR Absolute,X
    instructionMap[0x59] = std::make_pair(AddressingModeType::AbsoluteY, OperationType::EOR);  // EOR Absolute,Y

    // ORA - Logical OR
    instructionMap[0x09] = std::make_pair(AddressingModeType::Immediate, OperationType::ORA);  // ORA Immediate
    instructionMap[0x05] = std::make_pair(AddressingModeType::ZeroPage, OperationType::ORA);  // ORA ZeroPage
    instructionMap[0x01] = std::make_pair(AddressingModeType::IndexedIndirectX, OperationType::ORA);  // ORA (Indirect,X)
    instructionMap[0x0D] = std::make_pair(AddressingModeType::Absolute, OperationType::ORA);  // ORA Absolute
    instructionMap[0x15] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::ORA);  // ORA ZeroPage,X
    instructionMap[0x11] = std::make_pair(AddressingModeType::IndirectIndexedY, OperationType::ORA);  // ORA (Indirect),Y
    instructionMap[0x1D] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::ORA);  // ORA Absolute,X
    instructionMap[0x19] = std::make_pair(AddressingModeType::AbsoluteY, OperationType::ORA);  // ORA Absolute,Y

    // BIT - Bit Test
    instructionMap[0x24] = std::make_pair(AddressingModeType::ZeroPage, OperationType::BIT);  // BIT ZeroPage
    instructionMap[0x2C] = std::make_pair(AddressingModeType::Absolute, OperationType::BIT);  // BIT Absolute

    // Arithmetic Operations
    // ADC - Add with Carry
    instructionMap[0x69] = std::make_pair(AddressingModeType::Immediate, OperationType::ADC);  // ADC Immediate
    instructionMap[0x65] = std::make_pair(AddressingModeType::ZeroPage, OperationType::ADC);  // ADC ZeroPage
    instructionMap[0x75] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::ADC);  // ADC ZeroPage,X
    instructionMap[0x6D] = std::make_pair(AddressingModeType::Absolute, OperationType::ADC);  // ADC Absolute
    instructionMap[0x7D] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::ADC);  // ADC Absolute,X
    instructionMap[0x79] = std::make_pair(AddressingModeType::AbsoluteY, OperationType::ADC);  // ADC Absolute,Y
    instructionMap[0x61] = std::make_pair(AddressingModeType::IndexedIndirectX, OperationType::ADC);  // ADC (Indirect,X)
    instructionMap[0x71] = std::make_pair(AddressingModeType::IndirectIndexedY, OperationType::ADC);  // ADC (Indirect),Y

    // SBC - Subtract with Carry
    instructionMap[0xE9] = std::make_pair(AddressingModeType::Immediate, OperationType::SBC);  // SBC Immediate
    instructionMap[0xE5] = std::make_pair(AddressingModeType::ZeroPage, OperationType::SBC);  // SBC ZeroPage
    instructionMap[0xF5] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::SBC);  // SBC ZeroPage,X
    instructionMap[0xED] = std::make_pair(AddressingModeType::Absolute, OperationType::SBC);  // SBC Absolute
    instructionMap[0xFD] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::SBC);  // SBC Absolute,X
    instructionMap[0xF9] = std::make_pair(AddressingModeType::AbsoluteY, OperationType::SBC);  // SBC Absolute,Y
    instructionMap[0xE1] = std::make_pair(AddressingModeType::IndexedIndirectX, OperationType::SBC);  // SBC (Indirect,X)
    instructionMap[0xF1] = std::make_pair(AddressingModeType::IndirectIndexedY, OperationType::SBC);  // SBC (Indirect),Y

    // CMP - Compare Accumulator
    instructionMap[0xC9] = std::make_pair(AddressingModeType::Immediate, OperationType::CMP);  // CMP Immediate
    instructionMap[0xC5] = std::make_pair(AddressingModeType::ZeroPage, OperationType::CMP);  // CMP ZeroPage
    instructionMap[0xD5] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::CMP);  // CMP ZeroPage,X
    instructionMap[0xCD] = std::make_pair(AddressingModeType::Absolute, OperationType::CMP);  // CMP Absolute
    instructionMap[0xDD] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::CMP);  // CMP Absolute,X
    instructionMap[0xD9] = std::make_pair(AddressingModeType::AbsoluteY, OperationType::CMP);  // CMP Absolute,Y
    instructionMap[0xC1] = std::make_pair(AddressingModeType::IndexedIndirectX, OperationType::CMP);  // CMP (Indirect,X)
    instructionMap[0xD1] = std::make_pair(AddressingModeType::IndirectIndexedY, OperationType::CMP);  // CMP (Indirect),Y

    // CPX - Compare X Register
    instructionMap[0xE0] = std::make_pair(AddressingModeType::Immediate, OperationType::CPX);  // CPX Immediate
    instructionMap[0xE4] = std::make_pair(AddressingModeType::ZeroPage, OperationType::CPX);  // CPX ZeroPage
    instructionMap[0xEC] = std::make_pair(AddressingModeType::Absolute, OperationType::CPX);  // CPX Absolute

    // CPY - Compare Y Register
    instructionMap[0xC0] = std::make_pair(AddressingModeType::Immediate, OperationType::CPY);  // CPY Immediate
    instructionMap[0xC4] = std::make_pair(AddressingModeType::ZeroPage, OperationType::CPY);  // CPY ZeroPage
    instructionMap[0xCC] = std::make_pair(AddressingModeType::Absolute, OperationType::CPY);  // CPY Absolute

    // Increment and Decrement Operations
    // INC - Increment a memory location
    instructionMap[0xE6] = std::make_pair(AddressingModeType::ZeroPage, OperationType::INC);  // INC ZeroPage
    instructionMap[0xF6] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::INC);  // INC ZeroPage,X
    instructionMap[0xEE] = std::make_pair(AddressingModeType::Absolute, OperationType::INC);  // INC Absolute
    instructionMap[0xFE] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::INC);  // INC Absolute,X

    // INX - Increment the X register
    instructionMap[0xE8] = std::make_pair(AddressingModeType::Implied, OperationType::INX);  // INX

    // INY - Increment the Y register
    instructionMap[0xC8] = std::make_pair(AddressingModeType::Implied, OperationType::INY);  // INY

    // DEC - Decrement a memory location
    instructionMap[0xC6] = std::make_pair(AddressingModeType::ZeroPage, OperationType::DEC);  // DEC ZeroPage
    instructionMap[0xD6] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::DEC);  // DEC ZeroPage,X
    instructionMap[0xCE] = std::make_pair(AddressingModeType::Absolute, OperationType::DEC);  // DEC Absolute
    instructionMap[0xDE] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::DEC);  // DEC Absolute,X

    // DEX - Decrement the X register
    instructionMap[0xCA] = std::make_pair(AddressingModeType::Implied, OperationType::DEX);  // DEX

    // DEY - Decrement the Y register
    instructionMap[0x88] = std::make_pair(AddressingModeType::Implied, OperationType::DEY);  // DEY

    // Shift and Rotate Operations
    // ASL - Arithmetic Shift Left
    instructionMap[0x0A] = std::make_pair(AddressingModeType::Accumulator, OperationType::ASL);  // ASL Accumulator
    instructionMap[0x06] = std::make_pair(AddressingModeType::ZeroPage, OperationType::ASL);  // ASL ZeroPage
    instructionMap[0x16] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::ASL);  // ASL ZeroPage,X
    instructionMap[0x0E] = std::make_pair(AddressingModeType::Absolute, OperationType::ASL);  // ASL Absolute
    instructionMap[0x1E] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::ASL);  // ASL Absolute,X

    // LSR - Logical Shift Right
    instructionMap[0x4A] = std::make_pair(AddressingModeType::Accumulator, OperationType::LSR);  // LSR Accumulator
    instructionMap[0x46] = std::make_pair(AddressingModeType::ZeroPage, OperationType::LSR);  // LSR ZeroPage
    instructionMap[0x56] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::LSR);  // LSR ZeroPage,X
    instructionMap[0x4E] = std::make_pair(AddressingModeType::Absolute, OperationType::LSR);  // LSR Absolute
    instructionMap[0x5E] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::LSR);  // LSR Absolute,X

    // ROL - Rotate Left
    instructionMap[0x2A] = std::make_pair(AddressingModeType::Accumulator, OperationType::ROL);  // ROL Accumulator
    instructionMap[0x26] = std::make_pair(AddressingModeType::ZeroPage, OperationType::ROL);  // ROL ZeroPage
    instructionMap[0x36] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::ROL);  // ROL ZeroPage,X
    instructionMap[0x2E] = std::make_pair(AddressingModeType::Absolute, OperationType::ROL);  // ROL Absolute
    instructionMap[0x3E] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::ROL);  // ROL Absolute,X

    // ROR - Rotate Right
    instructionMap[0x6A] = std::make_pair(AddressingModeType::Accumulator, OperationType::ROR);  // ROR Accumulator
    instructionMap[0x66] = std::make_pair(AddressingModeType::ZeroPage, OperationType::ROR);  // ROR ZeroPage
    instructionMap[0x76] = std::make_pair(AddressingModeType::ZeroPageX, OperationType::ROR);  // ROR ZeroPage,X
    instructionMap[0x6E] = std::make_pair(AddressingModeType::Absolute, OperationType::ROR);  // ROR Absolute
    instructionMap[0x7E] = std::make_pair(AddressingModeType::AbsoluteX, OperationType::ROR);  // ROR Absolute,X

    // Jump and Subroutine Operations
    // JMP - Jump to another location
    instructionMap[0x4C] = std::make_pair(AddressingModeType::Absolute, OperationType::JMP);  // JMP Absolute
    instructionMap[0x6C] = std::make_pair(AddressingModeType::Indirect, OperationType::JMP);  // JMP Indirect

    // JSR - Jump to a subroutine
    instructionMap[0x20] = std::make_pair(AddressingModeType::Absolute, OperationType::JSR);  // JSR Absolute

    // RTS - Return from subroutine
    instructionMap[0x60] = std::make_pair(AddressingModeType::Implied, OperationType::RTS);  // RTS

    // Branches
    instructionMap[0x90] = std::make_pair(AddressingModeType::Relative, OperationType::BCC);  // BCC - Branch if carry flag clear
    instructionMap[0xB0] = std::make_pair(AddressingModeType::Relative, OperationType::BCS);  // BCS - Branch if carry flag set
    instructionMap[0xF0] = std::make_pair(AddressingModeType::Relative, OperationType::BEQ);  // BEQ - Branch if zero flag set
    instructionMap[0x30] = std::make_pair(AddressingModeType::Relative, OperationType::BMI);  // BMI - Branch if negative flag set
    instructionMap[0xD0] = std::make_pair(AddressingModeType::Relative, OperationType::BNE);  // BNE - Branch if zero flag clear
    instructionMap[0x10] = std::make_pair(AddressingModeType::Relative, OperationType::BPL);  // BPL - Branch if negative flag clear
    instructionMap[0x50] = std::make_pair(AddressingModeType::Relative, OperationType::BVC);  // BVC - Branch if overflow flag clear
    instructionMap[0x70] = std::make_pair(AddressingModeType::Relative, OperationType::BVS);  // BVS - Branch if overflow flag set

    // Status Flag Changes
    instructionMap[0x18] = std::make_pair(AddressingModeType::Implied, OperationType::CLC);  // CLC - Clear carry flag
    instructionMap[0xD8] = std::make_pair(AddressingModeType::Implied, OperationType::CLD);  // CLD - Clear decimal mode flag
    instructionMap[0x58] = std::make_pair(AddressingModeType::Implied, OperationType::CLI);  // CLI - Clear interrupt disable flag
    instructionMap[0xB8] = std::make_pair(AddressingModeType::Implied, OperationType::CLV);  // CLV - Clear overflow flag
    instructionMap[0x38] = std::make_pair(AddressingModeType::Implied, OperationType::SEC);  // SEC - Set carry flag
    instructionMap[0xF8] = std::make_pair(AddressingModeType::Implied, OperationType::SED);  // SED - Set decimal mode flag
    instructionMap[0x78] = std::make_pair(AddressingModeType::Implied, OperationType::SEI);  // SEI - Set interrupt disable flag

    // System Functions
    instructionMap[0x00] = std::make_pair(AddressingModeType::Implied, OperationType::BRK);  // BRK - Force an interrupt
    instructionMap[0xEA] = std::make_pair(AddressingModeType::Implied, OperationType::NOP);  // NOP - No operation
    instructionMap[0x40] = std::make_pair(AddressingModeType::Implied, OperationType::RTI);  // RTI - Return from interrupt

}