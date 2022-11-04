#include "Block.h"

Block::Block()
{
	for (int i = 6; i < sizeof(boardLine) / sizeof(*boardLine); i+=7) {
		for (int j = 0; j < sizeof(boardLine[0]) / sizeof(*boardLine[0]); j++) {
			if (j % 7 == 6) {
				boardLine[i][j] = "⁙";
			}
			else {
				boardLine[i][j] = "⁛";
				boardLine[j][i] = "⁛";
			}
		}
		
	}
	
	

//	for (int i = 0; i<6; i++)
//{for (int j =0; j<6; j++)
//{
//	cout.width(2);
//	cout << numBlock[BLOCK_128][i][j];
//}
//cout<<endl;
//cout << numBlock[BLOCK_128][0];
//
//cout << endl<< endl;
//cout << numBlock[BLOCK_128][0][0];
//
//}

}

Block::~Block()
{
}


/*		txtcolor(color);
		if (c == " ") cout << "  ";
		else cout << c;

*/

/*가장 첫 시작화면*/
void Block::printLogo(int name,int X,int Y) {
	for (int i = 0; i < sizeof(logo_MAIN) / sizeof(*logo_MAIN); i++) {
		gotoXY(X, 3 + Y);
		for (int j = 0; j < sizeof(logo_MAIN[i]) / sizeof(*logo_MAIN[i]); j++) {
			txtcolor(logoColor_[name][i][j]);
			cout.width(2);
			cout << logo_MAIN[i][j];
		}//for j end
		txtcolor(15);
		cout << endl;
	}//for i end
}

void Block::printTitle(int coin) {
	gotoXY(34, 9);
	cout << "♥PRESS ANY KEY TO START♥";
	printLogo(MAIN, 13, 24);

	
}

/*게임페이지 관련*/
void Block::printBlock(int number, int X, int Y)
{
	int color=0;
	this->number = number;

	switch (number) {
	case 0 : 		
		for (int i = 0; i < 6; i++) {
		gotoXY(X, Y + i);
		for (int j = 0; j < 6; j++) {
			txtcolor(0);
			cout << "  ";
		}
		cout << endl;
	}
		   txtcolor(15, 0);
		   break;


	case 2:
		for (int i = 0; i < 6; i++) {
			gotoXY(X, Y + i);
			for (int j = 0; j < 6; j++) {
				txtcolor(numBlockColor[BLOCK_2][i][j]);
				cout << "  ";
			}
			cout << endl;
		}
		txtcolor(15, 0);
		break;

	case 4:		for (int i = 0; i < 6; i++) {
		gotoXY(X, Y + i);
		for (int j = 0; j < 6; j++) {
			txtcolor(numBlockColor[BLOCK_4][i][j]);
			cout << "  ";
		}
		cout << endl;
	}
		  txtcolor(15, 0);

		break;

	case 8:
		for (int i = 0; i < 6; i++) {
			gotoXY(X, Y + i);
			for (int j = 0; j < 6; j++) {
				txtcolor(numBlockColor[BLOCK_8][i][j]);
				cout << "  ";
			}
			cout << endl;
		}
		txtcolor(15, 0);

		break;


	case 16:
		for (int i = 0; i < 6; i++) {
			gotoXY(X, Y + i);
			for (int j = 0; j < 6; j++) {
				txtcolor(numBlockColor[BLOCK_16][i][j]);
				cout << "  ";
			}
			cout << endl;
		}
		txtcolor(15, 0);

		break;

	case 32:
		for (int i = 0; i < 6; i++) {
			gotoXY(X, Y + i);
			for (int j = 0; j < 6; j++) {
				txtcolor(numBlockColor[BLOCK_32][i][j]);
				cout << "  ";
			}
			cout << endl;
		}
		txtcolor(15, 0);

		break;

	case 64:
		for (int i = 0; i < 6; i++) {
			gotoXY(X, Y + i);
			for (int j = 0; j < 6; j++) {
				txtcolor(numBlockColor[BLOCK_64][i][j]);
				cout << "  ";
			}
			cout << endl;
		}
		txtcolor(15, 0);

		break;

	case 128://128,256 배경 단일색 글씨 단일색이라서 txtcolor가 줄별로 한 번씩만 들어가게 만들었으니, 추후 그래픽 수정되면 이점 고려해서 위의 코드들처럼 다시 구성해야함
		for (int i = 0; i < 6; i++) {
			gotoXY(X, Y + i);
			txtcolor(numBlockColor[BLOCK_128][0][0]);
			for (int j = 0; j < 6; j++) {
					cout.width(2);
					cout << numBlock[BLOCK_128][i][j];
			}
			txtcolor(15, 0);
			cout << endl;
		}
		break;

	case 256:
		for (int i = 0; i < 6; i++) {
			gotoXY(X, Y + i);
			txtcolor(numBlockColor[BLOCK_256][0][0]);
			for (int j = 0; j < 6; j++) {
				cout.width(2);
				cout << numBlock[BLOCK_256][i][j];
			}
			txtcolor(15, 0);
			cout << endl;
		}
		break;

	case 512:
		for (int i = 0; i < 6; i++) {
			gotoXY(X, Y + i);
			for (int j = 0; j < 6; j++) {
				txtcolor(numBlockColor[BLOCK_512][i][j]);
				cout.width(2);
				cout << numBlock[BLOCK_512][i][j];
			}
			cout << endl;
		}
		txtcolor(15, 0);
		break;

	case 1024:
		for (int i = 0; i < 6; i++) {
			gotoXY(X, Y + i);
			for (int j = 0; j < 6; j++) {
				txtcolor(numBlockColor[BLOCK_512][i][j]);
				cout.width(2);
				cout << numBlock[BLOCK_512][i][j];
			}
			cout << endl;
		}
		txtcolor(15, 0);
		break;

	case 2048:
		break;


	
	default:  cout << "블록 생성 에러" << endl;
	}//switch끝





}
//메인 게임페이지 출력
void Block::printGamePage() {
	//게임 로고 프린트
	printLogo(MAIN, 16, 3);

//게임진행영역 선 프린트
	txtcolor(15);
	gotoXY(0, 18);
	cout << gamePage_upLine1 << endl << gamePage_upLine2 << endl;;
	for (int i = 0; i < sizeof(boardLine) / sizeof(*boardLine); i++) {
		for (int j = 0; j < sizeof(boardLine[i]) / sizeof(*boardLine[i]); j++) {
			if (boardLine[i][j].size()) {
				gotoXY((i + 2) * 2, 22 + j);
				cout << boardLine[i][j];
			}//if end
		}//for j end
	}//for i end
	gotoXY(0, 49);
	cout << gamePage_downLine1 << endl << gamePage_downLine2;
}//printGamePage 끝
//하단 아이템영역 출력
void Block::printGamePage_item(int a, int b, int c) {
	gotoXY(24, 52);
	cout << "< 아이템 >" << endl << endl;

	cout << "  1.블록지우개       2.저기 봐, 저기!       3.두배두배두" << endl << endl;
	printf("     %3d개                %3d개                 %3d개", a, b, c);
}