/*
 *  memoria.h
 *  MIPSc++
 *
 *  Created by Ricardo Jacobi on 18/4/15.
 *  Copyright 2015 Universidade de Brasilia. All rights reserved.
 *
 */

#ifndef __MEM_H__
#define __MEM_H__

#include <iostream>

using namespace std;
#include "globals.h"
//
// memoria ligada ao processador
//
extern
int32_t mem[MEM_SIZE];

int32_t lb(const uint32_t &address, int32_t kte);

uint32_t lbu(const uint32_t &address, int32_t kte);

int32_t lh(const uint32_t &address, int32_t kte);

uint32_t lhu(const uint32_t &address, int32_t kte);

int32_t lw(const uint32_t &address, int32_t kte);

void sb(const uint32_t &address, int32_t kte, int8_t dado);

void sh(const uint32_t &address, int32_t kte, int16_t dado);

void sw(const uint32_t &address, int32_t kte, int32_t dado);

#endif