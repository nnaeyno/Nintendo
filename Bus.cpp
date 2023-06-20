#include "Bus.h"

Bus::Bus(){
   // for(auto &bucket : cpuRam) bucket = 0x00;

    cpu.connectToBus(this);
}

Bus::~Bus(){

}

uint8_t Bus::read(uint16_t addr, bool readOnly){
    uint8_t data = 0x00;
    if(cart->read(addr, data)){

    }else if(addr >= 0x0000 && addr <= 0x1FFF){
        data = cpuRam[addr & 0x07FF];
    }else if(addr >= 0x2000 && addr <= 0x3FFF){
        ppu.read(addr & 0x0007, data);
    }
    return data; 
}

void Bus::write(uint16_t addr, uint8_t data){
    if(cart ->write(addr, data)){

    }else if(addr >= 0x0000 && addr <= 0xFFFF){
        cpuRam[addr & 0x07FF] = data;
    }else if(addr >= 0x2000 && addr <= 0x3FFF){
        ppu.write(addr & 0x0007, data);
    }
}
  

void Bus::reset(){
    cpu.reset();
    nSystemClockCounter = 0;
}

void Bus::insertCartridge(const std::shared_ptr<cartridge>& cartridge)
{
	this->cart = cartridge;
	ppu.ConnectCartridge(cartridge);
}

void Bus::clock(){
    ppu.clock();
    if(nSystemClockCounter % 3 == 0){
        cpu.clock();
    }
    nSystemClockCounter++;
}