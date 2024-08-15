#include "pch.h"
#include "Factory.h"
#include "GameOver.h"
#include "Image.h"
#include "Button.h"
#include "SceneManager.h"
#include "BattleWorld.h"
#include "TitleWorld.h"

GameOver::GameOver() //�¸� �� �й� ��� �ؽ�Ʈ�� �ٲ㼭 ���밡��
{
	Make(Image)(L"BigBack.png").setScale({ 2,2 }).setParent(transform).AddText(L"GAME OVER!!", 80,0,-50);
	Make(Button)(L"ImageBack.png", [this]() {sceneManager->ChangeScene(new BattleWorld); }).setPos_Parent_Text({ 0, 100 }, transform, L"�ٽý���", 30);//�ٽý���
	Make(Button)(L"ImageBack.png", [this]() {sceneManager->ChangeScene(new TitleWorld); }).setPos_Parent_Text({ 0, 200 }, transform, L"����ȭ��", 30);//����ȭ��

	SetActive(false);
}

GameOver::~GameOver()
{
}

