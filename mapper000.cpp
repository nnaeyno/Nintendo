#include "mapper000.h"

Mapper000::Mapper000(uint8_t prgBanks, uint8_t chrBanks) : Mapper(prgBanks, chrBanks){

}

Mapper000::~Mapper000(){

}

bool Mapper000::cpuMapRead(uint16_t addr, uint32_t &mapped_addr){
    if(addr >= 0x8000 && addr <= 0xFFFF){
        if (nPRGBanks > 1) {
            mapped_addr = addr & 0x7FFF;
        } else {
            mapped_addr = addr & 0x3FFF;
        }
        return true;
    }
    return false;
}

bool Mapper000::cpuMapWrite(uint16_t addr, uint32_t &mapped_addr){
    if(addr >= 0x8000 && addr <= 0xFFFF){
        if (nPRGBanks > 1) {
            mapped_addr = addr & 0x7FFF;
        } else {
            mapped_addr = addr & 0x3FFF;
        }
        return true;
    } 
    return false;
}
   
bool Mapper000::ppuMapRead(uint16_t addr, uint32_t &mapped_addr){
    if(addr >= 0x0000 && addr <= 0x1FFF){
        mapped_addr = addr;
        return true;
    }
    return false;
}

bool Mapper000::ppuMapWrite(uint16_t addr, uint32_t &mapped_addr){
    if(addr >= 0x0000 && addr <= 0x1FFF){
        if(nCHRBanks == 0){
            mapped_addr = addr;
            return true;
        }
    }
    return false;
}