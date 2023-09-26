#pragma once
#ifndef GAMESTORY_HPP
#define GAMESTORY_HPP
#include "GameInit.hpp"
#include "GameText.hpp"
#include "GameControl.hpp"
#include "GameScreenBuffer.hpp"
#include <thread>
#include <vector>

//-----------------------------------------------------------------------------------------------

class Scene {
public:
	Scene() {

	}
	Scene(ScreenBuffer* sb_in, const char picFiles[], const char textFiles[]) {
		//创建新屏幕缓冲区
		if (sb_in != hOut) {
			sb.push_back(sb_in);
		}
		else
		{

		}
		//打开存有图片、文本路径的txt文件
		ifstream pic_ifs, text_ifs;
		pic_ifs.open(picFiles, ios::in);
		text_ifs.open(textFiles, ios::in);
		if (pic_ifs.is_open() == 0) {
			cerr << "[ST01][ERROR][GameStory::Scene]\nFail to open picFile.\n";
			Sleep(5000);
			exit(1);
		}
		if (text_ifs.is_open() == 0) {
			cerr << "[ST02][ERROR][GameStory::Scene]\nFail to open textFile.\n";
			Sleep(5000);
			exit(1);
		}
		//逐行读取文件中的路径，并存入vector容器中
		string name_temp;
		while (!pic_ifs.eof()) {
			getline(pic_ifs, name_temp);
			PicFileNames.push_back(name_temp);
		}
		while (!text_ifs.eof()) {
			getline(text_ifs, name_temp);
			TextFileNames.push_back(name_temp);
		}
		//关闭文件
		pic_ifs.close();
		text_ifs.close();

	}


	//启动场景
	void SceneStart() {

	}

	//场景改变（场景A->切换背景->场景A）
	void SceneChange() {

	}

	//场景转换（场景A->场景B）
	void SceneSwitch(ScreenBuffer* sb_B) {
		if (sb_B != nullptr)
			this->sb.push_back(sb_B);
	}

	//场景展开（场景A->人物A出镜->句1->人物B出镜->...->场景A初始状态）
	void SceneUnfold() {

	}

	//场景对话（场景A->句1->句2->句3->文本区清屏->句4->句5->恢复场景A初始状态
	void SceneTalking() {

	}
	~Scene() {
		for (vector<ScreenBuffer*>::iterator sb_it = sb.begin(); sb_it < sb.end(); sb_it++)
			delete* sb_it;

	}
private:
	vector<ScreenBuffer*> sb;
	vector<string> TextFileNames;
	vector<string> PicFileNames;
};

void debuggerScene() {
	GameTextOutputControl_Debugger(
		"Resources\\Text\\7538_wchar_fzxs12.txt",
		{ 2, 2 }, { 255, 255, 255 }, 70000, 50, 0, 0, 35);
}

void FirstScene() {
	GameTextOutputControl(
		"Resources\\Text\\Story01.txt",
		{ 10, 30 }, { 255, 255, 255 }, 50, 60, 20, 4);
}

//-----------------------------------------------------------------------------------------------

#endif
