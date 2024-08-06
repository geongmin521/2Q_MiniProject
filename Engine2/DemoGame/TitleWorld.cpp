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
	//단순한 이미지만 띄우고싶어도.. 버튼 객체랑 그냥 이미지를 만들어야하잖아.. 
	//오브젝트를 만드는것을 생성자에서 처리하지 말고? 다 된이후에 만들면되지않을까?
		//람다식으로 넣어주면 어떤 함수라도 매개변수가 들어갈수있지..

	//일일이 쓰지않도록 업데이트해야겠다.. 
}

TitleWorld::~TitleWorld()
{

}

void TitleWorld::MakeObject() //월드가 변경될때 기존에 월드에 있던거는 삭제하도록 만들기.. 
{
	Image* img = new Image(L"../Data/Image/title.png");
	img->transform->SetRelativeLocation({ WinHalfSizeX, WinHalfSizeY });
	InsertGameObject(img);
	Button* btn = Factory::GetInstance().get()->CreateGameObject<Button>();
	btn->AddListener([]() { DemoGameApp::ChangeCurWorld(new BattleWorld); });
	btn->transform->SetRelativeLocation({ WinHalfSizeX, WinHalfSizeY + 300 });
}
