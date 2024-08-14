#include "pch.h"
#include "AnimationAsset.h"


bool AnimationAsset::LoadAnimation(std::wstring FilePath)
{
	

	std::wifstream file(FilePath);
	if (!file.is_open())
	{
		OutputDebugString(L"LoadAnimation 실패");
		return false;
	}


	std::wstring line; // 파일에서 읽은 각 줄을 저장용
	int animationCount = 0;
	std::getline(file, line);	  // 첫 번째 줄 읽기
	std::wstringstream wss(line); // 읽은 줄을 스트링 스트림으로 변환
	wss >> animationCount;		  // 애니메이션 개수를 스트림에서 읽기


	// 애니메이션 개수만큼 애니메이션 데이터를 읽어오기
	for (int i = 0; i < animationCount; i++)
	{
		if (!std::getline(file, line))
		{
			OutputDebugString(L"애니메이션 데이터 읽기 실패"); // 데이터 읽기 실패 시 디버그 메시지 출력
			return false; // 실패 시 false 반환
		}

		std::wstringstream wss(line);    // 한줄을 읽어서 wstringstream에 저장 첫줄 숫자
		std::wstring token;				 // wss의 내용을 ,를 기준으로 문자열을 분리

		getline(wss, token, L',');
		animations[i].Name = token;
		std::getline(wss, token, L',');
		if (!LoadAnimationFromCSV(i, token.c_str()))
		{
			OutputDebugString(L"애니메이션 데이터 로드 실패");
			return false;
		}
	}
	
	return true;
}

bool AnimationAsset::LoadAnimationFromCSV(int index, const wchar_t* fileName)  
{
	std::wifstream file(fileName); 
	if (!file.is_open()) {
		std::cout << "파일을 열 수 없습니다." << std::endl;
		return false;
	}
	std::wstring line;			// 한줄의 문자열	
	int FrameCount = 0;			// 프레임의 개수
	{
		std::getline(file, line);		// 첫번째 줄 읽기
		std::wstringstream wss(line);	// 읽은 줄을 스트링 스트림으로 변환
		wss >> FrameCount;				// 프레임 개수를 스트림에서 읽기
	}
	
	animations[index].Frames.resize(FrameCount);
	for (int j = 0; j < FrameCount; j++)
	{
		if (!std::getline(file, line))
		{
			OutputDebugString(L"프레임 데이터 읽기 실패");
			return false; // 실패 시 false 반환
		}
		std::wstringstream wss(line);   // 한줄을 읽어서 wstringstream에 저장
		std::wstring token;
		
		getline(wss, token, L',');	// wss의 내용을 ,를 기준으로 문자열을 분리
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

