#include <iostream> // debug
#include "manager.h"

Module::Module(const char* name, uint32_t addr, uint16_t length)
{
	Name = name;
	Addr = addr;
	Length = length;
	Data = NULL;
	Counter = 0;
	Offset = 0;
	Remainder = 0;
}

bool Module::SetData(std::vector <char>* data)
{
	if (data)
	{
		Data = data;
		Remainder = Data->size();
		return true;
	}
	return false;
}

void Module::PrintMessage() // debug
{
	if (!Data) return;
	std::string str(Data->begin(), Data->end());
	std::cout<<".DATA: "<<str<<std::endl;
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

bool Bus::SendData()
{
	char* buffer = new char[MAX_TGR_SIZE];
	Telegram* telegram = (Telegram*) buffer;

	bool result;
	bool EOD = false;

	while(!EOD)
	{
		memset(buffer, 0, MAX_TGR_SIZE);

		size_t tgoffset = 0;
		ptrdiff_t tglength = telegram->Data - (char*) telegram; // If additional fields are added in the Telegram struct after Length field
		if (tglength < 0)
		{
			for (auto it = begin(); it != end(); ++it) (&it->second)->Counter = 0;
			result = false;
			break;
		}

		EOD = true;
		for (auto it = begin(); it != end(); ++it)
		{
			Module* module = &it->second;
			if (!module->Remainder) continue;
			size_t partlength = module->Remainder > module->Length ? module->Length : module->Remainder;
			if (tglength + sizeof(Datagram) + partlength + sizeof(counter_t) > MAX_TGR_SIZE) break;
			Datagram* datagram = (Datagram*) (telegram->Data + tgoffset);
			datagram->Command = module->Command;
			datagram->Addr = module->Addr;
			datagram->Length = partlength;
			std::copy(module->Data->begin() + module->Offset, module->Data->begin() + module->Offset + partlength, datagram->Data);
			module->Offset += partlength;
			module->Remainder -= partlength;
			tglength += sizeof(Datagram) + datagram->Length + sizeof(counter_t);
			tgoffset += sizeof(Datagram) + datagram->Length + sizeof(counter_t);
			counter_t* counter = (counter_t*) (datagram->Data + datagram->Length);
			*counter = module->Counter;
			EOD &= (module->Remainder == 0);
		}
		telegram->Length = tglength;

		PrintTelegram(telegram, tglength); // debug

/* ONLY AS SAMPLE OF SOCKET SENDING
		char* tmp;
		int bytes;
		size_t total;
		size_t remainder;

		remainder = tglength;
		tmp = buffer;
		total = 0;
		do
		{
			int size = remainder <= MAX_SCK_SIZE ? (int) remainder : (int) MAX_SCK_SIZE;

			bytes = send(sock, tmp, size, 0);
			if (bytes < 0)
			{
				// loss of the telegrams is excluded - do nothing
			}

			tmp += (size_t) bytes;
			total += (size_t) bytes;
			remainder -= (size_t) bytes;
		} while (bytes != 0 && total < tglength);*/

/* ONLY AS SAMPLE OF SOCKET READING
		remainder = tglength;
		tmp = buffer;
		total = 0;
		do
		{
			int size = remainder <= MAX_SCK_SIZE ? (int) remainder : (int) MAX_SCK_SIZE;

			bytes = recv(sock, tmp, size, 0);
			if (bytes < 0)
			{
				// loss of the telegrams is excluded - do nothing
			}

			tmp += (size_t) bytes;
			total += (size_t) bytes;
			remainder -= (size_t) bytes;
		} while (bytes != 0 && total < tglength);*/

	}

	delete[] buffer;
	return result;
}

void Bus::PrintTelegram(const Telegram* telegram, uint16_t length) // debug
{
	if (!telegram) return;

	bool EOT = false;
	Datagram* datagram = (Datagram*) telegram->Data;
	std::cout<<"Telegram length: "<<telegram->Length<<std::endl;
	while(!EOT)
	{
		std::cout<<"\t"<<"Datagram address: 0x"<<std::hex<<datagram->Addr<<std::endl;
		std::cout<<"\t"<<"Module name: "<<GetModuleByAddr(datagram->Addr)->Name<<std::endl;
		std::cout<<"\t"<<"Datagram command: "<<datagram->Command<<std::endl;
		std::cout<<"\t"<<"Module message length: "<<std::dec<<GetModuleByAddr(datagram->Addr)->Length<<std::endl;
		std::cout<<"\t"<<"Datagram message length: "<<std::dec<<datagram->Length<<std::endl;
		std::string message(datagram->Data, datagram->Length);
		std::cout<<"\t"<<"Datagram message: "<<message<<std::endl;
		counter_t* counter = (counter_t*) (datagram->Data + datagram->Length);
		std::cout<<"\t"<<"Datagram counter: "<<std::dec<<*counter<<std::endl<<std::endl;
		datagram = (Datagram*) (datagram->Data + datagram->Length + sizeof(counter_t));
		if ((char*) datagram >= (char*) telegram + telegram->Length) EOT = true;
	}
}