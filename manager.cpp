#include <iostream>
#include "manager.h"

Module::Module(const char* n, uint32_t a, uint16_t l)
{
	name = n;
	addr = a;
	length = l;
	counter = 0;
}

Bus::Bus(const char* inifile)
{
// TODO ����� ������ ���� ������� ������ ini ����� � ���������� ��� ������� Modules
// ��� ��� ������ ������� ��������� �� ��������� ������ ����� O(1)
// ���� �������� ������������ "������"

	Modules.emplace(0x100, Module("RX100", 0x100, 10));
	Modules.emplace(0x200, Module("RX200", 0x200, 20));
	Modules.emplace(0x300, Module("RX300", 0x300, 30));
	Modules.emplace(0x400, Module("RX400", 0x400, 40));
	Modules.emplace(0x500, Module("RX500", 0x500, 50));
	Modules.emplace(0x600, Module("RX600", 0x600, 60));

//	for (auto it = Modules.begin(); it != Modules.end(); ++it) std::cout<<it->second.name<<std::endl;

	
}

int main(int argc, char* argv[])
{
	Bus bus("config.ini");
	return 0;
}