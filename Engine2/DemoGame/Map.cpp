#include "pch.h"			
#include "Bitmap.h"
#include "Transform.h"
#include "Map.h"	
#include "Container.h"
#include "Factory.h"
#include "Pools.h"



Map::Map()
{
	renderOrder = -100; //�̰� ������ �����׸���? �ƴѵ�.. 
	AddComponent(new Bitmap(L"..\\Data\\Image\\afternoon.png")); //��Ʈ���� �ΰ��������Ű��� �������� �ϳ� �� ����ְ�����.. 
	//�׸��� �������� ��ȯ�ִϸ��̼��̳����� �����Ҽ��ֵ����ϱ�.. 

	transform->SetRelativeLocation({ WinHalfSizeX, WinHalfSizeY });
	int LeftPadding = 400;
	int TopPadding = 300;	
	float gridSize = 150;
	for (int i = 0; i < 4; i++)	
		for (int j = 0; j < 4; j++)
		{
			int zigzag = j % 2 == 0 ? gridSize / 2 : 0;
			grid[i][j] = Factory().createObj<Container>(i*4 + j).
				setPosition({ LeftPadding + i * (gridSize +10) + zigzag, TopPadding + j * (gridSize+30) }).
				Get<Container>();
		}			
	for(int i=0;i< 4;i++)
		grid[i][1]->OnDrop(Pools::GetInstance().get()->PopPool(i*3));
	//�ϴ� ���� �����̳ʸ� ��������� ����ٰ� ����Ÿ���� ��ġ������.. 
	
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


