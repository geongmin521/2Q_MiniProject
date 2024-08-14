#pragma once
#include "World.h"
class TitleWorld : public World 
{
private:
public:
	TitleWorld(); 
	virtual ~TitleWorld();
	void MakeObject() override;
};

