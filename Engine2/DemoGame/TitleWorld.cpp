#include "pch.h"
#include "TitleWorld.h" 
#include "BattleWorld.h" 
#include "SceneManager.h"
#include "DemoGameApp.h"
#include "Factory.h"
#include "Image.h"
#include "Button.h"

TitleWorld::TitleWorld()
{
}

TitleWorld::~TitleWorld() 
{
}

void TitleWorld::MakeObject()
{
	Make(Image)(L"TitleWorld.png").setScale({0.75f,0.75f}).setPosition(WinHalfSizeXY);
	Make(Image)(L"Title.png").setScale({ 0.7f,0.7f }).setPosition({ WinHalfSizeX,WinHalfSizeY - 200 });
	Make(Button)(L"ImageBack.png", []() { SceneManager::GetInstance().get()->ChangeScene(new BattleWorld); }).setPosition({ WinHalfSizeX, WinHalfSizeY + 200 }).AddText(L"���ӽ���",50);//���ӽ���
	Make(Button)(L"ImageBack.png", []() {  }).setPosition({ WinHalfSizeX, WinHalfSizeY + 300 }).AddText(L"ȯ�漳��", 50);//ȯ�漳��
	Make(Button)(L"ImageBack.png", []() { SendMessage(DemoGameApp::hWnd, WM_CLOSE, 0, 0); }).setPosition({ WinHalfSizeX, WinHalfSizeY + 400 }).AddText(L"��������", 50); //��������
}
