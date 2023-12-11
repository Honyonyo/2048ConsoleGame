#pragma once

#include "Graphic.h"
#include "Game.h"

//소리넣기
#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>

class MainGame {
private:
	cGraphic graphic;
	Game2048 game;	//,,,이걸 생성자에 넣었었는데 생성자도 함수인지라 발동끝나면 접근이 안되므로 아예 선언하고시작

	int* gameBoard[4][4];
	int key=0;
	int coin = 1;
	
public:
	int getkey() { return key; };

	void printBoard();

	//타이틀화면 열리기
	//제일 처음 나오는 타이틀 페이지
	short titlePage();

	short helpPage();

	short shopPage();

	//게임페이지 열리기
	short mainGamePage(); 

	MainGame();
	~MainGame();
};

