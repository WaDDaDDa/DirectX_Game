#pragma once
#include "GameUnit.h"

class Swordman : public GameUnit
{
public:
    Swordman();
    ~Swordman();

    Swordman(const Swordman& _Other) = delete;
    Swordman(Swordman&& _Other) noexcept = delete;
    Swordman& operator=(const Swordman& _Other) = delete;
    Swordman& operator=(Swordman&& _Other) noexcept = delete;

    void SetUnitStatus()
    {
        AttackRange = SwordmanAttackRange;
        SkillRange = SwordmanSkillRange;
        UltRange = SwordmanUltRange;

        UnitSpeed = SwordmanSpeed;
        UnitHP = SwordmanHp;
        UnitDef = SwordmanDef;

        AttackDelay = SwordmanAttackDeley;

        SkillCooltime = SwordmanSkillCooltime;

        UltCooltime = SwordmanUltCooltime;
    }

    std::shared_ptr<class GameEngineSpriteRenderer> SkillEffectRenderer;

protected:
    void Start() override;
    // void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    void SpwanStart() override;

    void IdleStart() override;

    void MoveStart() override;
    void BackMoveStart() override;

    void SearchMoveStart() override;

    void AttackStart() override;
    void AttackUpdate(float _Delta) override;

    void SkillStart() override;
    void SkillUpdate(float _Delta) override;

    void Skill2Start() override;
    void Skill2Update(float _Delta) override;

private:
    float4 SwordmanAttackRange = { 55.0f, 55.0f };
    float4 SwordmanSkillRange = { 55.0f, 55.0f };
    float4 SwordmanUltRange = { 55.0f, 55.0f };

    float SwordmanSpeed = 100.0f;
    float SwordmanHp = 1000.0f;
    float SwordmanDef = 10.0f;
    float SwordmanAttackDeley = 2.5f;
    float SwordmanSkillCooltime = 11.0f;
    float SwordmanUltCooltime = 35.0f;
};

