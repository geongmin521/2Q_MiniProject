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
	//if (gameManager->events[Event::Reset] != nullptr) //ó���� ����� ���������س�����.. 
	//{
	//	gameManager->events[Event::Reset](); //�������µ�.. ������ �̺�Ʈ������ �����°ǰ�?  //���� ����� ��ӵ��´��ǰ�?
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
