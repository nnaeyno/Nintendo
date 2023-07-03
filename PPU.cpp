#include <cstdint>
#include "PPU.h"

PPU::PPU(){
    screen[0]  = olc::Pixel(84, 84, 84);
	screen[1]  = olc::Pixel(0, 30, 116);
	screen[2]  = olc::Pixel(8, 16, 144);
	screen[3]  = olc::Pixel(48, 0, 136);
	screen[4]  = olc::Pixel(68, 0, 100);
	screen[5]  = olc::Pixel(92, 0, 48);
	screen[6]  = olc::Pixel(84, 4, 0);
	screen[7]  = olc::Pixel(60, 24, 0);
	screen[8]  = olc::Pixel(32, 42, 0);
	screen[9]  = olc::Pixel(8, 58, 0);
	screen[10] = olc::Pixel(0, 64, 0);
	screen[11] = olc::Pixel(0, 60, 0);
	screen[12] = olc::Pixel(0, 50, 60);
	screen[13] = olc::Pixel(0, 0, 0);
	screen[14] = olc::Pixel(0, 0, 0);
	screen[15] = olc::Pixel(0, 0, 0);

	screen[16] = olc::Pixel(152, 150, 152);
	screen[17] = olc::Pixel(8, 76, 196);
	screen[18] = olc::Pixel(48, 50, 236);
	screen[19] = olc::Pixel(92, 30, 228);
	screen[20] = olc::Pixel(136, 20, 176);
	screen[21] = olc::Pixel(160, 20, 100);
	screen[22] = olc::Pixel(152, 34, 32);
	screen[23] = olc::Pixel(120, 60, 0);
	screen[24] = olc::Pixel(84, 90, 0);
	screen[25] = olc::Pixel(40, 114, 0);
	screen[26] = olc::Pixel(8, 124, 0);
	screen[27] = olc::Pixel(0, 118, 40);
	screen[28] = olc::Pixel(0, 102, 120);
	screen[29] = olc::Pixel(0, 0, 0);
	screen[30] = olc::Pixel(0, 0, 0);
	screen[31] = olc::Pixel(0, 0, 0);

	screen[32] = olc::Pixel(236, 238, 236);
	screen[33] = olc::Pixel(76, 154, 236);
	screen[34] = olc::Pixel(120, 124, 236);
	screen[35] = olc::Pixel(176, 98, 236);
	screen[36] = olc::Pixel(228, 84, 236);
	screen[37] = olc::Pixel(236, 88, 180);
	screen[38] = olc::Pixel(236, 106, 100);
	screen[39] = olc::Pixel(212, 136, 32);
	screen[40] = olc::Pixel(160, 170, 0);
	screen[41] = olc::Pixel(116, 196, 0);
	screen[42] = olc::Pixel(76, 208, 32);
	screen[43] = olc::Pixel(56, 204, 108);
	screen[44] = olc::Pixel(56, 180, 204);
	screen[45] = olc::Pixel(60, 60, 60);
	screen[46] = olc::Pixel(0, 0, 0);
	screen[47] = olc::Pixel(0, 0, 0);

	screen[48] = olc::Pixel(236, 238, 236);
	screen[49] = olc::Pixel(168, 204, 236);
	screen[50] = olc::Pixel(188, 188, 236);
	screen[51] = olc::Pixel(212, 178, 236);
	screen[52] = olc::Pixel(236, 174, 236);
	screen[53] = olc::Pixel(236, 174, 212);
	screen[54] = olc::Pixel(236, 180, 176);
	screen[55] = olc::Pixel(228, 196, 144);
	screen[56] = olc::Pixel(204, 210, 120);
	screen[57] = olc::Pixel(180, 222, 120);
	screen[58] = olc::Pixel(168, 226, 144);
	screen[59] = olc::Pixel(152, 226, 180);
	screen[60] = olc::Pixel(160, 214, 228);
	screen[61] = olc::Pixel(160, 162, 160);
	screen[62] = olc::Pixel(0, 0, 0);
	screen[63] = olc::Pixel(0, 0, 0);


    spriteScreen      = new olc::Sprite(256, 240); //sprScreen
	spriteNames[0]    = new olc::Sprite(256, 240); //sprNameTable
	spriteNames[1]    = new olc::Sprite(256, 240); 
	spritePatterns[0] = new olc::Sprite(128, 128);
	spritePatterns[1] = new olc::Sprite(128, 128);
    nmi = false;
}

