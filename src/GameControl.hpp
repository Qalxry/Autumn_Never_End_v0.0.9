#pragma once
#ifndef GAMECONTROL_HPP
#define GAMECONTROL_HPP
#include <iostream>
#include <Windows.h>
extern HANDLE hIn;

//-----------------------------------------------------------------------------------------------

//�ȴ�ָ����ֵ������
void WaitForInput(const char& input_char) {
	FlushConsoleInputBuffer(hIn);
	char temp = getchar();
	while (temp != input_char)
		temp = getchar();
}

//��ȡ����ƶ��¼�

//��ȡ������¼�

//-----------------------------------------------------------------------------------------------

#endif
