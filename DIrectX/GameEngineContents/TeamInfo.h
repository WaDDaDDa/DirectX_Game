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

protected:

private:
    int IconNum = 0;
};

