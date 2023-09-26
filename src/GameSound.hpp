#pragma once
#ifndef GAMESOUND_HPP
#define GAMESOUND_HPP
#include <Windows.h>
#include <mmsystem.h>
#pragma comment (lib, "Winmm.lib")

//-----------------------------------------------------------------------------------------------

void GameSoundPlay(const wstring soundFileDialog) {
	bool is_play = PlaySoundW(soundFileDialog.c_str(), nullptr, SND_FILENAME | SND_ASYNC | SND_LOOP);
	if (is_play == 0) {
		wcerr << "[GS01][GameSound::GameSoundPlay] Fail to play sound : Autumn_Never_End\\" << soundFileDialog;
		Sleep(3000);
		exit(1);
	}
}

void GameSoundStop() {
	PlaySoundW(nullptr, nullptr, SND_FILENAME);
}

//-----------------------------------------------------------------------------------------------

#endif