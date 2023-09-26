#pragma once
#ifndef GAMETEXT_HPP
#define GAMETEXT_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <Windows.h>
#include "GameClass.h"
#include "GameControl.hpp"
using namespace std;

//-----------------------------------------------------------------------------------------------

map<wchar_t, string> fonts_fzxs12;

void GameTextInit() {
	ifstream ifs_data;
	ifs_data.open("Resources\\Fonts\\7538_data_fzxs12.txt", ios::in);
	if (!ifs_data.is_open()) {
		cerr << "[T001][ERROR][GameTextInit::ifs_data]\nFail to open data file of font.";
		Sleep(3000);
		exit(1);
	}
	FILE* pf_wchar = NULL;
	errno_t err = 0;
	err = fopen_s(&pf_wchar, "Resources\\Fonts\\7538_wchar_fzxs12.txt", ("r, ccs = UTF-8"));
	if (err != 0) {
		cerr << "[T002][ERROR][GameTextInit::pf_wchar]\nFail to open wchar file of font.";
		Sleep(3000);
		exit(1);
	}
	pair<wchar_t, string> temp_data;
	for (int i = 0; i < 7538; i++) {
		temp_data.first = getwc(pf_wchar);
		getline(ifs_data, temp_data.second);
		fonts_fzxs12.insert(temp_data);
	}
	fclose(pf_wchar);
	ifs_data.close();
	if (fonts_fzxs12.empty()) {
		cerr << "[T003][ERROR][GameTextInit::map]\nmap<wchar_t, string> fonts_fzxs12 is empty.";
		Sleep(3000);
		exit(1);
	}
}

//-----------------------------------------------------------------------------------------------
//
//void TextOutputOfPicTxt(
//	const wchar_t text_str[], 
//	int beg_x = 0, 
//	int beg_y = 0, 
//	int br = 0, 
//	int bg = 0, 
//	int bb = 0) 
//{
//	unsigned text_len = wcslen(text_str);
//	cout << "\x1b[" << beg_y << ";" << beg_x << "H\x1b[48;2;" << br << ";" << bg << ";" << bb << "m";
//	for (int i = 0; i < text_len; i++) {
//		map<wchar_t, string>::iterator pos = fonts_fzxs12.find(text_str[i]);
//		cout << pos->second;
//	}
//	cout << "\x1b[0m";
//}

//void TextOutputOfPicTxt(
//	const wstring& text_str, 
//	int beg_x = 0, 
//	int beg_y = 0, 
//	int br = 0, 
//	int bg = 0, 
//	int bb = 0) 
//{
//	unsigned text_len = text_str.size();
//	cout << "\x1b[" << beg_y << ";" << beg_x << "H\x1b[48;2;" << br << ";" << bg << ";" << bb << "m";
//	for (int i = 0; i < text_len; i++) {
//		map<wchar_t, string>::iterator pos = fonts_fzxs12.find(text_str[i]);
//		if (pos->first != L'\n')
//			cout << pos->second;
//		else
//			cout << "\x1b[13B\x1b[" << beg_x << "G";
//	}
//	cout << "\x1b[0m";
//}
//

void TextOutputOfPicTxt(
	const wstring& text_wstr,
	const COORD& beg_xy,
	const COLOR& text_color,
	unsigned short print_time = 0,
	unsigned short line_space = 2)
{
	unsigned text_len = text_wstr.size();
	cout << "\x1b[" << beg_xy.Y << ";" << beg_xy.X << "H\x1b[48;2;" << text_color.br << ";" << text_color.bg << ";" << text_color.bb << "m";
	//��ӡ�ַ�
	if (print_time == 0)
		for (int i = 0; i < text_len; i++) {
			map<wchar_t, string>::iterator pos = fonts_fzxs12.find(text_wstr[i]);
			if (pos->first != L'\n' && pos->first != L'��')
				cout << pos->second;
			else if (pos->first == L'\n')
				cout << "\x1b[" << line_space + 12 << "B\x1b[" << beg_xy.X << "G";
			else
				WaitForInput('\n');
		}
	else
		for (int i = 0; i < text_len; i++) {
			map<wchar_t, string>::iterator pos = fonts_fzxs12.find(text_wstr[i]);
			if (pos->first != L'\n' && pos->first != L'��') {
				cout << pos->second;
				Sleep(print_time);
			}
			else if (pos->first == L'\n')
				cout << "\x1b[" << line_space + 12 << "B\x1b[" << beg_xy.X << "G";
			else
				WaitForInput('\n');
		}
	cout << "\x1b[0m";
}

