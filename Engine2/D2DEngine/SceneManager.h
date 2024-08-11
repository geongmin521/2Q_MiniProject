#pragma once
#include "SingletonBase.h"
class World;
class SceneManager : public SingletonBase<SceneManager>
{
private:
	World* curWorld;
public:
	SceneManager();
	~SceneManager();
	void ChangeScene(World* world);
	World* GetCurWorld() { return curWorld; }
};

