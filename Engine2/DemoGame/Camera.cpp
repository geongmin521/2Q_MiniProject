#include "../D2DEngine/pch.h"
#include "Camera.h"
#include "..//D2DEngine/CameraScene.h"
#include "..//D2DEngine/Transform.h"

Camera::Camera() //카메라를 생성할려면 타겟을 정해야한다? 
{
	CameraScene* scene = new CameraScene(); //타겟을 정해주는걸로 정의할까?
	AddComponent(scene);
	transform->relativeLocation = { WinHalfSizeX, WinHalfSizeY };
}

Camera::~Camera()
{
}
