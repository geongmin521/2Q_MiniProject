#include "pch.h"
#include "Factory.h"
#include "ShowWave.h"
#include "Image.h"
#include "Button.h"

ShowWave::ShowWave()
{
	float LeftPadding = 800;
	Factory().createObj<Image>(L"BigBack.png").setPosition({WinHalfSizeX ,WinHalfSizeY}).setScale({2,2}).setActive(false).setRoot(&sprites);
	for (int i = 0; i < 4; i++)
	{
		Factory().createObj<Image>(L"vampire.png").setPosition({LeftPadding + i * 130 ,WinHalfSizeY}).setActive(false).setRoot(&sprites);
		//�ؽ�Ʈ�� �߰��ϱ�... //�̰͵� ���丮�� �߰������̱��ѵ�.. ���UI�� ����ȯ�̵Ǿ����.. �ƴѰ�? �ٸ��ֵ鵵 �ʿ��Ѱ�? 
	}
		
	Factory().createObj<Button>(L"smallBack.png", [this]() { SetActive(false); }).setPosition({ WinHalfSizeX + 400, WinHalfSizeY - 400 }).setActive(false).setRoot(&exitButton);
}

ShowWave::~ShowWave()
{
	//�������� ���ݱ��� ���� ��� ui�� ���������.. ��� �ƹ��� �����̶�.. ��װ� ���� ����ִ°� ���� �ȵ���ϰŵ�? ��� �ٸ����Ϳ� ����ִ°ű��� �����ε�... �ᱹ ������ ������ �޾ƾ���.. 
	//�׸��� ������ �迭�� �������.. Ű�� ���°͵� ���� �����Ҽ������žƴϾ�.. ��.. �������� �ñ�°� ����. 
}

