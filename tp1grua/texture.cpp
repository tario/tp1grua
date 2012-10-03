#include "stdafx.h"
#include "texture.h"
#include "windows.h"

Texture::Texture(const std::string& path) {
	HBITMAP hBitmap = (HBITMAP)::LoadImage(NULL, path.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
   if(NULL == hBitmap)
   {
      // LoadImage faled so get extended error information.
	   throw std::runtime_error("error loading texture");
   }

    BITMAP bm;
    ::GetObject( hBitmap , sizeof(bm) , &bm );

	BITMAPINFO bmpInfo;
    bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmpInfo.bmiHeader.biWidth = bm.bmWidth;
    bmpInfo.bmiHeader.biHeight = -bm.bmHeight;
    bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = bm.bmBitsPixel;
    bmpInfo.bmiHeader.biCompression = BI_RGB;        
    bmpInfo.bmiHeader.biSizeImage = 0;  

	HDC dcBitmap = CreateCompatibleDC ( NULL );
    SelectObject( dcBitmap, hBitmap );

	//COLORREF* pixel = new COLORREF [ bm.bmWidth * bm.bmHeight ];
	unsigned char* bitmap_data = (unsigned char*)malloc(bm.bmHeight * bm.bmWidth * 3);
	this->texture_data = (unsigned char*)malloc(bm.bmHeight * bm.bmWidth * 4);

	GetDIBits(dcBitmap, hBitmap, 0, bm.bmHeight, bitmap_data, &bmpInfo, DIB_RGB_COLORS );
	int padding = ((bm.bmWidth * 3 / 4) + 1) * 4 - bm.bmWidth * 3;
	for (int i=0; i<bm.bmWidth; i++) {
		for (int j=0; j<bm.bmHeight; j++) {
			unsigned char* bitmapPixelData = (unsigned char*)bitmap_data + (j*bm.bmWidth + i) * 3 + j*padding;
			unsigned char* texturePixelData = (unsigned char*)texture_data + (j*bm.bmWidth + i) * 4;
			texturePixelData[0] = bitmapPixelData[2];
			texturePixelData[1] = bitmapPixelData[1];
			texturePixelData[2] = bitmapPixelData[0];
		}
	}

	width = bm.bmWidth;
	height = bm.bmHeight;

	glGenTextures(1, &textureid);
    glBindTexture(GL_TEXTURE_2D, textureid);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, this->texture_data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Texture::load(int slot) {
	glActiveTexture(GL_TEXTURE0+slot);
    glBindTexture(GL_TEXTURE_2D, textureid);
}
