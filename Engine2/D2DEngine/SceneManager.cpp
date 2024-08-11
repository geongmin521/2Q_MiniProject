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
		EventSystem::GetInstance().get()->Ui.clear(); //�̷������� �����͸� �����ϰ����������.. ���� ó���ҷ��� ���������͸� ����ϳ�? 
		delete curWorld; //���� ����ִ¾��� �Ҹ��ϱ�
	}
		
	curWorld = world;
	curWorld->MakeObject(); 

}