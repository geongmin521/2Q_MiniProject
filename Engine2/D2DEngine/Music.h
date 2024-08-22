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
        Effect2,
        Enemy1,
        Enemy2,
        TowerHitted,
        TowerAttack,
        TowerAttack2,
        TowerAttack3,
        TowerEffect,
        TowerEffect2,
        TowerEffect3,
        TowerDeath,
        Size
    };

    enum class eSoundList
    {
        GameOver,
        MainTheme,
        GameTheme,
        BossWave,
        Ending,
        BatDestroy,
        BatBombDestroy,
        DeffendDestroy,
        EnemyDestroy,
        BossSummon,
        BossAttack,
        BossAppear,
        BossDestroy,
        Lock,
        UnLock,
        RewardClose,
        RewardOpen,
        Reroll,
        PopupClose,
        PopupOpen,
        MainButtonClick,
        ButtonClick,
        NexusDestroy,
        WaveStart,
        Tower1Star,
        Tower2Star,
        Tower3Star,
        PileHitted,
        TowerHitted,
        TowerDestroy,
        TowerReplace,
        HiddenSummon,
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
        // 할때마다 추가할것 일단 공통적인 tower + enemy만
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