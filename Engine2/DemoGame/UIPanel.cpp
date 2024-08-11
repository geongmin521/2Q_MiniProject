#include "pch.h"
#include "UIPanel.h"
#include "EventSystem.h"

UIPanel::UIPanel()
{
	EventSystem::GetInstance().get()->Ui.insert(this);
}
