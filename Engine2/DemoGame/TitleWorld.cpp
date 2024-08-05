#include "../D2DEngine/pch.h"
#include "TitleWorld.h"
#include "BattleWorld.h"
#include "Image.h"
#include "Button.h"
#include "DemoGameApp.h"

TitleWorld::TitleWorld()
{
	//단순한 이미지만 띄우고싶어도.. 버튼 객체랑 그냥 이미지를 만들어야하잖아.. 

		//람다식으로 넣어주면 어떤 함수라도 매개변수가 들어갈수있지..
	InsertGameObject(new Image(L"../Data/Image/Title_main.png")); //이것도 각자가 앞에 경로를
	CreateGameObject<Button>()->AddListener([]() { DemoGameApp::ChangeCurWorld(new BattleWorld); });
	//일일이 쓰지않도록 업데이트해야겠다.. 
}

TitleWorld::~TitleWorld()
{

}
