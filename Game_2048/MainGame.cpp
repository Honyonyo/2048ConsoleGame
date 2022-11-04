#include "MainGame.h"

#pragma region Class Game2048
void Game2048::debugmode()
{
	int back_gameBoardtmp[4][4] = {
		{2,2,2,4},
		{2,0,0,2},
		{2,0,0,2},
		{4,2,2,2}
	};
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			back_gameBoard[i][j] = back_gameBoardtmp[i][j];

		}
	}
	//int tmp;
	//do {
	//	int i, j;
	//	cout << "좌표입력";
	//	cin >> tmp;
	//	i = tmp / 10;
	//	j = tmp % 10;
	//	cout << "숫자입력";
	//	cin >> back_gameBoard[i][j];
	//	tmp = _getch();
	//} while (tmp != 32);
}
void Game2048::backgroundBoardGenerator()
{
	for (int i=0; i < 4; i++) {
		for (int j=0; j < 4; j++) {
			back_gameBoard[i][j] = 0;
		}
	};

	mt19937_64 rnd(random());
	uniform_int_distribution<int> range(0, 3);

	back_gameBoard[range(rnd)][range(rnd)] = 2;
}

//이 게임 동작방식의 집약체!!!
void Game2048::hit_kbArrow(int key){
	//genBlock 할지말지 정하기 위해 tmpBoard에 현재보드 복사하기->화살표 입력 후 
	int tmpBoard[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			tmpBoard[i][j] = back_gameBoard[i][j];
		}
	}
#pragma region 화살표별 작동방식
	//작동잘해
	switch (key) {
	case 72: //cout << "↑" << endl;
		for (int i = 0; i < 4; i++) {
					bool murged = 0;
			for (int j = 1; j < 4; j++) {	//0번째칸은 이동 안해도 되니까 스킵
				int k = j;	//
				for (k; k > 0; k--) {
					if (!back_gameBoard[k][i]) break;	//나 = 0 이동필요x
					bool bk = NULL;	//for k브레이크키
					switch (back_gameBoard[k-1][i]) {//앞에거 0인지 차있는지
					case 0://비어있니
						back_gameBoard[k-1][i] = back_gameBoard[k][i];
						back_gameBoard[k][i] = NULL;
						break;

					default://차있을 때
						if (back_gameBoard[k - 1][i] == back_gameBoard[k][i]) {
							if (murged) { bk = 1; murged = 0; break; }
							back_gameBoard[k - 1][i] *= 2;
							back_gameBoard[k][i] = NULL;
							murged = 1;
							}						
						else {
							bk = 1; murged = 0;
						}
					}
					if (bk) break;	//k브레이크			
				}//for k
			}//for j
		}//for i 
		break;

	case 80: //cout << "↓";
		for (int i = 0; i < 4; i++) {
					bool murged = 0;
			for (int j = 2; j >=0 ; j--) {	//0번째칸은 이동 안해도 되니까 스킵
				int k = j;	//
				for (k; k < 3; k++) {
					if (!back_gameBoard[k][i]) break;	//나 = 0 이동필요x
					bool bk = NULL;	//for k브레이크키
					switch (back_gameBoard[k + 1][i]) {//밑에거 0인지 차있는지
					case 0:
						back_gameBoard[k + 1][i] = back_gameBoard[k][i];
						back_gameBoard[k][i] = NULL;
						break;

					default://옆에거 숫자 있을 때
						if (!murged) {	//병합된 적 없을 경우
							//나랑 같으면 병합하고 병합유무 1
							if (back_gameBoard[k + 1][i] == back_gameBoard[k][i]) {
								back_gameBoard[k + 1][i] *= 2;
								back_gameBoard[k][i] = NULL;
								murged = 1;
							}
							else {
								bk = 1;
								murged = 0;
							}
						}
						//병합된 적 있을 경우
					}
					if (bk) break;	//k브레이크			
				}//for k
			}//for j
		}//for i 

		break;

	case 75://cout << "←";
		//[i][j]칸을 k회만큼 움직일 수 있나 검토
		for (int i = 0; i < 4; i++) {
				bool murged = 0;
			for (int j = 1; j < 4; j++) {	//0번째칸은 이동 안해도 되니까 스킵
				int k = j;	//
				for (k; k > 0; k--) {
					if (!back_gameBoard[i][k]) break;	//나 = 0 이동필요x

					bool bk = NULL;	//for k브레이크키
					switch (back_gameBoard[i][k - 1]) {//앞에거 0인지 차있는지
					case 0:
						back_gameBoard[i][k - 1] = back_gameBoard[i][k];
						back_gameBoard[i][k] = NULL;
						break;

					default:
						if (!murged) {
							if (back_gameBoard[i][k - 1] == back_gameBoard[i][k]) {
								back_gameBoard[i][k - 1] *= 2;
								back_gameBoard[i][k] = NULL;
								murged = 1;
							}
						else {
							bk = 1; murged = 0;
						}
						}
					}
					if (bk) break;	//k브레이크			
				}//for k
			}//for j
		}//for i 

		break;

	case 77:	//cout << "→";
		for (int i = 0; i < 4; i++) {
			bool murged = 0;
			for (int j = 2; j >= 0; j--) {	//0번째칸은 이동 안해도 되니까 스킵
				int k = j;	//
				for (k; k < 3; k++) {
					if (!back_gameBoard[i][k]) break;	//나 = 0 이동필요x

					bool bk = NULL;	//for k브레이크키
					switch (back_gameBoard[i][k + 1]) {//앞에거 0인지 차있는지
					case 0:
						back_gameBoard[i][k + 1] = back_gameBoard[i][k];
						back_gameBoard[i][k] = NULL;
						break;

					default:
						if (!murged) {
							if (back_gameBoard[i][k + 1] == back_gameBoard[i][k]) {
								back_gameBoard[i][k + 1] *= 2;
								back_gameBoard[i][k] = NULL;
								murged = 1;
							}
						else {
							bk = 1; murged = 0;
						}
						}
					}
					if (bk) break;	//k브레이크			
				}//for k
			}//for j
		}//for i 
		break;
	default: cout << "뭔가 잘못됐다 _arrow" << endl;
	}//switch
