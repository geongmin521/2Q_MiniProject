#pragma once
#include<string>

struct EnemyData {
    int id;
    std::string name;
    std::string ShieldType; //사실 그냥 타입인거같고
    int star; //성급 //적들의 레벨도 이것도 구분하면될듯 이름이 같아야편하지.
    float ATK;
    float attackRange; //원형 콜라이더의 반지름
    float HP;  //데미지를 int로 처리하고싶어하지만 어차피 상성을 곱할려면. float인게 편함
    float attackSpeed;
    float speed;
    float detectRange; //렌지가 너무많은데..
    //각각의 콜라이더를 만들수없으니..
    //충돌체에 감지되고 ontriggerstay일때 거리별로 행동을 결정하기.
    //범위공격은 똑같이 어빌리티로 빼기? 이건 잘 모르겠다..
    //어빌리티로 광역공격을 구현한다고하면.. 투사체가 타겟에 가까워진다음에..
    //능력의 거리를 가져와서 그안에있는 처리하기? 결국 충돌처리인데..
    //콜라이더를 임시 생성하기? 트리거 스테이로 만들어서
    //진짜 딱한프레임만 적용받고 지우는게 가능할까? 
};

struct TowerData {
    int id;
    std::string name;
    std::string attackType;
    int star; //성급
    float ATK;
    float attackRange; //원형 콜라이더의 반지름
    float HP;  //데미지를 int로 처리하고싶어하지만 어차피 상성을 곱할려면. float인게 편함
    float attackSpeed;
    //특수능력에 대한 아이디로 처리하자
    //방사공격은 특수공격으로 넘기기.. 
};

struct WaveData {
    int id;
    int level;
    //float 간격도 물어봐야함. 아마 가능한 종류의 벡터로 처리할듯?
};