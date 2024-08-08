#include "../D2DEngine/pch.h"			
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Transform.h"
#include "Map.h"	
#include "Container.h"
#include "Factory.h"


Map::Map()
{
	renderOrder = -100;
	AddComponent(new Bitmap(L"..\\Data\\Image\\afternoon.png"));

	transform->SetRelativeLocation({ WinHalfSizeX, WinHalfSizeY });
	int LeftPadding = 400;
	int TopPadding = 300;
	float gridSize = 150;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			grid[i][j] = Fac->CreateGameObject<Container>();
			grid[i][j]->transform->SetRelativeLocation({ LeftPadding + i * gridSize , TopPadding + j * gridSize });
		}
	}
}

Map::~Map()
{
}

void Map::Update(float deltaTime)
{
	__super::Update(deltaTime);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			grid[i][j]->Update(deltaTime);
		}
	}
}

void Map::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	__super::Render(pRenderTarget);
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			grid[i][j]->Render(pRenderTarget);
		}
	}
}


