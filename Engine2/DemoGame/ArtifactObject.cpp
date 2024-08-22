#include "pch.h"
#include "ArtifactObject.h"
#include "Artifact.h"
#include "Factory.h"
#include "Dotween.h"
#include "Transform.h"
#include "DataManager.h"
#include "Bitmap.h"
#include "GameManager.h"
#include "EventSystem.h"

ArtifactObject::ArtifactObject(int id, float targetPosX, float targetPosY)
{
	data = &dataManager->getArtifactData(id);
	std::wstring original = L"../Data/Image/Artifact/" + Utility::convertFromString(data->filePath) + L".png";
	AddComponent(new Bitmap(original));
	transform->SetRelativeScale({ 0.8f,0.8f });
	auto& loca = transform->relativeLocation;
	new DOTween(loca.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 4.f, 400.0f, targetPosX);
	new DOTween(loca.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 4.f, 400.0f, targetPosY);
	SetBoundBox(0, 0, 50, 50);
	eventSystem->Ui.insert(this);
}

ArtifactObject::~ArtifactObject()
{
}

void ArtifactObject::OnMouse()
{
	if (data->type == "Normal")
		return;
	MathHelper::Vector2F pos = transform->GetWorldLocation();
	GameObject* tooltip = gameManager->getObject("ToolTip");
	tooltip->SetActive(true);
	tooltip->renderOrder = renderOrder + 1;
	tooltip->transform->SetRelativeLocation({ pos.x + 100,pos.y +100});
	std::wstring path = L"../Data/Image/UI/tooltip/" + Utility::convertFromString(data->filePath) + L"_tooltip.png";
	tooltip->GetComponent<Bitmap>()->LoadD2DBitmap(path);
}

void ArtifactObject::OutMouse()
{
	gameManager->getObject("ToolTip")->SetActive(false);
}
