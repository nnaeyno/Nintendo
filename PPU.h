#include <cstdint>
#include <iostream>
#include "cartridge.h"

using namespace std;
class PPU {
    private:		
	    uint8_t nameTable[2][Cartridge::ONE_KILOBYTE];  // two kilobytes 
        uint8_t	paletteTable[32]; //colors
        uint8_t patternTable[2][Cartridge::FOUR_KILOBYTES];
	    
    public:
        PPU();
        ~PPU();

        static const int MAX_PPU = 0x3FFF;
        static const int MIN_PPU = 0x2000;

        uint8_t read(uint16_t addr, bool RDONLY=false); //CPURead 
        uint8_t ppuRead(uint16_t addr, bool RDONLY=false);

        void write(uint16_t addr, uint8_t data); //CPUWrite
        void ppuWrite(uint16_t addr, uint8_t data);

        void connectCartridge(const std::shared_ptr<Cartridge>& cartridge);
	    void clock(); //count one system tick 

};