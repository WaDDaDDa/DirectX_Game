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
        for (size_t i = 0; i < 2; i++)
        {
            class GamePlayerInfo NewInfo;
            NewInfo.Random();
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

protected:

private:
    std::vector<class GamePlayerInfo> EnemyPlayer;

    int IconNum = 51;

    std::string TeamName = "SK L1";

};

