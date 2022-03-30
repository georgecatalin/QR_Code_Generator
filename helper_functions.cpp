/*
 ============================================================================
 Name: helper_functions.cpp
 Author: George Calin
 Email: george.calin@gmail.com
 Created on: Mar 30, 2022
 Description : 
 ============================================================================
 */

#include "helper_functions.h"

void write_data_into_file(int lineByte, int height, unsigned char *pBMPData, FILE *pf)
{
	//Write data into file
	fwrite(pBMPData, sizeof(unsigned char), lineByte * height, pf);
	fclose(pf);
	delete[] pBMPData;
	pBMPData = NULL;
}

