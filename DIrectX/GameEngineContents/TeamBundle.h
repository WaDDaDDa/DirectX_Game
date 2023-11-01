#pragma once
#include "ButtonBundle.h"

class TeamBundle : public ButtonBundle
{
public:
    TeamBundle();
    ~TeamBundle();

    TeamBundle(const TeamBundle& _Other) = delete;
    TeamBundle(TeamBundle&& _Other) noexcept = delete;
    TeamBundle& operator=(const TeamBundle& _Other) = delete;
    TeamBundle& operator=(TeamBundle&& _Other) noexcept = delete;

protected:
    void Start() override;

private:

};

