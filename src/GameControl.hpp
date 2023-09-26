#pragma once
#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP
#include <iostream>
#include <Windows.h>
extern HANDLE hIn;

//-----------------------------------------------------------------------------------------------

//等待指定键值的输入
void WaitForInput(const char& input_char) {
	FlushConsoleInputBuffer(hIn);
	char temp = getchar();
	while (temp != input_char)
		temp = getchar();
}

//获取鼠标移动事件

//获取鼠标点击事件

//-----------------------------------------------------------------------------------------------

#endif
