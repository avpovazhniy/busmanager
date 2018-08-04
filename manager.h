#ifndef __MANAGER__
#define __MANAGER__

#include <stdint.h>
#include <unordered_map>
#include <memory>
#include <string>
#include <list>

#define MAX_TGR_SIZE (1498) // максимальная длина телеграммы
#define MAX_MSG_SIZE (300) // максимальная длина сообщения

#pragma pack(push, 1)
typedef struct Telegram_tag
{
	uint16_t length;
	char data[];
} Telegram;

typedef struct Datagram_tag
{
	uint8_t command;
	uint32_t addr;
	uint16_t length;
	char data[];
//	uint16_t counter; // по условию счётчик расположен именно здесь, это неудачно, лучше бы его расположить
//	перед полем с данными, но вероятно это аппаратное ограничение, придётся счётчик "дописывать" в конец данных
} Datagram;
#pragma pack(pop)

class Module
{
	public:
		Module(const char*, uint32_t, uint16_t);
		~Module();
		std::string name;	// "имя" модуля, просто текстовая строка
		uint32_t addr;		// адрес модуля
		uint16_t length;	// длина сообщения с которым работает модуль
		char* data;		// здесь будут данные для модуля и также ответы от него
		uint16_t counter;	// значение счётчика, позволит отслеживать "потерю связи"
};

class Bus
{
	public:
		Bus(const char*);
//		Send(std::list <std::shared_ptr <Message> > MessageList);
//		std::list <std::shared_ptr <Message> > MessageList;

	private:
		std::unordered_map <uint32_t, Module> Modules;
		std::list <std::shared_ptr <Telegram> > TelegramList;
};

#endif