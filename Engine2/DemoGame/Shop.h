#pragma once
#include "../D2DEngine/UI.h"

class Shop: public UI //샵클래스? 사실 그냥 UI오브젝트들의 집합이자 상점에 필요한 함수들의 집합임
{
private:
	bool isLock[5];
	int Id[5]; //현재 상점에 뜬 아이콘 아이디? 
	int reroll; //남은 리롤개수
	std::vector<GameObject*> subUi;
public:

	Shop();
	virtual ~Shop();
	void Reroll();
	void Spawn(); //여기서 조합식 처리하는것도 만들어야하고.. 
	virtual void Update(float deltaTime) override;
	virtual void Render(ID2D1HwndRenderTarget* pRenderTarget) override;
};

