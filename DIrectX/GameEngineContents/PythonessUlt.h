#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GameUnit.h"

enum class PythonessUltState
{
    Spwan,
    Idle,
    Die,
    Max
};

enum class PythonessUltDir
{
    Left,
    Right,

};

class PythonessUlt : public GameEngineActor
{
public:
    PythonessUlt();
    ~PythonessUlt();

    PythonessUlt(const PythonessUlt& _Other) = delete;
    PythonessUlt(PythonessUlt&& _Other) noexcept = delete;
    PythonessUlt& operator=(const PythonessUlt& _Other) = delete;
    PythonessUlt& operator=(PythonessUlt&& _Other) noexcept = delete;

    PythonessUltState State = PythonessUltState::Max;
    PythonessUltDir Dir = PythonessUltDir::Right;
    std::shared_ptr<class GameUnit> Unit;
    TeamType MyTeam = TeamType::Blue;
    float Att;
    float LifeTime = 5.0f;
    int AttCount = 1;
    
    float4 SpwanPos = { 40.0f , 0.0f };

    void SetUnit(std::shared_ptr<class GameUnit> _Unit)
    {
        Unit = _Unit;
        if (TeamType::Blue == Unit->MyTeam)
        {
            MyTeam = TeamType::Blue;

            Col = CreateComponent<GameEngineCollision>(CollisionOrder::BlueTeamAttack);
            Col->Transform.SetLocalScale(Scale);

        }
        else if (TeamType::Red == Unit->MyTeam)
        {
            MyTeam = TeamType::Red;

            Col = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamAttack);
            Col->Transform.SetLocalScale(Scale);
        }

        if (GameUnitDir::Left == Unit->GetDir())
        {
            Transform.SetWorldPosition((Unit->Transform.GetWorldPosition() -SpwanPos));
        }
        else if (GameUnitDir::Right == Unit->GetDir())
        {
            Transform.SetWorldPosition((Unit->Transform.GetWorldPosition() + SpwanPos));
        }

        ChangeDir();

    }

    void ChangeDir(PythonessUltDir _Dir)
    {
        if (_Dir != Dir)
        {
            Transform.AddLocalRotation({ 0.0f, 180.0f });
            Dir = _Dir;
        }
    }

    void ChangeDir()
    {
        if (GameUnitDir::Left == Unit->GetDir())
        {
            ChangeDir(PythonessUltDir::Left);
        }
        else if (GameUnitDir::Right == Unit->GetDir())
        {
            ChangeDir(PythonessUltDir::Right);
        }
    }

protected:
    void Start();
    void Update(float _Delta);

    void ChangeState(PythonessUltState _State);
    void StateUpdate(float _Delta);

    void SpwanStart();
    void SpwanUpdate(float _Delta);

    void IdleStart();
    void IdleUpdate(float _Delta);

    void DieStart();
    void DieUpdate(float _Delta);

    class EventParameter Event;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<GameEngineCollision> Col;
    float4 Scale = { 600.0f, 600.0f };
    float AttackSpeed = 1.0f;
    float AttackValue = 0.0f;
    float UltInter = 0.1f;
    float HealInter = 0.12f;

};

