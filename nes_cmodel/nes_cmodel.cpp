// nes_cmodel.cpp : 定義靜態程式庫的函式。
//

#include "pch.h"
#include "nes_cmodel.h"

#include <stdio.h>
#include <conio.h>
#include <assert.h>

int REG::defCallback(int v)
{
	return 0;
}

REG& REG::operator[](unsigned int addr)
{
	return *this;
}

int REG::operator[](int regaddr)
{
	return 0;
}

REG& operator+=(REG a, REG b)
{
	printf("1 operator+=\n");
	return a;
}

REG& operator+=(REG a, int i)
{
	printf("2 operator+=\n");
	return a;
}

REG& operator-=(REG a, REG b)
{
	printf("3 operator-=\n");
	return a;
}

REG& operator-=(REG a, int i)
{
	printf("4 operator-=\n");
	return a;
}

REG& operator|=(REG a, REG b)
{
	printf("5 operator|=\n");
	return a;
}

REG& operator|=(REG a, int i)
{
	printf("6 operator|=\n");
	return a;
}

REG& operator&=(REG a, REG b)
{
	printf("7 operator&=\n");
	return a;
}

REG& operator&=(REG a, int i)
{
	printf("8 operator&=\n");
	return a;
}