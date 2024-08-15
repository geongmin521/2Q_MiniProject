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
	void GetCompensation();
	virtual void Enable() override;
};
