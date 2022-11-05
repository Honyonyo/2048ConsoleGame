#include "Block.h"

Block::Block()
{
	setLang("kor");
	for (int i = 6; i < sizeof(boardLine) / sizeof(*boardLine); i += 7) {
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
}

Block::~Block()
{
}

//로고 도트 출력 함수(이름, 도트시작점 X좌표, 도트시작점 Y좌표)
void Block::printLogo(string name, int X, int Y) {
	vector<vector<int>>logoColor;
	vector<vector<string>>logo;

	//함수에 입력받은 name에 따라 해당 csv파일을 open해서 값을 받아온다.
	//색상값 저장한 logoColor_파일 이름 생성
	string logoColor_ = "logoColor_";
	logoColor_.append(name);
	logoColor_.append(".csv");

	//문자값 저장한 logo_파일 이름 생성
	string logo_ = "logo_";
	logo_.append(name);
	logo_.append(".csv");

	//파일 열기 읽기전용 *참고 : 읽쓰fstream, 쓰ofstream
	ifstream file_color;
	file_color.open(logoColor_);

	//파일 로드 안될시 함수 강제종료
	if (!file_color.is_open()) {
		cout << "색깔 파일 로드 실패";
		return;
	}

	/*참고
	* 문자 0 = 48 1 = 49 2 = 50 ... 9 = 57
	* ->문자로 입력된 숫자 - 48을 하면
	*/
	//.h선언된 vector logo/logoColor에 값 받아오기
	string buffer;	//들어온 값을 임시저장해두고 /n(개행문자)일 경우 다음줄로 내려가게 하고 버리기 위함
	vector<int> tmpvector1;
	logoColor.push_back(tmpvector1);
	int i = 0;
	int j = 0;
	//색깔코드 벡터에 받아오기
	while (getline(file_color, buffer, ',')) {
		if (buffer == "\n") {//개행문자 /n이 나오면 i++해줘요. 강제로 while시작점으로 넘겨요.
			logoColor.push_back(tmpvector1);
			i++;
			j = 0;
			continue;
		}
	//	cout << "색파일로드중" << endl;
		char tmp[3] = {'0','0','0'};	//컬러코드 3자리수니까 3으로 지정해벌임 각각 100 10 1의자리숫자, while돌 때마다 소멸 및 생성되므로 찌꺼기 걱정은 없어도 되지 않지 않나 모르겠다 아ㅏ. ->.....하.. 0.. 넣어야함.. 숫자말고 문자로. 안글면 숫자 0으로 전부 초기화돼서 -48했을 때 문자형-48이 아니라 찐숫자 -48이 되더라
		for (int k = 0; k < buffer.size(); k++) {
			tmp[2 - k]=buffer[buffer.size() - 1 - k];
		}	//buffer 25라면 tmp[]에 {0,0,5} > {0,2,5} 이렇게 뒤부터 채워주기
		//각 자릿수 계산 후 vetor pushback
		logoColor[i].push_back((tmp[0] - 48) * 100 + (tmp[1] - 48) * 10 + tmp[2] - 48);
		j++;

	}//while end
	file_color.close();	//다 쓴 파일은 꼭 닫아주기
	//cout << "색파일로드성공";
		

	//문자 벡터에 받아오기
	ifstream file_letter;
	file_letter.open(logo_);
	if (!file_letter.is_open()) {
		cout << "문자파일 로드 실패" << endl;
		return;
	}

	vector<string> tmpvectorstring;
	logo.push_back(tmpvectorstring);
	i = 0;
	j = 0;
	while (getline(file_letter, buffer, ',')) {
	//	cout << "문자파일 로드중 ";
		if (buffer == "\n") {
			logo.push_back(tmpvectorstring);
			i++;
			j = 0;
			continue;
		}
		if(buffer =="")logo[i].push_back(" ");
		else logo[i].push_back(buffer);
	}//while
	file_letter.close();
	//cout << "문자파일로드성공" << endl;

	int rangeI = logo.size() > logoColor.size() ? logoColor.size() : logo.size();
	for (int i = 0; i < rangeI; i++) {
		int rangeJ = logo[i].size() > logoColor[j].size()
			? logoColor[i].size() : logo[j].size();
		gotoXY(X, Y+i);
		for (int j = 0; j < rangeJ; j++) {
			txtcolor(logoColor[i][j]);
			cout.width(2);
			cout << logo[i][j];
		}//for j end
		txtcolor(15);
		cout << endl;
	}//for i end
}


/*가장 첫 시작화면 그래픽 출력함수*/
void Block::printTitle(int coin) {
	gotoXY(17, 11);
	txtcolor(15);
	cout << "♥PRESS ANY KEY TO START♥";

	//로고 출력
	printLogo("MAIN", 15, 23);

	gotoXY(21, 45);
	cout << "¤ COIN = ";
	cout.width(3);
	cout<< coin << " ¤";
	gotoXY(22, 47);
	txtcolor(9);
	cout << "F2 : 상점가기";

	gotoXY(2, 58);
	txtcolor(8);
	cout << "도움말을 보고싶다면 F1을 눌러주세요.";
}

/*도움말 페이지 출력함수*/
void Block::printHelp() {
	printLogo("HELP", 10, 4);
	gotoXY(41, 12);

	
}

void Block::printShop() {

}

/*게임페이지 관련*/
void Block::printBlock(int number, int X, int Y)
{
	int color = 0;
	this->number = number;

	switch (number) {
	case 0:
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
	printLogo("MAIN", 15, 3);

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

 //게임 끝나고 결과메세지 출력


//하단 아이템영역 출력
void Block::printGamePage_item(int a, int b, int c) {
	gotoXY(24, 52);
	cout << "< 아이템 >" << endl << endl;

	cout << "  1.블록지우개       2.저기 봐, 저기!       3.두배두배두" << endl << endl;
	printf("     %3d개                %3d개                 %3d개", a, b, c);
}