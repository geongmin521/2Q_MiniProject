#pragma once
#include<string>

struct EnemyData {
    int id;
    std::string name;
    std::string ShieldType; //��� �׳� Ÿ���ΰŰ���
    int star; //���� //������ ������ �̰͵� �����ϸ�ɵ� �̸��� ���ƾ�������.
    float ATK;
    float attackRange; //���� �ݶ��̴��� ������
    float HP;  //�������� int�� ó���ϰ�;������� ������ ���� ���ҷ���. float�ΰ� ����
    float attackSpeed;
    float speed;
    float detectRange; //������ �ʹ�������..
    //������ �ݶ��̴��� �����������..
    //�浹ü�� �����ǰ� ontriggerstay�϶� �Ÿ����� �ൿ�� �����ϱ�.
    //���������� �Ȱ��� �����Ƽ�� ����? �̰� �� �𸣰ڴ�..
    //�����Ƽ�� ���������� �����Ѵٰ��ϸ�.. ����ü�� Ÿ�ٿ� �������������..
    //�ɷ��� �Ÿ��� �����ͼ� �׾ȿ��ִ� ó���ϱ�? �ᱹ �浹ó���ε�..
    //�ݶ��̴��� �ӽ� �����ϱ�? Ʈ���� �����̷� ����
    //��¥ ���������Ӹ� ����ް� ����°� �����ұ�? 
};

struct TowerData {
    int id;
    std::string name;
    std::string attackType;
    int star; //����
    float ATK;
    float attackRange; //���� �ݶ��̴��� ������
    float HP;  //�������� int�� ó���ϰ�;������� ������ ���� ���ҷ���. float�ΰ� ����
    float attackSpeed;
    //Ư���ɷ¿� ���� ���̵�� ó������
    //�������� Ư���������� �ѱ��.. 
};

struct WaveData {
    int id;
    int level;
    //float ���ݵ� ���������. �Ƹ� ������ ������ ���ͷ� ó���ҵ�?
};