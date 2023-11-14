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
    void Update(float _Delta) override;

    std::shared_ptr<class BundleButton> Button1;
    std::shared_ptr<class BundleButton> Button2;
    std::shared_ptr<class BundleButton> Button3;


    std::shared_ptr<class PlayerRecruitmentUI> PRUI = nullptr;
    std::shared_ptr<class PlayerSquadUI> PSUI = nullptr;
private:

};

