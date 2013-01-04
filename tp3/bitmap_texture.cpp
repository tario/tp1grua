#include "stdafx.h"
#include "bitmap_texture.h"
#include "windows.h"

BitmapTexture::BitmapTexture(const std::string& path) {
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

	unsigned char* texture_data = (unsigned char*)malloc(bm.bmHeight * bm.bmWidth * 4);

	for (int j=0; j<bm.bmHeight-1; j++) { 
		unsigned char* bitmap_data = (unsigned char*)malloc(bm.bmWidth * 3 + 3);
		GetDIBits(dcBitmap, hBitmap, bm.bmHeight-j-1, 1, bitmap_data, &bmpInfo, DIB_RGB_COLORS );

		for (int i=0; i<bm.bmWidth; i++) 
		{
			unsigned char* bitmapPixelData = (unsigned char*)bitmap_data + i * 3;
			unsigned char* texturePixelData = (unsigned char*)texture_data + (j*bm.bmWidth + i) * 4;
			texturePixelData[0] = bitmapPixelData[2];
			texturePixelData[1] = bitmapPixelData[1];
			texturePixelData[2] = bitmapPixelData[0];
		}

		free(bitmap_data);
	}

	width = bm.bmWidth;
	height = bm.bmHeight;

	glGenTextures(1, &textureid);
    glBindTexture(GL_TEXTURE_2D, textureid);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture_data);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	free(texture_data);
	DeleteDC(dcBitmap);
	DeleteObject(hBitmap);
}

void BitmapTexture::load(int slot) {
	glActiveTexture(GL_TEXTURE0+slot);
    glBindTexture(GL_TEXTURE_2D, textureid);
}
