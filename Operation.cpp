#include "Operation.h"
#include "CPU.h"
#include<iostream>

void LDAOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    cpu.setAccumulator(value);
    cpu.setZeroFlag(value == 0);
    cpu.setNegativeFlag(value & 0x80);
}

void LDXOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    cpu.setX(value);
    cpu.setZeroFlag(value == 0);
    cpu.setNegativeFlag(value & 0x80);
}

void LDYOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    cpu.setY(value);
    cpu.setZeroFlag(value == 0);
    cpu.setNegativeFlag(value & 0x80);
}

void STAOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.write(effectiveAddress, cpu.getAccumulator());
}

void STXOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.write(effectiveAddress, cpu.getX());
}

void STYOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.write(effectiveAddress, cpu.getY());
}

void ANDOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    uint8_t result = cpu.getAccumulator() & value;
    cpu.setAccumulator(result);
    cpu.setZeroFlag(result == 0);
    cpu.setNegativeFlag(result & 0x80);
}

void ORAOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    uint8_t result = cpu.getAccumulator() | value;
    cpu.setAccumulator(result);
    cpu.setZeroFlag(result == 0);
    cpu.setNegativeFlag(result & 0x80);
}

void EOROperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    uint8_t result = cpu.getAccumulator() ^ value;
    cpu.setAccumulator(result);
    cpu.setZeroFlag(result == 0);
    cpu.setNegativeFlag(result & 0x80);
}

void BITOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    cpu.setZeroFlag((cpu.getAccumulator() & value) == 0);
    cpu.setNegativeFlag(value & 0x80);
    cpu.setOverflowFlag(value & 0x40);
}

void ADCOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    uint16_t result = (uint16_t)cpu.getAccumulator() + (uint16_t)value + (cpu.getCarryFlag() ? 1 : 0);
    cpu.setCarryFlag(result > 0xFF);
    cpu.setZeroFlag((result & 0xFF) == 0);
    cpu.setNegativeFlag(result & 0x80);
    bool signBitSame = ((cpu.getAccumulator() ^ value) & 0x80) == 0;
    cpu.setOverflowFlag(signBitSame && ((cpu.getAccumulator() ^ result) & 0x80) != 0);
    cpu.setAccumulator(result & 0xFF);
}

void SBCOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    uint16_t result = (uint16_t)cpu.getAccumulator() - (uint16_t)value - (cpu.getCarryFlag() ? 0 : 1);
    cpu.setCarryFlag(result < 0x100);
    cpu.setZeroFlag((result & 0xFF) == 0);
    cpu.setNegativeFlag(result & 0x80);
    cpu.setOverflowFlag(((cpu.getAccumulator() & 0x80) != (value & 0x80)) && ((cpu.getAccumulator() & 0x80) != (result & 0x80)));
    cpu.setAccumulator(result & 0xFF);
}

void CMPOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    uint16_t result = cpu.getAccumulator() - value;
    cpu.setCarryFlag(cpu.getAccumulator() >= value);  // Carry flag set if A >= Operand
    cpu.setZeroFlag(result == 0);   // Zero flag if result is 0
    cpu.setNegativeFlag(result & 0x80);  // Negative flag if MSB is set
}

void CPXOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    uint16_t result = cpu.getX() - value;
    cpu.setCarryFlag(cpu.getX() >= value);  // Carry flag set if X >= Operand
    cpu.setZeroFlag(result == 0);   // Zero flag if result is 0
    cpu.setNegativeFlag(result & 0x80);  // Negative flag if MSB is set
}

void CPYOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    uint16_t result = cpu.getY() - value;
    cpu.setCarryFlag(cpu.getY() >= value);  // Carry flag set if Y >= Operand
    cpu.setZeroFlag(result == 0);   // Zero flag if result is 0
    cpu.setNegativeFlag(result & 0x80);  // Negative flag if MSB is set
}

void INCOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress) + 1;
    cpu.write(effectiveAddress, value);
    cpu.setZeroFlag(value == 0);
    cpu.setNegativeFlag(value & 0x80);
}

void DECOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress) - 1;
    cpu.write(effectiveAddress, value);
    cpu.setZeroFlag(value == 0);
    cpu.setNegativeFlag(value & 0x80);
}

void INXOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.getX() + 1;
    cpu.setX(value);
    cpu.setZeroFlag(value == 0);
    cpu.setNegativeFlag(value & 0x80);
}

void INYOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.getY() + 1;
    cpu.setY(value);
    cpu.setZeroFlag(value == 0);
    cpu.setNegativeFlag(value & 0x80);
}

void DEXOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.getX() - 1;
    cpu.setX(value);
    cpu.setZeroFlag(value == 0);
    cpu.setNegativeFlag(value & 0x80);
}

void DEYOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.getY() - 1;
    cpu.setY(value);
    cpu.setZeroFlag(value == 0);
    cpu.setNegativeFlag(value & 0x80);
}

void ASLOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    bool carry = (value >> 7) & 1;
    uint8_t result = value << 1;
    cpu.write(effectiveAddress, result);
    cpu.setCarryFlag(carry);
    cpu.setZeroFlag(result == 0);
    cpu.setNegativeFlag(result & 0x80);
}

void ASLOperation::operator()(CPU& cpu) const {
    uint8_t value = cpu.getAccumulator();
    bool carry = (value >> 7) & 1;
    uint8_t result = value << 1;
    cpu.setAccumulator(result);
    cpu.setCarryFlag(carry);
    cpu.setZeroFlag(result == 0);
    cpu.setNegativeFlag(result & 0x80);
}

void LSROperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    bool carry = value & 1;
    uint8_t result = value >> 1;
    cpu.write(effectiveAddress, result);
    cpu.setCarryFlag(carry);
    cpu.setZeroFlag(result == 0);
    cpu.setNegativeFlag(result & 0x80);
}

void LSROperation::operator()(CPU& cpu) const {
    uint8_t value = cpu.getAccumulator();
    bool carry = value & 1;
    uint8_t result = value >> 1;
    cpu.setAccumulator(result);
    cpu.setCarryFlag(carry);
    cpu.setZeroFlag(result == 0);
    cpu.setNegativeFlag(result & 0x80);
}

void ROROperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    bool carry = (value & 1);
    uint8_t result = (cpu.getCarryFlag() << 7) | (value >> 1);
    cpu.write(effectiveAddress, result);
    cpu.setCarryFlag(carry);
    cpu.setZeroFlag(result == 0);
    cpu.setNegativeFlag(result & 0x80);
}

void ROROperation::operator()(CPU& cpu) const {
    uint8_t value = cpu.getAccumulator();
    bool carry = value & 1;
    uint8_t result = (cpu.getCarryFlag() << 7) | (value >> 1);
    cpu.setAccumulator(result);
    cpu.setCarryFlag(carry);
    cpu.setZeroFlag(result == 0);
    cpu.setNegativeFlag(result & 0x80);
}

void ROLOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t value = cpu.read(effectiveAddress);
    bool carry = (value >> 7) & 1;
    uint8_t result = (value << 1) | (cpu.getCarryFlag());
    cpu.write(effectiveAddress, result);
    cpu.setCarryFlag(carry);
    cpu.setZeroFlag(result == 0);
    cpu.setNegativeFlag(result & 0x80);
}

void ROLOperation::operator()(CPU& cpu) const {
    uint8_t value = cpu.getAccumulator();
    bool carry = (value >> 7) & 1;
    uint8_t result = (value << 1) | (cpu.getCarryFlag());
    cpu.setAccumulator(result);
    cpu.setCarryFlag(carry);
    cpu.setZeroFlag(result == 0);
    cpu.setNegativeFlag(result & 0x80);
}

void BCCOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    if (!cpu.getCarryFlag()) {
        cpu.setPC(effectiveAddress);
    }
}

void BCSOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    if (cpu.getCarryFlag()) {
        cpu.setPC(effectiveAddress);
    }
}

void BEQOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    if (cpu.getZeroFlag()) {
        cpu.setPC(effectiveAddress);
    }
}

void BNEOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    if (!cpu.getZeroFlag()) {
        cpu.setPC(effectiveAddress);
    }
}

void BMIOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    if (cpu.getNegativeFlag()) {
        cpu.setPC(effectiveAddress);
    }
}

void BPLOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    if (!cpu.getNegativeFlag()) {
        cpu.setPC(effectiveAddress);
    }
}

void BVCOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    if (!cpu.getOverflowFlag()) {
        cpu.setPC(effectiveAddress);
    }
}

void BVSOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    if (cpu.getOverflowFlag()) {
        cpu.setPC(effectiveAddress);
    }
}

void JMPOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setPC(effectiveAddress);
}

void JSROperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    auto PCValue = cpu.getPC()-1;
    cpu.pushStack((PCValue >> 8) & 0xFF);
    cpu.pushStack(PCValue & 0xFF);
    cpu.setPC(effectiveAddress);
}

void RTSOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t low = cpu.pullStack();
    uint8_t high = cpu.pullStack();
    auto PCValue = ((high << 8) | low) + 1;
    cpu.setPC(PCValue);
}

void CLCOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setCarryFlag(false);
}

void SECOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setCarryFlag(true);
}

void CLDOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setDecimalFlag(false);
}

void SEDOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setDecimalFlag(true);
}

void CLIOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setInterruptDisableFlag(false);
}

void SEIOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setInterruptDisableFlag(true);
}

void CLVOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setOverflowFlag(false);
}

void TAXOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setX(cpu.getAccumulator());
    cpu.setZeroFlag(cpu.getX() == 0);
    cpu.setNegativeFlag(cpu.getX() & 0x80);
}

void TAYOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setY(cpu.getAccumulator());
    cpu.setZeroFlag(cpu.getY() == 0);
    cpu.setNegativeFlag(cpu.getY() & 0x80);
}

void TXAOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setAccumulator(cpu.getX());
    cpu.setZeroFlag(cpu.getAccumulator() == 0);
    cpu.setNegativeFlag(cpu.getAccumulator() & 0x80);
}

void TYAOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setAccumulator(cpu.getY());
    cpu.setZeroFlag(cpu.getAccumulator() == 0);
    cpu.setNegativeFlag(cpu.getAccumulator() & 0x80);
}

void TXSOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setSP(cpu.getX());
}

void TSXOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setX(cpu.getSP());
    cpu.setZeroFlag(cpu.getX() == 0);
    cpu.setNegativeFlag(cpu.getX() & 0x80);
}

void PHAOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.pushStack(cpu.getAccumulator());
}

void PHPOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setBreakFlag(true);
    cpu.setUnusedFlag(true);
    cpu.pushStack(cpu.getStatusRegister() );
}

void PLAOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setAccumulator(cpu.pullStack());
    cpu.setZeroFlag(cpu.getAccumulator() == 0);
    cpu.setNegativeFlag(cpu.getAccumulator() & 0x80);
}

void PLPOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    cpu.setStatusRegister(cpu.pullStack());
    cpu.setBreakFlag(false);
    cpu.setUnusedFlag(false);
}

void BRKOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    auto PCValue = cpu.getPC() + 1;
    cpu.pushStack((PCValue>> 8) & 0xFF);
    cpu.pushStack(PCValue& 0xFF);
    cpu.setBreakFlag(true);
    cpu.setUnusedFlag(true);
    cpu.pushStack(cpu.getStatusRegister());
    cpu.setInterruptDisableFlag(true);
    cpu.setPC(cpu.read(0xFFFE) | (cpu.read(0xFFFF) << 8));
}

void RTIOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    uint8_t status = cpu.pullStack();
    cpu.setStatusRegister(status);
    uint8_t low = cpu.pullStack();
    uint8_t high = cpu.pullStack();
    cpu.setPC((high << 8) | low);
}

void NOPOperation::operator()(CPU& cpu, uint16_t effectiveAddress) const {
    // No operation performed
}