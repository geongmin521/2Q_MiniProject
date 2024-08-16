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
		collisionManager->Clear();
		gameManager->reset();
		if (gameManager->events[Event::Reset] != nullptr)
		{
			gameManager->events[Event::Reset]();
		}
	}
	//pool �� �̱����̶� �ʱ�ȭ���س����ϴµ�.. ��� ���������������.. 
	curWorld = world;
	curWorld->MakeObject(); 

}