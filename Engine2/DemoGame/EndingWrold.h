#pragma once
#include "World.h"
class Image;
class EndingWrold : public World
{
private:
public:
	EndingWrold();
	virtual ~EndingWrold();
	virtual void Update(float deltaTime) override;
	void MakeObject() override;
	Image* endCredit;
	float creSpeed = 85;
	float Timer = 0;
	bool onceFade = false;
};