#pragma endregion
	

	//키입력으로 보드가 움직였을 때만 턴++, 새 블록 생성
	bool k = 0;	//움직임 여부 판별기
	short i = 0;
	do {
		for (short j = 0; j < 4; j++) {
			k= tmpBoard[i][j] != back_gameBoard[i][j] ? 1:0;
			if (k) break;
		}
		if (++i == 4)break;
	} while (!k);
	if (k) {
		turn++;
		set_HighestNumber();
		gen_NewBlock();
	}
	else {/*삐빅 사운드 넣을 수 있으면 넣기*/ };
}
bool Game2048::goStop(int key)
{
	if (key == 27) return false;
	{
		//동작 전 보드가 꽉 찼는지 검사하고
//꽉 차있다면 위, 아래로 같은숫자가 붙어있는 칸이 있는지 검사
//없다면 return false
		short k = 1;	//k가 0이면 빈칸이 있다는 뜻
		short j = 0;
		while (k) {
			for (int i = 0; i < 4; i++) {
				k = back_gameBoard[i][j];
			}
			if (++j == 4) break;
		};
		if (!k) {
			return 1;
		}
		else {
			short j = 0;
			while (k) {
				for (short i = 0; i < 3; i++) {
					//빈칸 만들 여지가 있는 경우 0, 여지 없는 경우 1
					k = ((back_gameBoard[j][i] == back_gameBoard[j][i + 1]) || (back_gameBoard[j + 1][i] == back_gameBoard[j][i]))
						? 0 : 1;
					if (!k) return 1;
				}
				if (++j == 4) break;
			}//while 끝

			for (short i = 0; i < 3; i++) {
				k = ((back_gameBoard[3][i] == back_gameBoard[3][i + 1]) || (back_gameBoard[i][3] == back_gameBoard[i + 1][3]))
					? 0 : 1;
				if (!k) return 1;
			}
			return 0;

		};

	}
	return false;
}


