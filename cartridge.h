#include <cstdint>
#include <array>
#include <iostream>
#include <fstream>
#include <vector>
#include "mapper000.h"

using namespace std;

class Cartridge {

    private:
        // program memory (back end logic)
        vector<uint8_t> vPRGMemory;
        // char and pattern memory (front end logic)
        vector<uint8_t> vCHRMemory;

        uint8_t mapperID = 0;
        uint8_t numPRG = 0;
        uint8_t numCHR = 0;
        shared_ptr<Mapper> mapper;
        bool validImage = false;

    public:
        Cartridge(const string& fileName);
        ~Cartridge();

        static const int ONE_KILOBYTE = 1024;
        static const int FOUR_KILOBYTES = ONE_KILOBYTE * 4;
        static const int EIGHT_KILOBYTES = FOUR_KILOBYTES * 2;
        static const int SIXTEEN_KILOBYTES = EIGHT_KILOBYTES * 2;

        bool read(uint16_t addr, uint8_t& data); //CPURead 
        bool ppuRead(uint16_t addr, uint8_t& data);

        bool write(uint16_t addr, uint8_t data); //CPUWrite
        bool ppuWrite(uint16_t addr, uint8_t data);

        bool isImageValid();

        struct Header
        {
            char name[4];
            uint8_t prg_rom_chunks;
            uint8_t chr_rom_chunks;
            uint8_t mapper1;
            uint8_t mapper2;
            uint8_t prg_ram_size;
            uint8_t tv_system1;
            uint8_t tv_system2;
            char unused[5];
        } header;

        enum MIRROR{
            HORIZONTAL,
            VERTICAL,
            ONESCREEN_LO,
            ONESCREEN_HI,
        } mirror = HORIZONTAL;

};