#include <iostream> // debug
#include "manager.h"

Module::Module(const char* name, uint32_t addr, uint16_t length)
{
	Name = name;
	Addr = addr;
	Length = length;
	Data = NULL;
	Counter = 0;
}

int Module::SetData(std::vector <char>* data)
{
	if (data)
	{
		Data = data;
		return true;
	}
	return false;
}

void Module::PrintMessage() // debug
{
	if (!Data) return;
	std::string str(Data->begin(), Data->end());
	std::cout<<".Data "<<str<<std::endl;
}

Bus::Bus(const char* inifile)
{
// TODO config.ini processing

	Modules.emplace(0x100, Module("RX100_1", 0x100, 10));
	Modules.emplace(0x200, Module("RX100_2", 0x200, 20));
	Modules.emplace(0x300, Module("RX100_3", 0x300, 30));
	Modules.emplace(0x400, Module("RX400_1", 0x400, 40));
	Modules.emplace(0x500, Module("RX500_1", 0x500, 50));
	Modules.emplace(0x600, Module("RX600_1", 0x600, 60));
}

std::unordered_map <uint32_t, Module>::iterator Bus::begin()
{
	return Modules.begin();
}

std::unordered_map <uint32_t, Module>::iterator Bus::end()
{
	return Modules.end();
}

Module* Bus::GetModuleByAddr(uint32_t addr)
{
	try
	{
		return &Modules.at(addr);
	}
	catch (std::out_of_range e)
	{
		return NULL;
	}
}

int Bus::SendData()
{
}
