#include "../D2DEngine/pch.h"
#include "TitleWorld.h"
#include "BattleWorld.h"
#include "Image.h"
#include "Button.h"
#include "DemoGameApp.h"

TitleWorld::TitleWorld()
{
	//�ܼ��� �̹����� ����;.. ��ư ��ü�� �׳� �̹����� ���������ݾ�.. 

		//���ٽ����� �־��ָ� � �Լ��� �Ű������� ��������..
	InsertGameObject(new Image(L"../Data/Image/Title_main.png")); //�̰͵� ���ڰ� �տ� ��θ�
	CreateGameObject<Button>()->AddListener([]() { DemoGameApp::ChangeCurWorld(new BattleWorld); });
	//������ �����ʵ��� ������Ʈ�ؾ߰ڴ�.. 
}

TitleWorld::~TitleWorld()
{

}
