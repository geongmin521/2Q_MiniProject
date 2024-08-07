#include "../D2DEngine/pch.h"
#include "BattleWorld.h"

#include "Map.h"
#include "Camera.h"
#include "ArrowTower.h"
#include "MeleeTower.h"
#include "Button.h"
#include "MoveIcon.h"
#include "EnemySpawner.h"
BattleWorld::BattleWorld()
{

}

BattleWorld::~BattleWorld()
{

}

void BattleWorld::MakeObject()
{
	CreateGameObject<ArrowTower>(); //�����忡 �ʱ� �ʿ��� ������Ʈ �����ϱ�
	CreateGameObject<MeleeTower>();
	CreateGameObject<Button>();
	CreateGameObject<MoveIcon>();
	CreateGameObject<EnemySpawner>();
}
