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
	Factory().createObj<Image>(L"title.png").setPosition(WinHalfSizeXY);
	Factory().createObj<Button>(L"ImageBack.png", []() { SceneManager::GetInstance().get()->ChangeScene(new BattleWorld); }).setPosition({ WinHalfSizeX, WinHalfSizeY + 200 }).AddText(L"���ӽ���",50);//���ӽ���
	Factory().createObj<Button>(L"ImageBack.png", []() {  }).setPosition({ WinHalfSizeX, WinHalfSizeY + 300 }).AddText(L"ȯ�漳��", 50);//ȯ�漳��
	Factory().createObj<Button>(L"ImageBack.png", []() { SendMessage(DemoGameApp::hWnd, WM_CLOSE, 0, 0); }).setPosition({ WinHalfSizeX, WinHalfSizeY + 400 }).AddText(L"��������", 50); //��������
}
