#include <iostream>
#include "manager.h"

std::vector <char> toVector(std::string data) // debug
{
	return std::vector <char> (data.begin(), data.end());
}

int main(int argc, char* argv[])
{
	Bus bus("config.ini");

	for (auto it = bus.Modules.begin(); it != bus.Modules.end(); ++it) std::cout<<it->second.Name<<" : 0x"<<std::hex<<it->second.Addr<<std::endl;

	std::vector <char> tmp;
	std::string str;
	Module* module;

	module = bus.GetModuleByAddr(0x200);
	if (module)
	{
		tmp = toVector("MESSAGE200");
		module->SetData(&tmp);
		module->PrintMessage();
	}

	module = bus.GetModuleByAddr(0x700);
	if (module)
	{
		tmp = toVector("MESSAGE700");
		module->SetData(&tmp);
		module->PrintMessage();
	}

	return 0;
}