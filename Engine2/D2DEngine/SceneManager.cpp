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
	if (gameManager->events[Event::Reset] != nullptr) //ó���� ����� ���������س�����.. 
	{
		gameManager->events[Event::Reset](); //�������µ�.. ������ �̺�Ʈ������ �����°ǰ�?  //���� ����� ��ӵ��´��ǰ�?
	}
	if (curWorld != nullptr)
	{
		EventSystem::GetInstance().get()->Ui.clear();
		delete curWorld; 
		collisionManager->Clear();
		gameManager->reset();
	}
	//pool �� �̱����̶� �ʱ�ȭ���س����ϴµ�.. ��� ���������������.. 
	curWorld = world;
	curWorld->MakeObject(); 

}