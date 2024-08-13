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
		//텍스트도 추가하기... //이것도 팩토리에 추가가능이긴한데.. 대신UI로 형변환이되어야함.. 아닌가? 다른애들도 필요한가? 
	}
		
	Factory().createObj<Button>(L"smallBack.png", [this]() { SetActive(false); }).setPosition({ WinHalfSizeX + 400, WinHalfSizeY - 400 }).setParent(this->transform);
	SetActive(false);
}

ShowWave::~ShowWave()
{
	//지워질때 지금까지 만든 모든 ui를 지워줘야함.. 사실 아무리 모임이라도.. 얘네가 따로 들고있는게 맘에 안들긴하거든? 어디 다른벡터에 담아주는거까진 인정인데... 결국 월드의 통제를 받아야함.. 
	//그리고 어차피 배열에 담았으니.. 키고 끄는것도 따로 통제할수있을거아니야.. 음.. 월드한테 맡기는게 나음. 
}

void ShowWave::Show() //게임
{
	SetActive(true);
	int curid = gameManager->curWaveId;
	WaveData wave = DataManager::GetInstance().get()->getWaveData(curid);//여기서 데이터를 먼저 받아오자
	int size = wave.enemyId.size();
	for (int i = 0; i < size; i++) //일단 걍 앞에서 부터 띄우자
	{
		images[i]->ChangeImage(L"../Data/Image/vampire.png"); //나중에는 이름으로 몬스터 이미지 경로를 가져오기 //아 드래그할려면.. 렌더 오더가 컨테이너보다 높아야하지.. 
		images[i]->GetComponent<D2DFont>()->SetDialog(L"X "+ std::to_wstring(wave.enemyCount[i])); //아 여기서 왜터지지? 
	}
	for (int i = size; i < 4; i++) //일단 걍 앞에서 부터 띄우자
	{
		images[i]->SetActive(false);
	}
}
//적들은 이전에 추가되어야함.. 그래야 웨이브를 띄울때 알수있으니까.. 웨이브를보여줄때 아이디를 정하는걸로하자. 

