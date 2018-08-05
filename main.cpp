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
	for (auto it = bus.begin(); it != bus.end(); ++it)
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
	}

	Module* module = bus.GetModuleByAddr(0x200);
	if (module)
	{
		std::cout<<module->Name;
		module->PrintMessage();

		std::vector <char> tmp = toVector("DEBUG_MESSAGE");
		module->SetData(&tmp);
		std::cout<<module->Name;
		module->PrintMessage();
	}

	bus.SendData();

	return 0;
}