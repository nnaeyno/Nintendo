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

        static const int MAX_CPU = 0x1FFF;
        static const int MIN_CPU = 0x0000;

        CPU cpu;
        PPU ppu;
        shared_ptr<Cartridge> cart; //shared_ptr
        uint8_t cpuRam[2048];
        void write(uint16_t addr, uint8_t data);
        uint8_t read(uint16_t addr, bool readOnly = false);
        void insertCartridge(const shared_ptr<Cartridge>& cartridge);
        void reset();
        void clock(); //system tick
    
    private: 
        uint32_t numSystemClockCounter = 0;
    
};

