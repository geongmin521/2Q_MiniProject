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
	std::vector<std::wstring> texts; //���� csv ���̺��� ���� ��ȹ�� ��������
	D2DFont* name[3];
	D2DFont* explain[3];
	Image* img[3];
	std::vector<int> SpecialArtifactID; //���簡 �����ؾ��ؼ�.. �̰��� ������
public:
	Compensation();
	~Compensation();

	float elapsedTime;
	bool isSelect = false;
	bool showonce = true; //ó�� ���� �����Ҷ� �ѹ��� ���̱� ����
	float deleteTime = 0.8f; 
	void Update(float deltatime);
	void GetCompensation();
	void ChoseCompensation(bool special); //����̱�.. 
	void ButtonSelect(int i);
	virtual void Enable() override;
	virtual void Disable() override;
};
