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
	//if (gameManager->events[Event::Reset] != nullptr) //처음의 등록을 이전부터해놔야해.. 
	//{
	//	gameManager->events[Event::Reset](); //지워졌는데.. 윈도우 이벤트때문에 들어오는건가?  //먼저 지우고 계속들어온느건가?
	//}

	nextWorld = world;
	isChange = true;
}

void SceneManager::Change()
{

	if (curWorld != nullptr)
	{
		delete curWorld;
	}
	gameManager->ResetFunc();
	curWorld = nextWorld;
	curWorld->MakeObject();
	isChange = false;
}

void SceneManager::reset()
{
	//curWorld = nullptr
}
