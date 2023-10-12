#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GameUnit.h"

class MonkUlt : public GameEngineActor
{
public:
    MonkUlt();
    ~MonkUlt();

    MonkUlt(const MonkUlt& _Other) = delete;
    MonkUlt(MonkUlt&& _Other) noexcept = delete;
    MonkUlt& operator=(const MonkUlt& _Other) = delete;
    MonkUlt& operator=(MonkUlt&& _Other) noexcept = delete;

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

        Transform.SetWorldPosition(Unit->Transform.GetWorldPosition());

    }

protected:
    void Start();
    void Update(float _Delta);
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<GameEngineCollision> Col;
    float4 Scale = { 500.0f, 500.0f };
    class EventParameter Event;
    float Att = 0.0f;
    float AttInter = 0.5f;
    float LifeTime = 5.0f;
    float EffectInter = 0.05f;

    std::shared_ptr<class GameUnit> Unit;
};

