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
#include "Effect.h"
#include "D2DEffectManager.h"
#include "CrossFadeEffect.h"
#include "D2DRenderer.h"
#include "GaussianBlurEffect.h"

Map::Map()
{
	name = "BattleMap";
	transform->SetRelativeScale({ 0.75f,0.75f });
	renderOrder = -100; 
	AddComponent(new Bitmap(L"..\\Data\\Image\\afternoon.png"));  //이게 진짜 맵배경
	afternoonBitmap = GetComponent<Bitmap>(); // 맵 변경을 위해 추가함
	D2DEffectManager::GetInstance()->CreateGaussianBlurEffect(L"afternoonBlur", afternoonBitmap->bitmap, 5.0f);

	AddComponent(new Bitmap(L"..\\Data\\Image\\night.png")); // 맵 변경을 위해 추가함
	nightBitmap = dynamic_cast<Bitmap*>(ownedComponents[2]); // 맵 변경을 위해 추가함
	D2DEffectManager::GetInstance()->CreateGaussianBlurEffect(L"nightBlur", nightBitmap->bitmap, 5.0f);
	D2DEffectManager::GetInstance()->CreateCrossFadeEffect(L"MapFade", afternoonBitmap->bitmap, nightBitmap->bitmap);

	transform->SetRelativeLocation({ WinHalfSizeX, WinHalfSizeY });
	int LPad = 475;
	int TopPadding = 300;	
	float gridSize = 150;
	for (int i = 0; i < 4; i++)	
		for (int j = 0; j < 4; j++)
		{
			int zigzag = j % 2 == 0 ? gridSize / 2 : 0;
			grid[i][j] = Make(Container)(i * 4 + j + 4).
				setPosition({ LPad + i * (gridSize +10) + zigzag, TopPadding + j * (gridSize+30) }).
				Get<Container>();
		}			
	int order[4] = { 0,1,3,2 };
	for(int i=0;i< 4;i++)
		grid[i][1]->OnDrop(Pools::GetInstance().get()->PopPool(order[i]*3));
	grid[1][2]->OnDrop(Pools::GetInstance().get()->PopPool(12));

	Make(Sculpture)().setPosition({ 113 + 117 / 2, 374 + 176 / 2 }).setScale({ 0.75f,0.75f });
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
	if (isBlurEffect == false)
	{
		D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffectManager::GetInstance()->FindEffect(L"MapFade"));
	}
	else
	{
		if (D2DEffectManager::GetInstance()->FindIEffect<CrossFadeEffect>(L"MapFade")->isFadeIn)
		{		
			D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffectManager::GetInstance()->FindEffect(L"afternoonBlur"));
		}
		else
		{
			D2DRenderer::GetInstance()->DeviceContext->DrawImage(D2DEffectManager::GetInstance()->FindEffect(L"nightBlur"));
		}
	}
	
}


