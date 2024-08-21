#pragma once
// FMOD
#ifndef _WIN64
#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif
#ifdef _WIN64
#include "fmod.hpp"
#pragma comment (lib, "fmod_vc.lib")
using namespace FMOD;
#endif
#include <string>

namespace Music
{
    enum class eSoundChannel
    {
        BGM,
        Effect1,
        EnemyHitted,
        EnemyHitted2,
        TowerHitted,
        TowerAttack,
        TowerAttack2,
        TowerEffect,
        Size
    };

    enum class eSoundList
    {
        GameOver,
        MainTheme,
        BatDestroy,
        BatBombDestroy,
        DeffendDestroy,
        Lock,
        UnLock,
        Reward,
        WaveStart,
        TowerUpgrade,
        PileHitted,
        TowerReplace,   
        CrossbowAttack,
        WaterAttack,
        HiddenAttack,
        HolyCrossAttack,
        PileAttack,
        CrossbowEffect,
        WaterEffect,
        HiddenEffect,
        HolyCrossEffect,
        PileEffect,
        Size
    };
    class SoundManager;  
    extern SoundManager* soundManager;  
    class SoundManager final
    {
    public:
        static SoundManager* GetInstance();

        static void DestroyInstance();

        void Init();

        void LoadMusic(eSoundList soundlist, bool loopcheck, const std::string& path);

        void PlayMusic(eSoundList list, eSoundChannel channel);

        void StopMusic(eSoundChannel channel);

        void SetVolume(float volume, eSoundChannel chanel);

        void SetIsWrong(int index, bool ture) { IsWrong[index] = ture;}

        void SetPause(eSoundChannel channel, bool isPaused);

        //bool IsPlay(eSoundChannel channel);

        eSoundList toEnum(const std::string& str);
    private:
        // �Ҷ����� �߰��Ұ� �ϴ� �������� tower + enemy��
        const std::unordered_map<std::string, eSoundList> stringToEnumMap = 
        {
                {"CrossbowAttack", eSoundList::CrossbowAttack},
                {"WaterAttack", eSoundList::WaterAttack},
                {"HiddenAttack", eSoundList::HiddenAttack},
                {"HolyCrossAttack", eSoundList::HolyCrossAttack},
                {"PileAttack", eSoundList::PileAttack},
                {"CrossbowEffect", eSoundList::CrossbowEffect},
                {"HolyCrossEffect", eSoundList::HolyCrossEffect},
                {"WaterEffect", eSoundList::WaterEffect},
                {"HiddenEffect", eSoundList::HiddenEffect},
                {"PileEffect", eSoundList::PileEffect},
                {"PileHitted", eSoundList::PileHitted},
                {"BatDestroy", eSoundList::BatDestroy},
                {"BatBombDestroy", eSoundList::BatBombDestroy},
                {"DeffendDestroy", eSoundList::DeffendDestroy},
        };

        SoundManager();

        ~SoundManager();

    private:

        static SoundManager* mInstance;
        bool IsWrong[6] = { false, false, false, false, false, false };
        FMOD::System* mSystem;
        FMOD::Channel* mChannel[static_cast<int>(eSoundChannel::Size)];
        FMOD::Sound* mSoundList[static_cast<int>(eSoundList::Size)];
        float mVolume;
    };

}