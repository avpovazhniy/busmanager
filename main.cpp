#include <iostream>
#include <cstdarg>
#include <list>
#include "manager.h"

std::vector <char> toVector(std::string data) // debug
{
	return std::vector <char> (data.begin(), data.end());
}

std::string stringf(const char *fmt, ...) // debug
{
	va_list args;
	va_start(args, fmt);
	std::vector <char> v(MAX_MSG_SIZE);
	while (true)
	{
		va_list args2;
		va_copy(args2, args);
		int res = vsnprintf(v.data(), v.size(), fmt, args2);
		if ((res >= 0) && (res < static_cast <int> (v.size())))
		{
			va_end(args);
			va_end(args2);
			std::string str = std::string(v.data());
			return str;
		}
		size_t size;
		if (res < 0) size = v.size() * 2;
		else size = (size_t) res + 1;
		v.clear();
		v.resize(size);
		va_end(args2);
	}
}

int main(int argc, char* argv[])
{
	Bus bus("config.ini");

	int count = 0;
	std::list <std::vector <char> > msgl;
/*	for (auto it = bus.begin(); it != bus.end(); ++it)
	{
		std::string tmp = stringf("MESSAGE_%s_", it->second.Name.c_str());
		for (int i = 0; i < count; i++) tmp += tmp;
		msgl.push_back(toVector(tmp));
		it->second.SetData(&msgl.back());
		count++;
	}

	for (auto it = bus.begin(); it != bus.end(); ++it)
	{
		std::cout<<it->second.Name;
		it->second.PrintMessage();
		std::cout<<std::endl;
	}*/

	Module* module = NULL;
	std::vector <char> data100 = toVector("THIS_IS_STREAM_MESSAGE_FOR_THE_RX100_1_MODULE!!!");
	std::vector <char> data200 = toVector("DEBUG_MESSAGE_RX100!");
	std::vector <char> data500 = toVector("LONG_LONG_DEBUG_MESSAGE_FOR_RX500_1_CONTROLLER_!!!");

	module = bus.GetModuleByAddr(0x100);
	if (module)
	{
		module->Command = 'R';
		module->SetData(&data100);
		std::cout<<module->Name;
		module->PrintMessage();
	}

	module = bus.GetModuleByAddr(0x200);
	if (module)
	{
		module->Command = 'W';
		module->SetData(&data200);
		std::cout<<module->Name;
		module->PrintMessage();
	}

	module = bus.GetModuleByAddr(0x500);
	if (module)
	{
		module->Command = 'B';
		module->SetData(&data500);
		std::cout<<module->Name;
		module->PrintMessage();
	}

	std::cout<<std::endl;

	bus.SendData();

	return 0;
}