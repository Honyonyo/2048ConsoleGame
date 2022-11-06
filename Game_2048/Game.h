#pragma once
#include <ctime>
#include <random>
#include <vector>
#include <conio.h>

#include <iostream>
#include <Windows.h>
#include <string>
#include <ctime>

#include "Graphic.h"


using namespace std;


/*화면에 보이지 않는 미니보드가 백그라운드에서 돌아간다*/


class Item
{
private:
	string caution = "아이템을 사용할 수 없다.";
	string name;
	int ea = 1;

public:

	virtual void active(int board[][4]) = 0;
	void eaPluse() { ea++; }
	void eaMinus() { ea--; }
	void setEaZero() { ea = 0; }
	void setName(string name) { this->name = name; }

	int getEa() { return ea; }
	string getName() { return name; }

	string getCaution() { return caution; }

	void printItemX() {
		gotoXY(16, 49);
		cout << " 아이템이 없다 . . .";
	}
};

//랜덤한 숫자 1개 지우기
class ItemEraser :public Item {
private:

public:
	void active(int board[][4]) {
		srand(time(NULL));
		int counter = 0;	//블록 있는 칸 갯수
		for (short i = 0; i < 4; i++) {
			for (short j = 0; j < 4; j++) {
				if (board[i][j] >=2) counter++;
			}
		}
		if (counter >= 2) {
			gotoXY(16, 49);
			cout << "아이템 \"" << getName() << "\"를 사용했다.";
			while (1) {
				short i = rand() % 4;
				short j = rand() % 4;
				if (board[i][j]>=2) {
					board[i][j] = 0;
					break;
				}
				if (getEa() > 0)eaMinus();
				else setEaZero();
				gotoXY(16, 50);
				cout << "남은 갯수 : " << getEa() << endl;
			}//while

		} else {
			gotoXY(9, 49);
			cout << getCaution();
			Sleep(400);

		}//else
	}//active()

	ItemEraser() {
		setName("블록 지우개");
	}
};

//판 흔들기
class ItemShake : public Item {
private:

public:
	void active(int board[][4]) {

		gotoXY(16, 49);
		cout << "아이템 \"" << getName() << "\"를 사용했다.";
		eaMinus();

		srand(time(NULL));
		for (int i = 0; i < 500; i++) {
			int tmp;
			int indexI = rand() % 4;
			int indexJ = rand() % 4;
			int IndexA = rand() % 4;
			int IndexB = rand() % 4;

			tmp = board[indexI][indexJ];
			board[indexI][indexJ] = board [IndexA][IndexB];
			board[IndexA][IndexB] = tmp;
		}
		gotoXY(16, 50);
		cout << "남은 갯수 : " << getEa() << endl;


	}

	ItemShake() {
		setName("저기봐! 저기");
	}
};

//제일 큰 숫자 2배 만들기
class ItemDouble :public Item {
private:

public:
	void active(int board[][4]) {
		gotoXY(16, 49);
		cout << "아이템 \"" << getName() << "\"를 사용했다.";
		eaMinus();

		srand(time(NULL));
		int high=0;
		vector<short> x, y;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				high = high > board[i][j] ? high : board[i][j];
			}
		}
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (high == board[i][j])
				{
					x.push_back(i); y.push_back(j);
				}
			}
		}

		short a = rand() % x.size();
		board[x[a]][y[a]] *= 2;

		gotoXY(16, 50);
		cout << "남은 갯수 : " << getEa() << endl;
	}

	ItemDouble() {
		setName("두배두배두");
	}
};

class Game2048 {
private:
	int range_newNum[4] = { 2,4,8,16 };
	int block_number;
	int back_gameBoard[4][4] = { 0, };
	int turn = 0;
	int high_num = 0;

	ItemEraser eraser;
	ItemDouble doubler;
	ItemShake shaker;

	random_device random;



public:

	int getTurn() { return turn; };
	int getHigh() { return high_num; };

	void debugmode();
	void backgroundBoardGenerator();
	int* getGameBoard(int i, int j) {
		return &back_gameBoard[i][j];
	};
	void set_HighestNumber();
	void gen_NewBlock();
	void hit_kbArrow(int key);
	bool hit_isThat_item(int key);
	bool goStop(int key);


	void plus_eraser() { eraser.eaPluse(); }
	void plus_shaker() { shaker.eaPluse(); }
	void plus_doubler() { doubler.eaPluse(); }
	int getEa_eraser() {	return eraser.getEa();	}
	int getEa_shaker() { return shaker.getEa(); }
	int getEa_doubler() { return doubler.getEa(); }
	string getName_eraser() { return eraser.getName(); }
	string getName_shaker() { return shaker.getName(); }
	string getName_doubler() { return doubler.getName(); }
	

	Game2048();
	~Game2048();

};