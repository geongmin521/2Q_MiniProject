#include "pch.h"
#include "Combination.h"
#include "Factory.h"
#include "Button.h"
#include "Image.h"
#include "Music.h"

Combination::Combination()
{
	renderOrder += 100;

	Make(Image)(L"UI/Pop_up/popup_Recipe.png").setParent(this->transform);	//���	
	Make(Image)(L"UI/Pop_up/popup_Recipe1p.png").setParent(this->transform).Get(recipe);	//����ǥ	
	Make(Button)(L"Left", [this]() { NextPage(true);
	Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::ButtonClick, Music::eSoundChannel::Effect1); }, ButtonType::Single).setPos_Parent({ -1100, 0 }, this->transform);//���� �������� ��ü
	Make(Button)(L"Right", [this]() { NextPage(false); 
	Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::ButtonClick, Music::eSoundChannel::Effect1); }, ButtonType::Single).setPos_Parent({ 1100, 0 }, this->transform);//������ ��������ü
	Make(Button)(L"Return", [this]() { SetActive(false);
	Music::soundManager->GetInstance()->PlayMusic(Music::eSoundList::PopupClose, Music::eSoundChannel::Effect1); }).setPos_Parent({0, 450},this->transform);//������ ��ư
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
