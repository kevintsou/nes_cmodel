// nes_cmodel.cpp : 定義靜態程式庫的函式。
//

#include "pch.h"
#include "nes_cmodel.h"


#include <stdio.h>
#include <conio.h>
#include <assert.h>

REG_R16_MR_QINFO::REG_R16_MR_QINFO(int inv) :_inv(inv) {
	_pOPRFunc = NULL;
	printf("new object HWREG with initial %d\n", _inv);
}

REG_R16_MR_QINFO::~REG_R16_MR_QINFO() {
	printf("free object HWREG %d\n", _inv);
}

unsigned char REG_R16_MR_QINFO::callfundef(unsigned char v)
{
	printf("%s(%d)\n", __FUNCTION__, v);
	return 0;
}
unsigned char REG_R16_MR_QINFO::callfun1(unsigned char v)
{
	assert(v < 8);
	printf("%s(%d)\n", __FUNCTION__, v);
	return 0x10 + v;
}
unsigned char REG_R16_MR_QINFO::callfun2(unsigned char v)
{
	assert(v < 8);
	printf("%s(%d)\n", __FUNCTION__, v);
	return 0x20 + v;
}

//assign value to register
unsigned char REG_R16_MR_QINFO::operator=(unsigned char v) {
	printf("set Value %d\n", v);
	return (*this.*_pOPRFunc)(v);
}

//use signed int as read operator
unsigned char REG_R16_MR_QINFO::operator[](int regaddr) {
	printf("get Value %d\n", regaddr);
	return regaddr;
}

//use unsigned int as write operator
REG_R16_MR_QINFO& REG_R16_MR_QINFO::operator[](unsigned int regaddr) {
	printf("REG_R16_MR_QINFO[%d] function\n", regaddr);
	switch (regaddr)
	{
	case 1:
		printf(" pointer to callfun 1\n");
		_pOPRFunc = &REG_R16_MR_QINFO::callfun1;
		break;
	case 2:
		printf(" pointer to callfun 2\n");
		_pOPRFunc = &REG_R16_MR_QINFO::callfun2;
		break;
	default:
		printf(" pointer to callfun default\n");
		_pOPRFunc = &REG_R16_MR_QINFO::callfundef;
		break;
	};
	return *this;
}
