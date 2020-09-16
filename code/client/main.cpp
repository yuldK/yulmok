#include "pch.h"
#include "framework.h"
#include "common/console_util.h"
#include "omok/hint.h"


namespace 
{
	framework g_framework;
};

// constexpr int8_t val = omok::hint::get_start_offset(omok::hint::free_state_1[4]);

int main()
{
	if (!g_framework.initialize()) return -1;

	while (g_framework.check_exit() == false)
	{
		if (g_framework.input())
		{
			g_framework.update();
			g_framework.draw();

			continue;
		}

		Sleep(10);
	}

	::system("pause");

	return 0;
}
