#include "../D2DEngine/pch.h"
#include "TitleWorld.h" 
#include "BattleWorld.h" //이것도 씬매니저에서 처리하면 여기서 처리 안해도될거임.. 
#include "DemoGameApp.h"
#include "Factory.h"

TitleWorld::TitleWorld()
{
}

TitleWorld::~TitleWorld()
{

}

void TitleWorld::MakeObject() //월드가 변경될때 기존에 월드에 있던거는 삭제하도록 만들기.. 
{
	Fac->CreateImage(L"title.png", WinHalfSizeXY);
	Fac->CreateButton(L"GameStart.png", []() { DemoGameApp::ChangeCurWorld(new BattleWorld); } ,{ WinHalfSizeX, WinHalfSizeY + 200 }); //게임시작
	Fac->CreateButton(L"GameStart.png", []() {  } ,{ WinHalfSizeX, WinHalfSizeY + 300 }); //환경설정
	Fac->CreateButton(L"GameStart.png", []()  { SendMessage(DemoGameApp::hWnd, WM_CLOSE, 0, 0); }, { WinHalfSizeX, WinHalfSizeY + 400 }); //게임종료
	//흠종료는 잘되는데 .. 또 전역변수를 써버렸다.. 
	//흠 더 짧게 쓰고싶어.. 그럴려면 이미지따로.. 버튼의 기능 따로 그런 컴포넌트 형식으로 만들어야했었을텐데..
	//아닌가? 
}
//람다식이 미친듯이 긴거같은데 따로 빼볼까? 

//다형성을 어떻게 만들지가 고민이고..    