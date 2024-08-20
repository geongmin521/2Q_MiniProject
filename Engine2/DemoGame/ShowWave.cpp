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
	float LPad = -200;
	//배경
	//적들아이콘
	//종료버튼
	Make(Image)(L"BigBack.png").setScale({2,2}).setParent(this->transform);
	for (int i = 0; i < 4; i++)
		Make(Image)(L"vampire.png").setPos_Parent({ LPad + i * 130 ,0 }, transform).AddText(L"", 20, 0, 25).Get<Image>(images[i]);
	Make(Button)(L"smallBack.png", [this]() { SetActive(false); }).setPos_Parent({ 400, -400 }, transform);
	SetActive(false);
}

ShowWave::~ShowWave()
{

}


void ShowWave::Show()  //이게 보여질때 데이터 매니저한테 가져오는걸로할까 이게 제일 처음이긴할텐데.. 
{
	dataManager->ChoseWave(); //오류테스트
	SetActive(true);
	int curid = gameManager->curWaveId;
	WaveData wave = dataManager->getWaveData(curid);
	int size = wave.enemyId.size();
	for (int i = 0; i < size; i++) 
	{
		images[i]->ChangeImage(L"../Data/Image/" + Utility::convertFromString(dataManager->getEnemyData(wave.enemyId[i]).name) + L".png");
		images[i]->GetComponent<D2DFont>()->SetDialog(L"X "+ std::to_wstring(wave.enemyCount[i]));
	}
	for (int i = size; i < 4; i++) 
	{
		images[i]->SetActive(false);
	}
}


