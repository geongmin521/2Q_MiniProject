#include "pch.h"
#include "GameObject.h"
#include "Transform.h"
#include "CameraScene.h" 
#include "D2DRenderer.h"
#include "World.h"
#include "AABB.h"

CameraScene::CameraScene()
{
	moveSpeed = 300;
	viewBoundBox = new AABB();
	viewBoundBox->SetExtent(WinHalfSizeX, WinHalfSizeY);

}

CameraScene::~CameraScene()
{

}

void CameraScene::Update(float deltaTime) //카메라는 타겟의 트랜스폼을 자기거처럼 사용하는거지?
{
	D2D1_MATRIX_3X2_F invserse = owner->transform->worldTransform;  
	D2D1InvertMatrix(&invserse); 
	D2DRenderer::cameraTransform = invserse * D2D1::Matrix3x2F::Translation(WinHalfSizeX, WinHalfSizeY); // 카메라의 좌표가 화면중앙일때가 0,0 으로 계산되기위함
	viewBoundBox->SetCenter(owner->transform->worldTransform.dx, owner->transform->worldTransform.dy);
	owner->owner->SetCullingBound(viewBoundBox);
}
//오브젝트를 추가할때 화면중앙에 그리기 쉽게하기.. 



