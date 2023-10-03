#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GameUnit.h"

class FlameAttack : public GameEngineActor
{
public:
    FlameAttack();
    ~FlameAttack();

    FlameAttack(const FlameAttack& _Other) = delete;
    FlameAttack(FlameAttack&& _Other) noexcept = delete;
    FlameAttack& operator=(const FlameAttack& _Other) = delete;
    FlameAttack& operator=(FlameAttack&& _Other) noexcept = delete;

    void SetUnit(std::shared_ptr<class GameUnit> _Unit)
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

        Transform.SetWorldPosition(Unit->GetAggroUnit()->Transform.GetWorldPosition());

    }

protected:
    void Start();
    void Update(float _Delta);

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<GameEngineCollision> Col;
    float4 Scale = { 50.0f, 50.0f };
    class EventParameter Event;

    std::shared_ptr<class GameUnit> Unit;
};

