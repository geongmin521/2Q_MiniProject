#include "pch.h"
#include "Factory.h"
#include "ShowWave.h"
#include "Image.h"
#include "Button.h"

ShowWave::ShowWave()
{
	float LeftPadding = 800;
	Factory().createObj<Image>(L"BigBack.png").setPosition({WinHalfSizeX ,WinHalfSizeY}).setScale({2,2}).setActive(false).setRoot(&sprites);
	for (int i = 0; i < 4; i++)
	{
		Factory().createObj<Image>(L"vampire.png").setPosition({LeftPadding + i * 130 ,WinHalfSizeY}).setActive(false).setRoot(&sprites);
		//텍스트도 추가하기... //이것도 팩토리에 추가가능이긴한데.. 대신UI로 형변환이되어야함.. 아닌가? 다른애들도 필요한가? 
	}
		
	Factory().createObj<Button>(L"smallBack.png", [this]() { SetActive(false); }).setPosition({ WinHalfSizeX + 400, WinHalfSizeY - 400 }).setActive(false).setRoot(&exitButton);
}

ShowWave::~ShowWave()
{
	//지워질때 지금까지 만든 모든 ui를 지워줘야함.. 사실 아무리 모임이라도.. 얘네가 따로 들고있는게 맘에 안들긴하거든? 어디 다른벡터에 담아주는거까진 인정인데... 결국 월드의 통제를 받아야함.. 
	//그리고 어차피 배열에 담았으니.. 키고 끄는것도 따로 통제할수있을거아니야.. 음.. 월드한테 맡기는게 나음. 
}