void Game2048::set_HighestNumber() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			high_num = high_num > back_gameBoard[i][j] ? high_num : back_gameBoard[i][j];
		}
	}
}

void Game2048::gen_NewBlock() {
	//슈오옹! 하고 블록 탄생하는 소리 넣을 수 있으면 넣기
	//		 cout << "블록생성!시작" << endl;
	srand(time(NULL));
	mt19937_64 rnd(random());
	uniform_int_distribution<int> range_4(0, 3);
	uniform_int_distribution<int> range_3(0, 2);

	bool succ_insert = 0;
	while (!succ_insert) {
		int numI = range_4(rnd);
		int numJ = range_4(rnd);
		//			 cout << "블록 생성중!" << endl;
		if (!back_gameBoard[numI][numJ]) {

			switch (high_num) {
			case 0: case 2: case 4: case 8: case 16:
				back_gameBoard[numI][numJ] = 2;
				break;
			case 32: case 64: case 128: case 256:
				back_gameBoard[numI][numJ] = range_newNum[rand() % 2];
				break;
			case 512: case 1024:
				back_gameBoard[numI][numJ] = range_newNum[range_3(rnd)];
			default:
				back_gameBoard[numI][numJ] = range_newNum[range_4(rnd)];
			}
			succ_insert = 1;
			//				 cout << "블록생성성공!" << endl;
		}
		//			 else cout << "블록생성실패!" << endl;
	}
}

Game2048::Game2048()
{
}

Game2048::~Game2048()
{

}
#pragma endregion

#pragma region Class MainGame
void MainGame::printBoard() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			//cout.width(12);
			int X, Y;
			switch (i) {
			case 0:
				Y = 22;
				break;
			case 1:
				Y = 29;
				break;
			case 2:
				Y = 36;
				break;
			case 3:
				Y = 43;
				break;
			}
			switch (j) {
			case 0:
				X = 3;
				break;
			case 1:
				X = 17;
				break;
			case 2:
				X = 31;
				break;
			case 3:
				X = 45;
				break;
			}
			graphic.printBlock(*gameBoard[i][j], X,Y);
		}
		cout << endl;
	}
}
void MainGame::tilePage()
{
	graphic.printTitle(1);
}
//게임실행화면 출력하기
void MainGame::maingGamePage() {


	do {
		graphic.printGamePage();

		gotoXY(0, 7);
		game.backgroundBoardGenerator();

		//백그라운드보드배열의 각 칸 주솟값을 게임보드에 옮겨왔다~ 동작시마다 재호출 안해도 댐
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				gameBoard[i][j] = game.getGameBoard(i, j);
			}
		}

		printBoard();

		do {
			//ESC눌렀을 때 종료되는건 goStop함수에서 처리한다.
			key = _getch();
			//디버그몯if
			/*if (key == 32) {
				game.debugmode();
				cout << endl;
				printBoard();
			}
			else */
			if (key == 224) {
				key = _getch();
				game.hit_kbArrow(key);
				//cout << endl;

					//system("cls");로 하면 화면이 깜빡이므로 일부씩 챠라락 바꾸게끔..
				gotoXY(0, 0);
				printBoard();
			}
			else {
				switch (key) {
				case 49:	//아이템 1번
					break;
				case 50:	//아이템 2번!
					break;
				case 51:	//아이템 3번!!
					break;

				default:
					//cout << "화살표 아닌거 입력" << endl;
					break;
				}
			}
		} while (game.goStop(key));	//while end;

		//goStop return false로 게임 종료시
		txtcolor(15, 3);
		gotoXY(25, 17);
		cout << "게임 종료!";
		txtcolor(15, 0);
		txtcolor(15, 3);
		gotoXY(16, 18);
		printf("%3d턴동안 %4d까지 만들었다!\n", game.getTurn(), game.getHigh());
		txtcolor(15, 0);
		gotoXY(13, 19);
		cout << "나가려면 ESC, 다시 하려면 SPACEbar";

		while (1) {
			key = _getch();
			if ((key == 27) || (key == 32)) break;
		}
	} while (key == 32);

};//func mainGamePage끝

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
}
#pragma endregion
