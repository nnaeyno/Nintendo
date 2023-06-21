#include "Bus.h"
#include "cartridge.h"


Bus::Bus(){
   // for(auto &bucket : cpuRam) bucket = 0x00;

    cpu.connectToBus(this);
}

Bus::~Bus(){

}

uint8_t Bus::read(uint16_t addr, bool readOnly){
    uint8_t data = 0x00;
    if(cart->read(addr, data)){

    }else if(addr >= 0x0000 && addr <= MAX_CPU){
        data = cpuRam[addr & 0x07FF];
    }else if(addr >= 0x2000 && addr <= PPU::MAX_PPU){
        ppu.read(addr & 0x0007, data);
    }
    return data; 
}

void Bus::write(uint16_t addr, uint8_t data){
    if(cart ->write(addr, data)){ // boolean if cartridge is handeling that read and write

    }else if(addr >= MIN_CPU && addr <= MAX_CPU){
        cpuRam[addr & 0x07FF] = data;

    }else if(addr >= PPU::MIN_PPU && addr <= PPU::MAX_PPU){
        ppu.write(addr & 0x0007, data);
    }
}
  

void Bus::reset(){
    cpu.reset();
    numSystemClockCounter = 0;
}

void Bus::insertCartridge(const std::shared_ptr<Cartridge>& cartridge)
{
	this->cart = cartridge;
	ppu.connectCartridge(cartridge);
}

void Bus::clock(){
    ppu.clock();
    if(numSystemClockCounter % 3 == 0){
        cpu.clock();
    }
    numSystemClockCounter++;
}