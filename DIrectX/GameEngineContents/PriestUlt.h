#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GameUnit.h"

class PriestUlt : public GameEngineActor
{
public:
    PriestUlt();
    ~PriestUlt();

    PriestUlt(const PriestUlt& _Other) = delete;
    PriestUlt(PriestUlt&& _Other) noexcept = delete;
    PriestUlt& operator=(const PriestUlt& _Other) = delete;
    PriestUlt& operator=(PriestUlt&& _Other) noexcept = delete;

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
        float4 SpawnPos = Unit->Transform.GetWorldPosition();
        SpawnPos.Z = 350.0f;
        Transform.SetWorldPosition(SpawnPos);

    }

protected:
    void Start();
    void Update(float _Delta);
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<GameEngineCollision> Col;
    float4 Scale = { 500.0f, 500.0f };
    class EventParameter Event;
    float Att = 0.0f;
    float AttInter = 0.5f;
    float LifeTime = 7.0f;
    float EffectInter = 1.0f;
    std::shared_ptr<class GameEngineSpriteRenderer> AttRangeRenderer;
    float RangeValue = 0.0f;

    std::shared_ptr<class GameUnit> Unit;
};

