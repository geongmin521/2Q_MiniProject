#pragma once
#include "SingletonBase.h"
#include "Data.h"

using namespace std;
using namespace MathHelper;

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
class EnemyBase;
class TowerBase;

class Image;
class MoveIcon;
class Button;
class Factory : public SingletonBase<Factory>  
{
	map<int,TowerData> towerData; 
	map<int,EnemyData> enemyData; //�����ϰ� �ڵ��Һ��� �����ϰ� �������ϸ����.. 
public:
	Factory();
	~Factory();
	World* curWorld;
	void GetData(std::wstring DataPath);
    template<typename T>
	T* CreateGameObject() //�� �´� �̰� ���ܳ����� �׷� �������׼� ���λ������ִ°���? 
	{
		bool bIsBase = is_base_of<GameObject, T>::value;
		assert(bIsBase == true);
		T* newObject = new T();
		InsertWorld(newObject);
		return newObject;
	}

	Image* CreateImage(wstring filePath, Vector2F pos = { 0,0 }, Vector2F scale = { 1,1 }, std::vector<GameObject*>* Root = nullptr);
	MoveIcon* CreateMoveIcon(wstring filePath, Vector2F pos = { 0,0 }); //�̰Ŵ� �׷��ʿ�� �����Ű���.. 
	GameObject* CreateGameObjectFromId(int id);
	template<typename T>
	T* CreateEnemy(int id);

	template<typename T>
	T* CreateTower(int id);
	Button* CreateButton(wstring filePath, function<void(void)> func, Vector2F pos = { 0,0 }, std::vector<GameObject*>* Root = nullptr); //��ư��.. �������� �Ű������� �Լ��� ��Ÿ��� �����غ���.. 
	
	void InsertWorld(GameObject* obj);

};

template<typename T>
T* Factory::CreateEnemy(int id) //�ֳ׵��� Ư�� �����Ͱ� �ʿ��ϰ�..
{
	bool bIsBase = is_base_of<EnemyBase, T>::value;
	assert(bIsBase == true);
	T* newObject = new T(enemyData[id]); //�����ڿ� �����͸� �߰��ϴ� ����̸� �ǰ���? �ϰ��ǰ� �����ϸ�.. cpp�� �پ������.. ������ ��ȭ�� ������ ������ۿ� ����.. 
	InsertWorld(newObject);
	return newObject;

}

//���̵� �ִµ�.. ��.. //���̵�� ���ϴ� �ֵ��� �ѹ��� �����ع�����? 
template<typename T> //�̰� ���ø��̶� �𸣴°ǰ�? //�����̶� �ٸ��� �̰͹ۿ����µ�.. 
T* Factory::CreateTower(int id) //�ϴ� �����͸� �ٸ��� ���� ������� �����߾��µ�.. �۵� ������� �ٸ����������Ű��Ƽ�. �� ���̽��� ��ӹ޾Ƽ� �����߰ڳ�.. 
{
	bool bIsBase = is_base_of<TowerBase, T>::value;
	assert(bIsBase == true);
	T* newObject = new T(towerData[id]); //���ڿ� �´� �����͸� �־��ֱ�.. 
	InsertWorld(newObject);
	return newObject;
}