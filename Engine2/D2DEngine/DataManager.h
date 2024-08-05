#pragma once
#include "SingletonBase.h"
#include "Data.h"


class DataManager : public SingletonBase<DataManager> //�� �����͸� �о�ͼ� ��û�Ѿ����� ��� �κ� �������.. 
{
private:
    std::vector<EnemyData> EnemyDataRead();
    std::vector<TowerData> TowerDataRead();
    std::vector<WaveData> WaveDataRead();
public:
    DataManager();
    ~DataManager();

    // std::variant�� ����Ͽ� ���� Ÿ���� �ϳ��� ��ȯ Ÿ������ ó��
    std::variant<std::vector<EnemyData>, std::vector<TowerData>, std::vector<WaveData>> CSVReader(const std::type_info& typeInfo);
    //�ʿ��Ѱ�ü�� �̰� �׳� ȣ���ϱ⸸ �ϸ��
};