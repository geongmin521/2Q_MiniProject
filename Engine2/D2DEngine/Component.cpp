#include "pch.h"
#include "Component.h"

Component::Component()
{

}

Component::~Component()
{

}

void Component::setActive(bool active)
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

void Component::Render(ID2D1RenderTarget* pRenderTarget)
{

}

void Component::Enable()
{
}

void Component::Disable()
{
}
