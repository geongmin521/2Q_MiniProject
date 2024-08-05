#include "../D2DEngine/pch.h"
#include "TitleWorld.h"
#include "BattleWorld.h"
#include "Image.h"
#include "Button.h"
#include "DemoGameApp.h"
#include "../D2DEngine/Factory.h"

TitleWorld::TitleWorld()
{
	//�ܼ��� �̹����� ����;.. ��ư ��ü�� �׳� �̹����� ���������ݾ�.. 
	//������Ʈ�� ����°��� �����ڿ��� ó������ ����? �� �����Ŀ� ��������������?
		//���ٽ����� �־��ָ� � �Լ��� �Ű������� ��������..

	//������ �����ʵ��� ������Ʈ�ؾ߰ڴ�.. 
}

TitleWorld::~TitleWorld()
{

}

void TitleWorld::MakeObject()
{
	Factory::GetInstance().get()->CreateGameObject<Button>();//������ ����� �״�� ���⺸�ٴ� 
	Factory::GetInstance().get()->CreateGameObject<Button>();//������ ����� �״�� ���⺸�ٴ� //�Ű������� �ְ������ ��� ó���ұ�? 
	//������ ������Ʈ�� ���������� �ٸ��� ó�����������ڴµ�.. 
	InsertGameObject(new Image(L"../Data/Image/Title_main.png")); //�̰͵� ���ڰ� �տ� ��θ�
	CreateGameObject<Button>()->AddListener([]() { DemoGameApp::ChangeCurWorld(new BattleWorld); });
}
