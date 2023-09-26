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
		//��������Ļ������
		if (sb_in != hOut) {
			sb.push_back(sb_in);
		}
		else
		{

		}
		//�򿪴���ͼƬ���ı�·����txt�ļ�
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
		//���ж�ȡ�ļ��е�·����������vector������
		string name_temp;
		while (!pic_ifs.eof()) {
			getline(pic_ifs, name_temp);
			PicFileNames.push_back(name_temp);
		}
		while (!text_ifs.eof()) {
			getline(text_ifs, name_temp);
			TextFileNames.push_back(name_temp);
		}
		//�ر��ļ�
		pic_ifs.close();
		text_ifs.close();

	}


	//��������
	void SceneStart() {

	}

	//�����ı䣨����A->�л�����->����A��
	void SceneChange() {

	}

	//����ת��������A->����B��
	void SceneSwitch(ScreenBuffer* sb_B) {
		if (sb_B != nullptr)
			this->sb.push_back(sb_B);
	}

	//����չ��������A->����A����->��1->����B����->...->����A��ʼ״̬��
	void SceneUnfold() {

	}

	//�����Ի�������A->��1->��2->��3->�ı�������->��4->��5->�ָ�����A��ʼ״̬
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
