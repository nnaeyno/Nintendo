#include <cstdint>
#include "PPU.h"


uint8_t PPU::read(uint16_t addr, bool RDONLY) {
    uint8_t data = 00;

    switch (addr)
    {
    case 0000: // Control
        break;
    case 0001: // Mask
        break;
    case 0002: // Status
        break;
    case 0003: // OAM Address
        break;
    case 0004: // OAM Data
        break;
    case 0005: // Scroll
        break;
    case 0006: // PPU Address
        break;
    case 0007: // PPU Data
        break;
    }

    return data;
}

void PPU::write(uint16_t addr, uint8_t data) {
    switch (addr)
    {
    case 0000: // Control
        break;
    case 0001: // Mask
        break;
    case 0002: // Status
        break;
    case 0003: // OAM Address
        break;
    case 0004: // OAM Data
        break;
    case 0005: // Scroll
        break;
    case 0006: // PPU Address
        break;
    case 0007: // PPU Data
        break;
    }
}

/*
    placeholders for now
    masking the address if addr is outside the range
*/
uint8_t PPU::ppuRead(uint16_t addr, bool rdonly) {
    uint8_t data = 00;
    addr &= MAX_PPU;

    return data;
}

void PPU::ppuWrite(uint16_t addr, uint8_t data) {
    addr &= MAX_PPU;

}


void PPU::connectCartridge(const std::shared_ptr<Cartridge>& cartridge) {
	this->cart = cartridge;
}

void PPU::clock() {

	// Fake some noise for now
	// sprScreen->SetPixel(cycle - 1, scanline, screen[(rand() % 2) ? 3F : 30]);

	// Advance renderer - it never stops, it's relentless
	cycle++;
	if (cycle >= 341)
	{
		cycle = 0;
		scanline++;
		if (scanline >= 261)
		{
			scanline = -1;
			//frame_complete = true;
		}
	}
}