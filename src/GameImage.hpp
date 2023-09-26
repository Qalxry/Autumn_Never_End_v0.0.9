#pragma once
#ifndef GAMEIMAGE_HPP
#define GAMEIMAGE_HPP
#include <fstream>
//#include "GameScreenBuffer.hpp"
#include "GameFileMapping.hpp"

//-----------------------------------------------------------------------------------------------

constexpr int WIDTH = 852;
constexpr int HEIGHT = 497;
constexpr int PIXEL_NUM = 852 * 497 * 3;
char* IMAGE_OUTPUT = nullptr;
extern HANDLE hOriginalOut;

//-----------------------------------------------------------------------------------------------

class Image {
	friend void ImageAddition(Image* img, short num_in);
	friend Image* Imgcpy(const Image* Source_Image, Image* Target_Image, int pixel_num);
public:
	Image() {
		this->Image_data = nullptr;
	}
	Image(int pixel_num) {
		this->Image_data = new short[pixel_num];
	}
	Image(const char fileName[]) {
		this->Image_data = convertFileToArray(fileName);
	}
	Image(const Image* Source_Image) {
		Imgcpy(Source_Image, this, Source_Image->Image_pixel);
	}
	Image operator=(const Image Source_Image) {
		Imgcpy(&Source_Image, this, Source_Image.Image_pixel);
	}
	short* convertFileToArray(const char fileName[], const int height_pic = HEIGHT, const int width_pic = WIDTH) {
		this->Image_pixel = height_pic * width_pic * 3;
		short* fileArray = new short[Image_pixel];
		short* p = fileArray;
		FILE* fp;
		fopen_s(&fp, fileName, "r");
		if (fp == NULL)
			exit(1);
		while (~fscanf_s(fp, "%hd ", p++));
		fclose(fp);
		return fileArray;
	}
	int Image_pixel = PIXEL_NUM;
	short* Image_data = nullptr;
	char* Image_output = IMAGE_OUTPUT;
};

Image* Imgcpy(const Image* Source_Image, Image* Target_Image = nullptr, int pixel_num = PIXEL_NUM) {
	if (Target_Image == nullptr)
		Target_Image = new Image(pixel_num);
	memcpy_s(Target_Image->Image_data, pixel_num * sizeof(short), Source_Image->Image_data, pixel_num * sizeof(short));
	return Target_Image;
}

void ImageAddition(Image* img, short num_in) {
	if (num_in > 255)
		num_in = 255;
	else if (num_in < -255)
		num_in = -255;
	short* p = img->Image_data;
	for (int i = 0; i < img->Image_pixel; i++) {
		*p += num_in; 
		if (*p < 0) 
			*p = 0; 
		p++;
		*p += num_in;
		if (*p < 0)
			*p = 0;
		p++;
		*p += num_in;
		if (*p < 0)
			*p = 0;
		p++;
	}
}

void Image_Init() {
	GameFileMap* gf = new GameFileMap(L"Resources\\Images\\Template_851x497.txt");
	IMAGE_OUTPUT = (char*)gf->pMapViewOfFile;
}

/*
void WriteImageToScreenBuffer(Image* img, ScreenBuffer* sb) {
	char pixel[] = "\x1b[48;2;000;000;000m ";
	char n1, n2, n3, *p_pixel;
	int time = img->Image_pixel / 3;
	short* p_img = img->Image_data;
	for (int i = 0; i < time; i++) {
		p_pixel = pixel + 7;
		n1 = ( *p_img / 100) + '0';
		n2 = ((*p_img % 100) / 10) + '0';
		n3 = ((*p_img) % 10) + '0';
		*p_pixel++ = n1;
		*p_pixel++ = n2;
		*p_pixel++ = n3;
		p_pixel++;
		p_img++;
		n1 = *p_img / 100 + '0';
		n2 = (*p_img % 100) / 10 + '0';
		n3 = (*p_img) % 10 + '0';
		*p_pixel++ = n1;
		*p_pixel++ = n2;
		*p_pixel++ = n3;
		p_pixel++;
		p_img++;
		n1 = *p_img / 100 + '0';
		n2 = (*p_img % 100) / 10 + '0';
		n3 = (*p_img) % 10 + '0';
		*p_pixel++ = n1;
		*p_pixel++ = n2;
		*p_pixel++ = n3;
		p_pixel++;
		p_img++;
		WriteConsoleA(sb->hGameScreenBuffer, pixel, 21, NULL, NULL);
	}
}

ScreenBuffer* ImageFadeOutComputing(Image* img, int reduce_num = -30) {
	ScreenBuffer* sbs[10] = {nullptr};
	for (int i = 0; i < 10; i++)
		sbs[i] = new ScreenBuffer;
	WriteImageToScreenBuffer(img, sbs[0]);
	for (int i = 1; i < 9; i++) {
		ImageAddition(img, reduce_num);
		WriteImageToScreenBuffer(img, sbs[i]);
	}
	return *sbs;
}

void ReleaseImageBuffer(ScreenBuffer* sbs[]) {
	for (int i = 0; i < 10; i++) {
		delete (sbs[i]);
		sbs[i] = nullptr;
	}
}

void ImageFadeOutShow(ScreenBuffer* sbs) {
	ScreenBuffer* sb = sbs;
	for (int i = 1; i < 10; i++) {
		sb->SetThisActiveScreenBuffer();
		Sleep(1);
	}
}

void ImageFadeOut(Image* img, int reduce_num = 30) {
	ScreenBuffer* sb0 = ImageFadeOutComputing(img, reduce_num);
	ScreenBuffer* sbs = sb0;
	ImageFadeOutShow(sbs);
	ReleaseImageBuffer(&sb0);
}
*/

//-----------------------------------------------------------------------------------------------

#endif

