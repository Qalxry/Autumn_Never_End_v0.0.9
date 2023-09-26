#pragma once
#ifndef GAMEINIT_HPP
#define GAMEINIT_HPP
#include <iostream>
#include <windows.h>
#include "GameText.hpp"
#include "GameImage.hpp"
using namespace std;

//-----------------------------------------------------------------------------------------------

HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);			//������
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);			//������

//-----------------------------------------------------------------------------------------------

//����̨��������
void setTitle() {
	SetConsoleTitle(L"Autumn Never End");
}

//���ý��ÿ���̨�༭
void setInput(HANDLE hIn_set = hIn) {
	DWORD mode;
	GetConsoleMode(hIn, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hIn, mode);
}

//����̨�������Կ��ַ��������
void setWcoutLocate() {
	wcout.imbue(locale("chs"));
}

//����̨�������
void setCursor(HANDLE hIn_set = hOut, bool showCursor = false) {
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hIn_set, &CursorInfo);			//��ȡ����̨�����Ϣ
	CursorInfo.bVisible = showCursor;					//���ؿ���̨���
	SetConsoleCursorInfo(hIn_set, &CursorInfo);			//���ÿ���̨���״̬
}

//����̨�����ն�����
void setRGB() {
	DWORD dwInMode, dwOutMode;
	GetConsoleMode(hIn, &dwInMode);						//��ȡ����̨����ģʽ
	GetConsoleMode(hOut, &dwOutMode);					//��ȡ����̨���ģʽ
	dwInMode |= 0x0200;									//���Ŀ���̨����ģʽ
	dwOutMode |= 0x0004;								//���Ŀ���̨���ģʽ
	SetConsoleMode(hIn, dwInMode);						//���ÿ���̨����ģʽ
	SetConsoleMode(hOut, dwOutMode);					//���ÿ���̨���ģʽ
}

//����̨��������
void setScreen(short screen_X = 213, short screen_Y = 133) {
	COORD coord = { screen_X + 1, screen_Y + 1 };		//�����Ļ��С����213����133 
	SetConsoleScreenBufferSize(hOut, coord); 			//���û���ߴ�
	SMALL_RECT wrt = { 0, 0, screen_X, screen_Y };
	SetConsoleWindowInfo(hOut, TRUE, &wrt); 			//���ô���ߴ�
}

//����̨��������
void setFont(HANDLE h_set = hOut, short font_X = 2, short font_Y = 2) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = font_X;
	cfi.dwFontSize.Y = font_Y;  						//���������С
	cfi.FontFamily = FF_DONTCARE;
	SetCurrentConsoleFontEx(h_set, FALSE, &cfi);
}

//����̨ȫ��ģʽ
void fullScreen() {
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);				//��Ļ��� ����
	int cy = GetSystemMetrics(SM_CYSCREEN);				//��Ļ�߶� ����
	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);	//��ȡ������Ϣ
	//���ô�����Ϣ ��� ȡ�����������߿�
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}

//����̨���ģʽ
void maxScreen() {
	COORD NewSize = GetLargestConsoleWindowSize(hOut);	//��ÿ���̨������꣬�������ַ���Ϊ��λ
	NewSize.X -= 1;
	NewSize.Y -= 1;    //���Բ��ӣ�����ʱ��ʾ������
	SetConsoleScreenBufferSize(hOut, NewSize);			//���ÿ���̨��������С

	SMALL_RECT DisplayArea = { 0,0,0,0 };
	DisplayArea.Right = NewSize.X;
	DisplayArea.Bottom = NewSize.Y;
	SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);		//���ÿ���̨��С

	//����̨�Ѿ���󻯣����ǳ�ʼλ�ò�����Ļ���Ͻǣ�������´���
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
}

//����̨���ģʽ
void maxScreen_debugger() {
	COORD NewSize = GetLargestConsoleWindowSize(hOut);	//��ÿ���̨������꣬�������ַ���Ϊ��λ
	NewSize.X -= 1;
	NewSize.Y -= 1;    //���Բ��ӣ�����ʱ��ʾ������
	SetConsoleScreenBufferSize(hOut, NewSize);			//���ÿ���̨��������С
	cout << "��������ȣ�" << NewSize.X << "\n�������߶ȣ�" << NewSize.Y << "\n";

	SMALL_RECT DisplayArea = { 0,0,0,0 };
	DisplayArea.Right = NewSize.X;
	DisplayArea.Bottom = NewSize.Y;
	SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);		//���ÿ���̨��С

	//����̨�Ѿ���󻯣����ǳ�ʼλ�ò�����Ļ���Ͻǣ�������´���
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
}

//-----------------------------------------------------------------------------------------------

//��Ϸ����Ĭ��ģʽ
void gameInit_default() {
	setTitle();
	setInput();
	setWcoutLocate();
	setCursor(hOut, false);
	setRGB();
	setFont();
	maxScreen();
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);
	GameTextInit();
	Image_Init();
}

//��Ϸ����ģʽ
void gameInit_console_size(int i = 2) {
	setTitle();
	setInput();
	setWcoutLocate();
	setCursor(hOut, false);
	setRGB();
	setFont(hOut,i,i);
	maxScreen();
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);
	GameTextInit();
	Image_Init();
}

//��Ϸ����ģʽ
void gameInit_debugger01() {
	setTitle();
	setWcoutLocate();
	setCursor(hOut, false);
	setRGB();
	while (1) {
		short font_X, font_Y;
		cout << "�������� X ֵ = ";
		cin >> font_X;
		cout << "�������� Y ֵ = ";
		cin >> font_Y;
		setFont(hOut, font_X, font_Y);
		maxScreen_debugger();
	}
}

//��Ϸ����ģʽ02
void gameInit_debugger02() {
	setTitle();
	setWcoutLocate();
	setCursor(hOut, false);
	setRGB();
	setFont();
	maxScreen();
	ios::sync_with_stdio(false);
	cout.tie(0);
	cin.tie(0);
	GameTextInit();

}


//-----------------------------------------------------------------------------------------------

#endif