#pragma once
#ifndef GAMEINIT_HPP
#define GAMEINIT_HPP
#include <iostream>
#include <windows.h>
#include "GameText.hpp"
#include "GameImage.hpp"
using namespace std;

//-----------------------------------------------------------------------------------------------

HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);			//输入句柄
HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);			//输出句柄

//-----------------------------------------------------------------------------------------------

//控制台标题设置
void setTitle() {
	SetConsoleTitle(L"Autumn Never End");
}

//设置禁用控制台编辑
void setInput(HANDLE hIn_set = hIn) {
	DWORD mode;
	GetConsoleMode(hIn, &mode);
	mode &= ~ENABLE_QUICK_EDIT_MODE;
	SetConsoleMode(hIn, mode);
}

//控制台本地语言宽字符输出设置
void setWcoutLocate() {
	wcout.imbue(locale("chs"));
}

//控制台光标设置
void setCursor(HANDLE hIn_set = hOut, bool showCursor = false) {
	CONSOLE_CURSOR_INFO CursorInfo;
	GetConsoleCursorInfo(hIn_set, &CursorInfo);			//获取控制台光标信息
	CursorInfo.bVisible = showCursor;					//隐藏控制台光标
	SetConsoleCursorInfo(hIn_set, &CursorInfo);			//设置控制台光标状态
}

//控制台虚拟终端设置
void setRGB() {
	DWORD dwInMode, dwOutMode;
	GetConsoleMode(hIn, &dwInMode);						//获取控制台输入模式
	GetConsoleMode(hOut, &dwOutMode);					//获取控制台输出模式
	dwInMode |= 0x0200;									//更改控制台输入模式
	dwOutMode |= 0x0004;								//更改控制台输出模式
	SetConsoleMode(hIn, dwInMode);						//设置控制台输入模式
	SetConsoleMode(hOut, dwOutMode);					//设置控制台输出模式
}

//控制台窗体设置
void setScreen(short screen_X = 213, short screen_Y = 133) {
	COORD coord = { screen_X + 1, screen_Y + 1 };		//最大化屏幕大小：横213，竖133 
	SetConsoleScreenBufferSize(hOut, coord); 			//设置缓冲尺寸
	SMALL_RECT wrt = { 0, 0, screen_X, screen_Y };
	SetConsoleWindowInfo(hOut, TRUE, &wrt); 			//设置窗体尺寸
}

//控制台字体设置
void setFont(HANDLE h_set = hOut, short font_X = 2, short font_Y = 2) {
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof cfi;
	cfi.nFont = 0;
	cfi.dwFontSize.X = font_X;
	cfi.dwFontSize.Y = font_Y;  						//设置字体大小
	cfi.FontFamily = FF_DONTCARE;
	SetCurrentConsoleFontEx(h_set, FALSE, &cfi);
}

//控制台全屏模式
void fullScreen() {
	HWND hwnd = GetForegroundWindow();
	int cx = GetSystemMetrics(SM_CXSCREEN);				//屏幕宽度 像素
	int cy = GetSystemMetrics(SM_CYSCREEN);				//屏幕高度 像素
	LONG l_WinStyle = GetWindowLong(hwnd, GWL_STYLE);	//获取窗口信息
	//设置窗口信息 最大化 取消标题栏及边框
	SetWindowLong(hwnd, GWL_STYLE, (l_WinStyle | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
	SetWindowPos(hwnd, HWND_TOP, 0, 0, cx, cy, 0);
}

//控制台最大化模式
void maxScreen() {
	COORD NewSize = GetLargestConsoleWindowSize(hOut);	//获得控制台最大坐标，坐标以字符数为单位
	NewSize.X -= 1;
	NewSize.Y -= 1;    //可以不加，不加时显示滚动条
	SetConsoleScreenBufferSize(hOut, NewSize);			//设置控制台缓冲区大小

	SMALL_RECT DisplayArea = { 0,0,0,0 };
	DisplayArea.Right = NewSize.X;
	DisplayArea.Bottom = NewSize.Y;
	SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);		//设置控制台大小

	//控制台已经最大化，但是初始位置不在屏幕左上角，添加如下代码
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
}

//控制台最大化模式
void maxScreen_debugger() {
	COORD NewSize = GetLargestConsoleWindowSize(hOut);	//获得控制台最大坐标，坐标以字符数为单位
	NewSize.X -= 1;
	NewSize.Y -= 1;    //可以不加，不加时显示滚动条
	SetConsoleScreenBufferSize(hOut, NewSize);			//设置控制台缓冲区大小
	cout << "缓冲区宽度：" << NewSize.X << "\n缓冲区高度：" << NewSize.Y << "\n";

	SMALL_RECT DisplayArea = { 0,0,0,0 };
	DisplayArea.Right = NewSize.X;
	DisplayArea.Bottom = NewSize.Y;
	SetConsoleWindowInfo(hOut, TRUE, &DisplayArea);		//设置控制台大小

	//控制台已经最大化，但是初始位置不在屏幕左上角，添加如下代码
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_MAXIMIZE);
}

//-----------------------------------------------------------------------------------------------

//游戏启动默认模式
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

//游戏调试模式
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

//游戏调试模式
void gameInit_debugger01() {
	setTitle();
	setWcoutLocate();
	setCursor(hOut, false);
	setRGB();
	while (1) {
		short font_X, font_Y;
		cout << "输入字体 X 值 = ";
		cin >> font_X;
		cout << "输入字体 Y 值 = ";
		cin >> font_Y;
		setFont(hOut, font_X, font_Y);
		maxScreen_debugger();
	}
}

//游戏调试模式02
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