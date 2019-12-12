#include "pch.h"
#include <conio.h>
#include "framework.h"

framework::framework()
{

}

framework::~framework()
{

}

bool framework::initialize()
{
	return true;
}

bool framework::input()
{
	state = key_state_t::none;

	while (_kbhit());

	switch (int key = tolower(_getch()))
	{
	// 방향 키의 처리
	case 0:
	case 224:
		process_arrow_key();
		break;

	// 입력 키의 처리
	case 13:
	case 32:
	case 'x':
		process_enter_key();
		break;

	// 취소 키의 처리
	case 27:
	case 'c':
		process_cancel_key();
		break;

	case 'q':
		return false;
		break;
	default:
		std::cout << key << std::endl;
		break;
	}

	return true;
}

void framework::process_arrow_key()
{
	using std::cout;
	using std::endl;

	switch (_getch())
	{
	case 72:	// ↑
		cout << "↑" << endl;
		break;
	case 75:	// ←
		cout << "←" << endl;
		break;
	case 77:	// →
		cout << "→" << endl;
		break;
	case 80:	// ↓
		cout << "↓" << endl;
		break;
	}
}

void framework::process_enter_key()
{
	state = key_state_t::enter;
}

void framework::process_cancel_key()
{
	state = key_state_t::cancel;
}

void framework::process_exit_key()
{
	state = key_state_t::exit;
}

void framework::update()
{
}

void framework::draw()
{
}
