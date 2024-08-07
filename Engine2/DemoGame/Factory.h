#pragma once
#include "../D2DEngine/SingletonBase.h"
#include "../D2DEngine/Data.h"

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
class Factory : public SingletonBase<Factory> //��ģ�� �����غ��� ���� �̱������� ���ص��ǰڴµ�?
	//�˰��־���ϴ¾ֵ��� �� �����, ������ƮǮ 3���ε�.. �ٵ� �� ������ �ν��Ͻ��� �����ʿ䵵������.. ��.. 
	//�ƴϸ� ������ƮǮ�� �̱����ϰŰ�.. ���丮�� ��������Ŵϱ� �����������? 
{
	vector<TowerData> towerData; 
	vector<EnemyData> enemyData;
	vector<WaveData> waveData;

public:
	World* curWorld;
	void GetData();
    template<typename T>
	T* CreateGameObject() //�Ű������� ���°�쿡�� ���⼭ ó���ϸ�ɰŰ�.. 
	{
		bool bIsBase = is_base_of<GameObject, T>::value;
		assert(bIsBase == true);
		T* newObject = new T();
		InsertWorld(newObject);
		return newObject;
	}//�ƴϸ� Ư��ȭ�� ��ų��? �׷��� �Ű������� �������ϱ� �н�.. 

	//��Ʈ�̸�.. ���忡 �����ְ� �ƴѰ�쿡�� �θ�UI�� ���� �ִٴ°Ŵϱ� �ű⿡ �־��ֱ�..
	//�� �ٵ� �̷��� ����ϸ� ���ϱ��ѵ�.. �̰͵� �߸������ ������ �ʹ� �����Ű���.. 
	//�ý��������� ���α׷����� �Ǽ��� �����Ҽ��־���ϴµ�.. 

	//����Ʈ �Ű������� �ʹ� �������� ����������.. ������ ���� ä��� ���� ��ġ�ʴ� ������ ä������.. 
	//�̰� ��¿������? ��.. 
	//�Ű������� �ʹ� ������ ����ϰ� ó���ϴ¹������? �������ڷδ� ó�������Ѱ�? 
	GameObject* CreateImage(wstring filePath, Vector2F pos = { 0,0 }, Vector2F scale = { 1,1 }, std::vector<GameObject*>* Root = nullptr);
	GameObject* CreateMoveIcon(wstring filePath, Vector2F pos = { 0,0 }); //�̰Ŵ� �׷��ʿ�� �����Ű���.. 
	GameObject* CreateEnemy(int id); 
	GameObject* CreateTower(int id); 
	GameObject* CreateButton(wstring filePath, function<void(void)> func, Vector2F pos = { 0,0 }, std::vector<GameObject*>* Root = nullptr); //��ư��.. �������� �Ű������� �Լ��� ��Ÿ��� �����غ���.. 
	
	//�ܼ� ���丮�� ����.. ������ ��üŬ������ ���ؼ� �پ��� ��������� �־߰ڴ�.. 
	//��������� ����ִٸ�.. �Ű������� �ʿ����������? �׷��ٸ� �߻�Ŭ������ ���� ���� ���丮�� �����Ӱ� �������������? 
	void InsertWorld(GameObject* obj);

};

