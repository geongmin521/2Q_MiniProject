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
	//���
	//���������
	//�����ư
	Make(Image)(L"UI/Pop_up/popup_Round.png").setParent(this->transform);
	for (int i = 0; i < 4; i++)	
		Make(Image)(L"Enemy/One/NormalEnemy.png").setPos_Parent({LPad + i * 400 ,0}, transform).AddText(L"", 70,0,95).Get<Image>(images[i]);		
	Make(Button)(L"smallBack", [this]() { SetActive(false); }).setPos_Parent({ 400, -400 }, transform);
	SetActive(false);
}

ShowWave::~ShowWave()
{

}

void ShowWave::Show()  //�̰� �������� ������ �Ŵ������� �������°ɷ��ұ� �̰� ���� ó���̱����ٵ�.. 
{
	dataManager->ChoseWave(); //�����׽�Ʈ
	SetActive(true);
	int curid = gameManager->curWaveId;
	WaveData wave = dataManager->getWaveData(curid);
	int size = wave.enemyId.size();
	for (int i = 0; i < size; i++) 
	{
		images[i]->ChangeImage(L"../Data/Image/Enemy/One/"+ Utility::convertFromString(dataManager->getEnemyData(wave.enemyId[i]).name) + L".png");
		images[i]->GetComponent<D2DFont>()->SetDialog(L"X "+ std::to_wstring(wave.enemyCount[i])); 
	}
	for (int i = size; i < 4; i++) 
	{
		images[i]->SetActive(false);
	}
}


