#include "../D2DEngine/pch.h"
#include "BattleWorld.h"

#include "Map.h"
#include "Camera.h"
#include "ArrowTower.h"
#include "Button.h"
#include "MoveIcon.h"

BattleWorld::BattleWorld()
{

}

BattleWorld::~BattleWorld()
{

}

void BattleWorld::MakeObject()
{
	CreateGameObject<ArrowTower>(); //각월드에 초기 필요한 오브젝트 생성하기
	CreateGameObject<Button>();
	CreateGameObject<MoveIcon>();
}
