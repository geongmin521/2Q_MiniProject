#pragma once
#include "SingletonBase.h"

#define sceneManager SceneManager::GetInstance().get()

class World;
class SceneManager : public SingletonBase<SceneManager>
{
private:
	World* nextWorld;
	World* curWorld;
public:
	SceneManager();
	~SceneManager();
	void ChangeScene(World* world);
	void Change();
	bool isChange = false;
	World* GetCurWorld() { return curWorld; }
	virtual void reset() override;
};

