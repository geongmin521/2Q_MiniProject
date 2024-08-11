#include "pch.h"
#include "TitleWorld.h" 
#include "BattleWorld.h" //이것도 씬매니저에서 처리하면 여기서 처리 안해도될거임.. 
#include "SceneManager.h"
#include "DemoGameApp.h"
#include "Factory.h"
#include "Image.h"
#include "Button.h"

TitleWorld::TitleWorld()
{
}

TitleWorld::~TitleWorld() //가상소멸자라 자동으로지울듯
{
}

void TitleWorld::MakeObject() //렌더할때 박스크기만큼 미는게 맞겠지? 
{
	Factory().createObj<Image>(L"title.png").setPosition(WinHalfSizeXY);
	Factory().createObj<Button>(L"ImageBack.png", []() { SceneManager::GetInstance().get()->ChangeScene(new BattleWorld); }).setPosition({ WinHalfSizeX, WinHalfSizeY + 200 }).AddText(L"게임시작",50);//게임시작
	Factory().createObj<Button>(L"ImageBack.png", []() {  }).setPosition({ WinHalfSizeX, WinHalfSizeY + 300 }).AddText(L"환경설정", 50);//환경설정
	Factory().createObj<Button>(L"ImageBack.png", []() { SendMessage(DemoGameApp::hWnd, WM_CLOSE, 0, 0); }).setPosition({ WinHalfSizeX, WinHalfSizeY + 400 }).AddText(L"게임종료", 50); //게임종료
}
