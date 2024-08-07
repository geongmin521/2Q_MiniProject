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
}
