#include "pch.h"
#include "EndingWrold.h"
#include "Factory.h"
#include "Image.h"
#include "Transform.h"
#include "SceneManager.h"
#include "TitleWorld.h" 
#include "FadeOut.h"
#include "Music.h"
EndingWrold::EndingWrold()
{
	Music::soundManager->PlayMusic(Music::eSoundList::Ending, Music::eSoundChannel::BGM);
}

EndingWrold::~EndingWrold()
{
}

void EndingWrold::Update(float deltaTime)
{
	__super::Update(deltaTime);
	Timer += deltaTime;
	if (Timer > 2 && onceFade == false)
	{
		onceFade = true;
		Make(FadeOut)([this]() {
			Make(Image)(L"endingCredit.png").setPosition(WinHalfSizeXY).setRenderOrder(1800).Get<Image>(endCredit); }, true);
	}
	if(!endCredit)
		return;
	endCredit->transform->AddRelativeLocation(0, -creSpeed * deltaTime);
	if(endCredit->transform->GetWorldLocation().y <= -530 )
		SceneManager::GetInstance().get()->ChangeScene(new TitleWorld);
}

void EndingWrold::MakeObject()
{
	Make(Image)(L"Ending_Cut.png").setPosition(WinHalfSizeXY);
	Make(FadeOut)([this]() {
		Make(Image)(L"endingCredit.png").setPosition(WinHalfSizeXY).setRenderOrder(1800).Get<Image>(endCredit); }, true);


}