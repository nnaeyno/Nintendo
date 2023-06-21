#include <cstdint>
#include "PPU.h"

uint8_t PPU::read(uint16_t addr, bool RDONLY) {
    uint8_t data = 0x00;

    switch (addr)
    {
    case 0x0000: // Control
        break;
    case 0x0001: // Mask
        break;
    case 0x0002: // Status
        break;
    case 0x0003: // OAM Address
        break;
    case 0x0004: // OAM Data
        break;
    case 0x0005: // Scroll
        break;
    case 0x0006: // PPU Address
        break;
    case 0x0007: // PPU Data
        break;
    }

    return data;
}

void PPU::write(uint16_t addr, uint8_t data) {
    switch (addr)
    {
    case 0x0000: // Control
        break;
    case 0x0001: // Mask
        break;
    case 0x0002: // Status
        break;
    case 0x0003: // OAM Address
        break;
    case 0x0004: // OAM Data
        break;
    case 0x0005: // Scroll
        break;
    case 0x0006: // PPU Address
        break;
    case 0x0007: // PPU Data
        break;
    }
}

/*
    placeholders for now
    masking the address if addr is outside the range
*/
uint8_t PPU::ppuRead(uint16_t addr, bool rdonly) {
    uint8_t data = 0x00;
    addr &= MAX_PPU;


    return data;
}

void PPU::ppuWrite(uint16_t addr, uint8_t data) {
    addr &= MAX_PPU;

}
