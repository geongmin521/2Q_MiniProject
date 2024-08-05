#include "../D2DEngine/pch.h"
#include "TitleWorld.h"
#include "BattleWorld.h"
#include "Image.h"
#include "Button.h"
#include "DemoGameApp.h"
#include "../D2DEngine/Factory.h"

TitleWorld::TitleWorld()
{
	//단순한 이미지만 띄우고싶어도.. 버튼 객체랑 그냥 이미지를 만들어야하잖아.. 
	//오브젝트를 만드는것을 생성자에서 처리하지 말고? 다 된이후에 만들면되지않을까?
		//람다식으로 넣어주면 어떤 함수라도 매개변수가 들어갈수있지..

	//일일이 쓰지않도록 업데이트해야겠다.. 
}

TitleWorld::~TitleWorld()
{

}

void TitleWorld::MakeObject()
{
	Factory::GetInstance().get()->CreateGameObject<Button>();//기존의 방식을 그대로 쓰기보다는 
	Factory::GetInstance().get()->CreateGameObject<Button>();//기존의 방식을 그대로 쓰기보다는 //매개변수를 넣고싶으면 어떻게 처리할까? 
	//생성할 오브젝트의 종류에따라 다르게 처리했으면좋겠는데.. 
	InsertGameObject(new Image(L"../Data/Image/Title_main.png")); //이것도 각자가 앞에 경로를
	CreateGameObject<Button>()->AddListener([]() { DemoGameApp::ChangeCurWorld(new BattleWorld); });
}
