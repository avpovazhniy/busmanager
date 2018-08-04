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
	std::cout<<"DEBUG: "<<str<<std::endl;
}

Bus::Bus(const char* inifile)
{
// TODO config.ini processing

	Modules.emplace(0x100, Module("RX100", 0x100, 10));
	Modules.emplace(0x200, Module("RX200", 0x200, 20));
	Modules.emplace(0x300, Module("RX300", 0x300, 30));
	Modules.emplace(0x400, Module("RX400", 0x400, 40));
	Modules.emplace(0x500, Module("RX500", 0x500, 50));
	Modules.emplace(0x600, Module("RX600", 0x600, 60));
}

Module* Bus::GetModuleByAddr(uint32_t addr)
{
	Module* result;
	try
	{
		result = &Modules.at(addr);
	}
	catch (std::out_of_range e)
	{
		return NULL;
	}
	return result;
}

