#pragma once
#include "SingletonBase.h"
enum EasingEffect
{
    // Linear
    Linear,

    // Sine
    InSine,
    OutSine,
    InOutSine,

    // Quad
    InQuad,
    OutQuad,
    InOutQuad,

    // Cubic
    InCubic,
    OutCubic,
    InOutCubic,

    // Quart
    InQuart,
    OutQuart,
    InOutQuart,

    // Quint
    InQuint,
    OutQuint,
    InOutQuint,

    // Expo
    InExpo,
    OutExpo,
    InOutExpo,

    // InCirc
    InCirc,
    OutCirc,
    InOutCirc,

    // Back
    InBack,
    OutBack,
    InOutBack,

    // Elastic
    InElastic,
    OutElastic,
    InOutElastic,

    // Bounce
    InBounce,
    OutBounce,
    InOutBounce,

    EasingEffectEnd
};
#pragma region GraphFunc
// Linear
float EaseLinear(float x);

// Sine
float EaseInSine(float x);
float EaseOutSine(float x);
float EaseInOutSine(float x);

// Quad
float EaseInQuad(float x);
float EaseOutQuad(float x);
float EaseInOutQuad(float x);

// Cubic
float EaseInCubic(float x);
float EaseOutCubic(float x);
float EaseInOutCubic(float x);

// Quart
float EaseInQuart(float x);
float EaseOutQuart(float x);
float EaseInOutQuart(float x);

// Quint
float EaseInQuint(float x);
float EaseOutQuint(float x);
float EaseInOutQuint(float x);

// Expo
float EaseInExpo(float x);
float EaseOutExpo(float x);
float EaseInOutExpo(float x);

// InCirc
float EaseInCirc(float x);
float EaseOutCirc(float x);
float EaseInOutCirc(float x);

// Back
float EaseInBack(float x);
float EaseOutBack(float x);
float EaseInOutBack(float x);

// Elastic
float EaseInElastic(float x);
float EaseOutElastic(float x);
float EaseInOutElastic(float x);

// Bounce
float EaseInBounce(float x);
float EaseOutBounce(float x);
float EaseInOutBounce(float x);
#pragma endregion GraphFunc
static std::function<float(float)> EasingFunction[EasingEffect::EasingEffectEnd] =
{
    // Linear
    EaseLinear,

    // Sine
    EaseInSine,
    EaseOutSine,
    EaseInOutSine,

    // Quad
    EaseInQuad,
    EaseOutQuad,
    EaseInOutQuad,

    // Cubic
    EaseInCubic,
    EaseOutCubic,
    EaseInOutCubic,

    // Quart
    EaseInQuart,
    EaseOutQuart,
    EaseInOutQuart,

    // Quint
    EaseInQuint,
    EaseOutQuint,
    EaseInOutQuint,

    // Expo
    EaseInExpo,
    EaseOutExpo,
    EaseInOutExpo,

    // InCirc
    EaseInCirc,
    EaseOutCirc,
    EaseInOutCirc,

    // Back
    EaseInBack,
    EaseOutBack,
    EaseInOutBack,

    // Elastic
    EaseInElastic,
    EaseOutElastic,
    EaseInOutElastic,

    // Bounce
    EaseInBounce,
    EaseOutBounce,
    EaseInOutBounce,
};;

enum StepAnimation
{
    StepOnceForward,
    StepOnceBack,
    StepOncePingPong,
    StepLoopForward,
    StepLoopBack,
    StepLoopPingPong,

    StepAnimationEnd
};
//근데 템플릿으로 다 저장할수가있나? 글쎄다.. 안될거같은데.. 만들어서 업데이트를 돌려야하는데.. 
//생성 시점은 언제 파악하고 .. 업데이트는 어떻게 돌리지? 

class DOTween
{
public:
    DOTween(float& _Data, EasingEffect _EasingEffect, StepAnimation _StepAnimation = StepOnceForward, float duration = 1, float startpoint = 0, float endpoint = 1);
    ~DOTween();

