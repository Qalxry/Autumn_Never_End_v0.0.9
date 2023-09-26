#ifndef GAMEFILEMAPPING_HPP
#define GAMEFILEMAPPING_HPP
#include <string>
#include <Windows.h>
using namespace std;

//-----------------------------------------------------------------------------------------------

class GameFileMap {
public:
	GameFileMap() {
		this->wcFileName = 0;
		this->fileSize.LowPart = 0;
		this->fileSize.HighPart = 0;
		this->fileSize.QuadPart = 0;
		this->hFile = INVALID_HANDLE_VALUE;
		this->hFileMapping = NULL;
		this->pMapViewOfFile = NULL;
	}
	GameFileMap(const wchar_t DialogName[]) {
		wcFileName = new wchar_t;
		wcFileName = DialogName;
		//创建内核对象，返回其句柄
		this->hFile = CreateFileW(
			this->wcFileName,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL, OPEN_EXISTING, FILE_ATTRIBUTE_TEMPORARY, NULL);
		//判定是否成功创建内核对象
		if (this->hFile == INVALID_HANDLE_VALUE) {
			cerr << "[M001][ERROR][GameFileMap::CreateFileW]\nFail to create File.\n";
			Sleep(2000);
			delete this;
		}
		//取得内核对象大小
		GetFileSizeEx(this->hFile, &fileSize);
		//创建文件映射内核对象
		this->hFileMapping = CreateFileMappingW(
			this->hFile,
			NULL, PAGE_READWRITE, 0, 0, NULL);
		//判定是否成功创建文件映射内核对象
		if (this->hFileMapping == NULL) {
			cerr << "[M002][GameFileMap::CreateFileMappingW]\nFail to create File Mapping.\n";
			Sleep(2000);
			delete this;
		}
		//将该文件映射对象映射到当前应用程序的地址空间
		else {
			this->pMapViewOfFile = MapViewOfFile(
				this->hFileMapping,
				FILE_MAP_READ | FILE_MAP_WRITE,
				0, 0, 0);
			if (this->pMapViewOfFile == NULL) {
				cerr << "[M003][ERROR][GameFileMap::MapViewOfFile]\nFail to create Map View.\n";
				Sleep(2000);
				delete this;
			}
		}
	}
	~GameFileMap() {
		UnmapViewOfFile(this->pMapViewOfFile);
		CloseHandle(this->hFileMapping);
		CloseHandle(this->hFile);
	}
	//输出文件映射
	void FileMappingOutput() {
		fwrite(this->pMapViewOfFile, 1, this->fileSize.QuadPart, stdout);
	}
	//关闭文件映射
	void CloseFileMapping() {
		delete this;
	}
	//文件映射数据修改
	void ChangeFileViewData(const unsigned short* frameData) {

	}
	const wchar_t* wcFileName;
	LARGE_INTEGER fileSize;
	HANDLE hFile = INVALID_HANDLE_VALUE;
	HANDLE hFileMapping = NULL;
	void* pMapViewOfFile = nullptr;
};

void deleteGameFileMapping(void* pvBaseAddress, HANDLE hCreatePicFileMapping, HANDLE hCreatePicFile, const wchar_t* PicFileName) {
	UnmapViewOfFile(pvBaseAddress);
	CloseHandle(hCreatePicFileMapping);
	CloseHandle(hCreatePicFile);
	delete PicFileName;
}
//-----------------------------------------------------------------------------------------------

#endif