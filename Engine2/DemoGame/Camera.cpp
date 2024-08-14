#include "pch.h"
#include "Camera.h"
#include "CameraScene.h"
#include "Transform.h"

Camera::Camera() 
{
	CameraScene* scene = new CameraScene(); 
	AddComponent(scene);
	transform->SetRelativeLocation({ WinHalfSizeX, WinHalfSizeY });
}

Camera::~Camera()
{
}
