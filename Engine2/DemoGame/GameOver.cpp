#include "pch.h"
#include "Factory.h"
#include "GameOver.h"
#include "Image.h"
#include "Button.h"
#include "SceneManager.h"
#include "BattleWorld.h"
#include "TitleWorld.h"

GameOver::GameOver() //승리 및 패배 모두 텍스트만 바꿔서 재사용가능
{
	Make(Image)(L"UI/Pop_up/Popup_Gameover.png").setParent(transform);
	Make(Button)(L"retry", [this]() {sceneManager->ChangeScene(new BattleWorld); }).setPos_Parent_Text({ 0, 100 }, transform, L"다시시작", 30);//다시시작
	Make(Button)(L"turnmain", [this]() {sceneManager->ChangeScene(new TitleWorld); }).setPos_Parent_Text({ 0, 200 }, transform, L"메인화면", 30);//메인화면

	SetActive(false);
}

GameOver::~GameOver()
{
}

