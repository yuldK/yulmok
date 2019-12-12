#include "pch.h"
#include "framework.h"

namespace 
{
	framework g_framework;
};

int main()
{
	if (!g_framework.initialize()) return -1;

	while (g_framework.input())
	{
		g_framework.update();
		g_framework.draw();
	}
	
	return 0;
}
