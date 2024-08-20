#include "pch.h"			
#include "Bitmap.h"
#include "Transform.h"
#include "Map.h"	
#include "Container.h"
#include "Factory.h"
#include "Pools.h"
#include "CircleCollider.h"
#include "Circle.h"
#include "GameManager.h"
#include "Sculpture.h"

#include "D2DEffectManager.h"
#include "CrossFadeEffect.h"
#include "D2DRenderer.h"

Map::Map()
{
	transform->SetRelativeScale({ 0.75f,0.75f });
	renderOrder = -100; 
	AddComponent(new Bitmap(L"..\\Data\\Image\\afternoon.png"));  //이게 진짜 맵배경
	afternoonBitmap = GetComponent<Bitmap>(); // 맵 변경을 위해 추가함
	AddComponent(new Bitmap(L"..\\Data\\Image\\night.png")); // 맵 변경을 위해 추가함
	nightBitmap = dynamic_cast<Bitmap*>(ownedComponents[2]); // 맵 변경을 위해 추가함
	D2DEffectManager::GetInstance()->CreateCrossFadeEffect(L"MapFade", afternoonBitmap->bitmap, nightBitmap->bitmap);

	transform->SetRelativeLocation({ WinHalfSizeX, WinHalfSizeY });
	int LPad = 400;
	int TopPadding = 300;	
	float gridSize = 150;
	for (int i = 0; i < 4; i++)	
		for (int j = 0; j < 4; j++)
		{
			int zigzag = j % 2 == 0 ? gridSize / 2 : 0;
			grid[i][j] = Make(Container)(i*4 + j).
				setPosition({ LPad + i * (gridSize +10) + zigzag, TopPadding + j * (gridSize+30) }).
				Get<Container>();
		}			
	for(int i=0;i< 4;i++)
		grid[i][1]->OnDrop(Pools::GetInstance().get()->PopPool(i*3));
	grid[0][1]->OnDrop(Pools::GetInstance().get()->PopPool(12));

	Make(Sculpture)().setPosition({ 100 , WinHalfSizeY });
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
//	__super::Render(pRenderTarget);

	D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffectManager::GetInstance()->FindEffect(L"MapFade"));
}


