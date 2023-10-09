#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "GameUnit.h"

class PythonessSkillBomb : public GameEngineActor
{
public:
    PythonessSkillBomb();
    ~PythonessSkillBomb();

    PythonessSkillBomb(const PythonessSkillBomb& _Other) = delete;
    PythonessSkillBomb(PythonessSkillBomb&& _Other) noexcept = delete;
    PythonessSkillBomb& operator=(const PythonessSkillBomb& _Other) = delete;
    PythonessSkillBomb& operator=(PythonessSkillBomb&& _Other) noexcept = delete;

    void SetUnit(std::shared_ptr<class GameUnit> _Unit, float _Att)
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
        Att = _Att;
    }

protected:
    void Start();
    void Update(float _Delta);

private:
    std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
    std::shared_ptr<GameEngineCollision> Col;
    float4 Scale = { 50.0f, 50.0f };
    class EventParameter Event;
    float Att = 0.0f;

    std::shared_ptr<class GameUnit> Unit;
};

