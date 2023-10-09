#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GameUnit.h"
#include "PythonessUlt.h"

class PythonessHeal : public GameEngineActor
{
public:
    PythonessHeal();
    ~PythonessHeal();

    PythonessHeal(const PythonessHeal& _Other) = delete;
    PythonessHeal(PythonessHeal&& _Other) noexcept = delete;
    PythonessHeal& operator=(const PythonessHeal& _Other) = delete;
    PythonessHeal& operator=(PythonessHeal&& _Other) noexcept = delete;

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
        // 회복 한다.
        for (size_t i = 0; i < Unit->EnemyGroup.size(); i++)
        {
            if (Unit->TeamGroup[i]->GetState() != GameUnitState::Die || Unit->TeamGroup[i]->GetState() != GameUnitState::DiePrev)
            {
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

    void InitUlt(std::shared_ptr<class PythonessUlt> _Unit)
    {
        Unit = _Unit->Unit;
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

        Transform.SetWorldPosition(_Unit->Transform.GetWorldPosition());

        float CurHpRate = 1.0f;
        size_t TeamNum = 0;
        // 회복 한다.
        for (size_t i = 0; i < Unit->EnemyGroup.size(); i++)
        {
            if (Unit->TeamGroup[i]->GetState() != GameUnitState::Die || Unit->TeamGroup[i]->GetState() != GameUnitState::DiePrev)
            {
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

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<GameEngineCollision> Col;
    float4 Scale = { 1.0f, 1.0f };
    float LifeTime = 5.0f;
    float Speed = 800.0f;
    bool AttackOn = false;
    class EventParameter Event;
    float4 Dir = float4::ZERO;
    float4 Pos = float4::ZERO;

    std::shared_ptr<class GameUnit> Unit;
    GameUnit* HealUnit = nullptr;

};

