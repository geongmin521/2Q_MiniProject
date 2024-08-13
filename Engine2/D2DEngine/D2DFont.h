#pragma once
#include "Renderer.h"

enum Setting // �뵵 ���� ���� �ϱ� ���ؼ�
{
	LEFT,
	MIDDLE,
	RIGHT,
	TOP,
	BOTTOM,
	EXIT
};


class Transform;
class Component;
class D2DFont : public Renderer // ���� �̸� Font���µ� ����ü�� �̹� �־ ������
{
public:
	D2DFont() = default;		 // ��Ʋ ���忡�� ��𼱰� ����ϰ� �ִµ� �ϴ� ����� ���� 
	D2DFont(const std::wstring _Dialog); // ���� ������ ��Ʈ ��ġ�� ���� ���Ŀ� �ܶ��� ���
	~D2DFont();

private:
	float FontSize = 10; 
	D2D1_POINT_2F Pos = {0.f , 0.f};   // ���� ��ǥ
	D2D_SIZE_F BoxSize = { 100.f, 50.f }; // �ؽ�Ʈ �ڽ� ������
	std::wstring Dialog; // public���� �س��� ����ڰ� ���� ���� �ۼ��ϴ°� �� ������?

	ID2D1SolidColorBrush* FontBrush = nullptr;
	IDWriteTextFormat* DWriteTextFormat = nullptr;;
	IDWriteTextLayout* DWriteTextLayout = nullptr;;

//	Transform* transform = nullptr;
//	bool IsTransform = false; 

	Setting FontX = MIDDLE;
	Setting FontY = MIDDLE;
public:
	virtual void Update(float deltaTime); // ������Ʈ�� �̰� �ʿ��Ұ�? ��λ���
	virtual void Render(ID2D1RenderTarget* pRenderTarget,float Alpha = 1);  // �ۼ��� ������ �׸�

	void SetColor(D2D1_COLOR_F color) { FontBrush->SetColor(color); } // �÷� ���� ���ǻ��� : ���� �ϱ����� ���� �����ؾ� ��
	void SetPos(float _X, float _Y) { Pos = { _X , _Y }; } // ��ġ ���� ������ǥ�϶� ���
	void SetBoxSize(float width, float height);
	void SetBoxSize(MathHelper::Vector2F size);
	void SetDialog(std::wstring input); // ���� ����

	void LoadFont(std::wstring FontName); // �뵵 ������ �۲ÿ� �ִ� ��Ʈ�� �ε��ϴ� ��
	void SetSize(float _FontSize , DWRITE_TEXT_RANGE textRange); // DWRITE_TEXT_RANGE ���� {0 , 9 } �̷��� ������ 0���� 9��° ������ ���� ũ�⸦ ����
	
	// ��Ʈ ���� �߸� �־����� ��� �߾����� ���ĵǰ� ������ 
	void Sort(Setting _SortX, Setting _SortY); // ����, ���, ������ ����

//	void OnTransform(); // Ʈ�������� �̿��� ������ ��� ���
//	Transform* GetTransform() { return transform; }

private:
	void CreateLayoutText(std::wstring detail); // �ؽ�Ʈ ������ �ۼ�
};

/// ��� ���� /// 
// �Ʒ��� 2���� ���� ������ �ϰ� LoadFont(L"�������� �۲�");�� �ϸ� �ȴ�.
// ������ D2DFont test(std::wstring n �Ǵ� L"�ȳ��ϼ���"); 
// Ʈ�������� ����ϴ� ���� OnTransform() �Լ��� ����ϰ� ���� GetTransform()->SetParent(������Ʈ�� Ʈ�������� �ϸ� �ȴ�.)
// �̷��� ����ҰŸ� ������Ʈ�� Ʈ������ Update()�� ���־�� �Ѵ