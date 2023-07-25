#include "Bus.h"
#include "cartridge.h"

/*

Bus class is representation of a connector that 
let's CPU, PPU, RAM and other components to talk to 
each other and exchange information. This allows our system
to have better isolation between components. 

*/

Bus::Bus(){

    cpu.connectToBus(this);
}

Bus::~Bus(){

}
/**
 * @brief CPU's read 
 * 
 * @param addr where to read
 * @param readOnly defining permissions
 * @return uint8_t data read from address provided
 */
uint8_t Bus::read(uint16_t addr, bool readOnly){
    uint8_t data = 0x00;
    if(cart->read(addr, data)){

    }else if(addr >= 0x0000 && addr <= MAX_CPU){
        data = cpuRam[addr & 0x07FF];
    }else if(addr >= 0x2000 && addr <= PPU::MAX_PPU){
        ppu.read(addr & 0x0007, readOnly);
    }else if(addr >= 0x4016 && addr <= 0x4017){
        // read status of the CPU-PPU connection
        data = (controller_state[addr & 0x0001] & 0x80) > 0;
        controller_state[addr & 0x0001] <<= 1;
    }
    return data; 
}

void Bus::write(uint16_t addr, uint8_t data){
    if(cart ->write(addr, data)){ // boolean if cartridge is handeling that read and write

    }else if(addr >= MIN_CPU && addr <= MAX_CPU){
        cpuRam[addr & 0x07FF] = data;

    }else if(addr >= PPU::MIN_PPU && addr <= PPU::MAX_PPU){
        ppu.write(addr & 0x0007, data);
    }else if(addr == 0x4014){
        dma_page = data;
        dma_addr = 0x00;
        dma_transfer = true;
    }else if(addr >= 0x4016 && addr <= 0x4017){
        controller_state[addr & 0x0001] = controller[addr & 0x0001];
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
/**
 * @brief 
 * in what sequence th einstructions 
 * should be executed and updating the status 
 * PPU is 3 times faster than CPU (thus the
 * if statements)
 * 
 */
void Bus::clock(){
    ppu.clock();
    if(numSystemClockCounter % 3 == 0){
        if(dma_transfer){
            if (dma_dummy){
				if (numSystemClockCounter % 2 == 1){
					dma_dummy = false;
				}
			}else{
                if (numSystemClockCounter % 2 == 0){
					dma_data = read(dma_page << 8 | dma_addr);
				}else{
					ppu.pOAM[dma_addr] = dma_data;
                    dma_addr++;
					if (dma_addr == 0x00)
					{
						dma_transfer = false;
						dma_dummy = true;
					}
				}

            }
        }else{
            cpu.clock();
        }
        
    }
    // if clock cycle is an interrupt
    if (ppu.nmi){
	 	ppu.nmi = false;
		cpu.nmi();
	}

    numSystemClockCounter++;
}