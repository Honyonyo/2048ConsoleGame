#pragma once

#include "Block.h"

#include <ctime>
#include <random>
#include <vector>
#include <conio.h>


/*화면에 뵈지 않는 미니보드가 백그라운드에서 돌아간다
* int 4*4 2차원배열의 보드로,
* 방향키 입력을 받았을 때
	for(int i = 0 ; i<4; i++){
		int j = i;
		for (j; j<4; j++){
		제일 끝칸부터 검사
		값이 있는가? 나와 같은가? 내자리 0, 나 소멸, 쟤*2.
					나와 다른가?break;
		값이 없는가? 방향 밀고 원래자리 값 0 만들기
		}
		}

		상속관계와 참조
		버퍼찍어보기 역순으로 돌리기
		한줄씩넣되 스킵기능 넣기
* 미니보드 먼저 움직이고 이 결과를 화면에 출력한다.!!!오 예~
*/
class Game2048{
private:
	int range_newNum[4] = { 2,4,8,16 };
	int block_number;
	int back_gameBoard[4][4];
	int turn=0;
	int high_num=0;

	random_device random;



public:
	int getTurn() { return turn; };
	int getHigh() { return high_num; };



	void debugmode();
	void backgroundBoardGenerator();
	//동적배열을 사용해서 배열을 retrun할 수 있다는데 잘 모르겠다..
	 int* getGameBoard(int i, int j) {
		return &back_gameBoard[i][j];
	};
	 void set_HighestNumber();
	 void gen_NewBlock();
	 void hit_kbArrow(int key);
	 bool goStop(int key);

	Game2048();
	~Game2048();

};

class MainGame {
private:
	Block graphic;
	Game2048 game;	//,,,이걸 생성자에 넣었었는데 생성자도 함수인지라 발동끝나면 접근이 안돼
	int* gameBoard[4][4];
	int key=0;
	
public:
	int getkey() { return key; };

	void printBoard();

	//타이틀화면 열리기
	void tilePage();

	//게임페이지 열리기
	void maingGamePage(); 

	MainGame();
	~MainGame();


};

