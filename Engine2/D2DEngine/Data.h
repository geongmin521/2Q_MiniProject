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
    float detectRange; //감지 거리
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
    float attackArea;  //적과 닿은시점(거리) 한번더 거리계산
    float knockBack;
    std::string ability;
};

struct WaveData {
    int id;
    int level;
    float levelPower;
    std::vector<int> enemyId;
    std::vector<float> spawnTime;
    std::vector<int> enemyCount;
};

struct ArtifactData
{
    int id;
    std::string type;
    std::string name;
    std::string target; //효과가 적용되는 대상
    std::string part; //효과가 적용되는 부위
    float power;
    std::string nameText;
    std::string explainText;
};