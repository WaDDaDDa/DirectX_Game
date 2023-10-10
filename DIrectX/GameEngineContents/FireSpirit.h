#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GameUnit.h"

enum class FireSpiritState
{
    Spwan,
    Idle,
    Attack1,
    Attack2,
    Die,
    Max
};

enum class FireSpiritDir
{
    Left,
    Right,

};

class FireSpirit : public GameEngineActor
{
public:
    FireSpirit();
    ~FireSpirit();

    FireSpirit(const FireSpirit& _Other) = delete;
    FireSpirit(FireSpirit&& _Other) noexcept = delete;
    FireSpirit& operator=(const FireSpirit& _Other) = delete;
    FireSpirit& operator=(FireSpirit&& _Other) noexcept = delete;

    FireSpiritState State = FireSpiritState::Max;
    FireSpiritDir Dir = FireSpiritDir::Right;
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
    }

    void ChangeDir(FireSpiritDir _Dir)
    {
        if (_Dir != Dir)
        {
            Transform.AddLocalRotation({ 0.0f, 180.0f });
            Dir = _Dir;
        }
    }

    void ChangeDir()
    {
        if (Transform.GetWorldPosition().X > Unit->GetAggroUnit()->Transform.GetWorldPosition().X)
        {
            ChangeDir(FireSpiritDir::Left);
        }
        else if (Transform.GetWorldPosition().X <= Unit->GetAggroUnit()->Transform.GetWorldPosition().X)
        {
            ChangeDir(FireSpiritDir::Right);
        }
    }

protected:
    void Start();
    void Update(float _Delta);

    void ChangeState(FireSpiritState _State);
    void StateUpdate(float _Delta);

    void SpwanStart();
    void SpwanUpdate(float _Delta);

    void IdleStart();
    void IdleUpdate(float _Delta);

    void Attack1Start();
    void Attack1Update(float _Delta);

    void Attack2Start();
    void Attack2Update(float _Delta);

    void DieStart();
    void DieUpdate(float _Delta);

    class EventParameter Event;

    float RangeValue = 0.0f;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<class GameEngineSpriteRenderer> EffectRenderer;
    std::shared_ptr<class GameEngineSpriteRenderer> AttRangeRenderer;
    std::shared_ptr<GameEngineCollision> Col;
    float4 Scale = { 200.0f, 200.0f };
    float AttackSpeed = 1.5f;
    float AttackValue = 0.0f;
};

