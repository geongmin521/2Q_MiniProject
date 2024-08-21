#include "pch.h"
#include "ArtifactObject.h"
#include "Artifact.h"
#include "Factory.h"
#include "Dotween.h"
#include "Transform.h"
#include "DataManager.h"
#include "Bitmap.h"

ArtifactObject::ArtifactObject(int id, float targetPosX, float targetPosY)
{
	std::wstring original = L"../Data/Image/Artifact/" + Utility::convertFromString(dataManager->getArtifactData(id).filePath) + L".png";
	AddComponent(new Bitmap(original));
	transform->SetRelativeScale({ 0.8f,0.8f });
	auto& loca = transform->relativeLocation;
	new DOTween(loca.x, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 4.f, 400.0f, targetPosX);
	new DOTween(loca.y, EasingEffect::OutExpo, StepAnimation::StepOnceForward, 4.f, 400.0f, targetPosY);

}

ArtifactObject::~ArtifactObject()
{
}