uint8_t PPU::read(uint16_t addr, bool RDONLY) {
    uint8_t data = 00;

    switch (addr)
    {
    case 0000: // Control
        break;
    case 0001: // Mask
        break;
    case 0002: // Status
        data = (status.reg & 0xE0) | (ppu_data_buffer & 0x1F);
		status.vertical_blank = 0;
		address_latch = 0;
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
        data = ppu_data_buffer;
        // palette case when cycle delay doesn't happen
        // to do 
        break;
    }

    return data;
}

void PPU::write(uint16_t addr, uint8_t data) {
    switch (addr)
    {
    case 0000: // Control
        control.reg = data;
        break;
    case 0001: // Mask
        mask.reg = data;
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
    if (address_latch == 0){
			// tram_addr.reg = (uint16_t)((data & 0x3F) << 8) | (tram_addr.reg & 0x00FF);
			address_latch = 1;
		} else {
			// tram_addr.reg = (tram_addr.reg & 0xFF00) | data;
			// vram_addr = tram_addr;
			address_latch = 0;
		}
        break;
    case 0007: // PPU Data
        // to do
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
    if (cart->ppuRead(addr, data))
	{

	}
	else if (addr >= 0x0000 && addr <= 0x1FFF) //pattern
	{
        data = patternTable[(addr & 0x1000) >> 12][addr & 0x0FFF];
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF) //nametable
	{
		
	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF) //palette
	{
		addr &= 0x001F;
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		data = paletteTable[addr]; // table size is 32
	}

    return data;
}

void PPU::ppuWrite(uint16_t addr, uint8_t data) {
    addr &= MAX_PPU;
    if (cart->ppuWrite(addr, data))
	{

	}
	else if (addr >= 0x0000 && addr <= 0x1FFF) //pattern
	{
		patternTable[(addr & 0x1000) >> 12][addr & 0x0FFF] = data;
	}
	else if (addr >= 0x2000 && addr <= 0x3EFF) //nametable
	{
		
	}
	else if (addr >= 0x3F00 && addr <= 0x3FFF) //pallete
	{
		addr &= 0x001F;
		if (addr == 0x0010) addr = 0x0000;
		if (addr == 0x0014) addr = 0x0004;
		if (addr == 0x0018) addr = 0x0008;
		if (addr == 0x001C) addr = 0x000C;
		paletteTable[addr] = data;
	}
}


void PPU::connectCartridge(const std::shared_ptr<Cartridge>& cartridge) {
	this->cart = cartridge;
}

void PPU::clock() {
    // to do!
    if (scanline >= 241 && scanline < 261)
	{
		if (scanline == 241 && cycle == 1)
		{
			status.vertical_blank = 1;
			if (control.enable_nmi) 
				nmi = true;
		}
	}

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

olc::Sprite& PPU::getPatterns(uint8_t palette, uint8_t ind) {
    for(int y = 0; y < PPU::TILE_SIZE; y++) {
        for(int x = 0; x < PPU::TILE_SIZE; x++) {

            int offset = 16 * (y  * 16 + x);

            for (int i = 0; i < PPU::PIXEL_SIZE; i++){

                uint8_t lsb = ppuRead(ind * cartridge::FOUR_KILOBYTES + offset + i + 0);
				uint8_t msb = ppuRead(ind * cartridge::FOUR_KILOBYTES + offset + i + 8); 

                for(int j = 0; j < PPU::PIXEL_SIZE; j++){
                    uint8_t pix = (lsb & 1) + (msb & 1);
                    lsb >>= 0x1; 
                    msb >>= 0x1;
                    spritePatterns[i]->SetPixel(x * 8 + (7 - j), y * 8 + i, getColourFromRam(palette, pix));

                }
            }
        }
    }

    return *spritePatterns[ind];
}

olc::Pixel& PPU::getColourFromRam(uint8_t palette, uint8_t pix) {
    //0x3f00 is constant for palette memory
	return screen[ppuRead(0x3F00 + (palette << 2) + pixel) & 0x3F];
}