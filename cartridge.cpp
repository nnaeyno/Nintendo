#include "cartridge.h"

Cartridge::Cartridge(const string& fileName){
    ifstream ifs;

	ifs.open(fileName, ifstream::binary);
	if (ifs.is_open())
	{

		ifs.read((char*)&header, sizeof(Header));

		if (header.mapper1 & 0x04)
			ifs.seekg(512, std::ios_base::cur);

		// get Mapper ID
		mapperID = ((header.mapper2 >> 4) << 4) | (header.mapper1 >> 4);
		
		uint8_t fileType = 1;

        // get File Format
		if (fileType == 0)
		{
            //space holders for now
		}

		if (fileType == 1)
		{
			numPRG = header.prg_rom_chunks;
			vPRGMemory.resize(numPRG * SIXTEEN_KILOBYTES);
			ifs.read((char*)vPRGMemory.data(), vPRGMemory.size());

			numCHR = header.chr_rom_chunks;
			vCHRMemory.resize(numCHR * EIGHT_KILOBYTES);
			ifs.read((char*)vCHRMemory.data(), vCHRMemory.size());
		}

		if (fileType == 2)
		{
            //space holders for now
		}	
        switch (mapperID){
		    case 0: 
                mapper = std::make_shared<Mapper000>(numPRG, numCHR); 
                break;
                // choosing which mapper to use

		}
		ifs.close();
    }
}

/**
 * @brief i copied this needs kinda more work 
 * 
 * @param addr 
 * @param data 
 * @return true 
 * @return false 
 */


bool Cartridge::read(uint16_t addr, uint8_t &data)
{
	uint32_t mapped_addr = 0;
	if (mapper->cpuMapRead(addr, mapped_addr))
	{
		data = vPRGMemory[mapped_addr];
		return true;
	}
	else
		return false;
}

bool Cartridge::write(uint16_t addr, uint8_t data)
{
	uint32_t mapped_addr = 0;
	if (mapper->cpuMapWrite(addr, mapped_addr))
	{
		vPRGMemory[mapped_addr] = data;
		return true;
	}
	else
		return false;
}

bool Cartridge::ppuRead(uint16_t addr, uint8_t & data)
{
	uint32_t mapped_addr = 0;
	if (mapper->ppuMapRead(addr, mapped_addr))
	{
		data = vCHRMemory[mapped_addr];
		return true;
	}
	else
		return false;
}

bool Cartridge::ppuWrite(uint16_t addr, uint8_t data)
{
	uint32_t mapped_addr = 0;
	if (mapper->ppuMapRead(addr, mapped_addr))
	{
		vCHRMemory[mapped_addr] = data;
		return true;
	}
	else
		return false;
}