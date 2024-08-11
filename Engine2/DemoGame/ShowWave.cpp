#include "pch.h"
#include "Factory.h"
#include "ShowWave.h"
#include "Image.h"
#include "Button.h"

ShowWave::ShowWave()
{
	float LeftPadding = 800;
	Factory().createObj<Image>(L"BigBack.png").setPosition({WinHalfSizeX ,WinHalfSizeY}).setScale({2,2}).setIsActive(false).setRoot(&sprites);
	for (int i = 0; i < 4; i++)
	{
		Factory().createObj<Image>(L"vampire.png").setPosition({LeftPadding + i * 130 ,WinHalfSizeY}).setIsActive(false).setRoot(&sprites);
		//텍스트도 추가하기... //이것도 팩토리에 추가가능이긴한데.. 대신UI로 형변환이되어야함.. 아닌가? 다른애들도 필요한가? 
	}
		
	Factory().createObj<Button>(L"smallBack.png", [this]() { isActive = false; }).setPosition({ WinHalfSizeX + 400, WinHalfSizeY - 400 }).setIsActive(false).setRoot(&exitButton);
}

ShowWave::~ShowWave()
{
	//지워질때 지금까지 만든 모든 ui를 지워줘야함.. 사실 아무리 모임이라도.. 얘네가 따로 들고있는게 맘에 안들긴하거든? 어디 다른벡터에 담아주는거까진 인정인데... 결국 월드의 통제를 받아야함.. 
	//그리고 어차피 배열에 담았으니.. 키고 끄는것도 따로 통제할수있을거아니야.. 음.. 월드한테 맡기는게 나음. 
}

void ShowWave::Show()
{
	isActive = true;
	sprites[0]->isActive = true;//첫번째는 배경이라 무조건켜지도록
	for (auto var : sprites) //이것도 다음인덱스부터 접근할거면 그냥 for문으로 처리해도되고
		var->isActive = true;
	//

	//이거는 데이터 구조랑 csv까지 생각해야하니까 좀이따 만들자.. 
	//데이터 매니저한테 불러오고 웨이브불러오기... 
}

void ShowWave::Update(float deltaTime) //이렇게 되면 이친구들도 필요하지않음.. 단순히 월드와 그걸 담고있을뿐인거지? 업데이트를 도는 게임오브젝트 객체라기보다는 그냥 담고있는 틀에 불과함.. 
{ //근데 모든애들이 그런건아닐걸? 필요한 능력을 들고있는애들도있는데.. 사실 필요없지않나? 
}

void ShowWave::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}