#include "../D2DEngine/pch.h"			
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Transform.h"
#include "Map.h"	
#include "Container.h"
#include "Factory.h"


Map::Map()
{
	renderOrder = -100;
	//AddComponent(new Bitmap(L"..\\Data\\map.png"));
	//transform->SetRelativeScale({ 3,2.4 });
	//Fac->CreateGameObject();
	transform->SetRelativeLocation({ WinHalfSizeX, WinHalfSizeY });

	//�굵 ���丮�� ���������? 
}

Map::~Map()
{
}


