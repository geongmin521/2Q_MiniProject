#pragma once
#include "SingletonBase.h"



class GameManager :public SingletonBase<GameManager>
{
private:

public:
	bool isBattle; //�̰� Ʈ�簡�Ǵ½����� ��ȯ�ϸ�ǳ�? set������? ��� ���� ���ؾ������� �𸣰ڳ�.. 
	int WaveLevel = 1;
	GameManager();
	~GameManager(); //���� �Ŵ���.. 

};

#define gameManager GameManager::GetInstance().get()