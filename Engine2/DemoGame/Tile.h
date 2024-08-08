#pragma once
#include "Container.h"

class Tile : public Container
{
	Tile();
	virtual ~Tile();
	void IconToTower();
	void TowerToIcon();
	//아이콘에서 타워로 변경하고
	//타워에서 아이콘으로 변경할까? //만약 아니라면 어떻게해야할가.. 음.. 그냥 이미지만 바꿔놓지뭐.. 
};

