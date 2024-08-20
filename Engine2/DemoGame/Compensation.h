#pragma once
#include "UI.h"
class Button;
class Compensation :public UI
{
private:
	int compensationId;
	Button* btn;
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
