#include "pch.h"			
#include "Bitmap.h"
#include "Transform.h"
#include "Map.h"	
#include "Container.h"
#include "Factory.h"


Map::Map()
{
	renderOrder = -100;
	AddComponent(new Bitmap(L"..\\Data\\Image\\afternoon.png")); //비트맵을 두개들긴힘들거같고 밤배경으로 하나 더 들고있게하자.. 
	//그리고 밤으로의 전환애니메이션이끝나면 전투할수있도록하기.. 

	transform->SetRelativeLocation({ WinHalfSizeX, WinHalfSizeY });
	int LeftPadding = 400;
	int TopPadding = 300;	
	float gridSize = 150;
	for (int i = 0; i < 4; i++)	
		for (int j = 0; j < 4; j++)
		{
			int zigzag = j % 2 == 0 ? gridSize / 2 : 0;
			grid[i][j] = Factory().createObj<Container>().
				setPosition({ LeftPadding + i * (gridSize +10) + zigzag, TopPadding + j * (gridSize+30) }).
				Get<Container>();
		}			
}

Map::~Map()
{
}

void Map::Update(float deltaTime)
{
	__super::Update(deltaTime);
}

void Map::Render(ID2D1HwndRenderTarget* pRenderTarget,float Alpha)
{
	__super::Render(pRenderTarget);
}


