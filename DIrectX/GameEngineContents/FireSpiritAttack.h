#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GameUnit.h"
#include "FireSpirit.h"

class FireSpiritAttack : public GameEngineActor
{
public:
    FireSpiritAttack();
    ~FireSpiritAttack();

    FireSpiritAttack(const FireSpiritAttack& _Other) = delete;
    FireSpiritAttack(FireSpiritAttack&& _Other) noexcept = delete;
    FireSpiritAttack& operator=(const FireSpiritAttack& _Other) = delete;
    FireSpiritAttack& operator=(FireSpiritAttack&& _Other) noexcept = delete;

    // 소환수, 적대상
    void Init(std::shared_ptr<class FireSpirit> _Unit, std::shared_ptr<class GameUnit> _Enemy)
    {
        Unit = _Unit;
        if (TeamType::Blue == Unit->MyTeam)
        {
            Col = CreateComponent<GameEngineCollision>(CollisionOrder::BlueTeamAttack);
            Col->Transform.SetLocalScale(Scale);
            //Col->Transform.AddLocalPosition((Scale * 1.3f).hX());
        }
        else if (TeamType::Red == Unit->MyTeam)
        {
            Col = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamAttack);
            Col->Transform.SetLocalScale(Scale);
            //Col->Transform.AddLocalPosition((Scale * 1.3f).hX());
        }

        Transform.SetWorldPosition(Unit->Transform.GetWorldPosition());
        Dir = _Enemy->Transform.GetWorldPosition() - Transform.GetWorldPosition();
        Dir.Normalize();
        float4 Rot = Dir.Angle2DDeg();
        float AggroY = _Enemy->Transform.GetWorldPosition().Y;
        float MyY = Transform.GetWorldPosition().Y;
        if (MyY <= AggroY)
        {
            Transform.SetWorldRotation({ 0.0f,0.0f, Rot.X });
        }
        else if (MyY > AggroY)
        {
            Transform.SetWorldRotation({ 0.0f,0.0f, -Rot.X });
        }
    }

protected:
    void Start();
    void Update(float _Delta);

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<GameEngineCollision> Col;
    float4 Scale = { 1.0f, 1.0f };
    float LifeTime = 2.0f;
    float Speed = 500.0f;
    bool AttackOn = false;
    class EventParameter Event;
    float4 Dir = float4::ZERO;
    float4 Pos = float4::ZERO;

    std::shared_ptr<class FireSpirit> Unit;
    GameUnit* EnemyUnit = nullptr;

};

