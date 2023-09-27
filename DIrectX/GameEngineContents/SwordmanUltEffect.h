#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GameUnit.h"

class SwordmanUltEffect : public GameEngineActor
{
public:
    SwordmanUltEffect();
    ~SwordmanUltEffect();

    SwordmanUltEffect(const SwordmanUltEffect& _Other) = delete;
    SwordmanUltEffect(SwordmanUltEffect&& _Other) noexcept = delete;
    SwordmanUltEffect& operator=(const SwordmanUltEffect& _Other) = delete;
    SwordmanUltEffect& operator=(SwordmanUltEffect&& _Other) noexcept = delete;

    void SetUnit(std::shared_ptr<class GameUnit> _Unit)
    {
        Unit = _Unit;
        if (TeamType::Blue == Unit->MyTeam)
        {
            Col = CreateComponent<GameEngineCollision>(CollisionOrder::BlueTeamAttack);
            Col->SetCollisionType(ColType::AABBBOX2D);
            Col->Transform.SetLocalScale(Scale * 1.3f);
            Col->Transform.AddLocalPosition((Scale * 1.3f).hX());
        }
        else if (TeamType::Red == Unit->MyTeam)
        {
            Col = CreateComponent<GameEngineCollision>(CollisionOrder::RedTeamAttack);
            Col->SetCollisionType(ColType::AABBBOX2D);
            Col->Transform.SetLocalScale(Scale * 1.3f);
            Col->Transform.AddLocalPosition((Scale *1.3f).hX());
        }

        Transform.SetWorldPosition(Unit->Transform.GetWorldPosition());
        float4 Vec = Unit->GetAggroUnit()->Transform.GetWorldPosition() - Transform.GetWorldPosition();
        float4 Rot = Vec.NormalizeReturn().Angle2DDeg();
        float AggroY = Unit->GetAggroUnit()->Transform.GetWorldPosition().Y;
        float MyY = Transform.GetWorldPosition().Y;
        if (MyY <= AggroY)
        {
            Transform.SetWorldRotation({0.0f,0.0f, Rot.X });
        }
        else if (MyY > AggroY)
        {
            Transform.SetWorldRotation({ 0.0f,0.0f, -Rot.X });
        }
    }

protected:
    void Start() override;
    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void Update(float _Delta) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<class GameEngineCollision> Col;
    float4 Scale = { 310.0f , 40.0f };

    class EventParameter Event;

    std::shared_ptr<class GameUnit> Unit;
    float LifeTime = 8.0f;

};

