#include "../D2DEngine/pch.h"
#include "Factory.h"
#include "ShowWave.h"

ShowWave::ShowWave()
{
	float LeftPadding = 800;
	Fac->CreateImage(L"BigBack.png", { WinHalfSizeX ,WinHalfSizeY }, { 2,2 }, &sprites);
	for (int i = 0; i < 4; i++)
	{
		Fac->CreateImage(L"vampire.png", { LeftPadding + i * 130 ,WinHalfSizeY }, { 1,1 }, &sprites);
		//텍스트도 추가하기...
	}
		
	Fac->CreateButton(L"smallBack.png", [this]() { isActive = false; }, { WinHalfSizeX + 400, WinHalfSizeY - 400 }, &exitButton);
	
	for (auto var : sprites)
		var->isActive = false;
	//팝업을 닫을 수 있는 버튼

}

ShowWave::~ShowWave()
{
	//지워질때 지금까지 만든 모든 ui를 지워줘야함.. 
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

void ShowWave::Update(float deltaTime)
{
	//이건 그냥 오브젝트의집합이라 오브젝트들의 오브젝트만 실행해주며될듯
	for (auto var : sprites)
		var->Update(deltaTime);
	exitButton[0]->Update(deltaTime);
}

void ShowWave::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto var : sprites)
		var->Render(pRenderTarget);
	exitButton[0]->Render(pRenderTarget); //사실하나밖에없는데 팩토리에 넣는구조때문에 벡터가되어버림.. 
}