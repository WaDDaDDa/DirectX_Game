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
        SkillColRange = SwordmanSkillColRange;
        UltRange = SwordmanUltRange;

        UnitSpeed = SwordmanSpeed;
        UnitHP = SwordmanHp;
        UnitMaxHP = SwordmanHp;
        UnitAtt = SwordmanAtt;
        UnitDef = SwordmanDef;
        UnitAbsoluteDef = SwordmanAbsoluteDef;

        AttackSpeed = SwordmanAttackSpeed;

        SkillCooltime = SwordmanSkillCooltime;

        UltCooltime = SwordmanUltCooltime;
    }


protected:
    void Start() override;
    // void Update(float _Delta) override;

    void LevelStart(GameEngineLevel* _PrevLevel) override;
    void LevelEnd(GameEngineLevel* _NextLevel) override;

    bool UltCheck() override;

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

    void UltStart() override;
    void UltUpdate(float _Delta) override;

    void Ult2Start() override;
    void Ult2Update(float _Delta) override;

    void DiePrevStart() override;

private:
    float4 SwordmanAttackRange = { 90.0f, 0.0f };
    float4 SwordmanSkillRange = { 80.0f, 0.0f };
    float4 SwordmanSkillColRange = { 100.0f, 0.0f };
    float4 SwordmanUltRange = { 500.0f, 0.0f };

    float SwordmanSpeed = 120.0f;
    float SwordmanHp = 130.0f;
    float SwordmanAtt = 24.0f;
    float SwordmanDef = 30.0f;
    float SwordmanAbsoluteDef = 30.0f;
    float SwordmanAttackSpeed = 1.25f;
    float SwordmanSkillCooltime = 3.8f;
    float SwordmanUltCooltime = 25.0f;


    float SkillTick = 3.0f;
    float SkillDamageDeley = 0.1f;

    bool SwordUlt = false;
};

