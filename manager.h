#ifndef __MANAGER__
#define __MANAGER__

#include <stdint.h>
#include <unordered_map>
#include <memory>
#include <string>
#include <list>

#define MAX_TGR_SIZE (1498) // ������������ ����� ����������
#define MAX_MSG_SIZE (300) // ������������ ����� ���������

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
//	uint16_t counter; // �� ������� ������� ���������� ������ �����, ��� ��������, ����� �� ��� �����������
//	����� ����� � �������, �� �������� ��� ���������� �����������, ������� ������� "����������" � ����� ������
} Datagram;

typedef struct Message_tag // ����� ����� ��������� ����� ��������� ����� ������ ��� �������� �� ���� � ���������� ����� ������
{
	uint32_t addr;
	uint16_t length;
	char data[];
} Message;
#pragma pack(pop)

class Module
{
	public:
		std::string name;	// "���" ������, ������ ��������� ������
		uint32_t addr;		// ����� ������
		uint16_t length;	// ����� ��������� � ������� �������� ������
		uint16_t counter;	// �������� ��������, �������� ����������� "������ �����"
		Module(const char*, uint32_t, uint16_t);
};

class Bus
{
	public:
		Bus(const char*);
		Send(std::list <std::shared_ptr<Message> > MessageList);
//		std::list <std::shared_ptr<Message> > MessageList;

	private:
		std::unordered_map <uint32_t, Module> Modules;
		std::list <std::shared_ptr<Telegram> > TelegramList;
};

#endif