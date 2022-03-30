/*
 ============================================================================
 Name: data_containers.h
 Author: George Calin
 Email: george.calin@gmail.com
 Created on: Mar 30, 2022
 Description : 
 ============================================================================
 */
#ifndef DATA_CONTAINERS_H_
#define DATA_CONTAINERS_H_

typedef unsigned char BYTE;
typedef unsigned short WORD;
typedef unsigned int DWORD;

//Bitmap file header definition;
typedef struct tagBITMAPFILEHEADER
{
    //WORD bfType;// If it is read separately, it is not defined in the structure
    DWORD bfSize;     //file size
    WORD bfReserved1; //Reserved word
    WORD bfReserved2; //Reserved word
    DWORD bfOffBits;  //The number of bytes offset from the file header to the actual bitmap data
} BITMAPFILEHEADER;

typedef struct tagBITMAPINFOHEADER
{
    DWORD biSize;          //Header size
    DWORD biWidth;         //Image width
    DWORD biHeight;        //Image height
    WORD biPlanes;         //Number of bit planes, must be 1
    WORD biBitCount;       //bits per pixel
    DWORD biCompression;   //Compression type
    DWORD biSizeImage;     //Compressed image size bytes
    DWORD biXPelsPerMeter; //Horizontal resolution
    DWORD biYPelsPerMeter; //Vertical resolution
    DWORD biClrUsed;       //The number of colors actually used by the bitmap
    DWORD biClrImportant;  //The number of important colors in the standard map
} BITMAPINFOHEADER;        //Bitmap header definition

//Pixel information
typedef struct tagIMAGEDATA
{
    BYTE blue;
    BYTE green;
    BYTE red;
} DATA;


#endif /* DATA_CONTAINERS_H_ */
