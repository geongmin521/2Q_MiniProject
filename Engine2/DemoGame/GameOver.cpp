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
	Factory().createObj<Image>(L"BigBack.png").setPosition(WinHalfSizeXY).setScale({ 2,2 }).setParent(this->transform).AddText(L"GAME OVER!!", 80,0,-50);
	Factory().createObj<Button>(L"ImageBack.png", [this]() {SceneManager::GetInstance().get()->ChangeScene(new BattleWorld); }).
		setPosition({ WinHalfSizeX, WinHalfSizeY + 100 }).setParent(this->transform).AddText(L"�ٽý���", 30);//�ٽý���
	Factory().createObj<Button>(L"ImageBack.png",[this]()  {SceneManager::GetInstance().get()->ChangeScene(new TitleWorld); }).
		setPosition({ WinHalfSizeX, WinHalfSizeY + 200 }).setParent(this->transform).AddText(L"����ȭ��", 30);//����ȭ��
}

GameOver::~GameOver()
{
}

