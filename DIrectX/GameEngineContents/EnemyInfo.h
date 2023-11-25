#pragma once
#include "GamePlayer.h"

class EnemyInfo
{
public:
    EnemyInfo();
    ~EnemyInfo();

    EnemyInfo(const EnemyInfo& _Other) = delete;
    EnemyInfo(EnemyInfo&& _Other) noexcept = delete;
    EnemyInfo& operator=(const EnemyInfo& _Other) = delete;
    EnemyInfo& operator=(EnemyInfo&& _Other) noexcept = delete;

    static EnemyInfo Info;

    void Init()
    {
        class GamePlayerInfo NewInfo;
        GameEngineRandom Rand;

        for (size_t i = 0; i < 3; i++)
        {
            NewInfo.CpuRandom();
            NewInfo.HairNum = Rand.RandomInt(1, 29);
            EnemyPlayer.push_back(NewInfo);
        }
    }

    int GetIconNum()
    {
        return IconNum;
    }

    std::string GetTeamName()
    {
        return TeamName;
    }

    GamePlayerInfo GetOnePlayer()
    {
        return EnemyPlayer[0];
    }

    GamePlayerInfo GetTwoPlayer()
    {
        return EnemyPlayer[1];
    }

    GamePlayerInfo GetThreePlayer()
    {
        return EnemyPlayer[2];
    }

    int WinCount = 0;
    int KillCount = 0;

protected:

private:
    std::vector<class GamePlayerInfo> EnemyPlayer;

    int IconNum = 51;

    std::string TeamName = "SK L1";

};

