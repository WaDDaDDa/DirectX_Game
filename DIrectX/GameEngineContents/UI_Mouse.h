#include <GameEngineCore/GameEngineActor.h>

enum class UI_MouseState
{
    Idle, // 그냥 가만히 있는 상태
    Stay, // 마우스 커서가 올라가 있는 상태.
    Click, // 마우스 커서가 올라가 있는 상태에서 클릭을 한 상태.
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

    static std::shared_ptr<class UI_Mouse> GameMouse;

    void SetMouseColScale(float4 _Scale)
    {
        MouseColScale = _Scale;
        MouseCol->Transform.SetLocalScale(MouseColScale);
    }

    TeamType GetPlayerTeam()
    {
        return PlayerTeam;
    }

    void SetPlayerTeam(TeamType _Team)
    {
        PlayerTeam = _Team;
    }

    void TeamSwitch()
    {
        if (TeamType::Blue == PlayerTeam)
        {
            PlayerTeam = TeamType::Red;
        }
        else if (TeamType::Red == PlayerTeam)
        {
            PlayerTeam = TeamType::Blue;
        }
    }

    std::shared_ptr<GameEngineCollision> MouseCol;

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
    TeamType PlayerTeam = TeamType::Blue;

    float4 MouseColScale = { 2.0f, 2.0f };
};

