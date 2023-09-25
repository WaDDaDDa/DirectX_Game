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
        UnitName = "Swordman";
        AttackRange = SwordmanAttackRange;
        SkillRange = SwordmanSkillRange;
        UltRange = SwordmanUltRange;

        UnitSpeed = SwordmanSpeed;
        UnitHP = SwordmanHp;
        UnitMaxHP = SwordmanHp;
        UnitAtt = SwordmanAtt;
        UnitDef = SwordmanDef;

        AttackDelay = SwordmanAttackSpeed;

        SkillCooltime = SwordmanSkillCooltime;

        UltCooltime = SwordmanUltCooltime;
    }


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

    void Attack2Start() override;
    void Attack2Update(float _Delta) override;

    void SkillStart() override;
    void SkillUpdate(float _Delta) override;

    void Skill2Start() override;
    void Skill2Update(float _Delta) override;

    void DiePrevStart() override;

private:
    float4 SwordmanAttackRange = { 55.0f, 55.0f };
    float4 SwordmanSkillRange = { 55.0f, 55.0f };
    float4 SwordmanUltRange = { 55.0f, 55.0f };

    float SwordmanSpeed = 100.0f;
    float SwordmanHp = 500.0f;
    float SwordmanAtt = 200.0f;
    float SwordmanDef = 10.0f;
    float SwordmanAttackSpeed = 1.25f;
    float SwordmanSkillCooltime = 3.8f;
    float SwordmanUltCooltime = 35.0f;
};

