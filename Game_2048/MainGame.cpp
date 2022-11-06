#include "MainGame.h"

#pragma region Class MainGame
//2048게임 4*4 보드 출력 함수 ( mainGamePage에서 호출)
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

//제일 처음 뜨는 타이틀페이지 호출
short MainGame::titlePage()
{
	//각 키 입력에 따라 동작함.
	graphic.printTitle(coin);
		switch (_getch()) {
		case 0:
			switch (_getch()) {
			case 59:
				return HELP;
				break;

			case 60:
				return SHOP;
				break;
			default: return GAME;
			}
			  break;

		case 49:
			if (++coin > 99) {
				gotoXY(1, 44);

				txtcolor(4, 7);
				gotoXY(21, 45);
				cout << "¤ COIN = ";
				cout.width(3);
				cout << coin << " ¤";
				gotoXY(1, 47);

				cout << "과욕은 금물입니다 . . . ";
				coin=10;
				system("PAUSE");				
			}
			txtcolor(15);
			return TITLE;
			break;

		default:
			system("cls");
			return GAME;
		
	}

}

//도움말 페이지 호출 (덜구현)
short MainGame::helpPage() {
	graphic.printHelp(1,1);
	int list_number = 1;
	while (1) {
		
		int btn = _getch();
		if(btn == 224){	//화살표입력
			switch (btn=_getch()) {
			case 72:	//위
				list_number--;
				if (list_number == 0) {
					list_number = 4;
					graphic.printHelp(1, list_number);
				}else graphic.printHelp(list_number + 1, list_number);
				break;
			case 80:	//아래
				list_number++;
				if (list_number == 5) {
					list_number = 1;
					graphic.printHelp(4, list_number);
				}
				else graphic.printHelp(list_number - 1, list_number);
				break;
			}
		}
		else {
			switch (btn) {
			case 27: return TITLE;
			case 49: graphic.printHelp(list_number, 1); list_number = 1; break;
			case 50: graphic.printHelp(list_number, 2); list_number = 2; break;
			case 51: graphic.printHelp(list_number, 3); list_number = 3; Sleep(300); break;
			case 52: graphic.printHelp(list_number, 4); Sleep(300); return TITLE;
			case 32: //스페이스바
				if (list_number == 3) {
					
				}
				else if (list_number == 4) return TITLE;
				   break;
			case 13://엔터
				if (list_number == 3) {

				}
				else if (list_number == 4) return TITLE;
				break;
			}//switch
		}
	}//while
}//helpPage()

//상점 페이지 (덜구현)
short MainGame::shopPage() {
	graphic.printShop();
	graphic.gamePage_downLine();
	graphic.printGamePage_item(game.getName_eraser(), game.getEa_eraser(), game.getName_shaker(), game.getEa_shaker(), game.getName_doubler(), game.getEa_doubler());

	while (1) {
		int btn = _getch();
		switch (btn) {
		case 49:
			if (coin >= 3) {
			coin -= 3;
			game.plus_eraser();
		}
			break;
		case 50:
			if (coin >= 5) {
				coin -= 5;
				game.plus_shaker();
			}
				break;
		case 51:
			if (coin >= 15) {
				coin -= 15;
				game.plus_doubler();
			}
				break;

		case 27: return TITLE;
		}
		graphic.printGamePage_item(game.getName_eraser(), game.getEa_eraser(), game.getName_shaker(), game.getEa_shaker(), game.getName_doubler(), game.getEa_doubler());
	}
}

//게임실행화면 출력하기
short MainGame::mainGamePage() {
	key = 0;
	do {

		game.backgroundBoardGenerator();
		graphic.printGamePage();
		graphic.printGamePage_item(game.getName_eraser(), game.getEa_eraser(), game.getName_shaker(), game.getEa_shaker(), game.getName_doubler(), game.getEa_doubler());

		gotoXY(0, 7);

		//백그라운드보드배열의 각 칸 주솟값을 게임보드에 옮겨옴.
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				gameBoard[i][j] = game.getGameBoard(i, j);
			}
		}
		printBoard();

		do {
			//ESC눌렀을 때 종료되는건 goStop함수에서 처리한다.
			key = _getch();
			//화살표 누를시
			if (key == 224) {
				key = _getch();
				game.hit_kbArrow(key);
				//cout << endl;

				//system("cls");로 하면 화면이 깜빡이므로 일부씩 챠라락 바꾸게끔..
				gotoXY(0, 0);
				printBoard();
			}
			//화살표 아닐시
			else {
				if (game.hit_isThat_item(key)) {

					graphic.printGamePage_item(game.getName_eraser(), game.getEa_eraser(), game.getName_shaker(), game.getEa_shaker(), game.getName_doubler(), game.getEa_doubler());

					printBoard();
					graphic.gamePage_downLine();
				}
			}//else

			game.set_HighestNumber();

			if (game.getHigh() == 2048) break;
		} while (game.goStop(key));	//while end;

			short y = 17;
		if (game.getHigh() == 2048) {//2048만들고 승리
			txtcolor(2, 14);
			gotoXY(13, y);
			cout.width(12);
			cout << " ";
			cout << "게임 승리!";
			cout.width(12);
			cout << " ";
			txtcolor(15, 0);
			gotoXY(13, y + 1);
			printf("  %3d턴만에 2048을 완성했다~~!!   \n", game.getTurn());
		} else {//goStop return false로 게임 종료시
			txtcolor(15, 3);
			gotoXY(13, y);
			cout.width(12);
			cout << " ";
			cout << "게임 종료!";
			cout.width(12);
			cout << " ";
		txtcolor(15, 0);
			gotoXY(13, y + 1);
			printf("   %3d턴동안 %4d까지 만들었다!   \n", game.getTurn(), game.getHigh());
		}
		gotoXY(13, y + 2);
		cout << "나가려면 ESC, 다시 하려면 SPACEbar";

		while (1) {
			key = _getch();
			if (key == 27) return TITLE;
			if (key == 32) break;
		}
	} while (key == 32);

};//func mainGamePage끝

MainGame::MainGame()
{
	short pageBtn = titlePage();
	while (1) {

		switch (pageBtn) {
		case TITLE : 
			system("cls");
			pageBtn = titlePage();
			break;
		case HELP: 
			system("cls"); 
			pageBtn = helpPage();
			break;
		case SHOP :
			system("cls"); 
			pageBtn = shopPage();
			break;
		case GAME: 
			system("cls"); 
			pageBtn = mainGamePage();
			break;
		}
	}
}

MainGame::~MainGame()
{
	
}
#pragma endregion
