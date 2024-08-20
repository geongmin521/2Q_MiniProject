#include "pch.h"
#include "Compensation.h"
#include "Factory.h"
#include "Button.h"
#include "Image.h"
#include "Artifact.h"
#include "GameManager.h"
#include "D2DFont.h"

Compensation::Compensation() 
{
	float LPad = 100; 
	//���
	Make(Image)(L"UI/Pop_up/Popup_SpecialReward.png").setPosition({ LPad , 100 }).setParent(this->transform);

	//csv�� Ÿ�� �޾Ƽ� �����.. 
	for (int i = 0; i < 3; i++)
		name[i] = new D2DFont(L""); //�̰� �׳� ���ع�����.. ����� ���� ���ؾ���? 
	for (int i = 0; i < 3; i++)
		explain[i] = new D2DFont(L"");
	for (int i = 0; i < 3; i++)
	{
		Make(Button)(L"Frame", [this,i]() {compensationId = i; btn->SetInteractive(true); }). //�ι�°���̺��϶��� �׳� ���̵� 3�� �����ֱ�
			AddComponent(name[i]).
			AddComponent(explain[i]).
			setPos_Parent({ LPad - 100 * i, 0 }, transform);
	}
	
	//����Ȯ�� ��ư 
	Make(Button)(L"Commit", [this]() {
		bool special = false;
		if (gameManager->curWaveId == 3 || gameManager->curWaveId == 6)
			special = true; 
		GetCompensation(special); 
		}).
		setPos_Parent_Text({ LPad + 500, 300 }, this->transform, L"���� �Ϸ�", 20).Get(btn);
	SetActive(false);

	//���� �� csv�� ���ú��� �׽�Ʈ�ϰ� �Ѱܾ��ҵ�. 
	texts.push_back(L"������ ���ݷ��� �����մϴ�."); //���߿� csv �ѱ� �ؽ�Ʈ �д°� �׽�Ÿ�ϱ� �� ���ڵ��� ����-8 csv�ε�
	texts.push_back(L"������ ���ݷ��� �����մϴ�.");
	texts.push_back(L"������ ���ݷ��� �����մϴ�.");
	texts.push_back(L"���ڰ��� ȸ������ �����մϴ�.");
	texts.push_back(L"���� ĳ������ ü���� �����մϴ�.");
	texts.push_back(L"���� ĳ������ ü���� �����մϴ�.");
	texts.push_back(L"���� ĳ������ ü���� �����մϴ�.");
	texts.push_back(L"���ڰ� ĳ������ ü���� �����մϴ�.");
	texts.push_back(L"���� ĳ������ ���� �ӵ��� �����մϴ�.");
	texts.push_back(L"���� ĳ������ ���� �ӵ��� �����մϴ�.");
	texts.push_back(L"���� ĳ������ ���� �ӵ��� �����մϴ�.");
	texts.push_back(L"���ڰ� ĳ������ ȸ�� �ӵ��� �����մϴ�.");
	texts.push_back(L"���� �ð� ���� ���鿡�� �߰� ���� ���ظ� �����ϴ�.");
	texts.push_back(L"�žӽ��� ȹ�淮�� �����մϴ�.");
	texts.push_back(L"�� ��� ĳ������ ���� ��Ÿ��� �����մϴ�.");
	texts.push_back(L"�� ��� ĳ������ �˹� ��ġ�� �����մϴ�.");
	texts.push_back(L"������ ���� �ӵ��� �����մϴ�.");
	texts.push_back(L"������ �̵� �ӵ��� �پ��ϴ�.");
}

Compensation::~Compensation() //��ư������ ���� ���� ���̵� �����ϰ� �ִٰ� Ȯ���ϸ� ��Ű��Ʈ �Ŵ������� �����ֱ�
{
}

void Compensation::GetCompensation(bool special) //�� �̰͵� �߻�ȭ�ϸ� ��ĥ���ֳ�? �ٵ� ���������̶� ������������ ������ ���̴ٸ����ѵ�.. 
{
	if (compensationId == -1)
		return; //���þȵ�
	artifact->SelectArtifact(compensationId);
	SetActive(false);
}

void Compensation::Enable()
{
	compensationId = -1;
	//Ȱ��ȭ�ɶ� ������ ���󸮽�Ʈ�߿� �̱�.. 
}