void TextOutputOfPicTxt_Debugger(
	const wstring& text_wstr,
	const COORD& beg_xy,
	const COLOR& text_color,
	unsigned short print_time = 0,
	unsigned short line_space = 2,
	unsigned short line_clean = 0)
{
	unsigned text_len = text_wstr.size();
	unsigned short line_cls = line_clean;
	cout << "\x1b[" << beg_xy.Y << ";" << beg_xy.X << "H\x1b[48;2;" << text_color.br << ";" << text_color.bg << ";" << text_color.bb << "m";
	//��ӡ�ַ�
	if (print_time == 0)
		for (int i = 0; i < text_len; i++) {
			map<wchar_t, string>::iterator pos = fonts_fzxs12.find(text_wstr[i]);
			if (pos->first != L'\n' && pos->first != L'��')
				cout << pos->second;
			else if (pos->first == L'\n') {
				if (line_cls <= 1) {
					WaitForInput('\n');
					cout << "\x1b[0m";
					system("cls");
					cout << "\x1b[" << beg_xy.Y << ";" << beg_xy.X << "H\x1b[48;2;" << text_color.br << ";" << text_color.bg << ";" << text_color.bb << "m";
					line_cls = line_clean;
				}
				else {
					cout << "\x1b[" << line_space + 12 << "B\x1b[" << beg_xy.X << "G";
					line_cls--;
				}
			}
			else
				WaitForInput('\n');
		}
	else
		for (int i = 0; i < text_len; i++) {
			map<wchar_t, string>::iterator pos = fonts_fzxs12.find(text_wstr[i]);
			if (pos->first != L'\n' && pos->first != L'��') {
				cout << pos->second;
				Sleep(print_time);
			}
			else if (pos->first == L'\n') {
				if (line_cls <= 1) {
					WaitForInput('\n');
					cout << "\x1b[0m";
					system("cls");
					cout << "\x1b[" << beg_xy.Y << ";" << beg_xy.X << "H\x1b[48;2;" << text_color.br << ";" << text_color.bg << ";" << text_color.bb << "m";
					line_cls = line_clean;
				}
				else {
					cout << "\x1b[" << line_space + 12 << "B\x1b[" << beg_xy.X << "G";
					line_cls--;
				}
			}
			else
				WaitForInput('\n');
		}
	cout << "\x1b[0m";
}


