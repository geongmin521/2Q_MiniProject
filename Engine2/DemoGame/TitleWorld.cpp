#include "../D2DEngine/pch.h"
#include "TitleWorld.h"
#include "BattleWorld.h"
#include "Image.h"
#include "Button.h"
#include "DemoGameApp.h"
#include "../D2DEngine/Factory.h"
#include "../D2DEngine/Transform.h"

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

void TitleWorld::MakeObject() //���尡 ����ɶ� ������ ���忡 �ִ��Ŵ� �����ϵ��� �����.. 
{
	Image* img = new Image(L"../Data/Image/title.png");
	img->transform->SetRelativeLocation({ WinHalfSizeX, WinHalfSizeY });
	InsertGameObject(img);
	Button* btn = Factory::GetInstance().get()->CreateGameObject<Button>();
	btn->AddListener([]() { DemoGameApp::ChangeCurWorld(new BattleWorld); });
	btn->transform->SetRelativeLocation({ WinHalfSizeX, WinHalfSizeY + 300 });
}
