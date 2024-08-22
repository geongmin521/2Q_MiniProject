#include "pch.h"
#include "Combination.h"
#include "Factory.h"
#include "Button.h"
#include "Image.h"
#include "Music.h"

Combination::Combination()
{
	renderOrder += 100;

	Make(Image)(L"UI/Pop_up/popup_Recipe.png").setParent(this->transform);	//배경	
	Make(Image)(L"UI/Pop_up/popup_Recipe1p.png").setParent(this->transform).Get(recipe);	//조합표	
	Make(Button)(L"Left", [this]() { NextPage(true);
	Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::ButtonClick, Music::eSoundChannel::Effect1); }, ButtonType::Single).setPos_Parent({ -1100, 0 }, this->transform);//왼쪽 페이지로 교체
	Make(Button)(L"Right", [this]() { NextPage(false); 
	Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::ButtonClick, Music::eSoundChannel::Effect1); }, ButtonType::Single).setPos_Parent({ 1100, 0 }, this->transform);//오른쪽 페이조교체
	Make(Button)(L"Return", [this]() { SetActive(false);
	Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::PopupClose, Music::eSoundChannel::Effect1); }).setPos_Parent({0, 450},this->transform);//나가기 버튼
	SetActive(false);
}

Combination::~Combination()
{

}

void Combination::NextPage(bool left)
{
	if (left)
	{
		if (curPage == 1)
		{
			curPage = 0;
			recipe->ChangeImage(L"../Data/Image/UI/Pop_up/popup_Recipe1p.png");
		}
	}
	else
	{
		if (curPage == 0)
		{
			curPage = 1;
			recipe->ChangeImage(L"../Data/Image/UI/Pop_up/popup_Recipe2p.png");
		}
	}
}
