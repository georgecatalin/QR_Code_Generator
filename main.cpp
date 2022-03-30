/*
 ============================================================================
 Name: main.cpp
 Author: George Calin
 Created on: Mar 30, 2022
 Description : 
 ============================================================================
 */


#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cerrno>
#include "macro_definitions.h"
#include "data_containers.h"
#include "helper_functions.h"
#include "qrencode.h"

using namespace std;

int main(int argc, char *argv[])
{
	if(argc!=4)
	{
		cout<<"You did not specify the right parameters to open the "<<argv[0]<<" application."<<endl;
		cout<<"The proper invocation of this application should look like : "<<argv[0]<<" <string to convert to QR> <path to save the .bmp file> <size version of QR>"<<endl;
		return (-1);
	}

	cout<<"==================================NOTES =============================================="<<endl;
	cout<<"The proper invocation of this application should look like : "<<argv[0]<<" <string to convert to QR> <path to save the .bmp file> <size version of QR>"<<endl;
	cout<<"In case the <string to convert to QR> contains spaces you need to enclose it with \" \""<<" example: \"Red fox jumps over the fence. \""<<endl;
	cout<<"The maximum value for <size version of QR> is 10."<<endl;

    // Passing the parameters from the application invocation to the execution
	const char *QRTEXT=argv[1];
	const char *path_to_file=argv[2];
	int version=atoi(argv[3]); //Set the version number,  5 has the corresponding size is 37 * 37

	//You can replace it with what you want to set
    //const char *QRTEXT = "Today is a great day!";


    QRcode *qrCode;
    QRecLevel level = QR_ECLEVEL_H;
    QRencodeMode hint = QR_MODE_8;
    int casesensitive = 1;

    qrCode = QRcode_encodeString(QRTEXT, version, level, hint, casesensitive);
    if (NULL == qrCode)
    {
        printf("QRcode create fail\n");
        return -1;
    }

    //Save the QR code to be generated as a BMP true color picture file
    FILE *pf = fopen(path_to_file, "wb");
    if (NULL == pf)
    {
       perror("Error when opening file");
        fclose(pf);
        return -1;
    }


    int width = qrCode->width;
    int height = qrCode->width;
    int biCount = 24;                                 //True color
    int lineByte = (width * biCount / 8 + 3) / 4 * 4; //Bytes per line must be a multiple of 4


    //bitmap-file header
    BITMAPFILEHEADER bitMapFileHeader;


    //bitMapFileHeader.bfType = 0x4D42;
    bitMapFileHeader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + lineByte * height;
    bitMapFileHeader.bfReserved1 = 0;
    bitMapFileHeader.bfReserved2 = 0;
    bitMapFileHeader.bfOffBits = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    //Bitmap header
    BITMAPINFOHEADER bitMapInfoHeader;
    bitMapInfoHeader.biBitCount = biCount;
    bitMapInfoHeader.biClrImportant = 0;
    bitMapInfoHeader.biClrUsed = 0;
    bitMapInfoHeader.biCompression = 0;
    bitMapInfoHeader.biHeight = height;
    bitMapInfoHeader.biPlanes = 1;
    bitMapInfoHeader.biSize = 40;
    bitMapInfoHeader.biSizeImage = lineByte * (height);
    bitMapInfoHeader.biWidth = width;
    bitMapInfoHeader.biXPelsPerMeter = 0;
    bitMapInfoHeader.biYPelsPerMeter = 0;

    WORD bfType = 0x4D42;

    //BM type
    fwrite(&bfType, sizeof(WORD), 1, pf);

    //Write file header into file
    fwrite(&bitMapFileHeader, sizeof(BITMAPFILEHEADER), 1, pf);

    //Write bitmap header into file
    fwrite(&bitMapInfoHeader, sizeof(BITMAPINFOHEADER), 1, pf);
    unsigned char *pBMPData = new unsigned char[lineByte * height];
    memset(pBMPData, 255, lineByte * height);

    unsigned char *qrData = qrCode->data;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < lineByte / 3; j++)
        {
            if (*(qrData)&1)
            {
                //Set rgb color, which can be customized. It is set to black here.
                *(pBMPData + lineByte * i + 3 * j) = 0;
                *(pBMPData + lineByte * i + 3 * j + 1) = 0;
                *(pBMPData + lineByte * i + 3 * j + 2) = 0;
            }
            qrData++;
        }
    }

    //Write data into file
	write_data_into_file(lineByte, height, pBMPData, pf);

    QRcode_free(qrCode);

	return 0;
}