void GameTextOutputControl(
	const char textName[],
	const COORD& beg_xy,
	const COLOR& text_color,
	short lineNum = 1,
	unsigned short singleLine_CharNum = 40,
	const unsigned short& print_time = 0,
	const unsigned short& line_space = 2)
{
	FILE* pf_wchar = NULL;
	errno_t err = 0;
	err = fopen_s(&pf_wchar, textName, ("r, ccs = UTF-8"));
	if (err != 0) {
		cerr << "[T004][ERROR][GameTextOutputControl::pf_wchar]\nFail to open story file.";
		Sleep(3000);
		exit(1);
	}
	wstring singlelinetext01;
	wchar_t temp_wchar;
	unsigned short count_len = 0;
	short num_change = 1;
	//������Ӣ�ַ�����������տ��ܳ��� singleLine_CharNum һ���ո�
	//���磺����7�֣�|��|ϲ|��|��|��|Re|m | ������ȱ��һ���ո��С��λ�ã�
	//������ж� count_len <= singleLine_CharNum ʱ����� count_len = 39��
	//��ʱ�����һ�������ַ�������� count_len = 41 �������ơ�
	unsigned short singleLine = singleLine_CharNum * 2;
	map<wchar_t, string>::iterator pos;

	//i �����Ҫ���е��ַ����˲������ɺ�̨������ɣ���ʹ�ٶȽ���Ҳ�޷�
	//�����������̣߳��Լ����ı����ݴ���
	for (int i = 0; ; i++) {
		//��ȡһ���ַ�
		temp_wchar = getwc(pf_wchar);
		if (temp_wchar == 65535)
			break;
		//�����ַ�Ϊ������ַ�
		if (temp_wchar > L'~') {
			count_len += 2;
			if (count_len > singleLine) {
				singlelinetext01 += L'\n';
				singlelinetext01 += temp_wchar;
				count_len = 0;
			}
			else
				singlelinetext01 += temp_wchar;
		}
		//�����ַ�Ϊ���з�����־��ǰһ���ַ�����ִ�л��л�ֹͣ��ȡ
		else if (temp_wchar == L'\n') {
			if (lineNum > 1) {
				singlelinetext01 += temp_wchar;
				singleLine = singleLine_CharNum * 2;
				count_len = 0;
				//�뷨���� map::fonts_fzxs12 ������ֱ�Ӽ��� \n \t �ȵȷ��ţ���������²���
				//cout << "\x1b[13B\x1b[" << beg_x << "G";
				lineNum--;
			}
			else {
				singlelinetext01 += temp_wchar;
				break;
			}
		}
		//�����ַ�Ϊһ����ַ� if (temp_wchar >= 32)
		else {
			count_len += 1;
			singleLine += (num_change = -num_change);
			if (count_len > singleLine) {
				singlelinetext01 += L'\n';
				singlelinetext01 += temp_wchar;
				count_len = 0;
			}
			else
				singlelinetext01 += temp_wchar;
		}
	}
	//��ʽ���
	if (singlelinetext01.empty()) {
		cerr << "[T005][ERROR][GameTextOutputControl::singlelinetext01]\n(wstring) singlelinetext01 is empty.";
		Sleep(3000);
		exit(1);
	}
	TextOutputOfPicTxt(singlelinetext01, beg_xy, text_color, print_time, line_space);
}

