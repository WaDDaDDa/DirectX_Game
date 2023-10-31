#pragma once
#include <GameEngineCore/GameEngineActor.h>

class TeamBundle : public GameEngineActor
{
public:
    TeamBundle();
    ~TeamBundle();

    TeamBundle(const TeamBundle& _Other) = delete;
    TeamBundle(TeamBundle&& _Other) noexcept = delete;
    TeamBundle& operator=(const TeamBundle& _Other) = delete;
    TeamBundle& operator=(TeamBundle&& _Other) noexcept = delete;

protected:
    void Start();
    void Update(float _Delta);

private:

    std::shared_ptr<class BundleButton> Recruitment;
    std::shared_ptr<class BundleButton> Traning;
    std::shared_ptr<class BundleButton> Squad;

    float4 ButtonPos = { -550.0f, -250.0f };
    float4 ButtonYInter = { 0.0f, 55.0f };

};

