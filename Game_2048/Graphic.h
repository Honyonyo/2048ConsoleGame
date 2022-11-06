#pragma once
#include <iostream>
#include <Windows.h>
#include <codecvt>
#include <conio.h>
#include <fstream>

#include <string>
#include <string.h>
#include <vector>

using namespace std;

/*
주요 키워드들을 #define으로 숫자 선언해준 뒤 편리하게 이용함
*/
#define TITLE 00
#define HELP 100
#define SHOP 200
#define GAME 300

#define BLOCK_2 0
#define BLOCK_4 1
#define BLOCK_8 2
#define BLOCK_16 3
#define BLOCK_32 4
#define BLOCK_64 5
#define BLOCK_128 6
#define BLOCK_256 7
#define BLOCK_512 8
#define BLOCK_1024 9
#define BLOCK_2048 10


/*
각종 블록과 게임 내 이미지구현부분을 담당하게 할 예정
*/

//만물공용함수, 아무데서나 꺼내쓰기 위해 함수 static선언
static void txtcolor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

}
static void txtcolor(int tcolor, int bcolor)
{
	int color = tcolor + bcolor * 16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);

}
static void gotoXY(short X, short Y) {
	COORD pos = { X,Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
static void CursorView()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
	cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}
static string utf16_to_utf8(std::u16string utf16_string)
{
	std::wstring_convert<std::codecvt_utf8_utf16<int16_t>, int16_t> convert;
	auto p = reinterpret_cast<const int16_t*>(utf16_string.data());
	return convert.to_bytes(p, p + utf16_string.size());
}
static string utf32_to_utf8(std::u32string utf32_string)
{
	std::wstring_convert<std::codecvt_utf8<int32_t>, int32_t> convert;
	auto p = reinterpret_cast<const int32_t*>(utf32_string.data());
	return convert.to_bytes(p, p + utf32_string.size());
}


/*
파일입출력시 특수문자 껴있는 경우 깨질 수도 있으니
메모장에서 인코딩 utf-8로 해줘야한다.
*/
class Block

{
private:
	int number;
	int pointX=0;
	int pointY;
	string textsetting="text_";
	string language = "kor";	//언어팩 설정하기
	string help_menu[4];
	vector<string>about_game;
	vector<string>::iterator iter;
	vector<string>how_to_play;
	vector<string>language_list;


	//숫자 블록 색깔담당자
	const int numBlockColor[11][6][6] =
	{
		//넘버블록 2
		{
			{238,238,238,238,238,238},
		{238,238,   0,   0,   0,238},
		{238,238,238,238,   0,238},
		{238,238,   0,   0,   0,238},
		{238,238,   0,238,238,238},
		{238,238,   0,   0,   0,238}
		},
		//넘버블록 4
		{
		{238,238,238,238,238,238},
		{238,102,238,102,238,238},
		{238,102,238,102,238,238},
		{238,102,102,102,102,238},
		{238,238,238,102,238,238},
		{238,238,238,238,238,238}
		},
		//넘버블록8
		{
			{102,102,102,102,102,102},
		{102,102,255,255,255,102},
		{102,102,255,102,255,102},
		{102,102,255,255,255,102},
		{102,102,255,102,255,102},
		{102,102,255,255,255,102},
		},
		//넘버블록16
		{
			{187,187,187,187,187,187},
		{187,255,187,255,187,187},
		{187,255,187,255,187,187},
		{187,255,187,255,255,255},
		{187,255,187,255,187,255},
		{187,255,187,255,255,255}
},
//넘버블록32
{	{153,153,153,153,153,153},
	{238,238,238,255,255,255},
	{153,153,238,153,153,255},
	{238,238,238,255,255,255},
	{153,153,238,255,153,153 },
	{238, 238, 238, 255, 255, 255}},

		//넘버블록 64
		{
			{85,85,255,85,255,85},
{238,85,255,85,255,85},
{238,85,255,255,255,255},
{238,238,238,85,255,85},
{238,85,238,85,255,85},
{238,238,238,85,85,85}
},

//넘버블록 128
{95
},

//넘버블록 256
{175,
15,//글씨색
10//배경색

},

//넘버블록 512
		{
			{250,250,250,250,250,250},
		{250,175,175,175,175,250},
		{250,175,175,175,175,250},
		{250,175,175,175,175,250},
		{250,175,175,175,175,250},
		{250,250,250,250,250,250}

},

//넘버블록 1024
		{
			{191,191,191,191,191,191},
		{191,251,251,251,251,191},
		{191,251,251,251,251,191},
		{191,251,251,251,251,191},
		{191,251,251,251,251,191},
			{191,191,191,191,191,191}
},

//넘버블록 2048
		{
		{47,47,47,47,47,47},
		{47,15,15,15,15,47},
		{47,15,15,15,15,47},
		{47,15,15,15,15,47},
		{47,15,15,15,15,47},
		{47,47,47,47,47,47}
}

	};
	//숫자 블록 내용물글씨 담당자
	const string numBlock[11][6][6] = {
		{/*2*/},{/*4*/},{/*8*/},{/*16*/},{/*32*/},{/*64*/},
		//128
		{"■","▼","▼","▼","▼","■",
		"▶"," "," "," "," ","◀",
		"▶"," ","1","2","8","◀",
		"▶"," ","백","이","팔","◀",
		"▶"," "," ","십"," ","◀",
		"■","▲","▲","▲","▲","■"},
		//256
		{"■","▼","▼","▼","▼","■",
		"▶"," "," "," "," ","◀",
		"▶"," ","2","5","6","◀",
		"▶"," ","이","오","육","◀",
		"▶"," ","백","십"," ","◀",
		"■","▲","▲","▲","▲","■"},
		//512
			{
				"■","▼","▼","▼","▼","■",
		"▶"," "," "," "," ","◀",
		"▶"," ","5","1","2","◀",
		"▶"," ","오"," ","이","◀",
		"▶"," ","백","십"," ","◀",
		"■","▲","▲","▲","▲","■"},
		//1024
		{"■","▼","▼","▼","▼","■",
	"▶"," "," "," "," ","◀",
	"▶","1","0","2","4","◀",
	"▶"," "," ","이","사","◀",
	"▶","천"," ","십"," ","◀",
	"■","▲","▲","▲","▲","■"},
	//2048
	{"■","▼","▼","▼","▼","■",
"▶"," "," "," "," ","◀",
"▶","2","0","4","8","◀",
"▶","이"," ","사","팔","◀",
"▶","천"," ","십"," ","◀",
"■","▲","▲","▲","▲","■"}

	};
	
	string gamePage_upLine1 = utf16_to_utf8(u"————————————————————————————————————————————————————————————");
	string gamePage_upLine2 = utf32_to_utf8(U"‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗‗");
	string gamePage_downLine1 = utf32_to_utf8(U"‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=‗=");
	string gamePage_downLine2 = utf16_to_utf8(u"————————————————————————————————————————————————————————————"); 
	string boardLine[27][27];

public:

	Block();
	~Block();
	void setLang(string lang);
	void printLogo(string name, int X, int Y);

	//게임시작페이지
	void printTitle(int coin);
	//F1메뉴, 이전선택a 현재선택b 화살표흔적 지우기 위함
	void printHelp(short a, short b);
	//상점
	void printShop();
	//게임페이지
	void printGamePage();
	
	//게임페이지 레이아웃 구성요소
	void printBlock(int number, int X, int Y);
	void printGamePage_item(string a_name, int a, string b_name, int b, string c_name, int c);
	void gamePage_downLine();
	};