    void   SetStartPoint(float _StartPoint) { StartPoint = _StartPoint; } //이거 초기값 세팅해줘야함. 
    void   SetEndPoint(float _EndPoint) { EndPoint = _EndPoint; }
    void   SetDuration(float   _Duration) { Duration = _Duration; }

    void   Update(const float& _DeltaTime) //시간이 지나면 본인이 스스로 소멸하는건가?
    {
        (this->*StepAnimationFunction[Type])(_DeltaTime);
    }

private:
    float& Data;         //   0 ~ 1(StartPoint ~ EndPoint)
    float                     StartPoint;
    float                     EndPoint;
    float                  Duration;      // N초 동안
    float                  CurTime = 0.f;
    std::function<float(float)>   Function;
    StepAnimation            Type;

private:
    void OnceForward(const float& _DeltaTime) //once는 한번만이고 loop 반복..   Forward 함수그래프의 시작이 앞에서 Back뒤에서 PingPong 앞에서 뒤로 왔다 갔다
    {
        if (CurTime > Duration)
        {
            delete this;
            return;
        }
          
        float CurStepTime;
        float CurStep;

        CurTime += _DeltaTime;
        CurStepTime = CurTime / Duration;
        CurStep = EndPoint - StartPoint;

        Data = StartPoint + CurStep * Function(CurStepTime); //소멸은 언제되지? 시간이 끝나면?
    }
    void OnceBack(const float& _DeltaTime)
    {
        if (CurTime > Duration)
        {
            delete this;
            return;
        }
        float CurStepTime;
        float CurStep;

        CurTime += _DeltaTime;
        CurStepTime = 1.f - (CurTime / Duration);
        CurStep = EndPoint - StartPoint;

        Data = StartPoint + CurStep * Function(CurStepTime);
    }
    void OncePingPong(const float& _DeltaTime)
    {
        if (CurTime > Duration)
        {
            delete this;
            return;
        }
        float CurStepTime;
        float CurStep;

        CurTime += _DeltaTime;
        CurStepTime = (CurTime < (Duration / 2))
            ? CurTime / (Duration / 2)
            : 1.f - ((CurTime - Duration / 2) / (Duration / 2));
        CurStep = EndPoint - StartPoint;

        Data = StartPoint + CurStep * Function(CurStepTime);
    }
    void LoopForward(const float& _DeltaTime) //루프는 종료조건이 없음
    {
        if (CurTime > Duration)
            CurTime -= Duration;
        float CurStepTime;
        float CurStep;

        CurTime += _DeltaTime;
        CurStepTime = CurTime / Duration;
        CurStep = EndPoint - StartPoint;

        Data = StartPoint + CurStep * Function(CurStepTime);
    }
    void LoopBack(const float& _DeltaTime)
    {
        if (CurTime > Duration)
            CurTime -= Duration;
        float CurStepTime;
        float CurStep;

        CurTime += _DeltaTime;
        CurStepTime = 1.f - (CurTime / Duration);
        CurStep = EndPoint - StartPoint;

        Data = StartPoint + CurStep * Function(CurStepTime);
    }
    void LoopPingPong(const float& _DeltaTime)
    {
        if (CurTime > Duration)
            CurTime -= Duration;
        float CurStepTime;
        float CurStep;

        CurTime += _DeltaTime;
        CurStepTime = (CurTime < (Duration / 2))
            ? CurTime / (Duration / 2)
            : 1.f - ((CurTime - Duration / 2) / (Duration / 2));
        CurStep = EndPoint - StartPoint;

        Data = StartPoint + CurStep * Function(CurStepTime);
    }

    //얘는 왜 전역으로되어있지? 
    static void (DOTween::* StepAnimationFunction[StepAnimation::StepAnimationEnd])(const float&);
};

// 정적 멤버 함수 포인터 배열 초기화


