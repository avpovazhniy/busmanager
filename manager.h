#ifndef __MANAGER__
#define __MANAGER__

#include <stdint.h>

#define MAX_TGRAM_SIZE (1498) // ������������ ����� ����������
#define MAX_MSG_SIZE (300) // ������������ ����� ���������

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
//	uint16_t counter; // �� ������� ������� ���������� ������ �����, ��� ��������, ����� �� ��� ����������� ����� ����� � �������, �� �������� ��� ���������� �����������
//	������� ������� "����������" � ����� ������
} Datagram;

typedef struct Message_tag
{
	uint16_t length;
	char data[];
} Message;

#endif