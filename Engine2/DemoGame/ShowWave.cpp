#include "pch.h"
#include "Factory.h"
#include "ShowWave.h"
#include "Image.h"
#include "Button.h"
#include "DataManager.h"
#include "GameManager.h"
#include "Image.h"
#include "D2DFont.h"

ShowWave::ShowWave()
{
	float LeftPadding = 800;
	Factory().createObj<Image>(L"BigBack.png").setPosition({WinHalfSizeX ,WinHalfSizeY}).setScale({2,2}).setParent(this->transform);
	for (int i = 0; i < 4; i++)
	{
		images[i] = Factory().createObj<Image>(L"vampire.png").setPosition({LeftPadding + i * 130 ,WinHalfSizeY}).AddText(L"", 20,0,25).setParent(this->transform).Get<Image>();
	}
		
	Factory().createObj<Button>(L"smallBack.png", [this]() { SetActive(false); }).setPosition({ WinHalfSizeX + 400, WinHalfSizeY - 400 }).setParent(this->transform);
	SetActive(false);
}

ShowWave::~ShowWave()
{

}

void ShowWave::Show() 
{
	SetActive(true);
	int curid = gameManager->curWaveId;
	WaveData wave = DataManager::GetInstance().get()->getWaveData(curid);
	int size = wave.enemyId.size();
	for (int i = 0; i < size; i++) 
	{
		images[i]->ChangeImage(L"../Data/Image/vampire.png");
		images[i]->GetComponent<D2DFont>()->SetDialog(L"X "+ std::to_wstring(wave.enemyCount[i])); 
	}
	for (int i = size; i < 4; i++) 
	{
		images[i]->SetActive(false);
	}
}


