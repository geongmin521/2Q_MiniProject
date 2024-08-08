#pragma once
#include<string>
#include<vector>

struct EnemyData {
    int id;
    std::string name;
    int level;
    std::string Type;
    float ATK;
    float attackRange; //공격 사거리
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
    float attackRange; //공격 사거리
    float HP;  
    float attackSpeed;
    float attackArea; //공격할때 박스가 추가되는형식.. 
    std::string ability;
};

struct WaveData {
    int id;
    int level;
    float levelPower;
    std::vector<int> enemyId;
    std::vector<int> spawnTime;
    std::vector<int> enemyCount;
    //float 간격도 물어봐야함. 아마 가능한 종류의 벡터로 처리할듯?
};