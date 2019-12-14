#include "pch.h"
#include "framework.h"

namespace 
{
	framework g_framework;
};

int main()
{
	if (!g_framework.initialize()) return -1;

	do
	{
		g_framework.update();
		g_framework.draw();
	} while (g_framework.input());
	
	return 0;
}
