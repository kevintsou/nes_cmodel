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

// memory BAR address
int* mem_bar = new int[0x29600UL];
int* buf_bar = new int[0x29600UL];

// init cmodel register default value
int initCmodelReg() {
	// allocate register space
	R16_MR_QINFO._pReg_mem = new char[1000];
	R16_MR_QINFO.regIdx = 0;

	DMAREG._pReg_mem = new char[1000];
	DMAREG.regIdx = 0;
	return 0;
}

// init cmodel memory space
int initCmodelMem() {
	return 0;
}