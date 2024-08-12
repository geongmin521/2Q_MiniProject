#include "pch.h"
#include "Factory.h"
#include "GameOver.h"
#include "Image.h"
#include "Button.h"
#include "SceneManager.h"
#include "BattleWorld.h"
#include "TitleWorld.h"


GameOver::GameOver()
{
	Factory().createObj<Image>(L"BigBack.png").setPosition(WinHalfSizeXY).setScale({ 2,2 }).setParent(this->transform);
	Factory().createObj<Button>(L"ImageBack.png", [this]() {SceneManager::GetInstance().get()->ChangeScene(new BattleWorld); }).
		setPosition({ WinHalfSizeX, WinHalfSizeY + 100 }).setParent(this->transform);//다시시작
	Factory().createObj<Button>(L"ImageBack.png",[this]()  {SceneManager::GetInstance().get()->ChangeScene(new TitleWorld); }).
		setPosition({ WinHalfSizeX, WinHalfSizeY + 300 }).setParent(this->transform);//메인화면
}

GameOver::~GameOver()
{
}

