#include <GameEngineCore/GameEngineActor.h>

enum class UI_MouseState
{
    Idle, // �׳� ������ �ִ� ����
    Stay, // ���콺 Ŀ���� �ö� �ִ� ����.
    Click, // ���콺 Ŀ���� �ö� �ִ� ���¿��� Ŭ���� �� ����.
    Max,
};

class UI_Mouse : public GameEngineActor
{
public:
    UI_Mouse();
    ~UI_Mouse();

    UI_Mouse(const UI_Mouse& _Other) = delete;
    UI_Mouse(UI_Mouse&& _Other) noexcept = delete;
    UI_Mouse& operator=(const UI_Mouse& _Other) = delete;
    UI_Mouse& operator=(UI_Mouse&& _Other) noexcept = delete;

    void SetMouseColScale(float4 _Scale)
    {
        MouseColScale = _Scale;
        MouseCol->Transform.SetLocalScale(MouseColScale);
    }

protected:
    EventParameter ColEvent;

    void Start() override;
    void Update(float _Delta) override;

    void ChangeState(UI_MouseState _State);
    void StateUpdate(float _Delta);

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    virtual void MaxStart();
    virtual void MaxUpdate(float _Delta);

    virtual void IdleStart();
    virtual void IdleUpdate(float _Delta);

    virtual void StayStart();
    virtual void StayUpdate(float _Delta);

    virtual void ClickStart();
    virtual void ClickUpdate(float _Delta);

    UI_MouseState State = UI_MouseState::Max;
private:
    std::shared_ptr<GameEngineCollision> MouseCol;
    float4 MouseColScale = { 5.0f, 5.0f };
};

