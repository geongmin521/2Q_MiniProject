#pragma once
#include "SingletonBase.h"
#include "Data.h"


struct VariantVisitor {
    std::vector<TowerData>& operator()( std::vector<TowerData>& towerData) {
        return towerData;
    }

    std::vector<EnemyData>& operator()(std::vector<EnemyData>& enemyData) {
        return enemyData;
    }

    std::vector<WaveData>& operator()(std::vector<WaveData>& waves) {
        return waves;
    }
};

class World;
class GameObject;
class Factory : public SingletonBase<Factory> 
{
	std::vector<TowerData> towerData; 
	std::vector<EnemyData> enemyData;
	std::vector<WaveData> waveData;

public:
	World* curWorld;
	void GetData();
    template<typename T>
	T* CreateGameObject() //�Ű������� ���°�쿡�� ���⼭ ó���ϸ�ɰŰ�.. 
	{
		bool bIsBase = std::is_base_of<GameObject, T>::value;
		assert(bIsBase == true);
		T* newObject = new T();
		InsertWorld(newObject);
		return newObject;
	}//�ƴϸ� Ư��ȭ�� ��ų��? �׷��� �Ű������� �������ϱ� �н�.. 

	void CreateImage(std::wstring filePath); //�Ű����� �ʿ��Ѿֵ������θ����? 
	void CreateEnemy(int id); 
	void CreateTower(int id); 
	void CreateButton(std::wstring filePath); //��ư��.. �������� �Ű������� �Լ��� ��Ÿ��� �����غ���.. 
	
	//�ܼ� ���丮�� ����.. ������ ��üŬ������ ���ؼ� �پ��� ��������� �־߰ڴ�.. 
	//��������� ����ִٸ�.. �Ű������� �ʿ����������? �׷��ٸ� �߻�Ŭ������ ���� ���� ���丮�� �����Ӱ� �������������? 
	void InsertWorld(GameObject* obj);

};

