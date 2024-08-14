#include "pch.h"
#include "AnimationAsset.h"


bool AnimationAsset::LoadAnimation(std::wstring FilePath)
{
	

	std::wifstream file(FilePath);
	if (!file.is_open())
	{
		OutputDebugString(L"LoadAnimation ����");
		return false;
	}


	std::wstring line; // ���Ͽ��� ���� �� ���� �����
	int animationCount = 0;
	std::getline(file, line);	  // ù ��° �� �б�
	std::wstringstream wss(line); // ���� ���� ��Ʈ�� ��Ʈ������ ��ȯ
	wss >> animationCount;		  // �ִϸ��̼� ������ ��Ʈ������ �б�


	// �ִϸ��̼� ������ŭ �ִϸ��̼� �����͸� �о����
	for (int i = 0; i < animationCount; i++)
	{
		if (!std::getline(file, line))
		{
			OutputDebugString(L"�ִϸ��̼� ������ �б� ����"); // ������ �б� ���� �� ����� �޽��� ���
			return false; // ���� �� false ��ȯ
		}

		std::wstringstream wss(line);    // ������ �о wstringstream�� ���� ù�� ����
		std::wstring token;				 // wss�� ������ ,�� �������� ���ڿ��� �и�

		getline(wss, token, L',');
		animations[i].Name = token;
		std::getline(wss, token, L',');
		if (!LoadAnimationFromCSV(i, token.c_str()))
		{
			OutputDebugString(L"�ִϸ��̼� ������ �ε� ����");
			return false;
		}
	}
	
	return true;
}

bool AnimationAsset::LoadAnimationFromCSV(int index, const wchar_t* fileName)  
{
	std::wifstream file(fileName); 
	if (!file.is_open()) {
		std::cout << "������ �� �� �����ϴ�." << std::endl;
		return false;
	}
	std::wstring line;			// ������ ���ڿ�	
	int FrameCount = 0;			// �������� ����
	{
		std::getline(file, line);		// ù��° �� �б�
		std::wstringstream wss(line);	// ���� ���� ��Ʈ�� ��Ʈ������ ��ȯ
		wss >> FrameCount;				// ������ ������ ��Ʈ������ �б�
	}
	
	animations[index].Frames.resize(FrameCount);
	for (int j = 0; j < FrameCount; j++)
	{
		if (!std::getline(file, line))
		{
			OutputDebugString(L"������ ������ �б� ����");
			return false; // ���� �� false ��ȯ
		}
		std::wstringstream wss(line);   // ������ �о wstringstream�� ����
		std::wstring token;
		
		getline(wss, token, L',');	// wss�� ������ ,�� �������� ���ڿ��� �и�
		animations[index].Frames[j].Source.left = (float)_wtoi(token.c_str());
		getline(wss, token, L',');
		animations[index].Frames[j].Source.top = (float)_wtoi(token.c_str());
		getline(wss, token, L',');
		animations[index].Frames[j].Source.right = (float)_wtoi(token.c_str());
		getline(wss, token, L',');
		animations[index].Frames[j].Source.bottom = (float)_wtoi(token.c_str());
		getline(wss, token, L',');
		animations[index].Frames[j].Center.x = (float)_wtoi(token.c_str());
		getline(wss, token, L',');
		animations[index].Frames[j].Center.y = (float)_wtoi(token.c_str());
		getline(wss, token, L',');
		animations[index].Frames[j].Duration = std::wcstod(token.c_str(), nullptr);
		
	}
			
	return true;
}

