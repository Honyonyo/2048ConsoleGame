#include "MainGame.h"
//#include <stdio.h>


//게임동작에는 애니메이션 없어도 됨
//화살표를 누르면,

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
* 미니보드 먼저 움직이고 이 결과를 화면에 출력한다.!!!오 예~
*
*
*
* */

void main() {
	system("mode con cols=60 lines=60");	//콘솔 사이즈 60*60변경
	SetConsoleOutputCP(CP_UTF8);
	CursorView();

	MainGame mg;
	mg.tilePage();
	//mg.maingGamePage();
		


	cout << endl << endl;




		//원리는 모르겠으나 이렇게하면 특특수문자 이모지가 나오앙ㅇ!!
		/*textcolor(15, 0);
		cout << utf16_to_utf8(u"————————————————————————————————————————————————————————————") << endl;
		cout << utf16_to_utf8(u"‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=") << endl << endl;


		textcolor(2, 15);*/




		//제어판 시간국가설정에서 국가 밑에 beta기능 켰다..
		// 
		//for (int i = 0; i < 16; i++) {
		//	for (int j = 0; j < 16; j++) {
		//		textcolor(i, j);
		//		printf("%3d %3d", i, j);
		//	}
		//	cout << endl;
		//}



		//textcolor(15, 0);
		//cout << utf16_to_utf8(u"‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=") << endl;
		//cout << utf16_to_utf8(u"————————————————————————————————————————————————————————————") << endl;



}


