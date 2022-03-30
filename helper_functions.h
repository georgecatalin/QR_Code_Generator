/*
 ============================================================================
 Name: helper_functions.h
 Author: George Calin
 Email: george.calin@gmail.com
 Created on: Mar 30, 2022
 Description : 
 ============================================================================
 */
#ifndef HELPER_FUNCTIONS_H_
#define HELPER_FUNCTIONS_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include "macro_definitions.h"
#include "data_containers.h"

void write_data_into_file(int lineByte, int height, unsigned char *pBMPData, FILE *pf);

#endif /* HELPER_FUNCTIONS_H_ */
