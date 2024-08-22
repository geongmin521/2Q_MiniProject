#include "pch.h"
#include "TitleWorld.h" 
#include "BattleWorld.h" 
#include "SceneManager.h"
#include "DemoGameApp.h"
#include "Factory.h"
#include "Image.h"
#include "Button.h"
#include "GameManager.h"
#include "Pools.h"
#include "EventSystem.h"
#include "CollisionManager.h"
#include "Music.h"

TitleWorld::TitleWorld()
{
	Music::soundManager->PlayMusic(Music::eSoundList::MainTheme, Music::eSoundChannel::BGM);
}

TitleWorld::~TitleWorld() 
{
}

void TitleWorld::MakeObject()
{
	Make(Image)(L"title.png").setRenderOrder(-100).setScale({0.75f,0.75f}).setPosition(WinHalfSizeXY);
	Make(Image)(L"UI/Title/title.png").setRenderOrder(-100).setScale({0.75f,0.75f}).setPosition(WinHalfSizeXYAdd(-399 + 860/2, -495 + 562 / 2));
	Make(Button)(L"Start", []() { SceneManager::GetInstance().get()->ChangeScene(new BattleWorld); }).setPosition({ WinHalfSizeX, WinHalfSizeY + 200 });//���ӽ���
	Make(Button)(L"EXIT", []() { SendMessage(DemoGameApp::hWnd, WM_CLOSE, 0, 0); }).setPosition({ WinHalfSizeX, WinHalfSizeY + 400 }); //��������
	//gameManager->events[Event::Reset] = [this]() { collisionManager. Pools::GetInstance().get()->reset(); eventSystem->Ui.clear(); eventSystem->curOnMouse.clear(); };
}
