#include <cstdint>
#include <iostream>
#include "cartridge.h"

using namespace std;

class PPU {
    private:		
	    uint8_t nameTable[2][Cartridge::ONE_KILOBYTE];  // two kilobytes 
        uint8_t	paletteTable[32]; //colors
        uint8_t patternTable[2][Cartridge::FOUR_KILOBYTES];
        
        //olc::Pixel is sourced from olcPixelGameEngine
        olc::Pixel screen[64]; //palScreen
        //sprite is foreground stuff
        olc::Sprite* spritePatterns[2]; //sprPatternTable
        olc::Sprite* spriteScreen; //sprScreen
	    olc::Sprite* spriteNames[]; //sprNameTable
        shared_ptr<Cartridge> cart;
        int16_t scanline = 0;
	    int16_t cycle = 0;

        // understand the syntax and what does it do 
        union
        {
            struct
            {
                uint8_t unused : 5;
                uint8_t sprite_overflow : 1;
                uint8_t sprite_zero_hit : 1;
                uint8_t vertical_blank : 1;
            };

            uint8_t reg;
        } status;


        union
        {
            struct
            {
                uint8_t grayscale : 1;
                uint8_t render_background_left : 1;
                uint8_t render_sprites_left : 1;
                uint8_t render_background : 1;
                uint8_t render_sprites : 1;
                uint8_t enhance_red : 1;
                uint8_t enhance_green : 1;
                uint8_t enhance_blue : 1;
            };

            uint8_t reg;
        } mask;

        union PPUCTRL
        {
            struct
            {
                uint8_t nametable_x : 1;
                uint8_t nametable_y : 1;
                uint8_t increment_mode : 1;
                uint8_t pattern_sprite : 1;
                uint8_t pattern_background : 1;
                uint8_t sprite_size : 1;
                uint8_t slave_mode : 1; // unused
                uint8_t enable_nmi : 1;
            };

            uint8_t reg;
        } control;

        union loopy{
		// Credit to Loopy for working this out :D
		struct
		{

			uint16_t coarse_x : 5;
			uint16_t coarse_y : 5;
			uint16_t nametable_x : 1;
			uint16_t nametable_y : 1;
			uint16_t fine_y : 3;
			uint16_t unused : 1;
		};

		uint16_t reg = 0x0000;
	    };

        struct sObjectAttributeEntry{
            uint8_t y;			
            uint8_t id;			
            uint8_t attribute;	
            uint8_t x;			
        } OAM[64];

        uint8_t oam_addr = 0x00;
        sObjectAttributeEntry spriteScanline[8];
	    uint8_t sprite_count;
        uint8_t sprite_shifter_pattern_lo[8];
	    uint8_t sprite_shifter_pattern_hi[8];


        loopy vram_addr;
        loopy tram_addr;
        uint8_t fine_x = 0x00;
	    uint8_t address_latch = 0x00; // low or high can be an enum would be cleaner
	    uint8_t ppu_data_buffer = 0x00;
        uint8_t bg_next_tile_id     = 0x00;
        uint8_t bg_next_tile_attrib = 0x00;
        uint8_t bg_next_tile_lsb    = 0x00;
        uint8_t bg_next_tile_msb    = 0x00;
        uint16_t bg_shifter_pattern_lo = 0x0000;
        uint16_t bg_shifter_pattern_hi = 0x0000;
        uint16_t bg_shifter_attrib_lo  = 0x0000;
        uint16_t bg_shifter_attrib_hi  = 0x0000;
    public:
        PPU();
        ~PPU();

        static const int MAX_PPU = 0x3FFF;
        static const int MIN_PPU = 0x2000;
        static const int TILE_SIZE = 16;
        static const int PIXEL_SIZE = 8;
        uint8_t read(uint16_t addr, bool RDONLY=false); //CPURead 
        uint8_t ppuRead(uint16_t addr, bool RDONLY=false);

        void write(uint16_t addr, uint8_t data); //CPUWrite
        void ppuWrite(uint16_t addr, uint8_t data);

        void connectCartridge(const std::shared_ptr<Cartridge>& cartridge);
	    void clock(); //count one system tick 
        bool nmi; //needs reset

        olc::Sprite& getPatterns(uint8_t palette, uint8_t ind); //olc::Sprite& olc2C02::GetPatternTable(uint8_t i, uint8_t palette)
        olc::Pixel& getColourFromRam(uint8_t palette, uint8_t pix);
        uint8_t* pOAM = (uint8_t*)OAM;
};