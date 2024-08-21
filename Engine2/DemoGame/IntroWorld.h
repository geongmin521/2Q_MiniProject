#pragma once
#include "World.h"
class Image;
class IntroWorld : public World
{
private:
public:
	IntroWorld();
	virtual ~IntroWorld();
	Image* image;
	
	int introNum = 0;

	float elapsedTime = 0;
	virtual void Update(float deltaTime) override;
	void MakeObject() override;
};