void GameTextOutputControl_Debugger(
	const char textName[],
	const COORD& beg_xy,
	const COLOR& text_color,
	short lineNum = 1,
	unsigned short singleLine_CharNum = 40,
	const unsigned short& print_time = 0,
	const unsigned short& line_space = 2,
	const unsigned short& clear_line = 0)
{
	FILE* pf_wchar = NULL;
	errno_t err = 0;
	err = fopen_s(&pf_wchar, textName, ("r, ccs = UTF-8"));
	if (err != 0) {
		cerr << "[T004][ERROR][GameTextOutputControl::pf_wchar]\nFail to open story file.";
		Sleep(3000);
		exit(1);
	}
	wstring singlelinetext01;
	wchar_t temp_wchar;
	unsigned short count_len = 0;
	short num_change = 1;
	//������Ӣ�ַ�����������տ��ܳ��� singleLine_CharNum һ���ո�
	//���磺����7�֣�|��|ϲ|��|��|��|Re|m | ������ȱ��һ���ո��С��λ�ã�
	//������ж� count_len <= singleLine_CharNum ʱ����� count_len = 39��
	//��ʱ�����һ�������ַ�������� count_len = 41 �������ơ�
	unsigned short singleLine = singleLine_CharNum * 2;
	map<wchar_t, string>::iterator pos;
	unsigned short clear_line_temp = clear_line;

	//i �����Ҫ���е��ַ����˲������ɺ�̨������ɣ���ʹ�ٶȽ���Ҳ�޷�
	//�����������̣߳��Լ����ı����ݴ���
	for (int i = 0; ; i++) {
		//��ȡһ���ַ�
		temp_wchar = getwc(pf_wchar);
		if (temp_wchar == 65535)
			break;
		//�����ַ�Ϊ������ַ�
		if (temp_wchar > L'~') {
			count_len += 2;
			if (count_len > singleLine) {
				singlelinetext01 += L'\n';
				singlelinetext01 += temp_wchar;
				count_len = 0;
			}
			else
				singlelinetext01 += temp_wchar;
		}
		//�����ַ�Ϊ���з�����־��ǰһ���ַ�����ִ�л��л�ֹͣ��ȡ
		else if (temp_wchar == L'\n') {
			if (lineNum > 1) {
				singlelinetext01 += temp_wchar;
				singleLine = singleLine_CharNum * 2;
				count_len = 0;
				//�뷨���� map::fonts_fzxs12 ������ֱ�Ӽ��� \n \t �ȵȷ��ţ���������²���
				//cout << "\x1b[13B\x1b[" << beg_x << "G";
				lineNum--;
			}
			else {
				singlelinetext01 += temp_wchar;
				if (clear_line_temp > 1) {
					clear_line_temp--;
				}
				else
					break;
			}
		}
		//�����ַ�Ϊһ����ַ� if (temp_wchar >= 32)
		else {
			count_len += 1;
			singleLine += (num_change = -num_change);
			if (count_len > singleLine) {
				singlelinetext01 += L'\n';
				singlelinetext01 += temp_wchar;
				count_len = 0;
			}
			else
				singlelinetext01 += temp_wchar;
		}
	}
	//��ʽ���
	if (singlelinetext01.empty()) {
		cerr << "[T005][ERROR][GameTextOutputControl::singlelinetext01]\n(wstring) singlelinetext01 is empty.";
		Sleep(3000);
		exit(1);
	}
	TextOutputOfPicTxt_Debugger(singlelinetext01, beg_xy, text_color, print_time, line_space, clear_line);
}


//�����ı����
//
//TextOutputMode:
//		0x01	�������������ÿ���һ���ַ�ͣ�� 75 ���룩
//		0x02	�������������ÿ���һ���ַ�ͣ�� 50 ���룩
//		0x04	���ֿ��������ÿ���һ���ַ�ͣ�� 25 ���룩
//		0x08	ȫ��������������һ���ַ�����ͣ��ʱ�䣩
//TextDeleteMode:
//		0x10	��������ɾ����ÿɾ��һ���ַ�ͣ�� 75 ���룩
//		0x20	��������ɾ����ÿɾ��һ���ַ�ͣ�� 50 ���룩
//		0x40	���ֿ���ɾ����ÿɾ��һ���ַ�ͣ�� 25 ���룩
//		0x80	ȫ������ɾ����ɾ��һ���ַ�����ͣ��ʱ�䣩
//void SingleLineTextOutput(
//	const string& sl_text,
//	const int& wr = 255,
//	const int& wg = 255,
//	const int& wb = 255,
//	const int& br = 0,
//	const int& bg = 0,
//	const int& bb = 0,
//	const BYTE& textOutputMode = 0x01,
//	const BYTE& textDeleteMode = 0x10,
//	const int& textRemainTime = 3000,
//	const int& systemPauseTime = 0)
//{
//	cout << "\x1b[38;2;" << wr << ";" << wg << ";" << wb << "m";
//	cout << "\x1b[48;2;" << br << ";" << bg << ";" << bb << "m";
//	unsigned textLength = sl_text.size();
//	if(textOutputMode == 0x01)
//		for (int i = 0; i < textLength; i++) {
//			cout << sl_text[i];
//			Sleep(50);
//		}
//	//else if (textOutputMode == ) {
//
//	//}
//	//else if (textOutputMode == ) {
//
//	//}
//	//else if (textOutputMode == ) {
//
//	//}
//	Sleep(textRemainTime);
//	for (int i = 0; i < textLength; i++) {
//		cout << "\x1b[1D\x1b[1X";
//		Sleep(25);
//	}
//	cout << "\n\x1b[0m";
//}




//-----------------------------------------------------------------------------------------------

#endif