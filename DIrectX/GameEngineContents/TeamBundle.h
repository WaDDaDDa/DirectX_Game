#pragma once
#include <GameEngineCore/GameEngineActor.h>
enum class BundleState
{
    Idle,
    PopUp,
    PopDown,
    Max,
};

class TeamBundle : public GameEngineActor
{
public:
    TeamBundle();
    ~TeamBundle();

    TeamBundle(const TeamBundle& _Other) = delete;
    TeamBundle(TeamBundle&& _Other) noexcept = delete;
    TeamBundle& operator=(const TeamBundle& _Other) = delete;
    TeamBundle& operator=(TeamBundle&& _Other) noexcept = delete;

    GameEngineState State;
    bool IsPopUp = false;
protected:
    void Start();
    void Update(float _Delta);
private:

    std::shared_ptr<class BundleButton> Recruitment;
    std::shared_ptr<class BundleButton> Traning;
    std::shared_ptr<class BundleButton> Squad;

    void AllButtonColOn();
    void AllButtonColOff();

    float4 ButtonPos = { -550.0f, -250.0f };
    float4 ButtonYInter = { 0.0f, 55.0f };

    float PopDownDelta = 0.0f;
    float PopUpDelta = 0.0f;
    float TestValue = 1.0f;
};

