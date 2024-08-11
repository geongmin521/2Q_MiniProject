#include "pch.h"
#include "Factory.h"
#include "ShowWave.h"
#include "Image.h"
#include "Button.h"

ShowWave::ShowWave()
{
	float LeftPadding = 800;
	Factory().createObj<Image>(L"BigBack.png").setPosition({WinHalfSizeX ,WinHalfSizeY}).setScale({2,2}).setIsActive(false).setRoot(&sprites);
	for (int i = 0; i < 4; i++)
	{
		Factory().createObj<Image>(L"vampire.png").setPosition({LeftPadding + i * 130 ,WinHalfSizeY}).setIsActive(false).setRoot(&sprites);
		//�ؽ�Ʈ�� �߰��ϱ�... //�̰͵� ���丮�� �߰������̱��ѵ�.. ���UI�� ����ȯ�̵Ǿ����.. �ƴѰ�? �ٸ��ֵ鵵 �ʿ��Ѱ�? 
	}
		
	Factory().createObj<Button>(L"smallBack.png", [this]() { isActive = false; }).setPosition({ WinHalfSizeX + 400, WinHalfSizeY - 400 }).setIsActive(false).setRoot(&exitButton);
}

ShowWave::~ShowWave()
{
	//�������� ���ݱ��� ���� ��� ui�� ���������.. ��� �ƹ��� �����̶�.. ��װ� ���� ����ִ°� ���� �ȵ���ϰŵ�? ��� �ٸ����Ϳ� ����ִ°ű��� �����ε�... �ᱹ ������ ������ �޾ƾ���.. 
	//�׸��� ������ �迭�� �������.. Ű�� ���°͵� ���� �����Ҽ������žƴϾ�.. ��.. �������� �ñ�°� ����. 
}

void ShowWave::Show()
{
	isActive = true;
	sprites[0]->isActive = true;//ù��°�� ����̶� ��������������
	for (auto var : sprites) //�̰͵� �����ε������� �����ҰŸ� �׳� for������ ó���ص��ǰ�
		var->isActive = true;
	//

	//�̰Ŵ� ������ ������ csv���� �����ؾ��ϴϱ� ���̵� ������.. 
	//������ �Ŵ������� �ҷ����� ���̺�ҷ�����... 
}

void ShowWave::Update(float deltaTime) //�̷��� �Ǹ� ��ģ���鵵 �ʿ���������.. �ܼ��� ����� �װ� ����������ΰ���? ������Ʈ�� ���� ���ӿ�����Ʈ ��ü��⺸�ٴ� �׳� ����ִ� Ʋ�� �Ұ���.. 
{ //�ٵ� ���ֵ��� �׷��ǾƴҰ�? �ʿ��� �ɷ��� ����ִ¾ֵ鵵�ִµ�.. ��� �ʿ�����ʳ�? 
}

void ShowWave::Render(ID2D1HwndRenderTarget* pRenderTarget)
{
}