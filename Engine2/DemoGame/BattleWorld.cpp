#include "../D2DEngine/pch.h"
#include "BattleWorld.h"

#include "Map.h"
#include "Camera.h"
#include "Button.h"
#include "MoveIcon.h"
#include "EnemySpawner.h"
#include "Image.h"
#include "ArrowTower.h"
#include "MeleeTower.h"
#include "HealingTower.h"
#include "../D2DEngine/Transform.h"
BattleWorld::BattleWorld()
{

}

BattleWorld::~BattleWorld()
{

}

void BattleWorld::MakeObject()
{
	Image* img = new Image(L"../Data/Image/낮.png");
	img->transform->SetRelativeLocation({ WinHalfSizeX, WinHalfSizeY });
	InsertGameObject(img);

	CreateGameObject<ArrowTower>(); //각월드에 초기 필요한 오브젝트 생성하기
	CreateGameObject<MeleeTower>();
	CreateGameObject<HealingTower>();
	CreateGameObject<Button>();
	CreateGameObject<MoveIcon>();
	CreateGameObject<EnemySpawner>();
}
