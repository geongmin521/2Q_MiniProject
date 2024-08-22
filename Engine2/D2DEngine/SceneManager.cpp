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
	if (curWorld != nullptr)
	{
		delete curWorld; 
	}
	gameManager->ResetFunc();
	//pool �� �̱����̶� �ʱ�ȭ���س����ϴµ�.. ��� ���������������.. 
	curWorld = world;
	curWorld->MakeObject(); 

}

void SceneManager::reset()
{
	//curWorld = nullptr
}
