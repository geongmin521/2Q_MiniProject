#pragma once
#include "../D2DEngine/World.h"
class BattleWorld : public World
{
private:
public:
	BattleWorld(); 
	~BattleWorld();
	void MakeObject() override;
};

