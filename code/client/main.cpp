#include "pch.h"
#include "framework.h"
#include "common/console_util.h"

namespace 
{
	framework g_framework;
};

int main()
{
	if (!g_framework.initialize()) return -1;

	while (g_framework.exit() == false)
	{
		if (g_framework.input())
		{
			g_framework.update();
			g_framework.draw();

			continue;
		}

		Sleep(10);
	}
	
	return 0;
}
