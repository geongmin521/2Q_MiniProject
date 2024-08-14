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

void CameraScene::Update(float deltaTime) 
{
	D2D1_MATRIX_3X2_F invserse = owner->transform->worldTransform;  
	D2D1InvertMatrix(&invserse); 
	D2DRenderer::cameraTransform = invserse;//* D2D1::Matrix3x2F::Translation(WinHalfSizeX, WinHalfSizeY); //È­¸éÁß¾ÓÀ¸·Î ¸ÂÃã
	viewBoundBox->SetCenter(owner->transform->worldTransform.dx, owner->transform->worldTransform.dy);
	owner->owner->SetCullingBound(viewBoundBox);
}




