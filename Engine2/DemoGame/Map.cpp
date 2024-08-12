#include "pch.h"			
#include "Bitmap.h"
#include "Transform.h"
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
		for (int j = 0; j < 4; j++)
		{
			grid[i][j] = Factory().createObj<Container>().
				setPosition({ LeftPadding + i * gridSize , TopPadding + j * gridSize }).
				Get<Container>();
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

	ID2D1BitmapBrush* bitmapBrush = nullptr;
	pRenderTarget->CreateBitmapBrush(GetComponent<Bitmap>()->bitmap, &bitmapBrush);

	// Set the opacity of the brush
	bitmapBrush->SetOpacity(0.5f); // 50% opacity

	// Now use the brush to draw
	pRenderTarget->FillRectangle(D2D1::RectF(0, 0, 100, 100), bitmapBrush);
}


