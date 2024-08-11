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

void TitleWorld::MakeObject()
{
	Factory().createObj<Image>(L"title.png").setPosition(WinHalfSizeXY);
	Factory().createObj<Button>(L"ImageBack.png", []() { SceneManager::GetInstance().get()->ChangeScene(new BattleWorld); }).setPosition({ WinHalfSizeX, WinHalfSizeY + 200 });//게임시작
	Factory().createObj<Button>(L"ImageBack.png", []() {  }).setPosition({ WinHalfSizeX, WinHalfSizeY + 300 });//환경설정
	Factory().createObj<Button>(L"ImageBack.png", []() { SendMessage(DemoGameApp::hWnd, WM_CLOSE, 0, 0); }).setPosition({ WinHalfSizeX, WinHalfSizeY + 400 }); //게임종료
}
