#ifndef __MANAGER__
#define __MANAGER__

#include <unordered_map>
#include <stdint.h>
#include <cstring>
#include <vector>
#include <string>
#include <list>

#define MAX_TGR_SIZE (1498)
#define MAX_MSG_SIZE (300)
#define MAX_SCK_SIZE (MAX_TGR_SIZE)

typedef uint16_t counter_t;

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

class Bus;

class Module
{
	friend class Bus;
	public:
		Module(const char*, uint32_t, uint16_t);
		bool SetData(std::vector <char>*);
		void PrintMessage(); // debug

		std::string Name;
		uint8_t Command;
		std::vector <char>* Data;

	private:
		uint32_t Addr;
		uint16_t Length;
		uint16_t Counter;
		size_t Offset;
		size_t Remainder;
};

class Bus
{
	public:
		Bus(const char*);
		std::unordered_map <uint32_t, Module>::iterator begin();
		std::unordered_map <uint32_t, Module>::iterator end();
		Module* GetModuleByAddr(uint32_t);
		bool SendData();

		std::unordered_map <uint32_t, Module> Modules;

	private:
		void PrintTelegram(const Telegram*, uint16_t);

		enum SocketFunction{Send, Recv}; // ONLY AS SAMPLE
		void Sock(/*socket,*/ char*, uint16_t, SocketFunction); // ONLY AS SAMPLE

};

#endif