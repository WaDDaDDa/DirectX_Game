#pragma once
#include <GameEngineCore/GameEngineActor.h>

enum class UI_ButtonState
{
    Idle, // 그냥 가만히 있는 상태
    Enter,
    Stay, // 마우스 커서가 올라가 있는 상태.
    End,
    Click, // 마우스 커서가 올라가 있는 상태에서 클릭을 한 상태.
    Max,
};

class UI_Button : public GameEngineActor
{
public:
    UI_Button();
    ~UI_Button();

    UI_Button(const UI_Button& _Other) = delete;
    UI_Button(UI_Button&& _Other) noexcept = delete;
    UI_Button& operator=(const UI_Button& _Other) = delete;
    UI_Button& operator=(UI_Button&& _Other) noexcept = delete;

    void SetButtonColScale(float4 _Scale)
    {
        ButtonColScale = _Scale;
        ButtonCol->Transform.SetLocalScale(ButtonColScale);
    }

protected:
    EventParameter ColEvent;

    void Start() override;
    void Update(float _Delta) override;

    void ChangeState(UI_ButtonState _State);
    void StateUpdate(float _Delta);

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    virtual void MaxStart();
    virtual void MaxUpdate(float _Delta);

    virtual void IdleStart();
    virtual void IdleUpdate(float _Delta);

    virtual void EnterStart();
    virtual void EnterUpdate(float _Delta);

    virtual void StayStart();
    virtual void StayUpdate(float _Delta);

    virtual void EndStart();
    virtual void EndUpdate(float _Delta);

    virtual void ClickStart();
    virtual void ClickUpdate(float _Delta);

    UI_ButtonState State = UI_ButtonState::Max;
private:
    std::shared_ptr<GameEngineCollision> ButtonCol;
    float4 ButtonColScale = { 200.0f, 100.0f };

};

