#pragma once
#include<string>
#include<vector>

struct EnemyData {
    int id;
    std::string name;
    int level;
    std::string Type;
    float ATK;
    float attackRange; //���� ��Ÿ�
    float HP; 
    float attackSpeed;
    float speed;
    std::string ability; 
};

struct TowerData {
    int id;
    std::string name;
    int level;
    std::string Type;   
    float ATK;
    float attackRange; //���� ��Ÿ�
    float HP;  
    float attackSpeed;
    float attackArea; //�����Ҷ� �ڽ��� �߰��Ǵ�����.. 
    std::string ability;
};

struct WaveData {
    int id;
    int level;
    float levelPower;
    std::vector<int> enemyId;
    std::vector<int> spawnTime;
    std::vector<int> enemyCount;
    //float ���ݵ� ���������. �Ƹ� ������ ������ ���ͷ� ó���ҵ�?
};