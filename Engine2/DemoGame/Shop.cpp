#include "../D2DEngine/pch.h"
#include "Factory.h"
#include "Shop.h"

Shop::Shop() //와.. 잠깐만.. 가독성 개에반데.. 근데 일관성도 없어서 통일하기도 힘듬.. 이런것 어떻게처리해야하나...
//매개변수에 담기는 에바임.. 아닌가? bool 타입 대신에 .. 담을수있는 벡터를 넘길까?  그게 차라리 나을거같은데.. 
{
	Fac->CreateImage(L"BigBack.png", WinHalfSizeXY, {2,2}, &subUi);
	float LeftPadding = 700; //왼쪽에 얼마만큼의 공백을 줄지
	for (int i = 0; i < 5; i++)//아이콘
		Fac->CreateImage(L"arrow.png", { LeftPadding + i * 130 ,WinHalfSizeY }, {1,1}, &subUi);
	for (int i = 0; i < 5; i++)//리롤 잠그기
		Fac->CreateButton(L"ImageBack.png", [i, this]() { isLock[i] = !isLock[i]; }, { LeftPadding + i * 130, WinHalfSizeY + 100 },&subUi);
	//멤버변수를 람다식에서 쓸때도 this를 캡쳐해놔야하는구나.. 

	Fac->CreateButton(L"ImageBack.png", std::bind(&Shop::Reroll, this), { LeftPadding + 250, WinHalfSizeY + 100 }, &subUi);
	//조합표를 보고 보상이 뭔지 출력하는 텍스트박스.. 
	Fac->CreateImage(L"ImageBack.png", { LeftPadding + 250, WinHalfSizeY + 200 }, { 1,1 }, &subUi);
	//리롤가능한 횟수를 출력하는 텍스트박스
	Fac->CreateImage(L"ImageBack.png", { LeftPadding + 250, WinHalfSizeY + 300 }, { 1,1 }, &subUi);
	//조합표 확인 버튼 //월드를 통해서 오브젝트를 가져올수있을듯.. 그럼 조합표 객체 가능.. 그냥 한장의 이미지가 훨씬 편할거같은데.. 
	//조합표가 그냥 평균이미지가 맞을까? 
	Fac->CreateButton(L"ImageBack.png", std::bind(&Shop::Reroll, this), { LeftPadding + 450, WinHalfSizeY + 300 }, &subUi);
	//소환하기 버튼
	Fac->CreateButton(L"ImageBack.png", std::bind(&Shop::Spawn, this), { LeftPadding + 450, WinHalfSizeY + 400 }, &subUi);
	//아 멤버변수를 또 function에 담는거는 조금 다르구나.. 
}//그건안되고.. 
//부모오브젝트에 대한 처리를 깔끔하게 할려면 어떻게 해야할까.. 

Shop::~Shop() //인규형이 만들어준 텍스트클래스를 기준으로 텍스트 박스도 빠르게 만들어야지.. 특정값을 출력할수있게 템플릿으로 만들수있을려나? 
{
}

void Shop::Reroll()
{
}
//이러면 드롭 able 이벤트가 발생할수도 있어야하고 .. 맵도 만들어야하고 미쳤네 그냥.. 하.. 
void Shop::Spawn() //샵이 인벤토리도 들고있어야하고.. 컨테이너 클래스도 설계해야하고.. 
{
}

void Shop::Update(float deltaTime)
{
	//이건 그냥 오브젝트의집합이라 오브젝트들의 오브젝트만 실행해주며될듯
	for (auto var : subUi)
		var->Update(deltaTime);
}

void Shop::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	for (auto var : subUi)
		var->Render(pRenderTarget);
}

//오케이 계층구조는 단한단계만 두면될거같고.. 월드에 오브젝트를 직접 넣는게 아니라
//여기서 처리하는걸로가자.. 

//틀만 세부 사항 