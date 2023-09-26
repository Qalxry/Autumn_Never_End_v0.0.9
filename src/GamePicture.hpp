//###########################################
//#											#
//#		GamePicture.hpp						#
//#		The Codes of Picture in Game.		#
//#		@Version 3.0						#
//#											#
//###########################################

//-----------------------------------------------------------------------------------------------

#ifndef GAMEPICTURE_H
#define GAMEPICTURE_H
#include "GameInit.hpp"
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

//-----------------------------------------------------------------------------------------------

class pixel;
class picture;
vector<pixel>* pixelDataCopy(const vector<vector<int> >*, char);
void picPrint(picture*, int, int);
picture* txtPicDataCopy(string, char);
void txtPicOutput(string, short, short, short, char);

//-----------------------------------------------------------------------------------------------

//像素点数据类型
class pixel {
	friend class picture;
	friend picture* txtPicDataCopy(string, char);
public:
	pixel() {
		br = 0;
		bg = 0;
		bb = 0;
		p_x = 0;
		p_y = 0;
	}
	pixel(const int& ir, const int& ig, const int& ib, const int& ix, const int& iy) {
		br = ir;
		bg = ig;
		bb = ib;
		p_x = ix;
		p_y = iy;
	}
	//像素点输出函数 
	void pixelPrint() {
		COORD coord = { this->p_x ,this->p_y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		cout << "\033[48;2;" << this->br << ";" << this->bg << ";" << this->bb << "m" << " ";
	}
	void pixelPrint(const int& beg_x, const int& beg_y) {
		COORD coord = { beg_x + this->p_x ,beg_y + this->p_y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		cout << "\033[48;2;" << this->br << ";" << this->bg << ";" << this->bb << "m" << " ";
	}
private:
	unsigned short br;
	unsigned short bg;
	unsigned short bb;
	int p_x;
	int p_y;
};

//图片数据类型
class picture {

	friend void picPrint(picture*, int, int);
	friend picture* txtPicDataCopy(string, char);

public:
	//使用二维向量构造
	picture() {
		pic_length = 0;
		pic_width = 0;
		pic = new vector<pixel>;
	}
	picture(const vector<vector<int> >* picInData) {
		pic_length = picInData->size();
		pic_width = (*picInData)[0].size();
		pic = pixelDataCopy(picInData, '\\');
	}
	//使用二维向量和颜色排除代码构造 
	picture(const vector<vector<int> >* picInData, char excludedColorCode) {
		pic_length = picInData->size();
		pic_width = (*picInData)[0].size();
		pic = pixelDataCopy(picInData, excludedColorCode);
	}
	~picture() {
		delete pic;
	}
private:
	int pic_length;
	int pic_width;
	vector<pixel>* pic;
};

//-----------------------------------------------------------------------------------------------

//将图片数据从二维整数向量转存至pixel向量（使用颜色排除代码）
vector<pixel>* pixelDataCopy(const vector<vector<int> >* intPictureData, char noColor = '\\') {
	int originalPicture_Y = (*intPictureData).size();
	int originalPicture_X = (*intPictureData)[0].size();
	vector<pixel>* pic_temp = new vector<pixel>;
	(*pic_temp).resize(originalPicture_Y * originalPicture_X);
	for (int i = 0; i < originalPicture_Y; i++) {
		for (int j = 0; j < originalPicture_X; j += 3) {
			if (noColor == '\\') {
				pixel pixel_temp((*intPictureData)[i][j], (*intPictureData)[i][j + 1], (*intPictureData)[i][j + 2], j / 3, i);
				(*pic_temp).push_back(pixel_temp);
			}
			else if (noColor == 'w') {
				if ((*intPictureData)[i][j] + (*intPictureData)[i][j + 1] + (*intPictureData)[i][j + 2] != 765) {
					pixel pixel_temp((*intPictureData)[i][j], (*intPictureData)[i][j + 1], (*intPictureData)[i][j + 2], j / 3, i);
					(*pic_temp).push_back(pixel_temp);
				}
				else
					continue;
			}
			else if (noColor == 'b') {
				if ((*intPictureData)[i][j] + (*intPictureData)[i][j + 1] + (*intPictureData)[i][j + 2] != 0) {
					pixel pixel_temp((*intPictureData)[i][j], (*intPictureData)[i][j + 1], (*intPictureData)[i][j + 2], j / 3, i);
					(*pic_temp).push_back(pixel_temp);
				}
				else
					continue;
			}
			else {
				cerr << "[ERROR] 图片转存时所输入的颜色排除代码错误";
				Sleep(2000);
				exit(1);
			}
		}
	}
	return pic_temp;
}

//图片类型输出（使用图像输出起始坐标）
void picPrint(picture* picPrintData, int begin_x = 0, int begin_y = 0) {
	for (vector<pixel>::iterator it = (*picPrintData).pic->begin(); it < (*picPrintData).pic->end(); it++)
		it->pixelPrint(begin_x, begin_y);
	cout << "\033[0m";
}

//从txt文件（完整像素阵列）直接转存为图片（使用颜色排除代码）
picture* txtPicDataCopy(string txtPicName, char noColor = '\\') {
	picture* newPitcure = new picture;
	ifstream ifs;
	ifs.open(txtPicName, ios::in);
	//判断文件是否打开成功
	if (!ifs.is_open()) {
		cerr << txtPicName << "图片文件打开失败！" << endl;
		exit(1);
	}
	//读取txt一行有多少个数字，通过把第一行数据存入vector，再通过size函数获取一行的数字个数
	int txtPicDataCopy_queue_num = 0;
	int txtPicDataCopy_line_num = 0;
	//使用 do while 循环来创建一些临时变量，更快被释放节省内存
	do {
		int txtPicDataCopy_tempInt;
		string txtPicDataCopy_tempStr;
		vector<int> txtPicDataCopy_tempVec;
		getline(ifs, txtPicDataCopy_tempStr);
		istringstream txtPicDataCopy_is(txtPicDataCopy_tempStr);	//将读出的一行转成数据流进行操作
		while (!txtPicDataCopy_is.eof()) {
			txtPicDataCopy_is >> txtPicDataCopy_tempInt;
			txtPicDataCopy_tempVec.push_back(txtPicDataCopy_tempInt);
		}
		txtPicDataCopy_queue_num = txtPicDataCopy_tempVec.size() / 3;
		ifs.seekg(0, ios::beg);		//重置文件读取指针位置
	} while (0);
	//正式开始读取
	for (; !ifs.eof(); txtPicDataCopy_line_num++) {
		for (int i = 0; i < txtPicDataCopy_queue_num; i++) {
			pixel pixel_temp;
			ifs >> pixel_temp.br >> pixel_temp.bg >> pixel_temp.bb;
			if (noColor == '\\') {

			}
			else if (noColor == 'w') {
				if (pixel_temp.br + pixel_temp.bg + pixel_temp.bb == 765)
					continue;
				else {
					pixel_temp.p_x = i;
					pixel_temp.p_y = txtPicDataCopy_line_num;
					(newPitcure->pic)->push_back(pixel_temp);
				}
			}
			else if (noColor == 'b') {
				if (pixel_temp.br + pixel_temp.bg + pixel_temp.bb == 0)
					continue;
				else {
					pixel_temp.p_x = i;
					pixel_temp.p_y = txtPicDataCopy_line_num;
					(newPitcure->pic)->push_back(pixel_temp);
				}
			}
			else {
				cerr << "[ERROR] txt文件直接转存为图片时所输入的颜色排除代码错误";
				Sleep(2000);
				exit(1);
			}
		}
	}
	ifs.close();
	newPitcure->pic_length = ++txtPicDataCopy_line_num;
	newPitcure->pic_width = txtPicDataCopy_queue_num;
	return newPitcure;
}

//从txt文件（完整像素阵列）直接输出（使用图像长度、图像输出起始坐标、颜色排除代码）
void txtPicOutput(string txtPicName, short pic_length = 0, short begin_x = 0, short begin_y = 0, char noColor = '\\') {
	ifstream ifs;
	ifs.open(txtPicName, ios::in);
	//判断文件是否打开成功 
	if (!ifs.is_open()) {
		cerr << txtPicName << "图片txt文件打开失败！" << endl;
		exit(1);
	}
	//读取txt一行有多少个数字
	//先直接读取一行储存在字符串里面，计算空格数+1即为每一行的数字个数
	if (pic_length == 0) {
		string firstLine;
		getline(ifs, firstLine);
		pic_length = count(firstLine.begin(), firstLine.end(), ' ') + 1;
		ifs.seekg(0, ios::beg);			//重置文件读取指针
	}
	//正式输出
	if (begin_x == 0 && begin_y == 0) {
		int temp_R = 0, temp_G = 0, temp_B = 0;
		if (noColor == '\\') {
			for (int i = 0; !ifs.eof(); i++) {
				for (int j = 0; j < pic_length; j++) {
					ifs >> temp_R >> temp_G >> temp_B;
					cout << "\033[48;2;" << temp_R << ";" << temp_G << ";" << temp_B << "m" << " ";
				}
				cout << "\033[0m";
			}
		}
		else if (noColor == 'w') {
			for (int i = 0; !ifs.eof(); i++) {
				for (int j = 0; j < pic_length; j++) {
					ifs >> temp_R >> temp_G >> temp_B;
					if (temp_R == 255 && temp_G == 255 && temp_B == 255) {
						COORD coord = { j + 1 , i };
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
						continue;
					}
					cout << "\033[48;2;" << temp_R << ";" << temp_G << ";" << temp_B << "m" << " ";
				}
				cout << "\033[0m";
			}
		}
		else if (noColor == 'b') {
			for (int i = 0; !ifs.eof(); i++) {
				for (int j = 0; j < pic_length; j++) {
					ifs >> temp_R >> temp_G >> temp_B;
					if (temp_R == 0 && temp_G == 0 && temp_B == 0) {
						COORD coord = { j + 1 , i };
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
						continue;
					}
					cout << "\033[48;2;" << temp_R << ";" << temp_G << ";" << temp_B << "m" << " ";
				}
				cout << "\033[0m";
			}
		}
		else {
			cerr << "[ERROR] txt文件直接转存为图片时所输入的颜色排除代码错误";
			Sleep(2000);
			exit(1);
		}
	}
	else {
		int temp_R = 0, temp_G = 0, temp_B = 0;
		if (noColor == '\\') {
			for (int i = 0; !ifs.eof(); i++) {
				COORD coord = { begin_x , begin_y + i };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				for (int j = 0; j < pic_length; j++) {
					ifs >> temp_R >> temp_G >> temp_B;
					cout << "\033[48;2;" << temp_R << ";" << temp_G << ";" << temp_B << "m" << " ";
				}
				cout << "\033[0m";
			}
		}
		else if (noColor == 'w') {
			for (int i = 0; !ifs.eof(); i++) {
				COORD coord = { begin_x , begin_y + i };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				for (int j = 0; j < pic_length; j++) {
					ifs >> temp_R >> temp_G >> temp_B;
					if (temp_R == 255 && temp_G == 255 && temp_B == 255) {
						COORD coord = { begin_x + j + 1 , begin_y + i };
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
						continue;
					}
					cout << "\033[48;2;" << temp_R << ";" << temp_G << ";" << temp_B << "m" << " ";
				}
				cout << "\033[0m";
			}
		}
		else if (noColor == 'b') {
			for (int i = 0; !ifs.eof(); i++) {
				COORD coord = { begin_x , begin_y + i };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
				for (int j = 0; j < pic_length; j++) {
					ifs >> temp_R >> temp_G >> temp_B;
					if (temp_R == 0 && temp_G == 0 && temp_B == 0) {
						COORD coord = { begin_x + j + 1 , begin_y + i };
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
						continue;
					}
					cout << "\033[48;2;" << temp_R << ";" << temp_G << ";" << temp_B << "m" << " ";
				}
				cout << "\033[0m";
			}
		}
		else {
			cerr << "[ERROR] txt文件直接转存为图片时所输入的颜色排除代码错误";
			Sleep(2000);
			exit(1);
		}
	}
	ifs.close();
}

//-----------------------------------------------------------------------------------------------

#endif

