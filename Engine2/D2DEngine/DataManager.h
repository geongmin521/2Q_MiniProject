#pragma once
#include "SingletonBase.h"
#include "Data.h"


class DataManager : public SingletonBase<DataManager> //�� �����͸� �о�ͼ� ��û�Ѿ����� ��� �κ� �������.. 
{
private:
    std::vector<EnemyData> EnemyDataRead(std::wifstream& file);
    std::vector<TowerData> TowerDataRead(std::wifstream& file);
    std::vector<WaveData> WaveDataRead(std::wifstream& file);
public:
    DataManager();
    ~DataManager();
    std::wifstream FileOften(std::wstring fileName);
    // std::variant�� ����Ͽ� ���� Ÿ���� �ϳ��� ��ȯ Ÿ������ ó��
    std::variant<std::vector<EnemyData>, std::vector<TowerData>, std::vector<WaveData>> CSVReader(std::wstring fileName);
    //�ʿ��Ѱ�ü�� �̰� �׳� ȣ���ϱ⸸ �ϸ��
};