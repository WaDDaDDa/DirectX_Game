#pragma once
#include "GameUnit.h"

class Monk : public GameUnit
{
public:
    Monk();
    ~Monk();

    Monk(const Monk& _Other) = delete;
    Monk(Monk&& _Other) noexcept = delete;
    Monk& operator=(const Monk& _Other) = delete;
    Monk& operator=(Monk&& _Other) noexcept = delete;

    void SetUnitStatus()
    {
        UnitName = "Monk";
        AttackRange = MonkAttackRange;
        SkillRange = MonkSkillRange;
        SkillColRange = MonkSkillColRange;
        UltRange = MonkUltRange;

        UnitSpeed = MonkSpeed;
        UnitHP = MonkHp;
        UnitMaxHP = MonkHp;
        UnitAtt = MonkAtt;
        UnitDef = MonkDef;
        UnitAbsoluteDef = MonkAbsoluteDef;

        AttackSpeed = MonkAttackSpeed;

        SkillCooltime = MonkSkillCooltime;

        UltCooltime = MonkUltCooltime;
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

    void UltStart() override;
    void UltUpdate(float _Delta) override;

    void DiePrevStart() override;

private:
    float4 MonkAttackRange = { 35.0f, 0.0f };
    float4 MonkSkillRange = { 200.0f, 0.0f };
    float4 MonkSkillColRange = { 200.0f, 0.0f };
    float4 MonkUltRange = { 300.0f, 0.0f };

    float MonkSpeed = 100.0f;
    float MonkHp = 210.0f;
    float MonkAtt = 32.0f;
    float MonkDef = 40.0f;
    float MonkAbsoluteDef = 40.0f;
    float MonkAttackSpeed = 1.4f;
    float MonkSkillCooltime = 5.4f;
    float MonkUltCooltime = 30.0f;
};

