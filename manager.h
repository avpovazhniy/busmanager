#ifndef __MANAGER__
#define __MANAGER__

#include <stdint.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <list>

#define MAX_TGR_SIZE (1498)
#define MAX_MSG_SIZE (300)

#pragma pack(push, 1)
typedef struct Telegram_tag
{
	uint16_t Length;
	char Data[];
} Telegram;

typedef struct Datagram_tag
{
	uint8_t Command;
	uint32_t Addr;
	uint16_t Length;
	char Data[];
//	uint16_t Counter; !!! for information only
} Datagram;
#pragma pack(pop)

class Module
{
	public:
		Module(const char*, uint32_t, uint16_t);
		int SetData(std::vector <char>*);
		void PrintMessage(); // debug

		std::string Name;
		uint32_t Addr;
		uint16_t Length;
		std::vector <char>* Data;
		uint16_t Counter;
};

class Bus
{
	public:
		Bus(const char*);
		Module* GetModuleByAddr(uint32_t);

		std::unordered_map <uint32_t, Module> Modules;
};

#endif