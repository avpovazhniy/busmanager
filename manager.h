#ifndef __MANAGER__
#define __MANAGER__

#include <stdint.h>

#define MAX_TGRAM_SIZE (1498) // максимальная длина телеграммы
#define MAX_MSG_SIZE (300) // максимальная длина сообщения

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
//	uint16_t counter; // по условию счётчик расположен именно здесь, это неудачно, лучше бы его расположить перед полем с данными, но вероятно это аппаратное ограничение
//	придётся счётчик "дописывать" в конец данных
} Datagram;

typedef struct Message_tag
{
	uint16_t length;
	char data[];
} Message;

#endif