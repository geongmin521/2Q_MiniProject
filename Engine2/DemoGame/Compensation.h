#pragma once
#include "UI.h"
class Button;
class D2DFont;
class Image;
class Compensation :public UI
{
private:
	int selectedId;
	int compensationId[3];
	Button* btn;
	Button* compensationButton[3];
	std::vector<std::wstring> texts; //내일 csv 테이블을 만들어서 기획에 제공하자
	D2DFont* name[3];
	D2DFont* explain[3];
	Image* img[3];
	std::vector<int> SpecialArtifactID; //존재가 고유해야해서.. 뽑고나면 지우자
public:
	Compensation();
	~Compensation();

	float elapsedTime;
	bool isSelect = false;
	bool showonce = true; //처음 게임 시작할때 한번만 보이기 위함
	float deleteTime = 0.8f; 
	void Update(float deltatime);
	void GetCompensation();
	void ChoseCompensation(bool special); //보상뽑기.. 
	void ButtonSelect(int i);
	virtual void Enable() override;
	virtual void Disable() override;
};
