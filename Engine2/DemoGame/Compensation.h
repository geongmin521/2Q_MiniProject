#pragma once
#include "UI.h"
class Button;
class D2DFont;
class Compensation :public UI
{
private:
	int selectedId;
	int compensationId[3];
	Button* btn;
	std::vector<std::wstring> texts; //���� csv ���̺��� ���� ��ȹ�� ��������
	D2DFont* name[3];
	D2DFont* explain[3];
public:
	Compensation();
	~Compensation();

	float elapsedTime;
	bool isSelect = false;
	float deleteTime = 0.8f; 
	void Update(float deltatime);
	void GetCompensation();
	virtual void Enable() override;
};
