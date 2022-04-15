#include "pch.h"
#include "nes_cmodel.h"

#include <stdio.h>
#include <conio.h>
#include <assert.h>

REG_R16 R16_MR_QINFO(123);

REG_R16::REG_R16(int inv) :_inv(inv) {
	_pOPRFunc = NULL;
	printf("new object HWREG with initial %d\n", _inv);
}

REG_R16::~REG_R16() {
	printf("free object HWREG %d\n", _inv);
}

int REG_R16::defCallback(int v)
{
	return 0;
}

unsigned char REG_R16::callfundef(unsigned char v)
{
	printf("%s(%d)\n", __FUNCTION__, v);
	return 0;
}
unsigned char REG_R16::callfun1(unsigned char v)
{
	assert(v < 8);
	printf("%s(%d)\n", __FUNCTION__, v);
	return 0x10 + v;
}
unsigned char REG_R16::callfun2(unsigned char v)
{
	assert(v < 8);
	printf("%s(%d)\n", __FUNCTION__, v);
	return 0x20 + v;
}

//assign value to register
int REG_R16::operator=(int v) {
	printf("set Value %d\n", v);
	this->_pR16_mem[this->regIdx] = v;
	return (*this.*_pOPRFunc)(v);
}

//use signed int as read operator
int REG_R16::operator[](int regaddr) {
	this->regIdx = regaddr;
	return this->_pR16_mem[this->regIdx];
}

//use unsigned int as write operator
REG_R16& REG_R16::operator[](unsigned int addr) {
	//printf("REG_R16[%d] function\n", addr);
	this->regIdx = addr;
	switch (addr)
	{
	case 1:
		//printf(" pointer to callfun 1\n");
		_pOPRFunc = &REG_R16::callfun1;
		break;
	case 2:
		//printf(" pointer to callfun 2\n");
		_pOPRFunc = &REG_R16::callfun2;
		break;
	default:
		//printf(" pointer to callfun default\n");
		_pOPRFunc = &REG_R16::callfundef;
		break;
	};
	return *this;
}

REG& REG_R16::operator|=(REG b)
{
	this->_pR16_mem[this->regIdx] |= b._pR16_mem[b.regIdx];
	printf("[|=] this->_pR16_mem[0x%x] = 0x%x\n", this->regIdx, this->_pR16_mem[this->regIdx]);
	return *this;
}

REG& REG_R16::operator|=(int i)
{
	this->_pR16_mem[this->regIdx] |= i;
	printf("[|=] this->_pR16_mem[0x%x] = 0x%x\n", this->regIdx, this->_pR16_mem[this->regIdx]);
	return *this;
}

REG& REG_R16::operator&=(REG b)
{
	this->_pR16_mem[this->regIdx] &= b._pR16_mem[b.regIdx];
	printf("[&=] this->_pR16_mem[0x%x] = 0x%x\n", this->regIdx, this->_pR16_mem[this->regIdx]);
	return *this;
}

REG& REG_R16::operator&=(int i)
{
	this->_pR16_mem[this->regIdx] &= i;
	printf("[&=] this->_pR16_mem[0x%x] = 0x%x\n", this->regIdx, this->_pR16_mem[this->regIdx]);
	return *this;
}