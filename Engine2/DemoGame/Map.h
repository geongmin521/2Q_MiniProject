#pragma once
#include "../D2DEngine/GameObject.h"
#include "../D2DEngine/IColliderNotify.h"

class Collider;
class Map : public GameObject
{
public:
	Map();
	~Map(); //¿œ¥‹¿∫ 
	bool LoadCollider();
	std::vector<Collider*> boxCols;
};

