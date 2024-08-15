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
	//���� �̱����ξֵ�. �ݸ��� �Ŵ��� ���� �Ŵ��� 
	collisionManager->Clear();
	gameManager->init();
	curWorld = world;
	curWorld->MakeObject(); 

}