#include <iostream> //!!!debug
#include "manager.h"

Module::Module(const char* n, uint32_t a, uint16_t l)
{
	name = n;
	addr = a;
	length = l;
	data = new std::vector <char>(length);
	counter = 0;
}

Module::~Module()
{
	delete data;
}

Bus::Bus(const char* inifile)
{
// TODO здесь должно быть сделано чтение ini файла и заполнение хэш таблицы Modules
// так как адреса модулей уникальны то сложность поиска будет O(1)
// пока заполним конфигурацию "руками"

	Modules.emplace(0x100, Module("RX100", 0x100, 10));
	Modules.emplace(0x200, Module("RX200", 0x200, 20));
	Modules.emplace(0x300, Module("RX300", 0x300, 30));
	Modules.emplace(0x400, Module("RX400", 0x400, 40));
	Modules.emplace(0x500, Module("RX500", 0x500, 50));
	Modules.emplace(0x600, Module("RX600", 0x600, 60));

//	for (auto it = Modules.begin(); it != Modules.end(); ++it) std::cout<<it->second.name<<std::endl; //!!!debug

	
}
