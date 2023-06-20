#pragma once

#include<cstdint>
#include<array>

#include "CPU.h"

using namespace std;

class Bus {
    public: 
        Bus();
        ~Bus();
        CPU cpu;
        array<uint8_t, 64 * 1024> ram;
        void write(uint16_t addr, uint8_t data);
        uint8_t read(uint16_t addr, bool readOnly = false);

};