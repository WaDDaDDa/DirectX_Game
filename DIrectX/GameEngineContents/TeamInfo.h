#pragma once

class TeamInfo :public std::enable_shared_from_this<TeamInfo>
{
public:
    TeamInfo();
    ~TeamInfo();

    static TeamInfo MyInfo;

    void SetIconNum(int _Num)
    {
        IconNum = _Num;
    }

    int GetIconNum()
    {
        return IconNum;
    }

    void SetHairNum(int _Num)
    {
        HairNum = _Num;
    }

    int GetHairNum()
    {
        return HairNum;
    }

    void SetGold(int _Num)
    {
        Gold = _Num;
    }

    void AddGold(int _Num)
    {
        Gold += _Num;
    }

    int GetGold()
    {
        return Gold;
    }

    std::string GetDate()
    {
        std::string Date = std::to_string(Year);
        Date += "년 ";
        Date += std::to_string(Month);
        Date += "월 ";
        Date += std::to_string(Week);
        Date += "주차";

        return Date;
    }

    void SetCoach(std::shared_ptr<class Coach> _Coach)
    {
        MyCoach = _Coach;
    }

    void AddPlayer(std::shared_ptr<class GamePlayer> _Player)
    {
        MyPlayer.push_back(_Player);
    }

    void AddWeek(int _Week)
    {
        Week += _Week;

        if (5 <= Week)
        {
            Week = 1;
            Month += 1;
        }

        if (13 <= Month)
        {
            Month = 1;
            Year += 1;
        }
    }

    int GetWeek()
    {
        return Week;
    }

    std::list<std::shared_ptr<class GamePlayer>>& GetMyPlayer()
    {
        return MyPlayer;
    }

    //void Resize()
    //{
    //    for (std::shared_ptr<GamePlayer>& Player : MyPlayer)
    //    {
    //        if (true == Player->IsDeath())
    //        {
    //            Player.reset();
    //        }
    //    }
    //}


protected:

private:
    int IconNum = 0;
    int HairNum = 0;
    int Gold = 200;
    int Year = 2023;
    int Month = 1;
    int Week = 1;

    std::shared_ptr<class Coach> MyCoach;
    std::list<std::shared_ptr<class GamePlayer>> MyPlayer;
};

