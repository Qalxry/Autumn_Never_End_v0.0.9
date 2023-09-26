#pragma once
#ifndef GAMESTART_HPP
#define GAMESTART_HPP
#include <thread>
#include "GameInit.hpp"
#include "GamePicture.hpp"
#include "GameFileMapping.hpp"
#include "GamePainting.hpp"
#include "GameScreenBuffer.hpp"
#include "GameStory.hpp"
#include "GameControl.hpp"
#include "GameImage.hpp"
#include "GameSound.hpp"
//-----------------------------------------------------------------------------------------------

//游戏启动
void gameStart() {
	gameInit_default();
	system("color d0");
	for (int i = -21; i < 22; i++)
		txtPicOutput("Resource\\pic_Plane.txt", 0, 97 + i, 37, 'b');
	for (int i = -20; i < 20; i++)
		txtPicOutput("Resource\\pic_Plane.txt", 0, 97, 37 + i, 'b');
	txtPicOutput("Resource\\pic_WenHao_b.txt", 0, 78, 37, 'w');
	Sleep(500);
	txtPicOutput("Resource\\pic_Start.txt", 0, 62, 86, 'b');
	COORD coord = { 180, 130 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	system("pause");
}

void gameStart_FileMapping() {
	gameInit_default();
	GameFileMap* pic1 = new GameFileMap(L"background.txt");
	pic1->FileMappingOutput();
	GameFileMap* pic2 = new GameFileMap(L"background.txt");
	drawGraphByTrace("trace_change.txt", 63, 50);
	system("pause");
}

void gameStart_FileMapping_MultipleBuffer() {
	//gameInit_default();
	//GameFileMap* pic1 = new GameFileMap(L"Resources\\Images\\start.txt");
	//GameFileMap* pic2 = new GameFileMap(L"Resources\\Images\\bk01.txt");

	//ScreenBuffer* sb2 = new ScreenBuffer(pic2);

	//pic1->FileMappingOutput();
	//drawGraphByTrace("Resources\\Traces\\trace01_xrbj.txt", 63, 50);
	//sb2->SetThisActiveScreenBuffer();
	//FirstScene();
	//delete pic1;
	//delete pic2;

	gameInit_default();
	GameFileMap* pic1 = new GameFileMap(L"Resources\\Images\\start.txt");
	GameFileMap* pic2 = new GameFileMap(L"Resources\\Images\\bk01.txt");
	ScreenBuffer* sb2 = new ScreenBuffer(pic1);
	sb2->SetThisActiveScreenBuffer();
	pic1->FileMappingOutput();

	GameSoundPlay(L"Resources\\Sound\\01_title.wav");
	SetConsoleActiveScreenBuffer(hOut);
	thread t1([&] {sb2->OutputToScreenBuffer(pic2); });
	
	/*thread t2([&] {
		char a = getchar();
		if (a == '\n')
			runTrace = 0; 
		});*/
	thread t2([&] {
		if ('\n' == getchar())
			runTrace = 0;
		});

	drawGraphByTrace("Resources\\Traces\\trace01_xrbj.txt", 370, 100, 1);
	drawGraphByTrace("Resources\\Traces\\trace01_xrbj.txt", 370, 100, 0);

	t2.detach();
	t1.join();

	TextOutputOfPicTxt(L"——· 进入游戏 ·——", { 362,150 }, { 255,255,255 });
	TextOutputOfPicTxt(L"\n\n    [Press  Enter]", { 362,150 }, { 255,255,255 });
	WaitForInput('\n');
	TextOutputOfPicTxt(L"——· 进入游戏 ·——", { 362,150 }, { 55,55,55 });
	TextOutputOfPicTxt(L"\n\n    [Press  Enter]", { 362,150 }, { 55,55,55 });
	Sleep(300);
	TextOutputOfPicTxt(L"——· 进入游戏 ·——", { 362,150 }, { 255,255,255 });
	TextOutputOfPicTxt(L"\n\n    [Press  Enter]", { 362,150 }, { 255,255,255 });
	Sleep(20);

	GameSoundStop();
	sb2->SetThisActiveScreenBuffer();
	pic2->FileMappingOutput();

	SetConsoleActiveScreenBuffer(hOut);
	FirstScene();
	delete pic1;
	delete pic2;
	delete sb2;
	pic1 = nullptr;
	pic2 = nullptr;
	sb2 = nullptr;
	//system("pause");
}

/*
void gameStart_Debugger01() {
	//gameInit_debugger();
	//gameInit_default();
	gameInit_debugger02();
	debuggerScene();
	system("pause");
}

void gameStart_Debugger02() {
	/*ScreenBuffer* sb0 = new ScreenBuffer(hOut);
	vector<ScreenBuffer*> sbs = { sb0 };
	cout << ">> Start to create 100 ScreenBuffers..." << endl;
	for (int i = 0; i < 100; i++) {
		ScreenBuffer* temp = new ScreenBuffer;
		sbs.push_back(temp);
	}
	cout << ">> Creating 100 ScreenBuffers is completed!" << endl;
	int i = 1;
	for (vector<ScreenBuffer*>::iterator sbs_it = sbs.begin(); sbs_it < sbs.end(); sbs_it++) {
		(*sbs_it)->SetThisActiveScreenBuffer();
		(*sbs_it)->SetStdOutputScreenBuffer();
		cout << ">> This is the " << i++ << " time to change Active Screen Buffer.\n";
	}
	//system("pause");
	cout << "No.1";
	ScreenBuffer sb = new ScreenBuffer;
	sb.SetStdOutputScreenBuffer();
	cout << "No.2";
	sb.SetThisActiveScreenBuffer();
	cout << "No.3";
}

void gameStart_Debugger03() {
	gameInit_default();
	GameFileMap* pic1 = new GameFileMap(L"Resources\\Images\\start.txt");
	GameFileMap* pic2 = new GameFileMap(L"Resources\\Images\\bk01.txt");
	ScreenBuffer* sb2 = new ScreenBuffer(pic1);
	sb2->SetThisActiveScreenBuffer();
	pic1->FileMappingOutput();

	GameSoundPlay(L"Resources\\Sound\\01_title.wav");
	SetConsoleActiveScreenBuffer(hOut);
	thread t1([&] {sb2->OutputToScreenBuffer(pic2); });

	Image* imgStart = new Image("Resources\\Images\\start1.txt");
	ScreenBuffer* sb_start = nullptr;
	thread t3([imgStart, sb_start]()mutable {
		sb_start = ImageFadeOutComputing(imgStart);
		});
	thread t2([&] {
		char a = getchar();
		if (a == '\n')
			runTrace = 0;
		});
	thread t2([&] {
		if ('\n' == getchar())
			runTrace = 0;
		});

	drawGraphByTrace("Resources\\Traces\\trace01_xrbj.txt", 370, 100, 1);
	drawGraphByTrace("Resources\\Traces\\trace01_xrbj.txt", 370, 100, 0);

	t2.detach();
	t1.join();

	TextOutputOfPicTxt(L"——· 进入游戏 ·——", { 362,150 }, { 255,255,255 });
	TextOutputOfPicTxt(L"\n\n    [Press  Enter]", { 362,150 }, { 255,255,255 });
	WaitForInput('\n');
	TextOutputOfPicTxt(L"——· 进入游戏 ·——", { 362,150 }, { 55,55,55 });
	TextOutputOfPicTxt(L"\n\n    [Press  Enter]", { 362,150 }, { 55,55,55 });
	Sleep(300);
	TextOutputOfPicTxt(L"——· 进入游戏 ·——", { 362,150 }, { 255,255,255 });
	TextOutputOfPicTxt(L"\n\n    [Press  Enter]", { 362,150 }, { 255,255,255 });
	Sleep(20);

	t3.join();
	ImageFadeOutShow(sb_start);

	GameSoundStop();
	sb2->SetThisActiveScreenBuffer();
	pic2->FileMappingOutput();

	SetConsoleActiveScreenBuffer(hOut);
	FirstScene();
	delete pic1;
	delete pic2;
	delete sb2;
	pic1 = nullptr;
	pic2 = nullptr;
	sb2 = nullptr;
	//system("pause");

}
*/

void gameStart_Debugger04_Image_test() {
	gameInit_default();
	Image* pic1 = new Image("Resources\\Images\\start.dat");
	Image* pic2 = new Image("Resources\\Images\\bk01.dat");
	ScreenBuffer* sb1 = new ScreenBuffer(hOut);
	ScreenBuffer* sb2 = new ScreenBuffer(pic1);
	sb2->SetThisActiveScreenBuffer();
	GameSoundPlay(L"Resources\\Sound\\01_title.wav");
	
	sb1->WriteImageToScreenBuffer(pic2);
	SetConsoleActiveScreenBuffer(hOut);

	thread t1([&] {sb1->WriteImageToScreenBuffer(pic2); });

	thread t2([&] {
		if ('\n' == getchar())
			runTrace = 0;
		});

	drawGraphByTrace("Resources\\Traces\\trace01_xrbj.txt", 370, 100, 1);
	drawGraphByTrace("Resources\\Traces\\trace01_xrbj.txt", 370, 100, 0);

	t2.detach();

	TextOutputOfPicTxt(L"——· 进入游戏 ·——", { 362,150 }, { 255,255,255 });
	TextOutputOfPicTxt(L"\n\n    [Press  Enter]", { 362,150 }, { 255,255,255 });
	WaitForInput('\n');
	TextOutputOfPicTxt(L"——· 进入游戏 ·——", { 362,150 }, { 55,55,55 });
	TextOutputOfPicTxt(L"\n\n    [Press  Enter]", { 362,150 }, { 55,55,55 });
	Sleep(300);
	TextOutputOfPicTxt(L"——· 进入游戏 ·——", { 362,150 }, { 255,255,255 });
	TextOutputOfPicTxt(L"\n\n    [Press  Enter]", { 362,150 }, { 255,255,255 });
	Sleep(20);

	t1.join();
	GameSoundStop();

	sb2->SetThisActiveScreenBuffer();
	sb1->WriteImageToScreenBuffer(pic2);

	SetConsoleActiveScreenBuffer(hOut);
	FirstScene();
	delete pic1;
	delete pic2;
	delete sb2;
	pic1 = nullptr;
	pic2 = nullptr;
	sb2 = nullptr;
	//system("pause");
}

void gameStart_Debugger05() {
	int n;
	cout << "输入字符大小：";
	cin >> n;
	gameInit_console_size(n);
	Sleep(10000);
	GameSoundPlay(L"Resources\\Sound\\01_title.wav");
	drawGraphByTrace("Resources\\Traces\\trace01_xrbj.txt", 370, 100, 1);
	system("cls");
	FirstScene();




}

//-----------------------------------------------------------------------------------------------

#endif
