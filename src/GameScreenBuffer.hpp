#pragma once
#ifndef GAMESCREENBUFFER_HPP
#define GAMESCREENBUFFER_HPP
#include <iostream>
#include <windows.h>
#include "GameInit.hpp"
#include "GameFileMapping.hpp"
using namespace std;

//-----------------------------------------------------------------------------------------------

HANDLE hOriginalIn = GetStdHandle(STD_INPUT_HANDLE);			//������
HANDLE hOriginalOut = GetStdHandle(STD_OUTPUT_HANDLE);			//������

//-----------------------------------------------------------------------------------------------

class ScreenBuffer {
public:
	ScreenBuffer() {
		hGameScreenBuffer = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		SetScreenBuffer();
	}
	ScreenBuffer(HANDLE output_handle) {
		this->hGameScreenBuffer = output_handle;
		if (output_handle != hOriginalOut)
			SetScreenBuffer();
	}
	ScreenBuffer(GameFileMap* gameFileMap) {
		//��������Ļ������
		hGameScreenBuffer = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		if (hGameScreenBuffer == INVALID_HANDLE_VALUE) {
			cerr << "[B001][ERROR][ScreenBuffer::CreateConsoleScreenBuffer]\nFail to create new Screen Buffer.\n";
			Sleep(3000);
			exit(1);
		}
		//��������Ļ����������
		SetScreenBuffer();
		//������Ļ�����������ʼ����
		resultOfWrite = WriteFile(
			hGameScreenBuffer,
			gameFileMap->pMapViewOfFile,
			gameFileMap->fileSize.LowPart,
			&writeCharNumber, NULL);
		if (!resultOfWrite) {
			cerr << "[B002][ERROR][ScreenBuffer::WriteFile]\nFail to write file data to new Screen Buffer.\n";
			Sleep(3000);
			exit(1);
		}
	}
	ScreenBuffer(Image* img) {
		//��������Ļ������
		hGameScreenBuffer = CreateConsoleScreenBuffer(
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
		if (hGameScreenBuffer == INVALID_HANDLE_VALUE) {
			cerr << "[B001][ERROR][ScreenBuffer::CreateConsoleScreenBuffer]\nFail to create new Screen Buffer.\n";
			Sleep(3000);
			exit(1);
		}
		//��������Ļ����������
		SetScreenBuffer();
		//������Ļ�����������ʼ����
		WriteImageToScreenBuffer(img);
	}
	void SetScreenBuffer() {
		setCursor(hGameScreenBuffer, false);
		setFont(hGameScreenBuffer);
		setInput(hGameScreenBuffer);
	}
	//���ļ����ݸ��ǻ�����������
	void OutputToScreenBuffer(GameFileMap* gameFileMap) {
		if (hGameScreenBuffer != nullptr)
			resultOfWrite = WriteFile(
				hGameScreenBuffer,
				gameFileMap->pMapViewOfFile,
				gameFileMap->fileSize.LowPart,
				&writeCharNumber, NULL);
		if (!resultOfWrite) {
			cerr << "[B002][ERROR][ScreenBuffer::WriteFile]\nFail to write file data to new Screen Buffer.\n";
			Sleep(3000);
			exit(1);
		}
	}
	//���Image����������������
	void WriteImageToScreenBuffer(Image* img) {
		/*char pixel[21] = "\x1b[48;2;000;000;000m ";*/
		char n1, n2, n3, * p_pixel = img->Image_output - 1;
		int time = img->Image_pixel / 3;
		short* p_img = img->Image_data;
		for (int i = 0; i < time; i++) {
			p_pixel = img->Image_output + 8;
			n1 = (*p_img / 100) + '0';
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
		}
		WriteFile(hOut, img->Image_output, 20 * time, NULL, NULL);
	}
	//���øû�����Ϊ�������
	void SetThisActiveScreenBuffer() {
		if (hGameScreenBuffer != nullptr)
			resultOfSetActive = SetConsoleActiveScreenBuffer(hGameScreenBuffer);
		if (!resultOfSetActive) {
			cerr << "[B004][ERROR][ScreenBuffer::SetActiveScreenBuffer]\nFail to set this Screen Buffer as Active Screen Buffer.\n";
			Sleep(3000);
			exit(1);
		}
	}
	//���øû�����Ϊ��׼���������
	void SetStdOutputScreenBuffer() {
		if (hGameScreenBuffer != nullptr)
			SetStdHandle(STD_OUTPUT_HANDLE, this->hGameScreenBuffer);
	}
	~ScreenBuffer() {
		HANDLE hCurrentStdOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		//HANDLE hCurrentActiveScreenBuffer = 
		if (hGameScreenBuffer != hCurrentStdOutputHandle)
			CloseHandle(hGameScreenBuffer);
	}
	HANDLE hGameScreenBuffer = nullptr;
	DWORD writeCharNumber = 0;
	BOOL resultOfWrite = 0;
	BOOL resultOfSetActive = 0;
};

//-----------------------------------------------------------------------------------------------

#endif
