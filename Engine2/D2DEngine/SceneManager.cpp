#include "pch.h"
#include "SceneManager.h"
#include "World.h"
#include "EventSystem.h"

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
		EventSystem::GetInstance().get()->Ui.clear(); //이런식으로 포인터를 관리하고싶지않은데.. 쉽게 처리할려면 공유포인터를 써야하나? 
		delete curWorld; //현재 들고있는씬은 소멸하기
	}
		
	curWorld = world;
	curWorld->MakeObject(); 

}