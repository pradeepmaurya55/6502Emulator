#include <iostream>
#include <cassert>
#include <string>
#include "Bus.h"
#include "CPU.h"
#include "Memory.h"

int main() {
    Memory memory;
    Bus bus(memory);
    CPU cpu(bus);

    std::string programPath = "C:\\Users\\impm7\\Desktop\\6502\\6502_functional_test.bin";

    memory.loadProgram(programPath, 0x000a);
    cpu.reset();
    cpu.setPC(0x400);

    bool running = true;

    while (running) {
        try {
            cpu.execute();
            
            if (cpu.getPC() > 0xFFFF) {
                std::cerr << "Error: Program counter out of bounds (0x" << std::hex << cpu.getPC() << ")." << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error: Exception caught during execution - " << e.what() << std::endl;
        }
        
    }
    std::cout << "\nFinal CPU State:" << std::endl;
    cpu.printState();
    return 0;
}


