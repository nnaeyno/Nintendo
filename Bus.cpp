#include "Bus.h"

Bus::Bus(){
    for(auto &bucket : ram) bucket = 0x00;

    cpu.connectToBus(this);
}

Bus::~Bus(){

}
//w
uint8_t Bus::read(uint16_t addr, bool readOnly){
    if(addr >= 0x0000 && addr <= 0xFFFF){
        return ram[addr];
    }
    return 0x00; 
}

void Bus::write(uint16_t addr, uint8_t data){
    if(addr >= 0x0000 && addr <= 0xFFFF){
        ram[addr] = data;
    }
}