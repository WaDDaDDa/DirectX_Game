#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GameUnit.h"

class PythonessSkill : public GameEngineActor
{
public:
    PythonessSkill();
    ~PythonessSkill();

    PythonessSkill(const PythonessSkill& _Other) = delete;
    PythonessSkill(PythonessSkill&& _Other) noexcept = delete;
    PythonessSkill& operator=(const PythonessSkill& _Other) = delete;
    PythonessSkill& operator=(PythonessSkill&& _Other) noexcept = delete;

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

        float CurHpRate = 1.0f;
        size_t TeamNum = 0;
        // ȸ�� �Ѵ�.
        for (size_t i = 0; i < Unit->EnemyGroup.size(); i++)
        {
            if (Unit->TeamGroup[i]->GetState() != GameUnitState::Die || Unit->TeamGroup[i]->GetState() != GameUnitState::DiePrev)
            {
                if (Unit->TeamGroup[i]->GetState() == GameUnitState::Die || Unit->TeamGroup[i]->GetState() == GameUnitState::DiePrev)
                {
                    continue;
                }

                if (CurHpRate >= Unit->TeamGroup[i]->GetHPRate())
                {
                    CurHpRate = Unit->TeamGroup[i]->GetHPRate();
                    TeamNum = i;
                }
            }
        }

        Unit->TeamGroup[TeamNum]->HealTarget = true;

        Dir = Unit->TeamGroup[TeamNum]->Transform.GetWorldPosition() - Transform.GetWorldPosition();
        Dir.Normalize();
        float4 Rot = Dir.Angle2DDeg();
        float AggroY = Unit->TeamGroup[TeamNum]->Transform.GetWorldPosition().Y;
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
    void LevelEnd(GameEngineLevel* _NextLevel) override;

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<GameEngineCollision> Col;
    float4 Scale = { 1.0f, 1.0f };
    float LifeTime = 5.0f;
    float Speed = 900.0f;
    bool AttackOn = false;
    class EventParameter Event;
    float4 Dir = float4::ZERO;
    float4 Pos = float4::ZERO;

    std::shared_ptr<class GameUnit> Unit;
    GameUnit* HealUnit = nullptr;

};

