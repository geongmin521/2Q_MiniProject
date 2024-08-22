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
	Music::soundManager->GetInstance()->SetVolume(0.3f, Music::eSoundChannel::BGM);
}

TitleWorld::~TitleWorld() 
{
}

void TitleWorld::MakeObject()
{
	Make(Image)(L"title.png").setRenderOrder(-100).setScale({0.75f,0.75f}).setPosition(WinHalfSizeXY);
	Make(Image)(L"UI/Title/title.png").setRenderOrder(-100).setScale({0.75f,0.75f}).setPosition(WinHalfSizeXYAdd(0, -200));
	Make(Button)(L"Start", []() { SceneManager::GetInstance().get()->ChangeScene(new BattleWorld); 
	Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::MainButtonClick, Music::eSoundChannel::Effect1); }).setPosition({ WinHalfSizeX, WinHalfSizeY + 200 });//게임시작
	Make(Button)(L"EXIT", []() { 
		Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::MainButtonClick, Music::eSoundChannel::Effect1);
		SendMessage(DemoGameApp::hWnd, WM_CLOSE, 0, 0); }).setPosition({ WinHalfSizeX, WinHalfSizeY + 400 }); //게임종료
	//gameManager->events[Event::Reset] = [this]() { collisionManager. Pools::GetInstance().get()->reset(); eventSystem->Ui.clear(); eventSystem->curOnMouse.clear(); };
}
