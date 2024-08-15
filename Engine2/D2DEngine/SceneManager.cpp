#include "pch.h"
#include "SceneManager.h"
#include "World.h"
#include "EventSystem.h"
#include "CollisionManager.h"
#include "GameManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{

}	
void SceneManager::ChangeScene(World* world)
{
	if (curWorld != nullptr)
	{
		EventSystem::GetInstance().get()->Ui.clear();
		delete curWorld; 
	}
	//현재 싱글톤인애들. 콜리젼 매니저 게임 매니저 
	collisionManager->Clear();
	gameManager->init();
	curWorld = world;
	curWorld->MakeObject(); 

}