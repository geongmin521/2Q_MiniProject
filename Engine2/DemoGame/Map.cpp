#include "../D2DEngine/pch.h"			
#include "../D2DEngine/Bitmap.h"
#include "../D2DEngine/Transform.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/BoxCollider.h"

#include "Map.h"	

Map::Map()
{
	renderOrder = -100;
	AddComponent(new Bitmap(L"..\\Data\\map.png"));
	//D2D1_SIZE_F size = GetComponent<Bitmap>()->Bitmap->GetSize();
	//SetBoundBox(0, 0, size.width, size.height);
	transform->relativeScale = { 3,2.4 };
	transform->relativeLocation = { WinHalfSizeX, WinHalfSizeY };
	LoadCollider();
}

Map::~Map()
{
}

bool Map::LoadCollider() //읽기부분이 좀 겹치는거같은데 어떻게 클래스로 빼보자
{
	std::wifstream file(L"..\\Data\\MapCollider.csv"); //읽기
	if (!file.is_open()) {
		std::cout << "파일을 열 수 없습니다." << std::endl;
		return false;
	}
	std::wstring line;			// 한줄의 문자열	
	boxCols.clear();// 불러올때는 기존의 콜라이더를 지우기
	int colliderCount = 0;			// 콜라이더의 개수
	{
		std::getline(file, line);		// 첫번째 줄 읽기
		std::wstringstream wss(line);
		wss >> colliderCount;
	}
	//animations[index].Frames.reserve(FrameCount);
	for (int j = 0; j < colliderCount; j++)
	{
		AABB* col = new AABB();

		getline(file, line);			// 한줄 읽기
		std::wstringstream wss(line);   // 한줄을 읽어서 wstringstream에 저장
		std::wstring token;
		{
			getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리
			col->Center.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			col->Center.y = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			col->Extent.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			col->Extent.y = (float)_wtoi(token.c_str());
		}
		//boxCols.push_back(new BoxCollider(col, CollisionType::Block,this,CollisionLayer::Platform)); 
	}
	return true;
}


