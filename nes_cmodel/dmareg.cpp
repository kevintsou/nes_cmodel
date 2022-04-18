#include "pch.h"
#include "nes_cmodel.h"

#include <stdio.h>
#include <conio.h>
#include <assert.h>

C_DMAREG DMAREG(0xF180);

C_DMAREG::C_DMAREG(int inv) :_inv(inv) {
	_pOPRFunc = NULL;
	regBar = inv;	// register bar address
	printf("new object C_DMAREG with initial %d\n", _inv);
}

C_DMAREG::~C_DMAREG() {
	printf("free object C_DMAREG %d\n", _inv);
}

int C_DMAREG::defCallback(int v)
{
	return 0;
}

unsigned char C_DMAREG::callfundef(unsigned char v)
{
	printf("%s(%d)\n", __FUNCTION__, v);
	return 0;
}
unsigned char C_DMAREG::callfun1(unsigned char v)
{
	assert(v < 8);
	printf("%s(%d)\n", __FUNCTION__, v);
	return 0x10 + v;
}
unsigned char C_DMAREG::callfun2(unsigned char v)
{
	assert(v < 8);
	printf("%s(%d)\n", __FUNCTION__, v);
	return 0x20 + v;
}

//assign value to register
int C_DMAREG::operator=(int v) {
	printf("set Value %d\n", v);
	this->_pReg_mem[this->regIdx] = v;
	return (*this.*_pOPRFunc)(v);
}

//use signed int as read operator
int C_DMAREG::operator[](int regaddr) {
	this->regIdx = regaddr;
	return this->_pReg_mem[this->regIdx];
}

//use unsigned int as write operator
C_DMAREG& C_DMAREG::operator[](unsigned int addr) {
	//printf("REG_R16[%d] function\n", addr);
	this->regIdx = addr;
	switch (addr)
	{
	case 1:
		//printf(" pointer to callfun 1\n");
		_pOPRFunc = &C_DMAREG::callfun1;
		break;
	case 2:
		//printf(" pointer to callfun 2\n");
		_pOPRFunc = &C_DMAREG::callfun2;
		break;
	default:
		//printf(" pointer to callfun default\n");
		_pOPRFunc = &C_DMAREG::callfundef;
		break;
	};
	return *this;
}

REG& C_DMAREG::operator|=(REG b)
{
	this->_pReg_mem[this->regIdx] |= b._pReg_mem[b.regIdx];
	printf("[|=] this->_pR16_mem[0x%x] = 0x%x\n", this->regIdx, this->_pReg_mem[this->regIdx]);
	return *this;
}

REG& C_DMAREG::operator|=(int i)
{
	this->_pReg_mem[this->regIdx] |= i;
	printf("[|=] this->_pR16_mem[0x%x] = 0x%x\n", this->regIdx, this->_pReg_mem[this->regIdx]);
	return *this;
}

REG& C_DMAREG::operator&=(REG b)
{
	this->_pReg_mem[this->regIdx] &= b._pReg_mem[b.regIdx];
	printf("[&=] this->_pR16_mem[0x%x] = 0x%x\n", this->regIdx, this->_pReg_mem[this->regIdx]);
	return *this;
}

REG& C_DMAREG::operator&=(int i)
{
	this->_pReg_mem[this->regIdx] &= i;
	printf("[&=] this->_pR16_mem[0x%x] = 0x%x\n", this->regIdx, this->_pReg_mem[this->regIdx]);
	return *this;
}