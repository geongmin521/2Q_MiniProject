#include "../D2DEngine//pch.h"
#include "../D2DEngine/InputSystem.h"
#include "../D2DEngine/D2DRenderer.h"
#include "../D2DEngine/AABB.h"
#include "../D2DEngine/Transform.h"
#include "MapEditer.h"

MapEditer::MapEditer()
{
	renderOrder = 10;
	SetBoundBox(0, 0, 1000, 1000);
}

MapEditer::~MapEditer()
{

}

void MapEditer::Update(float deltaTime)
{

	if (inputSystem->isKeyDown(VK_TAB)) //현재 마우스 좌표에 속한 모든 렉트 삭제하기
	{
		isActive = !isActive;
	}
	if (isActive == false)
		return;
    D2D1_VECTOR_2F curPos = { inputSystem->GetMouseState()._x,inputSystem->GetMouseState()._y };
	if (inputSystem->GetMouseButtonDown(0)) //눌릴때 좌표기억하고
	{
		startPoint = curPos; //카메라 움직이는걸뺄까? 
		return;
	}
	if (inputSystem->GetMouseButton(0)) //누르고있으 현재 좌표로 박스 계산
	{
		EndPoint = curPos;
	}
	if (inputSystem->GetMouseButtonUp(0)) //현재 만들어진 좌표를 토대로 박스를 만들고 벡터안에넣기
	{
		AABB* aabb = new AABB(); 
		//근데 생각해보니 이 모든건 스크린 좌표계일텐데.. 화면을 움직이면서 할려면 월드좌표를 더해줘야겠네.. 
		aabb->m_Extent = { abs(startPoint.x - EndPoint.x) / 2, abs(startPoint.y - EndPoint.y) / 2 };
		if (aabb->m_Extent.x < 10 || aabb->m_Extent.y < 10) //너무 작은거는 못그리게하자
			return;
		aabb->m_Center = { startPoint.x + aabb->m_Extent.x, startPoint.y + aabb->m_Extent.y };//여기에 월드좌표더하기
		mapCollider.push_back(aabb); //센터랑 익스텐드 넣어주면되는데
	}

	if (inputSystem->GetMouseButtonDown(2)) //현재 마우스 좌표에 속한 모든 렉트 삭제하기
	{
		mapCollider.erase(std::remove_if(mapCollider.begin(),mapCollider.end(), 
			[curPos](const AABB* aabb) { return aabb->CheckPoint(curPos); }),mapCollider.end());
	}

	if (inputSystem->isKeyDown('S'))
	{
		SaveCollider();
		return;
	}
	if (inputSystem->isKeyDown('L'))
	{
		LoadCollider();
		return;
	}
}

void MapEditer::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
	pRenderTarget->SetTransform(m_Transform->m_WorldTransform); 
	D2DRenderer::GetInstance()->DrawBox(
		startPoint.x,
		startPoint.y,
		EndPoint.x,
		EndPoint.y);
	for (int i = 0; i < mapCollider.size(); i++)
	{
		D2DRenderer::GetInstance()->DrawBox(
			mapCollider[i]->GetMinX(),
			mapCollider[i]->GetMaxY(),
			mapCollider[i]->GetMaxX(),
			mapCollider[i]->GetMinY());
	}
	pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
	if(isActive)
		D2DRenderer::GetInstance()->DrawTextFunc(L" 그리기 모드",0,0);
}

bool MapEditer::SaveCollider()
{
	std::wofstream file(L"..\\Data\\MapCollider.csv"); 
	if (!file.is_open()) {
		std::cout << "파일을 열 수 없습니다." << std::endl;
		return false; // Return false if file cannot be opened
	}

	int colliderCount = mapCollider.size();

	// Write the collider count as the first line
	file << colliderCount << std::endl;

	// Write each collider's data to subsequent lines
	for (int j = 0; j < colliderCount; j++)
	{
		const AABB* col = mapCollider[j];

		// Write comma-separated values
		file << col->m_Center.x << L',' << col->m_Center.y << L','
			<< col->m_Extent.x << L',' << col->m_Extent.y << std::endl;
	}

	file.close(); // Close the file

	return true;
}

bool MapEditer::LoadCollider() //이거 반복되는 기분인데 외부 파일 읽어오는 과정을 하나로 통일할수있는 시스템을 개발하자
{
	std::wifstream file(L"..\\Data\\MapCollider.csv"); //읽기
	if (!file.is_open()) {
		std::cout << "파일을 열 수 없습니다." << std::endl;
		return false;
	}
	std::wstring line;			// 한줄의 문자열	
	mapCollider.clear();// 불러올때는 기존의 콜라이더를 지우기
	int colliderCount = 0;			// 콜라이더의 개수
	{
		std::getline(file, line);		// 첫번째 줄 읽기
		std::wstringstream wss(line);
		wss >> colliderCount;
	}

	for (int j = 0; j < colliderCount; j++)
	{
		AABB* col = new AABB();

		getline(file, line);			// 한줄 읽기
		std::wstringstream wss(line);   // 한줄을 읽어서 wstringstream에 저장
		std::wstring token;
		{
			getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리
			col->m_Center.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			col->m_Center.y = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			col->m_Extent.x = (float)_wtoi(token.c_str());
			getline(wss, token, L',');
			col->m_Extent.y = (float)_wtoi(token.c_str());
		}
		mapCollider.push_back(col); //오 뭔가 잘되는거같은데?
	}
	return true;
}
