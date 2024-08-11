#pragma once
#include "GameObject.h"
class UIPanel : public GameObject
{
protected:
	std::vector<GameObject*> subUi; 
public:
	UIPanel();
	~UIPanel() = default;

	void SetActive(bool isActive) {
		for (auto var : subUi)
			var->isActive = isActive;
		this->isActive = isActive;
	}

};

