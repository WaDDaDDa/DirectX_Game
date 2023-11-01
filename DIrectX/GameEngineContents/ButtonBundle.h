#pragma once
#include <GameEngineCore/GameEngineActor.h>
enum class BundleState
{
    Idle,
    PopUp,
    PopDown,
    Max,
};

class ButtonBundle : public GameEngineActor
{
public:
    ButtonBundle();
    ~ButtonBundle();

    ButtonBundle(const ButtonBundle& _Other) = delete;
    ButtonBundle(ButtonBundle&& _Other) noexcept = delete;
    ButtonBundle& operator=(const ButtonBundle& _Other) = delete;
    ButtonBundle& operator=(ButtonBundle&& _Other) noexcept = delete;

    GameEngineState State;
    bool IsPopUp = false;

    bool IsButtonsClick();

protected:
    void Start();
    void Update(float _Delta);

    void AllButtonColOn();
    void AllButtonColOff();

    void CreateButton(const std::string& _Text);

    std::vector<std::shared_ptr<class BundleButton>> Buttons;

    float4 ButtonPos = { -550.0f, -250.0f };
    float4 ButtonYInter = { 0.0f, 55.0f };
    float MovePos = 0.0f;
    float CreateCount = 0.0f;

    float PopDownDelta = 0.0f;
    float PopUpDelta = 0.0f;
    float TestValue = 1.0f;
private:
};

