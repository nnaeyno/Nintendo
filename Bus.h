#pragma once

#include<cstdint>
#include<array>
#include <iostream>
#include <memory>

#include "CPU.h"
#include "PPU.h"
#include "cartridge.h"

using namespace std;

class Bus {
    public: 
        Bus();
        ~Bus();
        CPU cpu;
        PPU ppu;
        shared_ptr<cartridge> cart;
        uint8_t cpuRam[2048];
        void write(uint16_t addr, uint8_t data);
        uint8_t read(uint16_t addr, bool readOnly = false);
        void insertCartridge(const shared_ptr<cartridge>& cartridge);
        void reset();
        void clock();
    
    private: 
        uint32_t nSystemClockCounter = 0;
    
};

