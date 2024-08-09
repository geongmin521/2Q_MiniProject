#pragma once

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


class Dotween
{
};

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

template<typename T>
class DOTween
{
public:
    DOTween(T& _Data, EasingEffect _EasingEffect, StepAnimation _StepAnimation = StepOnceForward)
        :Data(_Data), Function(EasingFunction[_EasingEffect]), Type(_StepAnimation)
    {}
    ~DOTween() {};

    void   SetStartPoint(T _StartPoint) { StartPoint = _StartPoint; }
    void   SetEndPoint(T _EndPoint) { EndPoint = _EndPoint; }
    void   SetDuration(float   _Duration) { Duration = _Duration; }

    void   Update(const float& _DeltaTime)
    {
        (this->*StepAnimationFunction[Type])(_DeltaTime);
    }

private:
    T& Data;         //   0 ~ 1(StartPoint ~ EndPoint)
    T                     StartPoint;
    T                     EndPoint;
    float                  Duration;      // N�� ����
    float                  CurTime = 0.f;
    std::function<float(float)>   Function;
    StepAnimation            Type;

private:
    void OnceForward(const float& _DeltaTime) //once�� �ѹ����̰� loop �ݺ�..   Forward �Լ��׷����� ������ �տ��� Back�ڿ��� PingPong �տ��� �ڷ� �Դ� ����
    {
        if (CurTime > Duration)
            return;
        float CurStepTime;
        T CurStep;

        CurTime += _DeltaTime;
        CurStepTime = CurTime / Duration;
        CurStep = EndPoint - StartPoint;

        Data = StartPoint + CurStep * Function(CurStepTime); //�Ҹ��� ��������? �ð��� ������?
    }
    void OnceBack(const float& _DeltaTime)
    {
        if (CurTime > Duration)
            return;
        float CurStepTime;
        T CurStep;

        CurTime += _DeltaTime;
        CurStepTime = 1.f - (CurTime / Duration);
        CurStep = EndPoint - StartPoint;

        Data = StartPoint + CurStep * Function(CurStepTime);
    }
    void OncePingPong(const float& _DeltaTime)
    {
        if (CurTime > Duration)
            return;
        float CurStepTime;
        T CurStep;

        CurTime += _DeltaTime;
        CurStepTime = (CurTime < (Duration / 2))
            ? CurTime / (Duration / 2)
            : 1.f - ((CurTime - Duration / 2) / (Duration / 2));
        CurStep = EndPoint - StartPoint;

        Data = StartPoint + CurStep * Function(CurStepTime);
    }
    void LoopForward(const float& _DeltaTime)
    {
        if (CurTime > Duration)
            CurTime -= Duration;
        float CurStepTime;
        T CurStep;

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
        T CurStep;

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
        T CurStep;

        CurTime += _DeltaTime;
        CurStepTime = (CurTime < (Duration / 2))
            ? CurTime / (Duration / 2)
            : 1.f - ((CurTime - Duration / 2) / (Duration / 2));
        CurStep = EndPoint - StartPoint;

        Data = StartPoint + CurStep * Function(CurStepTime);
    }

    static void (DOTween::* StepAnimationFunction[StepAnimation::StepAnimationEnd])(const float&);
};

// ���� ��� �Լ� ������ �迭 �ʱ�ȭ
template<typename T>
void (DOTween<T>::* DOTween<T>::StepAnimationFunction[StepAnimation::StepAnimationEnd])(const float&) =
{
   &DOTween<T>::OnceForward,
   &DOTween<T>::OnceBack,
   &DOTween<T>::OncePingPong,
   &DOTween<T>::LoopForward,
   &DOTween<T>::LoopBack,
   &DOTween<T>::LoopPingPong
};
