#include "pch.h"
#include "Component.h"

Component::Component()
{

}

Component::~Component()
{

}

void Component::SetActive(bool active)
{
	if (isActive == active)
		return;
	isActive = active;

	if (active)
		Enable();
	else
		Disable();
}

void Component::Update(float deltaTime)
{

}

void Component::Render(ID2D1RenderTarget* pRenderTarget,float Alpha)
{

}

void Component::Enable()
{
}

void Component::Disable()
{
}
